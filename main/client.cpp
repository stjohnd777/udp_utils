//
// Created by Daniel St. John on 11/21/22.
//


#include <net.h>

#include <string>
#include <sstream>
#include <iostream>
#include <exception>
#include <chrono>

#include <boost/circular_buffer.hpp>

using namespace std;
using namespace lm::spp;
using namespace std::chrono;


PACK( struct Request
{
    uint32_t seq;
    uint64_t gpsTime;
    uint8_t cameraId;
});

PACK( struct Response
{
    uint32_t seq;
    uint64_t gpsTime;
    uint8_t cameraId;
    int retCode;
    //uint8_t matrix[600][800];
});


int main() {

    try {
        std::string host = "127.0.0.1";
        unsigned short port = 7767;
        int COUNT = 100;
        UdpUtils *udpUtil = new UdpUtils();
        for (int i = 0; i < COUNT; i++) {
 
            Request req;
            req.seq = i;
            req.gpsTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            req.cameraId = 1;
            auto bytes = lm::spp::Serialize(req);
            
            auto t = udpUtil->RequestReply(host, port, bytes, sizeof(Request));
            auto len = std::get<0>(t);
            auto pChar = std::get<1>(t);
            Response* res = lm::spp::DeSerialize<Response>(pChar.get());

        }
        cout << "cleaning up" << endl;
        delete udpUtil;
    }catch (std::exception& ex){
        cerr << ex.what() << endl;
    }

}

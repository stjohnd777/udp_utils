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


PACK(
struct Request {
    uint32_t seq =0;
    uint64_t gpsTime = 0;
    uint8_t cameraId = 0;

});

PACK(
struct Response {
    //Response() :seq(0),gpsTime(0),cameraId(0),retCode(0){}
    uint32_t seq;
    uint64_t gpsTime;
    uint8_t cameraId;
    int retCode;
});


// minimal abstraction client
// we are the UDP cleint awating a response
// we send byes
// we recieve bytes
// the conjugate class is server.cpp
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
            auto send_bytes = lm::spp::Serialize(req);

            auto t = udpUtil->RequestReply(host, port, send_bytes, sizeof(Request));

            auto len = std::get<0>(t);
            auto pChar = std::get<1>(t);
            Response *res = lm::spp::DeSerialize<Response>(pChar.get());

        }

        delete udpUtil;
    } catch (std::exception &ex) {
        cerr << ex.what() << endl;
    }

}

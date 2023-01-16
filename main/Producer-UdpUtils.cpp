//
// Created by Daniel St. John on 11/21/22.
//


#include <net.h>

#include <string>
#include <iostream>
#include <exception>
#include <chrono>


using namespace std;
 
using namespace std::chrono;

PACK(struct Request
             {
                 uint32_t seq;
                 uint64_t gpsTime;
                 uint8_t cameraId;
             });

PACK(struct Response
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
        int COUNT = 1000;
        UdpUtils *udpUtil = new UdpUtils();
        for (int i = 0; i < COUNT; i++) {
            Request req;
            req.seq = i;
            req.gpsTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            req.cameraId = 1;
            auto bytes = lm::spp::Serialize(req);
            stringstream ss;
            ss << "Sending Some Data " << bytes << endl;
            udpUtil->SendTo(host, port, bytes, sizeof(Request));
            cout << "sent:" << req.seq << ":" << req.gpsTime << ":" << req.cameraId << endl;
            std::this_thread::sleep_for(1000ms);
        }
        cout << "cleaning up" << endl;
        delete udpUtil;
    } catch (std::exception &ex) {
        cerr << ex.what() << endl;
    }

}

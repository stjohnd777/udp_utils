//
// Created by Daniel St. John on 11/21/22.
//


#include <net.h>

#include <string>
#include <iostream>
#include <tuple>


using namespace std;
 

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

    bool isRunning = true;
    std::string host = "127.0.0.1";
    unsigned short port = 7767;
    UdpUtils udpUtil;
    while (isRunning) {
        auto t = udpUtil.ServerReceiveNoReply(host, port);
        auto len = get < 0 > (t);
        auto pChar = std::get<1>(t);
        Request *req = lm::spp::DeSerialize<Request>(pChar.get());
        cout << "receive:" << req->seq << ":" << req->gpsTime << ":" << req->cameraId << endl;

    }

}

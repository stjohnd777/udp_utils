//
// Created by Daniel St. John on 11/21/22.
//


#include <net.h>

#include <string>
#include <iostream>
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


// mid level abstraction client
// templated
// we are the UDP client awating a response
// we send Request
// we recieve Responce
// the conjugate class is server_struct.cpp
int main() {

    bool isRunning = true;
    std::string host = "127.0.0.1";
    unsigned short port = 7767;


    for (auto i = 0; i < 100; i++) {

        Request req;
        req.seq = i;
        req.gpsTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        req.cameraId = 1;
        cout << "Send Request[" << req.seq << "," << req.gpsTime << "," << req.cameraId << "]" << endl;

        auto res = UdpRequestReply<Request, Response>(host, port, req);
        cout << "Get Response Request[" << res->seq << "," << res->gpsTime << "," << res->cameraId << ":"
             << res->retCode << "]" << endl;

        std::this_thread::sleep_for(10000ms);
    }

    return 0;

}

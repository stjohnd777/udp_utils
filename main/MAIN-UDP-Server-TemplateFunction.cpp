//
// Created by Daniel St. John on 11/21/22.
//


#include <net.h>

#include <string>
#include <iostream>
#include <chrono>


using namespace std;
using namespace lm::spp;
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

// Server part of Client/Server Model
// client_struct.cpp is conjugate to the class
// mode here is process to process of host to host

// mid level abstraction server
// we are the UDP service here
// templated
// we receive Request struct
// we reply to requester with Request
// we send bytes
int main() {

    bool isRunning = true;
    std::string host = "127.0.0.1";
    unsigned short port = 7767;

    // notice the server is implemented by suppling a handler with the signature below
    // lambda here to keep the code tight
    auto provider = [&](Request *req) {
        Response *res = new Response();
        res->seq = req->seq;
        res->gpsTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        res->cameraId = req->cameraId;
        res->retCode = 99;
        return res;
    };

    bool running = true;
    std::thread t([&]() {
        cout << "server running" << endl;
        while (running) {
            cout << "server blocking read" << endl;
            UpdReceiveReplyOne<Request, Response>(host, port, provider);
            cout << "process request" << endl;
        }
        cout << "server exiting" << endl;
    });

    t.join();

    return 0;

}

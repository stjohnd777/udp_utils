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
});

// Server part of Client/Server Model
// client_class.cpp is conjugate to the class
// mode here is process to process of host to host

// abstraction server
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
    UdpServer<Request,Response> server(host,port);
    server.StartReqRes([&](Request* req){
        cout << req->cameraId << ":" << req->gpsTime << ":"  << req->seq << endl;
        Response* res = new Response();
        return res;
    });

    return 0;

}

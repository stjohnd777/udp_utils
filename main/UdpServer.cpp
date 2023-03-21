//
// Created by Daniel St. John on 11/21/22.
//


#include <net.h>

#include <string>
#include <iostream>
#include <chrono>
#include <thread>


using namespace std;

using namespace std::chrono;


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


    // server is implemented by supplying a handler with the signature below

    thread t([&]() {
        UdpServer<Request, Response> server(host, port);
        server.Start([&](Request *req) {
            cout << req->cameraId << ":" << req->gpsTime << ":" << req->seq << endl;
            Response *res = new Response();
            return res;
        });
    });

    //std::this_thread::sleep_for(1000ms);
    return 0;

}

#define CATCH_CONFIG_MAIN // provides main(); this line is required in only one .cpp file
#include "catch.hpp"

#include <iostream>
#include <vector>
#include <sstream>
#include <chrono>
#include <algorithm>
#include <thread>
#include <net.h>

#include "teststructs.h"

using namespace std;
using namespace lm::spp;
using namespace std::chrono;


std::string host = "127.0.0.1";
unsigned short port = 7767;

TEST_CASE( "T2T-UdpClientServer-TemplateClass-TEST", "Request-Reply" ) {
    
    REQUIRE( true == true );

    UdpServer<Request, Response> server(host, port);
    thread t([&]() {
        server.StartReqRes([&](Request* req){
            static unsigned int count = 1;
            cout << "Server Received:[" << req->seq << "," << req->gpsTime << "," << req->cameraId << "]" << endl;
            REQUIRE(req->seq == count);
            REQUIRE(req->gpsTime == count);
            REQUIRE(req->cameraId == count);

            Response* res = new Response();
            res->seq = req->seq;
            res->gpsTime = req->gpsTime;
            res->cameraId = req->cameraId;
            res->retCode = count;
            count++;
            cout << "Server Sent:[" << res->seq << "," << res->gpsTime << "," << res->cameraId << "," << res->retCode << "]" << endl;

            return res;
        });
    });



    UdpClient<Request,Response> client(host,port);
    for ( auto i =1; i < 10 ; i++){
        Request req = { 0 };
        req.seq = i;
        req.gpsTime = i;
        req.cameraId = i;
        cout << "Client Sends:[" << req.seq << "," << req.gpsTime << "," << req.cameraId << "]" << endl;
        auto res = client.RequestReply(req);
        cout << "Client Received:[" << res->seq << "," << res->gpsTime << "," << res->cameraId << "," << res->retCode << "]" << endl;
        REQUIRE(res->seq == i);
        REQUIRE(res->gpsTime == i);
        REQUIRE(res->cameraId == i);
        REQUIRE(res->retCode == i);

        std::this_thread::sleep_for(1000ms);
    }
    server.Stop();
    std::this_thread::sleep_for(1000ms);

    cout << "Exit Test" << endl;

}
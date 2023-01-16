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


int main() {

    bool isRunning = true;
    std::string host = "127.0.0.1";
    unsigned short port = 7767;

    UdpClient<Request,Response> client(host,port);
    for ( auto i=0;i<100;i++){
        Request req = {static_cast<uint32_t>(i),static_cast<uint64_t>(2*i),static_cast<uint8_t>(3*i)};
        Response* res = client.RequestReply(req);
        cout << res->cameraId << ":" << res->gpsTime << ":" << res->seq << ":" << res->retCode << endl;
        delete res;
        std::this_thread::sleep_for(1000ms);
    }
    
    return 0;

}

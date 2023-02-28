//
// Created by Daniel St. John on 11/21/22.
//


#include <net.h>

#include <string>
#include <iostream>
#include <chrono>
#include <tuple>
#include <memory>



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

    bool isRunning = true;
    std::string host = "127.0.0.1";
    unsigned short port = 7767;
    UdpUtils udpUtil;

    while (isRunning) {

        // notice the server is implemented by suppling a handler with the signature below
        // lambda here to keep the code tight
        udpUtil.ReceiveReply(host, port, [&](std::tuple<size_t, std::shared_ptr<uint8_t[]>> req) {

            // Get request as bytes and number of bytes (length)
            auto len = std::get<0>(req);
            auto pChar = std::get<1>(req);

            // do whatever you need with the bytes, here as example we have bytes as Request struture
            // and ofcource clear voince is need on what this structure is
            Request *request = DeSerialize<Request>(pChar.get());
            cout << "receive:" << request->seq << ":" << request->gpsTime << ":" << request->cameraId << endl;

            // we retrun whatever is need in bytes/lenght. Here as example we serialize the structure
            Response response;
            response.seq = request->seq;
            response.gpsTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            response.cameraId = request->cameraId;

            auto bytesOut = Serialize<Response>(response);
            size_t size_bytes_out = sizeof(Response);
            std::shared_ptr<uint8_t[]> sp(new uint8_t[size_bytes_out]);
            memcpy(sp.get(), bytesOut, size_bytes_out);

            // sending byes back the endpoint that made the request
            auto res = std::make_tuple(size_bytes_out, sp);
            return res;
        });
    }

    return 0;

}

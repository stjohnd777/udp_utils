//
// Created by Daniel St. John on 11/21/22.
//


#include <net.h>

#include <string>
#include <iostream>
#include <chrono>
#include <tuple>
#include <memory>
#include <boost/array.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
using namespace lm::spp;
using namespace std::chrono;

PACK( struct Request
{
    uint32_t seq;
    uint64_t gpsTime;
    uint8_t cameraId;
});

PACK( struct Response
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

    while ( isRunning) {

        udpUtil.ReceiveReply(host, port, [&]( std::tuple<size_t,std::shared_ptr<char[]>> req) {

            // Get request Data
            auto len = std::get<0>(req);
            auto pChar = std::get<1>(req);
            Request* request = lm::spp::DeSerialize<Request>(pChar.get());
            cout << "receive:" << request->seq << ":" << request->gpsTime << ":" << request->cameraId << endl;

            Response response;
            response.seq = request->seq;
            response.gpsTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            response.cameraId = request->cameraId;


            // string img = "C:/Users/e438262/dev/github/udp_client_server/data/702HP_Satellite-Boeing.jpg";
            // Mat image = imread(img,IMREAD_GRAYSCALE);
            
            // int down_width = 800;
            // int down_height = 600;
            // Mat resized_down;
            // resize(image, resized_down, Size(down_width, down_height), INTER_LINEAR);
            // size_t size_down =  sizeof(resized_down);


            auto bytesOut = Serialize<Response>(response);
            size_t size_bytes_out = sizeof(Response);
            std::shared_ptr<char[]> sp(new char[size_bytes_out]);
            memcpy(sp.get(), bytesOut, size_bytes_out);     
 
            auto res = std::make_tuple(size_bytes_out,sp);
            return res;
        });
    }

    return 0;

}

//
// Created by Daniel St. John on 11/21/22.
//


#include <net.h>

#include <string>
#include <iostream>
#include <tuple>


#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace std;

#define ROWS 1080
#define COLS 1920
#define DEPTH 1

struct Frame {
    uint32_t seq;
    double gpsTime;
    uint8_t cameraId;
    char img[ROWS*COLS*DEPTH];
};

int main() {

    bool isRunning = true;
    std::string host = "127.0.0.1";
    unsigned short port = 7767;
    UdpUtils udpUtil;

    while (isRunning) {
        auto t = udpUtil.ServerReceiveNoReply(host, port);
        auto len = get < 0 > (t);
        auto pChar = std::get<1>(t);
        Frame *req = DeSerialize<Frame>(pChar.get());
        cv::Mat m(ROWS,COLS,DEPTH);
        m.data = reinterpret_cast<uchar *>(req->img);
        cv::imshow("streamed",m);
    }

}

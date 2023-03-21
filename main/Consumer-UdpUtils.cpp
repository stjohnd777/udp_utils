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
        cv::Mat m(HEIGHT,WIDTH,CHANNEL_DEPTH);
        m.data = reinterpret_cast<uchar *>(req->img);
        cv::imshow("streamed",m);
    }

}

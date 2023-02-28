//
// Created by Daniel St. John on 11/21/22.
//


#include <net.h>

#include <string>
#include <iostream>
#include <exception>
#include <chrono>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/videoio.hpp>

using namespace std;
 
using namespace std::chrono;

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

    try {
        std::string host = "127.0.0.1";
        unsigned short port = 7767;
        int COUNT = 1000;
        UdpUtils *udpUtil = new UdpUtils();
        for (int i = 0; i < COUNT; i++) {

            Frame aFrame ;
            aFrame.seq = i++;
            aFrame.gpsTime = duration_cast < milliseconds> (system_clock::now().time_since_epoch()).count();

            string imageSeed ="/home/overman/dev/github/_my/udp_utils/main/data/ori.jpg";
            cv::Mat in = imread(imageSeed, cv::IMREAD_GRAYSCALE);

            memcpy(aFrame.img ,in.data,ROWS*COLS*DEPTH);


            auto bytes = Serialize(aFrame);
            stringstream ss;
            ss << "Sending Some Data " << bytes << endl;
            udpUtil->Send(host, port, bytes, sizeof(Frame));

            std::this_thread::sleep_for(1000ms);
        }
        cout << "cleaning up" << endl;
        delete udpUtil;
    } catch (std::exception &ex) {
        cerr << ex.what() << endl;
    }

}

#include "net.h"

#include <tuple>
#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int StartTcpImageServer(std::string ip = "127.0.0.1" , unsigned short port = 7767 ) {

    bool isRunning = true;
    VideoCapture *pVideoCapture = new VideoCapture(0);
    if (!pVideoCapture->isOpened()) {
        return -1;
    }
    if (!pVideoCapture->isOpened()) {
        delete pVideoCapture;
        return -2;
    }

    auto srv = new SyncTcpServer(ip, port);
    int service_count = 0;
    while (isRunning) {
        srv->StartListeningAndHandleOneRequest([&](int cameraId, double time) {
            cv::Mat aCameraFrame;
            *(pVideoCapture) >> aCameraFrame;
            cvtColor(aCameraFrame, aCameraFrame, COLOR_BGR2GRAY);
            size_t len = aCameraFrame.rows * aCameraFrame.cols * aCameraFrame.elemSize();
            char *bytesToTransfer = new char[len];
            memset(bytesToTransfer, 0, len);
            memcpy(bytesToTransfer, aCameraFrame.data, len);
            auto tup = make_tuple(len, bytesToTransfer);
            return tup;
        });
        service_count++;
        cout << "server handled request " << service_count << endl;
    }
    delete srv;
    delete pVideoCapture;
    return 0;
}

int main() {
    StartTcpImageServer();
    return 0;
}
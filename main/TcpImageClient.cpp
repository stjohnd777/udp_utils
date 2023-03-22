#include <chrono>
#include <tuple>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

#include "net.h"

int main() {

    //const std::string host = "192.168.1.12";
    const std::string host = "127.0.0.1";
    const unsigned short port = 7767;
    int cameraId = 0;

    int height = 720;
    int width = 1280;

    bool isRunning = true;
    stringstream ss;
    ss << "Camera: " << cameraId << ":" << width << "x" << height << ":" << "tcp@" << host << ":" << port;
    string windowName = ss.str();
    cv::Mat img(height, width, cv::IMREAD_GRAYSCALE);
    cv::imshow(windowName, cv::WINDOW_AUTOSIZE);

    auto start = std::chrono::system_clock::now();

    while (isRunning) {
        SyncTcpClient client(host, port);

        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> diff = end - start;
        double time = diff.count(); // GPS TIME
        cout << "client request cameraId: " << cameraId << " time:" << time << endl;
        auto tupResponse = client.request_reply(time, cameraId);

        size_t numberBytesReply = get<0>(tupResponse);
        const char *bytesReply = get<1>(tupResponse);

        if (numberBytesReply == 0) {
            cout << "Zero bytes return " << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            continue;
        }
        if (numberBytesReply == 1) {
            cout << "Error Code Returned: " << (int) bytesReply[0] << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            continue;
        }

        memcpy(img.data, bytesReply, numberBytesReply);
        //cout << img.data << endl;
        cv::imshow(windowName, img);
        if (cv::waitKey(0) == 27) {
            isRunning = false;
        }
//        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
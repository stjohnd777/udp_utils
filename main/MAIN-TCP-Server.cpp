#include <net.h>
#include <tuple>
#include <iostream>
 
 

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#define WIDTH 2672
#define HEIGHT 1952
#define CHANNEL 2
// 5,215,744  bytes   5215744
// 10,431,488 bytes

string image_path = "../img/cat.2672x1952.grey16.png";

struct GncInputBus {

};

auto handler = [&](int cameraId, double time)
{
    GncInputBus gncData;
    size_t len = sizeof(GncInputBus);
    char* bytes =  Serialize<GncInputBus>(gncData);
    cout << "Handler Provided cameraId:" << cameraId << ", time:" << time << endl;
    char *dst = new char[WIDTH * HEIGHT * CHANNEL];
    memset(dst, 0, WIDTH * HEIGHT * CHANNEL);
    
    cv::Mat img = cv::imread(image_path, CV_16SC1);
    // cv::imshow("Display", img);
    // int k = cv::waitKey(0);

    int image_size = img.total();
    memcpy(dst, img.data, image_size);
    memcpy(dst,bytes,len);

    cout << "Handler Returning Image with: " << image_size << " bytes" << endl;
    auto tup = make_tuple(image_size, dst);
    return tup;
};

int main()
{

    auto srv = new SyncTCPServer(7767);
    bool isRunning = true;
    int service_count = 0;
    while (isRunning)
    {
        auto image = srv->StartOne(handler);
        service_count++;
        cout << "server handled request " << service_count << endl;
    }
    srv->Stop();

    delete srv;
    return 0;
}
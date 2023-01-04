#define CATCH_CONFIG_MAIN // provides main(); this line is required in only one .cpp file
#include "catch.hpp"

#include <net.h>
#include <tuple>

 

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#define WIDTH   2672
#define HEIGHT  1952
#define CHANNEL 2
// 5,215,744  bytes   5215744
// 10,431,488 bytes

string image_path = "C:/Users/e438262/dev/lm/gitlab/udp_utils/img/cat.2672x1952.grey16.png";

auto handler = [&](int cameraId, double time) {

    cout << "Handler Provided cameraId:" << cameraId << ", time:" << time << endl;
    char* dst = new char[WIDTH*HEIGHT * CHANNEL];
    memset(dst, 0, WIDTH* HEIGHT* CHANNEL);
    cv::Mat img = cv::imread(image_path, CV_16SC1);
    //cv::imshow("Display", img);
    //int k = cv::waitKey(0);
    int image_size = img.total();
    memcpy(dst, img.data, image_size);

    cout << "Handler Returning Image with: " << image_size << " bytes" << endl;
    auto tup = make_tuple(image_size, dst);
    return tup;
};


TEST_CASE( "Server Request Reply TCP", "Hello" ) {

    //char* dst = new char[WIDTH * HEIGHT * CHANNEL];
    //cv::Mat img = cv::imread(image_path, CV_16SC1);
    //cv::imshow("Display window", img);
    //int k = cv::waitKey(0);


    const std::string host = "127.0.0.1";
 
    REQUIRE( true == true );

    volatile bool isRunning = false;
    volatile bool isReady = false;
    volatile bool isShutdown = true;
    thread thread_srv([&]() {
        auto srv = new SyncTCPServer(7767);
        isRunning = true;
        int service_count = 0;
        while (isRunning) {
            isReady = true;
            auto image = srv->StartOne(handler);
            service_count++;
            cout << "server handled request " <<  service_count << endl;
        }
        srv->Stop();
        delete srv;
    });

    while (!isReady) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  
    std::this_thread::sleep_for(std::chrono::seconds(1));

    thread thread_client( [&]() {
        SyncTCPClient client(host, 7767);
        for (auto i = 0; i < 10; i++) {
            //cout << "client send request cameraId:" << i << "time:" << i << endl;
            auto tup = client.request_reply(i, i);
            size_t len = get<0>(tup);
            const char* image = get<1>(tup);
            //cout << "client received response bytes" << len << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        isRunning = false;
        }
    );
   
    thread_srv.join();
    thread_client.join();
}
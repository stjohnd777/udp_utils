#include <net.h>
#include <tuple>

 
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#define WIDTH 2672
#define HEIGHT 1952
#define CHANNEL 2

int main()
{
    const std::string host = "127.0.0.1";

    
    for (auto i = 0; i < 1000; i++)
    {
        SyncTCPClient client(host, 7767);
        cout << "client send request cameraId:" << i << "time:" << i << endl;
        auto tup = client.request_reply(i, i);
        size_t len = get<0>(tup);
        const char *image = get<1>(tup);
        cout << "client received response bytes" << len << endl;

        // cv::Mat img(WIDTH,HEIGHT, CV_8SC1);
        // img.data = (uchar*) image;
        // stringstream ss;
        // ss << "Camera:" << i << " time:" << i << endl;
        // cv::imshow(ss.str(), img);
        // int k = cv::waitKey(0);

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}
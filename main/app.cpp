
#include <string>
#include <memory>
#include <thread>
#include <vector>
#include <boost/circular_buffer.hpp>


 

#include "helix.h"
#include "Props.h"
#include <net.h>

using namespace std;
using namespace lm::spp;

typedef unsigned short PORT;

string host = "127.0.0.1";

PORT port1 = 7767;
PORT port2 = 7768;
PORT port3 = 7769;
PORT port4 = 7770;
PORT port5 = 7771;
PORT port6 = 7772;

bool isRunning0 = true;
bool isRunning1 = true;
bool isRunning2 = true;
bool isRunning3 = true;
bool isRunning4 = true;
bool isRunning5 = true;
bool isRunning6 = true;

REQ_REPLY_HANDLER providerCamera1 = [&](std::tuple<size_t, std::shared_ptr<char[]>> req)
{
    auto len = std::get<0>(req);
    auto pChar = std::get<1>(req);
     

    // DO CODE HERE
    char *bytesOut[MAX_DATAGRAM];
    size_t size_bytes_out = 1024; // sizeof(Response);
    std::shared_ptr<char[]> sp(new char[size_bytes_out]);
    memcpy(sp.get(), bytesOut, size_bytes_out);

    auto res = std::make_tuple(size_bytes_out, sp);
    return res;
};
REQ_REPLY_HANDLER providerCamera2 = providerCamera1;
REQ_REPLY_HANDLER providerCamera3 = providerCamera1;
REQ_REPLY_HANDLER providerCamera4 = providerCamera1;
REQ_REPLY_HANDLER providerCamera5 = providerCamera1;
REQ_REPLY_HANDLER providerCamera6 = providerCamera1;




auto camera_server = [&](string host, PORT port, REQ_REPLY_HANDLER serviceProvider)
{
    auto pThread = new thread([&]()
                              {
        UdpUtils udpUtil;
        while (isRunning1) {
            udpUtil.ReceiveReply(host, port, serviceProvider);
        }; });
    return pThread;
};


bool shutdown() {
    // TODO
    return false;
}


void logger() {
    // TODO
}

int main()
{
    boost::circular_buffer<GncInputBus*> circular_buffer(100);

    auto truth_consumer = [&](string host, PORT port)
    {
        auto pThread = new thread([&]() {
            UdpUtils udpUtil;
            while (isRunning1) {
                auto t = udpUtil.ServerReceiveNoReply(host, port);
                auto len = get<0>(t);
                auto pChar = std::get<1>(t);
                GncInputBus* req = lm::spp::DeSerialize<GncInputBus>(pChar.get());
                circular_buffer.push_back(req);
            };
            });
        return pThread;
    };

    auto pThreadCameraServer1 = camera_server(host, port1, providerCamera1);
    auto pThreadCameraServer2 = camera_server(host, port2, providerCamera2);
    auto pThreadCameraServer3 = camera_server(host, port3, providerCamera3);
    auto pThreadCameraServer4 = camera_server(host, port4, providerCamera4);
    auto pThreadCameraServer5 = camera_server(host, port5, providerCamera5);
    auto pThreadCameraServer6 = camera_server(host, port6, providerCamera6);

    while (true) {
        if (shutdown()) {
            bool isRunning0 = false;
            bool isRunning1 = false;
            bool isRunning2 = false;
            bool isRunning3 = false;
            bool isRunning4 = false;
            bool isRunning5 = false;
            bool isRunning6 = false;
        }
    } 

    pThreadCameraServer1->join();
    pThreadCameraServer2->join();
    pThreadCameraServer3->join();
    pThreadCameraServer4->join();
    pThreadCameraServer5->join();
    pThreadCameraServer6->join();

    return 0;
}
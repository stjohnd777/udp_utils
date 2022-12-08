#define CATCH_CONFIG_MAIN // provides main(); this line is required in only one .cpp file
#include "catch.hpp"
#include <net.h>
#include <iostream>
#include <sstream>
#include <iostream>
#include <thread>
#include <chrono>
#include <tuple>
#include <functional>
#include <memory>
#include <algorithm>

#include <boost/circular_buffer.hpp>


#include "teststructs.h"

using namespace std;
using namespace lm::spp;
using namespace std::chrono;


void HaltMainForSec(unsigned short seconds) {
    std::cout << "Main thread pause for " << seconds <<  std::endl;
    std::this_thread::sleep_for(seconds * 1000ms);
    std::this_thread::sleep_for(1000ms);
}


/*
* Producer/Comsumer
*
* TEST sending a bytes
*
* Comsumer and Producer in seperate threads.
*/
TEST_CASE("T2T-ProducerConsumer", "With Bytes") {

    bool isRunning = true;
    std::string host = "127.0.0.1";
    unsigned short port = 7767;

    char bytes[1000];
    std::generate(bytes, bytes + 1000, [n = 0]() mutable { return n++; });

    auto producer = [&]() {
        UdpUtils udpUtil;
        udpUtil.SendTo(host, port, bytes, 1000);
    };
    thread thread_producer(producer);


    auto consumer = [&]() {
        UdpUtils udpUtil;
        auto tup = udpUtil.ServerReceiveNoReply(host, port);
        size_t bytes_recv = get<0>(tup);
        std::shared_ptr<char[]> sp = get<1>(tup);
        cout <<  bytes_recv << endl;
        for (auto i=0; i < bytes_recv; i++) {
            char c = *(sp.get() + i);
            cout <<c << ":";
            if (i % 10 == 0) {
                cout << endl;
            }
            REQUIRE(bytes[i] == c);
        }
        cout << endl;
    };
    thread thread_consumer(consumer);

    thread_producer.join();
    thread_consumer.join();
}
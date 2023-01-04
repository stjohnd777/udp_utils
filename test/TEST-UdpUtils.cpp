#define CATCH_CONFIG_MAIN // provides main(); this line is required in only one .cpp file
#include "catch.hpp"
#include <net.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <tuple>
#include <functional>
#include <memory>

#include <cstddef>
#include <vector>

#include <boost/circular_buffer.hpp>

#include "teststructs.h"

using namespace std;
using namespace lm::spp;
using namespace std::chrono;

std::string host = "127.0.0.1";
unsigned short port = 7767;


 
using namespace lm::spp;

TEST_CASE("UdpUtils", "()")
{
    UdpUtils udp;
    REQUIRE( true == true);

}

TEST_CASE("UdpUtils::SendTo/ServerReceiveNoReply", "SendTo/ServerReceiveNoReply")
{
    char bytes[1000];
    std::generate(bytes, bytes + 1000, [n = 0]() mutable { return n++; });

    bool ready = false;

    auto consumer = [&]() {
        IUdpServer* server = new UdpUtils();
        ready = true;
        auto tup = server->ServerReceiveNoReply(host, port);
        size_t bytes_rcv = get < 0 > (tup);
        std::shared_ptr<char[]> sp = get<1>(tup);
        std::cout << bytes_rcv << endl;
        for (auto i = 0; i < bytes_rcv; i++) {
            char c = *(sp.get() + i);
            std::cout << c << ":";
            if (i % 10 == 0) {
                std::cout << endl;
            }
            REQUIRE(bytes[i] == c);
        }
        delete server;
        std::cout << endl;
    };
    thread thread_consumer(consumer);


    IUdpClient*  producer = new  UdpUtils ();

    while (!ready);

    producer->SendTo(host, port, bytes, 1000);
    delete producer;
    std::this_thread::sleep_for(1000ms);

    thread_consumer.join();

    REQUIRE(true == true);
}

TEST_CASE("UdpUtils::RequestReply/ReceiveReply", "RequestRepl/ReceiveReply")
{
    bool isRunning = true;
    bool isReady = false;
 
    thread server_thread ([&](string host, unsigned short port) {
        IUdpServer* echoServer = new  UdpUtils();
        isReady = true;
        echoServer->ReceiveReply(host, port, 
            [&](std::tuple<size_t, std::shared_ptr<char[]>> req) {
                auto len = std::get<0>(req);
                auto pChar = std::get<1>(req);

                if (len == 1) {
                    isRunning = false;
                }

                std::shared_ptr<char[]> sp(new char[len]);
                memcpy(sp.get(),pChar.get(),len);
                   
                auto res = std::make_tuple(len, sp);
                return res;
            });
        std::cout << "Server Thread exiting" << std::endl;
    }, host, port);

    while (!isReady);

    IUdpClient* client = new UdpUtils();
    char bytes[1000];
    std::generate(bytes, bytes + 1000, [n = 0]() mutable { return n++; });
    auto reply = client->RequestReply(host, port, bytes, 1000);
    size_t bytes_recv = get<0>(reply);

    REQUIRE(bytes_recv == 1000);

    std::shared_ptr<char[]> sp = get<1>(reply);
    std::cout << bytes_recv << endl;
    for (auto i = 0; i < bytes_recv; i++) {
        char c = *(sp.get() + i);
        std::cout << c << ":";
        if (i % 10 == 0) {
            std::cout << endl;
        }
        REQUIRE(bytes[i] == c);
    }
    std::cout << endl;

    server_thread.join();
    REQUIRE(true == true);

}

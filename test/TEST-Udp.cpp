#define CATCH_CONFIG_MAIN // provides main(); this line is required in only one .cpp file

#include "catch.hpp"
#include <net.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <tuple>
#include <memory>
#include <vector>

#include "teststructs.h"

using namespace std;
using namespace std::chrono;

std::string host = "127.0.0.1";
unsigned short port = 7767;


TEST_CASE("UdpUtils", "constructor")
{
    UdpUtils *udp = new UdpUtils();
    REQUIRE(udp != nullptr);
    delete udp;
    REQUIRE(true == true);
}

TEST_CASE("Produce-Consume", "Bytes")
{
    uint8_t bytes[128];
    std::generate(bytes, bytes + 128, [n = 0]() mutable { return n++; });

    bool ready = false;
    auto consumer = [&]() {
        UdpUtils *server = new UdpUtils();
        ready = true;
        std::tuple<size_t, std::shared_ptr<uint8_t[]>> tup = server->ServerReceiveNoReply(host, port);
        size_t numBytesRcv = get<0>(tup);
        std::shared_ptr<uint8_t[]> sp = get<1>(tup);
        std::cout << numBytesRcv << endl;
        for (auto i = 0; i < numBytesRcv; i++) {
            uint8_t c = *(sp.get() + i);
            std::cout << c << ":";
            if (i > 0 && i % 10 == 0) {
                std::cout << endl;
            }
            REQUIRE(bytes[i] == c);
        }
        delete server;
        std::cout << endl;
    };
    thread thread_consumer(consumer);
    while (!ready);

    UdpUtils *producer = new UdpUtils();
    producer->Send(host, port, bytes, 128);
    delete producer;

    thread_consumer.join();

    REQUIRE(true == true);
}

TEST_CASE("Request-Reply", "bytes")
{
    bool isRunning = true;
    uint8_t bytes[128];
    std::generate(bytes, bytes + 128, [n = 0]() mutable { return n++; });

    auto echoServer = [&]() {
        UdpUtils udp;
        while (isRunning) {
            udp.ReceiveReply(host, port, [&](std::tuple<size_t, std::shared_ptr<uint8_t[]>> t) {
                size_t len = get<0>(t);
                REQUIRE(len == 128);
                uint8_t *data = get<1>(t).get();
                for (auto i = 0; i < 128; i++) {
                    REQUIRE(*(data + i) == i);
                }
                std::shared_ptr<uint8_t[]> sp(new uint8_t[len]);
                memcpy(sp.get(), data, len);
                return make_tuple(len, sp);
            });
        }
        cout << "echo server exit" << endl;
    };
    thread thread_server(echoServer);

    auto echoClient = [&]() {
        UdpUtils udp;
        for (auto j = 0; j < 3; j++) {
            std::tuple<size_t, std::shared_ptr<uint8_t[]>> res = udp.RequestReply(host, port, bytes, 128);
            size_t len = get<0>(res);
            REQUIRE(len == 128);
            uint8_t *data = get<1>(res).get();
            for (auto i = 0; i < 128; i++) {
                REQUIRE(*(data + i) == i);
            }
        }
        cout << "echo client exit" << endl;
        isRunning = false;
        udp.RequestReply(host, port, bytes, 128);
    };
    thread thread_client(echoClient);

    thread_client.join();
    thread_server.join();

    cout << "done " << endl;
}

TEST_CASE("UdpProducer", "UdpConsumer")
{
    UdpConsumer<Request> consumer(host, port);

    auto t = consumer.Listen(
            [&](Request *req) {
                cout << req->seq << endl;
                delete req;
            }
    );

    for (auto i = 0; i < 10; i++) {
        Request req = {static_cast<uint8_t>(i), static_cast<uint64_t>(i), static_cast<uint32_t>(i)};
        Send<Request>(host, port, req);
    }

    consumer.Stop();
    Request req = {static_cast<uint8_t>(0), static_cast<uint64_t>(0), static_cast<uint32_t>(0)};

    Send<Request>(host, port, req);
    t->join();
}

TEST_CASE("UdpClient", "UdpServer")
{
    UdpServer<Request, Response> server(host, port);
    auto t = server.Start([&](Request *req) {
        cout << req->gpsTime << endl;
        Response *res = new Response();
        cout << "server: " <<  req->gpsTime << endl;
        return res;
    });

    for (auto i = 0; i < 10; i++) {
        Request req = {static_cast<uint8_t>(i), static_cast<uint64_t>(i), static_cast<uint32_t>(i)};
        Response *res = RequestReply<Request, Response>(host, port, req);
        cout << "client: " << res->gpsTime << endl;
    }
    server.Stop();
    Request req = {static_cast<uint8_t>(0), static_cast<uint64_t>(0), static_cast<uint32_t>(0)};
    Response *res = RequestReply<Request, Response>(host, port, req);
    t->join();

//
//    UpdClient<Request,Response> client ()
//

}
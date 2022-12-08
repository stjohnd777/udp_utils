#define CATCH_CONFIG_MAIN // provides main(); this line is required in only one .cpp file

#include "catch.hpp"
#include <net.h>
#include <iostream>
#include <sstream>
#include <iostream>
#include <thread>
#include <tuple>
#include <chrono>
#include <algorithm>

 

#include "teststructs.h"

using namespace std;
using namespace lm::spp;
using namespace std::chrono;

 
TEST_CASE( "T2T-RequestReplyAsync", "1" ) 
{
    REQUIRE( true == true );
    bool isRunning = true;
    std::string host = "127.0.0.1";
    unsigned short port = 7767;

    UdpUtils server; 
    server.AsyncReceiveReply<Request>(host, port, 
        [&](const boost::system::error_code& error, size_t bytes_transferred) {
            std::lock_guard<std::mutex> guard(server.m_async_buffer_mutex);
            std::cout << "Bytes Recieved:" << bytes_transferred << std::endl;
            for (auto b : server.async_reciev_buffer) {
                std::cout << b << ".";
            }
            std::cout << std::endl;
            for (auto b : server.async_reciev_buffer) {
                std::cout << lm::spp::toBinaryString(b) << ".";
            }
            std::cout << std::endl;
        }
    );

 
    UdpUtils client;
    int send_count = 0;
    int count = 0;
    while (isRunning) 
    {
        Request req ={ count, duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count(),1};
        char* bytesReq = lm::spp::Serialize(req);
        cout << "sending thread:" << std::this_thread::get_id()  << ":" << bytesReq << " len:" << sizeof(Request) << endl;
        
        auto tupleRes = client.RequestReply(host,port,bytesReq,sizeof(Request));

        auto len_res = std::get<0>(tupleRes);
        auto bytesRes = std::get<1>(tupleRes);
        Response* res = lm::spp::DeSerialize<Response>(bytesRes.get());

        std::this_thread::sleep_for(1000ms);
    }
}
 
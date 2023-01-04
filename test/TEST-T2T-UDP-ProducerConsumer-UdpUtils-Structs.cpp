#define CATCH_CONFIG_MAIN // provides main(); this line is required in only one .cpp file
#include "catch.hpp"
#include <net.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <tuple>
#include <functional>


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
* Producer/Consumer
* 
* TEST sending a packed serialized structure over the wire
* in fire and forget mode (Producer). 
*
* The TEST uses the lower level api UdpUtils
*
* Hence, works with bytes.
* 
* In such user is responsible for serializing 
* the struct.  
* 
* Consumer and Producer in separate threads.
*/
TEST_CASE( "T2T-ProducerConsumer", "With Structs" ) {
    REQUIRE( true == true );

    bool isRunning = true;
    std::string host = "127.0.0.1";
    unsigned short port = 7767;

    std::vector<Request> vsent;
    std::vector<Request*> vrecv;
    /*
    * Producer
    */
        auto startSending = [&,isRunning](string host, unsigned short port) {
            auto t = new thread([&](string host, unsigned short port) {
                UdpUtils udpUtil;
                int send_count = 0;
                while (isRunning) {
                    Request req;
                    req.seq = send_count;
                    req.gpsTime =  duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
                    req.cameraId = 1;
                    auto bytes = lm::spp::Serialize(req);
                    stringstream ss;
                    ss << "Sending Some Data " << bytes << endl;
                    udpUtil.SendTo(host, port,bytes,sizeof(Request));
                    vsent.push_back(req);
                    cout << "sent:" << req.seq << ":" << req.gpsTime << ":" << req.cameraId << endl;

                    std::this_thread::sleep_for(1000ms);
                    send_count++;
   
                }
                std::cout << "thread:" << std::this_thread::get_id()  << " Sender Exiting" << std::endl;
                },host,port );
            return t;
        };
        startSending(host,port)->detach();
        startSending(host,port)->detach();
        startSending(host,port)->detach();

        /*
        * Consumer
        */
        auto startReceiving = [&,isRunning](string host, unsigned short port) {
            auto t = new thread([&](string host, unsigned short port) {

                boost::circular_buffer<Request*> circular_buffer(3);
                UdpUtils udpUtil;
                while (isRunning) {
                    try {
                        auto t = udpUtil.ServerReceiveNoReply(host, port);
                        auto len = get<0>(t);
                        auto pChar = std::get<1>(t);
                        Request* req = lm::spp::DeSerialize<Request>(pChar.get());
                        vrecv.push_back(req);
                        cout << "receive:" << req->seq << ":" << req->gpsTime << ":" << req->cameraId << endl;
                        circular_buffer.push_back(req);
                    }
                    catch (std::exception &ex) {
                        std::cerr << ex.what() << endl;
                    }
                }
                std::cout << "Receiving Thread exiting" << std::endl;
                
                int index = 0;
                std::for_each(begin(circular_buffer), end(circular_buffer), [&](Request* m) {
                    std::cout << "index:" << index << "data:" << m << std::endl;
                    index++;
                    }); 
                },host,port);
            return t;
        };
        startReceiving(host,port)->detach();

        HaltMainForSec(60);
        isRunning = false;

        REQUIRE(vsent.size() == vrecv.size());

        for_each(begin(vsent), end(vsent), [&](Request req) {
            auto it = find_if(vrecv.begin(), vrecv.end(), [&](Request* _req) {
                return req.seq == _req->seq;
                });
            REQUIRE(it != end(vrecv));
            Request* _req = *it;
            REQUIRE(_req->cameraId == req.cameraId);
            REQUIRE(_req->gpsTime == req.gpsTime);
            });
}
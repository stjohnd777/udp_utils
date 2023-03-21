//
// Created by Daniel St. John on 11/21/22.
//


#include <net.h>

#include <string>
#include <sstream>
#include <iostream>
#include <exception>
#include <chrono>

#include <boost/circular_buffer.hpp>


using namespace std;
 
using namespace std::chrono;





// minimal abstraction client
// we are the UDP cleint awating a response
// we send byes
// we recieve bytes
// the conjugate class is server.cpp
int main() {

    try {
        std::string host = "127.0.0.1";
        unsigned short port = 7767;
        int COUNT = 100;
        UdpUtils *udpUtil = new UdpUtils();

        for (int i = 0; i < COUNT; i++) {

            Request req;
            req.seq = i;
            req.gpsTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            auto send_bytes = Serialize(req);

            auto t = udpUtil->RequestReply(host, port, send_bytes, sizeof(Request));

            auto len = std::get<0>(t);
            auto pChar = std::get<1>(t);
            Response *res = DeSerialize<Response>(pChar.get());

        }

        delete udpUtil;
    } catch (std::exception &ex) {
        cerr << ex.what() << endl;
    }

}

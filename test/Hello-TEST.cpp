#define CATCH_CONFIG_MAIN // provides main(); this line is required in only one .cpp file
#include "catch.hpp"

#include <iostream>
#include <sstream>

#include "teststructs.h"
#include "net.h"
using namespace std;

using namespace boost;


class SyncUDPClient {
public:
    SyncUDPClient() :
        m_sock(m_ios) {
        m_sock.open(asio::ip::udp::v4());
    }

    std::string emulateLongComputationOp(
        unsigned int sec,
        const std::string& ip,
        unsigned short port) {

        std::string request = "EMULATE_LONG_COMP_OP "
            + std::to_string(sec)
            + "\n";

        asio::ip::udp::endpoint ep(
            asio::ip::address::from_string(ip),
            port);

        sendRequest(ep, request);

        std::this_thread::sleep_for(sec*1000ms);

        return receiveResponse(ep);
    };

private:
    void sendRequest(const asio::ip::udp::endpoint& ep, const std::string& request) {
        
        m_sock.send_to(asio::buffer(request), ep);
    }

    std::string receiveResponse(asio::ip::udp::endpoint& ep) {
        char response[6];
        asio::ip::udp::endpoint rmt;
        std::size_t bytes_recieved =  m_sock.receive_from(asio::buffer(response), rmt);
        m_sock.shutdown(asio::ip::udp::socket::shutdown_both);
        return std::string(response, bytes_recieved);
    }
private:
    asio::io_service m_ios;
    asio::ip::udp::socket m_sock;
};


TEST_CASE( "UDP CLIENT ", "1" ) {

    const std::string server1_raw_ip_address = "127.0.0.1";
    const unsigned short server1_port_num = 7767;

 
    //try{
    //    SyncUDPClient client;

    //    std::cout << "Sending request to the server #1 ... " << std::endl;

    //    std::string response = client.emulateLongComputationOp(
    //            10,
    //            server1_raw_ip_address, 
    //            server1_port_num);

    //    std::cout << "Response from the server #1 received: "<< response << std::endl;

    //    std::cout << "Sending request to the server #2... " << std::endl;
    //}
    //catch (boost::system::system_error& e) {

    //    std::cout << "Error occured! Error code = " 
    //        << e.code()
    //        << ". Message: " 
    //        << e.what();

    //}

    boost::asio::io_service io;
    auto v4 = boost::asio::ip::udp::v4();
    auto ip = asio::ip::address::from_string("127.0.0.1");
    const unsigned short port = 7767;
    boost::asio::ip::udp::endpoint ep(ip, port);

    // socket set up
   
    boost::asio::ip::udp::socket udp_socket(io);
    udp_socket.open(v4);


    // send
    std::string request = "123456";
    udp_socket.send_to(asio::buffer(request), ep);


    // recv
    //boost::asio::io_service m_ios_rcv;
    //auto v4 = boost::asio::ip::udp::v4();
    //boost::asio::ip::udp::endpoint  ep_rcv(v4, port);
    //boost::asio::ip::udp::socket m_sock_rcv(m_ios_rcv, ep_rcv);
    //m_sock_rcv.open(asio::ip::udp::v4());

    char response[100];
    boost::asio::ip::udp::endpoint rmt;
    std::size_t bytes_recieved = udp_socket.receive_from(asio::buffer(response), rmt);
    cout << response << endl;

    // shutdown
    udp_socket.shutdown(asio::ip::udp::socket::shutdown_both);
    REQUIRE( true == true );
}
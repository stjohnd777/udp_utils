#pragma once
#include "net.h"

namespace lm { namespace spp {
// server receives rand replys to sender with artifact procuded by handler
template<class Req , class Res >
void UpdRecieveReplyOne(std::string host, unsigned short port, std::function< Res*(Req*)> handler) {

    try {
        // initilize udp
            boost::asio::io_service ios;
            auto udp_ep = utils::GetUdpEndpoint(host, port);
        /*boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4()*/
            boost::asio::ip::udp::socket socket(ios, udp_ep , port);

        // listening for incomming request from a sender
        char recv_buf[sizeof(Req)];
        boost::asio::ip::udp::endpoint senders_endpoint;
        std::size_t bytes_received = socket.receive_from(boost::asio::buffer(recv_buf), senders_endpoint);
        // assert bytes_received = M

        // deserialize client request
        auto req = lm::spp::DeSerialize<Req>(recv_buf);

        // the lambda computes response           
        auto res = handler(req);

        // serialize the response and place 
        auto size_bytes_res = sizeof(Res); // M
        auto bytes_res = Serialize(res);

        auto send_buf = new char[size_bytes_res];
        memcpy(send_buf, bytes_res, size_bytes_res);

        boost::system::error_code ignored_error;
        socket.send_to(boost::asio::buffer(send_buf, size_bytes_res), senders_endpoint, 0, ignored_error);

        // shutdown
        socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
        socket.close();
    }
    catch (boost::system::system_error& e) {
        cout << e.what() << endl;
        throw e;
    }
}

}}
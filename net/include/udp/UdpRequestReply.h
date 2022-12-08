#pragma once
#include "udp_utils.h"

namespace lm { namespace spp {
// client sends Req udp message and expects response Res
template<class Req, class Res>
Res* UdpRequestReply(std::string host, unsigned short port, Req req) {
    
    try {
        // send
        auto bytes_req = lm::spp::Serialize(req);
        char send_buf[sizeof(Req)];
        memcpy(send_buf, bytes_req, sizeof(Req));
        auto bufferedData = asio::buffer(send_buf);

        boost::asio::io_service ios;
        boost::asio::ip::udp::socket udp_socket(ios);
        udp_socket.open(asio::ip::udp::v4());
        auto udp_ep = utils::GetUdpEndpoint(host, port);
        udp_socket.send_to(bufferedData, udp_ep);


        char recv_buf[sizeof(Res)];
        boost::asio::ip::udp::endpoint remote_endpoint;
        std::size_t bytes_received = udp_socket.receive_from(boost::asio::buffer(recv_buf), remote_endpoint);
        Res* res = lm::spp::DeSerialize<Res>(recv_buf);
    
        // shutdown socket
        udp_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
        udp_socket.close();

        return res;
    }
    catch (boost::system::system_error& e) {
        cout << e.what() << endl;
        throw e;
    }
}


}}
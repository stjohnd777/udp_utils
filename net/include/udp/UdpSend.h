#pragma once
#include "net.h"

namespace lm { namespace spp {
// cleint send upd Req message does not expect response
template<class Req>
void UdpSend(std::string host, unsigned short port, Req req ) {

    auto p = lm::spp::Serialize(req);
    char send_buf[sizeof(Req)];
    memcpy(send_buf, p, sizeof(Req));
    auto bufferedData = asio::buffer(send_buf);

    // TODO: leverage 
    //boost::asio::io_service ios;
    //boost::asio::ip::udp::socket udp_socket(ios);
    //udp_socket.open(asio::ip::udp::v4());
    //auto udp_ep = utils::GetUdpEndpoint(host, port);
    //udp_socket.send_to(bufferedData, udp_ep);
    
    //udp_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
    //udp_socket.close();

    UdpUtils udpClient;
    udpClient.SendTo(host,port,p,sizeof(req));

}
}}
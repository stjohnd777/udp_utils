#pragma once

#include "net.h"
#include <algorithm>

namespace lm {
    namespace spp {

        template<class Req, class Res>
        Res *UdpRequestReply(std::string host, unsigned short port, Req req) {

            try {
                // TODO: std::array/copy_n over char[]/memcpy
                // TODO: consider shared_<ptr<Res*> over Res*
         
                auto bytes_req = lm::spp::Serialize(req);
                char send_buf[sizeof(Req)];
                memcpy(send_buf, bytes_req, sizeof(Req));
                auto bufferedData = asio::buffer(send_buf);
                //std::array<char, sizeof(Req)> send_buf;
                //std::copy_n(send_buf, sizeof(req), bytes_req);
                
                // send
                boost::asio::io_service ios;
                boost::asio::ip::udp::socket udp_socket(ios);
                udp_socket.open(asio::ip::udp::v4());
                auto udp_ep = utils::GetUdpEndpoint(host, port);
                udp_socket.send_to(bufferedData, udp_ep);

                // receive
                //char recv_buf[sizeof(Res)];
                char recv_buf[MAX_DATAGRAM] = { 0 };
                boost::asio::ip::udp::endpoint remote_endpoint;
                std::size_t bytes_received = udp_socket.receive_from(boost::asio::buffer(recv_buf), remote_endpoint);
                
                Res *res = lm::spp::DeSerialize<Res>(recv_buf);

                // shutdown socket
                udp_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
                udp_socket.close();

                return res;
            }
            catch (boost::system::system_error &e) {
                cout << e.what() << endl;
                throw e;
            }
        }


    }
}
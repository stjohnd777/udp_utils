#include "net.h"
#include <algorithm>

using namespace std;
 
        template<class Req>
        void UpdConsumeOne(std::string host, unsigned short port, std::function<void(Req *)> handler) {
            // TODO:: maybe shared pointer for Req

            // TODO : Dry
            boost::asio::io_service ios;
            auto udp_ep = utils::GetUdpEndpoint(host, port);
            boost::asio::ip::udp::socket socket(ios, udp_ep, port);

            char request[sizeof(Req)];
            boost::asio::ip::udp::endpoint remote_endpoint;
            std::size_t bytes_received = socket.receive_from(boost::asio::buffer(request), remote_endpoint);

            auto res = lm::spp::DeSerialize<Req>(request);
            handler(res);

            socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
            socket.close();
        }
 
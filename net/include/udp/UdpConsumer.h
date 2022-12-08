#pragma once
#include "net.h"
#include <algorithm>
using namespace std;

namespace lm { namespace spp {

    // server receives Req and process request with handler and does Reply to Sender

    //std::tuple<size_t, std::shared_ptr<char[]>> 
    //_UpdConsumeOne(std::string host, unsigned short port, const char* bytes, const size_t len) {
    //    // TODO:: maybe shared pointer for Req

    //    // TODO : Dry
    //    boost::asio::io_service ios;
    //    auto udp_ep = utils::GetUdpEndpoint(host, port);
    //    boost::asio::ip::udp::socket socket(ios, udp_ep, port);

    //    char recv_buf[MAX_DATAGRAM];
    //    boost::asio::ip::udp::endpoint remote_endpoint;
    //    std::size_t bytes_received = socket.receive_from(boost::asio::buffer(recv_buf), remote_endpoint);

    //    socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
    //    socket.close();

    //    std::shared_ptr<char[]> sp(new char[bytes_received]);
    //    std::copy_n( sp.get(), bytes_received, begin(recv_buf));

    //    return std::make_tuple(bytes_received, sp);
    //}

    template<class Req>
    void UpdConsumeOne(std::string host, unsigned short port, std::function<void(Req*)> handler) { 
        // TODO:: maybe shared pointer for Req

        // TODO : Dry
        boost::asio::io_service ios;
        auto udp_ep = utils::GetUdpEndpoint(host, port);
        boost::asio::ip::udp::socket socket(ios, udp_ep , port);

        char request[sizeof(Req)];
        boost::asio::ip::udp::endpoint remote_endpoint;
        std::size_t bytes_received = socket.receive_from(boost::asio::buffer(request), remote_endpoint);

        auto res = lm::spp::DeSerialize<Req>(request);
        handler(res);

        socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
        socket.close();
    }

    // Consumer
    template<class Req, class Reply >
    class UdpComsumer {
    public:
        std::shared_ptr<Req*> Receive(std::string host, unsigned short port, Req req) {
            auto data = udpUtil.ServerReceiveNoReply(host, port);
            Req* req = lm::spp::DeSerialize<Req>(data);
            return std::make_shared <Req*>(req);
        }

        void StartReceiving(std::string host, unsigned short port, std::function<void(Req*)> handler) {
            isRunning = true;
            while (isRunning) {
                auto req = Receive(host, port, handler);
                handler(req);
            }
        }

        void Stop() {
            isRunning false;
        }
    };
}}
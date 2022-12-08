#pragma once

#include <iostream>
#include <string>
#include <tuple>
#include <functional>
#include <memory>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <mutex>
#include <future>
#include "net.h"



typedef char byte;

namespace lm {

    namespace spp {

        typedef std::function <std::tuple<size_t, std::shared_ptr<char[]>>(std::tuple<size_t, std::shared_ptr<char[]>>) > REQ_REPLY_HANDLER;

        typedef std::function<void ( const boost::system::error_code& error, std::size_t bytes_transferred )> ASCYNC_RECEIVER;

        /**
        This Class encapsulates UDP functionaliy for convienance
        
        The UDP server/service is on host:port the data is a byte array of lenght len.
        - SendTo // fire and forget
        - ServerReceiveNoReply  // comsumer
        - BlockingRead  // server listening for connection
        - RequestReply  // client request and reply 
        */
        class UdpUtils {
        public:
            UdpUtils();

            /**
            This method is mdoeling UDP send and foget 
            
            The UDP server/service is on host:port the data is a byte array of lenght len.
            @parm host
            @parm port
            @parm pdata
            @parm len
            @return void
            */
            void SendTo(std::string host, unsigned short port,const char* pdata, size_t len);
            
            template<size_t N>
            void SendTo(std::string host, unsigned short port, const std::array<char, N>& data);

            /**
            This method is mdoeling UDP server receiving, acting as consumer
            
            @parm host
            @parm port
            @parm pdata
            @parm len
            @return  std::tuple<size_t,std::shared_ptr<char[]> >
            - <data length, bytes>
            */
            std::tuple<size_t,std::shared_ptr<char[]> >
            ServerReceiveNoReply(std::string host, unsigned short port);

           /**
            This method UDP server blocking reead
            
            @return  std::tuple<size_t,std::shared_ptr<char[]> >
            - <data length, bytes>
            */
            std::tuple<size_t,std::shared_ptr<char[]> >
            BlockingRead();

            /**
            This method is mdoeling UDP client request response behavior. 
            
            The UDP server/service is on host:port the data is a byte array of lenght len.
            @parm host
            @parm port
            @parm pdata
            @parm len
            */
            std::tuple<size_t,std::shared_ptr<char[]>>
            RequestReply(std::string host, unsigned short port, const char* pdata, size_t len);

            /**
            This method is mdoeling UDP server receive reply behavior.

            The UDP server/service is listening on host:port for connections
            @parm host
            @parm port
            @parm pdata
            @parm len
            */
            void ReceiveReply(std::string host, unsigned short port ,  REQ_REPLY_HANDLER handler);

            /**
            * This function is used to asynchronously receive a datagram. 
            * The function call always returns immediately.
            * Receive single data buffer  
            */
            template<class Req>
            void AsyncReceiveReply(std::string host, unsigned short port, ASCYNC_RECEIVER);

            ASCYNC_RECEIVER echo_handler = [this](const boost::system::error_code& error, std::size_t bytes_transferred) {
                std::lock_guard<std::mutex> guard(m_async_buffer_mutex);
                std::cout << "Bytes Recieved:" << bytes_transferred << std::endl;
                for (auto b : async_reciev_buffer) {
                    std::cout << b << "."; 
                }
                std::cout << std::endl;
                for (auto b : async_reciev_buffer) {
                    std::cout << lm::spp::toBinaryString(b) << ".";
                }
                std::cout << std::endl;
            };

            /*
            template<class Req>
            std::future<Req> GetRequest(std::string host, unsigned short port, ASCYNC_RECEIVER) {
                std::promise<int> promise;
                std::future<int>  future = promise.get_future();
                std::thread t([this]() {
                    Req req;
                    promise.set_value(req);
                },  std::move(promise));
                return std::move(future);
            }
            */

            virtual ~UdpUtils();


            // TODO: lambda access requires access to mutex and buffer, trade off
            char async_reciev_buffer[MAX_DATAGRAM];
            //ATR(char[MAX_DATAGRAM], async_reciev_buffer, AsyncRecievBuffer)
            std::mutex m_async_buffer_mutex;
        protected:
            boost::asio::io_service m_ios;
            boost::asio::ip::udp::socket m_udp_socket;
        };
 }
}


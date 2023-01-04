#pragma once

#include <iostream>
#include <string>
#include <tuple>
#include <functional>
#include <memory>
#include <boost/asio.hpp>
 
typedef char byte;
 

        typedef std::function<std::tuple<size_t, std::shared_ptr<char[]>>(
                std::tuple<size_t, std::shared_ptr<char[]>>)> REQ_REPLY_HANDLER;

        //typedef std::function<void ( const boost::system::error_code& error, std::size_t bytes_transferred )> ASCYNC_RECEIVER;

        class IUdpClient {
        public:
            virtual void SendTo(std::string host, unsigned short port, const char *pdata, size_t len) = 0;

            virtual std::tuple<size_t, std::shared_ptr<char[]>>
            RequestReply(std::string host, unsigned short port, const char *pdata, size_t len) = 0;

            virtual ~IUdpClient() {};
        };

        class IUdpServer {
        public:
            virtual std::tuple<size_t, std::shared_ptr<char[]>>
            ServerReceiveNoReply(std::string host, unsigned short port) = 0;

            virtual void ReceiveReply(std::string host, unsigned short port, REQ_REPLY_HANDLER handler) = 0;

            virtual ~IUdpServer() {};
        };

        class IUpdUtils : public IUdpClient, public IUdpServer {

        };

        /**
        Encapsulates UDP functionally for convenience
        - this interface is for bytes
        
        The UDP server/service is on host:port the data is a byte array of length len.
        - SendTo // fire and forget
        - ServerReceiveNoReply  // consumer
        - BlockingRead  // server listening for connection
        - RequestReply  // client request and reply 
        */
        class UdpUtils : public IUdpClient, public IUdpServer {
        public:
            UdpUtils();

            /**
            This method is modeling UDP send and foget
            
            The UDP server/service is on host:port the data is a byte array of lenght len.
            @parm host
            @parm port
            @parm pdata
            @parm len
            @return void
            */
            void SendTo(std::string host, unsigned short port, const char *pdata, size_t len);


            //// attempt to avoid older practices and avoid native C types
            //template<size_t N> 
            //void SendTo(std::string host, unsigned short port, const std::array<char, N>& data);

            /**
            This method is mdoeling UDP server receiving, acting as consumer
            
            @parm host
            @parm port
            @parm pdata
            @parm len
            @return  std::tuple<size_t,std::shared_ptr<char[]> >
            - <data length, bytes>
            */
            std::tuple<size_t, std::shared_ptr<char[]> >
            ServerReceiveNoReply(std::string host, unsigned short port);

            //// attempt to avoid older practices and avoid native C types
            //template < size_t N>
            //std::array<char, N > ServerReceiveNoReply2(std::string host, unsigned short port);

            /**
             This method UDP server blocking read

             @return  std::tuple<size_t,std::shared_ptr<char[]> >
             - <data length, bytes>
             */
            std::tuple<size_t, std::shared_ptr<char[]> >
            BlockingRead();

            /**
            This method is modeling UDP client request response behavior.
            
            The UDP server/service is on host:port the data is a byte array of length len.
            @parm host
            @parm port
            @parm pdata
            @parm len
            */
            std::tuple<size_t, std::shared_ptr<char[]>>
            RequestReply(std::string host, unsigned short port, const char *pdata, size_t len);

            /**
            This method is modeling UDP server receive reply behavior.

            The UDP server/service is listening on host:port for connections
            @parm host
            @parm port
            @parm pdata
            @parm len
            */
            void ReceiveReply(std::string host, unsigned short port, REQ_REPLY_HANDLER handler);

            virtual ~UdpUtils();

        protected:
            boost::asio::io_service m_ios;
            boost::asio::ip::udp::socket m_udp_socket;
        };
 
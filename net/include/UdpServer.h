#pragma once

#include "net.h"

template<class Request, class Response>
class UdpServer {
public:
    UdpServer(std::string host, unsigned short port) : m_host(host), m_port(port) {}

    void ReceiveReply(std::function<Response *(Request *)> handler) {

        using namespace boost::asio;
        using namespace boost::asio::ip;

        udp::socket socket(m_ios, boost::asio::ip::udp::endpoint( udp::v4(), m_port));

        uint8_t recv_buf[sizeof(Response)];
        udp::endpoint remote_endpoint;
        cout << "Server Blocking Read " << endl;
        std::size_t bytes_received = socket.receive_from(buffer(recv_buf), remote_endpoint);
        cout << "Server Received Request " << endl;
        cout << "Received: " << bytes_received << endl;

        Request* req = DeSerialize<Request>(recv_buf);

        Response* res = handler(req);
        cout << "Server Computed Response: " << endl;

//        size_t size = sizeof(Response);
//        uint8_t *p = (uint8_t *) res;

        boost::system::error_code ignored_error;
        socket.send_to(buffer( (uint8_t *)res, sizeof(Response) ), remote_endpoint, 0, ignored_error);
        cout << "Server Sent Response: " << endl;
        cout << "ignored_error:" << ignored_error << endl;

//        cout << "delete res" << endl;
//        delete res;

//        cout << "socket.shutdown" << endl;
//        socket.shutdown(boost::asio::socket_base::shutdown_both);
//        cout << "socket.close" << endl;
//        socket.close();
    }

    thread* Start(std::function<Response *(Request *)> handler) {
        return new thread([&](){
            m_IsRunning = true;
            while (m_IsRunning) {
                try {
                    cout << "Server Listening" << endl;
                    ReceiveReply(handler);
                    cout << "Server Processed Request" << endl;
                }catch(std::exception& e){
                    cout << "ERROR:ReceiveReply: " << e.what() << endl;

                }
            }
        });
    }

    void Stop() {
        m_IsRunning = false;
    }

protected:
    boost::asio::io_service m_ios;
    bool m_IsRunning = false;
    std::string m_host;
    unsigned short m_port;
};
 
 
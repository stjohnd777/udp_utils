#pragma once

#include "net.h"
 

        // Client
        template<class Request, class Response>
        class UdpClient {
        public:
            UdpClient(std::string host, unsigned short port) : m_host(host), m_port(port) {
            }

            void Send(Request &req) {
                lm::spp::UdpSend<Request>(m_host, m_port, req);
            }
            
            Response *RequestReply(Request req) {
                return lm::spp::UdpRequestReply<Request, Response>(m_host, m_port, req);
            }

        protected:
            std::string m_host;
            unsigned short m_port;
        };
 
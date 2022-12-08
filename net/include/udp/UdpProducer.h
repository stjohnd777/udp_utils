#pragma once
#include "udp_utils.h"

namespace lm { 
    namespace spp {
 
        // Producer
        template<class Request, class Response >
        class UdpSender {
        public:
            UdpSender(std::string host, unsigned short port) : m_host(host), m_port(port) {
            }
            void Send(Request& req) {
                lm::spp::UdpSend<Request>(m_host, m_port, req);
            }

        protected:
            std::string m_host;
            unsigned short m_port;
        };

    }
}
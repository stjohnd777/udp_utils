#pragma once

#include "net.h"
#include <algorithm>

using namespace std;

namespace lm {
    namespace spp {

        template<class Req, class Reply>
        class UdpConsumer {
        public:
            UdpConsumer(std::string host, unsigned short port) : m_host(host), m_port(port) {}

            std::shared_ptr<Req *> Receive() {
                auto data = m_UdpUtils.ServerReceiveNoReply(m_host, m_port);
                Req *req = lm::spp::DeSerialize<Req>(data);
                return std::make_shared<Req *>(req);
            }

            void StartReceiving(std::string host, unsigned short port, std::function<void(Req *)> handler) {
                m_IsRunning = true;
                while (m_IsRunning) {
                    auto req = Receive(host, port);
                    handler(req);
                }
            }

            void Stop() {
                m_IsRunning = false;
            }

        private:
            std::string m_host;
            unsigned short m_port;
            bool m_IsRunning = false;
            lm::spp::UdpUtils m_UdpUtils;
        };
    }
}
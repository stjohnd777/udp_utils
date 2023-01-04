#pragma once

#include "net.h"


namespace lm {
    namespace spp {
        template<class Request, class Response>
        class UdpServer {
        public:
            UdpServer(std::string host, unsigned short port) : m_host(host), m_port(port) {}

            void ReceiveReply(std::function<Response *(Request *)> handler) {
                
                
                UpdReceiveReplyOne<Request, Response>(m_host, m_port, handler);
            }

            void StartReqRes(std::function<Response *(Request *)> handler, bool isThread = false) {
                m_IsRunning = true;
                while (m_IsRunning) {
                    ReceiveReply(handler);
                }
            }

            void Stop() {
                m_IsRunning = false;
            }

        protected:
            bool m_IsRunning = false;
            std::string m_host;
            unsigned short m_port;
        };
    }
}
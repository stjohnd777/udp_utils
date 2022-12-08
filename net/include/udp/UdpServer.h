#pragma once
#include "udp_utils.h"


namespace lm { namespace spp {
    template<class Request, class Response >
    class UdpServer {
    public:
        UdpServer(std::string host, unsigned short port) : m_host(host), m_port(port) {}

        void ReceiveReply( std::function<Response*(Request*)> handler) { 
                UpdRecieveReplyOne<Request,Response>(m_host,m_port,handler);
        }

        void StartReqRes( std::function<Response* (Request*)> handler, bool isThread = false) {
            
            isRunning = true;

            auto worker = [&]() {
                while (isRunning) {
                    ReceiveReply(handler);
                }
            };

            if ( isThread) {
                std::thread(worker);
            }else {
                worker();
            }
            
        }
        void Stop() {
            isRunning =false;
        }
    protected:
        bool isRunning = false;
        std::string m_host;
        unsigned short m_port;
    };
}}
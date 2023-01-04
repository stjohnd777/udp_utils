#pragma once

#include "net.h"
#include "udp_utils.h"

 

        template<class Req>
        void UdpSend(std::string host, unsigned short port, Req req) {
            auto p = lm::spp::Serialize(req);
            UdpUtils udpClient;
            udpClient.SendTo(host, port, p, sizeof(req));

        }
 
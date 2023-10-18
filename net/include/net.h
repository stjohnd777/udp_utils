//
// Created by Daniel St. John on 11/16/22.
//

#pragma once

#include "macro.h"

#include "UdpUtils.h"
#include "UdpConsumer.h"
#include "UdpProducer.h"
#include "UdpClient.h"
#include "UdpServer.h"
#include "SyncTcpClient.h"
#include "SyncTcpServer.h"


struct Frame {
    uint32_t seq;
    double gpsTime;
    uint8_t cameraId;
    char img[HEIGHT * WIDTH * CHANNEL_DEPTH];
};


PACK(
        struct Request {
            uint32_t seq = 0;
            uint64_t gpsTime = 0;
            uint8_t cameraId = 0;

        });

PACK(
        struct Response {
            uint32_t seq;
            uint64_t gpsTime;
            uint8_t cameraId;
            int retCode;
        });
 


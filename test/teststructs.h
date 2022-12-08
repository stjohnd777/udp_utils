#pragma once
#include "macro.h"

PACK(
struct example {
    uint8_t _u8;
    uint16_t _u16;
    uint32_t _u32;
    char matrix[100][200];
});

PACK(
struct Request
{
    uint32_t seq;
    uint64_t gpsTime;
    uint8_t cameraId;
});

PACK(
struct RequestWithMat
{
    uint32_t seq;
    uint64_t gpsTime;
    uint8_t cameraId;
});

PACK(
    struct Response
{
    uint32_t seq;
    uint64_t gpsTime;
    uint8_t cameraId;
    int retCode;
    //uint8_t matrix[600][800];
});

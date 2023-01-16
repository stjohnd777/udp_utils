#pragma once
#include "macro.h"


PACK(
struct Request
{
    uint8_t cameraId;
    uint64_t gpsTime;
    uint32_t seq;
});

PACK(
struct Response
{
    uint8_t cameraId;
    uint64_t gpsTime;
    uint32_t seq;
    char matrix[100][200];
    int retCode;
});


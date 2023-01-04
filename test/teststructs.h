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
struct Response
{
    uint32_t seq;
    uint64_t gpsTime;
    uint8_t cameraId;
    int retCode;
});


struct A0 {
    uint8_t _u8;
    uint16_t _u16;
    uint32_t _u32;
};

PACK( struct A1 {
          uint8_t _u8;
          uint16_t _u16;
          uint32_t _u32;
      });

class A2 {
public:
    A2(): m_u8(1), m_u16(1), m_u32(1) { }
    A2(char c,
       uint16_t u16,
       uint32_t u32 )
            : m_u8(c),m_u16(u16),m_u32(u32)
    {

    }
    char m_u8;
    uint16_t m_u16;
    uint32_t m_u32;

};

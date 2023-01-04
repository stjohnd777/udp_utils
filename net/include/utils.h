#pragma once

#include <boost/asio.hpp>
#include <string>
#include <iostream>
#include <sstream>
#include <exception>
#include <memory>
#include <tuple>
#include <bitset>

using namespace boost;

 

        struct UdpTrack {
            uint8_t length = 0;
            uint64_t uuid  = 0;
            uint8_t seq    = 0;
        };

        std::string toBinaryString(char c);

        // TODO: maybe shared_ptr
        template <class SomeStruct>
        char* Serialize(SomeStruct& s) {
            size_t size = sizeof(SomeStruct);
            char* p = (char*)&s;
            return p;
        }

        // TODO: maybe shared_ptr
        template <class SomeStruct>
        SomeStruct* DeSerialize( char* src) {
            size_t len = sizeof(SomeStruct);
            char* dest = new char[len];
            memcpy(dest, src, len);
            SomeStruct* s = (SomeStruct*)(dest);
            return s;
        }


         struct PGMImage {
            char pgmType[3];
            unsigned char** data;
            unsigned int width;
            unsigned int height;
            unsigned int maxValue;
        } ;

        class utils {
        public:

            static asio::ip::udp::endpoint GetUdpEndpoint(std::string host, unsigned short port) ;
            static bool IsLittleIndian() ;
            static bool IsBigIndian();
            static bool OpenPGM_C(PGMImage* pgm, const char* filename);
            char* readFile_C(std::string fileName);
        private:
            static void IgnoreComments(FILE* fp);
        };
 
 


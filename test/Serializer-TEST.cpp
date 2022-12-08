#define CATCH_CONFIG_MAIN // provides main(); this line is required in only one .cpp file
#include "catch.hpp"

#include <iostream>
#include <sstream>
#include <tuple>
#include <net.h>


#include "teststructs.h"

using namespace std;

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
 

    std::shared_ptr<char[]>  serialize() {
        std::shared_ptr<char[]> sp(new char[sizeof(A2)]);
        char* p = (char*)this;
        memcpy(sp.get(), this, sizeof(A2));
        return sp;
    }
     
    char *  unsafe_serialize() {
        char* p = new char[sizeof(A2)];
        memcpy(p, this, sizeof(A2));
        return p;
    }
};


TEST_CASE("Serializer Test ", "Simple Small struct") {
    Test in;
    in._u8 = 1;
    in._u16 = 1;
    in._u32 = 3;

    char* t = lm::spp::Serialize(in);
    Test* out = lm::spp::DeSerialize<Test>(t);

    REQUIRE(in._u8 == out->_u8);
    REQUIRE(in._u16 == out->_u16);
    REQUIRE(in._u32 == out->_u32);


    
    // unsigned char m1[2][2] ={{1,0},{2,0 } };
    //unsigned int  m2[2][2] = { {3,0},{4,0 } };
    //A2 a2; // (1, 1, 1, m1, m2);
    //cout << sizeof(A1)<< "=" << sizeof(A2) << endl;
    //REQUIRE(sizeof(A1) == sizeof(A2));
    //auto sp = a2.serialize();
    //cout << sizeof(*(sp.get())) << endl;

    A0 a0 = { 1,1,1 };
    A1 a1 = { 1,1,1 };

    cout << "struct A0 " << sizeof(A0) << endl;
    char* p0 = lm::spp::Serialize(a0);
    for (auto i = 0; i < sizeof(A0) - 1; i++) {
        cout << "[" << i << "]:" << lm::spp::toBinaryString(p0[i]);
        if (i < (sizeof(A0) - 2)) {
            cout << ".";
        }
    }
    cout << endl;

    cout << "struct A1 " << sizeof(A1) << endl;
    char* p1 = lm::spp::Serialize(a1);
    for (auto i = 0; i < sizeof(A1)-1; i++) {
        cout << "[" << i << "]:" << lm::spp::toBinaryString(p1[i]);
        if (i < (sizeof(A1) - 2)) {
            cout << ".";
        }
    }
    cout << endl;


}



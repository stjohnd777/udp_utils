#define CATCH_CONFIG_MAIN 

#include "catch.hpp"
#include "teststructs.h"

#include <iostream>
#include <tuple>
#include <net.h>

//struct A0 {
//    uint8_t _u8;
//    uint16_t _u16;
//    uint32_t _u32;
//};
//
//
//PACK(struct A1 {
//    uint8_t _u8;
//    uint16_t _u16;
//    uint32_t _u32;
//});


using namespace std;

TEST_CASE("Serializer Test ", "Simple-Small-struct") {
    A1 in;
    in._u8 = 1;
    in._u16 = 1;
    in._u32 = 3;

    char* t =  Serialize(in);
    A1* out =  DeSerialize<A1>(t);

    REQUIRE(in._u8 == out->_u8);
    REQUIRE(in._u16 == out->_u16);
    REQUIRE(in._u32 == out->_u32);


    A0 a0 = { 1,1,1 };
    A1 a1 = { 1,1,1 };

    cout << "struct A0 " << sizeof(A0) << endl;
    char* p0 = lm::spp::Serialize(a0);
    for (auto i = 0; i < sizeof(A0) - 1; i++) {
        cout << "[" << i << "]:" <<  toBinaryString(p0[i]);
        if (i < (sizeof(A0) - 2)) {
            cout << ".";
        }
    }
    cout << endl;

    cout << "struct A1 " << sizeof(A1) << endl;
    char* p1 = lm::spp::Serialize(a1);
    for (auto i = 0; i < sizeof(A1)-1; i++) {
        cout << "[" << i << "]:" << toBinaryString(p1[i]);
        if (i < (sizeof(A1) - 2)) {
            cout << ".";
        }
    }
    cout << endl;
}


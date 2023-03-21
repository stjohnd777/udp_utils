// The correct maximum UDP message size is 65507, 
// as determined by the following formula : 
// 0xffff - (sizeof(IP Header) + sizeof(UDP Header)) = 65535 - (20 + 8) = 65507

#define MAX_DATAGRAM 65507
#define WIDTH   1920
#define HEIGHT  1080
#define CHANNEL_DEPTH 1
//#define COLS 1920
//#define ROWS 1089
//#define DEPTH 1



#ifdef __GNUC__
#define PACK( __Declaration__ ) __Declaration__ __attribute__((__packed__))
#endif

#ifdef _MSC_VER
#define PACK( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop))
#endif
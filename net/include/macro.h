// The correct maximum UDP message size is 65507, 
// as determined by the following formula : 
// 0xffff - (sizeof(IP Header) + sizeof(UDP Header)) = 65535 - (20 + 8) = 65507

#define MAX_DATAGRAM 65507
#define WIDTH   2672
#define HEIGHT  1952
#define CHANNEL 2
#define LEN     WIDTH*HEIGHT*CHANNEL

#define ATTRV(varType, varName, funName, v)\
    protected: varType varName = v ;\
    public: virtual varType get##funName(void) const {\
        return varName;\
    }\
    public: virtual void set##funName(varType var){\
        varName = var;\
    }\

#define ATTR(varType, varName, funName)\
    protected: varType varName ;\
    public: virtual varType get##funName(void) const {\
        return varName;\
    }\
    public: virtual void set##funName(varType var){\
        varName = var;\
    }\

#ifdef __GNUC__
#define PACK( __Declaration__ ) __Declaration__ __attribute__((__packed__))
#endif

#ifdef _MSC_VER
#define PACK( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop))
#endif
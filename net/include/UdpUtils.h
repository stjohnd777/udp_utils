#pragma once

#include <iostream>
#include <string>
#include <tuple>
#include <functional>
#include <memory>
#include <boost/asio.hpp>

typedef char byte;

using namespace std;

typedef
std::function<tuple<size_t, std::shared_ptr<uint8_t[]>>(tuple<size_t, std::shared_ptr<uint8_t[]>>)> REQ_REPLY_HANDLER;

template<class SomeStruct>
uint8_t *Serialize(SomeStruct &s) {
    size_t size = sizeof(SomeStruct);
    uint8_t *p = (uint8_t *) &s;
    return p;
}

// TODO: maybe shared_ptr
template<class SomeStruct>
SomeStruct *DeSerialize(uint8_t *src) {
    size_t len = sizeof(SomeStruct);
    uint8_t *dest = new uint8_t[len];
    memcpy(dest, src, len);
    SomeStruct *s = (SomeStruct *) (dest);
    return s;
}

boost::asio::ip::udp::endpoint GetUdpEndpoint(std::string host, unsigned short port) {
    boost::system::error_code ec;
    // checks whether argument contains a valid IPv4 or IPv6 address then
    // instantiates a corresponding v4 || v6
    auto ip_address = boost::asio::ip::address::from_string(host, ec);
    if (ec.value() != 0) {
        std::cout << ec.value() << std::endl;
        throw ec.value();
    }
    auto ep = boost::asio::ip::udp::endpoint(ip_address, port);
    return ep;
}


class UdpUtils {
public:
    UdpUtils();

    void Send(std::string host, unsigned short port, const uint8_t *pdata, size_t len);

    std::tuple<size_t, std::shared_ptr<uint8_t[]>>
    ServerReceiveNoReply(std::string host, unsigned short port);

    std::tuple<size_t, std::shared_ptr<::uint8_t[]>>
    RequestReply(std::string host, unsigned short port, const uint8_t *pdata, size_t len);

    void ReceiveReply(std::string host, unsigned short port, REQ_REPLY_HANDLER handler);

    virtual ~UdpUtils();

protected:
    boost::asio::io_service m_ios;
    boost::asio::ip::udp::socket m_udp_socket;
};
 
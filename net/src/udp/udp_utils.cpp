
#include <algorithm>
#include <boost/asio.hpp>

#include <utils.h>
#include <udp/udp_utils.h>



namespace lm {
    namespace  spp {

        using namespace std;
        using namespace boost;
        using namespace boost::asio;

        UdpUtils::UdpUtils(): 
            m_udp_socket(m_ios) {
            m_udp_socket.open(asio::ip::udp::v4());
        }

        void UdpUtils::SendTo(std::string host, unsigned short port, const char* pdata, size_t len) {
            auto udp_ep = utils::GetUdpEndpoint(host, port);

            char  data[MAX_DATAGRAM];
            memcpy(data, pdata, len);
            auto bufferedData = asio::buffer(data,len);
            m_udp_socket.send_to(bufferedData,udp_ep);
        }

        template<size_t N>
        void  UdpUtils::SendTo(std::string host, unsigned short port, const std::array<char, N>& data) {
            auto udp_ep = utils::GetUdpEndpoint(host, port);
            auto bufferedData = asio::buffer(data);
            m_udp_socket.send_to(bufferedData, udp_ep);
        }


        std::tuple<size_t,std::shared_ptr<char[]> >
        UdpUtils::BlockingRead() {

            char recv_buf[MAX_DATAGRAM] = {0};
            //memset(recv_buf,0, MAX_DATAGRAM);

            boost::asio::ip::udp::endpoint sender_endpoint;
            size_t bytes_received = m_udp_socket.receive_from(boost::asio::buffer(recv_buf), sender_endpoint);

            std::shared_ptr<char[]> sp(new char[bytes_received]);
            memcpy(sp.get(), recv_buf, bytes_received);

            return std::make_tuple(bytes_received,sp);
        }

        std::tuple<size_t,std::shared_ptr<char[]>>
        UdpUtils::ServerReceiveNoReply(std::string host, unsigned short port) {

            boost::asio::io_context io_context;
            boost::asio::ip::udp::socket socket(io_context, boost::asio::ip::udp::endpoint( boost::asio::ip::udp::v4(),port));

            char recv_buf[MAX_DATAGRAM] = {0};
            //memset(recv_buf,0, MAX_DATAGRAM);

            boost::asio::ip::udp::endpoint remote_endpoint;
            std::size_t bytes_received = socket.receive_from(boost::asio::buffer(recv_buf), remote_endpoint);

            std::shared_ptr<char[]> sp(new char[bytes_received]);
            memcpy(sp.get(),recv_buf,bytes_received);

            return std::make_tuple(bytes_received,sp);
        }

        std::tuple<size_t,std::shared_ptr<char[]>> UdpUtils::RequestReply(std::string host, unsigned short port, const char* pdata, size_t len) {
            SendTo(host,port,pdata,len);
            return BlockingRead();
        }

        void UdpUtils::ReceiveReply(std::string host, unsigned short port,REQ_REPLY_HANDLER f) {
            using namespace boost::asio;
            using namespace boost::asio::ip;

            udp::socket socket(m_ios, boost::asio::ip::udp::endpoint( udp::v4(), port));
            
            char recv_buf[MAX_DATAGRAM];
            udp::endpoint remote_endpoint;

            std::size_t bytes_received = socket.receive_from(buffer(recv_buf), remote_endpoint);
            std::shared_ptr<char[]> sp(new char[bytes_received]);

            memcpy(sp.get(), recv_buf, bytes_received);
 
            auto req = std::make_tuple(bytes_received,sp);

            auto res = f(req);

            auto size_bytes_response = std::get<0>(res);
            auto  spChar = std::get<1>(res);
            char* pChar = spChar.get();
            char send_buf[MAX_DATAGRAM];
            memcpy(send_buf, spChar.get(), size_bytes_response);

            boost::system::error_code ignored_error;
            socket.send_to(buffer(send_buf,size_bytes_response), remote_endpoint, 0, ignored_error);
        }

        template<class Req>
        void UdpUtils::AsyncReceiveReply(std::string host, unsigned short port, ASCYNC_RECEIVER handler) {
            using namespace boost::asio;
            using namespace boost::asio::ip;
            udp::socket socket(m_ios, boost::asio::ip::udp::endpoint(udp::v4(), port));
            udp::endpoint remote_endpoint;
            socket.async_receive_from( boost::asio::buffer(async_reciev_buffer, sizeof(Req)), 0, remote_endpoint, handler);
        }


        UdpUtils::~UdpUtils() {
            m_udp_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
            m_udp_socket.close();
        }

    }
}





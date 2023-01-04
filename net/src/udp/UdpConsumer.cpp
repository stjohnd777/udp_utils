
// #include "UdpConsumer.h"
// #include "net.h"
// #include <algorithm>

// using namespace std;

// namespace lm {
//     namespace spp {


//         template<class Req, class Reply>
//          UdpConsumer<Req,Reply>::UdpConsumer(std::string host, unsigned short port) : m_host(host), m_port(port) {}

//         template<class Req, class Reply>
//         std::shared_ptr<Req *> UdpConsumer<Req,Reply>::Receive() {
//             auto data = m_UdpUtils.ServerReceiveNoReply(m_host, m_port);
//             Req *req = lm::spp::DeSerialize<Req>(data);
//             return std::make_shared<Req *>(req);
//         }

//         template<class Req, class Reply>
//         void UdpConsumer<Req,Reply>::StartReceiving(std::string host, unsigned short port, std::function<void(Req *)> handler) {
//             m_IsRunning = true;
//             while (m_IsRunning) {
//                 auto req = Receive(host, port);
//                 handler(req);
//             }
//         }

//         template<class Req, class Reply>
//         void  UdpConsumer<Req,Reply>::Stop() {
//             m_IsRunning = false;
//         }

 
//     }
// }
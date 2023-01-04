#include <boost/asio.hpp>

#include <string>
#include <sstream>
#include <thread>
#include <atomic>
#include <memory>
#include <iostream>
#include <functional>
#include <vector>
#include <tuple>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace boost;
using namespace std;

#define WIDTH 2672
#define HEIGHT 1952
#define CHANNEL 2
#define LEN WIDTH *HEIGHT *CHANNEL
namespace lm
{
    namespace spp
    {
        struct camera_trigger
        {
            double time;
            uint16_t camera_id{0};
        };

        camera_trigger _ParseRequest(string line)
        {
            camera_trigger ret;

            vector<string> tokens;
            string delimiter = "|";
            size_t pos = 0;
            while ((pos = line.find(delimiter)) != std::string::npos)
            {
                string token = line.substr(0, pos);
                tokens.push_back(token);
                line.erase(0, pos + delimiter.length());
            }
            tokens.push_back(line);
            ret.time = stod(tokens[0]);
            ret.camera_id = stoi(tokens[1]);

            return ret;
        }

        typedef std::function<std::tuple<size_t, char *>(int cameraId, double timestamp)> TCP_HANDLER;

        class SyncTCPServer
        {
        public:
            asio::io_service m_ios;
            asio::ip::tcp::acceptor m_Acceptor;
            // asio::ip::tcp::socket sock;

            SyncTCPServer(unsigned short port) : m_port(port), m_stop(false),
                                                 m_Acceptor(m_ios, asio::ip::tcp::endpoint(asio::ip::address_v4::any(), port))
            {
                m_Acceptor.listen();
            }

            char *StartOne(std::function<std::tuple<size_t, char *>(int cameraId, double timestamp)> handler)
            {

                cout << "server create socket" << endl;
                asio::ip::tcp::socket sock(m_ios);
                cout << "server accept on socket ... waiting/blocking" << endl;
                m_Acceptor.accept(sock);

                cout << "server accepted reading request" << endl;
                asio::streambuf request;
                asio::read_until(sock, request, '\n');
                std::istream is(&request);
                std::string line;
                std::getline(is, line);
                cout << "server read request " << line << endl;

                auto req = _ParseRequest(line);

                auto tup = handler(req.camera_id, req.time);
                char *image = get<1>(tup);
                size_t len = get<0>(tup);

                cout << "server write to client " << len << " bytes" << endl;
                asio::write(sock, asio::buffer(image, len));

                return image;
            }

            void Start(std::function<std::tuple<size_t, char *>(int cameraId, double timestamp)> handler)
            {

                auto pThread = new std::thread([&]()
                    {
                        while (!this->m_stop.load())
                        {

                            // asio::ip::tcp::acceptor anAcceptor (m_ios, asio::ip::tcp::endpoint(asio::ip::address_v4::any(), m_port));
                            // anAcceptor.listen();
                            asio::ip::tcp::socket sock(m_ios);
                            m_Acceptor.accept(sock);

                            asio::streambuf request;
                            asio::read_until(sock, request, '\n');
                            std::istream is(&request);
                            std::string line;
                            std::getline(is, line);

                            auto req = _ParseRequest(line);

                            auto tup = handler(req.camera_id, req.time);
                            char *image = get<1>(tup);
                            size_t len = get<0>(tup);

                            asio::write(sock, asio::buffer(image, len));
                        }
                    });

                m_spThread.reset(pThread);
            }

            void join()
            {
                m_spThread->join();
            }

            void detach()
            {
                m_spThread->detach();
            }
            void Stop()
            {
                m_stop.store(true);
                m_spThread->join(); // TODO: humm ??
            }

        private:
            std::unique_ptr<std::thread> m_spThread;
            std::atomic<bool> m_stop;
            unsigned short m_port;
        };
    }
};

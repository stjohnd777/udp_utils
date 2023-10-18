//
// Created by Daniel St. John on 11/21/22.
//


#include <net.h>

#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include <filesystem>
#include <iostream>

using namespace std;
using namespace std::chrono;
namespace fs = std::filesystem;

// Server part of Client/Server Model
// client_class.cpp is conjugate to the class
// mode here is process to process of host to host

// abstraction server
// we are the UDP service here
// templated
// we receive Request struct
// we reply to requester with Request
// we send bytes


bool isRunning = true;
std::string host = "127.0.0.1";
unsigned short port = 7767;

string processName = string("udp_server_") + std::to_string(port);
inline bool exists (const std::string& name) {
    string path = fs::current_path().string()  + "/" + processName + "/" + name ;
    //cout << path << endl;
    ifstream f(path);
    return f.good();
}
void heartBeat(){
    string path = fs::current_path().string()  + "/" + processName + "/" + "server_heart_beat" ;
    std::ofstream outfile (path,std::ios::out | std::ios::app);
    std::time_t result = std::time(nullptr);
    outfile << std::asctime(std::localtime(&result)) << endl;
    outfile.close();
}
bool IsShutdown(){
    string path = fs::current_path().string()  + "/" + processName + "/" + "server_stop" ;
    return exists(path);
}

int main() {
    cout << "-----------------------" << endl;
    cout << "Start" << endl;
    cout << "-----------------------" << endl;
    cout << fs::current_path() << endl;
    fs::create_directories(processName);

    // server is implemented by supplying a handler with the signature below

    thread t([&]() {
        UdpServer<Request, Response> server(host, port);
        server.Start([&](Request *req) {
            cout << "-----------------------" << endl;
            cout << "Server Provider Handling Request" << endl;
            cout << req->cameraId << ":" << req->gpsTime << ":" << req->seq << endl;
            Response *res = new Response();
            cout << "-----------------------" << endl;
            return res;
        });
        if ( IsShutdown()){
            cout << "Stop Server" << endl;
            server.Stop();
        }
    });

    while ( isRunning) {
//        heartBeat();
//        isRunning = !IsShutdown();
        std::this_thread::sleep_for(1000ms);
    }
    t.join();

    return 0;
}

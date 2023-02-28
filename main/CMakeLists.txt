project(mains)
set(CMAKE_CXX_STANDARD 17)

find_package(Threads REQUIRED)
find_package(Boost REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)
find_package(OpenCV CONFIG REQUIRED)

set(THREADS_PREFER_PTHREAD_FLAG ON)




################################################################
# Process to Process Producer Consumer
################################################################
add_executable(Producer-UdpUtils Producer-UdpUtils.cpp)
target_include_directories( Producer-UdpUtils PUBLIC net )
target_link_libraries(Producer-UdpUtils  PRIVATE net Threads::Threads ${OpenCV_LIBS})

add_executable(Consumer-UdpUtils Consumer-UdpUtils.cpp)
target_include_directories( Consumer-UdpUtils PUBLIC  net)
target_link_libraries(Consumer-UdpUtils  PRIVATE net Threads::Threads ${OpenCV_LIBS} )
################################################################


################################################################
# Process:Client Request/Reply Process:Server
################################################################
add_executable(MAIN-UDP-Server-UdpUtils Server-UdpUtils.cpp)
target_include_directories(MAIN-UDP-Server-UdpUtils PUBLIC net)
target_link_libraries(MAIN-UDP-Server-UdpUtils  PRIVATE net Eigen3::Eigen Threads::Threads)

add_executable(MAIN-UDP-Client-UdpUtils Client-UdpUtils.cpp)
target_include_directories( MAIN-UDP-Client-UdpUtils PUBLIC net  Eigen3::Eigen )
target_link_libraries(MAIN-UDP-Client-UdpUtils PRIVATE net  Eigen3::Eigen Threads::Threads)



add_executable(MAIN-UDP-Server-Class UdpServer.cpp)
target_include_directories( MAIN-UDP-Server-Class PUBLIC net Eigen3::Eigen )
target_link_libraries(MAIN-UDP-Server-Class PRIVATE net  Eigen3::Eigen Threads::Threads)

add_executable(MAIN-UDP-Client-Class UdpClient.cpp)
target_include_directories( MAIN-UDP-Client-Class PUBLIC net Eigen3::Eigen )
target_link_libraries(MAIN-UDP-Client-Class PRIVATE net  Eigen3::Eigen Threads::Threads)


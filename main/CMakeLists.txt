project(mains)
set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

find_package(OpenCV CONFIG REQUIRED)

find_package(Boost REQUIRED)

 


################################################################
# Process to Process Producer Consumer
################################################################
add_executable(MAIN-UDP-Producer-UdpUtils MAIN-UDP-Producer-UdpUtils.cpp)
target_include_directories( MAIN-UDP-Producer-UdpUtils PUBLIC net )
target_link_libraries(MAIN-UDP-Producer-UdpUtils  PRIVATE net Threads::Threads)

add_executable(MAIN-UDP-Consumer-UdpUtils MAIN-UDP-Consumer-UdpUtils.cpp)
target_include_directories( MAIN-UDP-Consumer-UdpUtils PUBLIC  net)
target_link_libraries(MAIN-UDP-Consumer-UdpUtils  PRIVATE net Threads::Threads )
################################################################


################################################################
# Process:Client Request/Reply Process:Server
################################################################
add_executable(MAIN-UDP-Server-UdpUtils MAIN-UDP-Server-UdpUtils.cpp)
target_include_directories(MAIN-UDP-Server-UdpUtils PUBLIC net)
target_link_libraries(MAIN-UDP-Server-UdpUtils  PRIVATE net Eigen3::Eigen Threads::Threads)

add_executable(MAIN-UDP-Client-UdpUtils MAIN-UDP-Client-UdpUtils.cpp)
target_include_directories( MAIN-UDP-Client-UdpUtils PUBLIC net  Eigen3::Eigen )
target_link_libraries(MAIN-UDP-Client-UdpUtils PRIVATE net  Eigen3::Eigen Threads::Threads)

################################################################
# 
################################################################
add_executable(MAIN-UDP-Server-TemplateFunction MAIN-UDP-Server-TemplateFunction.cpp)
target_include_directories(MAIN-UDP-Server-TemplateFunction PUBLIC net)
target_link_libraries(MAIN-UDP-Server-TemplateFunction  PRIVATE net  Eigen3::Eigen Threads::Threads)


add_executable(MAIN-UDP-Client-TemplateFunction MAIN-UDP-Client-TemplateFunction.cpp)
target_include_directories( MAIN-UDP-Client-TemplateFunction PUBLIC net Eigen3::Eigen )
target_link_libraries(MAIN-UDP-Client-TemplateFunction PRIVATE net  Eigen3::Eigen Threads::Threads)


################################################################
#  UDP Cleint/Server ie. Request/Reply with Template to Accomodate 
# "sane" user defined structures
################################################################
add_executable(MAIN-UDP-Server-Class MAIN-UDP-Server-Class.cpp)
target_include_directories( MAIN-UDP-Server-Class PUBLIC net Eigen3::Eigen )
target_link_libraries(MAIN-UDP-Server-Class PRIVATE net  Eigen3::Eigen Threads::Threads)

add_executable(MAIN-UDP-Client-Class MAIN-UDP-Client-Class.cpp)
target_include_directories( MAIN-UDP-Client-Class PUBLIC net Eigen3::Eigen )
target_link_libraries(MAIN-UDP-Client-Class PRIVATE net  Eigen3::Eigen Threads::Threads)



################################################################
#  TCP Client Server
################################################################
add_executable(MAIN-TCP-Server MAIN-TCP-Server.cpp)
target_include_directories( MAIN-TCP-Server PUBLIC net Eigen3::Eigen )
target_link_libraries(MAIN-TCP-Server PRIVATE net  Eigen3::Eigen Threads::Threads  ${OpenCV_LIBS})

add_executable(MAIN-TCP-Client MAIN-TCP-Client.cpp)
target_include_directories( MAIN-TCP-Client PUBLIC net Eigen3::Eigen )
target_link_libraries(MAIN-TCP-Client PRIVATE net  Eigen3::Eigen Threads::Threads  ${OpenCV_LIBS})


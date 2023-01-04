project(net)
set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED)
if(Boost_FOUND)
    message(STATUS "Found Boost Success!")
endif()
 

# if(NOT TARGET spdlog)
#     # Stand-alone build
#     find_package(spdlog REQUIRED)
# endif()

 
add_library(
        ${PROJECT_NAME}
        include/macro.h
        include/utils.h
        include/udp/udp_utils.h
        
        include/udp/UdpProducer.h
        include/udp/UdpRequestReply.h
        include/udp/UpdReceiveReply.h
        include/udp/UdpSend.h
        include/udp/UdpClient.h
        include/udp/UdpServer.h
        

        include/udp/UdpConsumer.h
        # src/udp/UdpConsumer.cpp

        include/udp/UdpConsumeOne.h
        # src/udp/UdpConsumeOne.cpp
        
        include/tcp/SyncTCPServer.h
        include/tcp/SyncTcpClient.h

        include/Props.h
        include/TimeMetric.h
        include/RandomString.h



        src/Props.cpp
        src/utils.cpp
        src/TimeMetric.cpp
        src/RandomString.cpp

        src/udp/udp_utils.cpp
        include/utils.h
        include/net.h
        )

target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
                $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                $<INSTALL_INTERFACE:include>
                ${Boost_INCLUDE_DIRS}
        PRIVATE
        )

target_link_libraries(
        ${PROJECT_NAME}
        ${Boost_LIBRARIES}
        # PRIVATE
        # spdlog::spdlog
        )
        
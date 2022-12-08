project(net)
set(CMAKE_CXX_STANDARD 17)

find_package(boost 1.74.0 REQUIRED)
find_package(CURL CONFIG REQUIRED)
 

 

add_library(
        ${PROJECT_NAME}
        include/macro.h
        include/amssgstypes.h
        include/utils.h
        include/udp/udp_utils.h
        include/udp/UdpConsumer.h
        include/udp/UdpProducer.h
        include/udp/UdpRequestReply.h
        include/udp/UpdReceiveReply.h
        include/udp/UdpSend.h
        include/udp/UdpClient.h
        include/udp/UdpServer.h
        include/Props.h
        include/TimeMetric.h
        include/RandomString.h

        src/Props.cpp
        src/utils.cpp
        src/TimeMetric.cpp
        src/RandomString.cpp

        # include/http/RestClient.h
        # src/http/RestClient.cpp


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
        PRIVATE
        CURL::libcurl
        )
        
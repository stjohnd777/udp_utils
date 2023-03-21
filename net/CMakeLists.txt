project(net)
set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED)
if(Boost_FOUND)
    message(STATUS "Found Boost Success!")
endif()

add_library(
        ${PROJECT_NAME}

        include/macro.h
        include/net.h
        include/UdpUtils.h
        include/UdpClient.h
        include/UdpServer.h
        include/UdpConsumer.h
        include/UdpProducer.h

        src/UdpUtils.cpp
        include/SyncTcpServer.h include/SyncTcpClient.h)

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
        )
        
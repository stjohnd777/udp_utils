project(test)

set(CMAKE_CXX_STANDARD 17)

find_package(Eigen3 CONFIG REQUIRED)
find_package(OpenCV CONFIG REQUIRED)


add_executable(TEST-Hello  teststructs.h catch.hpp TEST-Hello.cpp)
target_include_directories(TEST-Hello PUBLIC net)
target_link_libraries(TEST-Hello  PRIVATE net Eigen3::Eigen)


add_executable(TEST-UdpUtils  teststructs.h catch.hpp TEST-Udp.cpp)
target_include_directories(TEST-UdpUtils PUBLIC net)
target_link_libraries(TEST-UdpUtils PRIVATE net Eigen3::Eigen  )


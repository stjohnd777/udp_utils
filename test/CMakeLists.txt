project(test)

set(CMAKE_CXX_STANDARD 17)

find_package(Eigen3 CONFIG REQUIRED)


find_package(OpenCV CONFIG REQUIRED)


################################################################
# Nameing Conventions
# T2T (Thread 2 Thread)
# P2P (Process 2 Process)
# All Catch2 Test end with executable name _TEST
# All intependent execuatables end woith _MAIN
# cmake target uses _ and cpp code uses - to seperate naming and the namin match up to underscore


################################################################
# Template to Copy
# Test is catch2 is working
################################################################
add_executable(TEST-Hello  teststructs.h catch.hpp TEST-Hello.cpp)
target_include_directories(TEST-Hello PUBLIC net)
target_link_libraries(TEST-Hello  PRIVATE net Eigen3::Eigen)
################################################################


################################################################
# INI
#
################################################################
add_executable(TEST-INI  teststructs.h catch.hpp TEST-INI.cpp)
target_include_directories(TEST-INI PUBLIC net)
target_link_libraries(TEST-INI  PRIVATE net Eigen3::Eigen)



################################################################
# Serialize/Deserialize structs
#
################################################################
add_executable(TEST-Serializer  teststructs.h catch.hpp TEST-Serializer.cpp)
target_include_directories(TEST-Serializer PUBLIC net)
target_link_libraries(TEST-Serializer  PRIVATE net  Eigen3::Eigen)
################################################################



# Procuder Consumer Section

################################################################
# Test UpdUtils Producer-Consumer Thread to Thread
#   Producer
#   void SendTo(std::string host, unsigned short port,const char* pdata, size_t len)
#   Consumer
#   std::tuple<size_t,std::shared_ptr<char[]> >ServerReceiveNoReply(std::string host, unsigned short port)
###############################################################
add_executable(TEST-T2T-UDP-ProducerConsumer-UdpUtils-Structs  teststructs.h catch.hpp TEST-T2T-UDP-ProducerConsumer-UdpUtils-Structs.cpp)
target_include_directories(TEST-T2T-UDP-ProducerConsumer-UdpUtils-Structs PUBLIC net)
target_link_libraries(TEST-T2T-UDP-ProducerConsumer-UdpUtils-Structs PRIVATE net Eigen3::Eigen  )

add_executable(TEST-T2T-UDP-ProducerConsumer-Bytes  teststructs.h catch.hpp TEST-T2T-UDP-ProducerConsumer-Bytes.cpp)
target_include_directories(TEST-T2T-UDP-ProducerConsumer-Bytes PUBLIC net)
target_link_libraries(TEST-T2T-UDP-ProducerConsumer-Bytes PRIVATE net Eigen3::Eigen  )


################################################################
# Test Template Funtion Thread 2 Thread
#   UpdConsumeOne<>
#   UdpSend<>
################################################################
add_executable(TEST-T2T-UDP-ProducerConsumer-TemplateFunctions  teststructs.h catch.hpp TEST-T2T-UDP-ProducerConsumer-TemplateFunction.cpp)
target_include_directories( TEST-T2T-UDP-ProducerConsumer-TemplateFunctions PUBLIC net)
target_link_libraries ( TEST-T2T-UDP-ProducerConsumer-TemplateFunctions PRIVATE net Eigen3::Eigen )


 

################################################################
# Test UpdUtilsSync Request-Response Thread to Thread
# client thread
# std::tuple<size_t,std::shared_ptr<char[]>>
# RequestReply(std::string host, unsigned short port, const char* pdata, size_t len);
# server/service thread
# void ReceiveReply(std::string host, unsigned short port ,  REQ_REPLY_HANDLER handler);
################################################################
add_executable(TEST-T2T-UDP-RequestReply-UdpUtils  teststructs.h catch.hpp TEST-T2T-UDP-RequestReply-UdpUtils.cpp)
target_include_directories(TEST-T2T-UDP-RequestReply-UdpUtils PUBLIC net)
target_link_libraries(TEST-T2T-UDP-RequestReply-UdpUtils PRIVATE net Eigen3::Eigen  )
 

################################################################
# Test UDP Request-Response Thread 2 Thread
# UdpServer<*,*>
# UdpClient<*,*>
#
################################################################
add_executable(TEST-T2T-UDP-RequestReply-TemplateFunction  teststructs.h catch.hpp TEST-T2T-UDP-RequestReply-TemplateFunction.cpp)
target_include_directories(TEST-T2T-UDP-RequestReply-TemplateFunction PUBLIC net)
target_link_libraries(TEST-T2T-UDP-RequestReply-TemplateFunction PRIVATE net  Eigen3::Eigen  )


add_executable(TEST-UdpUtils-TEST  teststructs.h catch.hpp TEST-UdpUtils.cpp)
target_include_directories(TEST-UdpUtils-TEST PUBLIC net)
target_link_libraries(TEST-UdpUtils-TEST PRIVATE net Eigen3::Eigen  )


add_executable(TEST-T2T-UDP-ClientServer-TemplateClass  teststructs.h catch.hpp TEST-T2T-UDP-ClientServer-TemplateClass.cpp)
target_include_directories(TEST-T2T-UDP-ClientServer-TemplateClass PUBLIC net)
target_link_libraries(TEST-T2T-UDP-ClientServer-TemplateClass PRIVATE net Eigen3::Eigen  )

add_executable(TEST-T2T-TCP-ClientServer TEST-T2T-TCP-ClientServer.cpp)
target_include_directories( TEST-T2T-TCP-ClientServer PUBLIC net Eigen3::Eigen )
target_link_libraries(TEST-T2T-TCP-ClientServer PRIVATE net  Eigen3::Eigen   ${OpenCV_LIBS})

 
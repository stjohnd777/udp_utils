#define CATCH_CONFIG_MAIN // provides main(); this line is required in only one .cpp file
#include "catch.hpp"

#include <string>


using namespace std;

#include "net.h"

TEST_CASE("INI TEST", "Props") {

    REQUIRE(true == true);

    string pathConfig = "C:/Users/e438262/dev/lm/gitlab/udp_utils/config.ini";
    lm::utils::Props props(pathConfig);


    // [Application]
    //     name = 1850 - mocks
    //     image_mode = static
    //     truth_ring_depth = 100
    //     data_mode = image_over_write
  
    auto name = props.getIniPropertyAsString("Application.name");
    REQUIRE(name == "1850-mocks");
    auto image_mode = props.getIniPropertyAsString("Application.image_mode");
    REQUIRE(image_mode == "static");
    auto truth_ring_depth = props.getIniPropertyAsString("Application.truth_ring_depth");
    REQUIRE(truth_ring_depth == "100");
    auto data_mode = props.getIniPropertyAsString("Application.data_mode");
    REQUIRE(data_mode == "image_over_write");

    //[StaticImage]
    // image_path = "C:/Users/e438262/dev/lm/gitlab/udp_utils/img/cat.2672x1952.grey16.png"


    // [TruthConsumer]
    // port = 8000
    // 
     //[Camera - 1850 - NOBLACK]
     //name = 1850 - vis - with - black
     //    description = "vis without black levels""
     //    enabled = true
     //    ip = 127.0.0.1
     //    port = 7000
     //    width = 2592
     //    height = 1952
     //    cv_color_mode = 16_GRAYSCALE
     //    interface = GIG_E_VISION

}
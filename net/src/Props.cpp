
#include "Props.h"
#include <iostream>

using namespace std;

namespace lm {
    namespace utils {

        Props::Props() {}

        Props::Props(string configPath) {
     
            boost::property_tree::ini_parser::read_ini(configPath, pt);
            //std::cout << pt.get<std::string>("Application.name") << std::endl;
            //std::cout << pt.get<std::string>("Application.image_mode") << std::endl;
            //std::cout << pt.get<std::string>("Application.truth_ring_depth") << std::endl;
            //std::cout << pt.get<std::string>("Application.data_mode") << std::endl;

        }

  
        string Props::getIniPropertyAsString(string sectionProp) {
            return pt.get<string>(sectionProp);
        }


        std::string Props::getEnvVarAsString(const std::string name) {
            std::string value;
            try {
                std::string value = std::getenv(name.c_str());
            } catch (...) {
                value = nullptr;
            }
            return value;
        }

        int Props::getEnvVarAsInt(const std::string name) {
            int value = -1;
            try {
                std::string svalue = std::getenv(name.c_str());
                std::istringstream(svalue) >> value;
            } catch (...) {

            }
            return value;
        }

        Props::~Props() {
             
        }

    }
}

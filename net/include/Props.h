
#pragma once

#include <string>
#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>


 

        class Props {

        public:

            Props();

            Props(std::string propsFile);

            std::string getEnvVarAsString(const std::string name);

            int getEnvVarAsInt(const std::string name);

            std::string getIniPropertyAsString(std::string sectionProp);

            virtual ~Props();

        private:

            boost::property_tree::ptree pt;


        };

 

 
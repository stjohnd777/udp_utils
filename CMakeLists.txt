
project (lm_upd) 

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_EXTENSIONS OFF)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

set(CMAKE_TOOLCHAIN_FILE /LM/dev/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "")

# Dependency Management:
option(ENABLE_FETCH OFF)
if (ENABLE_FETCH)
    include(cmake/manage_eigen3.cmake)
    include(cmake/manage_googletest.cmake)
    include(cmake/manage_boost.cmake)
endif()


add_subdirectory(net)

#option(ENABLE_HELIX_TYPES "Add HELIX Types" ON)
set(ENABLE_HELIX_TYPES OFF)
if (ENABLE_HELIX_TYPES)
    add_subdirectory(helix_types)
endif()

#option(ENABLE_TESTING "Add Testing" ON)
set(ENABLE_TESTING ON)
if (ENABLE_TESTING )
    add_subdirectory(test)
endif()

#option(ENABLE_EXAMPLES "Add Examples" ON)
set(ENABLE_EXAMPLES ON)
if (ENABLE_EXAMPLES)
    add_subdirectory(main)
endif()



#add_subdirectory(types)
# add_subdirectory(test)
# add_subdirectory(main)



project(lm_upd)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

option(ENABLE_FETCH OFF)
if (ENABLE_FETCH)
    include(cmake/manage_eigen3.cmake)
    include(cmake/manage_googletest.cmake)
    include(cmake/manage_boost.cmake)
endif ()

add_subdirectory(net)
add_subdirectory(test)
add_subdirectory(main)



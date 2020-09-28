cmake_minimum_required(VERSION 3.12.0)

project(one2III VERSION 0.1.0)

set_property(GLOBAL PROPERTY CXX_STANDARD 17)
set_property(GLOBAL PROPERTY CMAKE_CXX_STANDARD_REQUIRED ON)
if(MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)

set(one2III_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(one2III_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)

add_subdirectory(${one2III_SRC_DIR})

add_subdirectory(${one2III_TEST_DIR})

cmake_minimum_required(VERSION 3.3)
project(EffectiveModernCpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

find_package(Boost)

set(SOURCE_FILES_ITEM01 item01.cpp)
add_executable(item01 ${SOURCE_FILES_ITEM01})

set(SOURCE_FILES_ITEM02 item02.cpp)
add_executable(item02 ${SOURCE_FILES_ITEM02})

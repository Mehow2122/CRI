cmake_minimum_required(VERSION 3.2)
project(cpp1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp defines.h)
add_executable(cpp1 ${SOURCE_FILES} Spectrum.h Spectrum.cpp defines.h)
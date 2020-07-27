cmake_minimum_required(VERSION 3.16)
project(2GIS_git)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(2GIS_git
        main.cpp
        serializer.cpp
        serializer.h
        tree.h)

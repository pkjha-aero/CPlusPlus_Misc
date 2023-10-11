cmake_minimum_required(VERSION 2.8)
project(SimProj)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(DassultSys
        interest.cpp
        interest.h
        main.cpp
        person.cpp
        person.h
        utilFunc.cpp
        utilFunc.h)
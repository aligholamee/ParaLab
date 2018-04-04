cmake_minimum_required(VERSION 3.8)
project(pi_number)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        pi-number/pi-number.cpp
        pi-number/pi_parallel.c
        pi-number/stdafx.cpp
        pi-number/stdafx.h
        pi-number/targetver.h
        pi_parallel2.c)

add_executable(pi_number ${SOURCE_FILES})
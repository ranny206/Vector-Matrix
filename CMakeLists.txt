cmake_minimum_required(VERSION 3.13)
project(C___hw1)

set(CMAKE_CXX_STANDARD 17)

set(src Base.h Vector.h Matrix.h Vector.cpp Matrix.cpp main.cpp catch.hpp)

add_executable(C___hw1 ${src})
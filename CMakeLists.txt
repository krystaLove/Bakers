cmake_minimum_required(VERSION 3.15)
project(Bakers)

set(CMAKE_CXX_STANDARD 17)

add_executable(Bakers main.cpp Bun.cpp Bun.h Baker.cpp Baker.h)
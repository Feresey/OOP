cmake_minimum_required(VERSION 3.5)
project(lab04 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_CXX_OPTIONS "-Wall -Wextra -Wpedantic -Wno-sign-compare -Wno-long-long\
          -Weffc++ -Wctor-dtor-privacy -Wnon-virtual-dtor -Wold-style-cast -Winit-self\
          -Wconversion -Wsign-conversion -Wunreachable-code")
set(CMAKE_CXX_OPTIONS_DEBUG "-fsanitize=address -ftest-coverage -g3 -pg")
set(CMAKE_CXX_OPTIONS_RELEASE "-O3 -funroll-loops")

add_executable(${PROJECT_NAME} main.cpp Rectangle.cpp Sqr.cpp Triangle.cpp)

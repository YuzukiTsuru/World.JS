cmake_minimum_required(VERSION 2.8)
project(WorldJS)


add_definitions("-std=c++11")

file(GLOB sources src/*.cpp)

add_executable(WorldJS ${sources})

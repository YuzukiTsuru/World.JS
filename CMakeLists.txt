cmake_minimum_required(VERSION 2.8)
project(WorldJS)

add_definitions("-std=c++11")

include_directories(
    lib/WorldCmake/World/src/
    src/WorldJS
    tools
)

file(GLOB sources src/*.cpp)
file(GLOB tools tools/*.cpp)

add_library(tools ${tools})

add_executable(WorldJS ${sources})

set_target_properties(WorldJS PROPERTIES LINK_FLAGS "-s DEMANGLE_SUPPORT=1 --bind")

target_link_libraries(WorldJS tools)

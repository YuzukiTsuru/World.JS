cmake_minimum_required(VERSION 3.8)
project(WorldJS)

add_definitions("-std=c++11")
set(flag "-s SAFE_HEAP=1 -s WASM=1 --js-opts 0 -g3 -Oz -s ASSERTIONS=2 -s DEMANGLE_SUPPORT=1 --bind --preload-file vaiueo2d.wav --use-preload-plugins --llvm-opts 3 -v")

include_directories(
    lib/WorldCmake/World/src/
    src/WorldJS
    tools
)

file(GLOB sources src/*.cpp)
file(GLOB tools tools/*.cpp)
file(GLOB World lib/WorldCmake/World/src/*.cpp)

add_library(tools ${tools})
add_library(World ${World})

add_executable(WorldJS ${sources})

set_target_properties(WorldJS PROPERTIES LINK_FLAGS ${flag})

target_link_libraries(WorldJS tools World)

cmake_minimum_required(VERSION 3.8)
project(WorldJS)

set(CMAKE_CXX_STANDARD 17)

set(flag "-s SAFE_HEAP=1 -s WASM=1 -g3 -Oz -s ASSERTIONS=2 -s DEMANGLE_SUPPORT=1 --bind --preload-file vaiueo2d.wav --use-preload-plugins --llvm-opts 3 -v")

include_directories(
        lib/WorldCMake/World/src/
        src/WorldJS
        tools
)

file(GLOB sources src/*.cpp)
file(GLOB tools tools/*.cpp)
file(GLOB World lib/WorldCMake/World/src/*.cpp)

add_library(tools ${tools})
add_library(World ${World})

add_executable(WorldJS ${sources})

set_target_properties(WorldJS PROPERTIES LINK_FLAGS ${flag})

target_link_libraries(WorldJS tools World)

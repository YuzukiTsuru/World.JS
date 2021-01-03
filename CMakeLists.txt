cmake_minimum_required(VERSION 3.8)
project(WorldJS)

set(CMAKE_CXX_STANDARD 17)

set(flag "\
        -s SAFE_HEAP=1 \
        -s WASM=1 \
        -s FORCE_FILESYSTEM=1 \
        -s ALLOW_MEMORY_GROWTH=1 \
        -s LLD_REPORT_UNDEFINED \
        -s STRICT=1 \
        --no-entry \
        -g3 \
        -Oz \
        --bind \
        --preload-file vaiueo2d.wav \
        --use-preload-plugins \
        --llvm-opts 3 \
        ")

include_directories(
        lib/WorldCMake/src/
        src/WorldJS/
        src/WorldJSModule/
        tools
)

file(GLOB sources src/*.cpp)
file(GLOB tools tools/*.cpp)
file(GLOB Module src/WorldJSModule/*.cpp)
file(GLOB World lib/WorldCMake/src/*.cpp)

add_library(tools ${tools})
add_library(World ${World})

add_executable(WorldJS ${sources} ${Module})

set_target_properties(WorldJS PROPERTIES LINK_FLAGS ${flag})
target_link_libraries(WorldJS tools World)

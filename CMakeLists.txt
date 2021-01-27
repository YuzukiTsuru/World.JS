cmake_minimum_required(VERSION 3.8)
project(WorldJS)

set(CMAKE_CXX_STANDARD 17)

if (CMAKE_BUILD_TYPE STREQUAL Debug)
        set(flag "\
        -s SAFE_HEAP=1 \
        -s WASM=1 \
        -s FORCE_FILESYSTEM=1 \
        -s ALLOW_MEMORY_GROWTH=1 \
        -s LLD_REPORT_UNDEFINED \
        -s STRICT=1 \
        -s ASSERTIONS=1 \
        --no-entry \
        --bind \
        --preload-file vaiueo2d.wav \
        --use-preload-plugins \
        ")
else()
        set(flag "\
        -s SAFE_HEAP=1 \
        -s WASM=1 \
        -s FORCE_FILESYSTEM=1 \
        -s ALLOW_MEMORY_GROWTH=1 \
        -s LLD_REPORT_UNDEFINED \
        -s STRICT=1 \
        -s ASSERTIONS=1 \
        --no-entry \
        -g3 \
        -Oz \
        --bind \
        --llvm-opts 3 \
        ")
endif ()

include_directories(
        lib/WorldCMake/src/
        src/WorldJS/
        src/Wav2World/Module/
        src/Wav2World/
        tools
)

file(GLOB sources src/*.cpp)
file(GLOB tools tools/*.cpp)
file(GLOB W2WModule src/Wav2World/Module/*.cpp)
file(GLOB World lib/WorldCMake/src/*.cpp)
file(GLOB Wav2World src/Wav2World/*.cpp)

add_library(tools ${tools})
add_library(World ${World})
add_library(Wav2World ${Wav2World} ${W2WModule})
target_link_libraries(Wav2World World)

# World.JS
add_executable(WorldJS ${sources} ${Module})
set_target_properties(WorldJS PROPERTIES LINK_FLAGS ${flag} DEBUG_POSTFIX "d")
target_link_libraries(WorldJS tools World Wav2World)


if (CMAKE_BUILD_TYPE STREQUAL Debug)
        # Copy Files
        add_custom_command(TARGET WorldJS POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/test/index.html" ${CMAKE_BINARY_DIR})
        add_custom_command(TARGET WorldJS PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/test/vaiueo2d.wav" ${CMAKE_BINARY_DIR})
endif()

# test
add_executable(temp_test test/temp_test.cpp)
target_link_libraries(temp_test tools Wav2World)
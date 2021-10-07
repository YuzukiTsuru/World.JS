cmake_minimum_required(VERSION 3.8)
project(WorldJS)

set(CMAKE_CXX_STANDARD 17)

option(WASM "Build to WASM Code" OFF)

if (NOT CMAKE_TOOLCHAIN_FILE)
    message(WARNING "CMAKE_TOOLCHAIN_FILE is not defined, you may need to set it \
            -DCMAKE_TOOLCHAIN_FILE=\"path/to/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake\"")
endif ()

# EMSDK VERSION CHECK
if (${EMSCRIPTEN_VERSION} VERSION_LESS 2.0.29)
    message(FATAL_ERROR "EMSCRIPTEN version looks too old. Was ${EMSCRIPTEN_VERSION}, should be at least 2.0.29.")
endif ()

set(flag "-s SAFE_HEAP=1 -s FORCE_FILESYSTEM=1 -s ALLOW_MEMORY_GROWTH=1 -s STRICT=1 -s ALLOW_UNIMPLEMENTED_SYSCALLS \
          -s ASSERTIONS=1 --post-js ${CMAKE_SOURCE_DIR}/src/JS/JavaScriptLoader.js --no-entry")

if (WASM)
    set(flag "-s WASM=1 ${flag}")
else ()
    set(flag "-s WASM=0 ${flag}")
endif ()

if (CMAKE_BUILD_TYPE STREQUAL Debug)
    set(flag "${flag} -Wall -O0 -g3 -s LLD_REPORT_UNDEFINED --post-js ${CMAKE_SOURCE_DIR}/src/JS/StaticDebug.js --bind \
              --preload-file vaiueo2d.wav --use-preload-plugins")
else ()
    set(flag "${flag} -g0 -Oz --closure 2 --bind")
endif ()

add_subdirectory(lib/WorldCMake)

include_directories(
        lib/WorldCMake/src/
        lib/WorldCMake/tools/
        src/WorldJS/
        src/Wav2World/Module/
        src/Wav2World/
        src/
)

file(GLOB sources src/*.cpp)
file(GLOB WorldJS src/WorldJS/*.cpp)
file(GLOB W2WModule src/Wav2World/Module/*.cpp)
file(GLOB Wav2World src/Wav2World/*.cpp)

add_library(Wav2World ${Wav2World} ${W2WModule})
target_link_libraries(Wav2World world::core)

# World.JS
add_executable(WorldJS ${sources} ${WorldJS} ${Module} src/Config.h)
set_target_properties(WorldJS PROPERTIES LINK_FLAGS ${flag} DEBUG_POSTFIX "d")
target_link_libraries(WorldJS world::core world::tool Wav2World)


if (CMAKE_BUILD_TYPE STREQUAL Debug)
    # Copy Files
    add_custom_command(TARGET WorldJS PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/test/vaiueo2d.wav" ${CMAKE_BINARY_DIR})
    add_custom_command(TARGET WorldJS POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/test/index.html" ${CMAKE_BINARY_DIR})

    # test
    add_executable(temp_test test/temp_test.cpp)
    set_target_properties(temp_test PROPERTIES LINK_FLAGS "-s LLD_REPORT_UNDEFINED --bind --no-entry")
endif ()

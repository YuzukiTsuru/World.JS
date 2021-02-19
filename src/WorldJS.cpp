//
// Created by YuzukiTsuru on 2019/7/14.
//
#include <utility>

#include "WorldJS.h"

//-----------------------------------------------------------------------------
// The JavaScript API in C++
//----------------------------------------------------------------------------_

EMSCRIPTEN_KEEPALIVE emscripten::val WorldJS::Dio(emscripten::val x_val, int fs, double frame_period) {
    return WorldNativeFun::Dio_JS(std::move(x_val), fs, frame_period);
}

EMSCRIPTEN_KEEPALIVE emscripten::val WorldJS::Harvest(emscripten::val x_val, int fs, double frame_period) {
    return WorldNativeFun::Harvest_JS(std::move(x_val), fs, frame_period);
}

EMSCRIPTEN_KEEPALIVE emscripten::val WorldJS::CheapTrick(emscripten::val x_val, emscripten::val f0_val, emscripten::val time_axis_val, int fs) {
    return WorldNativeFun::CheapTrick_JS(std::move(x_val), std::move(f0_val), std::move(time_axis_val), fs);
}

EMSCRIPTEN_KEEPALIVE emscripten::val WorldJS::D4C(emscripten::val x_val, emscripten::val f0_val, emscripten::val time_axis_val, int fft_size, int fs) {
    return WorldNativeFun::D4C_JS(std::move(x_val), std::move(f0_val), std::move(time_axis_val), fft_size, fs);
}

EMSCRIPTEN_KEEPALIVE emscripten::val WorldJS::Synthesis(emscripten::val f0_val, const emscripten::val &spectral_val, const emscripten::val &aperiodicity_val, int fft_size, int fs, const emscripten::val &frame_period) {
    return WorldNativeFun::Synthesis_JS(std::move(f0_val), spectral_val, aperiodicity_val, fft_size, fs, frame_period);
}

EMSCRIPTEN_KEEPALIVE void WorldJS::DisplayInformation(int fs, int nbit, int x_length) {
    WorldNativeIO::DisplayInformation(fs, nbit, x_length);
}

EMSCRIPTEN_KEEPALIVE emscripten::val WorldJS::GetInformation(int fs, int nbit, int x_length) {
    return WorldNativeIO::GetInformation(fs, nbit, x_length);
}

EMSCRIPTEN_KEEPALIVE emscripten::val WorldJS::WavRead(const std::string &filename) {
    return WorldNativeIO::WavRead_JS(filename);
}

EMSCRIPTEN_KEEPALIVE emscripten::val WorldJS::WavWrite(emscripten::val y_val, int fs, const std::string &filename) {
    return WorldNativeIO::WavWrite_JS(std::move(y_val), fs, filename);
}

EMSCRIPTEN_KEEPALIVE void WorldJS::DisplayInformationVal(emscripten::val x) {
    WorldJSWrapper::DisplayInformationVal(std::move(x));
}

EMSCRIPTEN_KEEPALIVE emscripten::val WorldJS::GetInformationVal(const emscripten::val &x) {
    return WorldJSWrapper::GetInformationVal(x);
}

EMSCRIPTEN_KEEPALIVE emscripten::val WorldJS::Wav2World(const std::string &fileName) {
    return WorldJSWrapper::W2World(fileName);
}

//-----------------------------------------------------------------------------
// The JavaScript API bind for C++
//-----------------------------------------------------------------------------
EMSCRIPTEN_BINDINGS(WorldJS) {
    emscripten::class_<WorldJS>("WorldJS")
            .constructor<>()
            .function("DisplayInformation", &WorldJS::DisplayInformation)
            .function("WavRead", &WorldJS::WavRead)
            .function("GetInformation", &WorldJS::GetInformation)
            .function("WavWrite", &WorldJS::WavWrite)
            .function("Dio", &WorldJS::Dio)
            .function("Harvest", &WorldJS::Harvest)
            .function("CheapTrick", &WorldJS::CheapTrick)
            .function("D4C", &WorldJS::D4C)
            .function("Synthesis", &WorldJS::Synthesis)
            .function("DisplayInformationVal", &WorldJS::DisplayInformationVal)
            .function("GetInformationVal", &WorldJS::GetInformationVal)
            .function("Wav2World", &WorldJS::Wav2World);
}


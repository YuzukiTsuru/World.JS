//
// Created by YuzukiTsuru on 2019/7/14.
//
#include <emscripten/bind.h>

#include "WorldJS.h"
#include "WorldNativeIO.h"
#include "WorldNativeFun.h"
#include "WorldJSWrapper.h"

//-----------------------------------------------------------------------------
// The JavaScript API for C++
//-----------------------------------------------------------------------------
EMSCRIPTEN_BINDINGS(WorldJS) {
    emscripten::function("DisplayInformation", &WorldNativeIO::DisplayInformation);
    emscripten::function("WavRead_JS", &WorldNativeIO::WavRead_JS);
    emscripten::function("GetInformation", &WorldNativeIO::GetInformation);
    emscripten::function("WavWrite_JS", &WorldNativeIO::WavWrite_JS);
    emscripten::function("Dio_JS", &WorldNativeFun::Dio_JS);
    emscripten::function("Harvest_JS", &WorldNativeFun::Harvest_JS);
    emscripten::function("CheapTrick_JS", &WorldNativeFun::CheapTrick_JS);
    emscripten::function("D4C_JS", &WorldNativeFun::D4C_JS);
    emscripten::function("Synthesis_JS", &WorldNativeFun::Synthesis_JS);
    emscripten::function("DisplayInformationVal", &WorldJSWrapper::DisplayInformationVal);
    emscripten::function("GetInformationVal", &WorldJSWrapper::GetInformationVal);
    emscripten::function("Wav2World", &WorldJSWrapper::W2World);
}

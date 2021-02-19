#ifndef WORLDJS_WORLDJS_H
#define WORLDJS_WORLDJS_H
//-----------------------------------------------------------------------------
// WORLD core functions.
//-----------------------------------------------------------------------------
#include "world/d4c.h"
#include "world/dio.h"
#include "world/harvest.h"
#include "world/matlabfunctions.h"
#include "world/cheaptrick.h"
#include "world/stonemask.h"
#include "world/synthesis.h"
#include "world/synthesisrealtime.h"

//-----------------------------------------------------------------------------
// WORLD IO functions.
//-----------------------------------------------------------------------------
#include "audioio.h"

//-----------------------------------------------------------------------------
// WORLD JS functions.
//-----------------------------------------------------------------------------
#include "ErrorCode.h"
#include "Converter.h"
#include "Wav2World.h"
#include "WorldNativeIO.h"
#include "WorldNativeFun.h"
#include "WorldJSWrapper.h"

//-----------------------------------------------------------------------------
// emscripten functions.
//-----------------------------------------------------------------------------
#include <emscripten.h>
#include <emscripten/val.h>
#include <emscripten/bind.h>

class WorldJS {
public:
    WorldJS() = default;

    ~WorldJS() = default;

    static EMSCRIPTEN_KEEPALIVE emscripten::val Dio(emscripten::val x_val, int fs, double frame_period);

    static EMSCRIPTEN_KEEPALIVE emscripten::val Harvest(emscripten::val x_val, int fs, double frame_period);

    static EMSCRIPTEN_KEEPALIVE emscripten::val CheapTrick(emscripten::val x_val, emscripten::val f0_val, emscripten::val time_axis_val, int fs);

    static EMSCRIPTEN_KEEPALIVE emscripten::val D4C(emscripten::val x_val, emscripten::val f0_val, emscripten::val time_axis_val, int fft_size, int fs);

    static EMSCRIPTEN_KEEPALIVE emscripten::val Synthesis(emscripten::val f0_val, const emscripten::val &spectral_val, const emscripten::val &aperiodicity_val, int fft_size, int fs, const emscripten::val &frame_period);

    static EMSCRIPTEN_KEEPALIVE void DisplayInformation(int fs, int nbit, int x_length);

    static EMSCRIPTEN_KEEPALIVE emscripten::val GetInformation(int fs, int nbit, int x_length);

    static EMSCRIPTEN_KEEPALIVE emscripten::val WavRead(const std::string &filename);

    static EMSCRIPTEN_KEEPALIVE emscripten::val WavWrite(emscripten::val y_val, int fs, const std::string &filename);
};

#endif //WORLDJS_WORLDJS_H
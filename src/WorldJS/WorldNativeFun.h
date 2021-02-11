//
// Created by YuzukiTsuru on 2021/2/11.
//

#ifndef WORLDJS_WORLDNATIVEFUN_H
#define WORLDJS_WORLDNATIVEFUN_H

#include <iostream>
#include <emscripten.h>

#include "WorldJS.h"
#include "Converter.h"

class WorldNativeFun {
public:
    // DIO Wrapper
    static EMSCRIPTEN_KEEPALIVE emscripten::val Dio_JS(emscripten::val x_val, int fs, double frame_period);

    // Harvest
    static EMSCRIPTEN_KEEPALIVE emscripten::val Harvest_JS(emscripten::val x_val, int fs, double frame_period);

    // CheapTrick
    static EMSCRIPTEN_KEEPALIVE emscripten::val CheapTrick_JS(emscripten::val x_val, emscripten::val f0_val, emscripten::val time_axis_val, int fs);

    // D4C
    static EMSCRIPTEN_KEEPALIVE emscripten::val D4C_JS(emscripten::val x_val, emscripten::val f0_val, emscripten::val time_axis_val, int fft_size, int fs);

    // Synthesis
    static EMSCRIPTEN_KEEPALIVE emscripten::val Synthesis_JS(emscripten::val f0_val, const emscripten::val &spectral_val, const emscripten::val &aperiodicity_val, int fft_size, int fs, const emscripten::val &frame_period);
};


#endif //WORLDJS_WORLDNATIVEFUN_H

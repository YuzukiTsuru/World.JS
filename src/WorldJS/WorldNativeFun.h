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
    static emscripten::val Dio_JS(emscripten::val x_val, int fs, double frame_period);

    // Harvest
    static emscripten::val Harvest_JS(emscripten::val x_val, int fs, double frame_period);

    // CheapTrick
    static emscripten::val
    CheapTrick_JS(emscripten::val x_val, emscripten::val f0_val, emscripten::val time_axis_val, int fs);

    // D4C
    static emscripten::val
    D4C_JS(emscripten::val x_val, emscripten::val f0_val, emscripten::val time_axis_val, int fft_size, int fs);

    // Synthesis
    static emscripten::val
    Synthesis_JS(emscripten::val f0_val, const emscripten::val &spectral_val, const emscripten::val &aperiodicity_val,
                 int fft_size, int fs, const emscripten::val &frame_period);
};


#endif //WORLDJS_WORLDNATIVEFUN_H

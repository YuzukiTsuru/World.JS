//
// Created by YuzukiTsuru on 2021/2/5.
//

#ifndef WORLDJS_WORLDNATIVEIO_H
#define WORLDJS_WORLDNATIVEIO_H

#include <iostream>

#include "WorldJS.h"
#include "Converter.h"

class WorldNativeIO {
public:
    // Display Information in console
    static EMSCRIPTEN_KEEPALIVE void DisplayInformation(int fs, int nbit, int x_length);

    // GetInformation in HTML
    static EMSCRIPTEN_KEEPALIVE emscripten::val GetInformation(int fs, int nbit, int x_length);

    // WavFile Read
    static EMSCRIPTEN_KEEPALIVE emscripten::val WavRead_JS(const std::string &filename);

    // Wavfile Write
    static EMSCRIPTEN_KEEPALIVE emscripten::val WavWrite_JS(emscripten::val y_val, int fs, const std::string &filename);
};


#endif //WORLDJS_WORLDNATIVEIO_H

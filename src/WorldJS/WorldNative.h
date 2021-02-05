//
// Created by YuzukiTsuru on 2021/2/5.
//

#ifndef WORLDJS_WORLDNATIVE_H
#define WORLDJS_WORLDNATIVE_H

#include <iostream>
#include <emscripten.h>

#include "WorldJS.h"
#include "Converter.h"

class WorldNative {
public:
    static EMSCRIPTEN_KEEPALIVE void DisplayInformation(int fs, int nbit, int x_length);

    static EMSCRIPTEN_KEEPALIVE emscripten::val GetInformation(int fs, int nbit, int x_length);

};


#endif //WORLDJS_WORLDNATIVE_H

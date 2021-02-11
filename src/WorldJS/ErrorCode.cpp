//
// Created by YuzukiTsuru on 2021/2/11.
//

#include "emscripten.h"
#include "ErrorCode.h"

void EM_TERM() {
    EM_ASM(function WorldJSException(message) {
        this.message = message;
        this.name = 'WorldJSException';
    }
        throw new WorldJSException("WorldJS Error is Detected. Terminated.");
    );
}
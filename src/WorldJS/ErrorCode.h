//
// Created by YuzukiTsuru on 2021/1/28.
//

#ifndef WORLDJS_ERRORCODE_H
#define WORLDJS_ERRORCODE_H

#include <emscripten.h>

void EM_TERM();

/*
 *
 * #define EM_LOG_CONSOLE   1
 * #define EM_LOG_WARN      2
 * #define EM_LOG_ERROR     4
 * #define EM_LOG_C_STACK   8
 * #define EM_LOG_JS_STACK 16
 * #define EM_LOG_DEMANGLE 32  // deprecated
 * #define EM_LOG_NO_PATHS 64
 * #define EM_LOG_FUNC_PARAMS 128
 * #define EM_LOG_DEBUG    256
 * #define EM_LOG_INFO     512
 */

#define E00 EM_LOG_ERROR, "Audio File Error."
#define E01 EM_LOG_ERROR, "Audio Length Error, Audio Length Got 0"

#endif //WORLDJS_ERRORCODE_H

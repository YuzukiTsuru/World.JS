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
#include <emscripten/bind.h>

class WorldJS {
public:

};

#endif //WORLDJS_WORLDJS_H
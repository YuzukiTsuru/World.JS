#include <iostream>
#include <string>
#include <emscripten.h>
#include <emscripten/val.h>
#include <emscripten/bind.h>

#include "audioio.h"

#include "WorldJS.h"


using namespace std;
using namespace emscripten;

extern "C" {
    int Len(string file){
        cout << file << endl;
        const char *files = file.c_str();
        cout << files << endl;
        return GetAudioLength(files);
    }
}

EMSCRIPTEN_BINDINGS(my_module) {
    emscripten::function("Len", &Len);
}

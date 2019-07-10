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
    int Len(string file) {
        cout << file << endl;
        const char *files = file.c_str();
        cout << files << endl;
        return GetAudioLength(files);
    }

    int DisplayInformation(int fs, int nbit, int x_length) {
        printf("File information\n");
        printf("Sampling : %d Hz %d Bit\n", fs, nbit);
        printf("Length %d [sample]\n", x_length);
        printf("Length %f [sec]\n", static_cast<double>(x_length) / fs);
        return 0;
    }
}

EMSCRIPTEN_BINDINGS(my_module) {
    emscripten::function("Len", &Len);
    emscripten::function("DisplayInformation", &DisplayInformation);
}

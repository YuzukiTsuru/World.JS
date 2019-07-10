#include <iostream>
#include <string>

#include <emscripten.h>
#include <emscripten/val.h>
#include <emscripten/bind.h>

#include "audioio.h"

#include "WorldJS.h"

using namespace std;
using namespace emscripten;

//-----------------------------------------------------------------------------
// struct for WORLD
// This struct is an option.
// Users are NOT forced to use this struct.
//-----------------------------------------------------------------------------
typedef struct
{
    emscripten::val f0;
    emscripten::val time_axis;
    emscripten::val spectral;
    emscripten::val aperiodicity;
    int fs;
    int nbits;
    int frame_length;
    int fft_size;
} WorldJS;

namespace
{
template <class Type>
val Get1XArray(Type *arr, int len)
{
    return val(typed_memory_view(len, arr));
}

template <class Type>
val Get2XArray(Type **arr, int y_len, int x_len)
{
    val arr2x = val::array();
    for (int i = 0; i < y_len; i++)
    {
        arr2x.set(i, Get1XArray<Type>(arr[i], x_len));
    }
    return arr2x;
}
} // namespace

int DisplayInformation(int fs, int nbit, int x_length)
{
    printf("File information\n");
    printf("Sampling : %d Hz %d Bit\n", fs, nbit);
    printf("Length %d [sample]\n", x_length);
    printf("Length %f [sec]\n", static_cast<double>(x_length) / fs);
    return 0;
}
// WavFile Read
val WavRead_JS(string filename)
{
    val InWav = val::object();
    const char *f = filename.c_str();
    int fs, nbit;
    int x_length = GetAudioLength(f);
    double *x = new double[x_length];
    wavread(f, &fs, &nbit, x);
    InWav.set("x", Get1XArray<double>(x, x_length));
    InWav.set("fs", fs);
    InWav.set("nbit", nbit);
    InWav.set("x_length", x_length);
    delete[] x;
    return InWav;
}

EMSCRIPTEN_BINDINGS(my_module)
{
    emscripten::function("DisplayInformation", &DisplayInformation);
    emscripten::function("WavRead_JS", &WavRead_JS);
}


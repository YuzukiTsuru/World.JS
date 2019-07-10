#include <iostream>
#include <string>
#include <emscripten.h>
#include <emscripten/val.h>
#include <emscripten/bind.h>

#include "audioio.h"

#include "WorldJS.h"

using namespace std;
using namespace emscripten;

#if (defined(__WIN32__) || defined(_WIN32)) && !defined(__MINGW32__)
#include <conio.h>
#include <windows.h>
#pragma comment(lib, "winmm.lib")
#pragma warning(disable : 4996)
#endif
#if (defined(__linux__) || defined(__CYGWIN__) || defined(__APPLE__))
#include <stdint.h>
#include <sys/time.h>
#endif

#if (defined(__linux__) || defined(__CYGWIN__) || defined(__APPLE__))
// Linux porting section: implement timeGetTime() by gettimeofday(),
#ifndef DWORD
#define DWORD uint32_t
#endif
DWORD timeGetTime()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    DWORD ret = static_cast<DWORD>(tv.tv_usec / 1000 + tv.tv_sec * 1000);
    return ret;
}
#endif

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

extern "C"
{
    int Len(string file)
    {
        cout << file << endl;
        const char *files = file.c_str();
        cout << files << endl;
        return GetAudioLength(files);
    }

    int DisplayInformation(int fs, int nbit, int x_length)
    {
        printf("File information\n");
        printf("Sampling : %d Hz %d Bit\n", fs, nbit);
        printf("Length %d [sample]\n", x_length);
        printf("Length %f [sec]\n", static_cast<double>(x_length) / fs);
        return 0;
    }
}

EMSCRIPTEN_BINDINGS(my_module)
{
    emscripten::function("Len", &Len);
    emscripten::function("DisplayInformation", &DisplayInformation);
}

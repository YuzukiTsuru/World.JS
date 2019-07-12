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
template <class Type>
Type *GetPtrFrom1XArray(val arr, int *len = NULL)
{
    if (len == NULL)
    {
        len = new int[1];
    }
    *len = arr["length"].as<int>();
    Type *ret = new Type[*len];
    val module = val::global("Module");
    int ptr = (int)ret / sizeof(Type);
    module["HEAPF64"].call<val>("set", arr, val(ptr));
    return ret;
}

template <class Type>
Type **GetPtrFrom2XArray(val arr, int *y_len = NULL, int *x_len = NULL)
{
    if (y_len == NULL)
    {
        x_len = new int[1];
    }
    if (x_len == NULL)
    {
        x_len = new int[1];
    }

    *y_len = arr["length"].as<int>();

    val module = val::global("Module");
    int ptr;
    if (*y_len > 0)
    {
        *x_len = arr[0]["length"].as<int>();
        Type **ret = new Type *[*y_len];
        for (int i = 0; i < *y_len; i++)
        {
            ret[i] = new Type[*x_len];
            ptr = (int)ret[i] / sizeof(Type);
            module["HEAPF64"].call<val>("set", arr[i], val(ptr));
        }
        return ret;
    }
    else
    {
        *x_len = 0;
        return NULL;
    }
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
    // init val
    val InWav = val::object();
    // Get File Name
    const char *f = filename.c_str();
    int fs, nbit;
    // GetAudioLength for read
    int x_length = GetAudioLength(f);
    double *x = new double[x_length];
    // Use tools/audioio.cpp wavread function
    wavread(f, &fs, &nbit, x);
    // Set the output value
    InWav.set("x", Get1XArray<double>(x, x_length));
    InWav.set("fs", fs);
    InWav.set("nbit", nbit);
    InWav.set("x_length", x_length);
    delete[] x;
    return InWav;
}

val Dio_JS(val x_val, int fs, double frame_period)
{
    // init val
    val ret = val::object();
    int x_length;
    // translate array to C++ ptr
    double *x = GetPtrFrom1XArray<double>(x_val, &x_length);
    // init dio
    DioOption option = {0};
    InitializeDioOption(&option);
    // Get dio settings
    option.frame_period = frame_period;
    option.speed = 1;
    option.f0_floor = 71.0;
    option.allowed_range = 0.2;
    // Get Samples For DIO
    int f0_length = GetSamplesForDIO(fs, x_length, frame_period);
    double *f0 = new double[f0_length];
    double *time_axis = new double[f0_length];
    // run dio
    Dio(x, x_length, fs, &option, time_axis, f0);
    // Set the output value
    ret.set("f0", Get1XArray<double>(f0, f0_length));
    ret.set("time_axis", Get1XArray<double>(time_axis, f0_length));
    // destory memory
    delete[] f0;
    delete[] time_axis;
    delete[] x;
    return ret;
}

val Harvest_JS(val x_val, int fs, double frame_period)
{
    // init val
    val ret = val::object();
    // init 
    int x_length;
    // translate array to C++ ptr
    double *x = GetPtrFrom1XArray<double>(x_val, &x_length);
    // init Harvest Option
    HarvestOption option = {0};
    InitializeHarvestOption(&option);
    // Get harvest settings
    option.frame_period = frame_period;
    option.f0_floor = 71.0;
    // Get Samples For Harvest
    int f0_length = GetSamplesForHarvest(fs, x_length, frame_period);
    double *f0 = new double[f0_length];
    double *time_axis = new double[f0_length];
    // run harvest
    Harvest(x, x_length, fs, &option, time_axis, f0);
    // set outputs
    ret.set("f0", Get1XArray<double>(f0, f0_length));
    ret.set("time_axis", Get1XArray<double>(time_axis, f0_length));
    // destory memory
    delete[] f0;
    delete[] time_axis;
    delete[] x;
    return ret;
}

//-----------------------------------------------------------------------------
// The JavaScript API for C++
//-----------------------------------------------------------------------------
EMSCRIPTEN_BINDINGS(my_module)
{
    emscripten::function("DisplayInformation", &DisplayInformation);
    emscripten::function("WavRead_JS", &WavRead_JS);
    emscripten::function("Dio_JS", &Dio_JS);
    emscripten::function("Harvest_JS", &Harvest_JS);
}

#include <iostream>
#include <string>

#include <emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/val.h>

#include "audioio.h"

#include "WorldJS.h"

using namespace std;
using namespace emscripten;

namespace {
template <class Type>
val Get1XArray(Type* arr, int len) {
    return val(typed_memory_view(len, arr));
}

template <class Type>
val Get2XArray(Type** arr, int y_len, int x_len) {
    val arr2x = val::array();
    for (int i = 0; i < y_len; i++) {
        arr2x.set(i, Get1XArray<Type>(arr[i], x_len));
    }
    return arr2x;
}

template <class Type>
Type* GetPtrFrom1XArray(val arr, int* len = NULL) {
    if (len == NULL) {
        len = new int[1];
    }
    *len = arr["length"].as<int>();
    Type* ret = new Type[*len];
    val module = val::global("Module");
    int ptr = ( int )ret / sizeof(Type);
    module["HEAPF64"].call<val>("set", arr, val(ptr));
    return ret;
}

template <class Type>
Type** GetPtrFrom2XArray(val arr, int* y_len = NULL, int* x_len = NULL) {
    if (y_len == NULL) {
        y_len = new int[1];
    }
    if (x_len == NULL) {
        x_len = new int[1];
    }

    *y_len = arr["length"].as<int>();

    val module = val::global("Module");
    int ptr;
    if (*y_len > 0) {
        *x_len = arr[0]["length"].as<int>();
        Type** ret = new Type*[*y_len];
        for (int i = 0; i < *y_len; i++) {
            ret[i] = new Type[*x_len];
            ptr = ( int )ret[i] / sizeof(Type);
            module["HEAPF64"].call<val>("set", arr[i], val(ptr));
        }
        return ret;
    } else {
        *x_len = 0;
        return NULL;
    }
}
}  // namespace

int DisplayInformation(int fs, int nbit, int x_length) {
    printf("File information\n");
    printf("Sampling : %d Hz %d Bit\n", fs, nbit);
    printf("Length %d [sample]\n", x_length);
    printf("Length %f [sec]\n", static_cast<double>(x_length) / fs);
    return 0;
}
// WavFile Read
val WavRead_JS(string filename) {
    // init val
    val InWav = val::object();
    // Get File Name
    const char* f = filename.c_str();
    int fs, nbit;
    // GetAudioLength for read
    int x_length = GetAudioLength(f);
    double* x = new double[x_length];
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

val Dio_JS(val x_val, int fs, double frame_period) {
    // init val
    val ret = val::object();
    int x_length;
    // translate array to C++ ptr
    double* x = GetPtrFrom1XArray<double>(x_val, &x_length);
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
    double* f0 = new double[f0_length];
    double* time_axis = new double[f0_length];
    double* refined_f0 = new double[f0_length];
    // run dio
    Dio(x, x_length, fs, &option, time_axis, f0);
    StoneMask(x, x_length, fs, time_axis, f0, f0_length, refined_f0);
    for (int i = 0; i < f0_length; ++i) {
        f0[i] = refined_f0[i];
    }
    // Set the output value
    ret.set("f0", Get1XArray<double>(f0, f0_length));
    ret.set("time_axis", Get1XArray<double>(time_axis, f0_length));
    // destory memory
    delete[] f0;
    delete[] time_axis;
    delete[] x;
    delete[] refined_f0;
    return ret;
}

val Harvest_JS(val x_val, int fs, double frame_period) {
    // init val
    val ret = val::object();
    // init
    int x_length;
    // translate array to C++ ptr
    double* x = GetPtrFrom1XArray<double>(x_val, &x_length);
    // init Harvest Option
    HarvestOption option = {0};
    InitializeHarvestOption(&option);
    // Get harvest settings
    option.frame_period = frame_period;
    option.f0_floor = 71.0;
    // Get Samples For Harvest
    int f0_length = GetSamplesForHarvest(fs, x_length, frame_period);
    double* f0 = new double[f0_length];
    double* time_axis = new double[f0_length];
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

val CheapTrick_JS(val x_val, val f0_val, val time_axis_val, int fs, double frame_period) {
    // init val
    val ret = val::object();
    int x_length, f0_length;
    // translate array to C++ ptr
    double* x = GetPtrFrom1XArray<double>(x_val, &x_length);
    double* f0 = GetPtrFrom1XArray<double>(f0_val, &f0_length);
    double* time_axis = GetPtrFrom1XArray<double>(time_axis_val);
    // Run CheapTrick
    CheapTrickOption option = {0};
    InitializeCheapTrickOption(fs, &option);
    option.f0_floor = 71.0;
    option.fft_size = GetFFTSizeForCheapTrick(fs, &option);
    ret.set("fft_size", option.fft_size);
    double** spectrogram = new double*[f0_length];
    int specl = option.fft_size / 2 + 1;
    for (int i = 0; i < f0_length; i++) {
        spectrogram[i] = new double[specl];
    }
    CheapTrick(x, x_length, fs, time_axis, f0, f0_length, &option, spectrogram);
    ret.set("spectral", Get2XArray<double>(spectrogram, f0_length, specl));
    delete[] x;
    delete[] f0;
    delete[] time_axis;
    delete[] spectrogram;
    return ret;
}

val D4C_JS(val x_val, val f0_val, val time_axis_val, int fft_size, int fs, double frame_period) {
    // init val
    val ret = val::object();
    int x_length, f0_length;
    // translate array to C++ ptr
    double* x = GetPtrFrom1XArray<double>(x_val, &x_length);
    double* f0 = GetPtrFrom1XArray<double>(f0_val, &f0_length);
    double* time_axis = GetPtrFrom1XArray<double>(time_axis_val);
    // run D4C
    D4COption option = {0};
    InitializeD4COption(&option);
    option.threshold = 0.85;
    double** aperiodicity = new double*[f0_length];
    int specl = fft_size / 2 + 1;
    for (int i = 0; i < f0_length; ++i) {
        aperiodicity[i] = new double[specl];
    }
    D4C(x, x_length, fs, time_axis, f0, f0_length, fft_size, &option, aperiodicity);
    ret.set("aperiodicity", Get2XArray<double>(aperiodicity, f0_length, specl));
    delete[] x;
    delete[] f0;
    delete[] time_axis;
    delete[] aperiodicity;
    return ret;
}

val Synthesis_JS(val f0_val, val spectral_val, val aperiodicity_val, int fft_size, int fs, val frame_period) {
    // Synthesis Audio
    int f0_length;
    double framePeriodVal;
    framePeriodVal = frame_period.as<double>();
    double* f0 = GetPtrFrom1XArray<double>(f0_val, &f0_length);
    double** spectrogram = GetPtrFrom2XArray<double>(spectral_val);
    double** aperiodicity = GetPtrFrom2XArray<double>(aperiodicity_val);
    int y_length = static_cast<int>((f0_length - 1) * framePeriodVal / 1000.0 * fs) + 1;
    double* y = new double[y_length];
    Synthesis(f0, f0_length, spectrogram, aperiodicity, fft_size, framePeriodVal, fs, y_length, y);
    val ret = Get1XArray<double>(y, y_length);
    delete[] f0;
    delete[] spectrogram;
    delete[] aperiodicity;
    delete[] y;
    return ret;
}

val WavWrite_JS(val y_val, int fs, int nbits, string filename) {
    // init 
    int y_length;
    double* y = GetPtrFrom1XArray<double>(y_val, &y_length);
    wavwrite(y, y_length, fs, 16, filename.c_str());
    return val(y_length);
}

val Wav2World(string fileName) {
    // TODO
    // init return val
    val World = val::object();
    // Get File Name
    const char* f = fileName.c_str();
    int fs, nbit;
    // GetAudioLength for read
    int x_length = GetAudioLength(f);
    double* x = new double[x_length];
    // Use tools/audioio.cpp wavread function
    wavread(f, &fs, &nbit, x);

    return val(x);
}

//-----------------------------------------------------------------------------
// The JavaScript API for C++
//-----------------------------------------------------------------------------
EMSCRIPTEN_BINDINGS(my_module) {
    emscripten::function("DisplayInformation", &DisplayInformation);
    emscripten::function("WavRead_JS", &WavRead_JS);
    emscripten::function("Dio_JS", &Dio_JS);
    emscripten::function("Harvest_JS", &Harvest_JS);
    emscripten::function("CheapTrick_JS", &CheapTrick_JS);
    emscripten::function("D4C_JS", &D4C_JS);
    emscripten::function("Synthesis_JS", &Synthesis_JS);
    emscripten::function("WavWrite_JS", &WavWrite_JS);
    emscripten::function("Wav2World", &Wav2World);
}

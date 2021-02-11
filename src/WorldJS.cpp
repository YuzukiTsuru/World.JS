//
// Created by YuzukiTsuru on 2019/7/14.
//

#include <iostream>

#include <emscripten.h>
#include <emscripten/bind.h>

#include "WorldJS.h"
#include "WorldNativeIO.h"


EMSCRIPTEN_KEEPALIVE
void DisplayInformationVal(emscripten::val x) {
    std::cout << "File information" << std::endl;
    std::cout << "Sampling : " << x["fs"].as<int>() << " Hz " << x["nbit"].as<int>() << " Bit" << std::endl;
    std::cout << "Length " << x["x_length"].as<int>() << "[sample]" << std::endl;
    std::cout << "Length " << static_cast<double>(x["x_length"].as<int>()) / x["fs"].as<int>() << " [sec]" << std::endl;
}

EMSCRIPTEN_KEEPALIVE
emscripten::val GetInformationVal(const emscripten::val &x) {
    std::string info = "File information<br>Sampling : "
                       + std::to_string(x["fs"].as<int>())
                       + " Hz "
                       + std::to_string(x["nbit"].as<int>())
                       + " Bit"
                       + "<br>Length "
                       + std::to_string(x["x_length"].as<int>())
                       + "[sample]"
                       + "<br>Length " + std::to_string(static_cast<double>(x["x_length"].as<int>()) / x["fs"].as<int>())
                       + " [sec]";
    return emscripten::val(info);
}

EMSCRIPTEN_KEEPALIVE
emscripten::val Dio_JS(emscripten::val x_val, int fs, double frame_period) {
    // init val
    emscripten::val ret = emscripten::val::object();
    int x_length;
    // translate array to C++ ptr
    auto x = GetPtrFrom1XArray<double>(std::move(x_val), &x_length);
    if (x_length == 0) {
        emscripten_log(EM_LOG_ERROR, E01);
        EM_TERM();
    }

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
    auto f0 = new double[f0_length];
    auto time_axis = new double[f0_length];
    auto refined_f0 = new double[f0_length];
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

EMSCRIPTEN_KEEPALIVE
emscripten::val Harvest_JS(emscripten::val x_val, int fs, double frame_period) {
    // init val
    emscripten::val ret = emscripten::val::object();
    // init
    int x_length;
    // translate array to C++ ptr
    auto x = GetPtrFrom1XArray<double>(std::move(x_val), &x_length);
    if (x_length == 0) {
        emscripten_log(EM_LOG_ERROR, E01);
        EM_TERM();
    }
    // init Harvest Option
    HarvestOption option = {0};
    InitializeHarvestOption(&option);
    // Get harvest settings
    option.frame_period = frame_period;
    option.f0_floor = 71.0;
    // Get Samples For Harvest
    int f0_length = GetSamplesForHarvest(fs, x_length, frame_period);
    auto f0 = new double[f0_length];
    auto time_axis = new double[f0_length];
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

EMSCRIPTEN_KEEPALIVE
emscripten::val CheapTrick_JS(emscripten::val x_val, emscripten::val f0_val, emscripten::val time_axis_val, int fs) {
    // init val
    emscripten::val ret = emscripten::val::object();
    int x_length, f0_length;
    // translate array to C++ ptr
    auto x = GetPtrFrom1XArray<double>(std::move(x_val), &x_length);
    if (x_length == 0) {
        emscripten_log(EM_LOG_ERROR, E01);
        EM_TERM();
    }
    auto f0 = GetPtrFrom1XArray<double>(std::move(f0_val), &f0_length);
    auto time_axis = GetPtrFrom1XArray<double>(std::move(time_axis_val));
    // Run CheapTrick
    CheapTrickOption option = {0};
    InitializeCheapTrickOption(fs, &option);
    option.f0_floor = 71.0;
    option.fft_size = GetFFTSizeForCheapTrick(fs, &option);
    ret.set("fft_size", option.fft_size);
    auto spectrogram = new double *[f0_length];
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

EMSCRIPTEN_KEEPALIVE
emscripten::val D4C_JS(emscripten::val x_val, emscripten::val f0_val, emscripten::val time_axis_val, int fft_size, int fs) {
    // init val
    emscripten::val ret = emscripten::val::object();
    int x_length, f0_length;
    // translate array to C++ ptr
    auto x = GetPtrFrom1XArray<double>(std::move(x_val), &x_length);
    if (x_length == 0) {
        emscripten_log(EM_LOG_ERROR, E01);
        EM_TERM();
    }
    auto f0 = GetPtrFrom1XArray<double>(std::move(f0_val), &f0_length);
    auto time_axis = GetPtrFrom1XArray<double>(std::move(time_axis_val));
    // run D4C
    D4COption option = {0};
    InitializeD4COption(&option);
    option.threshold = 0.85;
    auto aperiodicity = new double *[f0_length];
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

EMSCRIPTEN_KEEPALIVE
emscripten::val Synthesis_JS(emscripten::val f0_val, const emscripten::val &spectral_val, const emscripten::val &aperiodicity_val, int fft_size, int fs, const emscripten::val &frame_period) {
    // Synthesis Audio
    int f0_length;
    double framePeriodVal;
    framePeriodVal = frame_period.as<double>();
    auto f0 = GetPtrFrom1XArray<double>(std::move(f0_val), &f0_length);
    double **spectrogram = GetPtrFrom2XArray<double>(spectral_val);
    double **aperiodicity = GetPtrFrom2XArray<double>(aperiodicity_val);
    int y_length = static_cast<int>((f0_length - 1) * framePeriodVal / 1000.0 * fs) + 1;
    auto y = new double[y_length];
    Synthesis(f0, f0_length, spectrogram, aperiodicity, fft_size, framePeriodVal, fs, y_length, y);
    emscripten::val ret = Get1XArray<double>(y, y_length);

    delete[] f0;
    delete[] spectrogram;
    delete[] aperiodicity;
    delete[] y;
    return ret;
}


EMSCRIPTEN_KEEPALIVE
emscripten::val W2World(const std::string &fileName) {
    // init return val
    // Get File Name
    const char *f = fileName.c_str();
    int fs, nbit;
    // GetAudioLength for read
    int x_length = GetAudioLength(f);

    if (x_length == 0) {
        emscripten_log(EM_LOG_ERROR, E01);
        EM_TERM();
    }

    auto x = new double[x_length];
    // Use tools/audioio.cpp wavread function
    wavread(f, &fs, &nbit, x);

    Wav2World wav2World(x, x_length, fs);

    emscripten::val ret = emscripten::val::object();
    ret.set("x", Get1XArray<double>(x, x_length));
    ret.set("fs", fs);
    ret.set("nbit", nbit);
    ret.set("x_length", x_length);
    ret.set("f0", Get1XArray<double>(wav2World.GetF0(), wav2World.GetF0Length()));
    ret.set("time_axis", Get1XArray<double>(wav2World.GetTimeAxis(), wav2World.GetF0Length()));
    ret.set("fft_size", wav2World.GetFFTSize());
    int specl = wav2World.GetFFTSize() / 2 + 1;
    ret.set("spectral", Get2XArray<double>(wav2World.GetSP(), wav2World.GetF0Length(), specl));
    ret.set("aperiodicity", Get2XArray<double>(wav2World.GetAP(), wav2World.GetF0Length(), specl));
    return ret;
}

//-----------------------------------------------------------------------------
// The JavaScript API for C++
//-----------------------------------------------------------------------------
EMSCRIPTEN_BINDINGS(WorldJS) {
    emscripten::function("DisplayInformation", &WorldNativeIO::DisplayInformation);
    emscripten::function("DisplayInformationVal", &DisplayInformationVal);
    emscripten::function("GetInformation", &WorldNativeIO::GetInformation);
    emscripten::function("GetInformationVal", &GetInformationVal);
    emscripten::function("WavRead_JS", &WorldNativeIO::WavRead_JS);
    emscripten::function("Dio_JS", &Dio_JS);
    emscripten::function("Harvest_JS", &Harvest_JS);
    emscripten::function("CheapTrick_JS", &CheapTrick_JS);
    emscripten::function("D4C_JS", &D4C_JS);
    emscripten::function("Synthesis_JS", &Synthesis_JS);
    emscripten::function("WavWrite_JS", &WorldNativeIO::WavWrite_JS);
    emscripten::function("Wav2World", &W2World);
}

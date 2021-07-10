//
// Created by YuzukiTsuru on 2021/2/11.
//

#include "WorldNativeFun.h"

emscripten::val WorldNativeFun::Dio_JS(emscripten::val x_val, int fs, double frame_period) {
    // init val
    emscripten::val ret = emscripten::val::object();
    int x_length;
    // translate array to C++ ptr
    auto x = GetPtrFrom1XArray<double>(std::move(x_val), &x_length);
    if (x_length == 0) {
        emscripten_log(E01);
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

emscripten::val WorldNativeFun::Harvest_JS(emscripten::val x_val, int fs, double frame_period) {
    // init val
    emscripten::val ret = emscripten::val::object();
    // init
    int x_length;
    // translate array to C++ ptr
    auto x = GetPtrFrom1XArray<double>(std::move(x_val), &x_length);
    if (x_length == 0) {
        emscripten_log(E01);
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

emscripten::val
WorldNativeFun::CheapTrick_JS(emscripten::val x_val, emscripten::val f0_val, emscripten::val time_axis_val, int fs) {
    // init val
    emscripten::val ret = emscripten::val::object();
    int x_length, f0_length;
    // translate array to C++ ptr
    auto x = GetPtrFrom1XArray<double>(std::move(x_val), &x_length);
    if (x_length == 0) {
        emscripten_log(E01);
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

emscripten::val
WorldNativeFun::D4C_JS(emscripten::val x_val, emscripten::val f0_val, emscripten::val time_axis_val, int fft_size,
                       int fs) {
    // init val
    emscripten::val ret = emscripten::val::object();
    int x_length, f0_length;
    // translate array to C++ ptr
    auto x = GetPtrFrom1XArray<double>(std::move(x_val), &x_length);
    if (x_length == 0) {
        emscripten_log(E01);
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

emscripten::val WorldNativeFun::Synthesis_JS(emscripten::val f0_val, const emscripten::val &spectral_val,
                                             const emscripten::val &aperiodicity_val, int fft_size, int fs,
                                             const emscripten::val &frame_period) {
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

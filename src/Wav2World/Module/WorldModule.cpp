//
// Created by YuzukiTsuru on 2021/1/27.
//
#include <world/dio.h>
#include <world/stonemask.h>
#include <world/cheaptrick.h>
#include <world/d4c.h>

#include "WorldModule.h"

WorldPara WorldModule::F0EstimationDio() {
    DioOption option = {0};
    InitializeDioOption(&option);

    // Modification of the option
    option.frame_period = worldPara.frame_period;

    // Valuable option.speed represents the ratio for downsampling.
    // The signal is downsampled to fs / speed Hz.
    // If you want to obtain the accurate result, speed should be set to 1.
    option.speed = 1;

    // You can set the f0_floor below world::kFloorF0.
    option.f0_floor = 40.0;
    option.allowed_range = 0.1;

    // Parameters setting and memory allocation.
    worldPara.f0_length = GetSamplesForDIO(worldPara.fs, x_length, worldPara.frame_period);
    worldPara.f0 = new double[worldPara.f0_length];
    worldPara.time_axis = new double[worldPara.f0_length];
    auto *refined_f0 = new double[worldPara.f0_length];

    Dio(x, x_length, worldPara.fs, &option, worldPara.time_axis, worldPara.f0);

    // StoneMask is carried out to improve the estimation performance.
    StoneMask(x, x_length, worldPara.fs, worldPara.time_axis, worldPara.f0, worldPara.f0_length, refined_f0);

    for (int i = 0; i < worldPara.f0_length; ++i) {
        worldPara.f0[i] = refined_f0[i];
    }

    delete[] refined_f0;

    return worldPara;
}

WorldPara WorldModule::SpectralEnvelopeEstimation() {
    CheapTrickOption option = {0};
    // Note (2017/01/02): fs is added as an argument.
    InitializeCheapTrickOption(worldPara.fs, &option);

    // Default value was modified to -0.15.
    // option.q1 = -0.15;

    // Important notice (2017/01/02)
    // You can set the fft_size.
    // Default is GetFFTSizeForCheapTrick(worldPara.fs, &option);
    // When fft_size changes from default value,
    // a replaced f0_floor will be used in CheapTrick().
    // The lowest F0 that WORLD can work as expected is determined
    // by the following : 3.0 * fs / fft_size.
    option.f0_floor = 71.0;
    option.fft_size = GetFFTSizeForCheapTrick(worldPara.fs, &option);
    // We can directly set fft_size.
//   option.fft_size = 1024;

    // Parameters setting and memory allocation.
    worldPara.fft_size = option.fft_size;
    worldPara.spectrogram = new double *[worldPara.f0_length];
    for (int i = 0; i < worldPara.f0_length; ++i) {
        worldPara.spectrogram[i] = new double[worldPara.fft_size / 2 + 1];
    }

    CheapTrick(x, x_length, worldPara.fs, worldPara.time_axis, worldPara.f0, worldPara.f0_length, &option, worldPara.spectrogram);
    return worldPara;
}

WorldPara WorldModule::AperiodicityEstimation() {
    D4COption option = {0};
    InitializeD4COption(&option);

    // Comment was modified because it was confusing (2017/12/10).
    // It is used to determine the aperiodicity in whole frequency band.
    // D4C identifies whether the frame is voiced segment even if it had an F0.
    // If the estimated value falls below the threshold,
    // the aperiodicity in whole frequency band will set to 1.0.
    // If you want to use the conventional D4C, please set the threshold to 0.0.
    option.threshold = 0.85;

    // Parameters setting and memory allocation.
    worldPara.aperiodicity = new double *[worldPara.f0_length];
    for (int i = 0; i < worldPara.f0_length; ++i) {
        worldPara.aperiodicity[i] = new double[worldPara.fft_size / 2 + 1];
    }

    D4C(x, x_length, worldPara.fs, worldPara.time_axis, worldPara.f0, worldPara.f0_length, worldPara.fft_size, &option, worldPara.aperiodicity);
    return worldPara;
}

WorldModule::WorldModule(double *x, int x_length, int fs) {
    this->x = x;
    this->x_length = x_length;
    worldPara.fs = fs;
    worldPara.frame_period = 5.0;
    F0EstimationDio();
    SpectralEnvelopeEstimation();
    AperiodicityEstimation();
}

WorldModule::~WorldModule() {
    delete[] worldPara.time_axis;
    delete[] worldPara.f0;
    for (int i = 0; i < worldPara.f0_length; ++i) {
        delete[] worldPara.spectrogram[i];
        delete[] worldPara.aperiodicity[i];
    }
    delete[] worldPara.spectrogram;
    delete[] worldPara.aperiodicity;
}

WorldPara WorldModule::GetModule() {
    return worldPara;
}

//
// Created by YuzukiTsuru on 2021/1/3.
//

#include <iostream>

#include "Wav2World.h"

Wav2World::Wav2World(double *x, int x_length, int fs) {
    WorldModule worldModule(x, x_length, fs);
    worldPara = worldModule.GetModule();
}

double *Wav2World::GetF0() const {
    return worldPara.f0;
}

double * Wav2World::GetTimeAxis() const {
    return worldPara.time_axis;
}

double **Wav2World::GetSP() const {
    return worldPara.spectrogram;
}

double **Wav2World::GetAP() const {
    return worldPara.aperiodicity;
}

int Wav2World::GetF0Length() const {
    return worldPara.f0_length;
}

int Wav2World::GetFFTSize() const {
    return worldPara.fft_size;
}


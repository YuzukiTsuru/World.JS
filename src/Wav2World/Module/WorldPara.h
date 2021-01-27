//
// Created by YuzukiTsuru on 2021/1/27.
//

#ifndef WORLDJS_WORLDPARA_H
#define WORLDJS_WORLDPARA_H

class WorldPara {
public:
    double frame_period = 0.0;
    int fs = 0;

    double *f0 = nullptr;
    double *time_axis = nullptr;
    int f0_length = 0;

    double **spectrogram = nullptr;
    double **aperiodicity = nullptr;
    int fft_size = 0;
};

#endif //WORLDJS_WORLDPARA_H

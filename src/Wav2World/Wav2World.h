//
// Created by YuzukiTsuru on 2021/1/3.
//

#ifndef WORLDJS_WAV2WORLD_H
#define WORLDJS_WAV2WORLD_H


class Wav2World {
public:
    [[maybe_unused]] Wav2World(const std::string fileName);
    Wav2World(int* x, int x_length);

    ~Wav2World();

private:


    class WorldPara {
    public:
        double frame_period;
        int fs;

        double *f0;
        double *time_axis;
        int f0_length;

        double **spectrogram;
        double **aperiodicity;
        int fft_size;
    };

protected:
    WorldPara worldPara;
};


#endif //WORLDJS_WAV2WORLD_H

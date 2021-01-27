//
// Created by YuzukiTsuru on 2021/1/27.
//

#include <iostream>

#include "Wav2World.h"
#include <audioio.h>


int main() {
    std::string file = "../test/vaiueo2d.wav";
    int x_length = GetAudioLength(file.c_str());
    if (x_length <= 0) {
        if (x_length == 0) printf("error: File not found.\n");
        else printf("error: The file is not .wav format.\n");
        return -1;
    }
    auto *x = new double[x_length];
    // wavread() must be called after GetAudioLength().
    int fs, nbit;
    wavread(file.c_str(), &fs, &nbit, x);
    Wav2World(x, x_length, fs);
    return 0;
}
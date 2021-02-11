//
// Created by YuzukiTsuru on 2021/2/5.
//

#include "WorldNativeIO.h"

void WorldNativeIO::DisplayInformation(int fs, int nbit, int x_length) {
    std::cout << "File information" << std::endl;
    std::cout << "Sampling : " << fs << " Hz " << nbit << " Bit" << std::endl;
    std::cout << "Length " << x_length << "[sample]" << std::endl;
    std::cout << "Length " << static_cast<double>(x_length) / fs << " [sec]" << std::endl;
}

emscripten::val WorldNativeIO::GetInformation(int fs, int nbit, int x_length) {
    std::string info = "File information<br>Sampling : "
                       + std::to_string(fs)
                       + " Hz "
                       + std::to_string(nbit)
                       + " Bit"
                       + "<br>Length "
                       + std::to_string(x_length)
                       + "[sample]"
                       + "<br>Length " + std::to_string(static_cast<double>(x_length) / fs)
                       + " [sec]";
    return emscripten::val(info);
}

emscripten::val WorldNativeIO::WavRead_JS(const std::string &filename) {
    // init val
    emscripten::val InWav = emscripten::val::object();
    // Get File Name
    const char *f = filename.c_str();
    int fs, nbit;
    // GetAudioLength for read
    int x_length = GetAudioLength(f);
    if (x_length == 0) {
        emscripten_log(EM_LOG_ERROR, E00);
        EM_TERM();
    }
    auto x = new double[x_length];
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

emscripten::val WorldNativeIO::WavWrite_JS(emscripten::val y_val, int fs, const std::string &filename) {
    // init
    int y_length;
    auto y = GetPtrFrom1XArray<double>(std::move(y_val), &y_length);
    wavwrite(y, y_length, fs, 16, filename.c_str());
    return emscripten::val(y_length);
}


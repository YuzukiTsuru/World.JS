//
// Created by YuzukiTsuru on 2021/2/5.
//

#include "WorldNative.h"

EMSCRIPTEN_KEEPALIVE void WorldNative::DisplayInformation(int fs, int nbit, int x_length) {
    std::cout << "File information" << std::endl;
    std::cout << "Sampling : " << fs << " Hz " << nbit << " Bit" << std::endl;
    std::cout << "Length " << x_length << "[sample]" << std::endl;
    std::cout << "Length " << static_cast<double>(x_length) / fs << " [sec]" << std::endl;
}

emscripten::val WorldNative::GetInformation(int fs, int nbit, int x_length) {
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
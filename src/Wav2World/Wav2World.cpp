//
// Created by YuzukiTsuru on 2021/1/3.
//

#include <iostream>

#include "Wav2World.h"

Wav2World::Wav2World(double *x, int x_length) {
    WorldModule worldModule(x, x_length);
    worldPara = worldModule.GetModule();
}

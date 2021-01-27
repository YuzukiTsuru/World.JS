//
// Created by YuzukiTsuru on 2021/1/3.
//

#ifndef WORLDJS_WAV2WORLD_H
#define WORLDJS_WAV2WORLD_H

#include "WorldPara.h"
#include "WorldModule.h"

class Wav2World {
public:
    Wav2World(double *x, int x_length);

private:
    WorldPara worldPara;
};


#endif //WORLDJS_WAV2WORLD_H

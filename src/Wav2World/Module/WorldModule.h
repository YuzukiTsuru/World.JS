//
// Created by YuzukiTsuru on 2021/1/27.
//

#ifndef WORLDJS_WORLDMODULE_H
#define WORLDJS_WORLDMODULE_H

#include "WorldPara.h"

class WorldModule {
public:
    WorldModule(double *x, int x_length, int fs);

    ~WorldModule();

    WorldPara GetModule();


private:
    WorldPara F0EstimationDio();

    WorldPara SpectralEnvelopeEstimation();

    WorldPara AperiodicityEstimation();

protected:
    double *x = nullptr;
    int x_length = 0;

    WorldPara worldPara;
};


#endif //WORLDJS_WORLDMODULE_H

//
// Created by YuzukiTsuru on 2021/3/4.
//

#ifndef WORLDJS_CONFIGURATION_H
#define WORLDJS_CONFIGURATION_H

#include "Config.h"

class Configuration {
public:
    Configure getConfig();

    // TODO: 增加 JS -> 配置floor，fper
    void setFramePeriod(int framePeriod);

    void setFramePeriod(double framePeriod);
};


#endif //WORLDJS_CONFIGURATION_H

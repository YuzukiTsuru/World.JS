//
// Created by YuzukiTsuru on 2021/3/4.
//

#ifndef WORLDJS_CONFIGURATION_H
#define WORLDJS_CONFIGURATION_H

#include "Config.h"

class Configuration {
public:
    Configuration(double framePeriod, double floor);

    Configure getConfig();

    // TODO: 增加 JS -> 配置floor，fper
    void setFramePeriod(int framePeriod);

    void setFramePeriod(double framePeriod);

    void setFloor(double floor);

    [[nodiscard]] double getFramePeriod() const;

    [[nodiscard]] double getFloor() const;

private:
    Configure configure;
};


#endif //WORLDJS_CONFIGURATION_H

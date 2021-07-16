//
// Created by YuzukiTsuru on 2021/3/4.
//

#include "Configuration.h"

//TODO

Configure Configuration::getConfig() {
    return configure;
}

Configuration::Configuration(double framePeriod, double floor) {
    configure.frame_period = framePeriod;
    configure.f0_floor = floor;
}


void Configuration::setFramePeriod(int framePeriod) {
    configure.frame_period = static_cast<double>(framePeriod);
}

void Configuration::setFramePeriod(double framePeriod) {
    configure.frame_period = framePeriod;
}

void Configuration::setFloor(double floor) {
    configure.f0_floor = floor;
}

double Configuration::getFramePeriod() const {
    return configure.frame_period;
}

double Configuration::getFloor() const {
    return configure.f0_floor;
}

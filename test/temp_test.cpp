//
// Created by YuzukiTsuru on 2021/1/27.
//

#include <iostream>
#include <emscripten.h>
#include <emscripten/bind.h>

using namespace emscripten;

class MyClass {
public:
    MyClass() = default;

    static void add(int a, int b) {
        printf("%d", a + b);
    };
};

EMSCRIPTEN_BINDINGS(external_constructors) {
    class_<MyClass>("MyClass")
            .constructor<>()
            .function("add", &MyClass::add);
}
//
// Created by YuzukiTsuru on 2021/1/19.
//

#pragma once

#include <emscripten/val.h>
#include <emscripten.h>

template<class Type>
emscripten::val Get1XArray(Type *arr, int len) {
    return emscripten::val(emscripten::typed_memory_view(len, arr));
}

template<class Type>
emscripten::val Get2XArray(Type **arr, int y_len, int x_len) {
    emscripten::val arr2x = emscripten::val::array();
    for (int i = 0; i < y_len; i++) {
        arr2x.set(i, Get1XArray<Type>(arr[i], x_len));
    }
    return arr2x;
}

template<class Type>
Type *GetPtrFrom1XArray(emscripten::val arr, int *len = nullptr) {
    if (len == nullptr) {
        len = new int[1];
    }
    *len = arr["length"].as<int>();

    auto *ret = new Type[*len];
    int ptr = (int) (ret) / sizeof(Type);

    emscripten::val module = emscripten::val::global("Module");
    module["HEAPF64"].call<emscripten::val>("set", arr, emscripten::val(ptr));
    return ret;
}

template<class Type>
Type **GetPtrFrom2XArray(const emscripten::val &arr, int *y_len = nullptr, int *x_len = nullptr) {
    if (y_len == nullptr) {
        y_len = new int[1];
    }
    if (x_len == nullptr) {
        x_len = new int[1];
    }

    *y_len = arr["length"].as<int>();

    emscripten::val module = emscripten::val::global("Module");
    if (*y_len > 0) {
        *x_len = arr[0]["length"].as<int>();
        Type **ret = new Type *[*y_len];
        for (int i = 0; i < *y_len; i++) {
            ret[i] = new Type[*x_len];
            int ptr = (int) (ret[i]) / sizeof(Type);
            module["HEAPF64"].call<emscripten::val>("set", arr[i], emscripten::val(ptr));
        }
        return ret;
    } else {
        *x_len = 0;
        return nullptr;
    }
}
//
// Created by YuzukiTsuru on 2021/1/27.
//

#include <iostream>
#include <emscripten.h>
#include <emscripten/bind.h>


struct Point2f {
    float x;
    float y;
};

struct PersonRecord {
    std::string name;
    int age;
};

// Array fields are treated as if they were std::array<type,size>
struct ArrayInStruct {
    int field[2];
};

PersonRecord findPersonAtLocation(Point2f) {
    return PersonRecord();
}


EMSCRIPTEN_BINDINGS(my_value_example) {
    emscripten::value_array<Point2f>("Point2f")
            .element(&Point2f::x)
            .element(&Point2f::y);

    emscripten::value_object<PersonRecord>("PersonRecord")
            .field("name", &PersonRecord::name)
            .field("age", &PersonRecord::age);

    emscripten::value_object<ArrayInStruct>("ArrayInStruct")
            .field("field", &ArrayInStruct::field) // Need to register the array type
            ;

    // Register std::array<int, 2> because ArrayInStruct::field is interpreted as such
    emscripten::value_array<std::array<int, 2>>("array_int_2")
            .element(emscripten::index<0>())
            .element(emscripten::index<1>());

    emscripten::function("findPersonAtLocation", &findPersonAtLocation);
}

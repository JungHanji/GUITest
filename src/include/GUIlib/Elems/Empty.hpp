#pragma once

#include <GUIlib/HIDhandler.hpp>
#include <AdtClasses/AdtClasses.hpp>
#include <functional>

namespace GUIlib{
    class Empty{
        public:
        string name;
        vec2 pos, size;

        Empty(string name, vec2 pos, vec2 size){
            this->name = name;
            this->pos = pos;
            this->size = size;
        }
    };
};
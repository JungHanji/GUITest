#pragma once

#include <GUIlib/HIDhandler.hpp>
#include <AdtClasses/AdtClasses.hpp>
#include <functional>

vec2 animationFastToSlow(vec2 start, vec2 end, int tickStart, int tick, float speed = 0.1, float speedFactor = 0.4){
    float way = pow((tick - tickStart) * speed, speedFactor);
    return {
        lerp(start.x, end.x, way),
        lerp(start.y, end.y, way)
    };
}

vec2 animationSlowToFast(vec2 start, vec2 end, int tickStart, int tick, float speed = 0.1, float speedFactor = 4){
    float way = pow((tick - tickStart) * speed, speedFactor);
    return {
        lerp(start.x, end.x, way),
        lerp(start.y, end.y, way)
    };
}

vec2 animationStable(vec2 start, vec2 end, int tickStart, int tick){
    float way = (tick - tickStart) * 0.1;
    return {
        lerp(start.x, end.x, way),
        lerp(start.y, end.y, way)
    };
}

class Animator{
    public:

    void newAnimation(){
        ;
    }

    Animator(){}
};
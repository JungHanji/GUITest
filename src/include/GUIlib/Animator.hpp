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

struct Animation{
    string type;
    vec2 start, end;
    int tickStart;

    vec2 update(int tick){
        if(type=="fast-to-slow"){ 
            return animationFastToSlow(start, end, tickStart, tick); 
        } else if(type=="slow-to-fast") {
            return animationSlowToFast(start, end, tickStart, tick);
        } else if(type=="stable") {
            return animationStable(start, end, tickStart, tick);
        }
    }
};

class Animator{
    public:

    vector<Animation> animations;

    void newAnimation(string type, vec2 start, vec2 end, int tickStart){
        animations.push_back({type, start, end, tickStart});
    }

    void update(){
        for(auto& animation : animations){
            ;
        }
    }

    Animator(){}
};
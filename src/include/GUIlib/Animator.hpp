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
    vec2 start, end, pos;
    int tickStart;
    bool active = true;

    void update(int tick){
        if(active){
            if(type=="fast-to-slow"){ 
                pos = animationFastToSlow(start, end, tickStart, tick); 
            } else if(type=="slow-to-fast") {
                pos = animationSlowToFast(start, end, tickStart, tick);
            } else if(type=="stable") {
                pos = animationStable(start, end, tickStart, tick);
            }
        }
    }
};

class Animator{
    public:

    vector<paar<string, Animation>> animations;

    void newAnimation(string name, string type, vec2 start, vec2 end, int tickStart){
        if(!keyInPaars(animations, name)) animations.push_back({name, {type, start, end, start, tickStart}});
        else {
            animations[paarIndexByName(animations, name)].value.type = type;
            animations[paarIndexByName(animations, name)].value.active = true;
            animations[paarIndexByName(animations, name)].value.start = start;
            animations[paarIndexByName(animations, name)].value.end = end;
            animations[paarIndexByName(animations, name)].value.tickStart = tickStart;
            animations[paarIndexByName(animations, name)].value.pos = start;
        }
    }

    void delAnimation(string name){
        for(int i = 0; i < animations.size(); i++){
            if(animations[i].key == name){
                animations.erase(animations.begin() + i);
                break;
            }
        }
    }

    bool isAnimationAlive(string name){
        for(paar<string, Animation> animation : animations){
            if(animation.key == name){
                return animation.value.active;
            }
        }
        return false;
    }

    vec2 getPosition(string name){
        return getPaarByName(animations, name).value.pos;
    }

    void update(int tick){
        for(auto& animation : animations){
            animation.value.update(tick);
            if(animation.value.pos > animation.value.end || animation.value.pos == animation.value.end){
                animation.value.active = false;
            }
        }

        for(auto &animation : animations){
            if(!animation.value.active){
                animation.value.pos = animation.value.start;
            }
        }
    }

    Animator(){}
};
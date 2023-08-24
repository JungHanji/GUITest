#pragma once

#include <GUIlib/HIDhandler.hpp>
#include <AdtClasses/AdtClasses.hpp>
#include <functional>
#include <MathLib/ColorTools.hpp>

enum AnimationMoves {
    FAST_TO_SLOW,
    SLOW_TO_FAST,
    STABLE
};
 
enum AnimationType {
    POS,
    FLOAT_LEN,
    COLOR
};

float getFastToSlowWay(int tickStart, int tick, float speed = 0.1, float speedFactor = 0.4){return pow((tick - tickStart) * speed, speedFactor);}
float getSlowToFastWay(int tickStart, int tick, float speed = 0.1, float speedFactor = 4){return pow((tick - tickStart) * speed, speedFactor);}
float getStableWay(int tickStart, int tick, float speed = 0.1){return (tick - tickStart) * speed;}

vec2 animationFastToSlow(vec2 start, vec2 end, int tickStart, int tick, float speed = 0.1, float speedFactor = 0.4){
    float way = getFastToSlowWay(tickStart, tick, speed, speedFactor);
    return {
        lerp(start.x, end.x, way),
        lerp(start.y, end.y, way)
    };
}

vec2 animationSlowToFast(vec2 start, vec2 end, int tickStart, int tick, float speed = 0.1, float speedFactor = 4){
    float way = getSlowToFastWay(tickStart, tick, speed, speedFactor);
    return {
        lerp(start.x, end.x, way),
        lerp(start.y, end.y, way)
    };
}

vec2 animationStable(vec2 start, vec2 end, int tickStart, int tick, float speed = 0.1){
    float way = getStableWay(tickStart, tick, speed);
    return {
        lerp(start.x, end.x, way),
        lerp(start.y, end.y, way)
    };
}

struct Animation{
    AnimationMoves moveType;
    AnimationType type = POS;
    vec2 start, end, pos;
    int tickStart;
    bool active = true;
    float fstart, fend, fpos;
    vec3 cstart, cend, cpos;

    Animation(vec2 start, vec2 end, int tickStart, AnimationMoves moveType){
        this->start = start;
        this->end = end;
        this->tickStart = tickStart;
        this->moveType = moveType;
        this->type = POS;
    }

    Animation(vec3 start, vec3 end, int tickStart, AnimationMoves moveType){
        this->cstart = start;
        this->cend = end;
        this->tickStart = tickStart;
        this->moveType = moveType;
        this->type = COLOR;
    }

    Animation(float start, float end, int tickStart, AnimationMoves moveType){
        this->fstart = start;
        this->fend = end;
        this->tickStart = tickStart;
        this->moveType = moveType;
        this->type = FLOAT_LEN;
    }

    Animation(){}

    void update(int tick){
        if(!active) return;
        
        switch (moveType)
        {
            case FAST_TO_SLOW: {
                if(type==POS) pos = animationFastToSlow(start, end, tickStart, tick); 
                else if(type == FLOAT_LEN) fpos = animationFastToSlow({fstart, fstart}, {fend, fend}, tickStart, tick).x;
                else if(type == COLOR) cpos = gradient(cstart, cend, getFastToSlowWay(tickStart, tick));
                break;
            }
            
            case SLOW_TO_FAST: {
                if(type==POS) pos = animationSlowToFast(start, end, tickStart, tick); 
                else if(type == FLOAT_LEN) fpos = animationSlowToFast({fstart, fstart}, {fend, fend}, tickStart, tick).x;
                else if(type == COLOR) cpos = gradient(cstart, cend, getSlowToFastWay(tickStart, tick));
                break;
            }
            
            case STABLE: {
                if(type==POS) pos = animationStable(start, end, tickStart, tick); 
                else if(type == FLOAT_LEN) fpos = animationStable({fstart, fstart}, {fend, fend}, tickStart, tick).x;
                else if(type == COLOR) cpos = gradient(cstart, cend, getStableWay(tickStart, tick));
                break;
            }
        }
    }
};

class Animator{
    public:

    vector<paar<string, Animation>> animations;

    void newAnimation(string name, AnimationMoves moveType, vec2 start, vec2 end, int tickStart){
        if(!keyInPaars(animations, name)) animations.push_back({name, {start, end, tickStart, moveType}});
        else {
            animations[paarIndexByName(animations, name)].value.moveType = moveType;
            animations[paarIndexByName(animations, name)].value.active = true;
            animations[paarIndexByName(animations, name)].value.start = start;
            animations[paarIndexByName(animations, name)].value.end = end;
            animations[paarIndexByName(animations, name)].value.tickStart = tickStart;
            animations[paarIndexByName(animations, name)].value.pos = start;
        }
    }

    void newAnimation(string name, AnimationMoves moveType, float start, float end, int tickStart){
        if(!keyInPaars(animations, name)) animations.push_back({name, {start, end, tickStart, moveType}});
        else {
            animations[paarIndexByName(animations, name)].value.moveType = moveType;
            animations[paarIndexByName(animations, name)].value.active = true;
            animations[paarIndexByName(animations, name)].value.fstart = start;
            animations[paarIndexByName(animations, name)].value.fend = end;
            animations[paarIndexByName(animations, name)].value.tickStart = tickStart;
            animations[paarIndexByName(animations, name)].value.fpos = start;
        }
    }

    void newAnimation(string name, AnimationMoves moveType, vec3 start, vec3 end, int tickStart){
        if(!keyInPaars(animations, name)) animations.push_back({name, {start, end, tickStart, moveType}});
        else {
            animations[paarIndexByName(animations, name)].value.moveType = moveType;
            animations[paarIndexByName(animations, name)].value.active = true;
            animations[paarIndexByName(animations, name)].value.cstart = start;
            animations[paarIndexByName(animations, name)].value.cend = end;
            animations[paarIndexByName(animations, name)].value.tickStart = tickStart;
            animations[paarIndexByName(animations, name)].value.cpos = start;
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

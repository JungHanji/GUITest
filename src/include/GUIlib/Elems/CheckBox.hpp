#pragma once

#include <GUIlib/HIDhandler.hpp>
#include <AdtClasses/AdtClasses.hpp>
#include <functional>

namespace GUIlib{

    class CheckBox{
        public:

        string name;
        vec2 pos, size;
        vec3 bgColor, activeColor;
        float activeOffset = 5;
        bool active = false;
        
        Button btn;
        RectangleShape bgRect, activeRect;
        function<void(CheckBox*, bool)> onClick;

        CheckBox(string name, vec2 pos, vec2 size, vec3 bgColor, vec3 activeColor, float activeOffset = 5) : name(name), pos(pos), size(size), bgColor(bgColor), activeColor(activeColor), activeOffset(activeOffset){
            btn.pos = pos;
            btn.size = size;
            btn.visible = false;
        
            bgRect = RectangleShape({size.x, size.y});
            bgRect.setFillColor({bgColor.x, bgColor.y, bgColor.z});
            activeRect = RectangleShape({size.x - activeOffset*2, size.y - activeOffset*2});
            activeRect.setFillColor({activeColor.x, activeColor.y, activeColor.z});
        }

        void update(RenderWindow &window, MouseData &mdata){
            bgRect.setPosition({pos.x, pos.y});
            activeRect.setPosition({pos.x + activeOffset, pos.y + activeOffset});
            window.draw(bgRect);
            bool temp = active;
            if(!active){
                active = btn.isClicked(getMousePos(window), 0, mdata);
            } else {
                active = !btn.isClicked(getMousePos(window), 0, mdata);
            }
            if(temp!= active && onClick) onClick(this, active);
            if(active) window.draw(activeRect);
        }

        bool operator==(CheckBox other){
            return name==other.name;
        }

        CheckBox(){
            ;
        }
    };

}
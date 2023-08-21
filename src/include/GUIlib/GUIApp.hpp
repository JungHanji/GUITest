#include "AllGUIelems.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using namespace GUIlib;

class GUIApp{
    public:

    string name;
    vec2 res;
    vec3 bgColor;

    KeyboardData kData;
    MouseData mData; 
    int tick = 0;

    Layer mainlayer = Layer("mainlayer");

    function<void(GUIApp*)> updateFunction;
    Animator animator;

    GUIApp(string name_, vec2 res_, vec3 bgColor_){
        name = name_;
        res = res_;
        bgColor = bgColor_;
    }

    void newAnimation(string name, AnimationType type, vec2 start, vec2 end, int tickStart){
        animator.newAnimation(name, type, start, end, tickStart);
    }

    void delAnimation(string name){
        animator.delAnimation(name);
    }

    Layer &addLayer(string name){
        return mainlayer.addLayer(name);
    }

    Layer &getLayer(string name){
        return mainlayer.getLayer(name);
    }

    void setUpdateFunction(function<void(GUIApp*)> updateFunction_){
        updateFunction = updateFunction_;
    }

    void update(RenderWindow &window, bool fullControl = false){
        if(fullControl){
            Event event;
            mData.clear();
            kData.clear();
            kData.typed = false;
            kData.unicode = -1;
            mData.wheelData = 0;       
            while (window.pollEvent(event)){
                switch (event.type){
                    case Event::Closed:
                        {window.close();}
                        break;
                    case Event::KeyPressed:
                        {kData.pressedKeys.push_back(event.key.code);}
                        break;
                    case Event::MouseButtonPressed:
                        {mData.pressedButtons[(int)(event.mouseButton.button)] = true;}
                        break;
                    case Event::TextEntered:
                        {Uint32 unicode = event.text.unicode;
                        if((unicode >= 32 && unicode <= 126) || (unicode >= 1040 && unicode <= 1103)){
                            kData.charkey = (char)unicode;
                            kData.typed = true;
                        }
                        kData.unicode = unicode;
                        if(kData.unicode == 13) kData.typed = true;}
                        break;
                    case Event::MouseWheelMoved:
                        {mData.wheelData = event.mouseWheel.delta;}
                        break;
                }
            }

            window.clear({bgColor.x, bgColor.y, bgColor.z});
            animator.update(tick);
            if(updateFunction){
                updateFunction(this);
            }
            
            mainlayer.update(window, mData, kData, tick);
            window.display();
            tick++;
        }
    }

    GUIApp(){}
};
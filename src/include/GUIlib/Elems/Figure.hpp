#pragma once

#include <GUIlib/HIDhandler.hpp>
#include <AdtClasses/AdtClasses.hpp>
#include <functional>

namespace GUIlib{

    class Figure{
        public:

        string name, type; 
        vec2 pos, size, point2;
        vec3 color;

        vec2 globalPadding = vec2(0, 0);
        RectangleShape rect;
        CircleShape circle, circle2, circle3, circle4;

        int radius;
        float smoothnes = 5.f, transparency = 255;

        Figure(string name, string type, vec2 pos, vec2 size, vec3 color){
            this->name = name;
            this->type = type;
            this->pos = pos;
            this->size = size;
            this->color = color;
        }

        void setRadius(int radius){
            this->radius = radius;
        }

        void setPoint2(vec2 point2){
            this->point2 = point2;
        }

        void setSmoothnes(float v){
            this->smoothnes = v;
        }

        void draw(RenderWindow& window){
            if(type == "rectangle") {
                rect.setSize({size.x, size.y});
                rect.setPosition({pos.x, pos.y});
                rect.setFillColor({color.x, color.y, color.z, transparency});
                window.draw(rect);
            } else if(type == "circle") {
                circle.setRadius(radius);
                circle.setPosition({pos.x, pos.y});
                circle.setFillColor({color.x, color.y, color.z, transparency});
                window.draw(circle);
            } else if(type == "line") {
                Vertex line[] =
                {
                    Vertex({pos.x, pos.y}, {color.x, color.y, color.z, transparency}),
                    Vertex({point2.x, point2.y}, {color.x, color.y, color.z, transparency})
                };

                window.draw(line, 2, Lines);
            } else if(type == "circled-line"){
                rect.setSize({size.x, size.y});
                rect.setPosition({pos.x, pos.y});
                rect.setFillColor({color.x, color.y, color.z, transparency});

                circle.setRadius(size.y/2);
                circle2.setRadius(size.y/2);
                circle.setFillColor({color.x, color.y, color.z, transparency});
                circle2.setFillColor({color.x, color.y, color.z, transparency});

                circle.setPosition({pos.x-size.y/2, pos.y});
                circle2.setPosition({pos.x+size.x+size.y/2, pos.y});

                window.draw(circle);
                window.draw(circle2);
                window.draw(rect);

            } else if(type == "circled-rectangle"){
                rect.setSize({size.x, size.y});
                rect.setPosition({pos.x, pos.y});
                rect.setFillColor({color.x, color.y, color.z, transparency});

                circle.setRadius(smoothnes);
                circle2.setRadius(smoothnes);
                circle3.setRadius(smoothnes);
                circle4.setRadius(smoothnes);
                circle.setFillColor({color.x, color.y, color.z, transparency});
                circle2.setFillColor({color.x, color.y, color.z, transparency});
                circle3.setFillColor({color.x, color.y, color.z, transparency});
                circle4.setFillColor({color.x, color.y, color.z, transparency});

                circle.setPosition({pos.x-smoothnes, pos.y});
                circle2.setPosition({pos.x+size.x-smoothnes, pos.y});
                circle3.setPosition({pos.x-smoothnes, pos.y + size.y-smoothnes*2});
                circle4.setPosition({pos.x+size.x-smoothnes, pos.y + size.y-smoothnes*2});

                window.draw(circle);
                window.draw(circle2);
                window.draw(circle3);
                window.draw(circle4);
                window.draw(rect);

                rect.setSize({size.x+smoothnes*2, size.y-smoothnes*2});
                rect.setPosition({pos.x-smoothnes, pos.y+smoothnes});
                window.draw(rect);
            }
        }

        bool operator==(const Figure &other) const {
            return name == other.name;
        }

        Figure(){
            ;
        }
    };

}
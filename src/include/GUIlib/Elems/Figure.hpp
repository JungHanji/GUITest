#pragma once

#include <GUIlib/HIDhandler.hpp>
#include <AdtClasses/AdtClasses.hpp>
#include <functional>
#include "RoundedRectangle.hpp"
#include <MathLib/ColorTools.hpp>

namespace GUIlib{

    class Figure{
        public:

        string name, type; 
        vec2 pos, size, point2;
        vec2 *psize, *ppos;
        vec3 color;

        vec2 globalPadding = vec2(0, 0);
        RectangleShape rect;
        CircleShape circle, circle2;
        RoundedRectangle rrect;
        GUIlib::Image texture;

        sf::BlendMode bl;

        int radius;
        float smoothnes = 5.f, transparency = 255;
        vector<vec3> gradients;
        bool useTexture = false, useGradient = false;

        Vertex *gradientRect;
        RenderTexture *rendTexture;

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

        void setImage(GUIlib::Image texture){
            this->texture = texture;
            useTexture = true;
        }

        void setGradientRect(){
            if(type=="rectangle"){
                gradientRect = new Vertex[4]{
                    Vertex({pos.x, pos.y}, {gradients[0].x, gradients[0].y, gradients[0].z, transparency}),
                    Vertex({pos.x + size.x, pos.y}, {getLast(gradients).x, getLast(gradients).y, getLast(gradients).z, transparency}),
                    Vertex({pos.x + size.x, pos.y + size.y}, {getLast(gradients).x, getLast(gradients).y, getLast(gradients).z, transparency}),
                    Vertex({pos.x, pos.y + size.y}, {gradients[0].x, gradients[0].y, gradients[0].z, transparency}),
                };
            } else {
                gradientRect = new Vertex[4]{
                    Vertex({0, 0}, {gradients[0].x, gradients[0].y, gradients[0].z, transparency}),
                    Vertex({size.x, 0}, {getLast(gradients).x, getLast(gradients).y, getLast(gradients).z, transparency}),
                    Vertex({size.x, size.y}, {getLast(gradients).x, getLast(gradients).y, getLast(gradients).z, transparency}),
                    Vertex({0, size.y}, {gradients[0].x, gradients[0].y, gradients[0].z, transparency}),
                };
            }
            useGradient = true;
            if(type=="circled-rectangle"){
                rendTexture = new RenderTexture();
                rendTexture->create(size.x, size.y);
                rendTexture->draw(gradientRect, 4, Quads);
                rendTexture->display();
            }
        }

        void draw(RenderWindow& window){
            if(type == "rectangle") {
                if(!useGradient){
                    if(useTexture) rect.setTexture(texture.tex_sprite.getTexture());
                    rect.setSize({size.x, size.y});
                    rect.setPosition({pos.x, pos.y});
                    rect.setFillColor({color.x, color.y, color.z, transparency});
                    window.draw(rect);
                } else {
                    window.draw(gradientRect, 4, Quads);
                }
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
            } else if(type == "circled-rectangle"){
                rrect = {sf::FloatRect(pos.x, pos.y , size.x, size.y), smoothnes};  
                if(useTexture) rrect.setTexture(texture.tex_sprite.getTexture());
                if(useGradient) rrect.setTexture(&(rendTexture->getTexture()));
                //rrect.setFillColor({color.x, color.y, color.z, transparency});      
                window.draw(rrect);                                                 
            } else {
                cout<<"No such figure. '"<<type<<"'\n";
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
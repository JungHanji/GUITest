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

        void setGradientRect(vector<vec3> gradients){
            this->gradients = gradients;
                
            rendTexture = new RenderTexture();
            rendTexture->create(size.x, size.y);
            
            for(int i = 0; i < gradients.size()-2; i++){
                gradientRect = new Vertex[4]{
                    Vertex({size.x / (gradients.size()-1) * i, 0}, {gradients[i].x, gradients[i].y, gradients[i].z, transparency}),
                    Vertex({size.x / (gradients.size()-1) * (i+1), 0}, {gradients[i+1].x, gradients[i+1].y, gradients[i+1].z, transparency}),
                    Vertex({size.x / (gradients.size()-1) * (i+1), size.y}, {gradients[i+1].x, gradients[i+1].y, gradients[i+1].z, transparency}),
                    Vertex({size.x / (gradients.size()-1) * i, size.y}, {gradients[i].x, gradients[i].y, gradients[i].z, transparency}),
                };
                rendTexture->draw(gradientRect, 4, Quads);
                rendTexture->display();
            }

            gradientRect = new Vertex[4]{
                Vertex({(gradients.size() > 2) ? size.x / (gradients.size()-1) * (gradients.size()-2) : 0, 0}, {gradients[gradients.size()-2].x, gradients[gradients.size()-2].y, gradients[gradients.size()-2].z, transparency}),
                Vertex({size.x, 0}, {gradients[gradients.size()-1].x, gradients[gradients.size()-1].y, gradients[gradients.size()-1].z, transparency}),
                Vertex({size.x, size.y}, {gradients[gradients.size()-1].x, gradients[gradients.size()-1].y, gradients[gradients.size()-1].z, transparency}),
                Vertex({(gradients.size() > 2) ? size.x / (gradients.size()-1) * (gradients.size()-2) : 0, size.y}, {gradients[gradients.size()-2].x, gradients[gradients.size()-2].y, gradients[gradients.size()-2].z, transparency}),
            };

            rendTexture->draw(gradientRect, 4, Quads);
            rendTexture->display();
            
            useGradient = true;
        }

        void draw(RenderWindow& window){
            if(type == "rectangle") {
                if(useTexture) rect.setTexture(texture.tex_sprite.getTexture());
                rect.setSize({size.x, size.y});
                rect.setPosition({pos.x, pos.y});
                rect.setFillColor({color.x, color.y, color.z, transparency});
                if(useGradient) rect.setTexture(&(rendTexture->getTexture()));
                window.draw(rect);
            } else if(type == "circle") {
                circle.setRadius(radius);
                circle.setPosition({pos.x, pos.y});
                circle.setFillColor({color.x, color.y, color.z, transparency});
                if(useGradient) circle.setTexture(&(rendTexture->getTexture()));
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
                rrect.setFillColor({color.x, color.y, color.z, transparency});      
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
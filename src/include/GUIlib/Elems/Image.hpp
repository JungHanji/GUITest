#pragma once

#include <GUIlib/HIDhandler.hpp>
#include <AdtClasses/AdtClasses.hpp>
#include <functional>

namespace GUIlib{

    class Image{
        public:

        sf::Image image;
        Texture texture;
        Sprite tex_sprite;
        RectangleShape rect;

        vec2 size, pos, textRectPos, textRectSize;
        vec2 *psize, *ppos;
        vec3 color;

        vec2 globalPadding = vec2(0, 0);

        string name;
        float transparency = 255;
        bool initilized = false;

        Image(string name_, string fileName, vec2 pos_, vec2 size_, vec3 color_ = vec3(255,255,255)){
            name = name_;
            size = size_;
            color = color_;
            pos = pos_;
            
            //rect.setSize({size.x, size.y});
            //rect.setFillColor(sf::Color(color.x, color.y, color.z, transparency));
            update(fileName);
        }

        void update(string fileName, vec2 trp = vec2(-1, -1), vec2 trs = vec2(-1, -1)){
            textRectPos = trp;
            textRectSize = trs;
            
            image.loadFromFile(fileName);
            texture.loadFromImage(image);
            tex_sprite.setTexture(texture, true);
            tex_sprite.setPosition({pos.x, pos.y});
            tex_sprite.setColor(sf::Color(color.x, color.y, color.z, transparency));
            tex_sprite.setScale({size.x / texture.getSize().x, size.y / texture.getSize().y});
            //tex_sprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
            //else tex_sprite.setTextureRect(sf::IntRect(textRectPos.x, textRectPos.y, textRectSize.x, textRectSize.y));
        }

        void setSize(vec2 size){
            this->size = size;
            tex_sprite.setScale({size.x / texture.getSize().x, size.y / texture.getSize().y});
        }

        void draw(sf::RenderWindow &window){
            if(!initilized){
                tex_sprite.setTexture(texture, true);
                initilized = true;
            }
            window.draw(tex_sprite);
        }

        bool operator==(const Image &other) const {
            return name == other.name;
        }

        Image(){
            ;
        }
    };

}
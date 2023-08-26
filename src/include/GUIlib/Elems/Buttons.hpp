#pragma once

#include <GUIlib/HIDhandler.hpp>
#include <AdtClasses/AdtClasses.hpp>
#include <functional>

namespace GUIlib{

    class Button{
        public:

        vec2 size, pos;
        vec3 color, clickColor, holdColor, hoverColor, textColor = vec3(255, 255, 255);
        wstring textString;
        string fontString;

        sf::Image image;
        Texture texture;
        bool imageLoaded = false;
        int fontSize;
        string name;
        bool visible = true, switchable = false;
        bool b_clicked = false, b_held = false, b_hovered = false, usingFigure = false;

        vec2 globalPadding = vec2(0, 0);

        using CallbackType = std::function<void(Button*)>;
        CallbackType onClick, onHold, onHover;

        Figure figure;

        Button(string name_, vec2 size_, vec2 pos_, vec3 color_){
            size = size_;
            pos = pos_;
            color = color_;
            name = name_;
        }

        Button(string name_, vec2 size_, vec2 pos_, vec3 color_, vec3 clickColor_, vec3 holdColor_, vec3 hoverColor_){
            size = size_;
            pos = pos_;
            color = color_;
            clickColor = clickColor_;
            holdColor = holdColor_;
            hoverColor = hoverColor_;
            name = name_;
        }

        Button(string name_, vec2 size_, vec2 pos_, wstring text_, string font_, vec3 texColor_, vec3 color_, vec3 clickColor_, vec3 holdColor_, vec3 hoverColor_, int fontSize_ = 20){
            size = size_;
            pos = pos_;
            color = color_;
            clickColor = clickColor_;
            holdColor = holdColor_;
            textString = text_;
            fontString = font_;
            textColor = texColor_;
            hoverColor = hoverColor_;
            name = name_;

            fontSize = fontSize_;

            if(!font.loadFromFile(fontString)){
                cout << "Failed to load font" << endl;
            }

            text.setString(textString);
            text.setCharacterSize(fontSize_);
            text.setFillColor({textColor.x, textColor.y, textColor.z});
        }

        void setFigure(Figure f){
            figure = f;
            usingFigure = true;
            figure.pos = pos;
            figure.size = size;
        }

        void setImage(string path){
            image.loadFromFile(path);
            imageLoaded = true;

            texture.loadFromImage(image);
        }

        void updateText(wstring text_){
            textString = text_;
            text.setString(textString);
        }

        void updateFont(string font_){
            fontString = font_;
            font.loadFromFile(fontString);
            text.setFont(font);
        }

        void addText(wstring textString_, string fontString, vec3 textColor, int fontSize_ = 20){
            fontSize = fontSize_;
            textString = textString_;
            font.loadFromFile(fontString);
            text.setString(textString_);
            text.setCharacterSize(fontSize);
            text.setFillColor({textColor.x, textColor.y, textColor.z});
        }  

        //onClick onHold onHover
        void setCallback(CallbackType callback_, string type){
            if(type == "onClick"){
                onClick = callback_;
            } else if(type == "onHold"){
                onHold = callback_;
            } else if(type == "onHover"){
                onHover = callback_;
            }
        }

        void setStyle(sf::Text::Style style_){ text.setStyle(style_); }

        bool isHovered(vec2 point) {
            return (point.x >= pos.x && point.x <= pos.x + size.x && point.y >= pos.y && point.y <= pos.y + size.y);
        }

        bool isHolded(vec2 point, int ind){ 
            if(!b_held) b_held = isHovered(point) && isButtonPressed(ind);
            if(!isHovered(point) && !isButtonPressed(ind)) b_held = false;
            return b_held; 
        }

        bool isClicked(vec2 point, int ind, MouseData &mdata){
            b_clicked = isHovered(point) && mdata.pressedButtons[ind];
            return b_clicked;
        }

        bool isClickedOutside(vec2 point, int ind, MouseData &mdata){
            if(!isHovered(point) && mdata.pressedButtons[ind]) return true;
            return false;
        }

        void draw(RenderWindow &window, MouseData &mdata, int tick){
            if(tick == 0) Init();
            
            if(visible){
                if(imageLoaded) rect.setTexture(&texture);
                else {rect.setFillColor({color.x, color.y, color.z}); figure.color = color;}
                rect.setPosition({pos.x, pos.y});
            }

            if(isHovered(getMousePos(window))){rect.setFillColor({hoverColor.x, hoverColor.y, hoverColor.z}); figure.color = hoverColor;}
            if(isHolded(getMousePos(window), 0)){rect.setFillColor({holdColor.x, holdColor.y, holdColor.z}); figure.color = holdColor;}
            if(isClicked(getMousePos(window), 0, mdata)){
                if (onClick) {
                    onClick(this);
                }
                rect.setFillColor({clickColor.x, clickColor.y, clickColor.z});  
                figure.color = clickColor;
            }
            
            if(textString!= ""){ text.setPosition({pos.x + size.x / 2 - text.getLocalBounds().width / 2, pos.y + text.getLocalBounds().height/2}); }
            if(visible){
                if(!usingFigure) window.draw(rect);
                else figure.draw(window);
                window.draw(text);
            }
        }

        Button(){}

        bool operator==(const Button &other) const {
            return name == other.name;
        }

        private:
        sf::Font font;
        sf::Text text;
        RectangleShape rect;

        void Init(){
            text.setFont(font);
            rect = RectangleShape({size.x, size.y}); //size
        }
    };

}
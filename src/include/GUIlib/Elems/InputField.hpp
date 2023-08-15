#pragma once

#include <GUIlib/HIDhandler.hpp>
#include <AdtClasses/AdtClasses.hpp>
#include <functional>

namespace GUIlib{

    class InputField{
        public:

        GUIlib::Text ttext;
        Button btn;
        wstring stext, startText;
        string name;

        Figure figure;

        vec2 globalPadding = vec2(0, 0);

        bool inFocus = false, isMultiLine = false, startTextChanged = false, usingFigure = false;
        vec2 textSize, padding;
        vec3 startTextColor, textColor;

        function<char(InputField*, char)> charHandler;

        InputField(string name, wstring startText, GUIlib::Text text, vec2 size, vec2 textSize, vec2 padding_, vec3 startTextColor, bool isMultiLine = false){
            this->name = name;
            this->isMultiLine = isMultiLine;
            this->padding = padding_;
            this->startTextColor = startTextColor;
            textColor = text.textColor;
            this->textSize = textSize;
            this->startText = startText;

            stext = " " + startText;
            ttext = text;

            ttext.padding = padding;
            ttext.enabledLines = isMultiLine;
            if(!isMultiLine){
                ttext.changeText(stext);
            } else {
                ttext.addLine(stext);
            }

            btn.pos = {ttext.pos.x, ttext.pos.y};
            btn.size = size;
            
        }

        void setCharHandler(function<char(InputField*, char)> charHandler){
            this->charHandler = charHandler;
        }

        void setTextType(int type){
            ttext.typeTextPosition = type;
        }

        void setFigure(Figure f){
            figure = f;
            figure.pos = btn.pos;
            figure.size = btn.size;
            usingFigure = true;
        }

        void setText(wstring newText){
            if(!isMultiLine) {ttext.changeText(newText); stext = newText;}
            if(isMultiLine)  {ttext.changeLine(0, newText); stext = newText;ttext.lines = vector<wstring>(); ttext.linesSF = vector<sf::Text>();}
        }

        void setButton(vec2 size){
            btn.size = size;
        }

        void update(RenderWindow& window, MouseData &mdata, KeyboardData &kdata, int tick){
            if(!inFocus) inFocus = btn.isClicked(getMousePos(window), 0, mdata);
            else inFocus = !btn.isClickedOutside(getMousePos(window), 0, mdata);

            if(usingFigure) figure.draw(window);

            if(inFocus){
                ttext.backgroundColor = {255, 0, 255};
                if(kdata.typed == true){
                    if(!startTextChanged) setText(L" ");
                    startTextChanged = true;
                    if(!isMultiLine && stext.size() < textSize.x){
                        if(!charHandler) stext += kdata.charkey;
                        else stext += charHandler(this, kdata.charkey);
                        ttext.changeText(stext);
                    } else {
                        if(ttext.lines.size() < textSize.y && kdata.unicode == 13) {
                            ttext.addLine(L" ");
                        } else if(ttext.getLine(-1).size() < textSize.x) {
                            if(!charHandler) ttext.changeLine(-1, ttext.getLine(-1) + kdata.charkey);
                            else ttext.changeLine(-1, ttext.getLine(-1) + charHandler(this, kdata.charkey));
                        }
                    }
                }
            } else {
                ttext.backgroundColor = {100, 0, 100};
            }

            if(inFocus && in(kdata.pressedKeys, sf::Keyboard::BackSpace)){
                if(!startTextChanged) setText(L" ");
                startTextChanged = true;
                if(!isMultiLine){
                    if(stext.size() != 0) stext = stext.substr(0, stext.size()-1);
                    ttext.changeText(stext);
                } else {
                    if(ttext.getLine(-1).size() >1) ttext.changeLine(-1, ttext.getLine(-1).substr(0, ttext.getLine(-1).size()-1));
                    if(ttext.lines.size() != 0 && ttext.getLine(-1).size() == 0) ttext.removeLine(-1);
                }
            }

            if(!inFocus && startTextChanged && stext == L" "){
                startTextChanged = false;
                stext = " " + startText;
                if(!startTextChanged && !isMultiLine) {ttext.changeText(stext);}
                if(!startTextChanged && isMultiLine)  {ttext.changeLine(0, stext);}
            }

            if(!startTextChanged) ttext.sftext.setColor({startTextColor.x, startTextColor.y, startTextColor.z});
            else ttext.sftext.setColor({textColor.x, textColor.y, textColor.z});

            ttext.draw(window, tick);
        }

        bool operator==(const InputField& other) const{
            return stext == other.stext && name == other.name;
        }

        InputField(){}
    };

}
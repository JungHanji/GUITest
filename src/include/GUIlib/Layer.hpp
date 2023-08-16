#pragma once

#include <GUIlib/HIDhandler.hpp>
#include <AdtClasses/AdtClasses.hpp>
#include <functional>
#include <GUIlib/AllGUIelems.hpp>

namespace GUIlib{

    class Layer{
        public:

        string name;
        vec2 pos;

        vector<paar<string, Button>> dButtons;
        vector<paar<string, Figure>> dFigures;
        vector<paar<string, GUIlib::Text>> dTexts;
        vector<paar<string, GUIlib::Image>> dImages;
        vector<paar<string, Slider>> dSliders;
        vector<paar<string, InputField>> dInputFields;
        vector<paar<string, CheckBox>> dCheckboxes;
        vector<paar<string, Layer>> dLayers;

        Layer(string name): name(name){}

        void addButton(Button button){dButtons.push_back(paar<string, Button>(button.name, button));}
        void addFigure(Figure figure){dFigures.push_back(paar<string, Figure>(figure.name, figure));}
        void addText(GUIlib::Text text){dTexts.push_back(paar<string, GUIlib::Text>(text.name, text));}
        void addImage(GUIlib::Image image){dImages.push_back(paar<string, GUIlib::Image>(image.name, image));}
        void addSlider(Slider slider){dSliders.push_back(paar<string, Slider>(slider.name, slider));}
        void addInputField(InputField inputField){dInputFields.push_back(paar<string, InputField>(inputField.name, inputField));}
        void addLayer(string name){dLayers.push_back(paar<string, Layer>(name, Layer(name)));}

        Button& getButton(string name){return dButtons[paarIndex(dButtons, getPaarByName(dButtons, name))].value;}
        Figure& getFigure(string name){return dFigures[paarIndex(dFigures, getPaarByName(dFigures, name))].value;}
        GUIlib::Text& getText(string name){return dTexts[paarIndex(dTexts, getPaarByName(dTexts, name))].value;}
        GUIlib::Image& getImage(string name){return dImages[paarIndex(dImages, getPaarByName(dImages, name))].value;}
        Slider& getSlider(string name){return dSliders[paarIndex(dSliders, getPaarByName(dSliders, name))].value;}
        InputField& getInputField(string name){return dInputFields[paarIndex(dInputFields, getPaarByName(dInputFields, name))].value;}
        Layer& getLayer(string name){return dLayers[paarIndex(dLayers, getPaarByName(dLayers, name))].value;}

        vec2 globalPadding = vec2(0, 0);

        void changePos(vec2 newPos){pos = newPos;}

        void update(RenderWindow& window, MouseData &mData, KeyboardData &kData, int tick){
            
            for(auto &figure : dFigures) figure.get().draw(window);
            for(auto &image : dImages) image.get().draw(window);
            for(auto &text : dTexts) text.get().draw(window, tick);
            for(auto &inputField : dInputFields) inputField.get().update(window, mData, kData, tick);
            for(auto &button : dButtons) button.get().draw(window, mData, tick);
            for(auto &slider : dSliders) slider.get().draw(window, mData);
            for(auto &layer : dLayers) layer.get().update(window, mData, kData, tick);
        }

        bool operator==(const Layer& other){
            return name == other.name;
        }

        Layer(){
            ;
        }
    };

}
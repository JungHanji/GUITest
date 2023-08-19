#pragma once

#include <GUIlib/HIDhandler.hpp>
#include <AdtClasses/AdtClasses.hpp>
#include <functional>
#include "Linker.hpp"

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
        //vector<paar<string, Link<Empty, Container>>> dLinks;
        vector<paar<string, Empty>> dEmptys;

        dict<string, Link<Empty, Button>> LinksButtons;
        dict<string, Link<Empty, Figure>> LinksFigures;
        dict<string, Link<Empty, GUIlib::Text>> LinksTexts;
        dict<string, Link<Empty, GUIlib::Image>> LinksImages;
        dict<string, Link<Empty, Slider>> LinksSliders;
        dict<string, Link<Empty, InputField>> LinksInputFields;
        dict<string, Link<Empty, CheckBox>> LinksCheckboxes;
        dict<string, Link<Empty, Layer>> LinksLayers;
        dict<string, Link<Empty, Empty>> LinksEmptys;

        Layer(string name): name(name){}

        void addButton(Button button){dButtons.push_back(paar<string, Button>(button.name, button));}
        void addFigure(Figure figure){dFigures.push_back(paar<string, Figure>(figure.name, figure));}
        void addText(GUIlib::Text text){dTexts.push_back(paar<string, GUIlib::Text>(text.name, text));}
        void addImage(GUIlib::Image image){dImages.push_back(paar<string, GUIlib::Image>(image.name, image));}
        void addSlider(Slider slider){dSliders.push_back(paar<string, Slider>(slider.name, slider));}
        void addInputField(InputField inputField){dInputFields.push_back(paar<string, InputField>(inputField.name, inputField));}
        void addLayer(string name){dLayers.push_back(paar<string, Layer>(name, Layer(name)));}
        //void addContainerLink(Link<Empty, Container> link){dLinks.push_back(paar<string, Link<Empty, Container>>(link.name, link));}
        void addEmpty(Empty empty){dEmptys.push_back(paar<string, Empty>(empty.name, empty));}
        void addCheckBox(CheckBox checkbox){dCheckboxes.push_back(paar<string, CheckBox>(checkbox.name, checkbox));}

        template<class link>
        void addLink(string hostname, string linkname, vec2 padding = vec2(0, 0), bool reversed = false){
            if(!keyInPaars(dEmptys, hostname)) addEmpty(Empty(hostname, {0, 0}, {0, 0}));

            if(is_same<link, Button>::value)             LinksButtons.set(hostname, {hostname, getEmpty(hostname), getButton(linkname), padding, reversed});
            else if(is_same<link, Figure>::value)        LinksFigures.set(hostname, {hostname, getEmpty(hostname), getFigure(linkname), padding, reversed});
            else if(is_same<link, GUIlib::Text>::value)  LinksTexts.set(hostname, {hostname, getEmpty(hostname), getText(linkname), padding, reversed});
            else if(is_same<link, GUIlib::Image>::value) LinksImages.set(hostname, {hostname, getEmpty(hostname), getImage(linkname), padding, reversed});
            else if(is_same<link, Slider>::value)        LinksSliders.set(hostname, {hostname, getEmpty(hostname), getSlider(linkname), padding, reversed});
            else cout<<"[Layer::"<<name<<"::addLink] No such type to link\n";
        }

        Button& getButton(string name){return dButtons[paarIndex(dButtons, getPaarByName(dButtons, name))].value;}
        Figure& getFigure(string name){return dFigures[paarIndex(dFigures, getPaarByName(dFigures, name))].value;}
        GUIlib::Text& getText(string name){return dTexts[paarIndex(dTexts, getPaarByName(dTexts, name))].value;}
        GUIlib::Image& getImage(string name){return dImages[paarIndex(dImages, getPaarByName(dImages, name))].value;}
        Slider& getSlider(string name){return dSliders[paarIndex(dSliders, getPaarByName(dSliders, name))].value;}
        InputField& getInputField(string name){return dInputFields[paarIndex(dInputFields, getPaarByName(dInputFields, name))].value;}
        Layer& getLayer(string name){return dLayers[paarIndex(dLayers, getPaarByName(dLayers, name))].value;}
        //Link<Empty, Container> &getLink(string name){return dLinks[paarIndex(dLinks, getPaarByName(dLinks, name))].value;}
        Empty& getEmpty(string name){return dEmptys[paarIndex(dEmptys, getPaarByName(dEmptys, name))].value;}
        CheckBox& getCheckBox(string name){return dCheckboxes[paarIndex(dCheckboxes, getPaarByName(dCheckboxes, name))].value;}

        void changePos(vec2 newPos){pos = newPos;}

        void update(RenderWindow& window, MouseData &mData, KeyboardData &kData, int tick){
            
            for(auto &link : LinksButtons.values) link.update();
            for(auto &link : LinksFigures.values) link.update();
            for(auto &link : LinksTexts.values) link.update();
            for(auto &link : LinksImages.values) link.update();
            for(auto &link : LinksSliders.values) link.update();
            //for(auto &link : dLinks) link.get().update();

            for(auto &figure : dFigures) figure.get().draw(window);
            for(auto &image : dImages) image.get().draw(window);
            for(auto &text : dTexts) text.get().draw(window, tick);
            for(auto &inputField : dInputFields) inputField.get().update(window, mData, kData, tick);
            for(auto &button : dButtons) button.get().draw(window, mData, tick);
            for(auto &slider : dSliders) slider.get().draw(window, mData);
            for(auto &layer : dLayers) layer.get().update(window, mData, kData, tick);
            for(auto &checkbox : dCheckboxes) checkbox.get().update(window, mData);
            //for(auto &empty : dEmptys) empty.get().update();
        }

        bool operator==(const Layer& other){
            return name == other.name;
        }

        Layer(){
            ;
        }
    };

}
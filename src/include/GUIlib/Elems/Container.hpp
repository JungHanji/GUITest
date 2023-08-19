#pragma once

#include <GUIlib/HIDhandler.hpp>
#include <AdtClasses/AdtClasses.hpp>
#include <functional>
#include <GUIlib/AllGUIelems.hpp>

namespace GUIlib{

    class Container{
        public:

        bool enabledLinks = false;
        string name;
        vec2 pos;

        vector<paar<string, Button>> dButtons;
        vector<paar<string, Figure>> dFigures;
        vector<paar<string, GUIlib::Text>> dTexts;
        vector<paar<string, GUIlib::Image>> dImages;
        vector<paar<string, Slider>> dSliders;
        vector<paar<string, InputField>> dInputFields;
        vector<paar<string, CheckBox>> dCheckboxes;
        vector<paar<string, Container>> dContainers;
        vector<paar<string, Empty>> dEmptys;

        vector<paar<string, Link<Empty, Button>>> LinksButtons;
        vector<paar<string, Link<Empty, Figure>>> LinksFigures;
        vector<paar<string, Link<Empty, GUIlib::Text>>> LinksTexts;
        vector<paar<string, Link<Empty, GUIlib::Image>>> LinksImages;
        vector<paar<string, Link<Empty, Slider>>> LinksSliders;
        vector<paar<string, Link<Empty, InputField>>> LinksInputFields;
        vector<paar<string, Link<Empty, CheckBox>>> LinksCheckboxes;
        vector<paar<string, Link<Empty, Container>>> LinksContainers;
        
        void addButton(Button button){dButtons.push_back(paar<string, Button>(button.name, button));}
        void addFigure(Figure figure){dFigures.push_back(paar<string, Figure>(figure.name, figure));}
        void addText(GUIlib::Text text){dTexts.push_back(paar<string, GUIlib::Text>(text.name, text));}
        void addImage(GUIlib::Image image){dImages.push_back(paar<string, GUIlib::Image>(image.name, image));}
        void addSlider(Slider slider){dSliders.push_back(paar<string, Slider>(slider.name, slider));}
        void addInputField(InputField inputField){dInputFields.push_back(paar<string, InputField>(inputField.name, inputField));}
        //void addCheckbox(CheckBox checkbox){dCheckboxes.push_back(paar<string, CheckBox>(checkbox.name, checkbox));}
        void addContainer(Container container){dContainers.push_back(paar<string, Container>(container.name, container));}
        void addEmpty(Empty empty){dEmptys.push_back(paar<string, Empty>(empty.name, empty));}

        Button& getButton(string name){return dButtons[paarIndex(dButtons, getPaarByName(dButtons, name))].value;}
        Figure& getFigure(string name){return dFigures[paarIndex(dFigures, getPaarByName(dFigures, name))].value;}
        GUIlib::Text& getText(string name){return dTexts[paarIndex(dTexts, getPaarByName(dTexts, name))].value;}
        GUIlib::Image& getImage(string name){return dImages[paarIndex(dImages, getPaarByName(dImages, name))].value;}
        Slider& getSlider(string name){return dSliders[paarIndex(dSliders, getPaarByName(dSliders, name))].value;}
        InputField& getInputField(string name){return dInputFields[paarIndex(dInputFields, getPaarByName(dInputFields, name))].value;}
        //CheckBox& getCheckbox(string name){return dCheckboxes[paarIndex(dCheckboxes, getPaarByName(dCheckboxes, name))].value;}
        Container& getContainer(string name){return dContainers[paarIndex(dContainers, getPaarByName(dContainers, name))].value;}
        Empty& getEmpty(string name){return dEmptys[paarIndex(dEmptys, getPaarByName(dEmptys, name))].value;}

        template<class link>
        void addLink(string hostname, string linkname, vec2 padding = vec2(0, 0), bool reversed = false, vec2 epos = vec2(0, 0)){
            if(!keyInPaars(dEmptys, hostname)) addEmpty(Empty(hostname, epos, {0, 0}));

            if(is_same<link, Button>)             LinksButtons.push_back(paar<string, Link<Empty, Button>>(getEmpty(hostname), {getEmpty(hostname), getButton(linkname), padding, reversed}));
            else if(is_same<link, Figure>)        LinksFigures.push_back(paar<string, Link<Empty, Figure>>(getEmpty(hostname), {getEmpty(hostname), getFigure(linkname), padding, reversed}));
            else if(is_same<link, GUIlib::Text>)  LinksTexts.push_back(paar<string, Link<Empty, GUIlib::Text>>(getEmpty(hostname), {getEmpty(hostname), getText(linkname), padding, reversed}));
            else if(is_same<link, GUIlib::Image>) LinksImages.push_back(paar<string, Link<Empty, GUIlib::Image>>(getEmpty(hostname), {getEmpty(hostname), getImage(linkname), padding, reversed}));
            else if(is_same<link, Slider>)        LinksSliders.push_back(paar<string, Link<Empty, Slider>>(getEmpty(hostname), {getEmpty(hostname), getSlider(linkname), padding, reversed}));
            else cout<<"[Layer::"<<name<<"::addLink] No such type to link\n";
        }

        vec2 globalPadding = vec2(0, 0);

        Container(string name){
            this->name = name;
        }

        void changePos(vec2 newPos){pos = newPos;}

        void update(RenderWindow& window, MouseData &mData, KeyboardData &kData, int tick){
            if(enabledLinks){
                for(auto &link : LinksButtons) link.get().update();
                for(auto &link : LinksFigures) link.get().update();
                for(auto &link : LinksTexts) link.get().update();
                for(auto &link : LinksImages) link.get().update();
                for(auto &link : LinksSliders) link.get().update();
            }

            for(auto &figure : dFigures) figure.get().draw(window);
            for(auto &image : dImages) image.get().draw(window);
            for(auto &text : dTexts) text.get().draw(window, tick);
            for(auto &inputField : dInputFields) inputField.get().update(window, mData, kData, tick);
            for(auto &button : dButtons) button.get().draw(window, mData, tick);
            for(auto &slider : dSliders) slider.get().draw(window, mData);
            for(auto &container : dContainers) container.get().update(window, mData, kData, tick);
            //for(auto &checkbox : dCheckboxes) checkbox.get().draw(window, mData);
        }

        bool operator==(const Container& other){
            return name == other.name;
        }

        Container(){}
    };

}
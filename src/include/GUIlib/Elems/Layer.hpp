#pragma once

#include <GUIlib/HIDhandler.hpp>
#include <AdtClasses/AdtClasses.hpp>
#include <functional>

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
        vector<paar<string, Container>> dContainers;
        vector<paar<string, Empty>> dEmptys;
        vector<paar<string, SuperText>> dSuperTexts;

        dict<string, Link<Empty, Button>> LinksButtons;
        dict<string, Link<Empty, Figure>> LinksFigures;
        dict<string, Link<Empty, GUIlib::Text>> LinksTexts;
        dict<string, Link<Empty, GUIlib::Image>> LinksImages;
        dict<string, Link<Empty, Slider>> LinksSliders;
        dict<string, Link<Empty, InputField>> LinksInputFields;
        dict<string, Link<Empty, CheckBox>> LinksCheckboxes;
        dict<string, Link<Empty, Layer>> LinksLayers;
        dict<string, Link<Empty, Container>> LinksContainers;
        dict<string, Link<Empty, Empty>> LinksEmptys;
        dict<string, Link<Empty, SuperText>> LinksSuperTexts;

        Layer(string name): name(name){}

        Button &addButton(Button button){dButtons.push_back(paar<string, Button>(button.name, button)); return getButton(button.name);}
        Figure &addFigure(Figure figure){dFigures.push_back(paar<string, Figure>(figure.name, figure)); return getFigure(figure.name);}
        GUIlib::Text &addText(GUIlib::Text text){dTexts.push_back(paar<string, GUIlib::Text>(text.name, text)); return getText(text.name);}
        GUIlib::Image &addImage(GUIlib::Image image){dImages.push_back(paar<string, GUIlib::Image>(image.name, image)); return getImage(image.name);}
        Slider &addSlider(Slider slider){dSliders.push_back(paar<string, Slider>(slider.name, slider)); return getSlider(slider.name);}
        InputField &addInputField(InputField inputField){dInputFields.push_back(paar<string, InputField>(inputField.name, inputField)); return getInputField(inputField.name);}
        Layer &addLayer(string name){dLayers.push_back(paar<string, Layer>(name, Layer(name))); return getLayer(name);}
        Empty &addEmpty(Empty empty){dEmptys.push_back(paar<string, Empty>(empty.name, empty)); return getEmpty(empty.name);}
        CheckBox &addCheckBox(CheckBox checkbox){dCheckboxes.push_back(paar<string, CheckBox>(checkbox.name, checkbox)); return getCheckBox(checkbox.name);}
        SuperText &addSuperText(SuperText superText){dSuperTexts.push_back(paar<string, SuperText>(superText.name, superText)); return getSuperText(superText.name);}
        Container &addContainer(Container container){dContainers.push_back(paar<string, Container>(container.name, container)); return getContainer(container.name);}

        template<class link>
        void addLink(string hostname, string linkname, vec2 padding = vec2(0, 0), bool reversed = false){
            if(!keyInPaars(dEmptys, hostname)) addEmpty(Empty(hostname, {0, 0}, {0, 0}));

            if(is_same<link, Button>::value)             LinksButtons.set(hostname, {hostname, getEmpty(hostname), getButton(linkname), padding, reversed});
            else if(is_same<link, Figure>::value)        LinksFigures.set(hostname, {hostname, getEmpty(hostname), getFigure(linkname), padding, reversed});
            else if(is_same<link, GUIlib::Text>::value)  LinksTexts.set(hostname, {hostname, getEmpty(hostname), getText(linkname), padding, reversed});
            else if(is_same<link, GUIlib::Image>::value) LinksImages.set(hostname, {hostname, getEmpty(hostname), getImage(linkname), padding, reversed});
            else if(is_same<link, Slider>::value)        LinksSliders.set(hostname, {hostname, getEmpty(hostname), getSlider(linkname), padding, reversed});
            else if(is_same<link, InputField>::value)    LinksInputFields.set(hostname, {hostname, getEmpty(hostname), getInputField(linkname), padding, reversed});
            else if(is_same<link, CheckBox>::value)      LinksCheckboxes.set(hostname, {hostname, getEmpty(hostname), getCheckBox(linkname), padding, reversed});
            else if(is_same<link, SuperText>::value)     LinksSuperTexts.set(hostname, {hostname, getEmpty(hostname), getSuperText(linkname), padding, reversed});
            else if(is_same<link, Container>::value)     LinksContainers.set(hostname, {hostname, getEmpty(hostname), getContainer(linkname), padding, reversed});
            else cout<<"[Layer::"<<name<<"::addLink] No such type to link\n";
        }

        template<class host, class link>
        void createDoubleLink(string hostName, string linkName, vec2 padding = {0, 0}){
            addLink<host>(hostName+linkName, hostName, {0, 0}, true);
            addLink<link>(hostName+linkName, linkName, padding);
        }

        Button& getButton(string name){return dButtons[paarIndex(dButtons, getPaarByName(dButtons, name))].value;}
        Figure& getFigure(string name){return dFigures[paarIndex(dFigures, getPaarByName(dFigures, name))].value;}
        GUIlib::Text& getText(string name){return dTexts[paarIndex(dTexts, getPaarByName(dTexts, name))].value;}
        GUIlib::Image& getImage(string name){return dImages[paarIndex(dImages, getPaarByName(dImages, name))].value;}
        Slider& getSlider(string name){return dSliders[paarIndex(dSliders, getPaarByName(dSliders, name))].value;}
        InputField& getInputField(string name){return dInputFields[paarIndex(dInputFields, getPaarByName(dInputFields, name))].value;}
        Layer& getLayer(string name){return dLayers[paarIndex(dLayers, getPaarByName(dLayers, name))].value;}
        Empty& getEmpty(string name){return dEmptys[paarIndex(dEmptys, getPaarByName(dEmptys, name))].value;}
        CheckBox& getCheckBox(string name){return dCheckboxes[paarIndex(dCheckboxes, getPaarByName(dCheckboxes, name))].value;}
        SuperText &getSuperText(string name){return dSuperTexts[paarIndex(dSuperTexts, getPaarByName(dSuperTexts, name))].value;}
        Container &getContainer(string name){return dContainers[paarIndex(dContainers, getPaarByName(dContainers, name))].value;}

        void changePos(vec2 newPos){pos = newPos;}

        void update(RenderWindow& window, MouseData &mData, KeyboardData &kData, int tick){
            
            for(auto &link : LinksContainers.values) link.update();
            for(auto &link : LinksButtons.values) link.update();
            for(auto &link : LinksFigures.values) link.update();
            for(auto &link : LinksTexts.values) link.update();
            for(auto &link : LinksImages.values) link.update();
            for(auto &link : LinksSliders.values) link.update();
            for(auto &link : LinksInputFields.values) link.update();
            for(auto &link : LinksCheckboxes.values) link.update();
            for(auto &link : LinksLayers.values) link.update();
            for(auto &link : LinksSuperTexts.values) link.update();

            for(auto &container : dContainers) container.get().update(window, mData, kData, tick);
            for(auto &figure : dFigures) figure.get().draw(window);
            for(auto &image : dImages) image.get().draw(window);
            for(auto &text : dTexts) text.get().draw(window, tick);
            for(auto &superText : dSuperTexts) superText.get().draw(window, tick);
            for(auto &inputField : dInputFields) inputField.get().update(window, mData, kData, tick);
            for(auto &button : dButtons) button.get().draw(window, mData, tick);
            for(auto &slider : dSliders) slider.get().draw(window, mData);
            for(auto &layer : dLayers) layer.get().update(window, mData, kData, tick);
            for(auto &checkbox : dCheckboxes) checkbox.get().update(window, mData);
            
        }

        bool operator==(const Layer& other){
            return name == other.name;
        }

        Layer(){
            ;
        }
    };

}
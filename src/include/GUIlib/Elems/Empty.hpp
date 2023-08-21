#pragma once

#include <GUIlib/HIDhandler.hpp>
#include <AdtClasses/AdtClasses.hpp>
#include <functional>

namespace GUIlib{
    class Empty{
        public:
        string name;
        vec2 pos, size;

        Empty(string name, vec2 pos, vec2 size){
            this->name = name;
            this->pos = pos;
            this->size = size;
        }

        bool operator==(Empty other) {
            return name == other.name;
        }

        Empty(){}
    };

    template<class h, class l>
    class Link{
        h& href;
        l& lref;

        vec2 padding;
        bool reversed = false;

        public:
        string name;
        Link(string name, h& href, l& lref, vec2 padding = vec2(0, 0), bool reversed = false) : name(name), href(href), lref(lref), padding(padding), reversed(reversed) {}

        void update(){
            if(!reversed) lref.pos = href.pos + padding;
            else href.pos = lref.pos + padding;
        }

        bool operator==(Link other) {
            return name == other.name;
        }

        void operator=(Link link){
            this->name = link.name;
            this->href = link.href;
            this->lref = link.lref;
            this->padding = link.padding;
            this->reversed = link.reversed;
        }
    };
};
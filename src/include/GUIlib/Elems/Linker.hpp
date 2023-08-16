#pragma once

#include <GUIlib/HIDhandler.hpp>
#include <AdtClasses/AdtClasses.hpp>
#include <functional>
#include <GUIlib/AllGUIelems.hpp>

namespace GUIlib{

    template<class hostT, class linkedT>
    class Linker{
        public:

        hostT *host;
        linkedT *linked;
        vec2 *pos1, *pos2,
            paddingPos, paddingSize;

        Linker(hostT *host, linkedT *linked): host(host), linked(linked) {}

        void link(){
            pos1 = &host.pos;
            pos2 = pos1;

            paddingPos = pos2 - pos1;
            linked->pos = *pos2;
        }

        void update(){
            linked->pos = *pos1 + paddingPos;
        }

        Linker(){}
    };
}
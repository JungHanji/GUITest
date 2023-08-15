#pragma once

#include <GUIlib/HIDhandler.hpp>
#include <AdtClasses/AdtClasses.hpp>
#include <functional>

template<class hostT, class linkedT>
class Linker{
    public:

    hostT *host;
    linkedT *linked;
    vec2 *pos1, *pos2, *size1, *size2;

    Linker(hostT *host, linkedT *linked): host(host), linked(linked) {}

    void link(){
        pos1 = &host.pos;
        pos2 = pos1;

        size1 = &host.size;
        pos2 = size1;

        linked->pos = *pos2;
        linked->size = *size2;
    }

    void update(){
        linked->pos = *pos1;
    }

    Linker(){}
};
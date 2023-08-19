#pragma once

#include <GUIlib/HIDhandler.hpp>
#include <AdtClasses/AdtClasses.hpp>
#include <functional>
#include <GUIlib/AllGUIelems.hpp>

namespace GUIlib{

    template<class hostT, class linkedT>
    class Linker{
        public:

        Linker(hostT *host, linkedT *linked): host(host), linked(linked) {}

        void link(){
            ;
        }

        void update(){
            ;
        }

        Linker(){}
    };
}
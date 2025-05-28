#pragma once
#include <vector>

class Global {
    static Global* instance;

    Global () {

    }
    public:
    Global(const Global& obj)
    = delete; 
};
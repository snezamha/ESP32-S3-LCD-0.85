#pragma once

#include "../system/System.h"

class App
{
public:
    void begin();
    void update();

private:
    System system;
};
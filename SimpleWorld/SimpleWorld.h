//
// Created by benes on 02/02/2024.
//

#ifndef UNTITLED1_SIMPLEWORLD_H
#define UNTITLED1_SIMPLEWORLD_H


#include "../Renderer/Renderer.h"
#include "../ProjectConstants.h"
#include "../Elements/Elements.h"
class SimpleWorld {
private:


    Renderer renderer;
    TwoDEnvironment environment;
    Elements elements;

    void render();


public:
    SimpleWorld();
    void run();


};


#endif //UNTITLED1_SIMPLEWORLD_H

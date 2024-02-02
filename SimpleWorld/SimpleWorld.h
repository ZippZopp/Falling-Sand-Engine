//
// Created by benes on 02/02/2024.
//

#ifndef UNTITLED1_SIMPLEWORLD_H
#define UNTITLED1_SIMPLEWORLD_H


#include "../Renderer/Renderer.h"
#include "../ProjectConstants.h"

class SimpleWorld {
private:


    Renderer renderer;
    std::map<int, SDL_Color> colorMap;
    TwoDEnvironment environment;

    void render();


public:
    SimpleWorld();
    void run();


};


#endif //UNTITLED1_SIMPLEWORLD_H

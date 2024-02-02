//
// Created by benes on 02/02/2024.
//

#include "SimpleWorld.h"

SimpleWorld::SimpleWorld(): renderer(), environment(ProjectConstants::COLS,ProjectConstants::ROWS){
    SDL_Color black = {0, 0, 0, 255};
    SDL_Color white = {255, 255, 255, 255};
    colorMap[0] = black;
    colorMap[1] = white;
}


void SimpleWorld::run() {
    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        render();
    }
}

void SimpleWorld::render() {
    renderer.resetImage();

    // update here environment z.B: environment.set(1,1,1);
    // maybe add buffer, because of flickering

    renderer.setImage(environment,colorMap);

    renderer.render();
}


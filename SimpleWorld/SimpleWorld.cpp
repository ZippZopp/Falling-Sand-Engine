//
// Created by benes on 02/02/2024.
//

#include "SimpleWorld.h"

SimpleWorld::SimpleWorld(): renderer(), environment(ProjectConstants::COLS, ProjectConstants::ROWS) {}


void SimpleWorld::run() {
    bool running = true;
    SDL_Event event;
    while(running) {
        renderer.handleEvents(&environment,&running);
        render();
    }
}

void SimpleWorld::render() {
    renderer.resetImage();

    Elements::changeEnvironment(&environment);
    // update here environment z.B: environment.set(1,1,1);
    // maybe add buffer, because of flickering

    renderer.setImage(&environment);

    renderer.render();
}


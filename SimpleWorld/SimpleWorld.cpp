//
// Created by benes on 02/02/2024.
//

#include "SimpleWorld.h"

SimpleWorld::SimpleWorld():  renderer(),
                             environment(ProjectConstants::COLS, ProjectConstants::ROWS),
                             colorMap({
                                              {0, {0, 0, 0, 255}}, // 0 -> nothing
                                              {1, {246,215,176, 255}} // 1 -> Sand
                                      })


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


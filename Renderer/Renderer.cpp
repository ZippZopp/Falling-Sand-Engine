//
// Created by benes on 02/02/2024.
//
// Renderer.cpp

#include "Renderer.h"
Renderer::Renderer() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Simple World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    delegatedRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(delegatedRenderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Renderer::render() const {
    SDL_RenderPresent(delegatedRenderer);
}

void Renderer::wait(int milliSeconds) const{
    SDL_Delay(milliSeconds);
}

void Renderer::resetImage() const {
    SDL_SetRenderDrawColor(delegatedRenderer, 0, 0, 0, 255); // Set background to black
    SDL_RenderClear(delegatedRenderer);
}

void
Renderer::setImage(TwoDEnvironment* env) const {
    const int width = WINDOW_WIDTH / env->cols();
    const int height = WINDOW_HEIGHT / env->rows();

    for (int col = 0; col < env->cols(); ++col) {
        for (int row = 0; row < env->rows(); ++row) {

            SDL_Color color = Elements::getColorForId(env->get(col,row));
            SDL_SetRenderDrawColor(delegatedRenderer, color.r, color.g, color.b, 255);

            SDL_Rect rect;
            rect.x = col * width;
            rect.y = row * height;
            rect.w = width;
            rect.h = height;

            SDL_RenderFillRect(delegatedRenderer, &rect);

        }
    }

}

void Renderer::handleEvents(TwoDEnvironment* environment, bool* running) const {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {  // Poll for pending events
        switch (event.type) {
            case SDL_QUIT:
                *running = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                // Handle mouse button click
                if (event.button.button == SDL_BUTTON_LEFT) {  // Check if the left button was clicked
                    const int width = WINDOW_WIDTH / environment->cols(); // todo this is calucated many times, mybe saved it
                    const int height = WINDOW_HEIGHT / environment->rows();

                    int col = (event.button.x) / width;
                    int row = (event.button.y) / height;
                    environment->set(col,row,Elements::SAND_ID);


                }
                break;
                // Handle other events as needed
        }
    }
}

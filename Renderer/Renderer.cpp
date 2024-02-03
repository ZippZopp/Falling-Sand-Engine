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
    static bool leftButtonHeld = false; // Static flag to track the left mouse button state
    static bool rightButtonHeld = false; // Static flag to track the right mouse button state
    SDL_Event event;

    while (SDL_PollEvent(&event)) {  // Poll for pending events
        switch (event.type) {
            case SDL_QUIT:
                *running = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                // Set the flag when the mouse button is pressed
                if (event.button.button == SDL_BUTTON_LEFT) {
                    leftButtonHeld = true;
                } else if (event.button.button == SDL_BUTTON_RIGHT) {
                    rightButtonHeld = true;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                // Clear the flag when the mouse button is released
                if (event.button.button == SDL_BUTTON_LEFT) {
                    leftButtonHeld = false;
                } else if (event.button.button == SDL_BUTTON_RIGHT) {
                    rightButtonHeld = false;
                }
                break;
        }
    }

    // If the left mouse button is being held, create SAND elements
    if (leftButtonHeld) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY); // Get the current mouse position
        createElementWithId(environment, mouseX, mouseY, Elements::SAND_ID);
    }

    // If the right mouse button is being held, create WATER elements
    if (rightButtonHeld) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY); // Get the current mouse position
        createElementWithId(environment, mouseX, mouseY, Elements::WATER_ID);
    }
}


void Renderer::createElementWithId(TwoDEnvironment *environment, int x, int y, int id) const {
    const int width = WINDOW_WIDTH / environment->cols(); // todo this is calucated many times, mybe saved it
    const int height = WINDOW_HEIGHT / environment->rows();
    int col = x / width;
    int row = y / height;
    environment->set(col,row,id);
}

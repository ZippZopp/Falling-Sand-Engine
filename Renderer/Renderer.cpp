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
    SDL_SetRenderDrawColor(delegatedRenderer, 255, 255, 255, 255);
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
    static bool buttonPressed0 = false;
    static bool buttonPressed1 = false;
    static bool buttonPressed2 = false;
    static bool buttonPressed3 = false;
    static bool buttonPressed4 = false;
    SDL_Event event;

    while (SDL_PollEvent(&event)) {  // Poll for pending events
        switch (event.type) {
            case SDL_QUIT:
                *running = false;
                break;
            case SDL_KEYDOWN:
                // Set the flag when the mouse button is pressed
                if (event.key.keysym.sym == SDLK_0) {
                    buttonPressed0 = true;
                } else if (event.key.keysym.sym == SDLK_1) {
                    buttonPressed1 = true;
                } else if (event.key.keysym.sym == SDLK_2) {
                    buttonPressed2 = true;
                }else if (event.key.keysym.sym == SDLK_3) {
                    buttonPressed3 = true;
                } else if (event.key.keysym.sym == SDLK_4) {
                    buttonPressed4 = true;
                }
                break;
            case SDL_KEYUP:
                if (event.key.keysym.sym == SDLK_0) {
                    buttonPressed0 = false;
                } else if (event.key.keysym.sym == SDLK_1) {
                    buttonPressed1 = false;
                } else if (event.key.keysym.sym == SDLK_2) {
                    buttonPressed2 = false;
                }else if (event.key.keysym.sym == SDLK_3) {
                    buttonPressed3 = false;
                } else if (event.key.keysym.sym == SDLK_4) {
                    buttonPressed4 = false;
                }
                break;
        }
    }

    if (buttonPressed0) {
        createElementWithId(environment, Elements::NOTHING_ID);
    }
    if (buttonPressed1) {
        createElementWithId(environment, Elements::SAND_ID);
    }
    if (buttonPressed2) {
        createElementWithId(environment, Elements::WATER_ID);
    }
    if (buttonPressed3) {
        createElementWithId(environment, Elements::STATIC_MATTER_ID);
    }
    if (buttonPressed4) {
        createElementWithId(environment, Elements::SMOKE_ID);
    }
}


void Renderer::createElementWithId(TwoDEnvironment *environment, int id) const {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY); // Get the current mouse position
    const int width = WINDOW_WIDTH / environment->cols(); // todo this is calucated many times, mybe saved it
    const int height = WINDOW_HEIGHT / environment->rows();
    int col = mouseX / width;
    int row = mouseY / height;
    environment->set(col,row,id);
}

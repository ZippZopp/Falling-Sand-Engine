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

#include <unordered_map>
#include <SDL.h>

void Renderer::handleEvents(TwoDEnvironment* environment, bool* running) const {
    static std::unordered_map<SDL_Keycode, bool> buttonPressed = {
            {SDLK_0, false},
            {SDLK_1, false},
            {SDLK_2, false},
            {SDLK_3, false},
            {SDLK_4, false},
            {SDLK_5, false},
            {SDLK_6, false},
            {SDLK_7, false},
    };

    // Mapping of keys to element IDs and their corresponding actions
    static std::unordered_map<SDL_Keycode, std::function<void()>> actions = {
            {SDLK_0, [&](){ createElementWithId(environment, Elements::NOTHING_ID, 3); }},
            {SDLK_1, [&](){ createElementWithId(environment, Elements::SAND_ID, 3); }},
            {SDLK_2, [&](){ createElementWithId(environment, Elements::WATER_ID, 3); }},
            {SDLK_3, [&](){ createElementWithId(environment, Elements::ACID_ID, 3); }},
            {SDLK_4, [&](){ createElementWithId(environment, Elements::STATIC_MATTER_ID, 3); }},
            {SDLK_5, [&](){ createElementWithId(environment, Elements::SMOKE_ID, 3); }},
            {SDLK_6, [&](){ createElementWithId(environment, Elements::CEMENT_ID, 3); }},
            {SDLK_7, [&](){ createElementWithId(environment, Elements::LAVA_ID, 3); }},
    };

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                *running = false;
                break;
            case SDL_KEYDOWN:
                // Set the flag when a key is pressed
                if (buttonPressed.find(event.key.keysym.sym) != buttonPressed.end()) {
                    buttonPressed[event.key.keysym.sym] = true;
                }
                break;
            case SDL_KEYUP:
                // Clear the flag when a key is released
                if (buttonPressed.find(event.key.keysym.sym) != buttonPressed.end()) {
                    buttonPressed[event.key.keysym.sym] = false;
                }
                break;
        }
    }

    // Execute actions for pressed buttons
    for (const auto& [key, pressed] : buttonPressed) {
        if (pressed && actions.find(key) != actions.end()) {
            actions[key]();  // Execute the associated action
        }
    }
}



void Renderer::createElementWithId(TwoDEnvironment *environment, int id,int radius) const {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY); // Get the current mouse position
    const int width = WINDOW_WIDTH / environment->cols(); // todo this is calucated many times, mybe saved it
    const int height = WINDOW_HEIGHT / environment->rows();
    int col = mouseX / width;
    int row = mouseY / height;
    environment->setWithRadius(col,row,id,radius);
}

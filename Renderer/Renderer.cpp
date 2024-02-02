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

void Renderer::resetImage() const {
    SDL_SetRenderDrawColor(delegatedRenderer, 0, 0, 0, 255); // Set background to black
    SDL_RenderClear(delegatedRenderer);
}

void
Renderer::setImage(TwoDEnvironment env, const std::map<int, SDL_Color> &colorMap) const {
    const int width = WINDOW_WIDTH / env.cols();
    const int height = WINDOW_HEIGHT / env.rows();

    for (int col = 0; col < env.cols(); ++col) {
        for (int row = 0; row < env.rows(); ++row) {
            auto colorIt = colorMap.find(env.get(col, row));
            if (colorIt != colorMap.end()) {
                SDL_Color color = colorIt->second;
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

}

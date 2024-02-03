// Renderer.h

#ifndef UNTITLED1_RENDERER_H
#define UNTITLED1_RENDERER_H

#include <SDL.h>
#include <map>
#include <vector>
#include "../2dWorld/TwoDEnvironment.h"
#include "../ProjectConstants.h"
#include "../Elements/Elements.h"
class Renderer {
private:
    SDL_Window* window;
    SDL_Renderer* delegatedRenderer;

public:
    static constexpr int WINDOW_WIDTH = ProjectConstants::WINDOW_WIDTH;
    static constexpr int WINDOW_HEIGHT = ProjectConstants::WINDOW_HEIGHT;

    Renderer();
    virtual ~Renderer();

    void render() const;
    void resetImage() const;
    void setImage(TwoDEnvironment* env) const;

    void handleEvents(TwoDEnvironment *environment, bool* running) const;

    void wait(int milliSeconds) const;

    void createElementWithId(TwoDEnvironment *environment, int id) const;
};

#endif // UNTITLED1_RENDERER_H

//
// Created by benes on 03/02/2024.
//

#ifndef SIMPLEWORLD_ELEMENTS_H
#define SIMPLEWORLD_ELEMENTS_H


#include <functional>
#include <SDL_pixels.h>
#include "../2dWorld/TwoDEnvironment.h"
class Elements {
public:
    static constexpr int NOTHING_ID = 0;
    static constexpr int SAND_ID = 1;
    static constexpr int WATER_ID = 2;

    static constexpr int SIZE = 3;
    static SDL_Color getColorForId(int id);
    void static changeEnvironment(TwoDEnvironment* environment);
private:
    void static changeSand(TwoDEnvironment* environment);

    void static changeEnvironmentWithExpandingType(TwoDEnvironment* environment,int id,
                                            std::function<void(TwoDEnvironment*,int,int, int)> updateMethod);

    void static updateSandLike(TwoDEnvironment* environment, int col, int row, int id);
};


#endif //SIMPLEWORLD_ELEMENTS_H

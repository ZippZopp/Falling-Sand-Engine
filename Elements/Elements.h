//
// Created by benes on 03/02/2024.
//

#ifndef SIMPLEWORLD_ELEMENTS_H
#define SIMPLEWORLD_ELEMENTS_H


#include <functional>
#include <SDL_pixels.h>
#include <random>
#include "../2dWorld/TwoDEnvironment.h"
class Elements {
public:
    Elements();

    static constexpr int NOTHING_ID = 0;
    static constexpr int SMOKE_ID = 10;
    static constexpr int WATER_ID = 20;
    static constexpr int SAND_ID = 30;

    int currentStep;

    static constexpr int STATIC_MATTER_ID = 100;// will never be updated
    static SDL_Color getColorForId(int id);
    void changeEnvironment(TwoDEnvironment* environment);
private:
    void changeSand(TwoDEnvironment* environment);


    void static updateSandLike(TwoDEnvironment* environment, int col, int row, int id);

    bool static moveWhenPossible(TwoDEnvironment *environment, int startCol, int startRow, int targetCol, int targetRow, int id);

    static bool pickOneOfThemRandomlyIfPossible(TwoDEnvironment *environment, int col, int row,  int newRow, int col1, int col2, int id);

    void changeWater(TwoDEnvironment *environment);

    void static updateWaterLike(TwoDEnvironment *environment, int col, int row, int id);

    static bool canSwitch(TwoDEnvironment *environment, int targetCol, int targetRow, int id);

    void changeSmoke(TwoDEnvironment *environment);

    static void updateGasLike(TwoDEnvironment *environment, int col, int row, int id);

    int toggleLeftRightWithId(int id) const;
};

#endif //SIMPLEWORLD_ELEMENTS_H

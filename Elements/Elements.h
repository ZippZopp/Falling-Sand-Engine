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

    // every type is id/10, so for example all gas like are 10 - 19, water like 20 - 29
    static constexpr int NOTHING_ID = 0;
    static constexpr int SMOKE_ID = 10;
    static constexpr int WATER_ID = 20;
    static constexpr int ACID_ID = 41; // orignal id 21, but 41, is more suitable for the code
    static constexpr int SAND_ID = 30;
    static constexpr int CEMENT_ID = 40;
    static constexpr int STATIC_MATTER_ID = 100;// will never be updated
    static constexpr int LAVA_ID = 200;

    int currentStep;
    static SDL_Color getColorForId(int id);
    void changeEnvironment(TwoDEnvironment* environment);
private:
    void changeSand(TwoDEnvironment* environment);


    void static updateSandLike(TwoDEnvironment* environment, int col, int row, int id);

    void static updateLavaLike(TwoDEnvironment *environment, int col, int row, int id);

    void static updateCementLike(TwoDEnvironment* environment, int col, int row, int id);

    bool static moveWhenPossible(TwoDEnvironment *environment, int startCol, int startRow, int targetCol, int targetRow, int id);

    static bool pickOneOfThemRandomlyIfPossible(TwoDEnvironment *environment, int col, int row,  int newRow, int col1, int col2, int id);

    void changeWater(TwoDEnvironment *environment);

    void static updateWaterLike(TwoDEnvironment *environment, int col, int row, int id);

    static bool canSwitch(TwoDEnvironment *environment, int targetCol, int targetRow, int id);

    void changeSmoke(TwoDEnvironment *environment);

    static void updateGasLike(TwoDEnvironment *environment, int col, int row, int id);

    int toggleLeftRightWithId(int id) const;

    void changeCement(TwoDEnvironment *environment);

    void changeLava(TwoDEnvironment *environment);

    void changeAcid(TwoDEnvironment *environment);

    static bool
    moveAndCreateWhenPossible(TwoDEnvironment *environment, int startCol, int startRow, int targetCol, int targetRow,
                              int id, int secId);

    static void
    moveAndCreate(TwoDEnvironment *environment, int startCol, int startRow, int targetCol, int targetRow, int secId);

    void static updateAcidLike(TwoDEnvironment *environment, int col, int row, int id);


    static bool
    pickOneOfThemRandomlyIfPossibleAndCreate(TwoDEnvironment *environment, int col, int row, int newRow, int col1,
                                             int col2,
                                             int id, int secId);
};

#endif //SIMPLEWORLD_ELEMENTS_H

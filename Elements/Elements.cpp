//
// Created by benes on 03/02/2024.
//

#include "Elements.h"

void Elements::changeEnvironment(TwoDEnvironment* environment) {
    changeSand(environment);
}

void Elements::changeSand(TwoDEnvironment* environment) {
    changeEnvironmentWithExpandingType(environment,SAND_ID,updateSandLike);
}

void Elements::changeEnvironmentWithExpandingType(TwoDEnvironment *environment, int id,
                                                  std::function<void(TwoDEnvironment *, int, int, int)> updateMethod) {
    environment->updateEnvironmentWithFunction(id,updateMethod);
}

void Elements::updateSandLike(TwoDEnvironment *environment, int col, int row, int id) {
}

SDL_Color Elements::getColorForId(int id) {
    switch (id) {
        case 1:
            return {246, 215, 176, 255};  // Sand
        case 2:
            return {0, 0, 255, 255};      // Water
        default:
            return {0, 0, 0, 255};        // Nothing
    }
}






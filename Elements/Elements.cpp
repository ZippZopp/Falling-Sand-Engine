//
// Created by benes on 03/02/2024.
//

#include <iostream>
#include "Elements.h"
SDL_Color Elements::getColorForId(int id) {
    switch (id) {
        case SAND_ID:
            return {246, 215, 176, 255};  // Sand
        case WATER_ID:
            return {0, 0, 255, 255};      // Water
        default:
            return {0, 0, 0, 255};        // Nothing
    }
}

void Elements::changeEnvironment(TwoDEnvironment* environment) {
    changeSand(environment);
    changeWater(environment);
}

void Elements::changeSand(TwoDEnvironment* environment) {
    changeEnvironmentWithExpandingType(environment,SAND_ID,updateSandLike);
}

void Elements::changeWater(TwoDEnvironment* environment) {
    changeEnvironmentWithExpandingType(environment,WATER_ID,updateWaterLike);
}

void Elements::changeEnvironmentWithExpandingType(TwoDEnvironment *environment, int id,
                                                  std::function<void(TwoDEnvironment *, int, int, int)> updateMethod) {
    environment->updateEnvironmentWithFunctionBottomToTop(id,updateMethod);
}

void Elements::updateSandLike(TwoDEnvironment *environment, int col, int row, int id) {
    // todo you could check if in bound at beginning, and then get, without checking ,should be faster.
    const int newRow = row+1;
    if(!moveWhenPossible(environment,col,row,col,newRow, id)){
        pickOneOfThemRandomlyIfPossible(environment, col, row, newRow,col-1,col+1,id);
    }
}

void Elements::updateWaterLike(TwoDEnvironment *environment, int col, int row, int id) {
    // todo water goes randomly left and right, this seems wrong
    // todo you could check if in bound at beginning, and then get, without checking ,should be faster.
    const int newRow = row+1;
    if(!moveWhenPossible(environment,col,row,col,newRow, id)){
        if(!pickOneOfThemRandomlyIfPossible(environment, col, row, newRow,col-1,col+1,id)){
            pickOneOfThemRandomlyIfPossible(environment, col, row, row,col-1,col+1, id);
    }
    }

}

bool Elements::pickOneOfThemRandomlyIfPossible(TwoDEnvironment *environment, int col, int row,  int newRow,int col1,int col2, int id) {
    const bool isLeftEmpty = canSwitch(environment, col1,newRow, id);
    const bool isRightEmpty = canSwitch(environment, col2,newRow, id);
    if(isLeftEmpty == isRightEmpty){
        if(isLeftEmpty){
            // TODO dont like how the random number generator is handled, it will initilaised every time and it looks ass
            std::random_device randomGenerator;  // Obtain a random number from hardware
            std::mt19937 gen(randomGenerator()); // Seed the generator
            std::bernoulli_distribution bernoulliDistribution(0.5);
            if(bernoulliDistribution(gen)){
                environment->switchElements(col, row, col1, newRow);
                return true;
            }else{
                environment->switchElements(col, row, col2, newRow);
                return true;
            }
        }
    }else{
        if(isLeftEmpty){
            environment->switchElements(col, row, col1, newRow);
            return true;
        }else{
            environment->switchElements(col, row, col2, newRow);
            return true;
        }
    }
    return false;
}

bool Elements::moveWhenPossible(TwoDEnvironment *environment,int startCol,int startRow, int targetCol, int targetRow, int id){
    if(canSwitch(environment, targetCol, targetRow, id)){
        environment->switchElements(startCol, startRow, targetCol, targetRow);
        return true;
    }else {
        return false;
    }
    }

bool Elements::canSwitch(TwoDEnvironment *environment, int targetCol, int targetRow,
                         int id) {
    int returnValue = environment->get(targetCol, targetRow);
    return (returnValue >= 0) && (returnValue < id);

}








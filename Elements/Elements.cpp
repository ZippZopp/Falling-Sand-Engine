//
// Created by benes on 03/02/2024.
//

#include <iostream>
#include "Elements.h"
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

void Elements::changeEnvironment(TwoDEnvironment* environment) {
    changeSand(environment);
}

void Elements::changeSand(TwoDEnvironment* environment) {
    changeEnvironmentWithExpandingType(environment,SAND_ID,updateSandLike);
}

void Elements::changeEnvironmentWithExpandingType(TwoDEnvironment *environment, int id,
                                                  std::function<void(TwoDEnvironment *, int, int, int)> updateMethod) {
    environment->updateEnvironmentWithFunctionBottomToTop(id,updateMethod);
}

void Elements::updateSandLike(TwoDEnvironment *environment, int col, int row, int id) {
    // todo you could check if in bound at beginning, and then get, without checking ,should be faster.
    std::cout << col << "/" << row << std::endl;
    const int newRow = row+1;
    if(!moveWhenPossible(environment,col,row,col,newRow)){
        pickOneOfThemRandomlyIfPossible(environment, col, row, newRow,col-1,col+1);
    }

}

void Elements::pickOneOfThemRandomlyIfPossible(TwoDEnvironment *environment, int col, int row,  int newRow,int col1,int col2) {
    const bool isLeftEmpty = environment->isEmpty(col1, newRow);
    const bool isRightEmpty = environment->isEmpty(col2,newRow);
    if(isLeftEmpty == isRightEmpty){
        if(isLeftEmpty){
            // TODO dont like how the random number generator is handled, it will initilaised every time and it looks ass
            std::random_device randomGenerator;  // Obtain a random number from hardware
            std::mt19937 gen(randomGenerator()); // Seed the generator
            std::bernoulli_distribution bernoulliDistribution(0.5);
            if(bernoulliDistribution(gen)){
                environment->move(col,row,col1,newRow);
            }else{
                environment->move(col,row,col2,newRow);
            }
        }
    }else{
        if(isLeftEmpty){
            environment->move(col,row,col1,newRow);
        }else{
            environment->move(col,row,col2,newRow);
        }
    }
}

bool Elements::moveWhenPossible(TwoDEnvironment *environment,int startCol,int startRow, int targetCol, int targetRow){
    if(environment->isEmpty(targetCol,targetRow)){
        environment->move(startCol,startRow,targetCol,targetRow);
        return true;
    }else {
        return false;
    }
    }








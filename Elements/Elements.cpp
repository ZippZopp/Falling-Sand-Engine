//
// Created by benes on 03/02/2024.
//

#include <iostream>
#include "Elements.h"
SDL_Color Elements::getColorForId(int id) {
    switch (id) {
        case SMOKE_ID:
            return {5, 5, 5, 255};
        case SAND_ID:
            return {246, 215, 176, 255};
        case WATER_ID:
            return {0, 0, 255, 255};
        case ACID_ID:
            return {214,	229,	64, 255};
        case CEMENT_ID:
            return {128,128,128, 255};
        case LAVA_ID:
            return {255,0,0, 255};
        case STATIC_MATTER_ID:
            return {139,69,19, 255};
        default:
            return {255, 255, 255, 255};
    }
}

void Elements::changeEnvironment(TwoDEnvironment* environment) {
    currentStep = (currentStep+1)%std::numeric_limits<int>::max();
    //todo update all with the same type together, so you only need two for loop for every type
    changeLava(environment);
    changeCement(environment);
    changeSand(environment);
    changeWater(environment);
    changeAcid(environment);
    changeSmoke(environment);
}

void Elements::changeSand(TwoDEnvironment* environment) {
    environment->updateEnvironmentWithFunctionBottomToTop(SAND_ID, updateSandLike, toggleLeftRightWithId(SAND_ID));
}

int Elements::toggleLeftRightWithId(int id) const { return (currentStep + id) % 2; }

void Elements::changeSmoke(TwoDEnvironment* environment) {
    environment->updateEnvironmentWithFunctionTopToBottom(SMOKE_ID,updateGasLike, toggleLeftRightWithId(SMOKE_ID));
}

void Elements::changeCement(TwoDEnvironment* environment) {
    environment->updateEnvironmentWithFunctionBottomToTop(CEMENT_ID,updateCementLike, toggleLeftRightWithId(SMOKE_ID));
}

void Elements::changeLava(TwoDEnvironment* environment) {
    environment->updateEnvironmentWithFunctionBottomToTop(LAVA_ID,updateLavaLike, toggleLeftRightWithId(SMOKE_ID));
}

void Elements::changeWater(TwoDEnvironment* environment) {
    environment->updateEnvironmentWithFunctionBottomToTop(WATER_ID,updateWaterLike, toggleLeftRightWithId(WATER_ID));
}

void Elements::changeAcid(TwoDEnvironment* environment) {
    environment->updateEnvironmentWithFunctionBottomToTop(ACID_ID,updateAcidLike, toggleLeftRightWithId(WATER_ID));
}

void Elements::updateSandLike(TwoDEnvironment *environment, int col, int row, int id) {
    // todo you could check if in bound at beginning, and then get, without checking ,should be faster.
    const int newRow = row+1;
    if(!moveWhenPossible(environment,col,row,col,newRow, id)){
        pickOneOfThemRandomlyIfPossible(environment, col, row, newRow,col-1,col+1,id);
    }
}

void Elements::updateCementLike(TwoDEnvironment *environment, int col, int row, int id) {
    moveWhenPossible(environment,col,row,col,row+1, id);
}
void Elements::updateAcidLike(TwoDEnvironment *environment, int col, int row, int id) {
    const int newRow = row+1;
    if(!moveAndCreateWhenPossible(environment,col,row,col,newRow, id,SMOKE_ID)){
        if(!pickOneOfThemRandomlyIfPossibleAndCreate(environment, col, row, newRow,col-1,col+1,id,SMOKE_ID)){
            pickOneOfThemRandomlyIfPossibleAndCreate(environment, col, row, row,col-1,col+1, id,SMOKE_ID);
        }
    }
}
void Elements::updateLavaLike(TwoDEnvironment *environment, int col, int row, int id) {
    moveAndCreateWhenPossible(environment,col,row,col,row+1, id,SMOKE_ID);
}

void Elements::updateGasLike(TwoDEnvironment *environment, int col, int row, int id) {
    // todo you could check if in bound at beginning, and then get, without checking ,should be faster.
    const int newRow = row-1;
    if(!moveWhenPossible(environment,col,row,col,newRow, id)){
        if(!pickOneOfThemRandomlyIfPossible(environment, col, row, newRow,col-1,col+1,id)){
            pickOneOfThemRandomlyIfPossible(environment, col, row, row,col-1,col+1, id);
        }
    }
}

void Elements::updateWaterLike(TwoDEnvironment *environment, int col, int row, int id) {
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
            if(rand() & 1){// randomly 0 and 1
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

bool Elements::pickOneOfThemRandomlyIfPossibleAndCreate(TwoDEnvironment *environment, int col, int row,  int newRow,int col1,int col2, int id, int secId) {
    const bool isLeftEmpty = canSwitch(environment, col1,newRow, id);
    const bool isRightEmpty = canSwitch(environment, col2,newRow, id);
    if(isLeftEmpty == isRightEmpty){
        if(isLeftEmpty){
            if(rand() & 1){// randomly 0 and 1
                moveAndCreate(environment, col, row, col1, newRow, secId);
                return true;
            }else{
                moveAndCreate(environment, col, row, col2, newRow, secId);
                return true;
            }
        }
    }else{
        if(isLeftEmpty){
            moveAndCreate(environment, col, row, col1, newRow, secId);
            return true;
        }else{
            moveAndCreate(environment, col, row, col2, newRow, secId);
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

bool Elements::moveAndCreateWhenPossible(TwoDEnvironment *environment,int startCol,int startRow, int targetCol, int targetRow, int id,int secId){
    if(canSwitch(environment, targetCol, targetRow, id)){
        moveAndCreate(environment, startCol, startRow, targetCol, targetRow, secId);
        return true;
    }else {
        return false;
    }
}

void
Elements::moveAndCreate(TwoDEnvironment *environment, int startCol, int startRow, int targetCol, int targetRow,
                        int secId) {
    int targetId = environment->get(targetCol, targetRow);
    if(targetId>=0){
        environment->set(targetCol,targetRow,environment->getInBound(startCol,startRow));
        if(targetId>0){
            environment->set(startCol,startRow,secId);
        }else{
            environment->set(startCol,startRow,NOTHING_ID);
        }

    }
}

bool Elements::canSwitch(TwoDEnvironment *environment, int targetCol, int targetRow,
                         int id) {
    int returnValue = (environment->get(targetCol, targetRow)/10);
    return (returnValue >= 0) && (returnValue < (id/10));

}

Elements::Elements() {
    currentStep = 0;
}








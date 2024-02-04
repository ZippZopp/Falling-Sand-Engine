//
// Created by benes on 02/02/2024.
//

#include <functional>
#include "TwoDEnvironment.h"

TwoDEnvironment::TwoDEnvironment(int cols, int rows) : colCount(cols), rowCount(rows), delegateVector(cols * rows, 0) {}

int TwoDEnvironment::size() const {
    return delegateVector.size();
}

int& TwoDEnvironment::operator[](int index) {
    if (checkIfInIndexBoundary(index)) {
        throw std::out_of_range("Index out of bounds.");
    }
    return delegateVector[index];
}

const int& TwoDEnvironment::operator[](int index) const {
    if (checkIfInIndexBoundary(index)) {
        throw std::out_of_range("Index out of bounds.");
    }
    return delegateVector[index];
}

int TwoDEnvironment::get(int col, int row) const {
    // return -1 when out of bounds
    return checkIfInBoundary(col, row) ? delegateVector[colCount * row + col] : -1;
}

bool TwoDEnvironment::isEmpty(int col,int row){
    return get(col,row) == 0;//Elements::NOTHING_ID;
}

int TwoDEnvironment::getInBound(int col, int row) const {
    int value = get(col,row);

    if(value < 0)
        throw std::out_of_range("Column or row is out of bounds.");

    return value;
}

void TwoDEnvironment::set(int col, int row, int value) {
    if(value < 0)
        throw std::invalid_argument("value cant be negative, because all the element ids are positive, and negative stands for outofbounds");
    if (checkIfInBoundary(col, row)) {
        delegateVector[colCount * row + col] = value;
    } else {
        throw std::out_of_range("Column or row is out of bounds. it cant be set");
    }
}

void TwoDEnvironment::setWithRadius(int centerCol, int centerRow, int value, int radius) {
    if (value < 0)
        throw std::invalid_argument("Value can't be negative, because all element IDs are positive, and negative stands for out-of-bounds.");

    for (int col = centerCol - radius; col <= centerCol + radius; ++col) {
        for (int row = centerRow - radius; row <= centerRow + radius; ++row) {
            // Calculate the distance from the center to the current point
            int dx = centerCol - col;
            int dy = centerRow - row;
            double distance = std::sqrt(dx * dx + dy * dy);

            // Check if the current point is within the specified radius
            if (distance <= radius) {
                // Attempt to set the value, but catch and ignore out-of-bounds errors
                try {
                    set(col, row, value);  // Use the existing set method
                } catch (const std::out_of_range&) {
                    // Ignore points that are out of bounds
                }
            }
        }
    }
}

void TwoDEnvironment::switchElements(int startCol, int startRow, int targetCol, int targetRow){
    int targetId = get(targetCol,targetRow);
    if(targetId>=0){
        set(targetCol,targetRow,getInBound(startCol,startRow));
        set(startCol,startRow,targetId);
    }

}


bool TwoDEnvironment::checkIfInIndexBoundary(int index) const {
    return index < 0 || index >= colCount * rowCount;
}

bool TwoDEnvironment::checkIfInBoundary(int col, int row) const {
    return col >= 0 && col < colCount && row >= 0 && row < rowCount;
}

int TwoDEnvironment::cols() const {
    return colCount;
}

int TwoDEnvironment::rows() const {
    return rowCount;
}


void TwoDEnvironment::updateEnvironmentWithFunctionTopToBottom(int id,
                                                        std::function<void(TwoDEnvironment *, int, int, int)> updateMethod, bool goLeft) {


    if(goLeft){
        for (int row = 0; row < rows(); ++row) {
            updateOneRowFromLeft(id, updateMethod, row);
        }
    }else{
        for (int row = 0; row < rows(); ++row) {
            updateOneRowFromRight(id, updateMethod, row);
        }
    }


}

void TwoDEnvironment::updateOneRowFromLeft(int id, std::function<void(TwoDEnvironment *, int, int, int)> &updateMethod,
                                      int row){
    for (int col = 0; col < cols(); ++col) {
        if(get(col, row) == id){
            updateMethod(this, col, row, id);
        }

    }
}

void TwoDEnvironment::updateOneRowFromRight(int id, std::function<void(TwoDEnvironment *, int, int, int)> &updateMethod,
                                      int row){
    for (int col = cols()-1; col >= 0; --col) {
        if(get(col, row) == id){
            updateMethod(this, col, row, id);
        }

    }
}

void TwoDEnvironment::updateEnvironmentWithFunctionBottomToTop(int id,
                                                               std::function<void(TwoDEnvironment *, int, int, int)> updateMethod, bool goLeft) {
    if(goLeft){
        for (int row = rows()-1; row >= 0 ; --row)  {
            updateOneRowFromLeft(id, updateMethod, row);
        }
    }else{
        for (int row = rows()-1; row >= 0 ; --row)  {
            updateOneRowFromRight(id, updateMethod, row);
        }
    }
}



TwoDEnvironment TwoDEnvironment::clone() const {
    return TwoDEnvironment(*this);
}

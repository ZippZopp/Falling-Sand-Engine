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

void TwoDEnvironment::set(int col, int row, int value) {
    if(value < 0)
        throw std::invalid_argument("value cant be negative, because all the element ids are positive, and negative stands for outofbounds");


    if (checkIfInBoundary(col, row)) {
        delegateVector[colCount * row + col] = value;
    } else {
        throw std::out_of_range("Column or row is out of bounds.");
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

void TwoDEnvironment::updateEnvironmentWithFunction(int id,
                                                   std::function<void(TwoDEnvironment *, int, int, int)> updateMethod) {
    for (int col = 0; col < cols(); ++col) {
        for (int row = 0; row < rows(); ++row) {
            updateMethod(this, col, row, id);
        }
    }
}

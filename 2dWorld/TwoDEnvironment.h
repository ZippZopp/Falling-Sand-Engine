//
// Created by benes on 02/02/2024.
//

#ifndef UNTITLED1_TWODENVIRONMENT_H
#define UNTITLED1_TWODENVIRONMENT_H


#include <vector>
#include <stdexcept>

class TwoDEnvironment {
private:
    std::vector<int> delegateVector;
    int colCount;

private:
    int rowCount;

public:
    TwoDEnvironment(int cols, int rows);

    int size() const;
    int& operator[](int index);
    const int& operator[](int index) const;
    int get(int col, int row) const;
    void set(int col, int row, int value);
    int cols() const;
    int rows() const;

private:
    bool checkIfInIndexBoundary(int index) const;
    bool checkIfInBoundary(int col, int row) const;
};

#endif //UNTITLED1_TWODENVIRONMENT_H

//
// Created by benes on 02/02/2024.
//

#ifndef UNTITLED1_TWODENVIRONMENT_H
#define UNTITLED1_TWODENVIRONMENT_H


#include <vector>
#include <stdexcept>
#include <functional>
//#include "../Elements/Elements.h"
class TwoDEnvironment {
private:
    std::vector<int> delegateVector;
    int colCount;
    int rowCount;
    bool checkIfInIndexBoundary(int index) const;
    bool checkIfInBoundary(int col, int row) const;
public:
    using iterator = std::vector<int>::iterator;
    using const_iterator = std::vector<int>::const_iterator;

    iterator begin() { return delegateVector.begin();}
    iterator end() { return delegateVector.end(); }

    // Const versions for iterating over const objects
    const_iterator begin() const { return delegateVector.begin(); }
    const_iterator end() const { return delegateVector.end(); }

    const_iterator cbegin() const { return delegateVector.cbegin(); }
    const_iterator cend() const { return delegateVector.cend(); }


    TwoDEnvironment(int cols, int rows);
    void updateEnvironmentWithFunctionSave(int id,std::function<void(TwoDEnvironment*,int,int, int)> updateMethod);

    int size() const;
    int& operator[](int index);
    const int& operator[](int index) const;
    int get(int col, int row) const;
    int getInBound(int col, int row) const;
    void set(int col, int row, int value);
    int cols() const;
    int rows() const;

    void switchElements(int startCol, int startRow, int targetCol, int targetRow);

    bool isEmpty(int col, int row);

    TwoDEnvironment clone() const;

    void
    updateEnvironmentWithFunctionBottomToTop(int id,
                                             std::function<void(TwoDEnvironment *, int, int, int)> updateMethod);

    void
    updateEnvironmentWithFunctionTopToBottom(int id,
                                             std::function<void(TwoDEnvironment *, int, int, int)> updateMethod);


};

#endif //UNTITLED1_TWODENVIRONMENT_H

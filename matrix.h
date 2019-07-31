#ifndef MATRIX_H
#define MATRIX_H

#include "cell.h"

const int MATRIX_DIMENSION = 9;

// The class is a matrix that stores the data puzzle.
class Matrix
{
public:
    Cell storage[MATRIX_DIMENSION][MATRIX_DIMENSION];
};

#endif // MATRIX_H

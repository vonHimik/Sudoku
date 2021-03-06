#ifndef MATRIX_H
#define MATRIX_H

#include "cell.h"

// The class is a matrix that stores the data puzzle.
class Matrix
{
public:
    static constexpr size_t DIMENSION = 9;
    static constexpr size_t BLOCK_DIMENSION = 3;
    Cell storage[DIMENSION][DIMENSION];
};

#endif // MATRIX_H

#ifndef SOLVER_H
#define SOLVER_H

#include "coordinate.h"
#include <vector>

// A class containing puzzle solving tools.
class Solver
{
public:

    std::vector <Coordinate> coordinates;
    int backStepCounter;

    bool CheckRowSolver (int x, int y);
    bool CheckColumnSolver (int x, int y);
    bool CheckBlockSolver (int x, int y);
    bool CheckRepeatedSolver (int i, int j);
    void MoveBackSolver (int& i, int& j);
    void WriteInArrayForTestingSolver (int i, int j);
};

#endif // SOLVER_H

#ifndef SOLVER_H
#define SOLVER_H

#include "coordinate.h"
#include <vector>

class GameMaster;
class MainWindow;

// A class containing puzzle solving tools.
class Solver
{
public:

    std::vector <Coordinate> coordinates;
    int backStepCounter;

    bool CheckRowSolver (int x, int y, GameMaster &gameMaster);
    bool CheckColumnSolver (int x, int y, GameMaster &gameMaster);
    bool CheckBlockSolver (int x, int y, GameMaster &gameMaster);
    bool CheckRepeatedSolver (int i, int j, GameMaster &gameMaster);
    void MoveBackSolver (int &i, int &j, GameMaster &gameMaster);
    void WriteInArrayForTestingSolver (int i, int j, GameMaster &gameMaster);
};

#endif // SOLVER_H

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
    static constexpr size_t MAXIMUM_NUMBER_OF_STEPS_BACK = 150;

    bool CheckRowSolver (int x, int y, const GameMaster &gameMaster) const;
    bool CheckColumnSolver (int x, int y, const GameMaster &gameMaster) const;
    bool CheckBlockSolver (int x, int y, const GameMaster &gameMaster) const;
    bool CheckRepeatedSolver (int i, int j, const GameMaster &gameMaster) const;
    void MoveBackSolver (int &i, int &j, GameMaster &gameMaster);
    void WriteInArrayForTestingSolver (int i, int j, GameMaster &gameMaster);
};

#endif // SOLVER_H

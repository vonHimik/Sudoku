#ifndef GAMEMASTER_H
#define GAMEMASTER_H

#include "gamesettings.h"
#include "generator.h"
#include "solver.h"
#include "matrix.h"

// Class - game manager: stores the current information and instances of all used tools.
class GameMaster
{
public:
    GameSettings gameSettings;

    Generator generator;

    Solver solver;

    // Matrix into which we write generated sudoku.
    Matrix realMatrix;

    // Matrix to display sudoku in a table, save and load, control win.
    Matrix maskMatrix;

    // Array for testing when generating sudoku.
    int arrayForTests[Matrix::DIMENSION*Matrix::DIMENSION][Matrix::DIMENSION] = {0};
};

#endif // GAMEMASTER_H

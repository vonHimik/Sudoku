#include "gamemaster.h"
#include "mainwindow.h"

// Option method above to solve the puzzle. Differs in that it completely passes through the row.
// When checking, it ignores the cell that called it.
bool Solver::CheckRowSolver(int x, int y, const GameMaster &gameMaster) const
{
    for (int i = 0; i < Matrix::DIMENSION; i++)
    {
        if (i != y)
        {
            if (gameMaster.maskMatrix.storage[x][i].value == gameMaster.maskMatrix.storage[x][y].value)
            {
                return false;
            }
        }
    }

    return true;
}

// Option method above to solve the puzzle. Differs in that it completely passes through the column.
// When checking, it ignores the cell that called it.
bool Solver::CheckColumnSolver (int x, int y, const GameMaster &gameMaster) const
{
    for (int i = 0; i < Matrix::DIMENSION; i++)
    {
        if (i != x)
        {
            if (gameMaster.maskMatrix.storage[i][y].value == gameMaster.maskMatrix.storage[x][y].value)
            {
                return false;
            }
        }
    }

    return true;
}

// Option method above to solve the puzzle. Differs in that it completely passes through the block.
// When checking, it ignores the cell that called it.
bool Solver::CheckBlockSolver (int x, int y, const GameMaster &gameMaster) const
{
    // This method is called by one cell in a 3x3 block, but must check it all.
    // Therefore, we transform the coordinates of the cell into the coordinates of the block, using division without a remainder.
    // For example, cell (17) in row 0 (x) and column 8 (y) is in a block of rows 0-1-2 and columns 6-7-8.
    // 1/3 = 0 and 8/3 = 2, 0 * 3 = 0 and 3 * 2 = 6.
    // That is, we start checking the block in which the cell is located from the very beginning and
    //    then we will move forward with a step of one three times to cover the entire block.
    int i_start = x/Matrix::BLOCK_DIMENSION;
    int j_start = y/Matrix::BLOCK_DIMENSION;
    i_start *= Matrix::BLOCK_DIMENSION;
    j_start *= Matrix::BLOCK_DIMENSION;

    for (int i = i_start; i < i_start + Matrix::BLOCK_DIMENSION; i++)
    {
        for (int j = j_start; j < j_start + Matrix::BLOCK_DIMENSION; j++)
        {
            if (i == x && j == y)
            {
            }
            else
            {
                if (gameMaster.maskMatrix.storage[i][j].value == gameMaster.maskMatrix.storage[x][y].value)
                {
                    return false;
                }
            }
        }
    }

    return true;
}

// Option method above to solve the puzzle. We check not a real matrix, but a mask matrix.
bool Solver::CheckRepeatedSolver (int i, int j, const GameMaster &gameMaster) const
{
    int value = gameMaster.maskMatrix.storage[i][j].value;

    int current = i * Matrix::DIMENSION + j + Generator::SHIFT;

    if (gameMaster.arrayForTests[current][value] == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Method to return to the previous cell.
void Solver::MoveBackSolver (int &i, int &j, GameMaster &gameMaster)
{
    // If the search for a solution lasts too long, then it makes sense to stop it and start a new, randomly provide different initial values,
    //    which can lead to a more rapid achievement of the solution, since the difficult situation will be eliminated.
    if (gameMaster.solver.backStepCounter > Solver::MAXIMUM_NUMBER_OF_STEPS_BACK)
    {
        gameMaster.solver.backStepCounter = 0;
        gameMaster.generator.ArrayForTestsClearing(gameMaster);

        for (int i = 0; i < Matrix::DIMENSION; i++)
        {
            for (int j = 0; j < Matrix::DIMENSION; j++)
            {
                if (gameMaster.maskMatrix.storage[i][j].editable == true)
                {
                    gameMaster.maskMatrix.storage[i][j].value = 0;
                }
            }
        }

        MainWindow().on_btn_save_clicked();
        MainWindow().on_btn_newgame_clicked();
        MainWindow().on_btn_load_clicked();
        MainWindow().on_btn_solve_clicked();
        MainWindow().WinControl();
    }
    else
    {
        // The sequence number of the current cell in the test array.
        int current = i * Matrix::DIMENSION + j + Generator::SHIFT;

        // We are going through the list of checked values of the current cell.
        for (int x = 1; x <= Matrix::DIMENSION; x++)
        {
            // We bring it to the original appearance.
            gameMaster.arrayForTests[current][x] = 0;
        }

        i = gameMaster.solver.coordinates.back().row;
        j = gameMaster.solver.coordinates.back().column;

        gameMaster.solver.coordinates.pop_back();
    }
}

// Option method above to solve the puzzle. We use not a real matrix, but a mask matrix.
void Solver::WriteInArrayForTestingSolver (int i, int j, GameMaster &gameMaster)
{
    int current = i * Matrix::DIMENSION + j + Generator::SHIFT;

    int value = gameMaster.maskMatrix.storage[i][j].value;

    gameMaster.arrayForTests[current][value] = 1;
}

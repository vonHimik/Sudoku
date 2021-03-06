#include "gamemaster.h"

// Method for checking the presence of the same value in the cell in the row, x and y - coordinates of the cell being checked.
bool Generator::CheckRow (int x, int y, const GameMaster &gameMaster) const
{
    // We pass on the line to the cell called the method.
    for (int i = 0; i < y; i++)
    {
        // If we meet a cell with the same value as in the checked cell.
        if (gameMaster.realMatrix.storage[x][i].value == gameMaster.realMatrix.storage[x][y].value)
        {
            // That check failed.
            return false;
        }
    }

    // Otherwise, the test passed.
    return true;
}

// Method for checking the presence of the same value in the cell in the column, x and y - coordinates of the cell being checked.
bool Generator::CheckColumn (int x, int y, const GameMaster &gameMaster) const
{
    // We pass through the column to the checked cell.
    for (int i = 0; i < x; i++)
    {
        // If we meet a cell with the same value as in the checked cell.
        if (gameMaster.realMatrix.storage[i][y].value == gameMaster.realMatrix.storage[x][y].value)
        {
            // That check failedThat check failed.
            return false;
        }
    }

    // Otherwise, the test passed.
    return true;
}

// Method for checking the presence of the same value in a cell in a block of nine cells (3x3), x and y - coordinates of the cell being checked.
bool Generator::CheckBlock (int x, int y, const GameMaster &gameMaster) const
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

    // Move around the block.
    for (int i = i_start; i < i_start + Matrix::BLOCK_DIMENSION; i++)
    {
        for (int j = j_start; j < j_start + Matrix::BLOCK_DIMENSION; j++)
        {
            // Before the calling cell.
            if (i == x && j == y)
            {
                return true;
            }

            // If in some other cell in the block the same number as in the one that we check.
            if (gameMaster.realMatrix.storage[i][j].value == gameMaster.realMatrix.storage[x][y].value)
            {
                // That check failed.
                return false;
            }
        }
    }

    // If the entire block passed and did not meet the matching value, then the test is successful.
    return true;
}

// Method to check if all possible values were checked for this cell.
bool Generator::AllValuesChecking (int i, int j, const GameMaster &gameMaster) const
{
    // The sequence number of the tested cell in the test array.
    int current = i * Matrix::DIMENSION + j + Generator::SHIFT;

    // We pass through the subarray representing the list of possible values of this cell.
    for (int x = 1; x < Matrix::DIMENSION; x++)
    {
        // If we find an empty field in this subarray.
        if (gameMaster.arrayForTests[current][x] == 0)
        {
            // This means that not all possible values have been checked.
            return true;
        }
    }

    // If there is no empty cell in the subarray, then all possible values for this cell have been checked.
    return false;
}

// A method that detects whether a cell has been checked for its current value.
bool Generator::CheckRepeated (int i, int j, const GameMaster &gameMaster) const
{
    // Current cell value.
    int value = gameMaster.realMatrix.storage[i][j].value;

    // Sequence number of the current cell in the test array.
    int current = i * Matrix::DIMENSION + j + Generator::SHIFT;

    // If this value has already been written to the matrix and checked.
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
void Generator::MoveBack (int &i, int &j, GameMaster &gameMaster)
{
    // The sequence number of the current cell in the test array.
    int current = i * Matrix::DIMENSION + j + Generator::SHIFT;

    // We are going through the list of checked values of the current cell.
    for (int x = 1; x <= Matrix::DIMENSION; x++)
    {
        // We bring it to the original appearance.
        gameMaster.arrayForTests[current][x] = 0;
    }

    // If it was the first line.
    if (j < 1)
    {
        // Then go to the previous column of the last row.
        i--;
        j = Matrix::DIMENSION - 1;
    }
    // Otherwise, we return to the previous row (and the same column).
    else
    {
        j--;
    }
}

// A method that writes to the test array that a certain value has been assigned to the current cell.
void Generator::WriteInArrayForTesting (int i, int j, GameMaster &gameMaster)
{
    // The sequence number of the current cell in the test array.
    int current = i * Matrix::DIMENSION + j + Generator::SHIFT;

    // Current cell value.
    int value = gameMaster.realMatrix.storage[i][j].value;

    // We mark in the corresponding current cell of the subarray that this value was checked.
    gameMaster.arrayForTests[current][value] = 1;
}

// Method clearing test array.
void Generator::ArrayForTestsClearing(GameMaster &gameMaster)
{
    for (int i = 1; i <= Matrix::DIMENSION * Matrix::DIMENSION; i++)
    {
        for (int j = 1; j <= Matrix::DIMENSION; j++)
        {
            gameMaster.arrayForTests[i][j] = 0;
        }
    }
}

// Method to create a mask-matrix.
void Generator::CreateMask(GameMaster &gameMaster)
{
    int changeCounter = 0; // The number of cells whose value will be unknown to the player.

    // We control the selected level of complexity and, depending on it, select the number of cells that we want to hide.
    if (gameMaster.gameSettings.difficult == gameMaster.gameSettings.easy)
    {
        changeCounter = Generator::NUMBER_OF_HIDDEN_CELLS_ON_EASY_DIFFICULTY;
    }
    else if (gameMaster.gameSettings.difficult == gameMaster.gameSettings.normal)
    {
        changeCounter = Generator::NUMBER_OF_HIDDEN_CELLS_ON_NORMAL_DIFFICULTY;
    }
    else if (gameMaster.gameSettings.difficult == gameMaster.gameSettings.hard)
    {
        changeCounter = Generator::NUMBER_OF_HIDDEN_CELLS_ON_HARD_DIFFICULTY;
    }

    // We pass through the matrix, randomly hiding the required number of cells.
    while (changeCounter > 0)
    {
        for (int i = 0; i < Matrix::DIMENSION; i++)
        {
            for (int j = 0; j < Matrix::DIMENSION; j++)
            {
                // Variable for calculating the chance that the value of this cell will be hidden.
                int random = rand()%10+1;

                // ~30%
                if (random < 3)
                {
                    gameMaster.maskMatrix.storage[i][j].value = 0;
                    changeCounter--;
                }
            }
        }
    }
}

void Generator::PlayFieldClearing(GameMaster &gameMaster)
{
    for (int i = 0; i < Matrix::DIMENSION; i++)
    {
        for (int j = 0; j < Matrix::DIMENSION; j++)
        {
            gameMaster.maskMatrix.storage[i][j].editable = true;
        }
    }
}

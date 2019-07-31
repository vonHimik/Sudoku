#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

const int DIMENSION = 9;

// For the program to work properly, we must create an instance of the game master.
GameMaster gameMaster;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Method for checking the presence of the same value in the cell in the row, x and y - coordinates of the cell being checked.
bool Generator::CheckRow (int x, int y)
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

// Option method above to solve the puzzle. Differs in that it completely passes through the row.
// When checking, it ignores the cell that called it.
bool Solver::CheckRowSolver(int x, int y)
{
    for (int i = 0; i < DIMENSION; i++)
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

// Method for checking the presence of the same value in the cell in the column, x and y - coordinates of the cell being checked.
bool Generator::CheckColumn (int x, int y)
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

// Option method above to solve the puzzle. Differs in that it completely passes through the column.
// When checking, it ignores the cell that called it.
bool Solver::CheckColumnSolver (int x, int y)
{
    for (int i = 0; i < DIMENSION; i++)
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

// Method for checking the presence of the same value in a cell in a block of nine cells (3x3), x and y - coordinates of the cell being checked.
bool Generator::CheckBlock (int x, int y)
{
    int i_start = x/3;
    int j_start = y/3;

    i_start *= 3;
    j_start *= 3;

    // Move around the block.
    for (int i = i_start; i < i_start + 3; i++)
    {
        for (int j = j_start; j < j_start + 3; j++)
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

// Option method above to solve the puzzle. Differs in that it completely passes through the block.
// When checking, it ignores the cell that called it.
bool Solver::CheckBlockSolver (int x, int y)
{
    int i_start = x/3;
    int j_start = y/3;

    i_start *= 3;
    j_start *= 3;

    for (int i = i_start; i < i_start + 3; i++)
    {
        for (int j = j_start; j < j_start + 3; j++)
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

// Method to check if all possible values were checked for this cell.
bool Generator::AllValuesChecking (int i, int j)
{
    // The sequence number of the tested cell in the test array.
    int current = i * DIMENSION + j + 1;

    // We pass through the subarray representing the list of possible values of this cell.
    for (int x = 1; x < DIMENSION; x++)
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
bool Generator::CheckRepeated (int i, int j)
{
    // Current cell value.
    int value = gameMaster.realMatrix.storage[i][j].value;

    // Sequence number of the current cell in the test array.
    int current = i * DIMENSION + j + 1;

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

// Option method above to solve the puzzle. We check not a real matrix, but a mask matrix.
bool Solver::CheckRepeatedSolver (int i, int j)
{
    int value = gameMaster.maskMatrix.storage[i][j].value;

    int current = i * DIMENSION + j + 1;

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
void Generator::MoveBack (int& i, int& j)
{
    // The sequence number of the current cell in the test array.
    int current = i * DIMENSION + j + 1;

    // We are going through the list of checked values of the current cell.
    for (int x = 1; x <= DIMENSION; x++)
    {
        // We bring it to the original appearance.
        gameMaster.arrayForTests[current][x] = 0;
    }

    // If it was the first line.
    if (j < 1)
    {
        // Then go to the previous column of the last row.
        i--;
        j = DIMENSION - 1;
    }
    // Otherwise, we return to the previous row (and the same column).
    else
    {
        j--;
    }
}

// Method to return to the previous cell.
void Solver::MoveBackSolver (int& i, int& j)
{
    // If the search for a solution lasts too long, then it makes sense to stop it and start a new, randomly provide different initial values,
    //    which can lead to a more rapid achievement of the solution, since the difficult situation will be eliminated.
    if (gameMaster.solver.backStepCounter > 150)
    {
        gameMaster.solver.backStepCounter = 0;
        gameMaster.generator.ArrayForTestsClearing();

        for (int i = 0; i < DIMENSION; i++)
        {
            for (int j = 0; j < DIMENSION; j++)
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
        int current = i * DIMENSION + j + 1;

        // We are going through the list of checked values of the current cell.
        for (int x = 1; x <= DIMENSION; x++)
        {
            // We bring it to the original appearance.
            gameMaster.arrayForTests[current][x] = 0;
        }

        i = gameMaster.solver.coordinates.back().row;
        j = gameMaster.solver.coordinates.back().column;

        gameMaster.solver.coordinates.pop_back();
    }
}

// A method that writes to the test array that a certain value has been assigned to the current cell.
void Generator::WriteInArrayForTesting (int i, int j)
{
    // The sequence number of the current cell in the test array.
    int current = i * DIMENSION + j + 1;

    // Current cell value.
    int value = gameMaster.realMatrix.storage[i][j].value;

    // We mark in the corresponding current cell of the subarray that this value was checked.
    gameMaster.arrayForTests[current][value] = 1;
}

// Option method above to solve the puzzle. We use not a real matrix, but a mask matrix.
void Solver::WriteInArrayForTestingSolver (int i, int j)
{
    int current = i * DIMENSION + j + 1;

    int value = gameMaster.maskMatrix.storage[i][j].value;

    gameMaster.arrayForTests[current][value] = 1;
}

// Method clearing test array.
void Generator::ArrayForTestsClearing()
{
    int i;
    int j;

    for (i = 1; i <= DIMENSION * DIMENSION; i++)
    {
        for (j = 1; j <= DIMENSION; j++)
        {
            gameMaster.arrayForTests[i][j] = 0;
        }
    }
}

// Method to create a mask-matrix.
void Generator::CreateMask()
{
    int i;
    int j;
    int changeCounter; // The number of cells whose value will be unknown to the player.
    int random;        // Variable for calculating the chance that the value of this cell will be hidden.

    // We control the selected level of complexity and, depending on it, select the number of cells that we want to hide.
    if (gameMaster.gameSettings.easy)
    {
        changeCounter = 15;
    }
    else if (gameMaster.gameSettings.normal)
    {
        changeCounter = 25;
    }
    else if (gameMaster.gameSettings.hard)
    {
        changeCounter = 35;
    }

    // We pass through the matrix, randomly hiding the required number of cells.
    while (changeCounter > 0)
    {
        for (i = 0; i < DIMENSION; i++)
        {
            for (j = 0; j < DIMENSION; j++)
            {
                random = rand()%10+1;

                if (random < 3)
                {
                    gameMaster.maskMatrix.storage[i][j].value = 0;
                    changeCounter--;
                }
            }
        }
    }
}

// Method controlling the winning in the game.
void MainWindow::WinControl()
{
    int i;
    int j;
    bool win = true;

    // We check the compliance of the displayed matrix-masks (as amended by the player) to the matrix with the solution.
    for (i = 0; i < DIMENSION; i++)
    {
        for (j = 0; j < DIMENSION; j++)
        {
            if (gameMaster.realMatrix.storage[i][j].value != gameMaster.maskMatrix.storage[i][j].value)
            {
                win = false;
            }
        }
    }

    // Depending on the result, we display characters on the screen.
    if (win)
    {
        ui->label->setText("WIN!");
    }
    else
    {
        ui->label->setText("- , -");
    }
}

// Template method for methods that write numbers to a table cell.
void MainWindow::click_on_btn (int num)
{
    if (gameMaster.maskMatrix.storage[Row][Column].editable == true) // If the user is allowed to edit this cell.
    {
        QTableWidgetItem* Cell = ui->table_gamefield->item(Row, Column);
        QString str = QString::number(num);
        Cell->setText(str);
        gameMaster.maskMatrix.storage[Row][Column].value = num;
        WinControl();
    }
}

// Methods for writing numbers to table cells.
void MainWindow::on_btn_1_clicked()
{
    click_on_btn(1);
}

void MainWindow::on_btn_2_clicked()
{
    click_on_btn(2);
}

void MainWindow::on_btn_3_clicked()
{
    click_on_btn(3);
}

void MainWindow::on_btn_4_clicked()
{
    click_on_btn(4);
}

void MainWindow::on_btn_5_clicked()
{
    click_on_btn(5);
}

void MainWindow::on_btn_6_clicked()
{
    click_on_btn(6);
}

void MainWindow::on_btn_7_clicked()
{
    click_on_btn(7);
}

void MainWindow::on_btn_8_clicked()
{
    click_on_btn(8);
}

void MainWindow::on_btn_9_clicked()
{
    click_on_btn(9);
}

// Method, when you click on a cell in the table that displays its coordinates.
void MainWindow::on_table_gamefield_cellClicked (int row, int column)
{
    Row = row;
    Column = column;
    QString str = "";
    str += '0' + row + 1;
    str += ',';
    str += '0' + column + 1;
    const QString cstr = str;
    ui->label->setText(cstr);
}

// Method that generates a new puzzle.
void MainWindow::on_btn_newgame_clicked()
{
    int i;
    int j;

    // We pass through each cell of the matrix representing the playing field.
    for (i = 0; i < DIMENSION; i++)
    {
        for (j = 0; j < DIMENSION; j++)
        {
            // Infinite loop for a particular cell.
            for (;;)
            {
                // Check if all values were tested for the current cell.
                if (!gameMaster.generator.AllValuesChecking (i, j))
                {
                    // If yes, then go back.
                    gameMaster.generator.MoveBack (i, j);
                }

                // We select a random value for the current cell.
                gameMaster.realMatrix.storage[i][j].value = rand()%9+1;
                gameMaster.maskMatrix.storage[i][j].value = gameMaster.realMatrix.storage[i][j].value;

                // Check if it was checked before.
                if (gameMaster.generator.CheckRepeated (i, j))
                {
                    // If yes, then go to check the next random value (obviously, it did not fit) for this cell.
                    continue;
                }

                // Otherwise, remember that it is verified.
                gameMaster.generator.WriteInArrayForTesting (i, j);

                // And check for matches in the block, row and column.
                if (gameMaster.generator.CheckBlock (i, j) && gameMaster.generator.CheckRow (i, j) && gameMaster.generator.CheckColumn (i, j))
                {
                    // If there is no match, go to the next cell.
                    break;
                }
            }
        }
    }

    // Clear the test array.
    gameMaster.generator.ArrayForTestsClearing();

    // Create a mask.
    gameMaster.generator.CreateMask();


    // We display the generated puzzle on the screen.
   for (int i = 0; i < DIMENSION; i++)
   {
       for (int j = 0; j < DIMENSION; j++)
       {
           QTableWidgetItem* Cell = ui->table_gamefield->item(i, j);
           int value = gameMaster.maskMatrix.storage[i][j].value;
           QString str;

           if (value == 0)
           {
               str = ' ';
               Cell->setBackgroundColor(Qt::white);
           }
           else
           {
               gameMaster.maskMatrix.storage[i][j].editable = false;
               str = QString::number(value);
               Cell->setBackgroundColor(Qt::gray);
           }

           Cell->setText(str);
       }
   }

   // We control whether there was a win.
   WinControl();
}

// This method saves the current game state to a text file.
void MainWindow::on_btn_save_clicked()
{
    // Open the file.
    ofstream infile("d:/SudokuSaveFile.txt");
    infile.is_open();
    
    // We pass on the matrix, which displays what is visible to the user.
    for (int i = 0; i < DIMENSION; i++)
    {
        for (int j = 0; j < DIMENSION; j++)
        {
            // Write from it to the file.
            infile << gameMaster.maskMatrix.storage[i][j].value << " ";
            
            // We move the carriage at the end of the row.
            if (j == DIMENSION - 1)
            {
                infile << endl;
            }
        }
    }

    // Close the file.
    infile.close();
}

// Method, loading the state of the game from a text file.
void MainWindow::on_btn_load_clicked()
{   
    // Open the file.
    ifstream input("d:/SudokuSaveFile.txt");

    // We read its contents in the matrix.
    int **matrix = new int *[DIMENSION];

    for (unsigned i = 0; i < DIMENSION; i++)
    {
        matrix[i] = new int [DIMENSION];

        for (unsigned j = 0; j < DIMENSION; j++)
        {
            input >> matrix[i][j];
        }
    }

    // Close the file.
    input.close();

    // Save data from the resulting matrix in the game.
    for (int i = 0; i < DIMENSION; i++)
    {
        for (int j = 0; j < DIMENSION; j++)
        {
            gameMaster.maskMatrix.storage[i][j].value = matrix[i][j];
            gameMaster.realMatrix.storage[i][j].value = matrix[i][j];
        }
    }

    // Display.
    for (int i = 0; i < DIMENSION; i++)
    {
        for (int j = 0; j < DIMENSION; j++)
        {
            QTableWidgetItem* Cell = ui->table_gamefield->item(i, j);
            int value = gameMaster.maskMatrix.storage[i][j].value;
            QString str;

            if (value == 0)
            {
                str = ' ';
                Cell->setBackgroundColor(Qt::white);
            }
            else
            {
                gameMaster.maskMatrix.storage[i][j].editable = false;
                str = QString::number(value);
                Cell->setBackgroundColor(Qt::gray);
            }

            Cell->setText(str);
        }
    }
}

// Method that solves the current puzzle.
void MainWindow::on_btn_solve_clicked()
{
    int i;
    int j;

    for (i = 0; i < DIMENSION; i++)
    {
        for (j = 0; j < DIMENSION; j++)
        {
            // We pass through the matrix, applying to each cell an infinite loop.
            for (;;)
            {
                // If this cell has no value.
                if (gameMaster.maskMatrix.storage[i][j].value == 0)
                {
                    // Check if all possible values were tested for the current cell.
                    if (!gameMaster.generator.AllValuesChecking (i, j))
                    {
                        // If yes, then go back.
                        gameMaster.solver.MoveBackSolver(i,j);
                        gameMaster.solver.backStepCounter++;
                    }

                    // We select a random value for the current cell.
                    gameMaster.maskMatrix.storage[i][j].value = rand()%9+1;
                    gameMaster.maskMatrix.storage[i][j].editable = true;

                    // Remember that it is verified.
                    gameMaster.solver.WriteInArrayForTestingSolver (i, j);

                    // And check for matches in the block, row and column.
                    if (gameMaster.solver.CheckBlockSolver(i,j) && gameMaster.solver.CheckRowSolver(i,j) && gameMaster.solver.CheckColumnSolver(i,j))
                    {
                        // Add the coordinates of this cell to the stack with the coordinates of the solved cells.
                        Coordinate coordinate;
                        coordinate.row = i;
                        coordinate.column = j;

                        gameMaster.solver.coordinates.push_back(coordinate);

                        // If there is no match, go to the next cell.
                        break;
                    }

                    // If the number does not fit, reset the value of the current cell in order not to go to the next one prematurely.
                    gameMaster.maskMatrix.storage[i][j].value = 0;
                }
                // If the cell already has a value.
                else
                {
                    // Then go to the next.
                    break;
                }
            }
        }
    }

    // We display the result on the screen.
    for (int i = 0; i < DIMENSION; i++)
    {
        for (int j = 0; j < DIMENSION; j++)
        {
            QTableWidgetItem* Cell = ui->table_gamefield->item(i, j);
            int value = gameMaster.maskMatrix.storage[i][j].value;
            QString str;
            str = QString::number(value);

            if (value == 0)
            {
                str = ' ';
                Cell->setBackgroundColor(Qt::white);
            }
            else
            {
                str = QString::number(value);
            }

            Cell->setText(str);
        }
    }

    // Clear the test array.
    gameMaster.generator.ArrayForTestsClearing();

    // We control the winnings.
    WinControl();
}

// Method completing the program.
void MainWindow::on_btn_close_clicked()
{
    close();
}

// Method setting easy game difficulty.
void MainWindow::on_rbtn_easy_toggled(bool checked)
{
    if (checked == true)
    {
        gameMaster.gameSettings.easy = true;
    }
    else
    {
        gameMaster.gameSettings.easy = false;
    }
}

// Method setting normal game difficulty.
void MainWindow::on_rbtn_normal_toggled(bool checked)
{
    if (checked == true)
    {
        gameMaster.gameSettings.normal = true;
    }
    else
    {
        gameMaster.gameSettings.normal = false;
    }
}

// Method setting hard game difficulty.
void MainWindow::on_rbtn_hard_toggled(bool checked)
{
    if (checked == true)
    {
        gameMaster.gameSettings.hard = true;
    }
    else
    {
        gameMaster.gameSettings.hard = false;
    }
}

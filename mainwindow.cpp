#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

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

// Method controlling the winning in the game.
void MainWindow::WinControl()
{
    bool win = true;

    // We check the compliance of the displayed matrix-masks (as amended by the player) to the matrix with the solution.
    for (int i = 0; i < Matrix::DIMENSION; i++)
    {
        for (int j = 0; j < Matrix::DIMENSION; j++)
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

        // Validation of the entered number.
        if (gameMaster.realMatrix.storage[Row][Column].value != num)
        {
            Cell->setBackgroundColor(Qt::red);
        }
        else
        {
            Cell->setBackgroundColor(Qt::white);
        }

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
    gameMaster.generator.PlayFieldClearing(gameMaster);

    // We pass through each cell of the matrix representing the playing field.
    for (int i = 0; i < Matrix::DIMENSION; i++)
    {
        for (int j = 0; j < Matrix::DIMENSION; j++)
        {
            // Loop for a particular cell.
            do
            {
                // Check if all values were tested for the current cell.
                if (!gameMaster.generator.AllValuesChecking (i, j, gameMaster))
                {
                    // If yes, then go back.
                    gameMaster.generator.MoveBack (i, j, gameMaster);
                }

                // We select a random value for the current cell.
                gameMaster.realMatrix.storage[i][j].value = rand()%9+1;
                gameMaster.maskMatrix.storage[i][j].value = gameMaster.realMatrix.storage[i][j].value;

                // Check if it was checked before.
                if (gameMaster.generator.CheckRepeated (i, j, gameMaster))
                {
                    // If yes, then go to check the next random value (obviously, it did not fit) for this cell.
                    continue;
                }

                // Otherwise, remember that it is verified.
                gameMaster.generator.WriteInArrayForTesting (i, j, gameMaster);
            }
            while (!gameMaster.generator.CheckBlock (i, j, gameMaster) || !gameMaster.generator.CheckRow (i, j, gameMaster)
                   || !gameMaster.generator.CheckColumn (i, j, gameMaster));
        }
    }

    // Clear the test array.
    gameMaster.generator.ArrayForTestsClearing(gameMaster);

    // Create a mask.
    gameMaster.generator.CreateMask(gameMaster);


    // We display the generated puzzle on the screen.
   for (int i = 0; i < Matrix::DIMENSION; i++)
   {
       for (int j = 0; j < Matrix::DIMENSION; j++)
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
    ofstream infile("SudokuSaveFile.txt");
    infile.is_open();
    
    // We pass on the matrix, which displays what is visible to the user.
    for (int i = 0; i < Matrix::DIMENSION; i++)
    {
        for (int j = 0; j < Matrix::DIMENSION; j++)
        {
            // Write from it to the file.
            infile << gameMaster.maskMatrix.storage[i][j].value << " ";
            
            // We move the carriage at the end of the row.
            if (j == Matrix::DIMENSION - 1)
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
    ifstream input("SudokuSaveFile.txt");

    // We read its contents in the matrix.
    int **matrix = new int *[Matrix::DIMENSION];

    for (unsigned i = 0; i < Matrix::DIMENSION; i++)
    {
        matrix[i] = new int [Matrix::DIMENSION];

        for (unsigned j = 0; j < Matrix::DIMENSION; j++)
        {
            input >> matrix[i][j];
        }
    }

    // Close the file.
    input.close();

    // Save data from the resulting matrix in the game.
    for (int i = 0; i < Matrix::DIMENSION; i++)
    {
        for (int j = 0; j < Matrix::DIMENSION; j++)
        {
            gameMaster.maskMatrix.storage[i][j].value = matrix[i][j];
            gameMaster.realMatrix.storage[i][j].value = matrix[i][j];
        }
    }

    // Display.
    for (int i = 0; i < Matrix::DIMENSION; i++)
    {
        for (int j = 0; j < Matrix::DIMENSION; j++)
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
    for (int i = 0; i < Matrix::DIMENSION; i++)
    {
        for (int j = 0; j < Matrix::DIMENSION; j++)
        {
            while (gameMaster.maskMatrix.storage[i][j].value == 0)
            {
                // Check if all possible values were tested for the current cell.
                if (!gameMaster.generator.AllValuesChecking (i, j, gameMaster))
                {
                    // If yes, then go back.
                    gameMaster.solver.MoveBackSolver(i, j, gameMaster);
                    gameMaster.solver.backStepCounter++;
                }

                // We select a random value for the current cell.
                gameMaster.maskMatrix.storage[i][j].value = rand()%9+1;
                gameMaster.maskMatrix.storage[i][j].editable = true;

                // Remember that it is verified.
                gameMaster.solver.WriteInArrayForTestingSolver (i, j, gameMaster);

                // And check for matches in the block, row and column.
                if (gameMaster.solver.CheckBlockSolver(i, j, gameMaster) && gameMaster.solver.CheckRowSolver(i, j, gameMaster)
                        && gameMaster.solver.CheckColumnSolver(i, j, gameMaster))
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
        }
    }

    // We display the result on the screen.
    for (int i = 0; i < Matrix::DIMENSION; i++)
    {
        for (int j = 0; j < Matrix::DIMENSION; j++)
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
    gameMaster.generator.ArrayForTestsClearing(gameMaster);

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

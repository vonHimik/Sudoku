#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QString>
#include <QTableWidget>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QIODevice>

#include <cstdio>
#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <locale>

namespace Ui
{
class MainWindow;
}

// A struct that represents a cell of the playing field.
struct Cell
{
    int value;
    bool editable = true;
};

// The class is a matrix that stores the data puzzle.
class Matrix
{
public:
    Cell storage[9][9];
};

// A class containing tools for generating a puzzle.
class Generator
{
public:
    bool CheckRow (int x, int y);
    bool CheckColumn (int x, int y);
    bool CheckBlock (int x, int y);
    bool AllValuesChecking (int i, int j);
    bool CheckRepeated (int i, int j);
    void MoveBack (int& i, int& j);
    void WriteInArrayForTesting (int i, int j);
    void ArrayForTestsClearing();
    void CreateMask();
};

// A class containing puzzle solving tools.
class Solver
{
public:
    bool CheckRowSolver (int x, int y);
    bool CheckColumnSolver (int x, int y);
    bool CheckBlockSolver (int x, int y);
    bool CheckRepeatedSolver (int i, int j);
    void WriteInArrayForTestingSolver (int i, int j);
};

// The class that implements the game settings storage.
class GameSettings
{
public:
    // Boolean variables for difficulty level
    bool easy = true;
    bool normal;
    bool hard;
};

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
    int arrayForTests[9*9][9] = {0};
};

// A class that implements program management through the user interface.
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // Through this variable, access the user interface.
    Ui::MainWindow *ui;

    // Variables to interact with the table.
    int Column;
    int Row;

public slots:

    // The pattern processing method of pressing the button with the number.
    void click_on_btn(int num);

    // Methods for processing the number buttons.
    void on_btn_1_clicked();
    void on_btn_2_clicked();
    void on_btn_3_clicked();
    void on_btn_4_clicked();
    void on_btn_5_clicked();
    void on_btn_6_clicked();
    void on_btn_7_clicked();
    void on_btn_8_clicked();
    void on_btn_9_clicked();

    // Method that handles clicking on a table field.
    void on_table_gamefield_cellClicked(int row, int column);

    // Handler pressing a button starting a new game.
    void on_btn_newgame_clicked();

    // Processing method of pressing the save button.
    void on_btn_save_clicked();

    // Processing method for pressing the download button.
    void on_btn_load_clicked();

    // The method of processing pressing the button to solve.
    void on_btn_solve_clicked();

    // Processing method of pressing the button to close the program.
    void on_btn_close_clicked();

    // Methods that handle pressing buttons that change difficult.
    void on_rbtn_easy_toggled(bool checked);
    void on_rbtn_normal_toggled(bool checked);
    void on_rbtn_hard_toggled(bool checked);

    // Method to control winnings.
    void WinControl();
};

#endif // MAINWINDOW_H

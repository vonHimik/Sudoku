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

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    // Methods declarations:

    // The pattern processing method of pressing the button with the number
    void click_on_btn(int num);

    // Methods for processing the number buttons
    void on_btn_1_clicked();
    void on_btn_2_clicked();
    void on_btn_3_clicked();
    void on_btn_4_clicked();
    void on_btn_5_clicked();
    void on_btn_6_clicked();
    void on_btn_7_clicked();
    void on_btn_8_clicked();
    void on_btn_9_clicked();

    // Method that handles clicking on a table field
    void on_table_gamefield_cellClicked(int row, int column);

    // Handler pressing a button starting a new game
    void on_btn_newgame_clicked();

    // Processing method of pressing the save button
    void on_btn_save_clicked();

    // Processing method for pressing the download button
    void on_btn_load_clicked();

    // The method of processing pressing the button to solve
    void on_btn_solve_clicked();

    // Processing method of pressing the button to close the program
    void on_btn_close_clicked();

    // Methods that handle pressing buttons that change difficult
    void on_rbtn_easy_toggled(bool checked);
    void on_rbtn_normal_toggled(bool checked);
    void on_rbtn_hard_toggled(bool checked);

    // Methods for generating sudoku
    bool CheckRow (int x, int y);
    bool CheckColumn (int x, int y);
    bool CheckSquare (int x, int y);
    bool Test (int i, int j);
    bool CheckRepeated (int i, int j);
    void MoveBack (int& i, int& j);
    void WriteInMatrix (int i, int j);

    // The method for creating a mask matrix
    void CreateMask();

    // Method to control winnings
    void WinControl();

private:

    // Through this variable, access the user interface
    Ui::MainWindow *ui;

    // Variables to interact with the table
    int Column, Row;

    // Boolean variables for difficulty level
    bool easy, normal, hard;

    // Matrix into which we write generated sudoku
    int SudokuRealMatrix[9][9];

    // Matrix to display sudoku in a table, save and load, control win
    int SudokuMaskMatrix[9][9];

    // Array for testing when generating sudoku
    int ArrayForTests[9*9][9] = {0};
};

#endif // MAINWINDOW_H

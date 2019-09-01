#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "cell.h"
#include "matrix.h"
#include "generator.h"
#include "coordinate.h"
#include "solver.h"
#include "gamesettings.h"
#include "gamemaster.h"

#include <QMainWindow>
#include <fstream>

namespace Ui
{
class MainWindow;
}

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
    void click_on_btn (int num);

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
    void on_rbtn_easy_toggled (bool checked);
    void on_rbtn_normal_toggled (bool checked);
    void on_rbtn_hard_toggled (bool checked);

    // Method to control winnings.
    void WinControl();
};

#endif // MAINWINDOW_H

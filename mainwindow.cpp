#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

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

const int SIZE = 9;
int SudokuRealMatrix[SIZE][SIZE];
int SudokuMaskMatrix[SIZE][SIZE];
int ArrayForTests[SIZE*SIZE][SIZE] = {0};

bool CheckRow (int x, int y);
bool CheckColumn (int x, int y);
bool CheckSquare (int x, int y);
bool Test (int i, int j);
bool CheckRepeated (int i, int j);
void MoveBack (int& i, int& j);
void WriteInMatrix (int i, int j);

bool CheckRow (int x, int y)
{
    for (int i = 0; i < y; i++)
    {
        if (SudokuRealMatrix[x][i] == SudokuRealMatrix[x][y])
        {
            return false;
        }
    }

    return true;
}

bool CheckColumn (int x, int y)
{
    for (int i = 0; i < x; i++)
    {
        if (SudokuRealMatrix[i][y] == SudokuRealMatrix[x][y])
        {
            return false;
        }
    }

    return true;
}

bool CheckSquare (int x, int y)
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
                return true;
            }

            if (SudokuRealMatrix[i][j] == SudokuRealMatrix[x][y])
            {
                return false;
            }
        }
    }

    return true;
}

bool Test (int i, int j)
{
    int current = i * 9 + j + 1;

    for(int x = 1; x < 9; x++)
    {
        if( ArrayForTests[current][x] == 0)
        {
            return true;
        }
    }

    return false;
}

bool CheckRepeated (int i, int j)
{
    int value = SudokuRealMatrix[i][j];
    int current = i * 9 + j + 1;

    if (ArrayForTests[current][value] == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void MoveBack (int& i, int& j)
{
    int current = i * 9 + j + 1;

    for (int x = 1; x <= 9; x++)
    {
        ArrayForTests[current][x] = 0;
    }

    if (j < 1)
    {
        i--;
        j = 8;
    }
    else
    {
        j--;
    }
}

void WriteInMatrix (int i, int j)
{
    int current = i * 9 + j + 1;
    int value = SudokuRealMatrix[i][j];
    ArrayForTests[current][value] = 1;
}

void MainWindow::click_on_btn(int num)
{
    QTableWidgetItem* Cell = ui->table_gamefield->item(Row, Column);
    QString str = QString::number(num);
    Cell->setText(str);
}

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

void MainWindow::on_btn_newgame_clicked()
{
    int i;
    int j;

    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            for (;;)
            {
                if (!Test (i, j))
                {
                    MoveBack (i, j);
                }

                SudokuRealMatrix[i][j] = rand()%9+1;
                SudokuMaskMatrix [i][j] = SudokuRealMatrix [i][j];

                if (CheckRepeated (i, j))
                {
                    continue;
                }

                WriteInMatrix (i, j);

                if ( CheckSquare (i, j) && CheckRow (i, j) && CheckColumn (i, j) )
                {
                    break;
                }
            }
        }
    }


   for (int i = 0; i < 9; i++)
   {
       for (int j = 0; j < 9; j++)
       {
           QTableWidgetItem* Cell = ui->table_gamefield->item(i, j);
           //int b = SudokuRealMatrix[i][j];
           int b = SudokuMaskMatrix[i][j];
           QString str = QString::number(b);
           Cell->setText(str);
       }
   }
}

void MainWindow::on_btn_save_clicked()
{

}

void MainWindow::on_btn_load_clicked()
{

}

void MainWindow::on_btn_solve_clicked()
{

}

void MainWindow::on_btn_close_clicked()
{
    close();
}

void MainWindow::on_rbtn_easy_toggled(bool checked)
{
    if (checked == true)
    {
        easy = true;
    }
    else
    {
        easy = false;
    }
}

void MainWindow::on_rbtn_normal_toggled(bool checked)
{
    if (checked == true)
    {
        normal = true;
    }
    else
    {
        normal = false;
    }
}

void MainWindow::on_rbtn_hard_toggled(bool checked)
{
    if (checked == true)
    {
        hard = true;
    }
    else
    {
        hard = false;
    }
}

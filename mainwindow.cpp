#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdio>
#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <locale>

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

bool MainWindow::CheckRow (int x, int y)
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

bool MainWindow::CheckColumn (int x, int y)
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

bool MainWindow::CheckSquare (int x, int y)
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

bool MainWindow::Test (int i, int j)
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

bool MainWindow::CheckRepeated (int i, int j)
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

void MainWindow::MoveBack (int& i, int& j)
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

void MainWindow::WriteInMatrix (int i, int j)
{
    int current = i * 9 + j + 1;
    int value = SudokuRealMatrix[i][j];
    ArrayForTests[current][value] = 1;
}

void MainWindow::CreateMask()
{
    int i;
    int j;
    int changeCounter;
    int random;

    if (easy)
    {
        changeCounter = 15;
    }
    else if (normal)
    {
        changeCounter = 35;
    }
    else if (hard)
    {
        changeCounter = 55;
    }

    while (changeCounter > 0)
    {
        for (i = 0; i < 9; i++)
        {
            for (j = 0; j < 9; j++)
            {
                random = rand()%10+1;

                if (random < 3)
                {
                    SudokuMaskMatrix[i][j] = 0;
                    changeCounter--;
                }
            }
        }
    }
}

void MainWindow::WinControl()
{
    int i;
    int j;
    bool win = true;

    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            if (SudokuRealMatrix[i][j] != SudokuMaskMatrix[i][j])
            {
                win = false;
            }
        }
    }

    if (win)
    {
        ui->label->setText("WIN!");
    }
}

void MainWindow::click_on_btn(int num)
{
    QTableWidgetItem* Cell = ui->table_gamefield->item(Row, Column);
    QString str = QString::number(num);
    Cell->setText(str);
    SudokuMaskMatrix[Row][Column] = num;
    WinControl();
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
                SudokuMaskMatrix[i][j] = SudokuRealMatrix[i][j];

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

    CreateMask();


   for (int i = 0; i < 9; i++)
   {
       for (int j = 0; j < 9; j++)
       {
           QTableWidgetItem* Cell = ui->table_gamefield->item(i, j);
           int b = SudokuMaskMatrix[i][j];
           QString str;

           if (b == 0)
           {
               str = ' ';
               Cell->setBackgroundColor(Qt::white);
           }
           else
           {
               str = QString::number(b);
               Cell->setBackgroundColor(Qt::gray);
           }

           Cell->setText(str);
       }
   }
}

void MainWindow::on_btn_save_clicked()
{

    ofstream infile("d:/SudokuSaveFile.txt");
    infile.is_open();

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            infile << SudokuMaskMatrix[i][j] << " ";

            if (j == 8)
            {
                infile << endl;
            }
        }
    }

    infile.close();
}

void MainWindow::on_btn_load_clicked()
{   
    std::ifstream input("d:/SudokuSaveFile.txt");

    int **matrix = new int *[9];

    for (unsigned i = 0; i < 9; i++)
    {
        matrix[i] = new int [9];

        for (unsigned j = 0; j < 9; j++)
        {
            input >> matrix[i][j];
        }
    }

    input.close();

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            SudokuMaskMatrix[i][j] = matrix[i][j];
        }
    }



    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            QTableWidgetItem* Cell = ui->table_gamefield->item(i, j);
            int b = SudokuMaskMatrix[i][j];
            QString str;

            if (b == 0)
            {
                str = ' ';
                Cell->setBackgroundColor(Qt::white);
            }
            else
            {
                str = QString::number(b);
                Cell->setBackgroundColor(Qt::gray);
            }

            Cell->setText(str);
        }
    }
}

void MainWindow::on_btn_solve_clicked()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            QTableWidgetItem* Cell = ui->table_gamefield->item(i, j);
            int b = SudokuRealMatrix[i][j];
            QString str;

            str = QString::number(b);

            Cell->setText(str);
        }
    }
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QString>
#include <QTableWidget>

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
    void on_btn_1_clicked();
    void on_btn_2_clicked();
    void on_btn_3_clicked();
    void on_btn_4_clicked();
    void on_btn_5_clicked();
    void on_btn_6_clicked();
    void on_btn_7_clicked();
    void on_btn_8_clicked();
    void on_btn_9_clicked();
    void on_table_gamefield_cellClicked(int row, int column);

    void on_btn_newgame_clicked();
    void on_btn_reset_clicked();
    void on_btn_save_clicked();
    void on_btn_load_clicked();
    void on_btn_dif_set_clicked();
    void on_btn_solve_clicked();

    void on_btn_close_clicked();

private:
    Ui::MainWindow *ui;
    int Column, Row;
    void click_on_btn(int num);
};

#endif // MAINWINDOW_H

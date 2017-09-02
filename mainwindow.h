#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QDebug>
#include <QtGlobal>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setCRValues(int avgPlayer, int numPlayers, int &outEasy, int &outMedium, int &outHard, int &outDeadly);
    int getTarget(int difficlty, int easy, int medium, int hard, int deadly);
    double getMultiplier(int numMooks, int numPlayers, int difficulty);

private slots:
    void on_pushButton_clicked();

    void on_but_calc_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

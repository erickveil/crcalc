#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList difficulty_options =
            (QStringList()<<"Easy"<<"Medium"<<"Hard"<<"Deadly");
    ui->comboBox->addItems(difficulty_options);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    int playerLevels = ui->lePartyLevels->text().toInt();
    int numPlayers = ui->leNumPlayers->text().toInt();
    int difficulty = ui->comboBox->currentIndex();
    int bossXpEach = ui->leBossXp->text().toInt();
    int mookXpEach = ui->leMookXp->text().toInt();
    int numBosses = ui->leNumBosses->text().toInt();

    int avgPlayer = qRound(static_cast<float>(playerLevels) / numPlayers);
    int easy;
    int medium;
    int hard;
    int deadly;
    int deadly2;
    int deadly3;

    setCRValues(avgPlayer, numPlayers, easy, medium, hard,
                deadly, deadly2, deadly3);
    ui->leDeadly->setText(QString::number(deadly));
    ui->leEasy->setText(QString::number(easy));
    ui->leHard->setText(QString::number(hard));
    ui->leMed->setText(QString::number(medium));

    int bossTotals = bossXpEach * numBosses;

    int numMooks = 0;
    double multiplier = getMultiplier(numMooks, numPlayers, difficulty);
    int crxp = static_cast<int>(
                std::round(
                    (bossTotals + (numMooks * mookXpEach)) * multiplier
                    )
                );

    int target = getTarget(difficulty, easy, medium, hard, deadly);

    int max = 50;
    while (crxp < target) {
        ++numMooks;
        multiplier = getMultiplier(numMooks, numPlayers, difficulty);
        crxp = static_cast<int>(
                    std::round(
                        (bossTotals + (numMooks * mookXpEach)) * multiplier
                        )
                    );

        bool isInviniteLoopDanger = (crxp <= 0);
        if (isInviniteLoopDanger) {
            ui->numMooks->setText(QString("Set Mook Xp > 0.") );
            return;
        }
        if (numMooks >= max) {
            ui->numMooks->setText("More than 50");
            return;
        }
    }

    --numMooks;
    if (numMooks < 0) {
        ui->numMooks->setText(QString("Needs weaker boss.") );
    }
    else {
        ui->numMooks->setText(QString::number(numMooks));
    }

}

int MainWindow::getTarget(int difficulty, int easy, int medium, int hard, int deadly)
{
    switch (difficulty) {
    case 0: return easy;
    case 1: return medium;
    case 2: return hard;
    case 3: return deadly;
    default: return -1;
    }
}


double MainWindow::getMultiplier(int numMooks, int numPlayers, int difficulty)
{
    if (numPlayers < 3) {
        if (numMooks <= 1) { return 1.5; }
        if (numMooks == 2) { return 2; }
        if (numMooks <= 6) { return 2.5; }
        if (numMooks <= 10) { return 3; }
        return 4;
    }
    if (numPlayers > 5) {
        if (numMooks <= 1) { return 1; }
        if (numMooks == 2) { return 1; }
        if (numMooks <= 6) { return 1.5; }
        if (numMooks <= 10) { return 2; }
        if (numMooks < 15) { return 2.5; }
        return 3;
    }

    if (numMooks <= 1) { return 1; }
    if (numMooks == 2) { return 1.5; }
    if (numMooks <= 6) { return 2; }
    if (numMooks <= 10) { return 2.5; }
    if (numMooks < 15) { return 3; }
    return 4;
}

void MainWindow::setCRValues(int avgPlayer, int numPlayers, int &outEasy,
                             int &outMedium, int &outHard, int &outDeadly,
                             int &outDeadly2, int &outDeadly3)
{
    switch(avgPlayer) {
    case 1:
        outEasy = 25;
        outMedium = 50;
        outHard = 75;
        outDeadly = 100;
        outDeadly2 = 150;
        outDeadly3 = 175;
        break;
    case 2:
        outEasy = 50;
        outMedium = 100;
        outHard = 150;
        outDeadly = 200;
        outDeadly2 = 250;
        outDeadly3 = 300;
        break;
    case 3:
        outEasy = 75;
        outMedium = 150;
        outHard = 225;
        outDeadly = 400;
        outDeadly2 = 600;
        outDeadly3 = 900;
        break;
    case 4:
        outEasy = 125;
        outMedium = 250;
        outHard = 375;
        outDeadly = 500;
        outDeadly2 = 750;
        outDeadly3 = 1100;
        break;
    case 5:
        outEasy = 250;
        outMedium = 500;
        outHard = 750;
        outDeadly = 1100;
        outDeadly2 = 1700;
        outDeadly3 = 2000;
        break;
    case 6:
        outEasy = 300;
        outMedium = 600;
        outHard = 900;
        outDeadly = 1400;
        outDeadly2 = 2100;
        outDeadly3 = 2400;
        break;
    case 7:
        outEasy = 350;
        outMedium = 750;
        outHard = 1100;
        outDeadly = 1700;
        outDeadly2 = 2400;
        outDeadly3 = 2800;
        break;
    case 8:
        outEasy = 450;
        outMedium = 900;
        outHard = 1400;
        outDeadly = 2100;
        outDeadly2 = 2800;
        outDeadly3 = 3000;
        break;
    case 9:
        outEasy = 550;
        outMedium = 1100;
        outHard = 1600;
        outDeadly = 2400;
        outDeadly2 = 3600;
        outDeadly3 = 4500;
        break;
    case 10:
        outEasy = 600;
        outMedium = 1200;
        outHard = 1900;
        outDeadly = 2800;
        outDeadly2 = 4300;
        outDeadly3 = 6400;
        break;
    case 11:
        outEasy = 800;
        outMedium = 1600;
        outHard = 2400;
        outDeadly = 3600;
        break;
    case 12:
        outEasy = 1000;
        outMedium = 2000;
        outHard = 3000;
        outDeadly = 4500;
        break;
    case 13:
        outEasy = 1100;
        outMedium = 2200;
        outHard = 3400;
        outDeadly = 5100;
        break;
    case 14:
        outEasy = 1250;
        outMedium = 2500;
        outHard = 3800;
        outDeadly = 5700;
        break;
    case 15:
        outEasy = 1400;
        outMedium = 2800;
        outHard = 4300;
        outDeadly = 6400;
        break;
    case 16:
        outEasy = 1600;
        outMedium = 3200;
        outHard = 4800;
        outDeadly = 7200;
        break;
    case 17:
        outEasy = 2000;
        outMedium = 3900;
        outHard = 5900;
        outDeadly = 8800;
        break;
    case 18:
        outEasy = 2100;
        outMedium = 4200;
        outHard = 6300;
        outDeadly = 9500;
        break;
    case 19:
        outEasy = 2400;
        outMedium = 4900;
        outHard = 7300;
        outDeadly = 10900;
        break;
    case 20:
        outEasy = 2800;
        outMedium = 5700;
        outHard = 8500;
        outDeadly = 12700;
        break;
    default:
        outEasy = 0;
        outMedium = 0;
        outHard = 0;
        outDeadly = 0;
        break;
    }

    outEasy *= numPlayers;
    outMedium *= numPlayers;
    outHard *= numPlayers;
    outDeadly *= numPlayers;

}

void MainWindow::on_but_calc_clicked()
{
    //qDebug() << "click";
    on_pushButton_clicked();
}

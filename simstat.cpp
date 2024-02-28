#include "simstat.h"
#include "ui_simstat.h"
#include "mainwindow.h"


SimStat::SimStat(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SimStat)
{
    ui->setupUi(this);
}

SimStat::~SimStat()
{
    delete ui;
}

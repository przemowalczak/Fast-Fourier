#ifndef SIMSTAT_H
#define SIMSTAT_H

#include <QMainWindow>

namespace Ui {
class SimStat;
}

class SimStat : public QMainWindow{
    Q_OBJECT


private slots:
    void resizeEvent(QResizeEvent* event);
    //void keyPressEvent(QKeyEvent *event);
    //void keyReleaseEvent(QKeyEvent *event);

public:
    explicit SimStat(QWidget *parent = nullptr);
    ~SimStat();

private:
    Ui::SimStat *ui;
};

#endif // SIMSTAT_H

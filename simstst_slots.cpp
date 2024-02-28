#include "simstat.h"



void SimStat::resizeEvent(QResizeEvent* event){
    QPixmap bkgnd(":/img/img/ancient_one_by_creativeportobello_deyorca-fullview.jpg");
        bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
        QPalette palette;
        palette.setBrush(QPalette::Background, bkgnd);
        this->setPalette(palette);


}

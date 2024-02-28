#include "mainwindow.h"


void MainWindow::init_customPlotLc(string xlabel,string ylabel){
    //cout<<"init_customPlotLc"<<endl;
    setlocale(LC_ALL, "en_US.utf8");
    customPlotLc->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                        QCP::iSelectLegend | QCP::iSelectPlottables | QCP::iMultiSelect);

    customPlotLc->axisRect()->setupFullAxesBox();
    customPlotLc->axisRect()->setAutoMargins(QCP::msLeft|QCP::msRight|QCP::msTop|QCP::msBottom);
    //customPlotLc->axisRect()->setAutoMargins(QCP::msRight|QCP::msTop|QCP::msBottom);

    customPlotLc->setLocale(QLocale::C);

    QPen pen;
    //pen.setStyle(Qt::DotLine);
    pen.setStyle(Qt::SolidLine);
    pen.setWidthF(1);
    pen.setColor(QColor(0, 0, 255));

    QFont lfont("times");
    lfont.setStyleHint(QFont::SansSerif);
    lfont.setPointSize(12);


    /*
    QCPItemText *text= new QCPItemText(customPlotLc);
    text->setText(ylabel.c_str());
    //text->position->setType(QCPItemPosition::ptPlotCoords);
    text->position->setTypeY(QCPItemPosition::ptAxisRectRatio);
    text->position->setTypeX(QCPItemPosition::ptAbsolute);
    //text->position->setType(QCPItemPosition::ptAbsolute);
    text->setPositionAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    text->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    text->setFont(lfont);
    text->setPadding(QMargins(2, 2, 2, 2));;
    text->setClipToAxisRect(false);
    //double y0=customPlotLc->yAxis->range().lower;
    //double ye=customPlotLc->yAxis->range().upper;
    //double y0pixel=customPlotLc->yAxis->coordToPixel(y0);
    //double yepixel=customPlotLc->yAxis->coordToPixel(ye);
    //cout<<"y0="<<y0<<" ye="<<ye<<endl;
    //cout<<"y0="<<y0pixel<<" ye="<<yepixel<<endl;
    //cout<<yepixel+(y0pixel-yepixel)/2.0<<endl;
    //text->position->setCoords(0,yepixel+0.4*(y0pixel-yepixel));
    text->position->setCoords(4,0.38);
    */

    customPlotLc->yAxis->setLabel(ylabel.c_str());


    customPlotLc->xAxis->setLabel(xlabel.c_str());
    //customPlotLc->xAxis->label().toHtmlEscaped();
    //customPlotLc->xAxis->label().resize(26);

    //customPlotLc->xAxis->setRangeReversed(true);


    QFont pfont("times");
    pfont.setStyleHint(QFont::SansSerif);
    pfont.setPointSize(10);
    customPlotLc->xAxis->setTickLabelFont(pfont);
    customPlotLc->yAxis->setTickLabelFont(pfont);
    customPlotLc->xAxis->setSelectedTickLabelFont(pfont);
    customPlotLc->yAxis->setSelectedTickLabelFont(pfont);
    //customPlotLc->axisRect(0)->setMargins(QMargins(100,110,20,0));
    //customPlotLc->axisRect()->insetLayout()->setMinimumMargins(QMargins(500,0,0,0));
    customPlotLc->axisRect()->setMinimumMargins(QMargins(10,10,10,10));

    customPlotLc->xAxis->setLabelFont(lfont);
    customPlotLc->yAxis->setLabelFont(lfont);
    customPlotLc->xAxis->setSelectedLabelFont(lfont);
    customPlotLc->yAxis->setSelectedLabelFont(lfont);
    customPlotLc->yAxis->setTickLabelRotation(0);

    customPlotLc->xAxis->setSubTicks(true);
    //customPlotLc->xAxis->setTickLength(4, 0);
    customPlotLc->xAxis->setBasePen(QPen(Qt::black));
    customPlotLc->xAxis->setTickPen(QPen(Qt::black));
    customPlotLc->xAxis->setSubTickPen(QPen(Qt::black));
    customPlotLc->xAxis->grid()->setVisible(true);
    customPlotLc->xAxis->grid()->setSubGridVisible(false);
    customPlotLc->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    customPlotLc->xAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    customPlotLc->xAxis->setTickLabelColor(Qt::black);
    customPlotLc->xAxis->setLabelColor(Qt::black);
    customPlotLc->xAxis->setPadding(-2); //from bottom to label
    customPlotLc->xAxis->setLabelPadding(-8); //from label to ticks label
    customPlotLc->xAxis->setTickLabelPadding(2); //from ticks label to axis

    customPlotLc->xAxis2->setPadding(0); // a bit more space to the left border
    customPlotLc->xAxis2->setBasePen(QPen(Qt::black));
    customPlotLc->xAxis2->setTickPen(QPen(Qt::black));
    customPlotLc->xAxis2->setSubTickPen(QPen(Qt::black));
    customPlotLc->xAxis2->grid()->setVisible(false);
    customPlotLc->xAxis2->grid()->setSubGridVisible(false);
    customPlotLc->xAxis2->setTickLabelColor(Qt::black);
    customPlotLc->xAxis2->setLabelColor(Qt::black);
    customPlotLc->xAxis2->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    customPlotLc->xAxis2->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));


    // prepare y axis:
    customPlotLc->yAxis->setBasePen(QPen(Qt::black));
    customPlotLc->yAxis->setTickPen(QPen(Qt::black));
    customPlotLc->yAxis->setSubTickPen(QPen(Qt::black));
    customPlotLc->yAxis->grid()->setVisible(true);
    customPlotLc->yAxis->grid()->setSubGridVisible(false);
    customPlotLc->yAxis->setTickLabelColor(Qt::black);
    customPlotLc->yAxis->setLabelColor(Qt::black);
    customPlotLc->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    customPlotLc->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    customPlotLc->yAxis->setPadding(5);

    //customPlotLc->yAxis->setPadding(0); //from left to label
    customPlotLc->yAxis->setLabelPadding(5); //from label to ticks label
    customPlotLc->yAxis->setTickLabelPadding(3); //from ticks label to axis


    customPlotLc->yAxis2->setPadding(0); // a bit more space to the left border
    customPlotLc->yAxis2->setBasePen(QPen(Qt::black));
    customPlotLc->yAxis2->setTickPen(QPen(Qt::black));
    customPlotLc->yAxis2->setSubTickPen(QPen(Qt::black));
    customPlotLc->yAxis2->grid()->setVisible(false);
    customPlotLc->yAxis2->grid()->setSubGridVisible(false);
    customPlotLc->yAxis2->setTickLabelColor(Qt::black);
    customPlotLc->yAxis2->setLabelColor(Qt::black);
    customPlotLc->yAxis2->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    customPlotLc->yAxis2->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    // setup legend:
    customPlotLc->legend->setVisible(true);
    customPlotLc->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignRight);
    customPlotLc->legend->setBrush(QColor(255, 255, 255, 100));
    customPlotLc->legend->setBorderPen(Qt::NoPen);
    //QFont legendFont = font();
    //legendFont.setPointSize(10);
    //_hisPlot->legend->setFont(legendFont);

    // connect slot that ties some axis selections together (especially opposite axes):
    connect(customPlotLc, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChangedLc()));
    // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
    connect(customPlotLc, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePressLc(QMouseEvent*)));
    connect(customPlotLc, SIGNAL(mouseDoubleClick(QMouseEvent*)), this, SLOT(mouseDoubleClickLc(QMouseEvent *)));
    //connect(title, SIGNAL(doubleClicked(QMouseEvent*)), this, SLOT(titleDoubleClick(QMouseEvent*)));

    connect(customPlotLc, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheelLc()));

    // make bottom and left axes transfer their ranges to top and right axes:
    connect(customPlotLc->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlotLc->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlotLc->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlotLc->yAxis2, SLOT(setRange(QCPRange)));

    // connect some interaction slots:
    connect(customPlotLc, SIGNAL(axisDoubleClick(QCPAxis*,QCPAxis::SelectablePart,QMouseEvent*)), this, SLOT(axisLabelDoubleClickLc(QCPAxis*,QCPAxis::SelectablePart)));
        connect(customPlotLc, SIGNAL(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)), this, SLOT(legendDoubleClickLc(QCPLegend*,QCPAbstractLegendItem*)));
    //connect(customPlotLc, SIGNAL(titleDoubleClick(QMouseEvent*)), this, SLOT(titleDoubleClickLc(QMouseEvent*)));

    // connect slot that shows a message in the status bar when a graph is clicked:
    connect(customPlotLc, SIGNAL(plottableClick(QCPAbstractPlottable*,int,QMouseEvent*)), this, SLOT(graphClickedLc(QCPAbstractPlottable*,int)));
    connect(customPlotLc, SIGNAL(plottableDoubleClick(QCPAbstractPlottable*,int,QMouseEvent*)), this, SLOT(graphDoubleClickedLc(QCPAbstractPlottable*,int)));

    connect(customPlotLc, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(onMouseMoveLc(QMouseEvent*)));
    connect(customPlotLc, SIGNAL(mouseRelease(QMouseEvent*)), this, SLOT(mouseReleaseLc(QMouseEvent*)));
    // setup policy and connect slot for context menu popup:
    customPlotLc->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(customPlotLc, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequestLc(QPoint)));


    customPlotLc->replot();

    _init_customPlotLc_ok=true;

}

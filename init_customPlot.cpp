#include "mainwindow.h"


void MainWindow::init_customPlot(string xlabel,string ylabel){
    setlocale(LC_ALL, "en_US.utf8");
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                        QCP::iSelectLegend | QCP::iSelectPlottables | QCP::iMultiSelect);

    customPlot->axisRect()->setupFullAxesBox();
    customPlot->axisRect()->setAutoMargins(QCP::msLeft|QCP::msRight|QCP::msTop|QCP::msBottom);
    //customPlot->axisRect()->setAutoMargins(QCP::msRight|QCP::msTop|QCP::msBottom);

    customPlot->setLocale(QLocale::C);

    QPen pen;
    //pen.setStyle(Qt::DotLine);
    pen.setStyle(Qt::SolidLine);
    pen.setWidthF(1);
    pen.setColor(QColor(0, 0, 255));

    QFont lfont("times");
    lfont.setStyleHint(QFont::SansSerif);
    lfont.setPointSize(18);


    /*
    QCPItemText *text= new QCPItemText(customPlot);
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
    //double y0=customPlot->yAxis->range().lower;
    //double ye=customPlot->yAxis->range().upper;
    //double y0pixel=customPlot->yAxis->coordToPixel(y0);
    //double yepixel=customPlot->yAxis->coordToPixel(ye);
    //cout<<"y0="<<y0<<" ye="<<ye<<endl;
    //cout<<"y0="<<y0pixel<<" ye="<<yepixel<<endl;
    //cout<<yepixel+(y0pixel-yepixel)/2.0<<endl;
    //text->position->setCoords(0,yepixel+0.4*(y0pixel-yepixel));
    text->position->setCoords(4,0.38);
    */

    customPlot->yAxis->setLabel(ylabel.c_str());

    customPlot->xAxis->setLabel(xlabel.c_str());
    //customPlot->xAxis->label().toHtmlEscaped();
    customPlot->xAxis->label().resize(26);

    //customPlot->xAxis->setRangeReversed(true);


    QFont pfont("times");
    pfont.setStyleHint(QFont::SansSerif);
    pfont.setPointSize(12);
    customPlot->xAxis->setTickLabelFont(pfont);
    customPlot->yAxis->setTickLabelFont(pfont);
    customPlot->xAxis->setSelectedTickLabelFont(pfont);
    customPlot->yAxis->setSelectedTickLabelFont(pfont);
    //customPlot->axisRect(0)->setMargins(QMargins(100,110,20,0));
    //customPlot->axisRect()->insetLayout()->setMinimumMargins(QMargins(500,0,0,0));
    customPlot->axisRect()->setMinimumMargins(QMargins(10,10,10,10));

    customPlot->xAxis->setLabelFont(lfont);
    customPlot->yAxis->setLabelFont(lfont);
    customPlot->xAxis->setSelectedLabelFont(lfont);
    customPlot->yAxis->setSelectedLabelFont(lfont);
    customPlot->yAxis->setTickLabelRotation(0);

    customPlot->xAxis->setSubTicks(true);
    //customPlot->xAxis->setTickLength(4, 0);
    customPlot->xAxis->setBasePen(QPen(Qt::black));
    customPlot->xAxis->setTickPen(QPen(Qt::black));
    customPlot->xAxis->setSubTickPen(QPen(Qt::black));
    customPlot->xAxis->grid()->setVisible(true);
    customPlot->xAxis->grid()->setSubGridVisible(false);
    customPlot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    customPlot->xAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    customPlot->xAxis->setTickLabelColor(Qt::black);
    customPlot->xAxis->setLabelColor(Qt::black);
    customPlot->xAxis->setPadding(0); //from bottom to label
    customPlot->xAxis->setLabelPadding(-8); //from label to ticks label
    customPlot->xAxis->setTickLabelPadding(2); //from ticks label to axis

    customPlot->xAxis2->setPadding(0); // a bit more space to the left border
    customPlot->xAxis2->setBasePen(QPen(Qt::black));
    customPlot->xAxis2->setTickPen(QPen(Qt::black));
    customPlot->xAxis2->setSubTickPen(QPen(Qt::black));
    customPlot->xAxis2->grid()->setVisible(false);
    customPlot->xAxis2->grid()->setSubGridVisible(false);
    customPlot->xAxis2->setTickLabelColor(Qt::black);
    customPlot->xAxis2->setLabelColor(Qt::black);
    customPlot->xAxis2->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    customPlot->xAxis2->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));


    // prepare y axis:
    customPlot->yAxis->setBasePen(QPen(Qt::black));
    customPlot->yAxis->setTickPen(QPen(Qt::black));
    customPlot->yAxis->setSubTickPen(QPen(Qt::black));
    customPlot->yAxis->grid()->setVisible(true);
    customPlot->yAxis->grid()->setSubGridVisible(false);
    customPlot->yAxis->setTickLabelColor(Qt::black);
    customPlot->yAxis->setLabelColor(Qt::black);
    customPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    customPlot->yAxis->setPadding(5);

    //customPlot->yAxis->setPadding(0); //from left to label
    customPlot->yAxis->setLabelPadding(5); //from label to ticks label
    customPlot->yAxis->setTickLabelPadding(3); //from ticks label to axis


    customPlot->yAxis2->setPadding(0); // a bit more space to the left border
    customPlot->yAxis2->setBasePen(QPen(Qt::black));
    customPlot->yAxis2->setTickPen(QPen(Qt::black));
    customPlot->yAxis2->setSubTickPen(QPen(Qt::black));
    customPlot->yAxis2->grid()->setVisible(false);
    customPlot->yAxis2->grid()->setSubGridVisible(false);
    customPlot->yAxis2->setTickLabelColor(Qt::black);
    customPlot->yAxis2->setLabelColor(Qt::black);
    customPlot->yAxis2->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    customPlot->yAxis2->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    //customPlot->yAxis->setNumberFormat("eb"); // e = exponential, b = beautiful decimal powers
    //customPlot->yAxis->setNumberPrecision(0); // makes sure "1*10^4" is displayed only as "10^4"

    // setup legend:
    customPlot->legend->setVisible(true);
    customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignRight);
    customPlot->legend->setBrush(QColor(255, 255, 255, 100));
    customPlot->legend->setBorderPen(Qt::NoPen);
    //QFont legendFont = font();
    //legendFont.setPointSize(10);
    //_hisPlot->legend->setFont(legendFont);

    // connect slot that ties some axis selections together (especially opposite axes):
    connect(customPlot, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));
    // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
    connect(customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress(QMouseEvent*)));
    connect(customPlot, SIGNAL(mouseDoubleClick(QMouseEvent*)), this, SLOT(mouseDoubleClick(QMouseEvent *)));
    //connect(title, SIGNAL(doubleClicked(QMouseEvent*)), this, SLOT(titleDoubleClick(QMouseEvent*)));

    connect(customPlot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));

    // make bottom and left axes transfer their ranges to top and right axes:
    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));

    // connect some interaction slots:
    connect(customPlot, SIGNAL(axisDoubleClick(QCPAxis*,QCPAxis::SelectablePart,QMouseEvent*)), this, SLOT(axisLabelDoubleClick(QCPAxis*,QCPAxis::SelectablePart)));
        connect(customPlot, SIGNAL(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)), this, SLOT(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*)));
    //connect(customPlot, SIGNAL(titleDoubleClick(QMouseEvent*)), this, SLOT(titleDoubleClick(QMouseEvent*)));

    // connect slot that shows a message in the status bar when a graph is clicked:
    connect(customPlot, SIGNAL(plottableClick(QCPAbstractPlottable*,int,QMouseEvent*)), this, SLOT(graphClicked(QCPAbstractPlottable*,int)));
    connect(customPlot, SIGNAL(plottableDoubleClick(QCPAbstractPlottable*,int,QMouseEvent*)), this, SLOT(graphDoubleClicked(QCPAbstractPlottable*,int)));

    connect(customPlot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(onMouseMove(QMouseEvent*)));
    connect(customPlot, SIGNAL(mouseRelease(QMouseEvent*)), this, SLOT(mouseRelease(QMouseEvent*)));
    // setup policy and connect slot for context menu popup:
    customPlot->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(customPlot, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));


    customPlot->replot();

    _init_customPlot_ok=true;

}


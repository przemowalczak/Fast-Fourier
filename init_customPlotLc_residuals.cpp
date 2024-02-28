#include "mainwindow.h"


void MainWindow::init_customPlotLc_residuals(string xlabel, string ylabel){
    //cout<<"init_customPlotLc_residuals"<<endl;
    setlocale(LC_ALL, "en_US.utf8");
    customPlotLc_residuals->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                        QCP::iSelectLegend | QCP::iSelectPlottables | QCP::iMultiSelect);

    customPlotLc_residuals->axisRect()->setupFullAxesBox();
    customPlotLc_residuals->axisRect()->setAutoMargins(QCP::msLeft|QCP::msRight|QCP::msTop|QCP::msBottom);
    //customPlotLc_residuals->axisRect()->setAutoMargins(QCP::msRight|QCP::msTop|QCP::msBottom);

    customPlotLc_residuals->setLocale(QLocale::C);

    QPen pen;
    //pen.setStyle(Qt::DotLine);
    pen.setStyle(Qt::SolidLine);
    pen.setWidthF(1);
    pen.setColor(QColor(0, 0, 255));

    QFont lfont("times");
    lfont.setStyleHint(QFont::SansSerif);
    lfont.setPointSize(12);


    /*
    QCPItemText *text= new QCPItemText(customPlotLc_residuals);
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
    //double y0=customPlotLc_residuals->yAxis->range().lower;
    //double ye=customPlotLc_residuals->yAxis->range().upper;
    //double y0pixel=customPlotLc_residuals->yAxis->coordToPixel(y0);
    //double yepixel=customPlotLc_residuals->yAxis->coordToPixel(ye);
    //cout<<"y0="<<y0<<" ye="<<ye<<endl;
    //cout<<"y0="<<y0pixel<<" ye="<<yepixel<<endl;
    //cout<<yepixel+(y0pixel-yepixel)/2.0<<endl;
    //text->position->setCoords(0,yepixel+0.4*(y0pixel-yepixel));
    text->position->setCoords(4,0.38);
    */

    customPlotLc_residuals->yAxis->setLabel(ylabel.c_str());


    customPlotLc_residuals->xAxis->setLabel(xlabel.c_str());
    //customPlotLc_residuals->xAxis->label().toHtmlEscaped();
    //customPlotLc_residuals->xAxis->label().resize(26);

    //customPlotLc_residuals->xAxis->setRangeReversed(true);


    QFont pfont("times");
    pfont.setStyleHint(QFont::SansSerif);
    pfont.setPointSize(10);
    customPlotLc_residuals->xAxis->setTickLabelFont(pfont);
    customPlotLc_residuals->yAxis->setTickLabelFont(pfont);
    customPlotLc_residuals->xAxis->setSelectedTickLabelFont(pfont);
    customPlotLc_residuals->yAxis->setSelectedTickLabelFont(pfont);
    //customPlotLc_residuals->axisRect(0)->setMargins(QMargins(100,110,20,0));
    //customPlotLc_residuals->axisRect()->insetLayout()->setMinimumMargins(QMargins(500,0,0,0));
    customPlotLc_residuals->axisRect()->setMinimumMargins(QMargins(10,10,10,10));

    customPlotLc_residuals->xAxis->setLabelFont(lfont);
    customPlotLc_residuals->yAxis->setLabelFont(lfont);
    customPlotLc_residuals->xAxis->setSelectedLabelFont(lfont);
    customPlotLc_residuals->yAxis->setSelectedLabelFont(lfont);
    customPlotLc_residuals->yAxis->setTickLabelRotation(0);

    customPlotLc_residuals->xAxis->setSubTicks(true);
    //customPlotLc_residuals->xAxis->setTickLength(4, 0);
    customPlotLc_residuals->xAxis->setBasePen(QPen(Qt::black));
    customPlotLc_residuals->xAxis->setTickPen(QPen(Qt::black));
    customPlotLc_residuals->xAxis->setSubTickPen(QPen(Qt::black));
    customPlotLc_residuals->xAxis->grid()->setVisible(true);
    customPlotLc_residuals->xAxis->grid()->setSubGridVisible(false);
    customPlotLc_residuals->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    customPlotLc_residuals->xAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    customPlotLc_residuals->xAxis->setTickLabelColor(Qt::black);
    customPlotLc_residuals->xAxis->setLabelColor(Qt::black);
    customPlotLc_residuals->xAxis->setPadding(-2); //from bottom to label
    customPlotLc_residuals->xAxis->setLabelPadding(-8); //from label to ticks label
    customPlotLc_residuals->xAxis->setTickLabelPadding(2); //from ticks label to axis

    customPlotLc_residuals->xAxis2->setPadding(0); // a bit more space to the left border
    customPlotLc_residuals->xAxis2->setBasePen(QPen(Qt::black));
    customPlotLc_residuals->xAxis2->setTickPen(QPen(Qt::black));
    customPlotLc_residuals->xAxis2->setSubTickPen(QPen(Qt::black));
    customPlotLc_residuals->xAxis2->grid()->setVisible(false);
    customPlotLc_residuals->xAxis2->grid()->setSubGridVisible(false);
    customPlotLc_residuals->xAxis2->setTickLabelColor(Qt::black);
    customPlotLc_residuals->xAxis2->setLabelColor(Qt::black);
    customPlotLc_residuals->xAxis2->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    customPlotLc_residuals->xAxis2->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));


    // prepare y axis:
    customPlotLc_residuals->yAxis->setBasePen(QPen(Qt::black));
    customPlotLc_residuals->yAxis->setTickPen(QPen(Qt::black));
    customPlotLc_residuals->yAxis->setSubTickPen(QPen(Qt::black));
    customPlotLc_residuals->yAxis->grid()->setVisible(true);
    customPlotLc_residuals->yAxis->grid()->setSubGridVisible(false);
    customPlotLc_residuals->yAxis->setTickLabelColor(Qt::black);
    customPlotLc_residuals->yAxis->setLabelColor(Qt::black);
    customPlotLc_residuals->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    customPlotLc_residuals->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    customPlotLc_residuals->yAxis->setPadding(5);

    //customPlotLc_residuals->yAxis->setPadding(0); //from left to label
    customPlotLc_residuals->yAxis->setLabelPadding(5); //from label to ticks label
    customPlotLc_residuals->yAxis->setTickLabelPadding(3); //from ticks label to axis


    customPlotLc_residuals->yAxis2->setPadding(0); // a bit more space to the left border
    customPlotLc_residuals->yAxis2->setBasePen(QPen(Qt::black));
    customPlotLc_residuals->yAxis2->setTickPen(QPen(Qt::black));
    customPlotLc_residuals->yAxis2->setSubTickPen(QPen(Qt::black));
    customPlotLc_residuals->yAxis2->grid()->setVisible(false);
    customPlotLc_residuals->yAxis2->grid()->setSubGridVisible(false);
    customPlotLc_residuals->yAxis2->setTickLabelColor(Qt::black);
    customPlotLc_residuals->yAxis2->setLabelColor(Qt::black);
    customPlotLc_residuals->yAxis2->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    customPlotLc_residuals->yAxis2->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    // setup legend:
    customPlotLc_residuals->legend->setVisible(true);
    customPlotLc_residuals->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignRight);
    customPlotLc_residuals->legend->setBrush(QColor(255, 255, 255, 100));
    customPlotLc_residuals->legend->setBorderPen(Qt::NoPen);
    //QFont legendFont = font();
    //legendFont.setPointSize(10);
    //_hisPlot->legend->setFont(legendFont);

    // connect slot that ties some axis selections together (especially opposite axes):
    connect(customPlotLc_residuals, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChangedLc_residuals()));
    // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
    connect(customPlotLc_residuals, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePressLc_residuals(QMouseEvent*)));
    connect(customPlotLc_residuals, SIGNAL(mouseDoubleClick(QMouseEvent*)), this, SLOT(mouseDoubleClickLc_residuals(QMouseEvent *)));
    //connect(title, SIGNAL(doubleClicked(QMouseEvent*)), this, SLOT(titleDoubleClick(QMouseEvent*)));

    connect(customPlotLc_residuals, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheelLc_residuals()));

    // make bottom and left axes transfer their ranges to top and right axes:
    connect(customPlotLc_residuals->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlotLc_residuals->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlotLc_residuals->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlotLc_residuals->yAxis2, SLOT(setRange(QCPRange)));

    // connect some interaction slots:
    connect(customPlotLc_residuals, SIGNAL(axisDoubleClick(QCPAxis*,QCPAxis::SelectablePart,QMouseEvent*)), this, SLOT(axisLabelDoubleClickLc_residuals(QCPAxis*,QCPAxis::SelectablePart)));
        connect(customPlotLc_residuals, SIGNAL(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)), this, SLOT(legendDoubleClickLc_residuals(QCPLegend*,QCPAbstractLegendItem*)));
    //connect(customPlotLc_residuals, SIGNAL(titleDoubleClick(QMouseEvent*)), this, SLOT(titleDoubleClickLc_residuals(QMouseEvent*)));

    // connect slot that shows a message in the status bar when a graph is clicked:
    connect(customPlotLc_residuals, SIGNAL(plottableClick(QCPAbstractPlottable*,int,QMouseEvent*)), this, SLOT(graphClickedLc_residuals(QCPAbstractPlottable*,int)));
    connect(customPlotLc_residuals, SIGNAL(plottableDoubleClick(QCPAbstractPlottable*,int,QMouseEvent*)), this, SLOT(graphDoubleClickedLc_residuals(QCPAbstractPlottable*,int)));

    connect(customPlotLc_residuals, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(onMouseMoveLc_residuals(QMouseEvent*)));
    connect(customPlotLc_residuals, SIGNAL(mouseRelease(QMouseEvent*)), this, SLOT(mouseReleaseLc_residuals(QMouseEvent*)));
    // setup policy and connect slot for context menu popup:
    customPlotLc_residuals->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(customPlotLc_residuals, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequestLc_residuals(QPoint)));


    customPlotLc_residuals->replot();

    _init_customPlotLc_residuals_ok=true;

}

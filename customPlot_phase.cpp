#include "mainwindow.h"



void MainWindow::get_phase_diagram(){
    if(table->rowCount()>0 && _file.file().size()>0){
           vector<double>freq_i;
           vector<double>freq_all;
           vector<double>A;
           vector<double>phi;

           int ind_freq=-1;
           int ind_status=-1;
           int ind_A=-1;
           int ind_sA=-1;
           int ind_phi=-1;
           int ind_sphi=-1;
           for(auto i=0;i<table->columnCount();++i){
               if(table->horizontalHeaderItem(i)->text()=="status"){
                   ind_status=i;
               }
               if(table->horizontalHeaderItem(i)->text()=="freq"){
                   ind_freq=i;
               }
               if(table->horizontalHeaderItem(i)->text()=="A"){
                   ind_A=i;
               }
               if(table->horizontalHeaderItem(i)->text()=="e_A"){
                   ind_sA=i;
               }
               if(table->horizontalHeaderItem(i)->text()=="phi"){
                   ind_phi=i;
               }
               if(table->horizontalHeaderItem(i)->text()=="e_phi"){
                   ind_sphi=i;
               }

           }
           cout<<"get_phase_diagram: ind_status="<<ind_status<<" ind_freq="<<ind_freq<<endl;
           if(ind_status!=-1 && ind_freq!=-1){
               for(int i=0;i<table->rowCount();++i){
                   freq_all.push_back(table->item(i,ind_freq)->text().toDouble());
                   A.push_back(table->item(i,ind_A)->text().toDouble());
                   phi.push_back(table->item(i,ind_phi)->text().toDouble());
               }
           }
           //cout<<"get_phase_diagram: freq_i="<<freq_i<<" ---"<<freq_i.size()<<endl;
           //cout<<"get_phase_diagram: freq_all="<<freq_all<<" ---"<<freq_all.size()<<endl;

           int nfreq=freq_all.size();
           int n=_file.file().size();

           if(nfreq>1){
             vector<double> fitted_curve;
             fitted_curve.reserve(n);
             for(size_t i=0;i<n;++i){
               double y=_A0;
               for(int j=0;j<nfreq-1;++j){
                  if(i==0) cout<<setprecision(10)<<freq_all[j]<<" "<<A[j]<<" "<<phi[j]<<endl;
                  y+=A[j]*sin(2*M_PI*freq_all[j]*(_file.file()[i][0]-_T0)+phi[j]);
               }
               fitted_curve.push_back(y);
             }

             _residuals_old.clear();
             _residuals_old.reserve(n);
             for(size_t i=0;i<n;++i){
                 _residuals_old.push_back(_file.file()[i][1]-fitted_curve[i]);
             }
           }else{
               _residuals_old=f_get_column(_file.file(),_file.head(),"2");
           }


           if(nfreq>0){
             _phase.clear();
             _phase.reserve(n);
             double freq=freq_all.back();
             for(size_t i=0;i<n;++i){
               _phase.push_back((_file.file()[i][0]-_T0)*freq-floor((_file.file()[i][0]-_T0)*freq));
             }
             //cout<<"phase calculated"<<endl;

             plot_phase_diagram();
           }
    }

}

void MainWindow::show_phase_clicked(){

    if(_init_customPlot_phase){
        pushB_show_phase_diagram->setText("show phase diagram");
        customPlot_phase->clearPlottables();
        for(int i=customPlot_phase->graphCount()-1;i>=0;--i){
            customPlot_phase->removeGraph(i);
        }
        customPlot_phase->deleteLater();
        _init_customPlot_phase=false;
        splitter->widget(2)->deleteLater();
        splitter->setStretchFactor(2,3);
        _ind_graph_lc_phase=-1;
    }else{
        pushB_show_phase_diagram->setText("hide phase diagram");
        customPlot_phase = new QCustomPlot();
        init_customPlot_phase("phase","A");
        splitter->insertWidget(2,customPlot_phase);
        splitter->setStretchFactor(2,1);
        splitter->setStretchFactor(3,3);


        get_phase_diagram();

    }

}

void MainWindow::plot_phase_diagram(){
    if(_init_customPlot_phase){
        size_t n=_file.file().size();
        size_t np=_phase.size();
        if(_residuals_old.size()==0 || _phase.size()==0){
            customPlot_phase->clearPlottables();
            for(int i=customPlot_phase->graphCount()-1;i>=0;--i){
                customPlot_phase->removeGraph(i);
            }
            _ind_graph_lc_phase=-1;
            _residuals_old_ok=false;
            customPlot_phase->replot();
        }else if(n>0 && np==n){

            if(_file.head().size()>=3){
               QVector<double> qx(n);
               QVector<double> qy(n);
               QVector<double> qerr(n);

               _xmin_Lc_phase=_phase[0];
               _xmax_Lc_phase=_phase[0];
               _ymin_Lc_phase=_residuals_old[0];
               _ymax_Lc_phase=_residuals_old[0];
               for(size_t i=0;i<n;++i){
                   qx[i]=_phase[i];
                   qy[i]=_residuals_old[i];
                   qerr[i]=_file.file()[i][2];
                   if(_xmax_Lc_phase<qx[i])_xmax_Lc_phase=qx[i];
                   if(_xmin_Lc_phase>qx[i])_xmin_Lc_phase=qx[i];
                   if(_ymax_Lc_phase<qy[i])_ymax_Lc_phase=qy[i];
                   if(_ymin_Lc_phase>qy[i])_ymin_Lc_phase=qy[i];

               }
               if(_ind_graph_lc_phase==-1){
                   _ind_graph_lc_phase=customPlot_phase->graphCount();
                   customPlot_phase->addGraph();
                   string name="lc";
                   if(customPlot_phase->layer(name.c_str())==nullptr){
                      customPlot_phase->addLayer(name.c_str());
                   }
                   customPlot_phase->graph(_ind_graph_lc_phase)->setLayer(name.c_str());
                   ErrorBars_phase = new QCPErrorBars (customPlot_phase->xAxis, customPlot_phase->yAxis);
              }
              //customPlotLc_residuals->graph(_ind_graph_lc_residuals)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, Qt::blue,QColor(50,200,100), 5));
              customPlot_phase->graph(_ind_graph_lc_phase)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QColor(lc_line_color),QColor(lc_point_color), 5));
              //customPlotLc->graph()->removeFromLegend();
              customPlot_phase->graph(_ind_graph_lc_phase)->addToLegend();
              customPlot_phase->graph(_ind_graph_lc_phase)->setLineStyle(QCPGraph::lsNone);


              //customPlotLc->graph(_ind_graph_lc)->setName(("data, DT="+to_string(_dT)+", 1/DT="+to_string(1/_dT)).c_str());
              customPlot_phase->graph(_ind_graph_lc_phase)->setName("residuals");
              customPlot_phase->graph(_ind_graph_lc_phase)->setSelectable(QCP::stMultipleDataRanges);
              //customPlotLc->graph(_ind_graph_lc)->setSelectable(QCP::stSingleData);


              ErrorBars_phase->setSelectable(QCP::stMultipleDataRanges);
              //ErrorBars->setSelectable(QCP::stNone);
              //ErrorBars->setSelectable(QCP::stSingleData);
              ErrorBars_phase->setData(qerr);
              ErrorBars_phase->removeFromLegend();
              ErrorBars_phase->setErrorType(QCPErrorBars::etValueError);
              ErrorBars_phase->setDataPlottable(customPlot_phase->graph(_ind_graph_lc_phase));
              ErrorBars_phase->setWhiskerWidth(10);
              ErrorBars_phase->setPen(QColor(0, 0, 255));
              ErrorBars_phase->setPen(QColor(lc_line_color));


              QPen selectedpen;
              selectedpen.setStyle(Qt::SolidLine);
              selectedpen.setWidth(3);
              selectedpen.setColor(QColor(180,180,180));
              customPlot_phase->graph(_ind_graph_lc_phase)->setPen(QColor(lc_line_color));
              customPlot_phase->graph(_ind_graph_lc_phase)->selectionDecorator()->setPen(selectedpen);
              customPlot_phase->graph(_ind_graph_lc_phase)->selectionDecorator()->setBrush(QColor(255,0,0,20));
              customPlot_phase->graph(_ind_graph_lc_phase)->selectionDecorator()->setScatterStyle(QCPScatterStyle::ssSquare);
              ErrorBars->selectionDecorator()->setPen(selectedpen);

              customPlot_phase->graph(_ind_graph_lc_phase)->setData(qx,qy);
              customPlot_phase->xAxis->setRange(_xmin_Lc_residuals,_xmax_Lc_residuals);
              customPlot_phase->yAxis->setRange(_ymin_Lc_residuals,_ymax_Lc_residuals);

              QCPLayer *l = customPlot_phase->layer("lc");
              customPlot_phase->moveLayer(l, customPlot_phase->layer(customPlot_phase->layerCount()-1));

              //init_trend();

              customPlot_phase->rescaleAxes();
              customPlot_phase->replot();

            }else{
                QMessageBox *message = new QMessageBox(this);
                message->setText("Wrong numebr of columns. Three are required, HJD, Flux and e_Flux");
                message->exec();
            }
       }else{
            QMessageBox *message = new QMessageBox(this);
            message->setText("Empty file was loaded");
            message->exec();
       }



    }
}


void MainWindow::init_customPlot_phase(string xlabel, string ylabel){
    setlocale(LC_ALL, "en_US.utf8");
    customPlot_phase->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                        QCP::iSelectLegend | QCP::iSelectPlottables | QCP::iMultiSelect);

    customPlot_phase->axisRect()->setupFullAxesBox();
    customPlot_phase->axisRect()->setAutoMargins(QCP::msLeft|QCP::msRight|QCP::msTop|QCP::msBottom);
    //customPlot_phase->axisRect()->setAutoMargins(QCP::msRight|QCP::msTop|QCP::msBottom);

    customPlot_phase->setLocale(QLocale::C);

    QPen pen;
    //pen.setStyle(Qt::DotLine);
    pen.setStyle(Qt::SolidLine);
    pen.setWidthF(1);
    pen.setColor(QColor(0, 0, 255));

    QFont lfont("times");
    lfont.setStyleHint(QFont::SansSerif);
    lfont.setPointSize(18);
    lfont.setPointSize(12);


    /*
    QCPItemText *text= new QCPItemText(customPlot_phase);
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
    //double y0=customPlot_phase->yAxis->range().lower;
    //double ye=customPlot_phase->yAxis->range().upper;
    //double y0pixel=customPlot_phase->yAxis->coordToPixel(y0);
    //double yepixel=customPlot_phase->yAxis->coordToPixel(ye);
    //cout<<"y0="<<y0<<" ye="<<ye<<endl;
    //cout<<"y0="<<y0pixel<<" ye="<<yepixel<<endl;
    //cout<<yepixel+(y0pixel-yepixel)/2.0<<endl;
    //text->position->setCoords(0,yepixel+0.4*(y0pixel-yepixel));
    text->position->setCoords(4,0.38);
    */

    customPlot_phase->yAxis->setLabel(ylabel.c_str());

    customPlot_phase->xAxis->setLabel(xlabel.c_str());
    //customPlot_phase->xAxis->label().toHtmlEscaped();
    customPlot_phase->xAxis->label().resize(26);

    //customPlot_phase->xAxis->setRangeReversed(true);


    QFont pfont("times");
    pfont.setStyleHint(QFont::SansSerif);
    pfont.setPointSize(12);
    pfont.setPointSize(10);
    customPlot_phase->xAxis->setTickLabelFont(pfont);
    customPlot_phase->yAxis->setTickLabelFont(pfont);
    customPlot_phase->xAxis->setSelectedTickLabelFont(pfont);
    customPlot_phase->yAxis->setSelectedTickLabelFont(pfont);
    //customPlot_phase->axisRect(0)->setMargins(QMargins(100,110,20,0));
    //customPlot_phase->axisRect()->insetLayout()->setMinimumMargins(QMargins(500,0,0,0));
    customPlot_phase->axisRect()->setMinimumMargins(QMargins(10,10,10,10));

    customPlot_phase->xAxis->setLabelFont(lfont);
    customPlot_phase->yAxis->setLabelFont(lfont);
    customPlot_phase->xAxis->setSelectedLabelFont(lfont);
    customPlot_phase->yAxis->setSelectedLabelFont(lfont);
    customPlot_phase->yAxis->setTickLabelRotation(0);

    customPlot_phase->xAxis->setSubTicks(true);
    //customPlot_phase->xAxis->setTickLength(4, 0);
    customPlot_phase->xAxis->setBasePen(QPen(Qt::black));
    customPlot_phase->xAxis->setTickPen(QPen(Qt::black));
    customPlot_phase->xAxis->setSubTickPen(QPen(Qt::black));
    customPlot_phase->xAxis->grid()->setVisible(true);
    customPlot_phase->xAxis->grid()->setSubGridVisible(false);
    customPlot_phase->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    customPlot_phase->xAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    customPlot_phase->xAxis->setTickLabelColor(Qt::black);
    customPlot_phase->xAxis->setLabelColor(Qt::black);
    customPlot_phase->xAxis->setPadding(0); //from bottom to label
    customPlot_phase->xAxis->setLabelPadding(-8); //from label to ticks label
    customPlot_phase->xAxis->setTickLabelPadding(2); //from ticks label to axis

    customPlot_phase->xAxis2->setPadding(0); // a bit more space to the left border
    customPlot_phase->xAxis2->setBasePen(QPen(Qt::black));
    customPlot_phase->xAxis2->setTickPen(QPen(Qt::black));
    customPlot_phase->xAxis2->setSubTickPen(QPen(Qt::black));
    customPlot_phase->xAxis2->grid()->setVisible(false);
    customPlot_phase->xAxis2->grid()->setSubGridVisible(false);
    customPlot_phase->xAxis2->setTickLabelColor(Qt::black);
    customPlot_phase->xAxis2->setLabelColor(Qt::black);
    customPlot_phase->xAxis2->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    customPlot_phase->xAxis2->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));


    // prepare y axis:
    customPlot_phase->yAxis->setBasePen(QPen(Qt::black));
    customPlot_phase->yAxis->setTickPen(QPen(Qt::black));
    customPlot_phase->yAxis->setSubTickPen(QPen(Qt::black));
    customPlot_phase->yAxis->grid()->setVisible(true);
    customPlot_phase->yAxis->grid()->setSubGridVisible(false);
    customPlot_phase->yAxis->setTickLabelColor(Qt::black);
    customPlot_phase->yAxis->setLabelColor(Qt::black);
    customPlot_phase->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    customPlot_phase->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    customPlot_phase->yAxis->setPadding(5);

    //customPlot_phase->yAxis->setPadding(0); //from left to label
    customPlot_phase->yAxis->setLabelPadding(5); //from label to ticks label
    customPlot_phase->yAxis->setTickLabelPadding(3); //from ticks label to axis


    customPlot_phase->yAxis2->setPadding(0); // a bit more space to the left border
    customPlot_phase->yAxis2->setBasePen(QPen(Qt::black));
    customPlot_phase->yAxis2->setTickPen(QPen(Qt::black));
    customPlot_phase->yAxis2->setSubTickPen(QPen(Qt::black));
    customPlot_phase->yAxis2->grid()->setVisible(false);
    customPlot_phase->yAxis2->grid()->setSubGridVisible(false);
    customPlot_phase->yAxis2->setTickLabelColor(Qt::black);
    customPlot_phase->yAxis2->setLabelColor(Qt::black);
    customPlot_phase->yAxis2->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    customPlot_phase->yAxis2->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    //customPlot_phase->yAxis->setNumberFormat("eb"); // e = exponential, b = beautiful decimal powers
    //customPlot_phase->yAxis->setNumberPrecision(0); // makes sure "1*10^4" is displayed only as "10^4"

    // setup legend:
    customPlot_phase->legend->setVisible(true);
    customPlot_phase->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignRight);
    customPlot_phase->legend->setBrush(QColor(255, 255, 255, 100));
    customPlot_phase->legend->setBorderPen(Qt::NoPen);
    //QFont legendFont = font();
    //legendFont.setPointSize(10);
    //_hisPlot->legend->setFont(legendFont);

    // connect slot that ties some axis selections together (especially opposite axes):
    connect(customPlot_phase, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChangedLc_phase()));
    // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
    connect(customPlot_phase, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePressLc_phase(QMouseEvent*)));
    connect(customPlot_phase, SIGNAL(mouseDoubleClick(QMouseEvent*)), this, SLOT(mouseDoubleClickLc_phase(QMouseEvent *)));
    //connect(title, SIGNAL(doubleClicked(QMouseEvent*)), this, SLOT(titleDoubleClick(QMouseEvent*)));

    connect(customPlot_phase, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheelLc_phase()));

    // make bottom and left axes transfer their ranges to top and right axes:
    connect(customPlot_phase->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot_phase->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot_phase->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot_phase->yAxis2, SLOT(setRange(QCPRange)));

    // connect some interaction slots:
    connect(customPlot_phase, SIGNAL(axisDoubleClick(QCPAxis*,QCPAxis::SelectablePart,QMouseEvent*)), this, SLOT(axisLabelDoubleClickLc_phase(QCPAxis*,QCPAxis::SelectablePart)));
        connect(customPlot_phase, SIGNAL(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)), this, SLOT(legendDoubleClickLc_phase(QCPLegend*,QCPAbstractLegendItem*)));
    //connect(customPlot_phase, SIGNAL(titleDoubleClick(QMouseEvent*)), this, SLOT(titleDoubleClick(QMouseEvent*)));

    // connect slot that shows a message in the status bar when a graph is clicked:
    connect(customPlot_phase, SIGNAL(plottableClick(QCPAbstractPlottable*,int,QMouseEvent*)), this, SLOT(graphClickedLc_phase(QCPAbstractPlottable*,int)));
    connect(customPlot_phase, SIGNAL(plottableDoubleClick(QCPAbstractPlottable*,int,QMouseEvent*)), this, SLOT(graphDoubleClickedLc_phase(QCPAbstractPlottable*,int)));

    connect(customPlot_phase, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(onMouseMoveLc_phase(QMouseEvent*)));
    connect(customPlot_phase, SIGNAL(mouseRelease(QMouseEvent*)), this, SLOT(mouseReleaseLc_phase(QMouseEvent*)));
    // setup policy and connect slot for context menu popup:
    customPlot_phase->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(customPlot_phase, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequestLc_phase(QPoint)));


    customPlot_phase->replot();

    _init_customPlot_phase=true;

}




void MainWindow::titleDoubleClickLc_phase(QMouseEvent* event)
{
    Q_UNUSED(event)
            if (QCPTextElement *title = qobject_cast<QCPTextElement*>(sender())){
                // Set the plot title by double clicking on it
                bool ok;
                QString newTitle = QInputDialog::getText(this, "QcustomPlot_phase example", "New plot title:", QLineEdit::Normal, "", &ok);
                if (ok){
                    string s=newTitle.toUtf8().constData();
                    QString newTitle2="multiplier="+newTitle;
                    title->setText(newTitle2);

                            customPlot_phase->replot();
                }
            }
             cout<<"titleDoubleClick"<<endl;
}


void MainWindow::axisLabelDoubleClickLc_phase(QCPAxis *axis, QCPAxis::SelectablePart part){
  // Set an axis label by double clicking on it
  if (part == QCPAxis::spAxisLabel){ // only react when the actual axis label is clicked, not tick label or axis backbone
    bool ok;
    QString newLabel = QInputDialog::getText(this, "QcustomPlot_phase example", "New axis label:", QLineEdit::Normal, axis->label(), &ok);
    if (ok){
      axis->setLabel(newLabel);
              customPlot_phase->replot();
    }
  }
    cout<<"axisLabelDoubleClick"<<endl;
}




void MainWindow::legendDoubleClickLc_phase(QCPLegend *legend, QCPAbstractLegendItem *item){
  // Rename a graph by double clicking on its legend item
  Q_UNUSED(legend)
  if (item){ // only react if item was clicked (user could have clicked on border padding of legend where there is no item, then item is 0)
    QCPPlottableLegendItem *plItem = qobject_cast<QCPPlottableLegendItem*>(item);
    bool ok;
    QString newName = QInputDialog::getText(this, "QcustomPlot_phase example", "New graph name:", QLineEdit::Normal, plItem->plottable()->name(), &ok);
    if (ok){
      plItem->plottable()->setName(newName);
             customPlot_phase->replot();
    }
  }
  cout<<"legendDoubleClick"<<endl;

}




void MainWindow::selectionChangedLc_phase(){

    cout<<"selectionChanged"<<endl;

  /*
   normally, axis base line, axis tick labels and axis labels are selectable separately, but we want
   the user only to be able to select the axis as a whole, so we tie the selected states of the tick labels
   and the axis base line together. However, the axis label shall be selectable individually.

   The selection state of the left and right axes shall be synchronized as well as the state of the
   bottom and top axes.

   Further, we want to synchronize the selection of the graphs with the selection state of the respective
   legend item belonging to that graph. So the user can select a graph by either clicking on the graph itself
   or on its legend item.
  */

  // make top and bottom axes be selected synchronously, and handle axis and tick labels as one selectable object:

           if (customPlot_phase->xAxis->selectedParts().testFlag(QCPAxis::spAxis) || customPlot_phase->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
               customPlot_phase->xAxis2->selectedParts().testFlag(QCPAxis::spAxis) || customPlot_phase->xAxis2->selectedParts().testFlag(QCPAxis::spTickLabels)){
                   customPlot_phase->xAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
                   customPlot_phase->xAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
           }
           // make left and right axes be selected synchronously, and handle axis and tick labels as one selectable object:
           if (customPlot_phase->yAxis->selectedParts().testFlag(QCPAxis::spAxis) || customPlot_phase->yAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
               customPlot_phase->yAxis2->selectedParts().testFlag(QCPAxis::spAxis) || customPlot_phase->yAxis2->selectedParts().testFlag(QCPAxis::spTickLabels)){
                   customPlot_phase->yAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
                   customPlot_phase->yAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
           }

           // synchronize selection of graphs with selection of corresponding legend items:

           for (int i=0; i<customPlot_phase->graphCount(); ++i){
               //cout<<"I="<<i<<endl;
               QCPGraph *graph = customPlot_phase->graph(i);

               QCPPlottableLegendItem *item = customPlot_phase->legend->itemWithPlottable(graph);
               /*
               if (item->selected() || graph->selected() || ErrorBarsx[i]->selected() || ErrorBarsy[i]->selected()){
                   cout<<"graph or legent = "<<i<<endl;
                   item->setSelected(true);
                   graph->setSelection(QCPDataSelection(graph->data()->dataRange()));
                   //ErrorBarsx->setSelection(QCPDataSelection(ErrorBarsx->dataValueRange(0)));
                   //QCPDataSelection selection=ErrorBarsx->selectTestRect();
                   ErrorBarsx[i]->setSelection(QCPDataSelection(QCPDataRange(0,ErrorBarsx[i]->dataCount())));
                   ErrorBarsy[i]->setSelection(QCPDataSelection(QCPDataRange(0,ErrorBarsy[i]->dataCount())));

               }//*/
           }//*/

           /*if(ErrorBarsx->selected()){
              cout<<"Errorbars selected"<<endl;
              /*QCPDataSelection selection = ErrorBarsy->selection() ;
              QCPDataRange datarange;
              datarange.setBegin(0);
              datarange.setEnd(ErrorBarsy->dataCount());
              cout<<"ErrorBarsy->dataCount()="<<ErrorBarsy->dataCount()<<endl;
              //selection.addDataRange(datarange);
              selection.addDataRange(QCPDataRange(0,ErrorBarsy->dataCount()));

              //ErrorBarsy->setSelection(selection);
              ErrorBarsy->setSelection(QCPDataSelection(QCPDataRange(0,ErrorBarsy->dataCount())));
           }*/



                   _key_selected.clear();
                   _value_selected.clear();

                   if(customPlot_phase->graphCount()>0){

                      QCPDataSelection selection = customPlot_phase->graph(0)->selection();
                      double sum = 0;
                      foreach (QCPDataRange dataRange, selection.dataRanges()){
                        //cout<<dataRange.begin()<<endl;
                        QCPGraphDataContainer::const_iterator begin = customPlot_phase->graph(0)->data()->at(dataRange.begin()); // get range begin iterator from index
                        QCPGraphDataContainer::const_iterator end = customPlot_phase->graph(0)->data()->at(dataRange.end()); // get range end iterator from index
                        for (QCPGraphDataContainer::const_iterator it=begin; it!=end; ++it){
                          // iterator "it" will go through all selected data points, as an example, we calculate the value average
                          //sum += it->value;
                          _value_selected.push_back(it->value);
                          _key_selected.push_back(it->key);
                        }
                      }
                    }
}


void MainWindow::mousePressLc_phase(QMouseEvent* event){
  // if an axis is selected, only allow the direction of that axis to be dragged
  // if no axis is selected, both directions may be dragged

            bool axis_set_on=false;
            if (customPlot_phase->xAxis->selectedParts().testFlag(QCPAxis::spAxis)){
                customPlot_phase->axisRect()->setRangeDrag(customPlot_phase->xAxis->orientation());
                axis_set_on=true;
            }else if (customPlot_phase->yAxis->selectedParts().testFlag(QCPAxis::spAxis)){
                customPlot_phase->axisRect()->setRangeDrag(customPlot_phase->yAxis->orientation());
                axis_set_on=true;
            }else{
                customPlot_phase->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
            }
            double xCoord = customPlot_phase->xAxis->pixelToCoord(event->pos().x());
            double yCoord = customPlot_phase->yAxis->pixelToCoord(event->pos().y());
            //cout<<"add plot: mouse move, click on: xCoord="<<xCoord<<" yCoord="<<yCoord<<endl;

}



void MainWindow::mouseDoubleClickLc_phase(QMouseEvent* event){

    //double x=event->pos().x();
    //cout<<"mouseDoubleClick pres"<<x<<endl;


            double xCoord = customPlot_phase->xAxis->pixelToCoord(event->pos().x());
            double yCoord = customPlot_phase->yAxis->pixelToCoord(event->pos().y());

            QString message = QString("Clicked at data point #%1 with value %2.").arg(xCoord).arg(yCoord);
            //ui->statusBar->showMessage(message, 25000);

            //cout<<"mouseDoubleClick: xCoord="<<xCoord<<" yCoord="<<yCoord<<endl;
            QString str=QString{"%1"}.arg(xCoord);

            customPlot_phase->rescaleAxes();
            customPlot_phase->replot();

}

void MainWindow::mouseWheelLc_phase(){
  // if an axis is selected, only allow the direction of that axis to be zoomed
  // if no axis is selected, both directions may be zoomed

  //cout<<"mouseWheel"<<endl;

           if (customPlot_phase->xAxis->selectedParts().testFlag(QCPAxis::spAxis)){
              customPlot_phase->axisRect()->setRangeZoom(customPlot_phase->xAxis->orientation());
              //customPlot_phase->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
              //cout<<"xAxis"<<endl;
           }else if (customPlot_phase->yAxis->selectedParts().testFlag(QCPAxis::spAxis)){
              customPlot_phase->axisRect()->setRangeZoom(customPlot_phase->yAxis->orientation());
              //cout<<"yAxis"<<endl;
           } else{
              customPlot_phase->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
              //customPlot_phase->axisRect()->setRangeZoom(customPlot_phase->xAxis->orientation());
              //customPlot_phase->axisRect()->setRangeZoom(customPlot_phase->yAxis->orientation());
              //cout<<"zoom"<<endl;

           }


}


void MainWindow::removeSelectedGraphLc_phase(){
  cout<<"removeSelectedGraph"<<endl;


  //QList<QCPGraph*>  qlist=customPlot_phase[0]->selectedGraphs ( );
  //if(qlist.empty()){
  //    cout<<"no graph selected"<<endl;
  //}else{
     //cout<<"some graph is selected"<<endl;
   //  for(auto it=qlist.begin();it!=qlist.end();++it){
         //cout<<*it<<endl;
         //if(*it==customPlot_phase[0]->graph(0)){
         //    cout<<"the grapth(0) was selected"<<endl;
         //}
   //  }

  //}



}

void MainWindow::removeAllGraphsLc_phase(){
           customPlot_phase->clearGraphs();
           customPlot_phase->replot();



}



void MainWindow::contextMenuRequestLc_phase(QPoint pos){
  QMenu *menu = new QMenu(this);
  //menu = new QMenu(add_plot_plot_dialog);
  //QMenu *menu = new QMenu(this);
  menu->setAttribute(Qt::WA_DeleteOnClose);

         if (false && customPlot_phase->legend->selectTest(pos, false) >= 0){
            menu->addAction("Move to top left", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignLeft));
            menu->addAction("Move to top center", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignHCenter));
            menu->addAction("Move to top right", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignRight));
            menu->addAction("Move to bottom right", this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignRight));
            menu->addAction("Move to bottom left", this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignLeft));
         }else if(customPlot_phase->xAxis->selectTest(pos,false)>=0){
            menu->addAction("Reverse x axis", this, SLOT(reverse_xAxis()));
         }else if(customPlot_phase->yAxis->selectTest(pos,false)>=0){
            menu->addAction("Reverse y axis", this, SLOT(reverse_yAxis()));
         }else{
            menu->addAction("Save phase to pdf", this, SLOT(savepdfLc_phase()));
            menu->addAction("Save phase to data file", this, SLOT(phase_save_phase()));
            if(_key_selected.size()>0){
               menu->addAction("clear selected data", this, SLOT(clear_selected_dataLc_phase()));
            }
            menu->addAction("remove selected data",this, SLOT(remove_selected_dataLc_phase()));
            /*if(!constant_border){
                menu->addAction("set constant margins",this, SLOT(set_constant_border()));
            }else{
                menu->addAction("set dynamic margins",this, SLOT(set_dynamic_border()));
            }*/
            //menu->addAction("rescale", this, SLOT(rescale()));


         }

         QList<QCPGraph*>  qlist=customPlot_phase->selectedGraphs ( );
         if(qlist.empty()){
             //cout<<"no graph selected"<<endl;
         }else{
             //cout<<"some graph is selected"<<endl;
             for(auto it=qlist.begin();it!=qlist.end();++it){
                //cout<<*it<<endl;
                for(int i=0;i<customPlot_phase->graphCount();++i){
                   if(*it==customPlot_phase->graph(i)){
                      //cout<<"the grapth("<<i<<") was selected"<<endl;
                      //menu->addAction("remove noise", this, SLOT(removenoise()));
                   }
                }
             }

         }

         menu->popup(customPlot_phase->mapToGlobal(pos));

}


void MainWindow::phase_save_phase(){
    int n=table->rowCount();
    size_t nlc=_file.file().size();
    if(_phase.size()==nlc){
        string input_file_name=_file.file_name();
        input_file_name=f_remove_ext(input_file_name);
        string name=input_file_name+"_data_phase_n"+to_string(n);
        ofstream fo{name};
        for(size_t i=0;i<nlc;++i){
           fo<<_phase[i]<<" "<<_residuals_old[i]<<" "<<_file.file()[i][2]<<endl;
        }
    }
}

bool existpdflc_phase (const std::string& name) {
   return ( access( name.c_str(), F_OK ) != -1 );
}

void MainWindow::remove_selected_dataLc_phase(){
    cout<<"removing selected data"<<endl;
    /*
    if(_ind_graph_lc>=0){
      QCPDataSelection selection = customPlot_phase->graph(_ind_graph_lc)->selection();
      double sum = 0;
      data_for_removing_x.clear();
      data_for_removing_y.clear();
      foreach (QCPDataRange dataRange, selection.dataRanges()){
        QCPGraphDataContainer::const_iterator begin = customPlot_phase->graph(_ind_graph_lc)->data()->at(dataRange.begin()); // get range begin iterator from index
        QCPGraphDataContainer::const_iterator end = customPlot_phase->graph(_ind_graph_lc)->data()->at(dataRange.end()); // get range end iterator from index
        for (QCPGraphDataContainer::const_iterator it=begin; it!=end; ++it){
           // iterator "it" will go through all selected data points, as an example, we calculate the value average
           sum += it->value;
           data_for_removing_x.push_back(it->key);
           data_for_removing_y.push_back(it->value);
        }
      }
      double average = sum/selection.dataPointCount();
      customPlot_phase->graph(_ind_graph_lc)->setSelection(QCPDataSelection(QCPDataRange()));
      cout<<"removed from file ok"<<endl;

          string newname=f_remove_ext(_file.file_name())+"_modif.dat";

          if(data_for_removing_x.size()>0){
             //this is highly inefficient, to improve in a future
             for(size_t i=0;i<_file.file().size();++i){
                 if(present(data_for_removing_x,_file.file()[i][0]) &&  present(data_for_removing_y,_file.file()[i][1]) ){
                    _file.file().erase(_file.file().begin()+i);
                    --i;
                 }
             }
             if(_init_customPlot_phase_ok){
                 plot_lc();
             }
          }


   }
   */

}

void MainWindow::clear_selected_dataLc_phase(){
    _key_selected.clear();
    _value_selected.clear();
    customPlot_phase->deselectAll();
    customPlot_phase->replot();
}


void MainWindow::reverse_xAxisLc_phase(){
    //cout<<"reversed = "<<customPlot_phase->xAxis->rangeReversed()<<endl;
    if(customPlot_phase->xAxis->rangeReversed()){
        customPlot_phase->xAxis->setRangeReversed(false);
        xrplot=false;
    }else{
        customPlot_phase->xAxis->setRangeReversed(true);
        xrplot=true;
    }
    customPlot_phase->replot();
}

void MainWindow::reverse_yAxisLc_phase(){
   //cout<<"reversed = "<<customPlot_phase->yAxis->rangeReversed()<<endl;
   if(customPlot_phase->yAxis->rangeReversed()){
       customPlot_phase->yAxis->setRangeReversed(false);
       yrplot=false;
   }else{
       customPlot_phase->yAxis->setRangeReversed(true);
       yrplot=true;
   }
   customPlot_phase->replot();
}



void MainWindow::savepdfLc_phase(){
  if(_ind_graph_lc_phase!=-1 && _init_customPlot_phase){
    //cout<<"saving pdf"<<endl;

    /*bool ok;
    QString name="file.pdf";
    QString newTitle = QInputDialog::getText(this, "write", "New plot title:", QLineEdit::Normal, "", &ok);
    cout<<"ok="<<ok<<" newtitle="<<newTitle.toStdString()<< endl;
    if (ok){
       name=newTitle;
    }
    */

    //string path=f_get_path_from_file_name(_fname);
    //string name="ap_"+_x_col+"_vs_"+_y_col+".pdf";
    int n=table->rowCount();
    string input_file_name=_file.file_name();
    input_file_name=f_remove_ext(input_file_name);
    string name=input_file_name+"_data_phase_n"+to_string(n)+".pdf";


    //f_replace(name,"/","");
    f_replace(name,"\\","");
    f_replace(name,"&","");
    f_replace(name,"$","");
    f_replace(name,"#","");
    //name=path+name;
    //cout<<"saving in a file = "<<name<<endl;


    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);


    //cout<<"printer.pageRect().width()="<<printer.pageRect().width()<<endl;
    //cout<<"customPlot_phase[i]->width()="<<customPlot_phase[i]->width()<<endl;
    //double xscale = printer.pageRect().width() / double(customPlot_phase[i]->width());
    //double yscale = printer.pageRect().height() / double(customPlot_phase[i]->height());
    //customPlot_phase[i]->savePdf(name.c_str(), customPlot_phase[i]->width(), customPlot_phase[i]->height() );
    //customPlot_phase[i]->savePdf(name.c_str(), printer.pageRect().width()/2, printer.pageRect().width()/2 );

    customPlot_phase->savePdf(name.c_str(), 800, 500 );
    customPlot_phase->replot();

    QString message = QString(("saving to pdf = "+name).c_str());
    this->statusBar()->showMessage(message, 0);

    label_info_fitting->setText(label_info_fitting2->text());
    string text;
    text="<font color="+NLSF_info_color_font.toStdString()+">pdf: saving to "+name;
    label_info_fitting2->setText(text.c_str());
  }
}



void MainWindow::moveLegendLc_phase()
{
  if (QAction* contextAction = qobject_cast<QAction*>(sender())) // make sure this slot is really called by a context menu action, so it carries the data we need
  {
    bool ok;
    int dataInt = contextAction->data().toInt(&ok);
    if (ok){

                customPlot_phase->axisRect()->insetLayout()->setInsetAlignment(0, (Qt::Alignment)dataInt);
                customPlot_phase->replot();


    }
  }
}

void MainWindow::graphClickedLc_phase(QCPAbstractPlottable *plottable, int dataIndex)
{
  // since we know we only have QCPGraphs in the plot, we can immediately access interface1D()
  // usually it's better to first check whether interface1D() returns non-zero, and only then use it.
  double dataValue = plottable->interface1D()->dataMainValue(dataIndex);
  double dataKey = plottable->interface1D()->dataSortKey(dataIndex);
  QString message = QString("Clicked on graph '%1' at x= %2, y= %3.").arg(plottable->name()).arg(dataKey).arg(dataValue);
  this->statusBar()->showMessage(message, 0);


  double xCoord=0, yCoord=0;

         QList<QCPGraph*>  qlist=customPlot_phase->selectedGraphs ( );
         size_t  n=customPlot_phase->graphCount();
         if(qlist.empty()){
              cout<<"no graph selected"<<endl;
         }else{
             cout<<"some graph is selected"<<endl;
             for(auto it=qlist.begin();it!=qlist.end();++it){
                  //cout<<*it<<endl;
                  for(int j=0;j<n;++j){
                     if(*it==customPlot_phase->graph(j)){
                         //cout<<"the graph "<<j<<" was selected"<<endl;
                     }
                  }
             }
        }

}


void MainWindow::graphDoubleClickedLc_phase(QCPAbstractPlottable *plottable, int dataIndex)
{
  // since we know we only have QCPGraphs in the plot, we can immediately access interface1D()
  // usually it's better to first check whether interface1D() returns non-zero, and only then use it.
  double dataValue = plottable->interface1D()->dataMainValue(dataIndex);
  double dataKey = plottable->interface1D()->dataSortKey(dataIndex);
  QString message = QString("Clicked on graph '%1' at x= %2, y= %3.").arg(plottable->name()).arg(dataKey).arg(dataValue);
  this->statusBar()->showMessage(message, 0);

  //cout<<"graphDoubleClicked: dataindex="<<dataIndex<<" dataKey="<<dataKey<<" dataValue="<<dataValue<<endl;

}




void MainWindow::onMouseMoveLc_phase(QMouseEvent *event){
    double xCoord=0, yCoord=0;
           xCoord = customPlot_phase->xAxis->pixelToCoord(event->pos().x());
           yCoord = customPlot_phase->yAxis->pixelToCoord(event->pos().y());


    QString message = QString("%1, %2")
            .arg(xCoord).arg(yCoord);

   //ui->statusBar->setStyleSheet("QStatusBar{color:red}") if needed
    this->statusBar()->setStyleSheet("color: orange");
    this->statusBar()->showMessage(message, 0);

}



void MainWindow::mouseReleaseLc_phase(QMouseEvent* event ){
    //cout<<"add plot: mouse release"<<endl;
    /*
          double xCoord = customPlot_phase->xAxis->pixelToCoord(event->pos().x());
          double yCoord = customPlot_phase->yAxis->pixelToCoord(event->pos().y());
          double xCoord_pix = event->pos().x();
          double yCoord_pix = event->pos().y();
    */

}




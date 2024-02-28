#include "mainwindow.h"




void MainWindow::init_customPlot_simulation(string xlabel, string ylabel){
    setlocale(LC_ALL, "en_US.utf8");
    customPlot_simulation->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                        QCP::iSelectLegend | QCP::iSelectPlottables | QCP::iMultiSelect);

    customPlot_simulation->axisRect()->setupFullAxesBox();
    customPlot_simulation->axisRect()->setAutoMargins(QCP::msLeft|QCP::msRight|QCP::msTop|QCP::msBottom);
    //customPlot_simulation->axisRect()->setAutoMargins(QCP::msRight|QCP::msTop|QCP::msBottom);

    customPlot_simulation->setLocale(QLocale::C);

    QPen pen;
    //pen.setStyle(Qt::DotLine);
    pen.setStyle(Qt::SolidLine);
    pen.setWidthF(1);
    pen.setColor(QColor(0, 0, 255));

    QFont lfont("times");
    lfont.setStyleHint(QFont::SansSerif);
    lfont.setPointSize(18);


    /*
    QCPItemText *text= new QCPItemText(customPlot_simulation);
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
    //double y0=customPlot_simulation->yAxis->range().lower;
    //double ye=customPlot_simulation->yAxis->range().upper;
    //double y0pixel=customPlot_simulation->yAxis->coordToPixel(y0);
    //double yepixel=customPlot_simulation->yAxis->coordToPixel(ye);
    //cout<<"y0="<<y0<<" ye="<<ye<<endl;
    //cout<<"y0="<<y0pixel<<" ye="<<yepixel<<endl;
    //cout<<yepixel+(y0pixel-yepixel)/2.0<<endl;
    //text->position->setCoords(0,yepixel+0.4*(y0pixel-yepixel));
    text->position->setCoords(4,0.38);
    */

    customPlot_simulation->yAxis->setLabel(ylabel.c_str());

    customPlot_simulation->xAxis->setLabel(xlabel.c_str());
    //customPlot_simulation->xAxis->label().toHtmlEscaped();
    customPlot_simulation->xAxis->label().resize(26);

    //customPlot_simulation->xAxis->setRangeReversed(true);


    QFont pfont("times");
    pfont.setStyleHint(QFont::SansSerif);
    pfont.setPointSize(12);
    customPlot_simulation->xAxis->setTickLabelFont(pfont);
    customPlot_simulation->yAxis->setTickLabelFont(pfont);
    customPlot_simulation->xAxis->setSelectedTickLabelFont(pfont);
    customPlot_simulation->yAxis->setSelectedTickLabelFont(pfont);
    //customPlot_simulation->axisRect(0)->setMargins(QMargins(100,110,20,0));
    //customPlot_simulation->axisRect()->insetLayout()->setMinimumMargins(QMargins(500,0,0,0));
    customPlot_simulation->axisRect()->setMinimumMargins(QMargins(10,10,10,10));

    customPlot_simulation->xAxis->setLabelFont(lfont);
    customPlot_simulation->yAxis->setLabelFont(lfont);
    customPlot_simulation->xAxis->setSelectedLabelFont(lfont);
    customPlot_simulation->yAxis->setSelectedLabelFont(lfont);
    customPlot_simulation->yAxis->setTickLabelRotation(0);

    customPlot_simulation->xAxis->setSubTicks(true);
    //customPlot_simulation->xAxis->setTickLength(4, 0);
    customPlot_simulation->xAxis->setBasePen(QPen(Qt::black));
    customPlot_simulation->xAxis->setTickPen(QPen(Qt::black));
    customPlot_simulation->xAxis->setSubTickPen(QPen(Qt::black));
    customPlot_simulation->xAxis->grid()->setVisible(true);
    customPlot_simulation->xAxis->grid()->setSubGridVisible(false);
    customPlot_simulation->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    customPlot_simulation->xAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    customPlot_simulation->xAxis->setTickLabelColor(Qt::black);
    customPlot_simulation->xAxis->setLabelColor(Qt::black);
    customPlot_simulation->xAxis->setPadding(0); //from bottom to label
    customPlot_simulation->xAxis->setLabelPadding(-8); //from label to ticks label
    customPlot_simulation->xAxis->setTickLabelPadding(2); //from ticks label to axis

    customPlot_simulation->xAxis2->setPadding(0); // a bit more space to the left border
    customPlot_simulation->xAxis2->setBasePen(QPen(Qt::black));
    customPlot_simulation->xAxis2->setTickPen(QPen(Qt::black));
    customPlot_simulation->xAxis2->setSubTickPen(QPen(Qt::black));
    customPlot_simulation->xAxis2->grid()->setVisible(false);
    customPlot_simulation->xAxis2->grid()->setSubGridVisible(false);
    customPlot_simulation->xAxis2->setTickLabelColor(Qt::black);
    customPlot_simulation->xAxis2->setLabelColor(Qt::black);
    customPlot_simulation->xAxis2->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    customPlot_simulation->xAxis2->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));


    // prepare y axis:
    customPlot_simulation->yAxis->setBasePen(QPen(Qt::black));
    customPlot_simulation->yAxis->setTickPen(QPen(Qt::black));
    customPlot_simulation->yAxis->setSubTickPen(QPen(Qt::black));
    customPlot_simulation->yAxis->grid()->setVisible(true);
    customPlot_simulation->yAxis->grid()->setSubGridVisible(false);
    customPlot_simulation->yAxis->setTickLabelColor(Qt::black);
    customPlot_simulation->yAxis->setLabelColor(Qt::black);
    customPlot_simulation->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    customPlot_simulation->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    customPlot_simulation->yAxis->setPadding(5);

    //customPlot_simulation->yAxis->setPadding(0); //from left to label
    customPlot_simulation->yAxis->setLabelPadding(5); //from label to ticks label
    customPlot_simulation->yAxis->setTickLabelPadding(3); //from ticks label to axis


    customPlot_simulation->yAxis2->setPadding(0); // a bit more space to the left border
    customPlot_simulation->yAxis2->setBasePen(QPen(Qt::black));
    customPlot_simulation->yAxis2->setTickPen(QPen(Qt::black));
    customPlot_simulation->yAxis2->setSubTickPen(QPen(Qt::black));
    customPlot_simulation->yAxis2->grid()->setVisible(false);
    customPlot_simulation->yAxis2->grid()->setSubGridVisible(false);
    customPlot_simulation->yAxis2->setTickLabelColor(Qt::black);
    customPlot_simulation->yAxis2->setLabelColor(Qt::black);
    customPlot_simulation->yAxis2->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    customPlot_simulation->yAxis2->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    //customPlot_simulation->yAxis->setNumberFormat("eb"); // e = exponential, b = beautiful decimal powers
    //customPlot_simulation->yAxis->setNumberPrecision(0); // makes sure "1*10^4" is displayed only as "10^4"

    // setup legend:
    customPlot_simulation->legend->setVisible(true);
    customPlot_simulation->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignRight);
    customPlot_simulation->legend->setBrush(QColor(255, 255, 255, 100));
    customPlot_simulation->legend->setBorderPen(Qt::NoPen);
    //QFont legendFont = font();
    //legendFont.setPointSize(10);
    //_hisPlot->legend->setFont(legendFont);

    // connect slot that ties some axis selections together (especially opposite axes):
    connect(customPlot_simulation, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged_simulation()));
    // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
    connect(customPlot_simulation, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress_simulation(QMouseEvent*)));
    connect(customPlot_simulation, SIGNAL(mouseDoubleClick(QMouseEvent*)), this, SLOT(mouseDoubleClick_simulation(QMouseEvent *)));
    //connect(title, SIGNAL(doubleClicked(QMouseEvent*)), this, SLOT(titleDoubleClick(QMouseEvent*)));

    connect(customPlot_simulation, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel_simulation()));

    // make bottom and left axes transfer their ranges to top and right axes:
    connect(customPlot_simulation->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot_simulation->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot_simulation->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot_simulation->yAxis2, SLOT(setRange(QCPRange)));

    // connect some interaction slots:
    connect(customPlot_simulation, SIGNAL(axisDoubleClick(QCPAxis*,QCPAxis::SelectablePart,QMouseEvent*)), this, SLOT(axisLabelDoubleClick_simulation(QCPAxis*,QCPAxis::SelectablePart)));
        connect(customPlot_simulation, SIGNAL(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)), this, SLOT(legendDoubleClick_simulation(QCPLegend*,QCPAbstractLegendItem*)));
    //connect(customPlot_simulation, SIGNAL(titleDoubleClick(QMouseEvent*)), this, SLOT(titleDoubleClick(QMouseEvent*)));

    // connect slot that shows a message in the status bar when a graph is clicked:
    connect(customPlot_simulation, SIGNAL(plottableClick(QCPAbstractPlottable*,int,QMouseEvent*)), this, SLOT(graphClicked_simulation(QCPAbstractPlottable*,int)));
    connect(customPlot_simulation, SIGNAL(plottableDoubleClick(QCPAbstractPlottable*,int,QMouseEvent*)), this, SLOT(graphDoubleClicked_simulation(QCPAbstractPlottable*,int)));

    connect(customPlot_simulation, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(onMouseMove_simulation(QMouseEvent*)));
    connect(customPlot_simulation, SIGNAL(mouseRelease(QMouseEvent*)), this, SLOT(mouseRelease_simulation(QMouseEvent*)));
    // setup policy and connect slot for context menu popup:
    customPlot_simulation->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(customPlot_simulation, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest_simulation(QPoint)));


    customPlot_simulation->replot();

    _init_customPlot_simulation_ok=true;

}





void MainWindow::titleDoubleClick_simulation(QMouseEvent* event)
{
    Q_UNUSED(event)
            if (QCPTextElement *title = qobject_cast<QCPTextElement*>(sender())){
                // Set the plot title by double clicking on it
                bool ok;
                QString newTitle = QInputDialog::getText(this, "QcustomPlot_simulation example", "New plot title:", QLineEdit::Normal, "", &ok);
                if (ok){
                    string s=newTitle.toUtf8().constData();
                    QString newTitle2="multiplier="+newTitle;
                    title->setText(newTitle2);

                            customPlot_simulation->replot();
                }
            }
             cout<<"titleDoubleClick"<<endl;
}


void MainWindow::axisLabelDoubleClick_simulation(QCPAxis *axis, QCPAxis::SelectablePart part){
  // Set an axis label by double clicking on it
  if (part == QCPAxis::spAxisLabel){ // only react when the actual axis label is clicked, not tick label or axis backbone
    bool ok;
    QString newLabel = QInputDialog::getText(this, "QcustomPlot_simulation example", "New axis label:", QLineEdit::Normal, axis->label(), &ok);
    if (ok){
      axis->setLabel(newLabel);
              customPlot_simulation->replot();
    }
  }
    cout<<"axisLabelDoubleClick"<<endl;
}




void MainWindow::legendDoubleClick_simulation(QCPLegend *legend, QCPAbstractLegendItem *item){
  // Rename a graph by double clicking on its legend item
  Q_UNUSED(legend)
  if (item){ // only react if item was clicked (user could have clicked on border padding of legend where there is no item, then item is 0)
    QCPPlottableLegendItem *plItem = qobject_cast<QCPPlottableLegendItem*>(item);
    bool ok;
    QString newName = QInputDialog::getText(this, "QcustomPlot_simulation example", "New graph name:", QLineEdit::Normal, plItem->plottable()->name(), &ok);
    if (ok){
      plItem->plottable()->setName(newName);
             customPlot_simulation->replot();
    }
  }
  cout<<"legendDoubleClick"<<endl;

}




void MainWindow::selectionChanged_simulation(){

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

           if (customPlot_simulation->xAxis->selectedParts().testFlag(QCPAxis::spAxis) || customPlot_simulation->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
               customPlot_simulation->xAxis2->selectedParts().testFlag(QCPAxis::spAxis) || customPlot_simulation->xAxis2->selectedParts().testFlag(QCPAxis::spTickLabels)){
                   customPlot_simulation->xAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
                   customPlot_simulation->xAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
           }
           // make left and right axes be selected synchronously, and handle axis and tick labels as one selectable object:
           if (customPlot_simulation->yAxis->selectedParts().testFlag(QCPAxis::spAxis) || customPlot_simulation->yAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
               customPlot_simulation->yAxis2->selectedParts().testFlag(QCPAxis::spAxis) || customPlot_simulation->yAxis2->selectedParts().testFlag(QCPAxis::spTickLabels)){
                   customPlot_simulation->yAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
                   customPlot_simulation->yAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
           }

           // synchronize selection of graphs with selection of corresponding legend items:

           for (int i=0; i<customPlot_simulation->graphCount(); ++i){
               //cout<<"I="<<i<<endl;
               QCPGraph *graph = customPlot_simulation->graph(i);

               QCPPlottableLegendItem *item = customPlot_simulation->legend->itemWithPlottable(graph);
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

                   if(customPlot_simulation->graphCount()>0){

                      QCPDataSelection selection = customPlot_simulation->graph(0)->selection();
                      double sum = 0;
                      foreach (QCPDataRange dataRange, selection.dataRanges()){
                        //cout<<dataRange.begin()<<endl;
                        QCPGraphDataContainer::const_iterator begin = customPlot_simulation->graph(0)->data()->at(dataRange.begin()); // get range begin iterator from index
                        QCPGraphDataContainer::const_iterator end = customPlot_simulation->graph(0)->data()->at(dataRange.end()); // get range end iterator from index
                        for (QCPGraphDataContainer::const_iterator it=begin; it!=end; ++it){
                          // iterator "it" will go through all selected data points, as an example, we ca_simulationulate the value average
                          //sum += it->value;
                          _value_selected.push_back(it->value);
                          _key_selected.push_back(it->key);
                        }
                      }
                    }
}


void MainWindow::mousePress_simulation(QMouseEvent* event){
  // if an axis is selected, only allow the direction of that axis to be dragged
  // if no axis is selected, both directions may be dragged

            bool axis_set_on=false;
            if (customPlot_simulation->xAxis->selectedParts().testFlag(QCPAxis::spAxis)){
                customPlot_simulation->axisRect()->setRangeDrag(customPlot_simulation->xAxis->orientation());
                axis_set_on=true;
            }else if (customPlot_simulation->yAxis->selectedParts().testFlag(QCPAxis::spAxis)){
                customPlot_simulation->axisRect()->setRangeDrag(customPlot_simulation->yAxis->orientation());
                axis_set_on=true;
            }else{
                customPlot_simulation->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
            }
            double xCoord = customPlot_simulation->xAxis->pixelToCoord(event->pos().x());
            double yCoord = customPlot_simulation->yAxis->pixelToCoord(event->pos().y());
            //cout<<"add plot: mouse move, click on: xCoord="<<xCoord<<" yCoord="<<yCoord<<endl;

}



void MainWindow::mouseDoubleClick_simulation(QMouseEvent* event){

    //double x=event->pos().x();
    //cout<<"mouseDoubleClick pres"<<x<<endl;


            double xCoord = customPlot_simulation->xAxis->pixelToCoord(event->pos().x());
            double yCoord = customPlot_simulation->yAxis->pixelToCoord(event->pos().y());

            QString message = QString("Clicked at data point #%1 with value %2.").arg(xCoord).arg(yCoord);
            //ui->statusBar->showMessage(message, 25000);

            //cout<<"mouseDoubleClick: xCoord="<<xCoord<<" yCoord="<<yCoord<<endl;
            QString str=QString{"%1"}.arg(xCoord);

            customPlot_simulation->rescaleAxes();
            customPlot_simulation->replot();

}

void MainWindow::mouseWheel_simulation(){
  // if an axis is selected, only allow the direction of that axis to be zoomed
  // if no axis is selected, both directions may be zoomed

  //cout<<"mouseWheel"<<endl;

           if (customPlot_simulation->xAxis->selectedParts().testFlag(QCPAxis::spAxis)){
              customPlot_simulation->axisRect()->setRangeZoom(customPlot_simulation->xAxis->orientation());
              //customPlot_simulation->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
              //cout<<"xAxis"<<endl;
           }else if (customPlot_simulation->yAxis->selectedParts().testFlag(QCPAxis::spAxis)){
              customPlot_simulation->axisRect()->setRangeZoom(customPlot_simulation->yAxis->orientation());
              //cout<<"yAxis"<<endl;
           } else{
              customPlot_simulation->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
              //customPlot_simulation->axisRect()->setRangeZoom(customPlot_simulation->xAxis->orientation());
              //customPlot_simulation->axisRect()->setRangeZoom(customPlot_simulation->yAxis->orientation());
              //cout<<"zoom"<<endl;

           }


}


void MainWindow::removeAllGraphs_simulation(){
           customPlot_simulation->clearGraphs();
           customPlot_simulation->replot();



}



void MainWindow::contextMenuRequest_simulation(QPoint pos){
  QMenu *menu = new QMenu(this);
  //menu = new QMenu(add_plot_plot_dialog);
  //QMenu *menu = new QMenu(this);
  menu->setAttribute(Qt::WA_DeleteOnClose);

         if (false && customPlot_simulation->legend->selectTest(pos, false) >= 0){
            menu->addAction("Move to top left", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignLeft));
            menu->addAction("Move to top center", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignHCenter));
            menu->addAction("Move to top right", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignRight));
            menu->addAction("Move to bottom right", this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignRight));
            menu->addAction("Move to bottom left", this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignLeft));
         }else if(customPlot_simulation->xAxis->selectTest(pos,false)>=0){
            menu->addAction("Reverse x axis", this, SLOT(reverse_xAxis()));
         }else if(customPlot_simulation->yAxis->selectTest(pos,false)>=0){
            menu->addAction("Reverse y axis", this, SLOT(reverse_yAxis()));
         }else{
            menu->addAction("Save simulation data to a pdf", this, SLOT(savepdf_simulation()));
            menu->addAction("Save simulation data to a file", this, SLOT(simulation_save()));
            }


         menu->popup(customPlot_simulation->mapToGlobal(pos));

}

void MainWindow::simulation_save(){
    size_t n=SN.size();
    if(n>0){
       string input_file_name=_file.file_name();
       input_file_name=f_remove_ext(input_file_name);
       string name=input_file_name+"_data_SN_"+to_string(n)+".dat";
       ofstream fo{name};
       cout<<"name="<<name<<endl;
       fo<<"No SN f A  SNo"<<endl;
       for(size_t i=0;i<n;++i){
           fo<<i<<" "<<SN[i]<<" "<<SNfr[i]<<" "<<SNAmpl[i]<<" "<<SNsn[i]<< endl;
       }
       string text;
       text="<font color="+NLSF_info_color_font.toStdString()+">data: saving to "+input_file_name;
       simulation_label->setText(text.c_str());
    }


}

bool existpdf_simulation (const std::string& name) {
   return ( access( name.c_str(), F_OK ) != -1 );
}




void MainWindow::reverse_xAxis_simulation(){
    //cout<<"reversed = "<<customPlot_simulation->xAxis->rangeReversed()<<endl;
    if(customPlot_simulation->xAxis->rangeReversed()){
        customPlot_simulation->xAxis->setRangeReversed(false);
        xrplot=false;
    }else{
        customPlot_simulation->xAxis->setRangeReversed(true);
        xrplot=true;
    }
    customPlot_simulation->replot();
}

void MainWindow::reverse_yAxis_simulation(){
   //cout<<"reversed = "<<customPlot_simulation->yAxis->rangeReversed()<<endl;
   if(customPlot_simulation->yAxis->rangeReversed()){
       customPlot_simulation->yAxis->setRangeReversed(false);
       yrplot=false;
   }else{
       customPlot_simulation->yAxis->setRangeReversed(true);
       yrplot=true;
   }
   customPlot_simulation->replot();
}



void MainWindow::savepdf_simulation(){
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
    string name=input_file_name+"_data_SN_n"+to_string(n)+".pdf";

    //f_replace(name,"/","");
    f_replace(name,"\\","");
    f_replace(name,"&","");
    f_replace(name,"$","");
    f_replace(name,"#","");
    //name=path+name;
    cout<<"saving in a file = "<<name<<endl;


    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);


    //cout<<"printer.pageRect().width()="<<printer.pageRect().width()<<endl;
    //cout<<"customPlot_simulation[i]->width()="<<customPlot_simulation[i]->width()<<endl;
    //double xscale = printer.pageRect().width() / double(customPlot_simulation[i]->width());
    //double yscale = printer.pageRect().height() / double(customPlot_simulation[i]->height());
    //customPlot_simulation[i]->savePdf(name.c_str(), customPlot_simulation[i]->width(), customPlot_simulation[i]->height() );
    //customPlot_simulation[i]->savePdf(name.c_str(), printer.pageRect().width()/2, printer.pageRect().width()/2 );

    customPlot_simulation->savePdf(name.c_str(), 800, 500 );
    customPlot_simulation->replot();

    QString message = QString(("saving to pdf = "+name).c_str());
    simulation_statusBar->showMessage(message, 0);

    string text;
    text="<font color="+NLSF_info_color_font.toStdString()+">pdf: saving to "+name;
    simulation_label->setText(text.c_str());

}



void MainWindow::moveLegend_simulation()
{
  if (QAction* contextAction = qobject_cast<QAction*>(sender())) // make sure this slot is really called by a context menu action, so it carries the data we need
  {
    bool ok;
    int dataInt = contextAction->data().toInt(&ok);
    if (ok){

                customPlot_simulation->axisRect()->insetLayout()->setInsetAlignment(0, (Qt::Alignment)dataInt);
                customPlot_simulation->replot();


    }
  }
}

void MainWindow::graphClicked_simulation(QCPAbstractPlottable *plottable, int dataIndex)
{
  // since we know we only have QCPGraphs in the plot, we can immediately access interface1D()
  // usually it's better to first check whether interface1D() returns non-zero, and only then use it.
  double dataValue = plottable->interface1D()->dataMainValue(dataIndex);
  double dataKey = plottable->interface1D()->dataSortKey(dataIndex);
  QString message = QString("Clicked on graph '%1' at x= %2, y= %3.").arg(plottable->name()).arg(dataKey).arg(dataValue);
  simulation_statusBar->showMessage(message, 0);


  double xCoord=0, yCoord=0;

         QList<QCPGraph*>  qlist=customPlot_simulation->selectedGraphs ( );
         size_t  n=customPlot_simulation->graphCount();
         if(qlist.empty()){
              cout<<"no graph selected"<<endl;
         }else{
             cout<<"some graph is selected"<<endl;
             for(auto it=qlist.begin();it!=qlist.end();++it){
                  //cout<<*it<<endl;
                  for(int j=0;j<n;++j){
                     if(*it==customPlot_simulation->graph(j)){
                         //cout<<"the graph "<<j<<" was selected"<<endl;
                     }
                  }
             }
        }

}


void MainWindow::graphDoubleClicked_simulation(QCPAbstractPlottable *plottable, int dataIndex)
{
  // since we know we only have QCPGraphs in the plot, we can immediately access interface1D()
  // usually it's better to first check whether interface1D() returns non-zero, and only then use it.
  double dataValue = plottable->interface1D()->dataMainValue(dataIndex);
  double dataKey = plottable->interface1D()->dataSortKey(dataIndex);
  QString message = QString("Clicked on graph '%1' at x= %2, y= %3.").arg(plottable->name()).arg(dataKey).arg(dataValue);
  simulation_statusBar->showMessage(message, 0);

  //cout<<"graphDoubleClicked: dataindex="<<dataIndex<<" dataKey="<<dataKey<<" dataValue="<<dataValue<<endl;

}




void MainWindow::onMouseMove_simulation(QMouseEvent *event){
    double xCoord=0, yCoord=0;
           xCoord = customPlot_simulation->xAxis->pixelToCoord(event->pos().x());
           yCoord = customPlot_simulation->yAxis->pixelToCoord(event->pos().y());


    QString message = QString("%1, %2")
            .arg(xCoord).arg(yCoord);

   //ui->statusBar->setStyleSheet("QStatusBar{color:red}") if needed
    simulation_statusBar->setStyleSheet("color: "+basic_color_font+"");
    simulation_statusBar->showMessage(message, 0);

}



void MainWindow::mouseRelease_simulation(QMouseEvent* event ){
    //cout<<"add plot: mouse release"<<endl;
    /*
          double xCoord = customPlot_simulation->xAxis->pixelToCoord(event->pos().x());
          double yCoord = customPlot_simulation->yAxis->pixelToCoord(event->pos().y());
          double xCoord_pix = event->pos().x();
          double yCoord_pix = event->pos().y();
    */

}


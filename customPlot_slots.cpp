#include "mainwindow.h"




void MainWindow::plot_trf(){


    size_t n=_fr.size();
    if(n>0){
       QVector<double>qx(n),qy(n);
       f_convert_data(_fr,_ampl,qx,qy);

       if(_ind_graph_trf==-1){
           //cout<<"plot trf: adding new graphs "<<endl;
           //cout<<customPlot->graphCount()<<endl;
           _ind_graph_trf=customPlot->graphCount();
           customPlot->addGraph();
           customPlot->graph(_ind_graph_trf)->setSelectable(QCP::stNone);
           trfTracer = new QCPItemTracer(customPlot);
       }
       customPlot->graph(_ind_graph_trf)->setData(qx,qy);
       //customPlot->graph(_ind_graph_trf_fwpeaks)->removeFromLegend();
       customPlot->graph(_ind_graph_trf)->addToLegend();
       customPlot->graph(_ind_graph_trf)->setName("Fourier Transform");
       QPen pen;
       pen.setColor(trf_line_color);
       pen.setWidth(trf_line_width);
       customPlot->graph(_ind_graph_trf)->setPen(pen);



      /*
     if(!_trfTracer_set_on){
         trfTracer = new QCPItemTracer(customPlot);
         _trfTracer_set_on=true;
     }
    */


       trfTracer->setGraph(customPlot->graph(_ind_graph_trf));
       trfTracer->setGraphKey(0);
       trfTracer->setInterpolating(true);
       trfTracer->setStyle(QCPItemTracer::tsCircle);
       trfTracer->setPen(QPen(Qt::green));
       trfTracer->setBrush(Qt::blue);
       trfTracer->setSize(7);



       //customPlot->rescaleAxes();
       if(_resize_x_axix){
           customPlot->xAxis->setRange(_xmin,_xmax);
       }
       if(_resize_y_axix){
           customPlot->yAxis->setRange(_ymin,_ymax*(1+0.15));
       }

       if(_show_peaks){
           show_peaks();
       }

       customPlot->replot();
       //_trf_ok=true;
       //_last_ctivity="trf";
    }

}


void MainWindow::titleDoubleClick(QMouseEvent* event)
{
    Q_UNUSED(event)
            if (QCPTextElement *title = qobject_cast<QCPTextElement*>(sender())){
                // Set the plot title by double clicking on it
                bool ok;
                QString newTitle = QInputDialog::getText(this, "QCustomPlot example", "New plot title:", QLineEdit::Normal, "", &ok);
                if (ok){
                    string s=newTitle.toUtf8().constData();
                    QString newTitle2="multiplier="+newTitle;
                    title->setText(newTitle2);

                            customPlot->replot();
                }
            }
             cout<<"titleDoubleClick"<<endl;
}


void MainWindow::axisLabelDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part){
  // Set an axis label by double clicking on it
  if (part == QCPAxis::spAxisLabel){ // only react when the actual axis label is clicked, not tick label or axis backbone
    bool ok;
    QString newLabel = QInputDialog::getText(this, "QCustomPlot example", "New axis label:", QLineEdit::Normal, axis->label(), &ok);
    if (ok){
      axis->setLabel(newLabel);
              customPlot->replot();
    }
  }
    cout<<"axisLabelDoubleClick"<<endl;
}




void MainWindow::legendDoubleClick(QCPLegend *legend, QCPAbstractLegendItem *item){
  // Rename a graph by double clicking on its legend item
  Q_UNUSED(legend)
  if (item){ // only react if item was clicked (user could have clicked on border padding of legend where there is no item, then item is 0)
    QCPPlottableLegendItem *plItem = qobject_cast<QCPPlottableLegendItem*>(item);
    bool ok;
    QString newName = QInputDialog::getText(this, "QCustomPlot example", "New graph name:", QLineEdit::Normal, plItem->plottable()->name(), &ok);
    if (ok){
      plItem->plottable()->setName(newName);
             customPlot->replot();
    }
  }
  cout<<"legendDoubleClick"<<endl;

}




void MainWindow::selectionChanged(){

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

           if (customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis) || customPlot->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
               customPlot->xAxis2->selectedParts().testFlag(QCPAxis::spAxis) || customPlot->xAxis2->selectedParts().testFlag(QCPAxis::spTickLabels)){
                   customPlot->xAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
                   customPlot->xAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
           }
           // make left and right axes be selected synchronously, and handle axis and tick labels as one selectable object:
           if (customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis) || customPlot->yAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
               customPlot->yAxis2->selectedParts().testFlag(QCPAxis::spAxis) || customPlot->yAxis2->selectedParts().testFlag(QCPAxis::spTickLabels)){
                   customPlot->yAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
                   customPlot->yAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
           }

           // synchronize selection of graphs with selection of corresponding legend items:

           for (int i=0; i<customPlot->graphCount(); ++i){
               //cout<<"I="<<i<<endl;
               QCPGraph *graph = customPlot->graph(i);

               QCPPlottableLegendItem *item = customPlot->legend->itemWithPlottable(graph);
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

                   if(customPlot->graphCount()>0){

                      QCPDataSelection selection = customPlot->graph(0)->selection();
                      double sum = 0;
                      foreach (QCPDataRange dataRange, selection.dataRanges()){
                        //cout<<dataRange.begin()<<endl;
                        QCPGraphDataContainer::const_iterator begin = customPlot->graph(0)->data()->at(dataRange.begin()); // get range begin iterator from index
                        QCPGraphDataContainer::const_iterator end = customPlot->graph(0)->data()->at(dataRange.end()); // get range end iterator from index
                        for (QCPGraphDataContainer::const_iterator it=begin; it!=end; ++it){
                          // iterator "it" will go through all selected data points, as an example, we calculate the value average
                          //sum += it->value;
                          _value_selected.push_back(it->value);
                          _key_selected.push_back(it->key);
                        }
                      }
                    }
}


void MainWindow::mousePress(QMouseEvent* event){
  // if an axis is selected, only allow the direction of that axis to be dragged
  // if no axis is selected, both directions may be dragged

            bool axis_set_on=false;
            if (customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis)){
                customPlot->axisRect()->setRangeDrag(customPlot->xAxis->orientation());
                axis_set_on=true;
            }else if (customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis)){
                customPlot->axisRect()->setRangeDrag(customPlot->yAxis->orientation());
                axis_set_on=true;
            }else{
                customPlot->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
            }
            double xCoord = customPlot->xAxis->pixelToCoord(event->pos().x());
            double yCoord = customPlot->yAxis->pixelToCoord(event->pos().y());
            //cout<<"add plot: mouse move, click on: xCoord="<<xCoord<<" yCoord="<<yCoord<<endl;

}



void MainWindow::mouseDoubleClick(QMouseEvent* event){

    //double x=event->pos().x();
    //cout<<"mouseDoubleClick pres"<<x<<endl;



            double xCoord = customPlot->xAxis->pixelToCoord(event->pos().x());
            double yCoord = customPlot->yAxis->pixelToCoord(event->pos().y());

            QString message = QString("Clicked at data point #%1 with value %2.").arg(xCoord).arg(yCoord);
            //ui->statusBar->showMessage(message, 25000);

            //cout<<"mouseDoubleClick: xCoord="<<xCoord<<" yCoord="<<yCoord<<endl;
            QString str=QString{"%1"}.arg(xCoord);

       if(_selection_mode){
            //customPlot->rescaleAxes();
            customPlot->xAxis->setRange(_xmin,_xmax);
            customPlot->yAxis->setRange(_ymin,_ymax*(1+0.015));
            customPlot->replot();
       }else{

           string text;
           double S=trfTracer->position->value();
           double sn=-1;
           if(_noise_ok){
               text="S/N="+to_string(S/spline_noise.e(xCoord));
               sn=S/spline_noise.e(xCoord);
           }
           cout<<"text="<<text<<endl;

           // _freq.push_back(xCoord);
            add_freq_to_table(xCoord,sn);
       }
}

void MainWindow::mouseWheel(){
  // if an axis is selected, only allow the direction of that axis to be zoomed
  // if no axis is selected, both directions may be zoomed

  //cout<<"mouseWheel"<<endl;

           if (customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis)){
              customPlot->axisRect()->setRangeZoom(customPlot->xAxis->orientation());
              //customPlot->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
              //cout<<"xAxis"<<endl;
           }else if (customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis)){
              customPlot->axisRect()->setRangeZoom(customPlot->yAxis->orientation());
              //cout<<"yAxis"<<endl;
           } else{
              customPlot->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
              //customPlot->axisRect()->setRangeZoom(customPlot->xAxis->orientation());
              //customPlot->axisRect()->setRangeZoom(customPlot->yAxis->orientation());
              //cout<<"zoom"<<endl;

           }


}


void MainWindow::removeSelectedGraph(){
  cout<<"removeSelectedGraph"<<endl;


  //QList<QCPGraph*>  qlist=customPlot[0]->selectedGraphs ( );
  //if(qlist.empty()){
  //    cout<<"no graph selected"<<endl;
  //}else{
     //cout<<"some graph is selected"<<endl;
   //  for(auto it=qlist.begin();it!=qlist.end();++it){
         //cout<<*it<<endl;
         //if(*it==customPlot[0]->graph(0)){
         //    cout<<"the grapth(0) was selected"<<endl;
         //}
   //  }

  //}



}

void MainWindow::removeAllGraphs(){
           customPlot->clearGraphs();
           customPlot->replot();



}



void MainWindow::contextMenuRequest(QPoint pos){
  QMenu *menu = new QMenu(this);
  //menu = new QMenu(add_plot_plot_dialog);
  //QMenu *menu = new QMenu(this);
  menu->setAttribute(Qt::WA_DeleteOnClose);

         if (false && customPlot->legend->selectTest(pos, false) >= 0){
            menu->addAction("Move to top left", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignLeft));
            menu->addAction("Move to top center", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignHCenter));
            menu->addAction("Move to top right", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignRight));
            menu->addAction("Move to bottom right", this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignRight));
            menu->addAction("Move to bottom left", this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignLeft));
         }else if(customPlot->xAxis->selectTest(pos,false)>=0){
            menu->addAction("reverse x axis", this, SLOT(reverse_xAxis()));
            if(_resize_x_axix){
                 menu->addAction("Set const x axis", this, SLOT(set_const_xAxis()));
            }else{
                 menu->addAction("Rescale x axis", this, SLOT(set_rescale_xAxis()));
            }
         }else if(customPlot->yAxis->selectTest(pos,false)>=0){
            menu->addAction("Reverse y axis", this, SLOT(reverse_yAxis()));
            if(_log_scale_y){
                menu->addAction("Unset log scale for y axis", this, SLOT(set_logscale_yAxis()));
            }else{
                menu->addAction("Set log scale for y axis", this, SLOT(set_logscale_yAxis()));
            }
         }else{
            if(_show_peaks){
                menu->addAction("Add max peak", this, SLOT(add_max_peak()));
            }
            menu->addAction("Save trf to pdf", this, SLOT(savepdf()));
            menu->addAction("Save trf to data file", this, SLOT(trf_save_trf()));

            if(_key_selected.size()>0){
               menu->addAction("clear selected data", this, SLOT(clear_selected_data()));
            }
            //menu->addAction("remove selected data",this, SLOT(remove_selected_data()));
            /*if(!constant_border){
                menu->addAction("set constant margins",this, SLOT(set_constant_border()));
            }else{
                menu->addAction("set dynamic margins",this, SLOT(set_dynamic_border()));
            }*/
            //menu->addAction("rescale", this, SLOT(rescale()));


         }

         QList<QCPGraph*>  qlist=customPlot->selectedGraphs ( );
         if(qlist.empty()){
             //cout<<"no graph selected"<<endl;
         }else{
             //cout<<"some graph is selected"<<endl;
             for(auto it=qlist.begin();it!=qlist.end();++it){
                //cout<<*it<<endl;
                for(int i=0;i<customPlot->graphCount();++i){
                   if(*it==customPlot->graph(i)){
                      //cout<<"the grapth("<<i<<") was selected"<<endl;
                      //menu->addAction("remove noise", this, SLOT(removenoise()));
                   }
                }
             }

         }

         menu->popup(customPlot->mapToGlobal(pos));

}
void MainWindow::set_const_xAxis(){
    _resize_x_axix=false;
}
void MainWindow::set_rescale_xAxis(){
    _resize_x_axix=true;
}

void MainWindow::trf_save_trf(){
    int n=table->rowCount();
    size_t nlc=_fr.size();
    if(nlc>0){
       string input_file_name=_file.file_name();
       input_file_name=f_remove_ext(input_file_name);
       string name=input_file_name+"_data_trf_n"+to_string(n);
       ofstream fo{name};
       if(_noise_ok){
          for(size_t i=0;i<_fr.size();++i){
             fo<<_fr[i]<<" "<<_ampl[i]<<" "<<spline_noise.e(_fr[i])<<endl;
          }
       }else{
           for(size_t i=0;i<_fr.size();++i){
              fo<<_fr[i]<<" "<<_ampl[i]<<endl;
           }
       }
    }
}
void MainWindow::set_logscale_yAxis(){
    if(!_log_scale_y){
        customPlot->yAxis->setScaleType(QCPAxis::stLogarithmic);
        customPlot->yAxis2->setScaleType(QCPAxis::stLogarithmic);
        _log_scale_y=true;
        customPlot->replot();
    }else{
        customPlot->yAxis->setScaleType(QCPAxis::stLinear);
        customPlot->yAxis2->setScaleType(QCPAxis::stLinear);
        _log_scale_y=false;
        customPlot->replot();
    }
}

void MainWindow::clear_selected_data(){
    _key_selected.clear();
    _value_selected.clear();
    customPlot->deselectAll();
    customPlot->replot();
}


void MainWindow::reverse_xAxis(){
    //cout<<"reversed = "<<customPlot->xAxis->rangeReversed()<<endl;
    if(customPlot->xAxis->rangeReversed()){
        customPlot->xAxis->setRangeReversed(false);
        xrplot=false;
    }else{
        customPlot->xAxis->setRangeReversed(true);
        xrplot=true;
    }
    customPlot->replot();
}

void MainWindow::reverse_yAxis(){
   //cout<<"reversed = "<<customPlot->yAxis->rangeReversed()<<endl;
   if(customPlot->yAxis->rangeReversed()){
       customPlot->yAxis->setRangeReversed(false);
       yrplot=false;
   }else{
       customPlot->yAxis->setRangeReversed(true);
       yrplot=true;
   }
   customPlot->replot();
}



void MainWindow::savepdf(){
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
    string name=input_file_name+"_data_trf_n"+to_string(n)+".pdf";

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
    //cout<<"customPlot[i]->width()="<<customPlot[i]->width()<<endl;
    //double xscale = printer.pageRect().width() / double(customPlot[i]->width());
    //double yscale = printer.pageRect().height() / double(customPlot[i]->height());
    //customPlot[i]->savePdf(name.c_str(), customPlot[i]->width(), customPlot[i]->height() );
    //customPlot[i]->savePdf(name.c_str(), printer.pageRect().width()/2, printer.pageRect().width()/2 );

    customPlot->savePdf(name.c_str(), 800, 500 );
    customPlot->replot();

    QString message = QString(("saving to pdf = "+name).c_str());
    this->statusBar()->showMessage(message, 0);

    label_info_fitting->setText(label_info_fitting2->text());
    string text;
    text="<font color="+NLSF_info_color_font.toStdString()+">pdf: saving to "+name;
    label_info_fitting2->setText(text.c_str());

}



void MainWindow::moveLegend()
{
  if (QAction* contextAction = qobject_cast<QAction*>(sender())) // make sure this slot is really called by a context menu action, so it carries the data we need
  {
    bool ok;
    int dataInt = contextAction->data().toInt(&ok);
    if (ok){

                customPlot->axisRect()->insetLayout()->setInsetAlignment(0, (Qt::Alignment)dataInt);
                customPlot->replot();


    }
  }
}

void MainWindow::graphClicked(QCPAbstractPlottable *plottable, int dataIndex)
{
  // since we know we only have QCPGraphs in the plot, we can immediately access interface1D()
  // usually it's better to first check whether interface1D() returns non-zero, and only then use it.
  double dataValue = plottable->interface1D()->dataMainValue(dataIndex);
  double dataKey = plottable->interface1D()->dataSortKey(dataIndex);
  QString message = QString("Clicked on graph '%1' at x= %2, y= %3.").arg(plottable->name()).arg(dataKey).arg(dataValue);
  this->statusBar()->showMessage(message, 0);


  double xCoord=0, yCoord=0;

         QList<QCPGraph*>  qlist=customPlot->selectedGraphs ( );
         size_t  n=customPlot->graphCount();
         if(qlist.empty()){
              cout<<"no graph selected"<<endl;
         }else{
             cout<<"some graph is selected"<<endl;
             for(auto it=qlist.begin();it!=qlist.end();++it){
                  //cout<<*it<<endl;
                  for(int j=0;j<n;++j){
                     if(*it==customPlot->graph(j)){
                         //cout<<"the graph "<<j<<" was selected"<<endl;
                     }
                  }
             }
        }
        //_start_point=dataKey;

         if(_markbar_ok && !_key_control_pressed){
             _markbar->setVisible(false);
             _start_point_ok=false;
             customPlot->replot();
         }

}


void MainWindow::graphDoubleClicked(QCPAbstractPlottable *plottable, int dataIndex)
{
  // since we know we only have QCPGraphs in the plot, we can immediately access interface1D()
  // usually it's better to first check whether interface1D() returns non-zero, and only then use it.
  double dataValue = plottable->interface1D()->dataMainValue(dataIndex);
  double dataKey = plottable->interface1D()->dataSortKey(dataIndex);
  QString message = QString("Clicked on graph '%1' at x= %2, y= %3.").arg(plottable->name()).arg(dataKey).arg(dataValue);
  this->statusBar()->showMessage(message, 0);

  //cout<<"graphDoubleClicked: dataindex="<<dataIndex<<" dataKey="<<dataKey<<" dataValue="<<dataValue<<endl;

}




void MainWindow::onMouseMove(QMouseEvent *event){
    double xCoord=0, yCoord=0;
           xCoord = customPlot->xAxis->pixelToCoord(event->pos().x());
           yCoord = customPlot->yAxis->pixelToCoord(event->pos().y());


    QString message = QString("%1, %2")
            .arg(xCoord).arg(yCoord);

    //ui->statusBar->setStyleSheet("QStatusBar{color:red}") if needed
    this->statusBar()->setStyleSheet("color: orange");
    this->statusBar()->showMessage(message, 0);

    if(_trf_ok && trfTracer!=nullptr && !_selection_mode){
       //cout<<"tracer is on"<<endl;
       trfTracer->setGraphKey(xCoord);

       //trfTracer->position->setType(QCPItemPosition::ptPlotCoords);
       //QCPItemPosition *pos = trfTracer->position;
       //cout<<"x="<<pos->key()<<endl;
       //cout<<"y="<<pos->value()<<endl;

       //plot_line(pos->key());

       string text;
       text="f="+to_string(xCoord);
       double S=trfTracer->position->value();
       text+="\nP="+to_string(S);
       if(_noise_ok){
           text+="\nS/N="+to_string(S/spline_noise.e(xCoord));
       }
       qcpit_info->setText(text.c_str());
       qcpit_info->position->setCoords(xCoord,0.05);

       plot_line(xCoord);       

       customPlot->replot();
    }



    if(_key_control_pressed && !_start_point_ok){
        _start_point=xCoord;
        _start_point_ok=true;
    }else if(_key_control_pressed && _start_point_ok){
        plot_bar(_start_point,xCoord);
    }
}


void MainWindow::plot_line(double x){
    if(!_linebar_ok){
                linebar = new QCPBars(customPlot->xAxis, customPlot->yAxis);
                linebar->setSelectable(QCP::stNone);
                linebar->setAntialiased(false); // gives more crisp, pixel aligned bar borders
                linebar->setStackingGap(1);
                // set names and colors:
                linebar->setName("line");
                //linebar->setPen(QPen(QColor(200, 200, 200,100)));
                linebar->setPen(QPen(QColor(0,0,0,100)));
                //linebar->setBrush(QColor(111, 9, 176,30).lighter(170));
                linebar->setBrush(QColor(0, 0, 0,100).lighter(170));
                linebar->setWidthType(QCPBars::wtAbsolute);
                linebar->setWidth(2);
                linebar->removeFromLegend();
                _linebar_ok=true;
    }
    QVector<double>qx(1),qy(1);
    qx[0]=x;
    qy[0]=_ymax*(1+0.1);
    linebar->setData(qx,qy);
    customPlot->replot();

}

void MainWindow::plot_bar(double x0, double xe){
    //cout<<"plot_bar"<<" xe="<<xe<<" x0="<<x0<<" "<<(x0+xe)/2.0<<endl;
    if(!_markbar_ok){
                _markbar = new QCPBars(customPlot->xAxis, customPlot->yAxis);
                _markbar->setSelectable(QCP::stNone);
                _markbar->setAntialiased(false); // gives more crisp, pixel aligned bar borders
                _markbar->setStackingGap(1);
                // set names and colors:
                _markbar->setName("line");
                //_markbar->setPen(QPen(QColor(200, 200, 200,100)));
                _markbar->setPen(QPen(QColor(0,0,0,100)));
                //_markbar->setBrush(QColor(111, 9, 176,30).lighter(170));
                _markbar->setBrush(QColor(0, 100, 0,10).lighter(170));
                _markbar->setWidthType(QCPBars::wtPlotCoords);

                _markbar->removeFromLegend();
                _markbar_ok=true;
    }
    _markbar->setVisible(true);
    QVector<double>qx(1),qy(1);
    qx[0]=(x0+xe)/2.0;
    qy[0]=_ymax*(1+0.1);
    _markbar->setWidth(abs((xe-x0)));
    _markbar->setData(qx,qy);
    get_half_width(x0,xe);
    customPlot->replot();
    string text;
    text="<font color="+NLSF_info_color_font.toStdString()+">  frequency range=["+to_string(x0)+","+to_string(xe)+"], width="+to_string(abs(xe-x0));
    text+=", [fmid,hw]: ";
    int nhw=_half_width.size();
    if(nhw>5)nhw=5;
    for(size_t i=0;i<nhw;++i){
        if(i>0)text+=", ";
        text+="["+to_string(_midx[i])+",";
        text+=to_string(_half_width[i])+"]";
    }
    if(_half_width.size()>nhw){
        text+="...";
    }
    label_info_fitting2->setText(text.c_str());

}


void MainWindow::get_half_width(double x0, double xe){
    cout<<"get_half_width"<<endl;
    _half_width.clear();
    _midx.clear();
    int i0= f_find_ind(_fr,x0);
    int ie= f_find_ind(_fr,xe);
    cout<<"i0="<<i0<<" ie="<<ie<<" _fr.size="<<_fr.size()<<endl;
    if(xe>x0){

        vector<double> ymax;
        vector<int> xmax_0;
        vector<int> xmax_e;
        vector<int> ind_xmax;

        for(int i=i0+1;i<ie-1;++i){
           if(_ampl[i-1]<_ampl[i] && _ampl[i]>_ampl[i+1]){
               ymax.push_back(_ampl[i]);
               ind_xmax.push_back(i);
           }
        }

        cout<<"ymax="<<ymax<<endl;
        cout<<"ind_max="<<ind_xmax<<endl;
        for(int i=0;i<ymax.size();++i){
            bool ok=false;
            for(int j=ind_xmax[i];j>i0;--j){
                //cout<<"j0="<<j<<endl;
                if( (_ampl[j-1]>_ampl[j] && _ampl[j]<_ampl[j+1])){
                    xmax_0.push_back(j);
                    //cout<<"i0: "<<"xmax_0="<<xmax_0.back()<<endl;
                    ok=true;
                    break;
                }
            }
            if(!ok){
                xmax_0.push_back(i0);
            }
            ok=false;
            for(int j=ind_xmax[i];j<ie;++j){
                //cout<<"je="<<j<<endl;
                if( (_ampl[j-1]>_ampl[j] && _ampl[j]<_ampl[j+1])){
                    xmax_e.push_back(j);
                    cout<<i<<" "<<j<<"   "<<"xmax_e="<<xmax_e.back()<<endl;
                    ok=true;
                    break;
                }
            }
            if(!ok){
                xmax_e.push_back(ie);
            }

        }
        cout<<"ffff: ymax size = "<<ymax.size()<<" "<<xmax_0.size()<<" "<<xmax_e.size()<<" -->"<<xmax_e<<endl;

        string hw="";
        for(size_t i=0;i<ymax.size();++i){
            //cout<<i<<" "<<ymax[i]<<" "<<xmax_0[i]<<" "<<xmax_e[i]<<endl;
            int imid0;
            double mindmid0;
            bool first=true;
            for(size_t j=xmax_0[i];j<ind_xmax[i];++j){
                  //cout<<"j="<<j<<endl;
                  if(first){
                      mindmid0=abs(_ampl[j]-ymax[i]/2.0);
                      imid0=j;
                      first=false;
                  }else
                  if(abs(_ampl[j]-ymax[i]/2.0)<mindmid0){
                      mindmid0=abs(_ampl[j]-ymax[i]/2.0);
                      imid0=j;
                  }
            }
            //cout<<"min ok"<<endl;
            int imide;
            double mindmide;
            first=true;
            for(size_t j=ind_xmax[i];j<xmax_e[i];++j){
                  //cout<<"max j="<<j<<endl;
                  if(first){
                      mindmide=abs(_ampl[j]-ymax[i]/2.0);
                      imide=j;
                      first=false;
                  }else
                  if(abs(_ampl[j]-ymax[i]/2.0)<mindmide){
                      mindmide=abs(_ampl[j]-ymax[i]/2.0);
                      imide=j;
                  }
            }
            if(i>0){
                hw+=",";
            }
            hw+=" ["+to_string(_fr[imide]-_fr[imid0])+"]";
            cout<<hw<<endl;
            _half_width.push_back(_fr[imide]-_fr[imid0]);
            _midx.push_back(_fr[ind_xmax[i]]);
            for(size_t i=0;i<ymax.size();++i){
               cout<<i<<" "<<ymax[i]<<" "<<xmax_0[i]<<" imid= "<<ind_xmax[i]<<" "<<xmax_e[i]<<endl;
            }

        }

    }
}

void MainWindow::mouseRelease(QMouseEvent* event ){
    //cout<<"add plot: mouse release"<<endl;
    /*
          double xCoord = customPlot->xAxis->pixelToCoord(event->pos().x());
          double yCoord = customPlot->yAxis->pixelToCoord(event->pos().y());
          double xCoord_pix = event->pos().x();
          double yCoord_pix = event->pos().y();
    */

}


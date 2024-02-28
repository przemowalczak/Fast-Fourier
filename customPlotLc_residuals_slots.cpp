#include "mainwindow.h"




void MainWindow::plot_lc_residuals(){
    if(_init_customPlotLc_residuals_ok){
        size_t n=_file.file().size();
        if(_residuals.size()==0){
            customPlotLc_residuals->clearPlottables();
            for(int i=customPlotLc_residuals->graphCount()-1;i>=0;--i){
                customPlotLc_residuals->removeGraph(i);
            }
            _ind_graph_lc_residuals=-1;
            _residuals_ok=false;
            customPlotLc_residuals->replot();
        }else if(n>0){
            if(_file.head().size()>=3){
               QVector<double> qx(n);
               QVector<double> qy(n);
               QVector<double> qerr(n);

               _xmin_Lc_residuals=_file.file()[0][0];
               _xmax_Lc_residuals=_file.file()[0][0];
               _ymin_Lc_residuals=_residuals[0];
               _ymax_Lc_residuals=_residuals[0];
               for(size_t i=0;i<n;++i){
                   qx[i]=_file.file()[i][0];
                   qy[i]=_residuals[i];
                   qerr[i]=_file.file()[i][2];
                   if(_xmax_Lc_residuals<qx[i])_xmax_Lc_residuals=qx[i];
                   if(_xmin_Lc_residuals>qx[i])_xmin_Lc_residuals=qx[i];
                   if(_ymax_Lc_residuals<qy[i])_ymax_Lc_residuals=qy[i];
                   if(_ymin_Lc_residuals>qy[i])_ymin_Lc_residuals=qy[i];

               }
               if(_ind_graph_lc_residuals==-1){
                   _ind_graph_lc_residuals=customPlotLc_residuals->graphCount();
                   customPlotLc_residuals->addGraph();
                   string name="lc";
                   if(customPlotLc_residuals->layer(name.c_str())==nullptr){
                      customPlotLc_residuals->addLayer(name.c_str());
                   }
                   customPlotLc_residuals->graph(_ind_graph_lc_residuals)->setLayer(name.c_str());
                   ErrorBars_residuals = new QCPErrorBars (customPlotLc_residuals->xAxis, customPlotLc_residuals->yAxis);
              }
              //customPlotLc_residuals->graph(_ind_graph_lc_residuals)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, Qt::blue,QColor(50,200,100), 5));
              customPlotLc_residuals->graph(_ind_graph_lc_residuals)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QColor(lc_line_color),QColor(lc_point_color), 5));
              //customPlotLc->graph()->removeFromLegend();
              customPlotLc_residuals->graph(_ind_graph_lc_residuals)->addToLegend();


              //customPlotLc->graph(_ind_graph_lc)->setName(("data, DT="+to_string(_dT)+", 1/DT="+to_string(1/_dT)).c_str());
              customPlotLc_residuals->graph(_ind_graph_lc_residuals)->setName("residuals");
              customPlotLc_residuals->graph(_ind_graph_lc_residuals)->setSelectable(QCP::stMultipleDataRanges);
              //customPlotLc->graph(_ind_graph_lc)->setSelectable(QCP::stSingleData);


              ErrorBars_residuals->setSelectable(QCP::stMultipleDataRanges);
              //ErrorBars->setSelectable(QCP::stNone);
              //ErrorBars->setSelectable(QCP::stSingleData);
              ErrorBars_residuals->setData(qerr);
              ErrorBars_residuals->removeFromLegend();
              ErrorBars_residuals->setErrorType(QCPErrorBars::etValueError);
              ErrorBars_residuals->setDataPlottable(customPlotLc_residuals->graph(_ind_graph_lc_residuals));
              ErrorBars_residuals->setWhiskerWidth(10);
              ErrorBars_residuals->setPen(QColor(0, 0, 255));
              ErrorBars_residuals->setPen(QColor(lc_line_color));


              QPen selectedpen;
              selectedpen.setStyle(Qt::SolidLine);
              selectedpen.setWidth(3);
              selectedpen.setColor(QColor(180,180,180));
              customPlotLc_residuals->graph(_ind_graph_lc_residuals)->setPen(QColor(lc_line_color));
              customPlotLc_residuals->graph(_ind_graph_lc_residuals)->selectionDecorator()->setPen(selectedpen);
              customPlotLc_residuals->graph(_ind_graph_lc_residuals)->selectionDecorator()->setBrush(QColor(255,0,0,20));
              customPlotLc_residuals->graph(_ind_graph_lc_residuals)->selectionDecorator()->setScatterStyle(QCPScatterStyle::ssSquare);
              ErrorBars->selectionDecorator()->setPen(selectedpen);

              customPlotLc_residuals->graph(_ind_graph_lc_residuals)->setData(qx,qy);
              customPlotLc_residuals->xAxis->setRange(_xmin_Lc_residuals,_xmax_Lc_residuals);
              customPlotLc_residuals->yAxis->setRange(_ymin_Lc_residuals,_ymax_Lc_residuals);

              QCPLayer *l = customPlotLc_residuals->layer("lc");
              customPlotLc_residuals->moveLayer(l, customPlotLc_residuals->layer(customPlotLc_residuals->layerCount()-1));

              //init_trend();


              customPlotLc_residuals->replot();

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



void MainWindow::titleDoubleClickLc_residuals(QMouseEvent* event)
{
    Q_UNUSED(event)
            if (QCPTextElement *title = qobject_cast<QCPTextElement*>(sender())){
                // Set the plot title by double clicking on it
                bool ok;
                QString newTitle = QInputDialog::getText(this, "QcustomPlotLc_residuals example", "New plot title:", QLineEdit::Normal, "", &ok);
                if (ok){
                    string s=newTitle.toUtf8().constData();
                    QString newTitle2="multiplier="+newTitle;
                    title->setText(newTitle2);

                            customPlotLc_residuals->replot();
                }
            }
             cout<<"titleDoubleClick"<<endl;
}


void MainWindow::axisLabelDoubleClickLc_residuals(QCPAxis *axis, QCPAxis::SelectablePart part){
  // Set an axis label by double clicking on it
  if (part == QCPAxis::spAxisLabel){ // only react when the actual axis label is clicked, not tick label or axis backbone
    bool ok;
    QString newLabel = QInputDialog::getText(this, "QcustomPlotLc_residuals example", "New axis label:", QLineEdit::Normal, axis->label(), &ok);
    if (ok){
      axis->setLabel(newLabel);
              customPlotLc_residuals->replot();
    }
  }
    cout<<"axisLabelDoubleClick"<<endl;
}




void MainWindow::legendDoubleClickLc_residuals(QCPLegend *legend, QCPAbstractLegendItem *item){
  // Rename a graph by double clicking on its legend item
  Q_UNUSED(legend)
  if (item){ // only react if item was clicked (user could have clicked on border padding of legend where there is no item, then item is 0)
    QCPPlottableLegendItem *plItem = qobject_cast<QCPPlottableLegendItem*>(item);
    bool ok;
    QString newName = QInputDialog::getText(this, "QcustomPlotLc_residuals example", "New graph name:", QLineEdit::Normal, plItem->plottable()->name(), &ok);
    if (ok){
      plItem->plottable()->setName(newName);
             customPlotLc_residuals->replot();
    }
  }
  cout<<"legendDoubleClick"<<endl;

}




void MainWindow::selectionChangedLc_residuals(){

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

           if (customPlotLc_residuals->xAxis->selectedParts().testFlag(QCPAxis::spAxis) || customPlotLc_residuals->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
               customPlotLc_residuals->xAxis2->selectedParts().testFlag(QCPAxis::spAxis) || customPlotLc_residuals->xAxis2->selectedParts().testFlag(QCPAxis::spTickLabels)){
                   customPlotLc_residuals->xAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
                   customPlotLc_residuals->xAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
           }
           // make left and right axes be selected synchronously, and handle axis and tick labels as one selectable object:
           if (customPlotLc_residuals->yAxis->selectedParts().testFlag(QCPAxis::spAxis) || customPlotLc_residuals->yAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
               customPlotLc_residuals->yAxis2->selectedParts().testFlag(QCPAxis::spAxis) || customPlotLc_residuals->yAxis2->selectedParts().testFlag(QCPAxis::spTickLabels)){
                   customPlotLc_residuals->yAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
                   customPlotLc_residuals->yAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
           }

           // synchronize selection of graphs with selection of corresponding legend items:

           for (int i=0; i<customPlotLc_residuals->graphCount(); ++i){
               //cout<<"I="<<i<<endl;
               QCPGraph *graph = customPlotLc_residuals->graph(i);

               QCPPlottableLegendItem *item = customPlotLc_residuals->legend->itemWithPlottable(graph);
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

                   if(customPlotLc_residuals->graphCount()>0){

                      QCPDataSelection selection = customPlotLc_residuals->graph(0)->selection();
                      double sum = 0;
                      foreach (QCPDataRange dataRange, selection.dataRanges()){
                        //cout<<dataRange.begin()<<endl;
                        QCPGraphDataContainer::const_iterator begin = customPlotLc_residuals->graph(0)->data()->at(dataRange.begin()); // get range begin iterator from index
                        QCPGraphDataContainer::const_iterator end = customPlotLc_residuals->graph(0)->data()->at(dataRange.end()); // get range end iterator from index
                        for (QCPGraphDataContainer::const_iterator it=begin; it!=end; ++it){
                          // iterator "it" will go through all selected data points, as an example, we calculate the value average
                          //sum += it->value;
                          _value_selected.push_back(it->value);
                          _key_selected.push_back(it->key);
                        }
                      }
                    }
}


void MainWindow::mousePressLc_residuals(QMouseEvent* event){
  // if an axis is selected, only allow the direction of that axis to be dragged
  // if no axis is selected, both directions may be dragged

            bool axis_set_on=false;
            if (customPlotLc_residuals->xAxis->selectedParts().testFlag(QCPAxis::spAxis)){
                customPlotLc_residuals->axisRect()->setRangeDrag(customPlotLc_residuals->xAxis->orientation());
                axis_set_on=true;
            }else if (customPlotLc_residuals->yAxis->selectedParts().testFlag(QCPAxis::spAxis)){
                customPlotLc_residuals->axisRect()->setRangeDrag(customPlotLc_residuals->yAxis->orientation());
                axis_set_on=true;
            }else{
                customPlotLc_residuals->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
            }
            double xCoord = customPlotLc_residuals->xAxis->pixelToCoord(event->pos().x());
            double yCoord = customPlotLc_residuals->yAxis->pixelToCoord(event->pos().y());
            //cout<<"add plot: mouse move, click on: xCoord="<<xCoord<<" yCoord="<<yCoord<<endl;

}



void MainWindow::mouseDoubleClickLc_residuals(QMouseEvent* event){

    //double x=event->pos().x();
    //cout<<"mouseDoubleClick pres"<<x<<endl;


            double xCoord = customPlotLc_residuals->xAxis->pixelToCoord(event->pos().x());
            double yCoord = customPlotLc_residuals->yAxis->pixelToCoord(event->pos().y());

            QString message = QString("Clicked at data point #%1 with value %2.").arg(xCoord).arg(yCoord);
            //ui->statusBar->showMessage(message, 25000);

            //cout<<"mouseDoubleClick: xCoord="<<xCoord<<" yCoord="<<yCoord<<endl;
            QString str=QString{"%1"}.arg(xCoord);

            customPlotLc_residuals->rescaleAxes();
            customPlotLc_residuals->replot();

}

void MainWindow::mouseWheelLc_residuals(){
  // if an axis is selected, only allow the direction of that axis to be zoomed
  // if no axis is selected, both directions may be zoomed

  //cout<<"mouseWheel"<<endl;

           if (customPlotLc_residuals->xAxis->selectedParts().testFlag(QCPAxis::spAxis)){
              customPlotLc_residuals->axisRect()->setRangeZoom(customPlotLc_residuals->xAxis->orientation());
              //customPlotLc_residuals->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
              //cout<<"xAxis"<<endl;
           }else if (customPlotLc_residuals->yAxis->selectedParts().testFlag(QCPAxis::spAxis)){
              customPlotLc_residuals->axisRect()->setRangeZoom(customPlotLc_residuals->yAxis->orientation());
              //cout<<"yAxis"<<endl;
           } else{
              customPlotLc_residuals->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
              //customPlotLc_residuals->axisRect()->setRangeZoom(customPlotLc_residuals->xAxis->orientation());
              //customPlotLc_residuals->axisRect()->setRangeZoom(customPlotLc_residuals->yAxis->orientation());
              //cout<<"zoom"<<endl;

           }


}


void MainWindow::removeSelectedGraphLc_residuals(){
  cout<<"removeSelectedGraph"<<endl;


  //QList<QCPGraph*>  qlist=customPlotLc_residuals[0]->selectedGraphs ( );
  //if(qlist.empty()){
  //    cout<<"no graph selected"<<endl;
  //}else{
     //cout<<"some graph is selected"<<endl;
   //  for(auto it=qlist.begin();it!=qlist.end();++it){
         //cout<<*it<<endl;
         //if(*it==customPlotLc_residuals[0]->graph(0)){
         //    cout<<"the grapth(0) was selected"<<endl;
         //}
   //  }

  //}



}

void MainWindow::removeAllGraphsLc_residuals(){
           customPlotLc_residuals->clearGraphs();
           customPlotLc_residuals->replot();



}



void MainWindow::contextMenuRequestLc_residuals(QPoint pos){
  QMenu *menu = new QMenu(this);
  //menu = new QMenu(add_plot_plot_dialog);
  //QMenu *menu = new QMenu(this);
  menu->setAttribute(Qt::WA_DeleteOnClose);

         if (false && customPlotLc_residuals->legend->selectTest(pos, false) >= 0){
            menu->addAction("Move to top left", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignLeft));
            menu->addAction("Move to top center", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignHCenter));
            menu->addAction("Move to top right", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignRight));
            menu->addAction("Move to bottom right", this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignRight));
            menu->addAction("Move to bottom left", this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignLeft));
         }else if(customPlotLc_residuals->xAxis->selectTest(pos,false)>=0){
            menu->addAction("Reverse x axis", this, SLOT(reverse_xAxis()));
         }else if(customPlotLc_residuals->yAxis->selectTest(pos,false)>=0){
            menu->addAction("Reverse y axis", this, SLOT(reverse_yAxis()));
         }else{
            menu->addAction("Save residuals to pdf", this, SLOT(savepdfLc_residuals()));
            menu->addAction("Save residuals to data file", this, SLOT(resid_save_resid()));
            if(_key_selected.size()>0){
               menu->addAction("clear selected data", this, SLOT(clear_selected_dataLc_residuals()));
            }
            menu->addAction("remove selected data",this, SLOT(remove_selected_dataLc_residuals()));
            /*if(!constant_border){
                menu->addAction("set constant margins",this, SLOT(set_constant_border()));
            }else{
                menu->addAction("set dynamic margins",this, SLOT(set_dynamic_border()));
            }*/
            //menu->addAction("rescale", this, SLOT(rescale()));


         }

         QList<QCPGraph*>  qlist=customPlotLc_residuals->selectedGraphs ( );
         if(qlist.empty()){
             //cout<<"no graph selected"<<endl;
         }else{
             //cout<<"some graph is selected"<<endl;
             for(auto it=qlist.begin();it!=qlist.end();++it){
                //cout<<*it<<endl;
                for(int i=0;i<customPlotLc_residuals->graphCount();++i){
                   if(*it==customPlotLc_residuals->graph(i)){
                      //cout<<"the grapth("<<i<<") was selected"<<endl;
                      //menu->addAction("remove noise", this, SLOT(removenoise()));
                   }
                }
             }

         }

         menu->popup(customPlotLc_residuals->mapToGlobal(pos));

}


void MainWindow::resid_save_resid(){
    int n=table->rowCount();
    size_t nlc=_file.file().size();
    if(_residuals.size()==nlc){
        string input_file_name=_file.file_name();
        input_file_name=f_remove_ext(input_file_name);
        string name=input_file_name+"_data_resid_n"+to_string(n);
        ofstream fo{name};
        for(size_t i=0;i<nlc;++i){
           fo<<_file.file()[i][0]<<" "<<_residuals[i]<<" "<<_file.file()[i][2]<<endl;
        }
    }
}

bool existpdflc_residuals (const std::string& name) {
   return ( access( name.c_str(), F_OK ) != -1 );
}

void MainWindow::remove_selected_dataLc_residuals(){
    cout<<"removing selected data"<<endl;
    /*
    if(_ind_graph_lc>=0){
      QCPDataSelection selection = customPlotLc_residuals->graph(_ind_graph_lc)->selection();
      double sum = 0;
      data_for_removing_x.clear();
      data_for_removing_y.clear();
      foreach (QCPDataRange dataRange, selection.dataRanges()){
        QCPGraphDataContainer::const_iterator begin = customPlotLc_residuals->graph(_ind_graph_lc)->data()->at(dataRange.begin()); // get range begin iterator from index
        QCPGraphDataContainer::const_iterator end = customPlotLc_residuals->graph(_ind_graph_lc)->data()->at(dataRange.end()); // get range end iterator from index
        for (QCPGraphDataContainer::const_iterator it=begin; it!=end; ++it){
           // iterator "it" will go through all selected data points, as an example, we calculate the value average
           sum += it->value;
           data_for_removing_x.push_back(it->key);
           data_for_removing_y.push_back(it->value);
        }
      }
      double average = sum/selection.dataPointCount();
      customPlotLc_residuals->graph(_ind_graph_lc)->setSelection(QCPDataSelection(QCPDataRange()));
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
             if(_init_customPlotLc_residuals_ok){
                 plot_lc();
             }
          }


   }
   */

}

void MainWindow::clear_selected_dataLc_residuals(){
    _key_selected.clear();
    _value_selected.clear();
    customPlotLc_residuals->deselectAll();
    customPlotLc_residuals->replot();
}


void MainWindow::reverse_xAxisLc_residuals(){
    //cout<<"reversed = "<<customPlotLc_residuals->xAxis->rangeReversed()<<endl;
    if(customPlotLc_residuals->xAxis->rangeReversed()){
        customPlotLc_residuals->xAxis->setRangeReversed(false);
        xrplot=false;
    }else{
        customPlotLc_residuals->xAxis->setRangeReversed(true);
        xrplot=true;
    }
    customPlotLc_residuals->replot();
}

void MainWindow::reverse_yAxisLc_residuals(){
   //cout<<"reversed = "<<customPlotLc_residuals->yAxis->rangeReversed()<<endl;
   if(customPlotLc_residuals->yAxis->rangeReversed()){
       customPlotLc_residuals->yAxis->setRangeReversed(false);
       yrplot=false;
   }else{
       customPlotLc_residuals->yAxis->setRangeReversed(true);
       yrplot=true;
   }
   customPlotLc_residuals->replot();
}



void MainWindow::savepdfLc_residuals(){
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
    string name=input_file_name+"_data_residuals_n"+to_string(n)+".pdf";


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
    //cout<<"customPlotLc_residuals[i]->width()="<<customPlotLc_residuals[i]->width()<<endl;
    //double xscale = printer.pageRect().width() / double(customPlotLc_residuals[i]->width());
    //double yscale = printer.pageRect().height() / double(customPlotLc_residuals[i]->height());
    //customPlotLc_residuals[i]->savePdf(name.c_str(), customPlotLc_residuals[i]->width(), customPlotLc_residuals[i]->height() );
    //customPlotLc_residuals[i]->savePdf(name.c_str(), printer.pageRect().width()/2, printer.pageRect().width()/2 );

    customPlotLc_residuals->savePdf(name.c_str(), 800, 500 );
    customPlotLc_residuals->replot();

    QString message = QString(("saving to pdf = "+name).c_str());
    this->statusBar()->showMessage(message, 0);

    label_info_fitting->setText(label_info_fitting2->text());
    string text;
    text="<font color="+NLSF_info_color_font.toStdString()+">pdf: saving to "+name;
    label_info_fitting2->setText(text.c_str());

}



void MainWindow::moveLegendLc_residuals()
{
  if (QAction* contextAction = qobject_cast<QAction*>(sender())) // make sure this slot is really called by a context menu action, so it carries the data we need
  {
    bool ok;
    int dataInt = contextAction->data().toInt(&ok);
    if (ok){

                customPlotLc_residuals->axisRect()->insetLayout()->setInsetAlignment(0, (Qt::Alignment)dataInt);
                customPlotLc_residuals->replot();


    }
  }
}

void MainWindow::graphClickedLc_residuals(QCPAbstractPlottable *plottable, int dataIndex)
{
  // since we know we only have QCPGraphs in the plot, we can immediately access interface1D()
  // usually it's better to first check whether interface1D() returns non-zero, and only then use it.
  double dataValue = plottable->interface1D()->dataMainValue(dataIndex);
  double dataKey = plottable->interface1D()->dataSortKey(dataIndex);
  QString message = QString("Clicked on graph '%1' at x= %2, y= %3.").arg(plottable->name()).arg(dataKey).arg(dataValue);
  this->statusBar()->showMessage(message, 0);


  double xCoord=0, yCoord=0;

         QList<QCPGraph*>  qlist=customPlotLc_residuals->selectedGraphs ( );
         size_t  n=customPlotLc_residuals->graphCount();
         if(qlist.empty()){
              cout<<"no graph selected"<<endl;
         }else{
             cout<<"some graph is selected"<<endl;
             for(auto it=qlist.begin();it!=qlist.end();++it){
                  //cout<<*it<<endl;
                  for(int j=0;j<n;++j){
                     if(*it==customPlotLc_residuals->graph(j)){
                         //cout<<"the graph "<<j<<" was selected"<<endl;
                     }
                  }
             }
        }

}


void MainWindow::graphDoubleClickedLc_residuals(QCPAbstractPlottable *plottable, int dataIndex)
{
  // since we know we only have QCPGraphs in the plot, we can immediately access interface1D()
  // usually it's better to first check whether interface1D() returns non-zero, and only then use it.
  double dataValue = plottable->interface1D()->dataMainValue(dataIndex);
  double dataKey = plottable->interface1D()->dataSortKey(dataIndex);
  QString message = QString("Clicked on graph '%1' at x= %2, y= %3.").arg(plottable->name()).arg(dataKey).arg(dataValue);
  this->statusBar()->showMessage(message, 0);

  //cout<<"graphDoubleClicked: dataindex="<<dataIndex<<" dataKey="<<dataKey<<" dataValue="<<dataValue<<endl;

}




void MainWindow::onMouseMoveLc_residuals(QMouseEvent *event){
    double xCoord=0, yCoord=0;
           xCoord = customPlotLc_residuals->xAxis->pixelToCoord(event->pos().x());
           yCoord = customPlotLc_residuals->yAxis->pixelToCoord(event->pos().y());


    QString message = QString("%1, %2")
            .arg(xCoord).arg(yCoord);

   //ui->statusBar->setStyleSheet("QStatusBar{color:red}") if needed
    this->statusBar()->setStyleSheet("color: orange");
    this->statusBar()->showMessage(message, 0);

}



void MainWindow::mouseReleaseLc_residuals(QMouseEvent* event ){
    //cout<<"add plot: mouse release"<<endl;
    /*
          double xCoord = customPlotLc_residuals->xAxis->pixelToCoord(event->pos().x());
          double yCoord = customPlotLc_residuals->yAxis->pixelToCoord(event->pos().y());
          double xCoord_pix = event->pos().x();
          double yCoord_pix = event->pos().y();
    */

}


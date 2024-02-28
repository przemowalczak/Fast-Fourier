#include "mainwindow.h"




void MainWindow::add_fitted_curve(){
    if(_init_customPlotLc_ok && _fitted_curve_ok){
        //cout<<"add_fitted_curve"<<endl;
        size_t n=_file.file().size();
        if(_ind_graph_fitted_curve_lc==-1){
            _ind_graph_fitted_curve_lc=customPlotLc->graphCount();
            customPlotLc->addGraph();
            string name="fitted_curve";
            if(customPlotLc->layer(name.c_str())==nullptr){
               customPlotLc->addLayer(name.c_str());
            }
            customPlotLc->graph(_ind_graph_fitted_curve_lc)->setLayer(name.c_str());
       }

        //customPlotLc->graph(_ind_graph_fitted_curve_lc)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, Qt::blue,QColor(50,200,100), 5));
        //customPlotLc->graph(_ind_graph_fitted_curve_lc)->setScatterStyle(QCP::);
        //customPlotLc->graph(_ind_graph_fitted_curve_lc)->removeFromLegend();
        customPlotLc->graph(_ind_graph_fitted_curve_lc)->setName("fitted curve");
        customPlotLc->graph(_ind_graph_fitted_curve_lc)->addToLegend();



        QVector<double> qx(n);
        QVector<double> qy(n);
        for(size_t i=0;i<n;++i){
            qx[i]=_file.file()[i][0];
            qy[i]=_fitted_curve[i];
        }

        QPen selectedpen;
        selectedpen.setStyle(Qt::SolidLine);
        selectedpen.setWidth(3);
        selectedpen.setColor(QColor(180,180,180));
        QPen pen;
        //pen.setStyle(Qt::DotLine);
        pen.setStyle(Qt::SolidLine);
        pen.setWidthF(2);
        pen.setColor(QColor(102, 255, 102));
        pen.setColor(QColor(202, 205, 10));
        pen.setColor(QColor(lc_fitted_line_color));

        customPlotLc->graph(_ind_graph_fitted_curve_lc)->setPen(pen);
        customPlotLc->graph(_ind_graph_fitted_curve_lc)->setData(qx,qy);
        customPlotLc->graph(_ind_graph_fitted_curve_lc)->selectionDecorator()->setPen(selectedpen);
        customPlotLc->graph(_ind_graph_fitted_curve_lc)->setSelectable(QCP::stNone);

        QCPLayer *l = customPlotLc->layer("fitted_curve");
        customPlotLc->moveLayer(l, customPlotLc->layer(customPlotLc->layerCount()-1));

        customPlotLc->replot();
    }
}



void MainWindow::plot_lc(){
    if(_init_customPlotLc_ok){
        size_t n=_file.file().size();
        if(n>0){
            if(_file.head().size()>=3){
               QVector<double> qx(n);
               QVector<double> qy(n);
               QVector<double> qerr(n);
               vector<double> dT(n-1);

               _xmin_Lc=_file.file()[0][0];
               _xmax_Lc=_file.file()[0][0];
               _ymin_Lc=_file.file()[0][1];
               _ymax_Lc=_file.file()[0][1];
               for(size_t i=0;i<n;++i){
                   qx[i]=_file.file()[i][0];
                   qy[i]=_file.file()[i][1];
                   qerr[i]=_file.file()[i][2];
                   if(_xmax_Lc<qx[i])_xmax_Lc=qx[i];
                   if(_xmin_Lc>qx[i])_xmin_Lc=qx[i];
                   if(_ymax_Lc<qy[i])_ymax_Lc=qy[i];
                   if(_ymin_Lc>qy[i])_ymin_Lc=qy[i];

               }
               if(_ind_graph_lc==-1){
                   _ind_graph_lc=customPlotLc->graphCount();
                   customPlotLc->addGraph();
                   string name="lc";
                   if(customPlotLc->layer(name.c_str())==nullptr){
                      customPlotLc->addLayer(name.c_str());
                   }
                   customPlotLc->graph(_ind_graph_lc)->setLayer(name.c_str());
                   ErrorBars = new QCPErrorBars (customPlotLc->xAxis, customPlotLc->yAxis);
              }
              //customPlotLc->graph(_ind_graph_lc)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, Qt::blue,QColor(50,200,100), 5));
               customPlotLc->graph(_ind_graph_lc)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QColor(lc_line_color),QColor(lc_point_color), 5));
              //customPlotLc->graph()->removeFromLegend();
              customPlotLc->graph(_ind_graph_lc)->addToLegend();

              _T0=_xmin_Lc;
              _dT=_xmax_Lc-_xmin_Lc;
              if(first_lc){
                 spinBox_resolution_for_combination->setValue(_resolution_for_combination_factor/_dT);
                 spinBox_resolution_for_combination->setSingleStep(_resolution_for_combination_step*_resolution_for_combination_factor/_dT);
                 //spinBox_resolution_for_combination->setValue(0.4);
                 _resolution=_resolution_for_combination_factor/_dT;
                 if(_combo_settings_action_General_dialog_init){
                     _skipp_peaks_resolution->setValue(_resolution_for_combination_factor/_dT);
                     _skipp_peaks_resolution->setSingleStep(_resolution_for_combination_step*_resolution_for_combination_factor/_dT);
                 }
              }

              if(first_lc){
                  first_lc=false;
                  for(int i=1;i<n;++i){
                          dT[i-1]=qx[i]-qx[i-1];
                  }

                  cl_stat stat;
                  stat.init(dT);
                  stat.compute();

                  first_lc_add =", min(dT)="+to_string(stat.min());
                  first_lc_add+=", max(dT)="+to_string(stat.max());
                  first_lc_add+=", median(dT)="+to_string(stat.mediana());
                  first_lc_add+=", mean(dT)="+to_string(stat.mean());
                  first_lc_add+=", Ny(mean)="+to_string(1.0/(2*stat.mean()));


              }
              //customPlotLc->graph(_ind_graph_lc)->setName(("data, DT="+to_string(_dT)+", 1/DT="+to_string(1/_dT)).c_str());
              customPlotLc->graph(_ind_graph_lc)->setName("data");
              customPlotLc->graph(_ind_graph_lc)->setSelectable(QCP::stMultipleDataRanges);
              //customPlotLc->graph(_ind_graph_lc)->setSelectable(QCP::stSingleData);

              string lcname="";
              lcname=f_get_file_name_from_path(_file.file_name());
              string text="<font color="+basic_color_font.toStdString()+">file="+lcname+", n="+to_string(n)+", DT="+to_string(_dT)+", 1/DT="+to_string(1/_dT);
              text+=first_lc_add;
              label_info->setLocale(QLocale::C);
              label_info->setText(text.c_str());



              ErrorBars->setSelectable(QCP::stMultipleDataRanges);
              //ErrorBars->setSelectable(QCP::stNone);
              //ErrorBars->setSelectable(QCP::stSingleData);
              ErrorBars->setData(qerr);
              ErrorBars->removeFromLegend();
              ErrorBars->setErrorType(QCPErrorBars::etValueError);
              ErrorBars->setDataPlottable(customPlotLc->graph(_ind_graph_lc));
              ErrorBars->setWhiskerWidth(10);
              ErrorBars->setPen(QColor(0, 0, 255));
              ErrorBars->setPen(QColor(lc_line_color));

              QPen selectedpen;
              selectedpen.setStyle(Qt::SolidLine);
              selectedpen.setWidth(3);
              selectedpen.setColor(QColor(180,180,180));
              customPlotLc->graph(_ind_graph_lc)->setPen(QColor(lc_line_color));
              customPlotLc->graph(_ind_graph_lc)->selectionDecorator()->setPen(selectedpen);
              customPlotLc->graph(_ind_graph_lc)->selectionDecorator()->setBrush(QColor(255,0,0,20));
              customPlotLc->graph(_ind_graph_lc)->selectionDecorator()->setScatterStyle(QCPScatterStyle::ssSquare);
              ErrorBars->selectionDecorator()->setPen(selectedpen);

              customPlotLc->graph(_ind_graph_lc)->setData(qx,qy);
              customPlotLc->xAxis->setRange(_xmin_Lc,_xmax_Lc);
              customPlotLc->yAxis->setRange(_ymin_Lc,_ymax_Lc);

              QCPLayer *l = customPlotLc->layer("lc");
              customPlotLc->moveLayer(l, customPlotLc->layer(customPlotLc->layerCount()-1));

              //init_trend();


              customPlotLc->replot();

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




void MainWindow::titleDoubleClickLc(QMouseEvent* event)
{
    Q_UNUSED(event)
            if (QCPTextElement *title = qobject_cast<QCPTextElement*>(sender())){
                // Set the plot title by double clicking on it
                bool ok;
                QString newTitle = QInputDialog::getText(this, "QcustomPlotLc example", "New plot title:", QLineEdit::Normal, "", &ok);
                if (ok){
                    string s=newTitle.toUtf8().constData();
                    QString newTitle2="multiplier="+newTitle;
                    title->setText(newTitle2);

                            customPlotLc->replot();
                }
            }
             cout<<"titleDoubleClick"<<endl;
}


void MainWindow::axisLabelDoubleClickLc(QCPAxis *axis, QCPAxis::SelectablePart part){
  // Set an axis label by double clicking on it
  if (part == QCPAxis::spAxisLabel){ // only react when the actual axis label is clicked, not tick label or axis backbone
    bool ok;
    QString newLabel = QInputDialog::getText(this, "QcustomPlotLc example", "New axis label:", QLineEdit::Normal, axis->label(), &ok);
    if (ok){
      axis->setLabel(newLabel);
              customPlotLc->replot();
    }
  }
    cout<<"axisLabelDoubleClick"<<endl;
}




void MainWindow::legendDoubleClickLc(QCPLegend *legend, QCPAbstractLegendItem *item){
  // Rename a graph by double clicking on its legend item
  Q_UNUSED(legend)
  if (item){ // only react if item was clicked (user could have clicked on border padding of legend where there is no item, then item is 0)
    QCPPlottableLegendItem *plItem = qobject_cast<QCPPlottableLegendItem*>(item);
    bool ok;
    QString newName = QInputDialog::getText(this, "QcustomPlotLc example", "New graph name:", QLineEdit::Normal, plItem->plottable()->name(), &ok);
    if (ok){
      plItem->plottable()->setName(newName);
             customPlotLc->replot();
    }
  }
  cout<<"legendDoubleClick"<<endl;

}




void MainWindow::selectionChangedLc(){

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

           if (customPlotLc->xAxis->selectedParts().testFlag(QCPAxis::spAxis) || customPlotLc->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
               customPlotLc->xAxis2->selectedParts().testFlag(QCPAxis::spAxis) || customPlotLc->xAxis2->selectedParts().testFlag(QCPAxis::spTickLabels)){
                   customPlotLc->xAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
                   customPlotLc->xAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
           }
           // make left and right axes be selected synchronously, and handle axis and tick labels as one selectable object:
           if (customPlotLc->yAxis->selectedParts().testFlag(QCPAxis::spAxis) || customPlotLc->yAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
               customPlotLc->yAxis2->selectedParts().testFlag(QCPAxis::spAxis) || customPlotLc->yAxis2->selectedParts().testFlag(QCPAxis::spTickLabels)){
                   customPlotLc->yAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
                   customPlotLc->yAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
           }

           // synchronize selection of graphs with selection of corresponding legend items:

           for (int i=0; i<customPlotLc->graphCount(); ++i){
               //cout<<"I="<<i<<endl;
               QCPGraph *graph = customPlotLc->graph(i);

               QCPPlottableLegendItem *item = customPlotLc->legend->itemWithPlottable(graph);
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

                   if(customPlotLc->graphCount()>0){

                      QCPDataSelection selection = customPlotLc->graph(0)->selection();
                      double sum = 0;
                      foreach (QCPDataRange dataRange, selection.dataRanges()){
                        //cout<<dataRange.begin()<<endl;
                        QCPGraphDataContainer::const_iterator begin = customPlotLc->graph(0)->data()->at(dataRange.begin()); // get range begin iterator from index
                        QCPGraphDataContainer::const_iterator end = customPlotLc->graph(0)->data()->at(dataRange.end()); // get range end iterator from index
                        for (QCPGraphDataContainer::const_iterator it=begin; it!=end; ++it){
                          // iterator "it" will go through all selected data points, as an example, we calculate the value average
                          //sum += it->value;
                          _value_selected.push_back(it->value);
                          _key_selected.push_back(it->key);
                        }
                      }
                    }
}


void MainWindow::mousePressLc(QMouseEvent* event){
  // if an axis is selected, only allow the direction of that axis to be dragged
  // if no axis is selected, both directions may be dragged

            bool axis_set_on=false;
            if (customPlotLc->xAxis->selectedParts().testFlag(QCPAxis::spAxis)){
                customPlotLc->axisRect()->setRangeDrag(customPlotLc->xAxis->orientation());
                axis_set_on=true;
            }else if (customPlotLc->yAxis->selectedParts().testFlag(QCPAxis::spAxis)){
                customPlotLc->axisRect()->setRangeDrag(customPlotLc->yAxis->orientation());
                axis_set_on=true;
            }else{
                customPlotLc->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
            }
            double xCoord = customPlotLc->xAxis->pixelToCoord(event->pos().x());
            double yCoord = customPlotLc->yAxis->pixelToCoord(event->pos().y());
            //cout<<"add plot: mouse move, click on: xCoord="<<xCoord<<" yCoord="<<yCoord<<endl;

}



void MainWindow::mouseDoubleClickLc(QMouseEvent* event){

    //double x=event->pos().x();
    //cout<<"mouseDoubleClick pres"<<x<<endl;


            double xCoord = customPlotLc->xAxis->pixelToCoord(event->pos().x());
            double yCoord = customPlotLc->yAxis->pixelToCoord(event->pos().y());

            QString message = QString("Clicked at data point #%1 with value %2.").arg(xCoord).arg(yCoord);
            //ui->statusBar->showMessage(message, 25000);

            //cout<<"mouseDoubleClick: xCoord="<<xCoord<<" yCoord="<<yCoord<<endl;
            QString str=QString{"%1"}.arg(xCoord);

            customPlotLc->rescaleAxes();
            customPlotLc->replot();

}

void MainWindow::mouseWheelLc(){
  // if an axis is selected, only allow the direction of that axis to be zoomed
  // if no axis is selected, both directions may be zoomed

  //cout<<"mouseWheel"<<endl;

           if (customPlotLc->xAxis->selectedParts().testFlag(QCPAxis::spAxis)){
              customPlotLc->axisRect()->setRangeZoom(customPlotLc->xAxis->orientation());
              //customPlotLc->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
              //cout<<"xAxis"<<endl;
           }else if (customPlotLc->yAxis->selectedParts().testFlag(QCPAxis::spAxis)){
              customPlotLc->axisRect()->setRangeZoom(customPlotLc->yAxis->orientation());
              //cout<<"yAxis"<<endl;
           } else{
              customPlotLc->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
              //customPlotLc->axisRect()->setRangeZoom(customPlotLc->xAxis->orientation());
              //customPlotLc->axisRect()->setRangeZoom(customPlotLc->yAxis->orientation());
              //cout<<"zoom"<<endl;

           }


}


void MainWindow::removeSelectedGraphLc(){
  cout<<"removeSelectedGraph"<<endl;


  //QList<QCPGraph*>  qlist=customPlotLc[0]->selectedGraphs ( );
  //if(qlist.empty()){
  //    cout<<"no graph selected"<<endl;
  //}else{
     //cout<<"some graph is selected"<<endl;
   //  for(auto it=qlist.begin();it!=qlist.end();++it){
         //cout<<*it<<endl;
         //if(*it==customPlotLc[0]->graph(0)){
         //    cout<<"the grapth(0) was selected"<<endl;
         //}
   //  }

  //}



}

void MainWindow::removeAllGraphsLc(){
           customPlotLc->clearGraphs();
           customPlotLc->replot();



}



void MainWindow::contextMenuRequestLc(QPoint pos){
  QMenu *menu = new QMenu(this);
  //menu = new QMenu(add_plot_plot_dialog);
  //QMenu *menu = new QMenu(this);
  menu->setAttribute(Qt::WA_DeleteOnClose);

         if (false && customPlotLc->legend->selectTest(pos, false) >= 0){
            menu->addAction("Move to top left", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignLeft));
            menu->addAction("Move to top center", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignHCenter));
            menu->addAction("Move to top right", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignRight));
            menu->addAction("Move to bottom right", this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignRight));
            menu->addAction("Move to bottom left", this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignLeft));
         }else if(customPlotLc->xAxis->selectTest(pos,false)>=0){
            menu->addAction("Reverse x axis", this, SLOT(reverse_xAxis()));
         }else if(customPlotLc->yAxis->selectTest(pos,false)>=0){
            menu->addAction("Reverse y axis", this, SLOT(reverse_yAxis()));
         }else{
            menu->addAction("Save lc to pdf", this, SLOT(savepdfLc()));
            menu->addAction("Save lc to data file", this, SLOT(lc_save_lc()));
            if(_key_selected.size()>0){
               menu->addAction("clear selected data", this, SLOT(clear_selected_data()));
            }
            menu->addAction("remove selected data",this, SLOT(remove_selected_data()));
            /*if(!constant_border){
                menu->addAction("set constant margins",this, SLOT(set_constant_border()));
            }else{
                menu->addAction("set dynamic margins",this, SLOT(set_dynamic_border()));
            }*/
            //menu->addAction("rescale", this, SLOT(rescale()));


         }

         QList<QCPGraph*>  qlist=customPlotLc->selectedGraphs ( );
         if(qlist.empty()){
             //cout<<"no graph selected"<<endl;
         }else{
             //cout<<"some graph is selected"<<endl;
             for(auto it=qlist.begin();it!=qlist.end();++it){
                //cout<<*it<<endl;
                for(int i=0;i<customPlotLc->graphCount();++i){
                   if(*it==customPlotLc->graph(i)){
                      //cout<<"the grapth("<<i<<") was selected"<<endl;
                      //menu->addAction("remove noise", this, SLOT(removenoise()));
                   }
                }
             }

         }

         menu->popup(customPlotLc->mapToGlobal(pos));

}

void MainWindow::lc_save_lc(){
    int n=table->rowCount();
    size_t nlc=_file.file().size();
    if(nlc>0){
       string input_file_name=_file.file_name();
       input_file_name=f_remove_ext(input_file_name);
       string name=input_file_name+"_data_lc_n"+to_string(n);
       ofstream fo{name};
       cout<<"name="<<name<<endl;
       if(_fitted_curve.size()==nlc){
           for(size_t i=0;i<nlc;++i){
               fo<<_file.file()[i][0]<<" "<<_file.file()[i][1]<<" "<<_file.file()[i][2]<<" "<<_fitted_curve[i]<<endl;
           }
       }else{
           for(size_t i=0;i<nlc;++i){
               fo<<_file.file()[i][0]<<" "<<_file.file()[i][1]<<" "<<_file.file()[i][2]<<endl;
           }
       }
    }
}

bool existpdflc (const std::string& name) {
   return ( access( name.c_str(), F_OK ) != -1 );
}

void MainWindow::remove_selected_data(){
    cout<<"removing selected data"<<endl;
    if(_ind_graph_lc>=0){
      QCPDataSelection selection = customPlotLc->graph(_ind_graph_lc)->selection();
      double sum = 0;
      data_for_removing_x.clear();
      data_for_removing_y.clear();
      foreach (QCPDataRange dataRange, selection.dataRanges()){
        QCPGraphDataContainer::const_iterator begin = customPlotLc->graph(_ind_graph_lc)->data()->at(dataRange.begin()); // get range begin iterator from index
        QCPGraphDataContainer::const_iterator end = customPlotLc->graph(_ind_graph_lc)->data()->at(dataRange.end()); // get range end iterator from index
        for (QCPGraphDataContainer::const_iterator it=begin; it!=end; ++it){
           // iterator "it" will go through all selected data points, as an example, we calculate the value average
           sum += it->value;
           data_for_removing_x.push_back(it->key);
           data_for_removing_y.push_back(it->value);
        }
      }
      double average = sum/selection.dataPointCount();
      customPlotLc->graph(_ind_graph_lc)->setSelection(QCPDataSelection(QCPDataRange()));
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
             if(_init_customPlotLc_ok){
                 plot_lc();
             }
          }


   }


}

void MainWindow::clear_selected_dataLc(){
    _key_selected.clear();
    _value_selected.clear();
    customPlotLc->deselectAll();
    customPlotLc->replot();
}


void MainWindow::reverse_xAxisLc(){
    //cout<<"reversed = "<<customPlotLc->xAxis->rangeReversed()<<endl;
    if(customPlotLc->xAxis->rangeReversed()){
        customPlotLc->xAxis->setRangeReversed(false);
        xrplot=false;
    }else{
        customPlotLc->xAxis->setRangeReversed(true);
        xrplot=true;
    }
    customPlotLc->replot();
}

void MainWindow::reverse_yAxisLc(){
   //cout<<"reversed = "<<customPlotLc->yAxis->rangeReversed()<<endl;
   if(customPlotLc->yAxis->rangeReversed()){
       customPlotLc->yAxis->setRangeReversed(false);
       yrplot=false;
   }else{
       customPlotLc->yAxis->setRangeReversed(true);
       yrplot=true;
   }
   customPlotLc->replot();
}



void MainWindow::savepdfLc(){
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
    string name=input_file_name+"_data_lc_n"+to_string(n)+".pdf";

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
    //cout<<"customPlotLc[i]->width()="<<customPlotLc[i]->width()<<endl;
    //double xscale = printer.pageRect().width() / double(customPlotLc[i]->width());
    //double yscale = printer.pageRect().height() / double(customPlotLc[i]->height());
    //customPlotLc[i]->savePdf(name.c_str(), customPlotLc[i]->width(), customPlotLc[i]->height() );
    //customPlotLc[i]->savePdf(name.c_str(), printer.pageRect().width()/2, printer.pageRect().width()/2 );

    customPlotLc->savePdf(name.c_str(), 800, 500 );
    customPlotLc->replot();

    QString message = QString(("saving to pdf = "+name).c_str());
    this->statusBar()->showMessage(message, 0);

    label_info_fitting->setText(label_info_fitting2->text());
    string text;
    text="<font color="+NLSF_info_color_font.toStdString()+">pdf: saving to "+name;
    label_info_fitting2->setText(text.c_str());

}



void MainWindow::moveLegendLc()
{
  if (QAction* contextAction = qobject_cast<QAction*>(sender())) // make sure this slot is really called by a context menu action, so it carries the data we need
  {
    bool ok;
    int dataInt = contextAction->data().toInt(&ok);
    if (ok){

                customPlotLc->axisRect()->insetLayout()->setInsetAlignment(0, (Qt::Alignment)dataInt);
                customPlotLc->replot();


    }
  }
}

void MainWindow::graphClickedLc(QCPAbstractPlottable *plottable, int dataIndex)
{
  // since we know we only have QCPGraphs in the plot, we can immediately access interface1D()
  // usually it's better to first check whether interface1D() returns non-zero, and only then use it.
  double dataValue = plottable->interface1D()->dataMainValue(dataIndex);
  double dataKey = plottable->interface1D()->dataSortKey(dataIndex);
  QString message = QString("Clicked on graph '%1' at x= %2, y= %3.").arg(plottable->name()).arg(dataKey).arg(dataValue);
  this->statusBar()->showMessage(message, 0);


  double xCoord=0, yCoord=0;

         QList<QCPGraph*>  qlist=customPlotLc->selectedGraphs ( );
         size_t  n=customPlotLc->graphCount();
         if(qlist.empty()){
              cout<<"no graph selected"<<endl;
         }else{
             cout<<"some graph is selected"<<endl;
             for(auto it=qlist.begin();it!=qlist.end();++it){
                  //cout<<*it<<endl;
                  for(int j=0;j<n;++j){
                     if(*it==customPlotLc->graph(j)){
                         //cout<<"the graph "<<j<<" was selected"<<endl;
                     }
                  }
             }
        }

}


void MainWindow::graphDoubleClickedLc(QCPAbstractPlottable *plottable, int dataIndex)
{
  // since we know we only have QCPGraphs in the plot, we can immediately access interface1D()
  // usually it's better to first check whether interface1D() returns non-zero, and only then use it.
  double dataValue = plottable->interface1D()->dataMainValue(dataIndex);
  double dataKey = plottable->interface1D()->dataSortKey(dataIndex);
  QString message = QString("Clicked on graph '%1' at x= %2, y= %3.").arg(plottable->name()).arg(dataKey).arg(dataValue);
  this->statusBar()->showMessage(message, 0);

  //cout<<"graphDoubleClicked: dataindex="<<dataIndex<<" dataKey="<<dataKey<<" dataValue="<<dataValue<<endl;

}




void MainWindow::onMouseMoveLc(QMouseEvent *event){
    double xCoord=0, yCoord=0;
           xCoord = customPlotLc->xAxis->pixelToCoord(event->pos().x());
           yCoord = customPlotLc->yAxis->pixelToCoord(event->pos().y());


    QString message = QString("%1, %2")
            .arg(xCoord).arg(yCoord);

   //ui->statusBar->setStyleSheet("QStatusBar{color:red}") if needed
    this->statusBar()->setStyleSheet("color: "+basic_color_font+"");
    this->statusBar()->showMessage(message, 0);

}



void MainWindow::mouseReleaseLc(QMouseEvent* event ){
    //cout<<"add plot: mouse release"<<endl;
    /*
          double xCoord = customPlotLc->xAxis->pixelToCoord(event->pos().x());
          double yCoord = customPlotLc->yAxis->pixelToCoord(event->pos().y());
          double xCoord_pix = event->pos().x();
          double yCoord_pix = event->pos().y();
    */

}


#include "mainwindow.h"


void MainWindow::init_freq_table(){
    cout<<"init table"<<endl;
    table->clear();
    //table->insertRow(0);
    table->insertColumn(0);
    QTableWidgetItem* item = new QTableWidgetItem("freq");
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    item->setFlags(item->flags() ^ Qt::ItemIsSelectable);
    table->setHorizontalHeaderItem(0,item);
    table->insertColumn(1);
    QTableWidgetItem* item1 = new QTableWidgetItem("e_freq");
    item1->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    item1->setFlags(item1->flags() ^ Qt::ItemIsSelectable);
    table->setHorizontalHeaderItem(1,item1);
    table->insertColumn(2);
    QTableWidgetItem* item2 = new QTableWidgetItem("A");
    item2->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    table->setHorizontalHeaderItem(2,item2);
    table->insertColumn(3);
    QTableWidgetItem* item3 = new QTableWidgetItem("e_A");
    item3->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    table->setHorizontalHeaderItem(3,item3);
    table->insertColumn(4);
    QTableWidgetItem* item4 = new QTableWidgetItem("phi");
    item4->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    table->setHorizontalHeaderItem(4,item4);
    table->insertColumn(5);
    QTableWidgetItem* item5 = new QTableWidgetItem("e_phi");
    item5->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    table->setHorizontalHeaderItem(5,item5);
    table->insertColumn(6);
    QTableWidgetItem* item6 = new QTableWidgetItem("status");
    item6->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    table->setHorizontalHeaderItem(6,item6);
    table->insertColumn(7);
    QTableWidgetItem* item7 = new QTableWidgetItem("S/N");
    item7->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    table->setHorizontalHeaderItem(7,item7);

    //disconnect(table->horizontalHeader(),SIGNAL(selectionPressed(int)),table,SLOT(selectionColumn(int)));
    //connect(table->horizontalHeader(),SIGNAL(selectionPressed(int)),table,SLOT(selectionColumn_ud(int)));
    //connect(table->horizontalHeader(),SIGNAL(clicked(int)),table,SLOT(selectionColumn_ud(int)));
    //connect(table->horizontalHeader(),SIGNAL(sectionPressed(int)),table,SLOT(selectionColumn_ud(int)));

    cout<<"init done"<<endl;



    table->setStyleSheet(
                "QTableView::item:selected"
                "{"
                "background-color : "+table_color_selection_background+";"
                "selection-color : #000000;"
                "}"
            );

}

void MainWindow::selectionColumn_ud(int icol){
    cout<<"selectionColumn_ud"<<endl;
    _cell_selection_triggered_by_horizontalheader=true;
    /*for(size_t i=0;i<table->rowCount();++i){
        for(size_t j=0;j<table->columnCount();++j){
             table->item(i,j)->setSelected(false);
        }
        //cout<<endl;
    }*/
    _cell_selection_triggered_by_horizontalheader=false;
}

void MainWindow::copy_table_to_backup(){
    QTableWidget *tab_temp= new QTableWidget();
    for(size_t j=0;j<table->columnCount();++j){
        tab_temp->insertColumn(j);
    }
    for(size_t i=0;i<table->rowCount();++i){
        tab_temp->insertRow(i);
        for(size_t j=0;j<table->columnCount();++j){
            tab_temp->setItem(i,j,new QTableWidgetItem(table->item(i,j)->text()));
            //cout<<"tab_temp="<<tab_temp->item(i,j)->text().toStdString()<<" ";
        }
        //cout<<endl;
    }
    if(table_backup.size()<max_table_backup){
       table_backup.push_back(tab_temp);
    }else{
       table_backup.front()->clear();
       while(table_backup.front()->rowCount()>0){
         table_backup.front()->removeRow(0);
       }
       while(table_backup.front()->columnCount()>0){
         table_backup.front()->removeColumn(0);
       }
       table_backup.erase(table_backup.begin());
       table_backup.push_back(tab_temp);
    }
    /*
    for(size_t i=0;i<table_backup.back()->rowCount();++i){
        for(size_t j=0;j<table_backup.back()->columnCount();++j){
            cout<<table_backup.back()->item(i,j)->text().toStdString()<<" ";
        }
        cout<<endl;
    }
    cout<<"table_backup size = "<<table_backup.size()<<endl;
    */

    if(table_backup.size()>0){
        pushB_table_back->setEnabled(true);
    }
    _table_back_iter=0;
}

void MainWindow::table_back_clicked(){
    int nn=table_backup.size()-1-_table_back_iter;
    if(nn>=0){
        //table->clear();
        while(table->rowCount()>0){
            table->removeRow(0);
        }
        //init_freq_table();
        for(size_t i=0;i<table_backup[nn]->rowCount();++i){
            //cout<<"set coppy"<<endl;
            table->insertRow(i);
            table->setRowHeight(i,10);
            for(size_t j=0;j<table_backup[nn]->columnCount();++j){
                table->setItem(i,j,new QTableWidgetItem(table_backup[nn]->item(i,j)->text()));
            }
        }
        ++_table_back_iter;
        pushB_table_forward->setEnabled(true);
        if(nn==0){
            pushB_table_back->setDisabled(true);
        }
    }else{
        pushB_table_back->setDisabled(true);
    }
}
void MainWindow::table_forward_clicked(){
    int nn=table_backup.size()-1-_table_back_iter+2;
    if(nn>=0 && nn<table_backup.size()){
        //table->clear();
        while(table->rowCount()>0){
            table->removeRow(0);
        }
        //init_freq_table();
        for(size_t i=0;i<table_backup[nn]->rowCount();++i){
            //cout<<"set coppy"<<endl;
            table->insertRow(i);
            table->setRowHeight(i,10);
            for(size_t j=0;j<table_backup[nn]->columnCount();++j){
                table->setItem(i,j,new QTableWidgetItem(table_backup[nn]->item(i,j)->text()));
            }
        }
        --_table_back_iter;
        pushB_table_back->setEnabled(true);
        if(nn==0){
            pushB_table_forward->setDisabled(true);
        }
    }else{
        pushB_table_forward->setDisabled(true);
    }
}


void MainWindow::add_freq_to_table(double f,double sn){

    cout<<"adding freq"<<endl;
    if(table->rowCount()==0 && table->columnCount()==0){
        init_freq_table();
        init_info_table();
    }


    int ir=table->rowCount();
    table->insertRow(ir);
    table->setRowHeight(ir,10);
    QTableWidgetItem *item = new QTableWidgetItem(to_string(f).c_str());
    table->setItem(ir,0,item);
    for(auto i=1;i<table->columnCount();++i){
        QTableWidgetItem *item = new QTableWidgetItem("");
        table->setItem(ir,i,item);
    }
    if(sn>=0){
        int ind_sn=-1;
        for(auto i=0;i<table->columnCount();++i){
            //cout<<(table->horizontalHeaderItem(i)->text()).toStdString()<<endl;
            if(table->horizontalHeaderItem(i)->text()=="S/N"){
                ind_sn=i;
                break;
            }
        }
        //cout<<"sn="<<sn<<" ind_sn="<<ind_sn<<endl;
        if(ind_sn!=-1){
            QTableWidgetItem *item = new QTableWidgetItem(to_string(sn).c_str());
            table->setItem(ir,ind_sn,item);
        }
    }
    //cout<<"adding freq done"<<endl;



    check_for_combination();

    update_matrix();

    copy_table_to_backup();


}

void MainWindow::update_matrix(){
    cout<<"update_matrix"<<endl;

    _freq_matrix.clear();
    int ind_freq=-1;
    int ind_status=-1;
    for(auto i=0;i<table->columnCount();++i){
        if(table->horizontalHeaderItem(i)->text()=="status"){
            ind_status=i;
        }
        if(table->horizontalHeaderItem(i)->text()=="freq"){
            ind_freq=i;
        }
    }
    if(ind_status!=-1 && ind_freq!=-1){
        int index=0;
        int nfreq_i=0;
        int nfreq_c=0;
        vector<double> freq_i;
        for(auto i=0;i<table->rowCount();++i){
            //cout<<"i row="<<i<<endl;
            //cout<<_freq_matrix.size()<<endl;
            vector<double> vec;
            if(table->item(i,ind_status)!=nullptr){
                if(table->item(i,ind_status)->text()=="" || table->item(i,ind_status)->text()=="i"){
                    //cout<<"independent frequency "<<endl;
                    ++nfreq_i;
                    for(int j=0;j<nfreq_i-1;++j){
                        vec.push_back(0);
                    }
                    vec.push_back(1);
                    freq_i.push_back(table->item(i,ind_freq)->text().toDouble());

                }else{
                    //cout<<"potential combination found"<<endl;
                    ++nfreq_c;
                    string status=(table->item(i,ind_status)->text()).toStdString();
                    smatch match;
                    //string pattern="\\d+\\.\\d+\\*f\\d";
                    //regex r(pattern);
                    //cout<<"patter="<<pattern<<" "<<status<<endl;
                    //if(regex_match(status,match,r)){
                    //    cout<<"match"<<endl;
                    //}
                    if(regex_match(status,match,regex("\\d+\\*f\\d+")) || regex_match(status,match,regex("\\d+\\.\\d+\\*f\\d+"))){
                       //cout<<"update_matrix: harmonic found"<<endl;
                       /*cout<<match[0]<<endl;
                       cout<<match.prefix()<<endl;
                       cout<<match.suffix()<<endl;
                       cout<<match.length()<<endl;
                       cout<<match.position()<<endl;
                       cout<<match.str()<<endl;*/
                       double mul=f_get_db(status);
                       //cout<<"mul="<<mul<<endl;
                       int ind_c_freq=round(f_get_db(status,"f"));
                       //cout<<"ind_freq="<<ind_c_freq<<endl;
                       //cout<<"_freq_matrix.back().size()="<<_freq_matrix.back().size()<<endl;
                       for(int in=0;in<ind_c_freq-1;++in){
                          vec.push_back(0);
                       }
                       vec.push_back(mul);
                       for(int in=ind_c_freq;in<_freq_matrix.back().size();++in){
                          vec.push_back(0);
                       }
                       double new_freq=0;
                       for(int in=0;in<vec.size();++in){
                           new_freq+=vec[in]*freq_i[in];
                       }
                       //cout<<"new_freq="<<new_freq<<endl;
                       table->item(i,ind_freq)->setText(to_string(new_freq).c_str());
                    }
                    if(regex_match(status,match,regex("\\d+\\*f\\d+\\+\\d+\\*f\\d+")) || regex_match(status,match,regex("\\d+\\*f\\d+\\-\\d+\\*f\\d+")) ||
                       regex_match(status,match,regex("-\\d+\\*f\\d+\\+\\d+\\*f\\d+")) || regex_match(status,match,regex("-\\d+\\*f\\d+\\-\\d+\\*f\\d+"))    ){
                       //cout<<"update_matrix: combination 2e found"<<endl;
                       /*cout<<match[0]<<endl;
                       cout<<match.prefix()<<endl;
                       cout<<match.suffix()<<endl;
                       cout<<match.length()<<endl;
                       cout<<match.position()<<endl;
                       cout<<match.str()<<endl;*/
                       double mul=f_get_db(status);
                       //cout<<"mul="<<mul<<endl;
                       int ind_c_freq=round(f_get_db(status,"f"));
                       //cout<<"ind_freq="<<ind_c_freq<<endl;
                       //cout<<"_freq_matrix.back().size()="<<_freq_matrix.back().size()<<endl;
                       int freq_number_length=(to_string(ind_c_freq)).length();
                       //cout<<"freq_number_length="<<freq_number_length<<endl;
                       string status_r=status.substr(status.find("f")+1+freq_number_length,status.length()-status.find("f")-1-freq_number_length);
                       //cout<<"status_r="<<status_r<<endl;

                       double mul2=f_get_db(status_r);
                       //cout<<"mul2="<<mul2<<endl;
                       int ind_c_freq2=round(f_get_db(status_r,"f"));
                       //cout<<"ind_freq2="<<ind_c_freq2<<endl;

                       for(int in=0;in<ind_c_freq-1;++in){
                          vec.push_back(0);
                       }
                       vec.push_back(mul);
                       for(int in=ind_c_freq;in<ind_c_freq2-1;++in){
                          vec.push_back(0);
                       }
                       vec.push_back(mul2);
                       for(int in=ind_c_freq2;in<_freq_matrix.back().size();++in){
                          vec.push_back(0);
                       }
                       double new_freq=0;
                       for(int in=0;in<vec.size();++in){
                           new_freq+=vec[in]*freq_i[in];
                       }
                       //cout<<"new_freq="<<new_freq<<endl;
                       table->item(i,ind_freq)->setText(to_string(new_freq).c_str());
                    }

                    if(regex_match(status,match,regex("\\d+\\*f\\d+\\+\\d+\\*f\\d+\\+\\d+\\*f\\d+")) || regex_match(status,match,regex("\\d+\\*f\\d+\\-\\d+\\*f\\d+\\+\\d+\\*f\\d+")) ||
                       regex_match(status,match,regex("-\\d+\\*f\\d+\\+\\d+\\*f\\d+\\+\\d+\\*f\\d+")) || regex_match(status,match,regex("-\\d+\\*f\\d+\\-\\d+\\*f\\d+\\+\\d+\\*f\\d+")) ||
                       regex_match(status,match,regex("\\d+\\*f\\d+\\+\\d+\\*f\\d+\\-\\d+\\*f\\d+")) || regex_match(status,match,regex("\\d+\\*f\\d+\\-\\d+\\*f\\d+\\-\\d+\\*f\\d+")) ||
                       regex_match(status,match,regex("-\\d+\\*f\\d+\\+\\d+\\*f\\d+\\-\\d+\\*f\\d+")) || regex_match(status,match,regex("-\\d+\\*f\\d+\\-\\d+\\*f\\d+\\-\\d+\\*f\\d+")) ){
                       //cout<<"update_matrix: combination 3e found"<<endl;
                       /*cout<<match[0]<<endl;
                       cout<<match.prefix()<<endl;
                       cout<<match.suffix()<<endl;
                       cout<<match.length()<<endl;
                       cout<<match.position()<<endl;
                       cout<<match.str()<<endl;*/
                       double mul=f_get_db(status);
                       //cout<<"mul="<<mul<<endl;
                       int ind_c_freq=round(f_get_db(status,"f"));
                       //cout<<"ind_freq="<<ind_c_freq<<endl;
                       //cout<<"_freq_matrix.back().size()="<<_freq_matrix.back().size()<<endl;
                       int freq_number_length=(to_string(ind_c_freq)).length();
                       //cout<<"freq_number_length="<<freq_number_length<<endl;
                       string status_r=status.substr(status.find("f")+1+freq_number_length,status.length()-status.find("f")-1-freq_number_length);
                       //cout<<"status_r="<<status_r<<endl;

                       double mul2=f_get_db(status_r);
                       //cout<<"mul2="<<mul2<<endl;
                       int ind_c_freq2=round(f_get_db(status_r,"f"));
                       //cout<<"ind_freq2="<<ind_c_freq2<<endl;

                       int freq_number_length2=(to_string(ind_c_freq2)).length();
                       //cout<<"freq_number_length2="<<freq_number_length2<<endl;
                       string status_r2=status_r.substr(status_r.find("f")+1+freq_number_length2,status_r.length()-status_r.find("f")-1-freq_number_length2);
                       //cout<<"status_r2="<<status_r2<<endl;

                       double mul3=f_get_db(status_r2);
                       //cout<<"mul3="<<mul3<<endl;
                       int ind_c_freq3=round(f_get_db(status_r2,"f"));
                       //cout<<"ind_freq3="<<ind_c_freq3<<endl;


                       for(int in=0;in<ind_c_freq-1;++in){
                          vec.push_back(0);
                       }
                       vec.push_back(mul);
                       for(int in=ind_c_freq;in<ind_c_freq2-1;++in){
                          vec.push_back(0);
                       }
                       vec.push_back(mul2);
                       for(int in=ind_c_freq2;in<ind_c_freq3-1;++in){
                          vec.push_back(0);
                       }
                       vec.push_back(mul3);
                       for(int in=ind_c_freq3;in<_freq_matrix.back().size();++in){
                          vec.push_back(0);
                       }
                       double new_freq=0;
                       for(int in=0;in<vec.size();++in){
                           new_freq+=vec[in]*freq_i[in];
                       }
                       //cout<<"new_freq="<<new_freq<<endl;
                       table->item(i,ind_freq)->setText(to_string(new_freq).c_str());
                    }

                }

            }else{
                //cout<<"not status element"<<endl;
                ++nfreq_i;
                for(int j=0;j<nfreq_i-1;++j){
                    vec.push_back(0);
                }
                vec.push_back(1);
            }
            _freq_matrix.push_back(vec);
        }
    }
    //cout<<"matrix:"<<endl;
    //cout<<_freq_matrix<<endl;
    //cout<<"-----------"<<_freq_matrix.size()<< endl;

    update_freq_number();
    update_frequency_manager();

}

void MainWindow::table_ContextMenuRequested(const QPoint& pos){
    //cout<<"table_ContextMenuRequested"<<endl;
    QMenu *menu = new QMenu(this);
    menu->setAttribute(Qt::WA_DeleteOnClose);
    if(table->rowCount()>0){
       menu->addAction("save data", this, SLOT(table_save_data()));
       menu->addAction("remove the last row", this, SLOT(table_remove_last_row()));
       menu->addAction("remove this row", this, SLOT(table_remove_this_row()));
       menu->addAction("remove all rows", this, SLOT(table_remove_all_rows()));
    }
    menu->popup(table->mapToGlobal(pos));
}

void MainWindow::table_save_data(){
    if(table->rowCount()>0){
        int n=table->rowCount();
        string input_file_name=_file.file_name();
        input_file_name=f_remove_ext(input_file_name);
        string name=input_file_name+"_data_freq_n"+to_string(n);
        ofstream fo{name};
        vector<int>nc(table->columnCount(),0);
        for(size_t i=0;i<n;++i){
            for(size_t j=0;j<table->columnCount();++j){
               if(nc[j]<table->item(i,j)->text().length()){
                   nc[j]=table->item(i,j)->text().length();
               }
            }
        }
        for(size_t j=0;j<table->columnCount();++j){
           if(nc[j]<table->horizontalHeaderItem(j)->text().length()){
               nc[j]=table->horizontalHeaderItem(j)->text().length();
           }
        }

        for(size_t j=0;j<table->columnCount();++j){
            int cnc=table->horizontalHeaderItem(j)->text().length();
            fo<<table->horizontalHeaderItem(j)->text().toStdString()<<" ";
            for(int k=cnc;k<nc[j];++k){
                fo<<" ";
            }
        }
        fo<<endl;

        for(size_t i=0;i<n;++i){
            for(size_t j=0;j<table->columnCount();++j){
                int cnc=table->item(i,j)->text().length();
                fo<<table->item(i,j)->text().toStdString()<<" ";
                for(int k=cnc;k<nc[j];++k){
                    fo<<" ";
                }
            }
            fo<<endl;

        }
        cout<<"nc=\n"<<nc<<endl;
    }
}

void MainWindow::table_remove_all_rows(){
    table->clear();
    while(table->rowCount()>0){
      table->removeRow(0);
    }
    while(table->columnCount()>0){
      table->removeColumn(0);
    }
    customPlotLc_residuals->clearPlottables();
    for(int i=customPlotLc_residuals->graphCount()-1;i>=0;--i){
        customPlotLc_residuals->removeGraph(i);
    }
    _ind_graph_lc_residuals=-1;
    _residuals_ok=false;
    customPlotLc_residuals->replot();
    _residuals.clear();
    update_freq_number();
}
void MainWindow::table_remove_last_row(){
    int ind=table->rowCount();
    if(ind>0){
       table->removeRow(ind-1);
       if(table->rowCount()==0){
           customPlotLc_residuals->clearPlottables();
           for(int i=customPlotLc_residuals->graphCount()-1;i>=0;--i){
               customPlotLc_residuals->removeGraph(i);
           }
           _ind_graph_lc_residuals=-1;
           _residuals_ok=false;
           customPlotLc_residuals->replot();
           _residuals.clear();

       }
    }
    update_freq_number();
}

/*
void f_sort_int(vector<int> &v){
    for(size_t i=0;i<v.size();++i){
        for(size_t j=i+1;j<v.size();++j){
           if()
        }
    }

}*/


void MainWindow::table_remove_this_row(){
    int ind=table->rowCount();
    if(ind>0){
         int row_erased=-1;
         int opt=0;
         for(int i=0;i<ind;++i){
           if(table->item(i,0)->isSelected()){
              row_erased=i;
              vector<int> rows=frequency_manager.children(i);              
              if(frequency_manager.is_independent(i)){
                  opt=1;
              }
              rows.insert(rows.begin(),i);
              for(int j=rows.size()-1;j>=0;--j){
                table->removeRow(rows[j]);
              }
              if(table->rowCount()==0){
                  customPlotLc_residuals->clearPlottables();
                  for(int i=customPlotLc_residuals->graphCount()-1;i>=0;--i){
                      customPlotLc_residuals->removeGraph(i);
                  }
                  _ind_graph_lc_residuals=-1;
                  _residuals_ok=false;
                  customPlotLc_residuals->replot();
                  _residuals.clear();
              }
              break;
           }
        }
        table_changed(row_erased,opt);
        update_freq_number();
        update_matrix();
    }
}


void MainWindow::table_selectionChanged(){
    if(_cell_selection_triggered_by_horizontalheader){

    }else{
    //cout<<"selection changed"<<endl;
    _cell_changed_triggered_by_selection_change=true;
    for(auto i=0;i<table->rowCount();++i){
        for(auto j=0;j<table->columnCount();++j){
            table->item(i,j)->setBackground(QColor("white"));
        }
    }
    for(QTableWidgetItem* item: table->selectedItems()){
       //cout<<"row selected = "<<item->row()<<endl;
       for(auto i=0;i<table->columnCount();++i){
           if(table->item(item->row(),i)!=nullptr){
               table->item(item->row(),i)->setSelected(true);
           }
       }
       vector<int> rows=frequency_manager.children(item->row());
       for(auto i=0;i<table->columnCount();++i){
               for(size_t j=0;j<rows.size();++j){
                   //table->item(rows[j],i)->setSelected(true);
                   table->item(rows[j],i)->setBackground(QColor(table_color_selection_background_children));
               }
       }
       vector<int> rows_p=frequency_manager.parents(item->row());
       for(auto i=0;i<table->columnCount();++i){
              for(size_t j=0;j<rows_p.size();++j){
                   //table->item(rows[j],i)->setSelected(true);
                   table->item(rows_p[j],i)->setBackground(QColor(table_color_selection_background_parents));

               }
       }
    }
    _cell_changed_triggered_by_selection_change=false;
   }
}

void MainWindow::table_changed(int ind,int opt){
    cout<<"table_changed"<<endl;
    vector<double>freq_i;
    int ind_freq=-1;
    int ind_status=-1;
    for(auto i=0;i<table->columnCount();++i){
        if(table->horizontalHeaderItem(i)->text()=="status"){
            ind_status=i;
        }
        if(table->horizontalHeaderItem(i)->text()=="freq"){
            ind_freq=i;
        }

    }


    if(ind_status!=-1 && opt!=0){
        for(auto i=ind;i<table->rowCount();++i){
            if(table->item(i,ind_status)!=nullptr){
                if(table->item(i,ind_status)->text()=="" || table->item(i,ind_status)->text()=="i"){

                }else{
                    int indred=frequency_manager.index_of_independent_freq(ind);
                    cout<<"table_changed cobination section"<<endl;
                    string status=(table->item(i,ind_status)->text()).toStdString();
                    smatch match;
                    if(regex_match(status,match,regex("\\d+\\*f\\d+")) || regex_match(status,match,regex("\\d+\\.\\d+\\*f\\d+"))){
                       cout<<"table_changed harmonic found"<<endl;
                       double mul=f_get_db(status);
                       int ind_c_freq=round(f_get_db(status,"f"));
                       if(ind_c_freq>=indred){
                          int new_freq_ind=ind_c_freq-1;
                          ostringstream o;
                          o<<mul;
                          string newstatus=o.str()+"*f"+to_string(new_freq_ind);
                          cout<<"table_changed: new_freq="<<newstatus<<endl;
                          table->item(i,ind_status)->setText(newstatus.c_str());
                       }
                    }

                    if(regex_match(status,match,regex("\\d+\\*f\\d+\\+\\d+\\*f\\d+")) || regex_match(status,match,regex("\\d+\\*f\\d+\\-\\d+\\*f\\d+")) ||
                       regex_match(status,match,regex("-\\d+\\*f\\d+\\+\\d+\\*f\\d+")) || regex_match(status,match,regex("-\\d+\\*f\\d+\\-\\d+\\*f\\d+"))    ){
                       int mul=round(f_get_db(status));
                       int ind_c_freq=round(f_get_db(status,"f"));
                       int freq_number_length=(to_string(ind_c_freq)).length();
                       string status_r=status.substr(status.find("f")+1+freq_number_length,status.length()-status.find("f")-1-freq_number_length);
                       int mul2=round(f_get_db(status_r));
                       int ind_c_freq2=round(f_get_db(status_r,"f"));
                       if(ind_c_freq>=indred || ind_c_freq2>=indred){
                           int new_freq_ind=ind_c_freq;
                           int new_freq_ind2=ind_c_freq2;
                           if(ind_c_freq>=indred){
                               new_freq_ind=ind_c_freq-1;
                           }
                           if(ind_c_freq2>=indred){
                               new_freq_ind2=ind_c_freq2-1;
                           }
                           string sign="";
                           if(mul2>0){
                               sign="+";
                           }
                           string newstatus=to_string(mul)+"*f"+to_string(new_freq_ind);
                           newstatus+=sign+to_string(mul2)+"*f"+to_string(new_freq_ind2);
                           cout<<"newstatus ="<<newstatus<<endl;
                           table->item(i,ind_status)->setText(newstatus.c_str());
                       }
                    }
                    if(regex_match(status,match,regex("\\d+\\*f\\d+\\+\\d+\\*f\\d+\\+\\d+\\*f\\d+")) || regex_match(status,match,regex("\\d+\\*f\\d+\\-\\d+\\*f\\d+\\+\\d+\\*f\\d+")) ||
                       regex_match(status,match,regex("-\\d+\\*f\\d+\\+\\d+\\*f\\d+\\+\\d+\\*f\\d+")) || regex_match(status,match,regex("-\\d+\\*f\\d+\\-\\d+\\*f\\d+\\+\\d+\\*f\\d+")) ||
                       regex_match(status,match,regex("\\d+\\*f\\d+\\+\\d+\\*f\\d+\\-\\d+\\*f\\d+")) || regex_match(status,match,regex("\\d+\\*f\\d+\\-\\d+\\*f\\d+\\-\\d+\\*f\\d+")) ||
                       regex_match(status,match,regex("-\\d+\\*f\\d+\\+\\d+\\*f\\d+\\-\\d+\\*f\\d+")) || regex_match(status,match,regex("-\\d+\\*f\\d+\\-\\d+\\*f\\d+\\-\\d+\\*f\\d+")) ){
                       int mul=round(f_get_db(status));
                       int ind_c_freq=round(f_get_db(status,"f"));
                       int freq_number_length=(to_string(ind_c_freq)).length();
                       string status_r=status.substr(status.find("f")+1+freq_number_length,status.length()-status.find("f")-1-freq_number_length);
                       int mul2=round(f_get_db(status_r));
                       int ind_c_freq2=round(f_get_db(status_r,"f"));
                       int freq_number_length2=(to_string(ind_c_freq2)).length();
                       string status_r2=status_r.substr(status_r.find("f")+1+freq_number_length2,status_r.length()-status_r.find("f")-1-freq_number_length2);
                       int mul3=round(f_get_db(status_r2));
                       int ind_c_freq3=round(f_get_db(status_r2,"f"));
                       if(ind_c_freq>=indred || ind_c_freq2>=indred || ind_c_freq3>=indred){
                           int new_freq_ind=ind_c_freq;
                           int new_freq_ind2=ind_c_freq2;
                           int new_freq_ind3=ind_c_freq3;
                           if(ind_c_freq>=indred){
                               new_freq_ind=ind_c_freq-1;
                           }
                           if(ind_c_freq2>=indred){
                               new_freq_ind2=ind_c_freq2-1;
                           }
                           if(ind_c_freq3>=indred){
                               new_freq_ind3=ind_c_freq3-1;
                           }
                           string sign="";
                           if(mul2>0){
                               sign="+";
                           }
                           string sign2="";
                           if(mul3>0){
                               sign2="+";
                           }
                           string newstatus=to_string(mul)+"*f"+to_string(new_freq_ind);
                           newstatus+=sign+to_string(mul2)+"*f"+to_string(new_freq_ind2);
                           newstatus+=sign2+to_string(mul3)+"*f"+to_string(new_freq_ind3);
                           cout<<"table_changed="<<newstatus<<endl;
                           table->item(i,ind_status)->setText(newstatus.c_str());
                       }
                    }

                }
            }

        }

        int nfreq_i=0;
        int nfreq_c=0;
        for(auto i=0;i<table->rowCount();++i){
            if(table->item(i,ind_status)->text()=="" || table->item(i,ind_status)->text()=="i"){
                ++nfreq_i;
                QTableWidgetItem *itemh = new QTableWidgetItem(to_string((nfreq_i)).c_str());
                itemh->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                itemh->font().Bold;
                table->setVerticalHeaderItem(i,itemh);
            }else{
                ++nfreq_c;
                QTableWidgetItem *itemh = new QTableWidgetItem(to_string(-1*(nfreq_c)).c_str());
                itemh->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                itemh->font().Bold;
                table->setVerticalHeaderItem(i,itemh);
            }
        }

        update_matrix();

    }
}

void MainWindow::table_cellChanged(int irow,int icol){
    //cout<<"sell changed"<<endl;
    if(_cell_changed_triggered_by_selection_change){
        //_cell_changed_triggered_by_selection_change=false;
        //cout<<"... ignored"<<endl;
    }else{
    vector<double>freq_i;
    int ind_freq=-1;
    int ind_status=-1;
    for(auto i=0;i<table->columnCount();++i){
        if(table->horizontalHeaderItem(i)->text()=="status"){
            ind_status=i;
        }
        if(table->horizontalHeaderItem(i)->text()=="freq"){
            ind_freq=i;
        }

    }
    if(ind_status==icol){
        cout<<"status changed"<<endl;
        int nfreq_i=0;
        int nfreq_c=0;
        for(auto i=0;i<table->rowCount();++i){
            if(table->item(i,ind_status)->text()=="" || table->item(i,ind_status)->text()=="i"){
                ++nfreq_i;
                QTableWidgetItem *itemh = new QTableWidgetItem(to_string((nfreq_i)).c_str());
                itemh->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                itemh->font().Bold;
                table->setVerticalHeaderItem(i,itemh);
            }else{
                ++nfreq_c;
                QTableWidgetItem *itemh = new QTableWidgetItem(to_string(-1*(nfreq_c)).c_str());
                itemh->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                itemh->font().Bold;
                table->setVerticalHeaderItem(i,itemh);
            }
        }
        table->resizeColumnsToContents();
        update_matrix();
     }
    }
}


void MainWindow::table_currentItemChange(int irow, int icol, int irowprev ,int icolprev){
    //cout<<"table_currentItemChange "<<endl;
    //cout<<irow<<" "<<icol<<" "<<irowprev<<" "<<icolprev<<endl;

    /*
    for(auto i=0;i<table->columnCount();++i){
        //table->itemAt(irow,i)->setBackgroundColor(qRgba64(100,100,100,10));
        if(table->item(irow,i)!=nullptr){
            QBrush brush;
            brush.setColor(qRgba64(0,100,100,10));
            table->item(irow,i)->setBackground(brush);
            cout<<"  -- icol="<<i<<endl;
        }
    }//*/
    //Vtable.push_back(new QTableWidget());



}



void MainWindow:: check_for_combination(){
     //cout<<"check_for_combination"<<endl;

    if(table->rowCount()>0){
        _resolution_for_combination=spinBox_resolution_for_combination->value();

       vector<double>freq_i;
       vector<double>A_i;
       double A_i_max=0;
       int ind_freq=-1;
       int ind_status=-1;
       int ind_A=-1;
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

       }
       int ind_freq_closest=-1;
       double diff_closest=0;
       if(ind_status!=-1 && ind_freq!=-1){
           for(int i=0;i<table->rowCount()-1;++i){
               if(table->item(i,ind_status)!=nullptr){
                   if(table->item(i,ind_status)->text()=="" || table->item(i,ind_status)->text()=="i"){
                       //cout<<"check_for_combination: independent frequency "<<endl;
                       freq_i.push_back(table->item(i,ind_freq)->text().toDouble());                      
                   }
               }
           }
       }
       if(ind_A!=-1){
           for(int i=0;i<table->rowCount()-1;++i){
               if(table->item(i,ind_status)!=nullptr){
                   if(table->item(i,ind_status)->text()=="" || table->item(i,ind_status)->text()=="i"){
                       //cout<<"check_for_combination: independent frequency "<<endl;
                       A_i.push_back(table->item(i,ind_A)->text().toDouble());
                       if(A_i.back()>A_i_max)A_i_max=A_i.back();
                   }
               }
           }
       }
       //cout<<"freq_i="<<freq_i<<endl;
       double freq_test=table->item(table->rowCount()-1,ind_freq)->text().toDouble();
       QTableWidgetItem *itemh = new QTableWidgetItem(to_string(freq_test).c_str());
       itemh->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
       info_table->setHorizontalHeaderItem(0,itemh);
       if(_info_table_column_sort==0){
          if(_info_table_column_sort_ascending){
             info_table->horizontalHeaderItem(0)->setIcon(QIcon(":/img/img/up-arrow_608336.png"));
          }else{
             info_table->horizontalHeaderItem(0)->setIcon(QIcon(":/img/img/download-arrow_109609.png"));
          }
       }
       //cout<<"freq_test="<<freq_test<<endl;
       while(info_table->rowCount()>0){
         info_table->removeRow(0);
       }

       for(size_t i=0;i<freq_i.size();++i){
           if(i>0){
              if(abs(freq_i[i]-freq_test)<diff_closest){
                  diff_closest=abs(freq_i[i]-freq_test);
                  ind_freq_closest=i;
              }
           }else{
              diff_closest=abs(freq_i[i]-freq_test);
              ind_freq_closest=i;
           }
       }

       info_table->insertRow(info_table->rowCount());
       info_table->setRowHeight(info_table->rowCount()-1,10);
       QTableWidgetItem *item = new QTableWidgetItem("i");
       item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
       info_table->setItem(0,0,item);
       info_table->item(0,0)->setFlags(item->flags() ^ Qt::ItemIsEditable);
       //QTableWidgetItem *item2 = new QTableWidgetItem((("1*f"+to_strin"g(freq_i.size()+1)).c_str()));
       QTableWidgetItem *item2 = new QTableWidgetItem("");
       item2->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
       info_table->setItem(0,1,item2);
       info_table->item(0,1)->setFlags(item2->flags() ^ Qt::ItemIsEditable);
       QTableWidgetItem *item3 = new QTableWidgetItem("0.1");
       item3->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
       info_table->setItem(0,2,item3);
       info_table->item(0,2)->setFlags(item3->flags() ^ Qt::ItemIsEditable);
       QTableWidgetItem *item4 = new QTableWidgetItem("0");
       item4->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
       info_table->setItem(0,3,item4);
       info_table->item(0,3)->setFlags(item4->flags() ^ Qt::ItemIsEditable);

       double IP=0;

       QTableWidgetItem *item5 = new QTableWidgetItem(to_string(IP).c_str());
       item5->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
       info_table->setItem(info_table->rowCount()-1,4,item5);
       info_table->item(info_table->rowCount()-1,4)->setFlags(item5->flags() ^ Qt::ItemIsEditable);

       if(freq_i.size()>0){
       QTableWidgetItem *item6 = new QTableWidgetItem((to_string(ind_freq_closest+1)).c_str());
       item6->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
       info_table->setItem(info_table->rowCount()-1,5,item6);
       info_table->item(info_table->rowCount()-1,5)->setFlags(item6->flags() ^ Qt::ItemIsEditable);

       QTableWidgetItem *item7 = new QTableWidgetItem((to_string(diff_closest)).c_str());
       item7->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
       info_table->setItem(info_table->rowCount()-1,6,item7);
       info_table->item(info_table->rowCount()-1,6)->setFlags(item7->flags() ^ Qt::ItemIsEditable);
       }else{

           QTableWidgetItem *item6 = new QTableWidgetItem("");
           item6->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
           info_table->setItem(info_table->rowCount()-1,5,item6);
           info_table->item(info_table->rowCount()-1,5)->setFlags(item6->flags() ^ Qt::ItemIsEditable);

           QTableWidgetItem *item7 = new QTableWidgetItem("");
           item7->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
           info_table->setItem(info_table->rowCount()-1,6,item7);
           info_table->item(info_table->rowCount()-1,6)->setFlags(item7->flags() ^ Qt::ItemIsEditable);

       }

       //subharmonics

       int jmax=4;
       jmax=_General_n_s;
       for(size_t i=0;i<freq_i.size();++i){
           for(int j=2;j<jmax;++j){
              //cout<<freq_i[i]/(j*1.0)-freq_test<<" i="<<i<<" j="<<j<<" freq i = "<<freq_i[i]<<" "<<freq_test<<endl;
               double diff=freq_i[i]/(1.0*j)-freq_test;
              if(abs(diff)<_resolution_for_combination){
                  //cout<<"subharmonic found"<<endl;
                  info_table->insertRow(info_table->rowCount());
                  info_table->setRowHeight(info_table->rowCount()-1,10);
                  QTableWidgetItem *item = new QTableWidgetItem("s");
                  item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                  info_table->setItem(info_table->rowCount()-1,0,item);
                  info_table->item(info_table->rowCount()-1,0)->setFlags(item3->flags() ^ Qt::ItemIsEditable);
                  QTableWidgetItem *item2 = new QTableWidgetItem((to_string(1.0/j)+"*f"+to_string(i+1)).c_str());
                  item2->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                  info_table->setItem(info_table->rowCount()-1,1,item2);
                  info_table->item(info_table->rowCount()-1,1)->setFlags(item2->flags() ^ Qt::ItemIsEditable);

                  double nd2=fabs(j);
                  double AP=nd2/exp(-100*abs(diff))/10.0;

                  double IP=0;
                  if(ind_A!=-1){
                      IP=A_i[i]/A_i_max;
                  }

                  QTableWidgetItem *item3 = new QTableWidgetItem(to_string(AP).c_str());
                  item3->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                  info_table->setItem(info_table->rowCount()-1,2,item3);
                  info_table->item(info_table->rowCount()-1,2)->setFlags(item3->flags() ^ Qt::ItemIsEditable);

                  QTableWidgetItem *item4 = new QTableWidgetItem(to_string(diff).c_str());
                  item4->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                  info_table->setItem(info_table->rowCount()-1,3,item4);
                  info_table->item(info_table->rowCount()-1,3)->setFlags(item4->flags() ^ Qt::ItemIsEditable);

                  QTableWidgetItem *item5 = new QTableWidgetItem(to_string(IP).c_str());
                  item5->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                  info_table->setItem(info_table->rowCount()-1,4,item5);
                  info_table->item(info_table->rowCount()-1,4)->setFlags(item5->flags() ^ Qt::ItemIsEditable);

                  QTableWidgetItem *item6 = new QTableWidgetItem("");
                  item6->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                  info_table->setItem(info_table->rowCount()-1,5,item6);
                  info_table->item(info_table->rowCount()-1,5)->setFlags(item6->flags() ^ Qt::ItemIsEditable);

                  QTableWidgetItem *item7 = new QTableWidgetItem("");
                  item7->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                  info_table->setItem(info_table->rowCount()-1,6,item7);
                  info_table->item(info_table->rowCount()-1,6)->setFlags(item7->flags() ^ Qt::ItemIsEditable);


              }
           }
       }

       //harmonic
       jmax=10;
       jmax=_General_n_h;
       for(size_t i=0;i<freq_i.size();++i){
           for(size_t j=2;j<jmax;++j){
              //cout<<j*freq_i[i]-freq_test<<" i="<<i<<" j="<<j<<" freq i = "<<freq_i[i]<<" "<<freq_test<<endl;
               double diff=j*freq_i[i]-freq_test;
              if(abs(diff)<_resolution_for_combination){
                  //cout<<"harmonic found"<<endl;
                  info_table->insertRow(info_table->rowCount());
                  info_table->setRowHeight(info_table->rowCount()-1,10);
                  QTableWidgetItem *item = new QTableWidgetItem("h");
                  item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                  info_table->setItem(info_table->rowCount()-1,0,item);
                  info_table->item(info_table->rowCount()-1,0)->setFlags(item->flags() ^ Qt::ItemIsEditable);
                  QTableWidgetItem *item2 = new QTableWidgetItem((to_string(j)+"*f"+to_string(i+1)).c_str());
                  item2->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                  info_table->setItem(info_table->rowCount()-1,1,item2);
                  info_table->item(info_table->rowCount()-1,1)->setFlags(item2->flags() ^ Qt::ItemIsEditable);

                  double nd2=fabs(j);
                  double AP=nd2/exp(-100*abs(diff))/10.0;

                  double IP=0;
                  if(ind_A!=-1){
                      IP=A_i[i]/A_i_max;
                  }

                  QTableWidgetItem *item3 = new QTableWidgetItem(to_string(AP).c_str());
                  item3->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                  info_table->setItem(info_table->rowCount()-1,2,item3);
                  info_table->item(info_table->rowCount()-1,2)->setFlags(item3->flags() ^ Qt::ItemIsEditable);

                  QTableWidgetItem *item4 = new QTableWidgetItem(to_string(diff).c_str());
                  item4->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                  info_table->setItem(info_table->rowCount()-1,3,item4);
                  info_table->item(info_table->rowCount()-1,3)->setFlags(item4->flags() ^ Qt::ItemIsEditable);

                  QTableWidgetItem *item5 = new QTableWidgetItem(to_string(IP).c_str());
                  item5->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                  info_table->setItem(info_table->rowCount()-1,4,item5);
                  info_table->item(info_table->rowCount()-1,4)->setFlags(item5->flags() ^ Qt::ItemIsEditable);

                  QTableWidgetItem *item6 = new QTableWidgetItem("");
                  item6->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                  info_table->setItem(info_table->rowCount()-1,5,item6);
                  info_table->item(info_table->rowCount()-1,5)->setFlags(item6->flags() ^ Qt::ItemIsEditable);

                  QTableWidgetItem *item7 = new QTableWidgetItem("");
                  item7->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                  info_table->setItem(info_table->rowCount()-1,6,item7);
                  info_table->item(info_table->rowCount()-1,6)->setFlags(item7->flags() ^ Qt::ItemIsEditable);

              }
           }
       }

       //combination
       int n1max=10;
       n1max=_General_n_c2_1;
       int n2max=10;
       n2max=_General_n_c2_2;
       for(size_t i=0;i<freq_i.size();++i){
           for(size_t j=i+1;j<freq_i.size();++j){
              for(int in1=-n1max;in1<n1max;++in1){
                  for(int in2=-n2max;in2<n2max;++in2){
                      if(in1!=0 && in2!=0){
                         //cout<<in1*freq_i[i]+in2*freq_i[j]-freq_test<<" i="<<i<<" j="<<j<<" freq i = "<<freq_i[i]<<" freq j = "<<freq_i[j]<<" "<<freq_test<<endl;
                         double diff=in1*freq_i[i]+in2*freq_i[j]-freq_test;
                         if(abs(diff)<_resolution_for_combination){
                             //cout<<"combination 2e found"<<endl;
                             info_table->insertRow(info_table->rowCount());
                             info_table->setRowHeight(info_table->rowCount()-1,10);
                             QTableWidgetItem *item = new QTableWidgetItem("c2");
                             item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                             info_table->setItem(info_table->rowCount()-1,0,item);
                             info_table->item(info_table->rowCount()-1,0)->setFlags(item->flags() ^ Qt::ItemIsEditable);
                             string sign="";
                             if(in2>0){
                                 sign="+";
                             }
                             QTableWidgetItem *item2 = new QTableWidgetItem((to_string(in1)+"*f"+to_string(i+1)+sign+to_string(in2)+"*f"+to_string(j+1)).c_str());
                             item2->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                             info_table->setItem(info_table->rowCount()-1,1,item2);
                             info_table->item(info_table->rowCount()-1,1)->setFlags(item2->flags() ^ Qt::ItemIsEditable);

                             double nd2=abs(in1)+abs(in2)*2;
                             double nd22=in1*2+in2*1;
                             //cout<<"nd2="<<nd2<<" "<<nd22<<" diff="<<diff<<" "<<-100*abs(diff)<<" "<<exp(-100*abs(diff))<<endl;
                             double AP=nd2/exp(-100*abs(diff))/10.0;
                             double AP2=nd22/exp(-100*abs(diff))/10.0;
                             //cout<<"AP="<<AP<<" "<<AP2<<endl;

                             double IP=0;
                             if(ind_A!=-1){
                                 IP=sqrt(pow(A_i[i],2)+pow(A_i[j],2))/A_i_max;
                             }

                             QTableWidgetItem *item3 = new QTableWidgetItem(to_string(AP).c_str());
                             item3->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                             info_table->setItem(info_table->rowCount()-1,2,item3);
                             info_table->item(info_table->rowCount()-1,2)->setFlags(item3->flags() ^ Qt::ItemIsEditable);

                             QTableWidgetItem *item4 = new QTableWidgetItem(to_string(diff).c_str());
                             item4->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                             info_table->setItem(info_table->rowCount()-1,3,item4);
                             info_table->item(info_table->rowCount()-1,3)->setFlags(item4->flags() ^ Qt::ItemIsEditable);

                             QTableWidgetItem *item5 = new QTableWidgetItem(to_string(IP).c_str());
                             item5->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                             info_table->setItem(info_table->rowCount()-1,4,item5);
                             info_table->item(info_table->rowCount()-1,4)->setFlags(item5->flags() ^ Qt::ItemIsEditable);

                             QTableWidgetItem *item6 = new QTableWidgetItem("");
                             item6->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                             info_table->setItem(info_table->rowCount()-1,5,item6);
                             info_table->item(info_table->rowCount()-1,5)->setFlags(item6->flags() ^ Qt::ItemIsEditable);

                             QTableWidgetItem *item7 = new QTableWidgetItem("");
                             item7->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                             info_table->setItem(info_table->rowCount()-1,6,item7);
                             info_table->item(info_table->rowCount()-1,6)->setFlags(item7->flags() ^ Qt::ItemIsEditable);

                         }
                     }
                  }
              }
           }
       }

       //combination
       n1max=5;
       n1max=_General_n_c3_1;
       n2max=5;
       n2max=_General_n_c3_2;
       int n3max=5;
       n3max=_General_n_c3_3;
       for(size_t i=0;i<freq_i.size();++i){
           for(size_t j=i+1;j<freq_i.size();++j){
               for(size_t k=j+1;k<freq_i.size();++k){
                  for(int in1=-n1max;in1<n1max;++in1){
                      for(int in2=-n2max;in2<n2max;++in2){
                          for(int in3=-n3max;in3<n3max;++in3){
                             if(in1!=0 && in2!=0 && in3!=0){
                                 //cout<<in1*freq_i[i]+in2*freq_i[j]-freq_test<<" i="<<i<<" j="<<j<<" freq i = "<<freq_i[i]<<" freq j = "<<freq_i[j]<<" "<<freq_test<<endl;
                                 double diff=in1*freq_i[i]+in2*freq_i[j]+in3*freq_i[k]-freq_test;
                                 if(abs(diff)<_resolution_for_combination){
                                     //cout<<"combination 3e found"<<endl;
                                     info_table->insertRow(info_table->rowCount());
                                     info_table->setRowHeight(info_table->rowCount()-1,10);
                                     QTableWidgetItem *item = new QTableWidgetItem("c3");
                                     item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                                     info_table->setItem(info_table->rowCount()-1,0,item);
                                     info_table->item(info_table->rowCount()-1,0)->setFlags(item->flags() ^ Qt::ItemIsEditable);
                                     string sign="";
                                     if(in2>0){
                                         sign="+";
                                     }
                                     string sign2="";
                                     if(in3>0){
                                         sign2="+";
                                     }
                                     QTableWidgetItem *item2 = new QTableWidgetItem((to_string(in1)+"*f"+to_string(i+1)+sign+to_string(in2)+"*f"+to_string(j+1)+sign2+to_string(in3)+"*f"+to_string(k+1)).c_str());
                                     item2->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                                     info_table->setItem(info_table->rowCount()-1,1,item2);
                                     info_table->item(info_table->rowCount()-1,1)->setFlags(item2->flags() ^ Qt::ItemIsEditable);

                                     double nd2=abs(in1)+abs(in2)*2;
                                     double nd22=in1*2+in2*1;
                                     //cout<<"nd2="<<nd2<<" "<<nd22<<" diff="<<diff<<" "<<-100*abs(diff)<<" "<<exp(-100*abs(diff))<<endl;
                                     double AP=nd2/exp(-100*abs(diff))/10.0;
                                     double AP2=nd22/exp(-100*abs(diff))/10.0;
                                     //cout<<"AP="<<AP<<" "<<AP2<<endl;

                                     double IP=0;
                                     if(ind_A!=-1){
                                         IP=sqrt(pow(A_i[i],2)+pow(A_i[j],2)+pow(A_i[k],2))/A_i_max;
                                     }

                                     QTableWidgetItem *item3 = new QTableWidgetItem(to_string(AP).c_str());
                                     item3->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                                     info_table->setItem(info_table->rowCount()-1,2,item3);
                                     info_table->item(info_table->rowCount()-1,2)->setFlags(item3->flags() ^ Qt::ItemIsEditable);

                                     QTableWidgetItem *item4 = new QTableWidgetItem(to_string(diff).c_str());
                                     item4->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                                     info_table->setItem(info_table->rowCount()-1,3,item4);
                                     info_table->item(info_table->rowCount()-1,3)->setFlags(item4->flags() ^ Qt::ItemIsEditable);


                                     QTableWidgetItem *item5 = new QTableWidgetItem(to_string(IP).c_str());
                                     item5->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                                     info_table->setItem(info_table->rowCount()-1,4,item5);
                                     info_table->item(info_table->rowCount()-1,4)->setFlags(item5->flags() ^ Qt::ItemIsEditable);

                                     QTableWidgetItem *item6 = new QTableWidgetItem("");
                                     item6->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                                     info_table->setItem(info_table->rowCount()-1,5,item6);
                                     info_table->item(info_table->rowCount()-1,5)->setFlags(item6->flags() ^ Qt::ItemIsEditable);

                                     QTableWidgetItem *item7 = new QTableWidgetItem("");
                                     item7->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                                     info_table->setItem(info_table->rowCount()-1,6,item7);
                                     info_table->item(info_table->rowCount()-1,6)->setFlags(item7->flags() ^ Qt::ItemIsEditable);
                                 }
                             }
                         }
                     }
                  }
              }
           }
       }

       /*
       for(size_t i=0;i<info_table->rowCount();++i){
           //for(size_t j=0;j<info_table->columnCount();++j){
             cout<<info_table->item(i,2)->text().toStdString()<<" ";
           //}
           cout<<endl;
       }*/

       //info_table->sortByColumn(2,Qt::SortOrder::AscendingOrder);
       //info_table->sortItems(2,Qt::SortOrder::AscendingOrder);
/*

       for(size_t i=0;i<info_table->rowCount();++i){
           for(size_t j=i+1;j<info_table->rowCount();++j){
              //cout<<info_table->item(i,2)->text().toStdString()<<" ";
              if(info_table->item(i,2)->text().toDouble()>info_table->item(j,2)->text().toDouble()){
                      QList<QTableWidgetItem*> sourceItems = takeRow(i);
                      QList<QTableWidgetItem*> destItems = takeRow(j);

                      // set back in reverse order
                      setRow(i, destItems);
                      setRow(j, sourceItems);

              }
           }
           //cout<<endl;
       }
*/

       info_table->resizeColumnsToContents();
       sort_info_table();

       /*
       cout<<"sorted:"<<endl;
       for(size_t i=0;i<info_table->rowCount();++i){
           //for(size_t j=0;j<info_table->columnCount();++j){
             cout<<info_table->item(i,2)->text().toStdString()<<" ";
           //}
           cout<<endl;
       }*/


    }
}


void MainWindow::init_info_table(){
    cout<<"init info table"<<endl;
    info_table->clear();
    //table->insertRow(0);
    info_table->insertColumn(0);
    QTableWidgetItem* item = new QTableWidgetItem("status");
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    info_table->setHorizontalHeaderItem(0,item);
    //info_table->insertColumn(1);
    //QTableWidgetItem* item1 = new QTableWidgetItem("test freq");
    //item1->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    //info_table->setHorizontalHeaderItem(1,item1);
    info_table->insertColumn(1);
    QTableWidgetItem* item2 = new QTableWidgetItem("info");
    item2->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    info_table->setHorizontalHeaderItem(1,item2);
    info_table->insertColumn(2);
    QTableWidgetItem* item3 = new QTableWidgetItem("add. info");
    item3->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    info_table->setHorizontalHeaderItem(2,item3);
    info_table->insertColumn(3);
    QTableWidgetItem* item4 = new QTableWidgetItem("diff");
    item4->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    info_table->setHorizontalHeaderItem(3,item4);
    info_table->insertColumn(4);
    QTableWidgetItem* item5 = new QTableWidgetItem("IP");
    item5->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    info_table->setHorizontalHeaderItem(4,item5);
    info_table->insertColumn(5);
    QTableWidgetItem* item6 = new QTableWidgetItem("closest freq");
    item6->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    info_table->setHorizontalHeaderItem(5,item6);
    info_table->insertColumn(6);
    QTableWidgetItem* item7 = new QTableWidgetItem("diff closest freq");
    item7->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    info_table->setHorizontalHeaderItem(6,item7);


    _info_table_column_sort=2;
    _info_table_column_sort_ascending=true;
    info_table->horizontalHeaderItem(_info_table_column_sort)->setIcon(QIcon(":/img/img/up-arrow_608336.png"));

    info_table->setStyleSheet(
                "QTableView::item:selected"
                "{"
                "background-color : "+table_color_selection_background+";"
                "selection-color : #000000;"
                "}"
            );


    cout<<"init done"<<endl;
}

void MainWindow::info_table_selectionChanged(){
    /*
    if(!info_table_sorting){
       cout<<"info_table selection changed"<<endl;
       for(QTableWidgetItem* item: info_table->selectedItems()){
          //cout<<"row selected = "<<item->row()<<endl;
          for(auto i=0;i<info_table->columnCount();++i){
             if(info_table->item(item->row(),i)!=nullptr){
                 info_table->item(item->row(),i)->setSelected(true);
             }
          }
       }
    }*/

}

void MainWindow::info_table_doubleclicked(int irow,int icol){
   //cout<<"info_table_doubleclicked"<<endl;
   QString text=info_table->item(irow,1)->text();
   //update_table_status(info_table->horizontalHeaderItem(0)->text().toDouble(),text);
   update_table_status(text);
}

void MainWindow::update_table_status(double freq, QString text){
   int ind_freq=-1;
   int ind_status=-1;
   for(auto i=0;i<table->columnCount();++i){
       if(table->horizontalHeaderItem(i)->text()=="status"){
           ind_status=i;
       }
       if(table->horizontalHeaderItem(i)->text()=="freq"){
           ind_freq=i;
       }
   }
   if(ind_status!=-1 && ind_freq!=-1){
      for(int i=0;i<table->rowCount();++i){
          //cout<<table->item(i,ind_freq)->text().toDouble()<<" "<<freq<<" "<<table->item(i,ind_freq)->text().toDouble()-freq<<endl;
          if(table->item(i,ind_freq)!=nullptr){
              if(table->item(i,ind_freq)->text().toDouble()==freq){
                  cout<<"frequency found "<<freq<<endl;
                  table->item(i,ind_status)->setText(text);
              }
          }
      }
   }
}

void MainWindow::update_table_status(QString text){
   int ind_freq=-1;
   int ind_status=-1;
   for(auto i=0;i<table->columnCount();++i){
       if(table->horizontalHeaderItem(i)->text()=="status"){
           ind_status=i;
       }
       if(table->horizontalHeaderItem(i)->text()=="freq"){
           ind_freq=i;
       }
   }
   if(ind_status!=-1 && ind_freq!=-1){
          if(table->item(table->rowCount()-1,ind_freq)!=nullptr){
                  cout<<"frequency found "<<endl;
                  table->item(table->rowCount()-1,ind_status)->setText(text);
          }
   }
}


bool MainWindow::info_table_compare_1c(QString s1,QString s2){
    bool r=false;


    if(s1=="c2" && s2=="i"){
        r=true;
    }else if(s1=="c3" && s2=="i"){
        r=true;
    }else if(s1=="h" && s2=="i"){
        r=true;
    }else if(s1=="s" && s2=="i"){
        r=true;
    }else if(s1=="h" && s2=="s"){
        r=true;
    }else if(s1=="c2" && s2=="s"){
        r=true;
    }else if(s1=="c3" && s2=="s"){
        r=true;
    }else if(s1=="c2" && s2=="h"){
        r=true;
    }else if(s1=="c3" && s2=="h"){
        r=true;
    }else if(s1=="c3" && s2=="c2"){
        r=true;
    }


    return(r);
}


void MainWindow::sort_info_table(){

  info_table_sorting=true;
  if(_info_table_column_sort==0){
      //cout<<" sorting column 1 "<<endl;
      for(size_t i=0;i<info_table->rowCount();++i){
         for(size_t j=i+1;j<info_table->rowCount();++j){
            //cout<<info_table->item(i,2)->text().toStdString()<<" ";
            if(_info_table_column_sort_ascending){
                //if(info_table->item(i,_info_table_column_sort)->text()=="c2" && info_table->item(j,_info_table_column_sort)->text()=="i"){
                if( info_table_compare_1c(info_table->item(i,_info_table_column_sort)->text(),info_table->item(j,_info_table_column_sort)->text())){
                   QList<QTableWidgetItem*> sourceItems = takeRow(i);
                   QList<QTableWidgetItem*> destItems = takeRow(j);
                   // set back in reverse order
                   setRow(i, destItems);
                   setRow(j, sourceItems);
                }
            }else{
                //if(info_table->item(i,_info_table_column_sort)->text()=="i" && info_table->item(j,_info_table_column_sort)->text()=="c2"){
                if( info_table_compare_1c(info_table->item(j,_info_table_column_sort)->text(),info_table->item(i,_info_table_column_sort)->text())){

                   QList<QTableWidgetItem*> sourceItems = takeRow(i);
                   QList<QTableWidgetItem*> destItems = takeRow(j);
                   // set back in reverse order
                   setRow(i, destItems);
                   setRow(j, sourceItems);
                }
            }
         }
      }
      //cout<<" sorting column 1 done"<<endl;
  }else if(_info_table_column_sort==1){

  }else{
    //cout<<"sorting according to = "<<_info_table_column_sort<<endl;
    if(_info_table_column_sort<info_table->columnCount()){
       for(size_t i=0;i<info_table->rowCount();++i){
          for(size_t j=i+1;j<info_table->rowCount();++j){
             //cout<<info_table->item(i,_info_table_column_sort)->text().toDouble()<<" "<<endl;
             if(_info_table_column_sort_ascending){
                 if(abs(info_table->item(i,_info_table_column_sort)->text().toDouble())>abs(info_table->item(j,_info_table_column_sort)->text().toDouble())){
                    QList<QTableWidgetItem*> sourceItems = takeRow(i);
                    QList<QTableWidgetItem*> destItems = takeRow(j);
                    // set back in reverse order
                    setRow(i, destItems);
                    setRow(j, sourceItems);
                 }
             }else{
                 if(abs(info_table->item(i,_info_table_column_sort)->text().toDouble())<abs(info_table->item(j,_info_table_column_sort)->text().toDouble())){
                    QList<QTableWidgetItem*> sourceItems = takeRow(i);
                    QList<QTableWidgetItem*> destItems = takeRow(j);
                    // set back in reverse order
                    setRow(i, destItems);
                    setRow(j, sourceItems);
                 }
             }
          }
       }
    }
    //cout<<"done"<<endl;
  }
  info_table_sorting=false;
}

//J-P Nurmi:
// takes and returns the whole row
QList<QTableWidgetItem*> MainWindow::takeRow(int row)
{
    QList<QTableWidgetItem*> rowItems;
    for (int col = 0; col < info_table->columnCount(); ++col)
    {
        rowItems << info_table->takeItem(row, col);
    }
    return rowItems;
}

// sets the whole row
void MainWindow::setRow(int row, const QList<QTableWidgetItem*>& rowItems)
{
    for (int col = 0; col < info_table->columnCount(); ++col)
    {
        info_table->setItem(row, col, rowItems.at(col));
    }
}


void MainWindow::horizontalHeaderClicked(int column){
    cout<<"horizontalHeaderClicked="<<column<<endl;
    if(pushB_fitsin->isEnabled()){
      if(column<info_table->columnCount()){
       //info_table->setSelectionBehavior(QAbstractItemView::SelectColumns);
       //info_table->selectColumn(column);
       // <a href="https://www.flaticon.com/free-icons/up-arrow" title="up arrow icons">Up arrow icons created by Roundicons Premium - Flaticon</a>
       //<a target="_blank" href="https://icons8.com/icon/166/up">Up</a> icon by <a target="_blank" href="https://icons8.com">Icons8</a>

        //info_table->setSelectionMode(QAbstractItemView::NoSelection);

        //cout<<"_info_table_column_sort="<<_info_table_column_sort<<endl;
        //cout<<"_info_table_column_sort_ascending="<<_info_table_column_sort_ascending<<endl;

        if(column==_info_table_column_sort){
            if(_info_table_column_sort_ascending){
                _info_table_column_sort_ascending=false;
            }else{
                _info_table_column_sort_ascending=true;
            }
        }else{
            _info_table_column_sort=column;
            _info_table_column_sort_ascending=true;
        }

        //cout<<"_info_table_column_sort="<<_info_table_column_sort<<endl;
        //cout<<"_info_table_column_sort_ascending="<<_info_table_column_sort_ascending<<endl;


        if(_info_table_column_sort_ascending){
           info_table->horizontalHeaderItem(column)->setIcon(QIcon(":/img/img/up-arrow_608336.png"));
        }else{
           info_table->horizontalHeaderItem(column)->setIcon(QIcon(":/img/img/download-arrow_109609.png"));
        }


        for(int i=0;i<info_table->columnCount();++i){
            if(i!=column){
              QString text=info_table->horizontalHeaderItem(i)->text();
              QTableWidgetItem* item = new QTableWidgetItem(text);
              item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
              info_table->setHorizontalHeaderItem(i,item);
            }
        }

        sort_info_table();
        for(int i=0;i<info_table->rowCount();++i){
             for(int j=0;j<info_table->columnCount();++j){
                info_table->item(i,j)->setSelected(false);
             }
        }

        //info_table->setSelectionBehavior(QAbstractItemView::SelectRows);

     }
    }
}

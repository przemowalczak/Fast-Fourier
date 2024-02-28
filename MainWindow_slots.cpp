#include "mainwindow.h"
#include "ui_mainwindow.h"


void MainWindow::exit(){
   QApplication::quit();
}

void MainWindow::help(){
    QMessageBox *message = new QMessageBox(this);

    string text="This program calculates fourier transform and performs linear and nonlinear sine fitting of the form sum_{i=1}^{n}A_isin(2*pi*f_i*t_j+phi_i).";
    text+="The input file should consist of three columns separated with spaces: julian date, flux, flux uncertainty";
    text+="\ncombinations:";
    text+="\n";
    text+="   <li>diff - frequency_difference = current frequency - frequency derived from combination\n";
    text+="   IP - sqrt(sum_{i=1}^{nc}A(i)^2)/AH, where nc - number of frequencies involved in a combination,";
    text+="   AH is the highest amplitude in the whole spectrum. See also equation 3 from MNRAS 503, 5894–5928 (2021)\n";
    text+="   add.info = nd/(10*exp(-100.d0*abs(frequency_difference))), where nd=sum_{i=0}^{nc}n(i)*i";
    text+="(the lower the value, that higher probability, that this is a combination\n";
    text+="   closest freq - the closest independent frequency number.\n";
    text+="   frequency difference between the current frequency and the closest independent frequency";
    text+="";

    message->setText(text.c_str());

    message->exec();

}

void MainWindow::data_spectral_window_clicked(){
    if(_file_loaded){
    if(_use_data){
        _use_data=false;
        pushB_spec_wind_data->setText("    use data   ");
        _data_file_copy=f_get_column(_file.file(),_file.head(),"2");
        _e_data_file_copy=f_get_column(_file.file(),_file.head(),"3");
        size_t nr=_file.file().size();
        for(size_t i=0;i<nr;++i){
            _file.file()[i][1]=1;
            _file.file()[i][2]=1;
        }
        if(_file.nr()>0){
            _file.file()[0][1]=1;
        }
        if(_init_customPlotLc_ok){
            detrended_ok=false;
            calculate_trend();
            plot_lc();
        }
        //cout<<_file<<endl;
        _copy_residuals_ok=_residuals_ok;
        _residuals_ok=false;

    }else{
        _use_data=true;
        pushB_spec_wind_data->setText("spec. win.");
        if(_data_file_copy.size()!=_file.nr() || _e_data_file_copy.size()!=_file.nr()){
            cout<<"oooo :("<<endl;
        }else{
            size_t nr=_file.file().size();
            for(size_t i=0;i<nr;++i){
               _file.file()[i][1]=_data_file_copy[i];
               _file.file()[i][2]=_e_data_file_copy[i];
            }
        }
        if(_init_customPlotLc_ok){
           detrended_ok=false;
           calculate_trend();
           plot_lc();
        }
        _residuals_ok=_copy_residuals_ok;

    }
    }

}

void MainWindow::main_save_data_clicked(){
    //cout<<"main_save_data_clicked"<<endl;
    trf_save_trf();
    phase_save_phase();
    lc_save_lc();
    resid_save_resid();
    table_save_data();
}

void MainWindow::main_save_pdf_clicked(){
    //cout<<"main_save_data_clicked"<<endl;
    savepdf();
    savepdfLc_phase();
    savepdfLc();
    savepdfLc_residuals();
}

void MainWindow::full_auto_clicked(){
    if(!_full_auto){
        pushB_full_auto->setText("stop auto");
        _full_auto=true;
        _iter_auto=0;
        auto_clicked();
    }else{
        _full_auto=false;
        pushB_full_auto->setText("full auto");
    }
}

void MainWindow::auto_clicked(){

   get_trf_FastFourier_WS();

   if(!_noise_ok){
       pushB_calculate_noise();
   }
   if(!_show_peaks){
       show_peaks();
   }
   bool go=true;
   if(!_file_loaded){
       go=false;
   }
   size_t iter=1;
   size_t itermax=1;

   //while(go){

       //get_trf_FastFourier_WS();

       add_max_peak();

       if(_use_first_combination){
           if(info_table->rowCount()>=2){
               QString text=info_table->item(1,1)->text();
               //cout<<"change status"<<endl;
               update_table_status(text);
           }
       }

       pushB_fitsin_function();

       //cout<<"freq "<<_amplpeaks[0]<<endl;
       /*if(_SNpeaks.size()>0){
          if(_SNpeaks[0]<_crit_stop){
              go=false;
              _full_auto=false;
              pushB_full_auto->setText("full auto");
          }
          //cout<<"_SNpeaks[0]="<<_SNpeaks[0]<<endl;
       }else{
           //cout<<"_SNpeaks.size()=0"<<endl;
           go=false;
           pushB_full_auto->setText("full auto");
           _full_auto=false;
       }*/
       int ind_freq=-1;
       int ind_SN=-1;
       vector<bool> ind_ind;
       for(auto i=0;i<table->columnCount();++i){
           if(table->horizontalHeaderItem(i)->text()=="freq"){
               ind_freq=i;
           }
           if(table->horizontalHeaderItem(i)->text()=="S/N"){
               ind_SN=i;
           }
       }
       if(_noise_ok && ind_SN!=-1){
          if(table->item(table->rowCount()-1,ind_SN)->text().toDouble()<_crit_stop){
              go=false;
              _full_auto=false;
              pushB_full_auto->setText("full auto");
          }
          //cout<<"_SNpeaks[0]="<<_SNpeaks[0]<<endl;
       }else{
           //cout<<"_SNpeaks.size()=0"<<endl;
           go=false;
           pushB_full_auto->setText("full auto");
           _full_auto=false;
       }



       ++iter;
       ++_iter_auto;
   //}


}

void MainWindow::open_file(){
    setlocale(LC_ALL, "en_US.utf8");
    cout<<"opening file"<<endl;
    if(_file_loaded){
        reset();
    }
    _file_loaded=false;

    dialog_open_file.setFileMode(QFileDialog::AnyFile);
    dialog_open_file.setNameFilter(tr("Text files (*.txt *.dat *.data *.out *.in);;All files *"));
    dialog_open_file.setViewMode(QFileDialog::Detail);

    dialog_open_file.show();
    dialog_open_file.raise();
    dialog_open_file.activateWindow();

    QStringList fileNames;
    if (dialog_open_file.exec())
        fileNames = dialog_open_file.selectedFiles();

    int n=fileNames.count();
    //cout<<n<<endl;
    string fname="";
    for(int i=0;i<n;++i){
       cout<<"file = "<<fileNames[i].toStdString()<<endl;
       if(i==0)fname=fileNames[i].toStdString();
    }


    if(fname!=""){
        int nhead=1;
        int ihead=0;

        nhead=0;
        ihead=-1;

        string snhead= "-1";

        if(isNumber(snhead)){
           nhead=stof(snhead);
        }else{
           nhead=1;
        }

        string sihead="0";
        if(isNumber(sihead)){
           ihead=stof(sihead);
        }else{
           ihead=1;
        }

        //cl_read_file file{fname,nhead,ihead," ",true,false,true};
        _file.init(fname,nhead,ihead," ",true,false,true);
        if(_file.ok()){
            if(_file.file().size()>0){
                //cout<<_file.head()<<endl;
                _file_loaded=true;
                if(_init_customPlotLc_ok){
                    plot_lc();
                    calculate_trend();
                }
            }
        }
    }
}

void MainWindow::combo_settings_action_NLSF_clicked(){
    if(!_combo_settings_action_NLSF_dialog_init){
        dialog_NLSF = new QDialog(this);
        dialog_NLSF->setWindowTitle("NLSF");
        dialog_NLSF_layout = new QGridLayout(dialog_NLSF);
        _combo_settings_action_NLSF_dialog_init=true;

        QGroupBox *groupBox3 = new QGroupBox(tr("Maximal number of iteration"));
        QVBoxLayout *vbox3 = new QVBoxLayout;
        spinB_NLSF_maxiter = new QSpinBox();
        spinB_NLSF_maxiter->setLocale(QLocale::C);
        spinB_NLSF_maxiter->setSingleStep(100);
        spinB_NLSF_maxiter->setMinimum(1);
        spinB_NLSF_maxiter->setMaximum(1e8);
        spinB_NLSF_maxiter->setValue(_NLSF_max_iteration);
        connect(spinB_NLSF_maxiter,SIGNAL(valueChanged(int)),this,SLOT(spinB_NLSF_maxiter_changed(int)));
        vbox3->addWidget(spinB_NLSF_maxiter);
        groupBox3->setLayout(vbox3);
        dialog_NLSF_layout->addWidget(groupBox3);


        QGroupBox *groupBox2 = new QGroupBox(tr("Select the method used to solve the trust region subproblem"));
        radio_NLSF_trs_1 = new QRadioButton(tr("&Levenberg-Marquardt algorithm"));
        radio_NLSF_trs_2 = new QRadioButton(tr("L&evenberg-Marquardt algorithm with geodesic acceleration"));
        radio_NLSF_trs_3 = new QRadioButton(tr("Do&gleg algorithm"));
        radio_NLSF_trs_4 = new QRadioButton(tr("Dou&ble dogleg algorithm"));
        radio_NLSF_trs_5 = new QRadioButton(tr("2D su&bspace algorithm"));
        radio_NLSF_trs_1->setChecked(true);
        QVBoxLayout *vbox2 = new QVBoxLayout;
        vbox2->addWidget(radio_NLSF_trs_1);
        vbox2->addWidget(radio_NLSF_trs_2);
        vbox2->addWidget(radio_NLSF_trs_3);
        vbox2->addWidget(radio_NLSF_trs_4);
        vbox2->addWidget(radio_NLSF_trs_5);
        groupBox2->setLayout(vbox2);
        dialog_NLSF_layout->addWidget(groupBox2);

        QGroupBox *groupBox = new QGroupBox(tr("Select NLSF solver"));
        radio_NLSF_1 = new QRadioButton(tr("&Modified Cholesky Decomposition"));
        radio_NLSF_2 = new QRadioButton(tr("C&holesky Decomposition"));
        radio_NLSF_3 = new QRadioButton(tr("QR &Decomposition "));
        radio_NLSF_4 = new QRadioButton(tr("Sing&ular Value Decomposition"));
        radio_NLSF_1->setChecked(true);
        QVBoxLayout *vbox = new QVBoxLayout;
        vbox->addWidget(radio_NLSF_1);
        vbox->addWidget(radio_NLSF_2);
        vbox->addWidget(radio_NLSF_3);
        vbox->addWidget(radio_NLSF_4);
        //vbox->addStretch(1);
        groupBox->setLayout(vbox);
        dialog_NLSF_layout->addWidget(groupBox);
    }
    dialog_NLSF->show();
    dialog_NLSF->raise();
    dialog_NLSF->activateWindow();
}

void MainWindow::combo_settings_action_General_clicked(){
    if(!_combo_settings_action_General_dialog_init){
        dialog_General = new QDialog(this);
        dialog_General->setWindowTitle("NLSF");
        dialog_General_layout = new QGridLayout(dialog_General);
        _combo_settings_action_General_dialog_init=true;
        QGroupBox *groupBox = new QGroupBox(tr("fit n last frequencies (not implementet yet)"));

        QVBoxLayout *vbox = new QVBoxLayout;
        spinB_General_nfreq = new QSpinBox();
        spinB_General_nfreq->setLocale(QLocale::C);
        spinB_General_nfreq->setSingleStep(1);
        spinB_General_nfreq->setMinimum(-1);
        spinB_General_nfreq->setMaximum(1e6);
        spinB_General_nfreq->setValue(_General_n_last_freq);
        connect(spinB_General_nfreq,SIGNAL(valueChanged(int)),this,SLOT(spinB_General_nfreq_changed(int)));
        vbox->addWidget(spinB_General_nfreq,0);

        //vbox->addStretch(1);
        groupBox->setLayout(vbox);
        dialog_General_layout->addWidget(groupBox);

        QGroupBox *groupBox2 = new QGroupBox(tr("Hormonics and combinations"));
        QVBoxLayout *vbox2 = new QVBoxLayout;

        QHBoxLayout *hbox_s=new QHBoxLayout();
        QLabel *label_s = new QLabel(tr("subharmonic n<sub>max</sub> = "));
        label_s->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        hbox_s->addWidget(label_s);
        spinB_General_n_s = new QSpinBox();
        spinB_General_n_s->setLocale(QLocale::C);
        spinB_General_n_s->setSingleStep(1);
        spinB_General_n_s->setMinimum(0);
        spinB_General_n_s->setMaximum(1e6);
        spinB_General_n_s->setValue(_General_n_s);
        connect(spinB_General_n_s,SIGNAL(valueChanged(int)),this,SLOT(spinB_General_n_s_changed(int)));
        hbox_s->addWidget(spinB_General_n_s);
        vbox2->addLayout(hbox_s);

        QHBoxLayout *hbox_h=new QHBoxLayout();
        QLabel *label_h = new QLabel(tr("harmonic n<sub>max</sub> = "));
        label_h->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        hbox_h->addWidget(label_h);
        spinB_General_n_h = new QSpinBox();
        spinB_General_n_h->setLocale(QLocale::C);
        spinB_General_n_h->setSingleStep(1);
        spinB_General_n_h->setMinimum(0);
        spinB_General_n_h->setMaximum(1e6);
        spinB_General_n_h->setValue(_General_n_h);
        connect(spinB_General_n_h,SIGNAL(valueChanged(int)),this,SLOT(spinB_General_n_h_changed(int)));
        hbox_h->addWidget(spinB_General_n_h);
        vbox2->addLayout(hbox_h);

        QGroupBox *groupBox2_c2 = new QGroupBox(tr(""));
        QVBoxLayout *vbox2_c2 = new QVBoxLayout;

        QHBoxLayout *hbox_c2_1=new QHBoxLayout();
        QLabel *label_c2_1 = new QLabel(tr("two elements combination n<sub>max</sub>(f1) = "));
        label_c2_1->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        hbox_c2_1->addWidget(label_c2_1);
        spinB_General_n_c2_1 = new QSpinBox();
        spinB_General_n_c2_1->setLocale(QLocale::C);
        spinB_General_n_c2_1->setSingleStep(1);
        spinB_General_n_c2_1->setMinimum(0);
        spinB_General_n_c2_1->setMaximum(1e6);
        spinB_General_n_c2_1->setValue(_General_n_c2_1);
        connect(spinB_General_n_c2_1,SIGNAL(valueChanged(int)),this,SLOT(spinB_General_n_c2_1_changed(int)));
        hbox_c2_1->addWidget(spinB_General_n_c2_1);
        vbox2_c2->addLayout(hbox_c2_1);

        QHBoxLayout *hbox_c2_2=new QHBoxLayout();
        QLabel *label_c2_2 = new QLabel(tr("two elements combination n<sub>max</sub>(f2) = "));
        label_c2_2->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        hbox_c2_2->addWidget(label_c2_2);
        spinB_General_n_c2_2 = new QSpinBox();
        spinB_General_n_c2_2->setLocale(QLocale::C);
        spinB_General_n_c2_2->setSingleStep(1);
        spinB_General_n_c2_2->setMinimum(0);
        spinB_General_n_c2_2->setMaximum(1e6);
        spinB_General_n_c2_2->setValue(_General_n_c2_2);
        connect(spinB_General_n_c2_2,SIGNAL(valueChanged(int)),this,SLOT(spinB_General_n_c2_2_changed(int)));
        hbox_c2_2->addWidget(spinB_General_n_c2_2);
        vbox2_c2->addLayout(hbox_c2_2);

        groupBox2_c2->setLayout(vbox2_c2);
        vbox2->addWidget(groupBox2_c2);

        QGroupBox *groupBox2_c3 = new QGroupBox(tr(""));
        QVBoxLayout *vbox2_c3 = new QVBoxLayout;

        QHBoxLayout *hbox_c3_1=new QHBoxLayout();
        QLabel *label_c3_1 = new QLabel(tr("three elements combination n<sub>max</sub>(f1) = "));
        label_c3_1->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        hbox_c3_1->addWidget(label_c3_1);
        spinB_General_n_c3_1 = new QSpinBox();
        spinB_General_n_c3_1->setLocale(QLocale::C);
        spinB_General_n_c3_1->setSingleStep(1);
        spinB_General_n_c3_1->setMinimum(0);
        spinB_General_n_c3_1->setMaximum(1e6);
        spinB_General_n_c3_1->setValue(_General_n_c3_1);
        connect(spinB_General_n_c3_1,SIGNAL(valueChanged(int)),this,SLOT(spinB_General_n_c3_1_changed(int)));
        hbox_c3_1->addWidget(spinB_General_n_c3_1);
        vbox2_c3->addLayout(hbox_c3_1);

        QHBoxLayout *hbox_c3_2=new QHBoxLayout();
        QLabel *label_c3_2 = new QLabel(tr("three elements combination n<sub>max</sub>(f2) = "));
        label_c3_2->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        hbox_c3_2->addWidget(label_c3_2);
        spinB_General_n_c3_2 = new QSpinBox();
        spinB_General_n_c3_2->setLocale(QLocale::C);
        spinB_General_n_c3_2->setSingleStep(1);
        spinB_General_n_c3_2->setMinimum(0);
        spinB_General_n_c3_2->setMaximum(1e6);
        spinB_General_n_c3_2->setValue(_General_n_c3_2);
        connect(spinB_General_n_c3_2,SIGNAL(valueChanged(int)),this,SLOT(spinB_General_n_c3_2_changed(int)));
        hbox_c3_2->addWidget(spinB_General_n_c3_2);
        vbox2_c3->addLayout(hbox_c3_2);

        groupBox2_c3->setLayout(vbox2_c3);
        vbox2->addWidget(groupBox2_c3);

        QHBoxLayout *hbox_c3_3=new QHBoxLayout();
        QLabel *label_c3_3 = new QLabel(tr("three elements combination n<sub>max</sub>(f3) = "));
        label_c3_3->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        hbox_c3_3->addWidget(label_c3_3);
        spinB_General_n_c3_3 = new QSpinBox();
        spinB_General_n_c3_3->setLocale(QLocale::C);
        spinB_General_n_c3_3->setSingleStep(1);
        spinB_General_n_c3_3->setMinimum(0);
        spinB_General_n_c3_3->setMaximum(1e6);
        spinB_General_n_c3_3->setValue(_General_n_c3_3);
        connect(spinB_General_n_c3_3,SIGNAL(valueChanged(int)),this,SLOT(spinB_General_n_c3_3_changed(int)));
        hbox_c3_3->addWidget(spinB_General_n_c3_3);
        vbox2_c3->addLayout(hbox_c3_3);

        groupBox2_c3->setLayout(vbox2_c3);

        groupBox2->setLayout(vbox2);
        dialog_General_layout->addWidget(groupBox2);


        QGroupBox *groupBox3 = new QGroupBox(tr("Auto mode option"));
        radio_General_use_combination = new QRadioButton(tr("&Use first combination"));
        connect(radio_General_use_combination,SIGNAL(toggled(bool)),this,SLOT(radio_General_use_combination_changed(bool)));
        radio_General_use_independent = new QRadioButton(tr("A&ssume, that all frequencies are independent"));
        connect(radio_General_use_independent,SIGNAL(toggled(bool)),this,SLOT(radio_General_use_independent_changed(bool)));
        QVBoxLayout *vbox3 = new QVBoxLayout();
        vbox3->addWidget(radio_General_use_combination);
        vbox3->addWidget(radio_General_use_independent);
        if(_use_first_combination){
            radio_General_use_combination->setChecked(true);
        }else{
            radio_General_use_independent->setChecked(true);
        }
        QHBoxLayout *layout_h_crit_SN = new QHBoxLayout();
        QLabel *label_stop_crit = new QLabel("stop when S/N<");
        label_stop_crit->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        layout_h_crit_SN->addWidget(label_stop_crit);
        spinB_General_auto_stop_crit_SN = new QDoubleSpinBox();
        spinB_General_auto_stop_crit_SN->setLocale(QLocale::C);
        spinB_General_auto_stop_crit_SN->setSingleStep(1);
        spinB_General_auto_stop_crit_SN->setMinimum(0);
        spinB_General_auto_stop_crit_SN->setMaximum(1000);
        spinB_General_auto_stop_crit_SN->setValue(_crit_stop);
        connect(spinB_General_auto_stop_crit_SN,SIGNAL(valueChanged(double)),this,SLOT(spinB_General_auto_stop_crit_SN_changed(double)));
        layout_h_crit_SN->addWidget(spinB_General_auto_stop_crit_SN);
        spinB_General_auto_stop_crit_SN->setAlignment(Qt::AlignLeft);
        layout_h_crit_SN->addSpacing(1);
        vbox3->addLayout(layout_h_crit_SN);
        layout_h_crit_SN->setStretch(0,0);
        layout_h_crit_SN->setStretch(1,1);

        groupBox3->setLayout(vbox3);
        dialog_General_layout->addWidget(groupBox3);


        QGroupBox *groupBox4 = new QGroupBox(tr("Highest peaks"));
        QVBoxLayout *vbox4_main = new QVBoxLayout();

        QGroupBox *groupBox4_1 = new QGroupBox(tr(""));
        radio_General_use_all_peaks = new QRadioButton(tr("&Take all peaks"));
        connect(radio_General_use_all_peaks,SIGNAL(toggled(bool)),this,SLOT(radio_General_use_all_peaks_changed(bool)));
        radio_General_use_selected_peaks = new QRadioButton(tr("I&gore frequencies closer than the resolution:"));
        connect(radio_General_use_selected_peaks,SIGNAL(toggled(bool)),this,SLOT(radio_General_use_selected_peaks_changed(bool)));
        _skipp_peaks_resolution = new QDoubleSpinBox();
        _skipp_peaks_resolution->setLocale(QLocale::C);
        _skipp_peaks_resolution->setSingleStep(0.01);
        _skipp_peaks_resolution->setMinimum(0);
        _skipp_peaks_resolution->setMaximum(1e6);
        _skipp_peaks_resolution->setDecimals(6);
        _skipp_peaks_resolution->setValue(_resolution);
        if(_dT>0){
           _skipp_peaks_resolution->setValue(_resolution_for_combination_factor/_dT);
           _skipp_peaks_resolution->setSingleStep(_resolution_for_combination_step*_resolution_for_combination_factor/_dT);
           _resolution=_skipp_peaks_resolution->value();
        }
        connect(_skipp_peaks_resolution,SIGNAL(valueChanged(double)),this,SLOT(skipp_peaks_resolution_changed(double)));
        QVBoxLayout *vbox4 = new QVBoxLayout();
        vbox4->addWidget(radio_General_use_all_peaks);
        vbox4->addWidget(radio_General_use_selected_peaks);
        QHBoxLayout *hbox_for_resolution = new QHBoxLayout();
        //vbox4->addWidget(_skipp_peaks_resolution);
        hbox_for_resolution->addStretch(1);
        QLabel *label_res = new QLabel("resolution=");
        label_res->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        hbox_for_resolution->addWidget(_skipp_peaks_resolution);
        vbox4->addLayout(hbox_for_resolution);
        if(_skipp_peaks_closer_than_resolution){
            radio_General_use_selected_peaks->setChecked(true);
        }else{
            radio_General_use_all_peaks->setChecked(true);
        }
        groupBox4_1->setLayout(vbox4);


        QGroupBox *groupBox4_2 = new QGroupBox(tr(""));
        radio_General_use_h_peaks = new QRadioButton(tr("&Take the highest peaks"));
        connect(radio_General_use_h_peaks,SIGNAL(toggled(bool)),this,SLOT(radio_General_use_h_peaks_changed(bool)));
        radio_General_use_h_SN = new QRadioButton(tr("T&ake the highest S/N"));
        connect(radio_General_use_h_SN,SIGNAL(toggled(bool)),this,SLOT(radio_General_use_h_SN_changed(bool)));
        QVBoxLayout *vbox4_2 = new QVBoxLayout();
        vbox4_2->addWidget(radio_General_use_h_peaks);
        vbox4_2->addWidget(radio_General_use_h_SN);
        if(_use_highest_peaks){
           radio_General_use_h_peaks->setChecked(true);
        }else{
           radio_General_use_h_SN->setChecked(true);
        }
        groupBox4_2->setLayout(vbox4_2);

        vbox4_main->addWidget(groupBox4_1);
        vbox4_main->addWidget(groupBox4_2);

        groupBox4->setLayout(vbox4_main);
        dialog_General_layout->addWidget(groupBox4);





    }
    dialog_General->show();
    dialog_General->raise();
    dialog_General->activateWindow();
}

void MainWindow::spinB_General_auto_stop_crit_SN_changed(double crit){
    _crit_stop=crit;
}
void MainWindow::spinB_NLSF_maxiter_changed(int maxiter){
    _NLSF_max_iteration=maxiter;
}
void MainWindow::spinB_General_nfreq_changed(int nfreq){
    _General_n_last_freq=nfreq;
}
void MainWindow::spinB_General_n_s_changed(int n){
    _General_n_s=n;
}
void MainWindow::spinB_General_n_h_changed(int n){
    _General_n_h=n;
}
void MainWindow::spinB_General_n_c2_1_changed(int n){
    _General_n_c2_1=n;
}
void MainWindow::spinB_General_n_c2_2_changed(int n){
    _General_n_c2_2=n;
}
void MainWindow::spinB_General_n_c3_1_changed(int n){
    _General_n_c3_1=n;
}
void MainWindow::spinB_General_n_c3_2_changed(int n){
    _General_n_c3_2=n;
}
void MainWindow::spinB_General_n_c3_3_changed(int n){
    _General_n_c3_3=n;
}
void MainWindow::radio_General_use_combination_changed(bool checked){
    if(checked){
        _use_first_combination=true;
    }
}
void MainWindow::radio_General_use_independent_changed(bool checked){
    if(checked){
        _use_first_combination=false;
    }
}
void MainWindow::radio_General_use_all_peaks_changed(bool checked){
    if(checked){
        _skipp_peaks_closer_than_resolution=false;
    }
}
void MainWindow::radio_General_use_selected_peaks_changed(bool checked){
    if(checked){
        _skipp_peaks_closer_than_resolution=true;
        _resolution=_skipp_peaks_resolution->value();

    }
}

void MainWindow::radio_General_use_h_peaks_changed(bool checked){
    if(checked){
        _use_highest_peaks=true;
       //cout<<"radio_General_use_h_peaks_changed: _use_highest_peaks="<<_use_highest_peaks<<endl;
    }
}

void MainWindow::radio_General_use_h_SN_changed(bool checked){
    if(checked){
        _use_highest_peaks=false;
        //cout<<"radio_General_use_h_SN_changed: _use_highest_peaks="<<_use_highest_peaks<<endl;
    }
}

void MainWindow::skipp_peaks_resolution_changed(double){
    _resolution=_skipp_peaks_resolution->value();
}

void MainWindow::add_max_peak(){
    if(!_skipp_peaks_closer_than_resolution){
       if(_frpeaks.size()>0 && _amplpeaks.size()>0){
           double f=_frpeaks[0];
           double sn=-1;
           if(_noise_ok){
              sn=_amplpeaks[0]/spline_noise.e(f);
           }
           add_freq_to_table(f,sn);
        }
    }else{
        for(size_t i=0;i<_frpeaks.size();++i){
            if(is_closer_than_freqs_from_table(_frpeaks[i])){

            }else{
                double f=_frpeaks[i];
                double sn=-1;
                if(_noise_ok){
                   sn=_amplpeaks[i]/spline_noise.e(f);
                }
                add_freq_to_table(f,sn);
                break;
            }
         }

    }
}
bool MainWindow::is_closer_than_freqs_from_table(double freq){
    bool ok=false;
    int ind_freq=-1;
    for(auto i=0;i<table->columnCount();++i){
        if(table->horizontalHeaderItem(i)->text()=="freq"){
            ind_freq=i;
            break;
        }
    }
    if(ind_freq!=-1){
        for(auto i=0;i<table->rowCount();++i){
           double freq_table=table->item(i,ind_freq)->text().toDouble();
           if(abs(freq_table-freq)<_resolution){
               ok=true;
               break;
           }
        }
    }

    return(ok);
}

void MainWindow::get_trf_FastFourier_WS(){//written by Wojciech Szewczuk
    //pushB_trf1 QPushButton fwpeaks
    cout<<"QPushButton pushB_trf1 fwpeaks triggered"<<endl;

    if(_file.ok()){
        fast_LS_periodogram LS;
        double f0=_f0;
        double fe=_fe;
        double df=_df;
        vector<double>y;
        vector<double>x=f_get_column(_file.file(),_file.head(),"1");
        if(!_residuals_ok){
           y=f_get_column(_file.file(),_file.head(),"2");
        }
        vector<double>e_y=f_get_column(_file.file(),_file.head(),"3");

        //    void calculate_LS(const vector<double> & t, const vector<double> & y, const int npts , const double over=4 , const double hifac=1, bool save_trf=true);
        //    void find_nu_max_amp(double StoNlimit=4, bool noise_in_window=true, double window_size=1);
        if(!_residuals_ok){
           LS.calculate_LS(x, y, x.size() ,f0,fe,df, 4 , 1, false,_use_data);
        }else{
           LS.calculate_LS(x, _residuals, x.size() ,f0,fe,df, 4 , 1, false,_use_data);
        }

        _trf_ok=true;
        _fr=LS.fr();
        _ampl=LS.ampl();

        _frpeaks=LS.frpeaks();
        _amplpeaks=LS.amplpeaks();
        _Ppeaks=LS.Ppeaks();
        _SNpeaks=LS.SNpeaks();

        _xmin=f_min(_fr);
        _xmax=f_max(_fr);
        _ymin=f_min(_ampl);
        _ymax=f_max(_ampl);
        //cout<<"_fr size = "<<_fr.size()<<endl;
        plot_trf();
        if(_noise_ok){
            calculate_noise();
            plot_noise();
        }
        if(_ind_graph_peaks_fwpeaks>0){
            show_peaks();
        }
    }
}



void MainWindow::get_trf_fwpeaks(){
    //pushB_trf1 QPushButton fwpeaks
    //cout<<"QPushButton pushB_trf1 fwpeaks triggered"<<endl;

    if(_file.ok()){

        FWPeaks fwpeaks;
        double f0=_f0;
        double fe=_fe;
        double df=_df;
        vector<double>y;
        vector<double>x=f_get_column(_file.file(),_file.head(),"1");
        if(!_residuals_ok){
           y=f_get_column(_file.file(),_file.head(),"2");
        }
        vector<double>e_y=f_get_column(_file.file(),_file.head(),"3");
        if(!_residuals_ok){
            fwpeaks.fourier(x,y,e_y,f0,fe,df,_use_data);
        }else{
            fwpeaks.fourier(x,_residuals,e_y,f0,fe,df,_use_data);
        }
        _trf_ok=true;
        _fr=fwpeaks.fr();
        _ampl=fwpeaks.ampl();

        _frpeaks=fwpeaks.frpeaks();
        _amplpeaks=fwpeaks.amplpeaks();
        _Ppeaks=fwpeaks.Ppeaks();
        _SNpeaks=fwpeaks.SNpeaks();

        _xmin=f_min(_fr);
        _xmax=f_max(_fr);
        _ymin=f_min(_ampl);
        _ymax=f_max(_ampl);
        //cout<<"_fr size = "<<_fr.size()<<endl;
        plot_trf();
        if(_noise_ok){
            first_lc=true;
            calculate_noise();
            plot_noise();
        }
        if(_ind_graph_peaks_fwpeaks>0){
            show_peaks();
        }
    }
}

void MainWindow::show_peaks_clicked(){
    if(_ind_graph_peaks_fwpeaks>0){        
         hide_peaks();
         _show_peaks=false;
    }else{
         show_peaks();         
         _show_peaks=true;
    }
}


void MainWindow::get_peaks(){
    //cout<<"get_peaks"<<endl;
    _frpeaks.clear();
    _amplpeaks.clear();
    _Ppeaks.clear();
    _SNpeaks.clear();

    if(!_noise_ok){
        pushB_calculate_noise();
    }

    int nfreqs=_fr.size();
    //cout<<"nfreqs="<<nfreqs<<endl;
    for(int i=1; i<nfreqs; i++){
         if(i<nfreqs-1){
             if(_ampl[i-1]<_ampl[i] && _ampl[i]>_ampl[i+1]){
                 _frpeaks.push_back(_fr[i]);
                 _amplpeaks.push_back(_ampl[i]);
                 _Ppeaks.push_back(1.0/_fr[i]);
                 _SNpeaks.push_back(_ampl[i]/spline_noise.e(_fr[i]));
             }
         }
    }

    if(_use_highest_peaks){
        //cout<<"using highest peaks"<<endl;
        f_sort_mr(_amplpeaks,_frpeaks,_Ppeaks,_SNpeaks);
    }else{
        //cout<<"using highest SN"<<endl;
        f_sort_mr(_SNpeaks,_amplpeaks,_frpeaks,_Ppeaks);
    }

}

void MainWindow::show_peaks(){
    if(_fr.size()>0){

        get_peaks();

        _show_peaks=true;
        pushB_showPeaks->setText("hide peaks");
        size_t n=_frpeaks.size();
        if(n>_n_peaks)n=_n_peaks;
        QVector<double>qx(n),qy(n);


        if(!_skipp_peaks_closer_than_resolution){
           f_convert_data(_frpeaks,_amplpeaks,qx,qy,n);
        }else{
           vector<double>x,y;
           for(size_t i=0;i<_frpeaks.size();++i){
               if(is_closer_than_freqs_from_table(_frpeaks[i])){

               }else{
                  x.push_back(_frpeaks[i]);
                  y.push_back(_amplpeaks[i]);
               }
               if(x.size()>=n){
                   break;
               }
           }
           qx.resize(x.size());
           qy.resize(x.size());
           f_convert_data(x,y,qx,qy);
           if(x.size()<n)n=x.size();
       }

       double dy=_ymax-_ymin;
       for(size_t i=0;i<n;++i){
          qy[i]+=0.01*dy;
       }


       if(_ind_graph_peaks_fwpeaks==-1){
           _ind_graph_peaks_fwpeaks=customPlot->graphCount();
           customPlot->addGraph();
       }
       customPlot->graph(_ind_graph_peaks_fwpeaks)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssTriangleInverted, Qt::blue,QColor(50,200,100), 15));

       customPlot->graph(_ind_graph_peaks_fwpeaks)->setData(qx,qy);
       //ui->customPlot->graph(_ind_graph_peaks_fwpeaks)->removeFromLegend();
       customPlot->graph(_ind_graph_peaks_fwpeaks)->addToLegend();
       customPlot->graph(_ind_graph_peaks_fwpeaks)->setName("peaks");
       customPlot->graph(_ind_graph_peaks_fwpeaks)->setPen(QColor(Qt::black));
       customPlot->graph(_ind_graph_peaks_fwpeaks)->setLineStyle(QCPGraph::lsNone);

       if(Textpeaks.size()==0){
          for(size_t i=0;i<n;++i){
             QCPItemText *Textpeak = new QCPItemText(customPlot);
             Textpeaks.push_back(Textpeak);
          }
       }
       for(size_t i=0;i<n;++i){
          Textpeaks[i]->position->setType(QCPItemPosition::ptPlotCoords);
          Textpeaks[i]->setPositionAlignment(Qt::AlignCenter|Qt::AlignBottom);
          Textpeaks[i]->position->setCoords(qx[i],qy[i]);
          string text=to_string(i+1);
          Textpeaks[i]->setText(text.c_str());
          Textpeaks[i]->setTextAlignment(Qt::AlignCenter);
          Textpeaks[i]->setFont(QFont(font().family(), 9));
          Textpeaks[i]->setPadding(QMargins(0, -25, 0, 0));
       }

       customPlot->replot();
   }
}

void MainWindow::hide_peaks(){
    pushB_showPeaks->setText("show peaks");
    if(_ind_graph_peaks_fwpeaks!=-1){
        customPlot->removeGraph(_ind_graph_peaks_fwpeaks);
        if(_ind_graph_noise>_ind_graph_peaks_fwpeaks){
                --_ind_graph_noise_sn5;
                --_ind_graph_noise_sn4;
                --_ind_graph_noise;
        }

        _ind_graph_peaks_fwpeaks=-1;
        int n=(int)Textpeaks.size()-1;
        for(int i=n;i>=0;--i){
            cout<<(Textpeaks[i]->text()).toStdString()<<endl;
           customPlot->removeItem(Textpeaks[i]);
        }
        Textpeaks.clear();
        customPlot->replot();
    }
}






void MainWindow::slider_no_box_valueChanged(int k){
    /*_box_number=k;
    if(spinbox_no_box->value()!=k){
       spinbox_no_box->setValue(k);
    }
    calculate_trend();
    */
}



void MainWindow::spinbox_no_box_valueChanged(int k){
    _box_number=k;
    //if(slider_no_box->value()!=k){
    //   slider_no_box->setValue(k);
    //}
    calculate_trend();
}


void MainWindow::pushB_detrend_clicked(){
    if(detrended_ok){
        detrend_splines.push_back(detrend_spline);
        pushB_restore->setText(("restore("+to_string(detrend_splines.size())+")").c_str());
        for(size_t i=0;i<_file.file().size();++i){
            _file.file()[i][1]-=detrend_spline.e(_file.file()[i][0]);
        }
        detrended_ok=false;
        plot_lc();
        calculate_trend();
        already_added=true;
    }
}


void MainWindow::pushB_restore_clicked(){
    if(detrended_ok){
       if(detrend_splines.size()>0){
          for(size_t i=0;i<_file.file().size();++i){
             _file.file()[i][1]+=detrend_splines.back().e(_file.file()[i][0]);
          }
          detrend_splines.erase(detrend_splines.end());
          pushB_restore->setText(("restore("+to_string(detrend_splines.size())+")").c_str());
          detrended_ok=false;
          plot_lc();
          calculate_trend();

       }
    }
}



void MainWindow::spinbox_setf0(double f){
   _f0=f;
   if(_init_layout){
       double box_width=2*(spinbox_fe->value()-spinbox_f0->value());
       if(spinbox_box_width->value()>box_width){
              spinbox_box_width->setValue(box_width);
       }
   }
}
void MainWindow::spinbox_setfe(double f){
   _fe=f;
   if(_init_layout){
       double box_width=2*(spinbox_fe->value()-spinbox_f0->value());
       if(spinbox_box_width->value()>box_width){
              spinbox_box_width->setValue(box_width);
       }
   }
}
void MainWindow::spinbox_setdf(double f){
   _df=f;
   //cout<<"new df="<<_df<<endl;
   if((_fe-_f0)/_df<2){
       //cout<<"set maximal value of df"<<endl;
       _df=(_fe-_f0)/2.0;
       spinbox_df->setValue(_df);
   }
}


void MainWindow::pushB_open_simulation_dialog_slot(){
    if(!_dialog_simulation_ok){
            _dialog_simulation_ok=true;
            simstatMW = new SimStat(this);
            simstatMW->setWindowTitle("Simulation");
            simstatMW->setGeometry(0,0,300,400);
            //simstatMW->setWindowModality(Qt::WindowModal);
            QHBoxLayout* mainh_layout = new QHBoxLayout(simstatMW->centralWidget());
            simulation_dialog_layout = new QGridLayout();
            spinbox_simulationNO = new QSpinBox();
            spinbox_simulationNO->setMinimum(1);
            spinbox_simulationNO->setMaximum(1e6);
            spinbox_simulationNO->setValue(100);
            spinbox_simulationNO->setSingleStep(100);
            QLabel* label = new QLabel("<font color="+basic_color_font+">Simulation Number");
            label->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
            simulation_dialog_layout->addWidget(label,0,0);
            simulation_dialog_layout->addWidget(spinbox_simulationNO,0,1);

            spinbox_simulation_sigma = new QSpinBox();
            spinbox_simulation_sigma->setMinimum(0);
            spinbox_simulation_sigma->setMaximum(1e6);
            double ampl=abs(_ymax_Lc-_ymin_Lc)/10;
            spinbox_simulation_sigma->setValue(ampl);
            spinbox_simulation_sigma->setSingleStep(1);
            QLabel* label2 = new QLabel("<font color="+basic_color_font+">Noise amplitude");
            label2->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
            simulation_dialog_layout->addWidget(label2,1,0);
            simulation_dialog_layout->addWidget(spinbox_simulation_sigma,1,1);

            pushB_start_simulation = new QPushButton("Start Simulation");
            simulation_dialog_layout->addWidget(pushB_start_simulation,2,0,1,2);
            connect(pushB_start_simulation,SIGNAL(clicked()),this,SLOT(pushB_start_simulation_slot()));

            QVBoxLayout* vlayout_plot_interactively = new QVBoxLayout();
            simulation_dialog_layout->addLayout(vlayout_plot_interactively,3,0,1,2);
            //QSpacerItem* spacer = new QSpacerItem(1,1,QSizePolicy::Minimum,QSizePolicy::Expanding);
            //simulation_dialog_layout->addItem(spacer,4,0,1,2);

            //QLabel* label3 = new QLabel("<font color="+basic_color_font+">Show consecutive plots?");
            //label3->setAlignment(Qt::AlignHCenter);
            //vlayout_plot_interactively->addWidget(label3);

            QHBoxLayout* hlayout_plot_interactively = new QHBoxLayout();
            radioB_plot_interactively_no = new QRadioButton();
            radioB_plot_interactively_no->setText("no");
            radioB_plot_interactively_no->setStyleSheet("color: "+basic_color_font+"");
            radioB_plot_interactively_no->setChecked(true);
            radioB_plot_interactively_yes = new QRadioButton();
            radioB_plot_interactively_yes->setText("yes");
            radioB_plot_interactively_yes->setStyleSheet("color: "+basic_color_font+"");
            //radioB_plot_interactively_yes->setChecked(true);
            hlayout_plot_interactively->addWidget(radioB_plot_interactively_no);
            hlayout_plot_interactively->addWidget(radioB_plot_interactively_yes);
            QGroupBox *groupBox = new QGroupBox(tr("Show consecutive plots?"));
            groupBox->setStyleSheet("color: "+basic_color_font+"");
            groupBox->setAlignment(Qt::AlignHCenter);
            groupBox->setLayout(hlayout_plot_interactively);
            //vlayout_plot_interactively->addLayout(hlayout_plot_interactively);
            vlayout_plot_interactively->addWidget(groupBox);


            QVBoxLayout* vlayout_trf = new QVBoxLayout();
            simulation_dialog_layout->addLayout(vlayout_trf,4,0,1,2);
            QSpacerItem* spacer2 = new QSpacerItem(1,1,QSizePolicy::Minimum,QSizePolicy::Expanding);
            simulation_dialog_layout->addItem(spacer2,5,0,1,2);

            //QLabel* label4 = new QLabel("<font color="+basic_color_font+">TRF");
            //label4->setAlignment(Qt::AlignHCenter);
            //vlayout_trf->addWidget(label4);
            QHBoxLayout* hlayout_trf = new QHBoxLayout();
            radioB_hlayout_trf_fwpeaks = new QRadioButton();
            radioB_hlayout_trf_fwpeaks->setText("fwpeaks");
            radioB_hlayout_trf_fwpeaks->setStyleSheet("color: "+basic_color_font+"");
            radioB_hlayout_trf_FF = new QRadioButton();
            radioB_hlayout_trf_FF->setText("FF WS");
            radioB_hlayout_trf_FF->setStyleSheet("color: "+basic_color_font+"");
            radioB_hlayout_trf_FF->setChecked(true);
            hlayout_trf->addWidget(radioB_hlayout_trf_fwpeaks);
            hlayout_trf->addWidget(radioB_hlayout_trf_FF);
            QGroupBox *groupBox2 = new QGroupBox(tr("TRF"));
            groupBox2->setStyleSheet("color: "+basic_color_font+"");
            groupBox2->setAlignment(Qt::AlignHCenter);
            //hlayout_trf->addStretch(1);
            groupBox2->setLayout(hlayout_trf);
            //vlayout_trf->addLayout(hlayout_trf);
            vlayout_trf->addWidget(groupBox2);

            mainh_layout->addLayout(simulation_dialog_layout);

            QVBoxLayout* vplot_layout = new QVBoxLayout();

            QGridLayout* button_grid_layout = new QGridLayout();
            vplot_layout->addLayout(button_grid_layout);
            /*
            QGridLayout* plot_grid_layout = new QGridLayout();
            //vplot_layout->addLayout(plot_grid_layout);
            simstst_customPlotsn = new QCustomPlot();
            plot_grid_layout->addWidget(simstst_customPlotsn,0,0);
            simstst_customPlotf = new QCustomPlot();
            plot_grid_layout->addWidget(simstst_customPlotf,1,0);
            */

            simulation_label = new QLabel("");
            simulation_dialog_layout->addWidget(simulation_label,6,0,1,2);
            simulation_label->setWordWrap(true);
            simulation_label->setMaximumWidth(300);


            mainh_layout->addLayout(vplot_layout);
            mainh_layout->setStretch(0,0);
            mainh_layout->setStretch(1,1);


            QVBoxLayout* vplot_layout_plot = new QVBoxLayout();
            mainh_layout->addLayout(vplot_layout_plot);
            mainh_layout->setStretch(2,2);


            QHBoxLayout *layout_h_slider_plot = new QHBoxLayout();
            vplot_layout_plot->addLayout(layout_h_slider_plot);
            vplot_layout_plot->setStretch(0,0);

            simulation_SpinBox = new QSpinBox();
            layout_h_slider_plot->addWidget(simulation_SpinBox);
            layout_h_slider_plot->setStretch(0,0);
            simulation_SpinBox->setLocale(QLocale::C);
            simulation_SpinBox->setSingleStep(1);
            simulation_SpinBox->setMinimum(2);
            simulation_SpinBox->setMaximum(1e4);
            simulation_SpinBox->setValue(2);
            connect(simulation_SpinBox,SIGNAL(valueChanged(int)),this,SLOT(simulation_spinBox_changed(int)));


            simulation_slider = new QSlider();
            simulation_slider->setOrientation(Qt::Horizontal);
            layout_h_slider_plot->addWidget(simulation_slider);
            int nmax=100;
            int step=2;
            simulation_slider->setSingleStep(step);
            simulation_slider->setMinimum(2);
            simulation_slider->setMaximum(nmax);
            layout_h_slider_plot->setStretch(1,1);
            connect(simulation_slider,SIGNAL(valueChanged(int)),this,SLOT(simulation_slider_changed(int)));


            customPlot_simulation = new QCustomPlot();
            //mainh_layout->addWidget(customPlot_simulation);
            vplot_layout_plot->addWidget(customPlot_simulation);
            vplot_layout_plot->setStretch(1,1);
            init_customPlot_simulation("S/N","N");
            customPlot_simulation->setMinimumWidth(300);


            simulation_statusBar = new QStatusBar();
            vplot_layout_plot->addWidget(simulation_statusBar);
            vplot_layout_plot->setStretch(2,0);


            simulation_bar = new QCPBars(customPlot_simulation->xAxis, customPlot_simulation->yAxis);
            simulation_bar->setAntialiased(false); // gives more crisp, pixel aligned bar borders
            simulation_bar->setStackingGap(1);
            // set names and colors:
            simulation_bar->setName("");
            simulation_bar->removeFromLegend();

            //simstatMW->setWindowModality(Qt::ApplicationModal);
            //simstatMW->setWindowModality(Qt::WindowModal);
    }

    simstatMW->show();
    simstatMW->raise();
    simstatMW->activateWindow();

    /*dialog_simulation->show();
    dialog_simulation->raise();
    dialog_simulation->activateWindow();*/
}
void MainWindow::simulation_spinBox_changed(int k){
    if(k!=simulation_slider->value() && k<=simulation_slider->maximum()){
         simulation_slider->setValue(k);
    }else{
         simulation_analyse(k);
    }

}
void MainWindow::simulation_slider_changed(int k){
    //int k=simulation_slider->value();
    if(k!=round(simulation_SpinBox->value())){
         simulation_SpinBox->setValue(k);
    }else{
        simulation_analyse(k);
   }
}
/*
Worker::Worker() { // Constructor
    // you could copy data from constructor arguments to internal variables here.
}

Worker::~Worker() { // Destructor
    // free resources
}

void Worker::process() { // Process. Start processing data.
    // allocate resources using new here
    qDebug("Hello World!");
    cout<<name<<endl;
    emit finished();
}*/




void MainWindow::pushB_start_simulation_slot(){
    if(_dialog_simulation_ok){
          bool trf_after_sim;
          if(!_trf_ok)trf_after_sim=false;
          else trf_after_sim=true;
          //simstatMW->setWindowModality(Qt::ApplicationModal);
          //ui->centralwidget-> setDisabled(true);
          this->setDisabled(true);
          bool replot_ok=true;
          if(radioB_plot_interactively_no->isChecked()){
              replot_ok=false;
          }
          pushB_start_simulation_ok=true;

          if(radioB_hlayout_trf_fwpeaks->isChecked()){
              _chosen_trf=0;
          }
          if(radioB_hlayout_trf_FF->isChecked()){
              _chosen_trf=1;
          }

          if(replot_ok){
              pushB_start_simulation_slot_graph();
          }else{
              pushB_start_simulation_slot_nograph();
              /*

              QThread* thread = new QThread();
              Worker* worker = new Worker();
              worker->moveToThread(thread);
              connect( thread, &QThread::started, worker, &Worker::process);
              connect( worker, &Worker::finished, thread, &QThread::quit);
              connect( worker, &Worker::finished, worker, &Worker::deleteLater);
              connect( thread, &QThread::finished, thread, &QThread::deleteLater);
              thread->start();

              QThread* thread2 = new QThread();
              Worker* worker2 = new Worker();
              worker->name="th2";
              worker->moveToThread(thread);
              connect( thread2, &QThread::started, worker2, &Worker::process);
              connect( worker2, &Worker::finished, thread2, &QThread::quit);
              connect( worker2, &Worker::finished, worker2, &Worker::deleteLater);
              connect( thread2, &QThread::finished, thread2, &QThread::deleteLater);
              thread2->start();

              */

          }
          pushB_start_simulation_ok=false;
          _trf_ok=trf_after_sim;

          //ui->centralwidget->setEnabled(true);
          this->setDisabled(false);
    }
}

void MainWindow::pushB_start_simulation_slot_graph(){
            cout<<"Simulation on"<<endl;
            int ns=spinbox_simulationNO->value();
            //cout<<"Simulation number = "<<ns<<endl;
            random_device rd;
            //default_random_engine generator{100};
            double sigma = spinbox_simulation_sigma->value();
            normal_distribution<double> distribution(0,sigma);
            vector<double>x=f_get_column(_file.file(),_file.head(),"1");
            //vector<double>y=f_get_column(_file.file(),_file.head(),"2");
            //vector<double>e_y=f_get_column(_file.file(),_file.head(),"3");
            size_t n=x.size();

            cout<<"dddd"<<endl;
            vector<double> weighs(n);
            vector<double> ampl_noise(n);
            QVector<double>qx(n),qy(n),qerr(n);
            for(size_t i=0;i<n;++i){
                 weighs[i]=1.0;
                 qx[i]=x[i];
                 qerr[i]=weighs[i];
            }
            //vector<double>SN(ns);
            SN.resize(ns);
            //vector<double>SNfr(ns);
            //vector<double>SNAmpl(ns);
            //vector<double>SNsn(ns);
            SNfr.resize(ns);
            SNAmpl.resize(ns);
            SNsn.resize(ns);


            cout<<"dddd"<<endl;
            for(size_t is=0;is<ns;++is){
                if(!pushB_start_simulation_ok)break;
                   pushB_open_simulation_dialog->setText( ("("+to_string(is)+"/"+to_string(ns)+")").c_str() );

                for(size_t i=0;i<n;++i){
                     ampl_noise[i]=distribution(rd);
                     qy[i]=ampl_noise[i];
                }
                if(_ind_graph_lc!=-1){
                    customPlotLc->graph(_ind_graph_lc)->setData(qx,qy);
                    ErrorBars->setData(qerr);
                    if(_ind_graph_lc_detrend_points!=-1){
                         customPlotLc->removeGraph(_ind_graph_lc_detrend_inter);
                         customPlotLc->removeGraph(_ind_graph_lc_detrend_points);
                         _noise_ok=false;
                         _ind_graph_lc_detrend_inter=-1;
                         _ind_graph_lc_detrend_points=-1;
                    }
                    //calculate_trend();
                    if(is==0){
                        customPlotLc->rescaleAxes();
                    }
                    customPlotLc->replot();
                }
                cout<<"customPlotLc"<<endl;

                if(_chosen_trf==0){
                   FWPeaks fwpeaks;
                   fwpeaks.fourier(x,ampl_noise,weighs,_f0,_fe,_df);                   
                   _trf_ok=true;
                   _fr=fwpeaks.fr();
                   _ampl=fwpeaks.ampl();
                   calculate_noise();
                   get_peaks();
                   //_frpeaks=fwpeaks.frpeaks();
                   //_amplpeaks=fwpeaks.amplpeaks();
                   //_Ppeaks=fwpeaks.Ppeaks();
                   //_SNpeaks=fwpeaks.SNpeaks();
                }else if(_chosen_trf==1){
                    fast_LS_periodogram LS;
                    LS.calculate_LS(x, ampl_noise, x.size() ,_f0,_fe,_df, 4 , 1, false);
                    _trf_ok=true;
                    _fr=LS.fr();
                    _ampl=LS.ampl();
                    calculate_noise();
                    get_peaks();
                    //_frpeaks=LS.frpeaks();
                    //_amplpeaks=LS.amplpeaks();
                    //_Ppeaks=LS.Ppeaks();
                    //_SNpeaks=LS.SNpeaks();
                }

                _xmin=f_min(_fr);
                _xmax=f_max(_fr);
                _ymin=f_min(_ampl);
                _ymax=f_max(_ampl);

                plot_trf();
                calculate_noise();

                plot_noise();
                SN[is]=_amplpeaks[0]/spline_noise.e(_frpeaks[0]);
                SNfr[is]=_frpeaks[0];
                SNAmpl[is]=_amplpeaks[0];
                SNsn[is]=_SNpeaks[0];
                cout<<is<<" f="<<_frpeaks[0]<<" a="<<_amplpeaks[0]<<" "<<spline_noise.e(_frpeaks[0])<<" S/N="<<SN[is]<<" S/N from trf ="<<SNsn[is]<<endl;

             }

             pushB_open_simulation_dialog->setText("simulation");

             int nbox=10;
             nbox=round(sqrt(ns));
             if(nbox<5)nbox=5;
             simulation_SpinBox->setValue(nbox);
             //simulation_analyse(nbox);

}


void MainWindow::pushB_start_simulation_slot_nograph(){
            cout<<"Simulation on"<<endl;
            int ns=spinbox_simulationNO->value();
            //cout<<"Simulation number = "<<ns<<endl;
            random_device rd;
            //default_random_engine generator{100};
            double sigma = spinbox_simulation_sigma->value();
            normal_distribution<double> distribution(0,sigma);
            vector<double>x=f_get_column(_file.file(),_file.head(),"1");
            //vector<double>y=f_get_column(_file.file(),_file.head(),"2");
            //vector<double>e_y=f_get_column(_file.file(),_file.head(),"3");
            size_t n=x.size();
            pushB_start_simulation->setText( "Stom simulation");

            vector<double> weighs(n);
            vector<double> ampl_noise(n);
            //QVector<double>qx(n),qy(n),qerr(n);
            for(size_t i=0;i<n;++i){
                 weighs[i]=1.0;
                 //qx[i]=x[i];
                 //qerr[i]=weighs[i];
            }
            //vector<double>SN(ns);
            SN.resize(ns);
            //vector<double>SNfr(ns);
            //vector<double>SNAmpl(ns);
            //vector<double>SNsn(ns);
            SNfr.resize(ns);
            SNAmpl.resize(ns);
            SNsn.resize(ns);

            for(size_t is=0;is<ns;++is){
                //if(!pushB_start_simulation_ok)break;
                //if(is%100==0){
                //simstatMW->activateWindow();
                pushB_start_simulation->setText( ("("+to_string(is)+"/"+to_string(ns)+")").c_str() );
                //}
                for(size_t i=0;i<n;++i){
                     ampl_noise[i]=distribution(rd);
                     //qy[i]=ampl_noise[i];
                }

                if(_chosen_trf==0){
                    FWPeaks fwpeaks;
                    fwpeaks.fourier(x,ampl_noise,weighs,_f0,_fe,_df);
                    _trf_ok=true;
                    _fr=fwpeaks.fr();
                    _ampl=fwpeaks.ampl();
                    calculate_noise();
                    get_peaks();
                    //_frpeaks=fwpeaks.frpeaks();
                    //_amplpeaks=fwpeaks.amplpeaks();
                    //_Ppeaks=fwpeaks.Ppeaks();
                    //_SNpeaks=fwpeaks.SNpeaks();
                }else if(_chosen_trf==1){
                    fast_LS_periodogram LS;
                    LS.calculate_LS(x, ampl_noise, x.size() ,_f0,_fe,_df, 4 , 1, false);
                    _trf_ok=true;
                    _fr=LS.fr();
                    _ampl=LS.ampl();
                    calculate_noise();
                    get_peaks();
                    //_frpeaks=LS.frpeaks();
                    //_amplpeaks=LS.amplpeaks();
                    //_Ppeaks=LS.Ppeaks();
                    //_SNpeaks=LS.SNpeaks();
                }
                _xmin=f_min(_fr);
                _xmax=f_max(_fr);
                _ymin=f_min(_ampl);
                _ymax=f_max(_ampl);
                calculate_noise();
                SN[is]=_amplpeaks[0]/spline_noise.e(_frpeaks[0]);
                SNfr[is]=_frpeaks[0];
                SNAmpl[is]=_amplpeaks[0];
                SNsn[is]=_SNpeaks[0];
                if(is%100==0)cout<<is<<" f="<<_frpeaks[0]<<" a="<<_amplpeaks[0]<<" "<<spline_noise.e(_frpeaks[0])<<" S/N="<<SN[is]<<" S/N from trf ="<<SNsn[is]<<endl;

                if(is%5000==0){
                    string name2=f_remove_ext(_file.file_name())+"_"+to_string(ns)+"_input.dat";
                    ofstream fo{name2};
                    fo<<"No SN f A  SNo"<<endl;
                    for(size_t i=0;i<is;++i){
                        fo<<i<<" "<<SN[i]<<" "<<SNfr[i]<<" "<<SNAmpl[i]<<" "<<SNsn[i]<< endl;
                    }
                }
                //string text="iter = "+to_string(is);
                //simulation_label->setText(text.c_str());
             }
             _noise.clear();
             _noise_ok=false;
             pushB_start_simulation->setText("Start simulation");

             int nbox=10;
             nbox=round(sqrt(ns));
             if(nbox<5)nbox=5;
             simulation_SpinBox->setValue(nbox);
             //simulation_analyse(nbox);
}

void MainWindow::simulation_analyse(int nbox){

    int ns=SN.size();
    if(ns>1){
       cl_histogram his;
       if(his.init(SN)){
          his.his(nbox,false);
          his.compute();
          his.print();
          his.printall();
          string name=f_remove_ext(_file.file_name())+"_"+to_string(ns)+".dat";
          his.save(name);
       }
       string name2=f_remove_ext(_file.file_name())+"_"+to_string(ns)+"_input.dat";
       ofstream fo{name2};
       fo<<"No SN f A  SNo"<<endl;
       for(size_t i=0;i<ns;++i){
          fo<<i<<" "<<SN[i]<<" "<<SNfr[i]<<" "<<SNAmpl[i]<<" "<<SNsn[i]<< endl;
       }
       //simstatMW->setWindowModality(Qt::NonModal);
       QString result="SN done";

       string line_out="Mean="+to_string(his.mean());

       //label_info_fitting->setText(label_info_fitting2->text());
       string text;
       text="<font color="+NLSF_info_color_font.toStdString()+">Mean="+to_string(his.mean());;
       text+=" D*="+to_string(his.D());
       text+=" q(0.5)="+to_string(his.cquantile(0.5));
       text+=" q(0.99)="+to_string(his.cquantile(0.99));
       text+=" q(0.999)="+to_string(his.cquantile(0.999));
       text+=" q(0.9999)="+to_string(his.cquantile(0.9999));

       //label_info_fitting2->setText(text.c_str());
       simulation_label->setText(text.c_str());

       double dx=his.dx()*0.9;
       if(dx==0)dx=1;
       simulation_bar->setWidth(dx);
       size_t nn=his.x().size();
       QVector<double>qx(nn),qy(nn);
       for(size_t ii=0;ii<his.x().size();++ii){
           qx[ii]=his.x()[ii];
           qy[ii]=his.N()[ii];
       }

       simulation_bar->setData(qx,qy,true);
       simulation_bar->setSelectable(QCP::stMultipleDataRanges);
       customPlot_simulation->rescaleAxes();
       customPlot_simulation->replot();
   }
}



/*
void MainWindow::pushB_start_simulation_slot(){
    if(_dialog_simulation_ok){
        //simstatMW->setWindowModality(Qt::ApplicationModal);

        bool replot_ok=true;
        if(radioB_plot_interactively_no->isChecked()){
            replot_ok=false;
        }

        //dialog_simulation->hide();
        //cout<<"Simulation on"<<endl;
        int ns=spinbox_simulationNO->value();
        //cout<<"Simulation number = "<<ns<<endl;
        random_device rd;
        //default_random_engine generator{100};
        double sigma = spinbox_simulation_sigma->value();
        normal_distribution<double> distribution(0,sigma);
        vector<double>x=f_get_column(_file.file(),_file.head(),"1");
        //vector<double>y=f_get_column(_file.file(),_file.head(),"2");
        //vector<double>e_y=f_get_column(_file.file(),_file.head(),"3");
        size_t n=x.size();

        vector<double> weighs(n);
        vector<double> ampl_noise(n);
        QVector<double>qx(n),qy(n),qerr(n);
        for(size_t i=0;i<n;++i){
             weighs[i]=1.0;
             qx[i]=x[i];
             qerr[i]=weighs[i];
        }
        vector<double>SN(ns);
        vector<double>SNfr(ns);
        vector<double>SNAmpl(ns);
        vector<double>SNsn(ns);

        for(size_t is=0;is<ns;++is){
            if(replot_ok){
               pushB_open_simulation_dialog->setText( ("("+to_string(is)+"/"+to_string(ns)+")").c_str() );
            }else{
                simstatMW->activateWindow();
               pushB_start_simulation->setText( ("("+to_string(is)+"/"+to_string(ns)+")").c_str() );
               simstatMW->setWindowTitle(("("+to_string(is)+"/"+to_string(ns)+")").c_str() );
            }
            for(size_t i=0;i<n;++i){
                 ampl_noise[i]=distribution(rd);
                 qy[i]=ampl_noise[i];
            }
            if(replot_ok){
              if(_ind_graph_lc!=-1){
                customPlotLc->graph(_ind_graph_lc)->setData(qx,qy);
                ErrorBars->setData(qerr);
                if(_ind_graph_lc_detrend_points!=-1){
                     customPlotLc->removeGraph(_ind_graph_lc_detrend_inter);
                     customPlotLc->removeGraph(_ind_graph_lc_detrend_points);
                     _noise_ok=false;
                     _ind_graph_lc_detrend_inter=-1;
                     _ind_graph_lc_detrend_points=-1;
                }
                //calculate_trend();
                if(is==0){
                    customPlotLc->rescaleAxes();
                }
                customPlotLc->replot();
              }
            }
            FWPeaks fwpeaks;
            fwpeaks.fourier(x,ampl_noise,weighs,_f0,_fe,_df);
            _trf_ok=true;
            _fr=fwpeaks.fr();
            _ampl=fwpeaks.ampl();
            _frpeaks=fwpeaks.frpeaks();
            _amplpeaks=fwpeaks.amplpeaks();
            _Ppeaks=fwpeaks.Ppeaks();
            _SNpeaks=fwpeaks.SNpeaks();
            _xmin=f_min(_fr);
            _xmax=f_max(_fr);
            _ymin=f_min(_ampl);
            _ymax=f_max(_ampl);
            if(replot_ok){
               plot_trf();
            }
            calculate_noise();

            if(replot_ok){
               plot_noise();
            }
            SN[is]=_amplpeaks[0]/spline_noise.e(_frpeaks[0]);
            SNfr[is]=_frpeaks[0];
            SNAmpl[is]=_amplpeaks[0];
            SNsn[is]=_SNpeaks[0];
            cout<<is<<" f="<<_frpeaks[0]<<" a="<<_amplpeaks[0]<<" "<<spline_noise.e(_frpeaks[0])<<" S/N="<<SN[is]<<endl;

        }
        if(replot_ok){
           pushB_open_simulation_dialog->setText("simulation");
        }else{
           pushB_start_simulation->setText("start simulation");
        }
        cl_histogram his;

        int nbox=10;
        his.init(SN);
        his.his(nbox,false);
        his.compute();
        his.print();
        his.printall();
        string name=f_remove_ext(_file.file_name())+"_"+to_string(ns)+".dat";
        his.save(name);
        if(replot_ok){
           plot_lc();
        }else{
            _trf_ok=false;
            _noise_ok=false;
            _noise.clear();
        }

        string name2=f_remove_ext(_file.file_name())+"_"+to_string(ns)+"_input.dat";

        ofstream fo{name2};
        fo<<"No SN f A  SNo"<<endl;
        for(size_t i=0;i<ns;++i){
            fo<<i<<" "<<SN[i]<<" "<<SNfr[i]<<" "<<SNAmpl[i]<<" "<<SNsn[i]<< endl;
        }
        //simstatMW->setWindowModality(Qt::NonModal);
    }
}
*/


void MainWindow::spinbox_comb_res_valueChanged(double d){
    double val=spinBox_resolution_for_combination->value()*_dT;
    ostringstream o;
    o<<setprecision(3)<<val;

    label_resolution_for_combination->setText( ( "<font color="+basic_color_font.toStdString()+">comb. res ("+o.str()+"[1/DT])").c_str());
}

void  MainWindow::pushB_fitsin_function(){
      fitsin_function();
}


void  MainWindow::fitsin_function(){

      if(table->rowCount()>0){
         pushB_fitsin->setDisabled(true);
         pushB_fitsin_only_nonlin->setDisabled(true);
         info_table->horizontalHeader()->setDisabled(true);
         pushB_auto->setDisabled(true);
         pushB_fitsin_only_lin->setDisabled(true);
      }


      //fitsin_linear();

      fitsin_linear_thread_init();

      //get_residuals();


      //fitsin_nonlinear_thread_init();


/*
      get_residuals();

      update_sn();

      check_for_combination();
      */

}

void  MainWindow::update_sn(){
    if(_noise_ok){
       int ind_sn=-1;
       int ind_A=-1;
       int ind_freq=-1;
       for(auto i=0;i<table->columnCount();++i){
          if(table->horizontalHeaderItem(i)->text()=="S/N"){
              ind_sn=i;
          }
          if(table->horizontalHeaderItem(i)->text()=="A"){
              ind_A=i;
          }
          if(table->horizontalHeaderItem(i)->text()=="freq"){
              ind_freq=i;
          }
       }
       if(ind_sn!=-1 && ind_A!=-1){
            if(table->item(table->rowCount()-1,ind_sn)!=nullptr){
                   //cout<<"S/N found "<<endl;
                   double ampl=table->item(table->rowCount()-1,ind_A)->text().toDouble();
                   double freq=table->item(table->rowCount()-1,ind_freq)->text().toDouble();
                   double sn=ampl/spline_noise.e(freq);
                   table->item(table->rowCount()-1,ind_sn)->setText(to_string(sn).c_str());
            }
       }
    }
}


void  MainWindow::fitsin_linear(){
    //cout<<"fitsin_linear"<<endl;
    //cout<<_freq_matrix<<endl;

    if(table->rowCount()>0){

       vector<double>freq_i;
       vector<double>freq_all;
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
       //cout<<"ind_status="<<ind_status<<" ind_freq="<<ind_freq<<endl;
       if(ind_status!=-1 && ind_freq!=-1){
           for(int i=0;i<table->rowCount();++i){
               if(table->item(i,ind_status)!=nullptr){
                   if(table->item(i,ind_status)->text()=="" || table->item(i,ind_status)->text()=="i"){
                       freq_i.push_back(table->item(i,ind_freq)->text().toDouble());
                   }
               }
               freq_all.push_back(table->item(i,ind_freq)->text().toDouble());
           }
       }
       //cout<<"fitsin_linear: freq_i="<<freq_i<<" ---"<<freq_i.size()<<endl;
       //cout<<"fitsin_linear: freq_all="<<freq_all<<" ---"<<freq_all.size()<<endl;




       int nfreq=freq_all.size();
       int n=_file.file().size();

       _A_lin.clear();
       _phi_lin.clear();
       _sA_lin.clear();
       _sphi_lin.clear();

           vector<double>a,sa;

           double chisq;
           gsl_matrix *XX,*cov;
           gsl_vector *YY,*WW,*c;
           //cout<<"ncoef="<< ncoef<<endl;
           int ncoef=1+nfreq*2;
           XX=gsl_matrix_alloc(n,ncoef);
           YY=gsl_vector_alloc(n);
           WW=gsl_vector_alloc(n);
           c=gsl_vector_alloc(ncoef);
           cov=gsl_matrix_alloc(ncoef,ncoef);
           int l=0;
           for(int i=0;i<n;i++){
              gsl_matrix_set(XX,i,0,1);
              for(int j=0;j<nfreq;++j){
                 //cout<<x[k][i]<<" i="<<i<<" j="<<j<<" ll="<<ll<<endl;
                   gsl_matrix_set(XX,i,j+1,sin(_file.file()[i][0]*2*M_PI*freq_all[j]));
              }
              for(int j=0;j<nfreq;++j){
                 //cout<<x[k][i]<<" i="<<i<<" j="<<j<<" ll="<<ll<<endl;
                   gsl_matrix_set(XX,i,1+nfreq+j,cos(_file.file()[i][0]*2*M_PI*freq_all[j]));
              }
              gsl_vector_set(YY,i,_file.file()[i][1]);
              gsl_vector_set(WW,i,1.0/pow(_file.file()[i][2],2));

           }
           gsl_multifit_linear_workspace *work=gsl_multifit_linear_alloc(n,ncoef);
           gsl_multifit_wlinear(XX,WW,YY,c,cov,&chisq,work);

           #define C(i)(gsl_vector_get(c,(i)))
           //cout<<C(0)<<" "<<C(1)<<" "<<C(2)<<" "<<C(3)<<" "<<C(4)<<endl;

           for(int i=0;i<ncoef;i++){
               a.push_back(C(i));
               sa.push_back(sqrt(chisq*gsl_matrix_get(cov,i,i)/(double(n-ncoef))));
               //cout<<chisq<<" n="<<n<<" order="<<order<<" "<<gsl_matrix_get(cov,i,i)<<" "<<(double(n-ncoef))<<endl;
           }
           //cout<<"n="<<n<<endl;
           //cout<<"a="<<a<<endl;
           //cout<<"sa="<<sa<<endl;

           gsl_matrix_free (XX);
           gsl_vector_free (YY);
           gsl_vector_free (WW);
           gsl_vector_free (c);
           gsl_matrix_free (cov);
           gsl_multifit_linear_free(work);

           for(int i=0;i<nfreq;i++){
              _A_lin.push_back(sqrt(pow(a[1+i],2.0)+pow(a[1+i+nfreq],2.0)));
              _sA_lin.push_back(1.0/_A_lin.back()*(sqrt(pow(a[1+i]*sa[1+i],2)+pow(a[1+nfreq+i]*sa[1+nfreq+i],2))));
              double phi=atan2(a[1+i+nfreq],a[1+i]);
              if(phi<0){
                  while(phi<0){
                      phi+=2*M_PI;
                  }
              }
              //_phi_lin.push_back(atan2(a[1+i+nfreq],a[1+i]));
              _phi_lin.push_back(phi);
              _sphi_lin.push_back( sqrt(pow(a[1+nfreq+i]*sa[1+i]/(a[1+i]*a[1+i]),2) + pow(sa[1+nfreq+i]/a[1+i],2) )/(1+(pow(a[1+nfreq+i]/a[1+i],2))) );

              //phi.push_back(atan(s[i+nfreq]/s[i]));
           }
           _A0_lin=a[0];
           _sA0_lin=sa[0];
           _A0=_A0_lin;


           if(ind_A!=-1 && ind_sA!=-1 && ind_phi && ind_sphi){
               for(int i=0;i<table->rowCount();++i){
                   if(table->item(i,ind_A)!=nullptr){
                       table->item(i,ind_A)->setText( to_string(_A_lin[i]).c_str());
                   }
                   if(table->item(i,ind_sA)!=nullptr){
                       table->item(i,ind_sA)->setText( to_string(_sA_lin[i]).c_str());
                   }
                   if(table->item(i,ind_phi)!=nullptr){
                       table->item(i,ind_phi)->setText( to_string(_phi_lin[i]).c_str());
                   }
                   if(table->item(i,ind_sphi)!=nullptr){
                       table->item(i,ind_sphi)->setText( to_string(_sphi_lin[i]).c_str());
                   }
               }
           }




    }
}


void  MainWindow::fitsin_linear_thread(){
    //cout<<"fitsin_linear"<<endl;
    //cout<<_freq_matrix<<endl;

    if(table->rowCount()>0){

       vector<double>freq_i;
       vector<double>freq_all;
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
       //cout<<"ind_status="<<ind_status<<" ind_freq="<<ind_freq<<endl;
       if(ind_status!=-1 && ind_freq!=-1){
           for(int i=0;i<table->rowCount();++i){
               if(table->item(i,ind_status)!=nullptr){
                   if(table->item(i,ind_status)->text()=="" || table->item(i,ind_status)->text()=="i"){
                       freq_i.push_back(table->item(i,ind_freq)->text().toDouble());
                   }
               }
               freq_all.push_back(table->item(i,ind_freq)->text().toDouble());
           }
       }
       //cout<<"fitsin_linear: freq_i="<<freq_i<<" ---"<<freq_i.size()<<endl;
       //cout<<"fitsin_linear: freq_all="<<freq_all<<" ---"<<freq_all.size()<<endl;


       Worker_linear *worker = new Worker_linear();
       worker->freq_i=freq_i;
       worker->freq_all=freq_all;
       worker->_file=&_file;
       worker->_A_lin=_A_lin;
       worker->_phi_lin=_phi_lin;
       worker->_T0=_T0;


       qRegisterMetaType<Worker_data_out_linear>("Worker_data_out_linear");

       worker->moveToThread(&workerThread_linear);
       //worker->moveToThread(thread);
               connect(&workerThread_linear, &QThread::finished, worker, &QObject::deleteLater);
               //connect(&workerThread, &QThread::started, worker, &Worker::doWork);
               connect(this, &MainWindow::operate_linear, worker, &Worker_linear::doWork);
       //        connect(this, &MainWindow::start, worker, &Worker::doWork);
               connect(worker, &Worker_linear::resultReady_linear, this, &MainWindow::handleResults_linear);
               workerThread_linear.start();







    }
}

void  Worker_linear::doWork(const QString &parameter){
    cout<<"doWork linear"<<endl;

    Worker_data_out_linear results;

    int nfreq=freq_all.size();
    int n=_file->file().size();

    vector<double> _A_lin;
    vector<double> _phi_lin;
    vector<double> _sA_lin;
    vector<double> _sphi_lin;

        vector<double>a,sa;

        double chisq;
        gsl_matrix *XX,*cov;
        gsl_vector *YY,*WW,*c;
        //cout<<"ncoef="<< ncoef<<endl;
        int ncoef=1+nfreq*2;
        XX=gsl_matrix_alloc(n,ncoef);
        YY=gsl_vector_alloc(n);
        WW=gsl_vector_alloc(n);
        c=gsl_vector_alloc(ncoef);
        cov=gsl_matrix_alloc(ncoef,ncoef);
        int l=0;
        for(int i=0;i<n;i++){
           gsl_matrix_set(XX,i,0,1);
           for(int j=0;j<nfreq;++j){
              //cout<<x[k][i]<<" i="<<i<<" j="<<j<<" ll="<<ll<<endl;
                gsl_matrix_set(XX,i,j+1,sin((_file->file()[i][0]-_T0)*2*M_PI*freq_all[j]));
           }
           for(int j=0;j<nfreq;++j){
              //cout<<x[k][i]<<" i="<<i<<" j="<<j<<" ll="<<ll<<endl;
                gsl_matrix_set(XX,i,1+nfreq+j,cos((_file->file()[i][0]-_T0)*2*M_PI*freq_all[j]));
           }
           gsl_vector_set(YY,i,_file->file()[i][1]);
           gsl_vector_set(WW,i,1.0/pow(_file->file()[i][2],2));

        }
        gsl_multifit_linear_workspace *work=gsl_multifit_linear_alloc(n,ncoef);
        gsl_multifit_wlinear(XX,WW,YY,c,cov,&chisq,work);

        #define C(i)(gsl_vector_get(c,(i)))
        //cout<<C(0)<<" "<<C(1)<<" "<<C(2)<<" "<<C(3)<<" "<<C(4)<<endl;

        for(int i=0;i<ncoef;i++){
            a.push_back(C(i));
            sa.push_back(sqrt(chisq*gsl_matrix_get(cov,i,i)/(double(n-ncoef))));
            //cout<<chisq<<" n="<<n<<" order="<<order<<" "<<gsl_matrix_get(cov,i,i)<<" "<<(double(n-ncoef))<<endl;
        }
        //cout<<"n="<<n<<endl;
        //cout<<"a="<<a<<endl;
        //cout<<"sa="<<sa<<endl;

        gsl_matrix_free (XX);
        gsl_vector_free (YY);
        gsl_vector_free (WW);
        gsl_vector_free (c);
        gsl_matrix_free (cov);
        gsl_multifit_linear_free(work);

        for(int i=0;i<nfreq;i++){
           _A_lin.push_back(sqrt(pow(a[1+i],2.0)+pow(a[1+i+nfreq],2.0)));
           _sA_lin.push_back(1.0/_A_lin.back()*(sqrt(pow(a[1+i]*sa[1+i],2)+pow(a[1+nfreq+i]*sa[1+nfreq+i],2))));
           double phi=atan2(a[1+i+nfreq],a[1+i]);
           if(phi<0){
               while(phi<0){
                   phi+=2*M_PI;
               }
           }
           //_phi_lin.push_back(atan2(a[1+i+nfreq],a[1+i]));
           _phi_lin.push_back(phi);
           _sphi_lin.push_back( sqrt(pow(a[1+nfreq+i]*sa[1+i]/(a[1+i]*a[1+i]),2) + pow(sa[1+nfreq+i]/a[1+i],2) )/(1+(pow(a[1+nfreq+i]/a[1+i],2))) );

           //phi.push_back(atan(s[i+nfreq]/s[i]));
        }

        double _A0_lin=a[0];
        double _sA0_lin=sa[0];


        results._A0_lin=_A0_lin;
        results._sA0_lin=_sA0_lin;
        results._A_lin=_A_lin;
        results._sA_lin=_sA_lin;
        results._phi_lin=_phi_lin;
        results._sphi_lin=_sphi_lin;
        results.chisqrt=sqrt(chisq/(double(n-ncoef)));

        emit resultReady_linear(results);

}


void MainWindow::fitsin_only_linear_thread_init(){
    if(table->rowCount()>0){
       pushB_fitsin->setDisabled(true);
       pushB_fitsin_only_nonlin->setDisabled(true);
       info_table->horizontalHeader()->setDisabled(true);
       pushB_auto->setDisabled(true);
       pushB_fitsin_only_lin->setDisabled(true);
    }
    _fit_linear_only=true;
    _time_start_linear_thread=time(NULL);
    fitsin_linear_thread();
    emit(operate_linear("start"));

}

void MainWindow::fitsin_linear_thread_init(){
    if(table->rowCount()>0){
       pushB_fitsin->setDisabled(true);
       pushB_fitsin_only_nonlin->setDisabled(true);
       info_table->horizontalHeader()->setDisabled(true);
       pushB_auto->setDisabled(true);
       pushB_fitsin_only_lin->setDisabled(true);
    }
    _time_start_linear_thread=time(NULL);
    fitsin_linear_thread();
    emit(operate_linear("start"));
}

void MainWindow::handleResults_linear(const Worker_data_out_linear results){
    cout<<"linear thread done"<<endl;


    int ind_A=-1;
    int ind_sA=-1;
    int ind_phi=-1;
    int ind_sphi=-1;
    vector<bool> ind_ind;
    for(auto i=0;i<table->columnCount();++i){
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


    _A0_lin=results._A0_lin;
    _sA0_lin=results._sA0_lin;

    _A0=results._A0_lin;
    _sA0=results._sA0_lin;

    int rowmax=table->rowCount();
    int p0=results.p0;
    rowmax=rowmax-p0;

    if(ind_A!=-1 && ind_sA!=-1 && ind_phi && ind_sphi){
        for(int i=0;i<rowmax;++i){
            if(table->item(i+p0,ind_A)!=nullptr){
                table->item(i+p0,ind_A)->setText( to_string_pw(results._A_lin[i],8).c_str());
            }
            if(table->item(i+p0,ind_sA)!=nullptr){
                table->item(i+p0,ind_sA)->setText( to_string_pw(results._sA_lin[i],8).c_str());
            }

            if(table->item(i+p0,ind_phi)!=nullptr){
                table->item(i+p0,ind_phi)->setText( to_string_pw(results._phi_lin[i],8).c_str());
            }
            if(table->item(i+p0,ind_sphi)!=nullptr){
                table->item(i+p0,ind_sphi)->setText( to_string_pw(results._sphi_lin[i],8).c_str());
            }
        }
        table->resizeColumnsToContents();
    }//

    //cout<<"A0="<<_A0<<endl;
    //cout<<"sA0="<<_sA0<<endl;

    workerThread_linear.quit();
    workerThread_linear.wait();

   // workerThread.deleteLater();

    pushB_fitsin->setDisabled(false);
    pushB_fitsin_only_nonlin->setDisabled(false);
    pushB_fitsin_only_lin->setDisabled(true);
    pushB_auto->setDisabled(false);


    //get_residuals();

    //update_sn();

    //check_for_combination();

    _time_stop_linear_thread=time(NULL);
    cout<<"time = "<<f_time(_time_stop_linear_thread-_time_start_linear_thread)<<endl;


    label_info_fitting->setText(label_info_fitting2->text());
    string text;
    text="<font color="+NLSF_info_color_font.toStdString()+">   linear: chisq="+to_string(results.chisqrt);
    text+=", time = "+f_time(_time_stop_linear_thread-_time_start_linear_thread);
    label_info_fitting2->setText(text.c_str());

    get_residuals();


    if(!_fit_linear_only){
       fitsin_nonlinear_thread_init();
    }else{
       _fit_linear_only=false;
       pushB_fitsin_only_lin->setDisabled(false);
    }



}



struct params{
    int p;
    int n;
};

struct data {
  size_t n;
  gsl_vector *t;
  gsl_vector *y;
  vector<double>freq_i;
  vector<double>freq_all;
  vector<bool> ind_ind;
  vector<vector<double> > matrix;
  double _T0;
  int p;
};

int expb_f (const gsl_vector * x, void *data, gsl_vector * f){
  size_t n = ((struct data *)data)->n;
  gsl_vector *t = ((struct data *)data)->t;
  gsl_vector *y= ((struct data *)data)->y;
  vector<bool> ind_ind = ((struct data *)data)->ind_ind;
  vector<vector<double> > matrix = ((struct data *)data)->matrix;

  size_t i;

  for (i = 0; i < n; i++){
      /* Model Yi = A * exp(-lambda * t_i) + b */
      //double Yi = A * exp (-lambda * gsl_vector_get(t,i)) + b;
      double Yi=gsl_vector_get (x,0);

      //cout<<gsl_vector_get(x,0)<<" ";
      int ind=1;
      vector<int>ind_freq_ind;
      int iter=1;
      for(size_t j=0;j<ind_ind.size();++j){
          //cout<<"j="<<j<<endl;
          //cout<<gsl_vector_get(x,ind)<<" "<<gsl_vector_get(x,ind+1)<<" "<<gsl_vector_get(x,ind+2)<<endl;
          if(ind_ind[j]){
             Yi+=gsl_vector_get(x,ind+1)*sin(2*M_PI*gsl_vector_get(x,ind)*gsl_vector_get(t,i)+gsl_vector_get(x,ind+2));
             ind_freq_ind.push_back(ind);
             ind+=3;
             ++iter;
          }else{
              double freq=0;
              for(size_t k=0;k<matrix[j].size();++k){
                  //cout<<"k="<<k<<" "<<matrix[j][k]<<" "<<gsl_vector_get(x,ind_freq_ind[k])<<" ind_freq_ind[k]="<<ind_freq_ind[k]<<endl;
                  freq+=matrix[j][k]*gsl_vector_get(x,ind_freq_ind[k]);//
              }
              //cout<<"freq in f ="<<freq<<endl;
              Yi+=gsl_vector_get(x,ind)*sin(2*M_PI*freq*gsl_vector_get(t,i)+gsl_vector_get(x,ind+1));
              ind+=2;
           }
      }
      gsl_vector_set (f, i, Yi - gsl_vector_get(y,i));
    }

  return GSL_SUCCESS;
}


int sinsum (const gsl_vector * x, void *data, gsl_vector * f){
  size_t n = ((struct data *)data)->n;
  gsl_vector *t = ((struct data *)data)->t;
  gsl_vector *y= ((struct data *)data)->y;
  vector<bool> ind_ind = ((struct data *)data)->ind_ind;
  vector<vector<double> > matrix = ((struct data *)data)->matrix;
  double _T0= ((struct data *)data)->_T0;
  int p=((struct data *)data)->p;

  size_t i;

  //cout<<"sinsum begin"<<endl;

  for (i = 0; i < n; i++){
      /* Model Yi = A0+Asin(2pift+phi) */
      //double Yi = A * exp (-lambda * gsl_vector_get(t,i)) + b;
      double Yi=gsl_vector_get (x,0);

      int ind=1;
      vector<int>ind_freq_ind;
      int iter=1;
      for(size_t j=0;j<ind_ind.size();++j){
          //cout<<"j="<<j<<endl;
          //cout<<gsl_vector_get(x,ind)<<" "<<gsl_vector_get(x,ind+1)<<" "<<gsl_vector_get(x,ind+2)<<endl;
          if(ind_ind[j]){
             Yi+=gsl_vector_get(x,ind+1)*sin(2*M_PI*gsl_vector_get(x,ind)*(gsl_vector_get(t,i)-_T0));//+gsl_vector_get(x,ind+2));
             Yi+=gsl_vector_get(x,ind+2)*cos(2*M_PI*gsl_vector_get(x,ind)*(gsl_vector_get(t,i)-_T0));
             ind_freq_ind.push_back(ind);
             ind+=3;
             ++iter;
          }else{
              //cout<<"dependent"<<endl;
              double freq=0;              
              for(size_t k=0;k<matrix[j].size();++k){
                  //if(ind_freq_ind[k]>=p){
                  //   cout<<"problem"<<p<<" ind_freq_ind[k]="<<ind_freq_ind[k]<<" all="<<ind_freq_ind<<endl;
                  //}
                  //cout<<"k="<<k<<" "<<matrix[j][k]<<" "<<gsl_vector_get(x,ind_freq_ind[k])<<" ind_freq_ind[k]="<<ind_freq_ind[k]<<endl;
                  if(matrix[j][k]!=0){
                     freq+=matrix[j][k]*gsl_vector_get(x,ind_freq_ind[k]);//
                  }
              }
              //cout<<"freq in f ="<<freq<<endl;
              Yi+=gsl_vector_get(x,ind)*sin(2*M_PI*freq*(gsl_vector_get(t,i)-_T0));//+gsl_vector_get(x,ind+1));
              Yi+=gsl_vector_get(x,ind+1)*cos(2*M_PI*freq*(gsl_vector_get(t,i)-_T0));//+gsl_vector_get(x,ind+1));
              ind+=2;
           }
      }
      gsl_vector_set (f, i, Yi - gsl_vector_get(y,i));
    }
    //cout<<"sinsum done"<<endl;
    return GSL_SUCCESS;
}
int sinsum_df (const gsl_vector * x, void *data, gsl_matrix * J){
    size_t n = ((struct data *)data)->n;
    gsl_vector *t = ((struct data *)data)->t;
    gsl_vector *y= ((struct data *)data)->y;
    vector<bool> ind_ind = ((struct data *)data)->ind_ind;
    vector<vector<double> > matrix = ((struct data *)data)->matrix;
    double _T0= ((struct data *)data)->_T0;

    size_t i;

    //cout<<"sinsum_df begin"<<endl;
    //cout<<"matrix"<<endl;
    //cout<<matrix<<endl;
    //cout<<"ind_ind="<<ind_ind<<endl;

    for (i = 0; i < n; i++){

        gsl_matrix_set (J, i, 0, 1.0);
        int ind=1;
        vector<int>ind_freq_ind;
        int iter=1;
        for(size_t j=0;j<ind_ind.size();++j){
            //cout<<"j="<<j<<endl;
            if(ind_ind[j]){
               gsl_matrix_set (J, i, ind,gsl_vector_get(x,ind+1)*cos(2*M_PI*gsl_vector_get(x,ind)*(gsl_vector_get(t,i)-_T0))*2*M_PI*(gsl_vector_get(t,i)-_T0)-
                                         gsl_vector_get(x,ind+2)*sin(2*M_PI*gsl_vector_get(x,ind)*(gsl_vector_get(t,i)-_T0))*2*M_PI*(gsl_vector_get(t,i)-_T0));
               gsl_matrix_set (J, i, ind+1,sin(2*M_PI*gsl_vector_get(x,ind)*(gsl_vector_get(t,i)-_T0)));
               gsl_matrix_set (J, i, ind+2,cos(2*M_PI*gsl_vector_get(x,ind)*(gsl_vector_get(t,i)-_T0)));
               ind_freq_ind.push_back(ind);
               ind+=3;
               ++iter;
            }else{
                double freq=0;
                //if(i<2)cout<<"matrix[j].size()="<<matrix[j].size()<<endl;
                for(size_t k=0;k<matrix[j].size();++k){
                    if(matrix[j][k]!=0){
                       //cout<<"k="<<k<<" "<<matrix[j][k]<<" "<<" ind_freq_ind[k]="<<ind_freq_ind[k]<<endl;
                       freq+=matrix[j][k]*gsl_vector_get(x,ind_freq_ind[k]);//
                    }
                }
                //if(i<2)cout<<"J: freq in f ="<<freq<<endl;
                gsl_matrix_set (J, i, ind,sin(2*M_PI*freq*(gsl_vector_get(t,i)-_T0)));
                gsl_matrix_set (J, i, ind+1,cos(2*M_PI*freq*(gsl_vector_get(t,i)-_T0)));
                ind+=2;
             }
        }
      }

     //cout<<"J done"<<endl;

  return GSL_SUCCESS;
}


int expb_df (const gsl_vector * x, void *data, gsl_matrix * J){
    size_t n = ((struct data *)data)->n;
    gsl_vector *t = ((struct data *)data)->t;
    gsl_vector *y= ((struct data *)data)->y;
    vector<bool> ind_ind = ((struct data *)data)->ind_ind;
    vector<vector<double> > matrix = ((struct data *)data)->matrix;
    double _T0= ((struct data *)data)->_T0;

    size_t i;

    for (i = 0; i < n; i++){

        gsl_matrix_set (J, i, 0, 1.0);
        int ind=1;
        vector<int>ind_freq_ind;
        int iter=1;
        for(size_t j=0;j<ind_ind.size();++j){
            //cout<<"j="<<j<<endl;
            if(ind_ind[j]){
               gsl_matrix_set (J, i, ind,gsl_vector_get(x,ind+1)*cos(2*M_PI*gsl_vector_get(x,ind)*(gsl_vector_get(t,i)-_T0)+gsl_vector_get(x,ind+2))*2*M_PI*(gsl_vector_get(t,i)-_T0));
               gsl_matrix_set (J, i, ind+1,sin(2*M_PI*gsl_vector_get(x,ind)*(gsl_vector_get(t,i)-_T0)+gsl_vector_get(x,ind+2)));
               gsl_matrix_set (J, i, ind+2,gsl_vector_get(x,ind+1)*cos(2*M_PI*gsl_vector_get(x,ind)*(gsl_vector_get(t,i)-_T0)+gsl_vector_get(x,ind+2)));
               ind_freq_ind.push_back(ind);
               ind+=3;
               ++iter;
            }else{
                double freq=0;
                for(size_t k=0;k<matrix[j].size();++k){
                    //cout<<"k="<<k<<" "<<matrix[j][k]<<" "<<gsl_vector_get(x,ind_freq_ind[k])<<" ind_freq_ind[k]="<<ind_freq_ind[k]<<endl;
                    freq+=matrix[j][k]*gsl_vector_get(x,ind_freq_ind[k]);//
                }
                //cout<<"J: freq in f ="<<freq<<endl;
                gsl_matrix_set (J, i, ind,sin(2*M_PI*freq*(gsl_vector_get(t,i)-_T0)+gsl_vector_get(x,ind+1)));
                gsl_matrix_set (J, i, ind+1,gsl_vector_get(x,ind)*cos(2*M_PI*freq*(gsl_vector_get(t,i)-_T0)+gsl_vector_get(x,ind+1)));

                ind+=2;
             }
        }
      }



  return GSL_SUCCESS;
}


void callback(const size_t iter, void *params, const gsl_multifit_nlinear_workspace *w){
  gsl_vector *f = gsl_multifit_nlinear_residual(w);
  gsl_vector *x = gsl_multifit_nlinear_position(w);
  gsl_vector *dx = w->dx;
  gsl_matrix *J = w->J;
  double rcond;

  size_t p = ((struct params *)params)->p;
  size_t n = ((struct params *)params)->n;
  //cout<<"ppp="<<p<<endl;

  /* compute reciprocal condition number of J(x) */
  gsl_multifit_nlinear_rcond(&rcond, w);


  //fprintf(stderr, "iter %2zu: A0 = %.4f, freq = %.4f, A= %.4f, phi = %.4f, A= %.4f, phi = %.4f, cond(J) = %8.4f, |f(x)| = %.4f\n",
    //      iter,
      //    fprintf(stderr, "iter %2zu: cond(J) = %8.4f, |f(x)| = %.4f\n",
      //            iter,
          //gsl_vector_get(x, 0),
          //gsl_vector_get(x, 1),
          //gsl_vector_get(x, 2),
          //gsl_vector_get(x, 3),
          //gsl_vector_get(x, 4),
          //gsl_vector_get(x, 5),
      //    1.0 / rcond,
      //    gsl_blas_dnrm2(f));//*/


  fprintf(stderr, "iter %2zu: cond(J) = %8.4f, |f(x)| = %.4f\n",
          iter,
          1.0 / rcond,
          gsl_blas_dnrm2(f));


  cout<<"x: ";
  for(size_t i=0;i<p;++i){
      cout<<gsl_vector_get(x, i)<<" ";
  }
  cout<<endl;
    //
  //for(size_t i=0;i<p;++i){
  //    cout<<gsl_vector_get(f, i)<<" ";
  //}

  cout<<"dx: ";
  for(size_t i=0;i<p;++i){
      cout<<gsl_vector_get(dx, i)<<" ";
  }
  cout<<endl;

  /*
  ofstream fo{"test_anal_"+to_string(iter)+".dat"};
  for(size_t i=0;i<n;++i){
   for(size_t j=0;j<p;++j){
      fo<<gsl_matrix_get(J, i,j)<<" ";
   }
   fo<<endl;
  }
  cout<<endl;
  //*/
}


void  MainWindow::fitsin_nonlinear(){
    cout<<"fitsin_nonlinear"<<endl;
    cout<<_freq_matrix<<endl;

    if(table->rowCount()>0){

       vector<double>freq_i;
       vector<double>freq_all;
       vector<double>freq_c;
       int ind_freq=-1;
       int ind_sfreq=-1;
       int ind_status=-1;
       int ind_A=-1;
       int ind_sA=-1;
       int ind_phi=-1;
       int ind_sphi=-1;
       vector<bool> ind_ind;
       for(auto i=0;i<table->columnCount();++i){
           if(table->horizontalHeaderItem(i)->text()=="status"){
               ind_status=i;
           }
           if(table->horizontalHeaderItem(i)->text()=="freq"){
               ind_freq=i;
           }
           if(table->horizontalHeaderItem(i)->text()=="e_freq"){
               ind_sfreq=i;
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
       cout<<"ind_status="<<ind_status<<" ind_freq="<<ind_freq<<endl;
       if(ind_status!=-1 && ind_freq!=-1){
           for(int i=0;i<table->rowCount();++i){
               if(table->item(i,ind_status)!=nullptr){
                   if(table->item(i,ind_status)->text()=="" || table->item(i,ind_status)->text()=="i"){
                       freq_i.push_back(table->item(i,ind_freq)->text().toDouble());
                       ind_ind.push_back(true);
                   }else{
                       freq_c.push_back(table->item(i,ind_freq)->text().toDouble());
                       ind_ind.push_back(false);
                   }
               }
               freq_all.push_back(table->item(i,ind_freq)->text().toDouble());
           }
       }
       cout<<"freq_i="<<freq_i<<" --- "<<freq_i.size()<<endl;
       cout<<"freq_c="<<freq_c<<" --- "<<freq_c.size()<<endl;
       cout<<"freq_all="<<freq_all<<" --- "<<freq_all.size()<<endl;



       int nfreq=freq_all.size();
       size_t n=_file.file().size();

       _f.clear();
       _sf.clear();
       _A.clear();
       _phi.clear();
       _sA.clear();
       _sphi.clear();

       int p=freq_i.size()*3+freq_c.size()*2+1;


       //cout<<"parameters number="<<p<<endl;

       const gsl_multifit_nlinear_type *T = gsl_multifit_nlinear_trust;
       gsl_multifit_nlinear_workspace *w;
       gsl_multifit_nlinear_fdf fdf;
       gsl_multifit_nlinear_parameters fdf_params = gsl_multifit_nlinear_default_parameters();
       //if(_NLSF_solver="cholesky";)
       if(!_combo_settings_action_NLSF_dialog_init){
          fdf_params.solver=gsl_multifit_nlinear_solver_mcholesky;
       }else{
           if(radio_NLSF_1->isChecked()){
               fdf_params.solver=gsl_multifit_nlinear_solver_mcholesky;
           }
           if(radio_NLSF_2->isChecked()){
               fdf_params.solver=gsl_multifit_nlinear_solver_cholesky;
           }
           if(radio_NLSF_3->isChecked()){
               fdf_params.solver=gsl_multifit_nlinear_solver_qr;
               cout<<"QR solver set"<<endl;
           }
           if(radio_NLSF_4->isChecked()){
               fdf_params.solver=gsl_multifit_nlinear_solver_svd;
               cout<<"SVD solver set"<<endl;
           }

       }
       //cout<<"fdf_params h_df="<<fdf_params.h_df<<endl;
       //fdf_params.trs = gsl_multifit_nlinear_trs_subspace2D;
       //fdf_params.solver=gsl_multifit_nlinear_solver_cholesky;
       //fdf_params.solver=gsl_multifit_nlinear_solver_mcholesky;
       //fdf_params.solver=gsl_multifit_nlinear_solver_qr;
       //fdf_params.solver=gsl_multifit_nlinear_solver_svd;
       //fdf_params.factor_up=4;
       fdf_params.fdtype=GSL_MULTIFIT_NLINEAR_FWDIFF;
       fdf_params.fdtype=GSL_MULTIFIT_NLINEAR_CTRDIFF;



         gsl_vector *f;
         //gsl_vector_long_double *ff;
         gsl_matrix *J;
         gsl_matrix *covar = gsl_matrix_alloc (p, p);
         gsl_vector *t, *y, *weights,*x;
         t = gsl_vector_alloc(n);
         y = gsl_vector_alloc(n);
         weights = gsl_vector_alloc(n);
         x =  gsl_vector_alloc(p);

         for(size_t i=0;i<n;++i){
             gsl_vector_set(t,i,_file.file()[i][0]);
             gsl_vector_set(y,i,_file.file()[i][1]);
             gsl_vector_set(weights,i,1.0/pow(_file.file()[i][2],2));
         }

         int ind=1;
         gsl_vector_set(x,0,1);
         for(size_t i=0;i<nfreq;++i){
             if(ind_ind[i]){
                gsl_vector_set(x,ind,freq_all[i]);
                gsl_vector_set(x,ind+1,_A_lin[i]);
                //gsl_vector_set(x,ind+1,_A_lin[i]*cos(_phi_lin[i]));
                gsl_vector_set(x,ind+2,_phi_lin[i]);
                //gsl_vector_set(x,ind+2,_A_lin[i]*sin(_phi_lin[i]));
                ind+=3;
             }else{
                 gsl_vector_set(x,ind,_A_lin[i]);
                 gsl_vector_set(x,ind+1,_phi_lin[i]);
                 //gsl_vector_set(x,ind,_A_lin[i]*cos(_phi_lin[i]));
                 //gsl_vector_set(x,ind+1,_A_lin[i]*sin(_phi_lin[i]));
                 ind+=2;
             }
         }

         //cout<<"initial data set"<<endl;
         //for(size_t i=0;i<p;++i){
         //    cout<<gsl_vector_get(x,i)<<" ";
         //}
         //cout<<endl;

         struct data d = { n, t, y,freq_i,freq_all,ind_ind,_freq_matrix };

         double chisq, chisq0;
         int status, info;

         //const double xtol = 1e-8;
         //const double gtol = 1e-8;
         const double ftol = 0.0;
         const double xtol = 1e-12;
         const double gtol = 1e-12;


         /* define the function to be minimized */
         fdf.f = expb_f;
         //fdf.f = sinsum;
         //fdf.df = NULL;   /* set to NULL for finite-difference Jacobian */
         fdf.df=expb_df;
         fdf.fvv = NULL;     /* not using geodesic acceleration */
         fdf.n = n;
         fdf.p = p;
         fdf.params = &d;


         params params;
         params.p=p;
         params.n=n;


         /* allocate workspace with default parameters */
         w = gsl_multifit_nlinear_alloc (T, &fdf_params, n, p);

         /* initialize solver with starting point and weights */
         gsl_multifit_nlinear_winit (x, weights, &fdf, w);

         /* compute initial cost function */
         f = gsl_multifit_nlinear_residual(w);
         gsl_blas_ddot(f, f, &chisq0);

         cout<<"init ok"<<endl;

         /* solve the system with a maximum of 100 iterations */
         //status = gsl_multifit_nlinear_driver(100, xtol, gtol, ftol, callback, &params, &info, w);
         status = gsl_multifit_nlinear_driver(100, xtol, gtol, ftol, NULL, &params, &info, w);

         /* compute covariance of best fit parameters */
         J = gsl_multifit_nlinear_jac(w);
         gsl_multifit_nlinear_covar (J, 0.0, covar);

         /* compute final cost */
         gsl_blas_ddot(f, f, &chisq);

         #define FIT(i) gsl_vector_get(w->x, i)
         #define ERR(i) sqrt(gsl_matrix_get(covar,i,i))

         fprintf(stderr, "summary from method '%s/%s'\n",gsl_multifit_nlinear_name(w),gsl_multifit_nlinear_trs_name(w));
         fprintf(stderr, "number of iterations: %zu\n", gsl_multifit_nlinear_niter(w));
         fprintf(stderr, "function evaluations: %zu\n", fdf.nevalf);
         fprintf(stderr, "Jacobian evaluations: %zu\n", fdf.nevaldf);
         fprintf(stderr, "reason for stopping: %s\n", (info == 1) ? "small step size" : "small gradient");
         fprintf(stderr, "initial |f(x)| = %f\n", sqrt(chisq0));
         fprintf(stderr, "final   |f(x)| = %f\n", sqrt(chisq));

         double dof = n - p;
         double c = GSL_MAX_DBL(1, sqrt(chisq / dof));

         fprintf(stderr, "chisq/dof = %g\n", chisq / dof);
         fprintf (stderr, "status = %s\n", gsl_strerror (status));

         _A0=gsl_vector_get(w->x,0);
         _sA0=c*ERR(0);

         ind=1;
         for(size_t j=0;j<ind_ind.size();++j){
             //cout<<"jjjj="<<j<<endl;
             if(ind_ind[j]){
                 //cout<<"aaadd "<<ind_ind.size()<<endl;
                 _f.push_back(gsl_vector_get(w->x,ind));
                 _sf.push_back(c*ERR(ind));
                 _A.push_back(gsl_vector_get(w->x,ind+1));
                 _sA.push_back(c*ERR(ind+1));
                 _phi.push_back(gsl_vector_get(w->x,ind+2));
                 _sphi.push_back(c*ERR(ind+2));
                 /*
                 _A.push_back(sqrt(pow(gsl_vector_get(w->x,ind+1),2)+pow(gsl_vector_get(w->x,ind+2),2)));
                 _sA.push_back(1.0/_A.back()*(sqrt(pow(gsl_vector_get(w->x,ind+1)*c*ERR(ind+1),2)+pow(gsl_vector_get(w->x,ind+2)*c*ERR(ind+2),2)) ));
                 _phi.push_back(atan2(gsl_vector_get(w->x,ind+2),gsl_vector_get(w->x,ind+1)));
                 _sphi.push_back(sqrt(pow(gsl_vector_get(w->x,ind+2)*c*ERR(ind+1)/(gsl_vector_get(w->x,ind+1)*gsl_vector_get(w->x,ind+1)),2) + pow(c*ERR(ind+2)/gsl_vector_get(w->x,ind+1),2) )/(1+(pow(gsl_vector_get(w->x,ind+2)/gsl_vector_get(w->x,ind+1),2))));
                 */

                 //cout<<"dddd"<<endl;
                 ind+=3;
             }else{
                 double freq=0;
                 for(size_t k=0;k<_freq_matrix[j].size();++k){
                     //cout<<"k="<<k<<endl;
                     freq+=_freq_matrix[j][k]*freq_i[k];//
                 }
                 _f.push_back(freq);
                 _sf.push_back(0);

                 _A.push_back(gsl_vector_get(w->x,ind));
                 _sA.push_back(c*ERR(ind));
                 _phi.push_back(gsl_vector_get(w->x,ind+1));
                 _sphi.push_back(c*ERR(ind+1));

                 /*
                 _A.push_back(sqrt(pow(gsl_vector_get(w->x,ind),2)+pow(gsl_vector_get(w->x,ind+1),2)));
                 _sA.push_back(1.0/_A.back()*(sqrt(pow(gsl_vector_get(w->x,ind)*c*ERR(ind),2)+pow(gsl_vector_get(w->x,ind+1)*c*ERR(ind+1),2)) ));
                 _phi.push_back(atan2(gsl_vector_get(w->x,ind+1),gsl_vector_get(w->x,ind)));
                 _sphi.push_back(sqrt(pow(gsl_vector_get(w->x,ind+1)*c*ERR(ind)/(gsl_vector_get(w->x,ind)*gsl_vector_get(w->x,ind)),2) + pow(c*ERR(ind+1)/gsl_vector_get(w->x,ind),2) )/(1+(pow(gsl_vector_get(w->x,ind+1)/gsl_vector_get(w->x,ind),2))));
                 */

                 ind+=2;
              }
         }
         //cout<<"data update"<<endl;


           if(ind_A!=-1 && ind_sA!=-1 && ind_phi && ind_sphi){
               for(int i=0;i<table->rowCount();++i){
                   if(table->item(i,ind_A)!=nullptr){
                       table->item(i,ind_A)->setText( to_string(_A[i]).c_str());
                   }
                   if(table->item(i,ind_sA)!=nullptr){
                       table->item(i,ind_sA)->setText( to_string(_sA[i]).c_str());
                   }
                   if(table->item(i,ind_phi)!=nullptr){
                       table->item(i,ind_phi)->setText( to_string(_phi[i]).c_str());
                   }
                   if(table->item(i,ind_sphi)!=nullptr){
                       table->item(i,ind_sphi)->setText( to_string(_sphi[i]).c_str());
                   }
                   if(table->item(i,ind_freq)!=nullptr){
                       table->item(i,ind_freq)->setText( to_string(_f[i]).c_str());
                   }
                   if(table->item(i,ind_freq)!=nullptr){
                       table->item(i,ind_sfreq)->setText( to_string(_sf[i]).c_str());
                   }
               }
           }//*/


           gsl_multifit_nlinear_free (w);
           gsl_matrix_free (covar);
           gsl_vector_free(t);
           gsl_vector_free(y);
           gsl_vector_free(x);
           gsl_vector_free(weights);



    }
}



void Worker::doWork(const QString &parameter){
//void Worker::doWork(){

        cout<<"doWork nonlinear"<<endl;

        //QString result;
        Worker_data_out results;
        /* ... here is the expensive or blocking operation ... */


        int nfreq=freq_all.size();
        size_t n=_file->file().size();

        int p=freq_i.size()*3+freq_c.size()*2+1;

        int p0=0;



        //cout<<"parameters number="<<p<<endl;

        const gsl_multifit_nlinear_type *T = gsl_multifit_nlinear_trust;
        gsl_multifit_nlinear_workspace *w;
        gsl_multifit_nlinear_fdf fdf;

          gsl_vector *f;
          //gsl_vector_long_double *ff;
          gsl_matrix *J;
          gsl_matrix *covar = gsl_matrix_alloc (p, p);
          gsl_vector *t, *y, *weights,*x;
          t = gsl_vector_alloc(n);
          y = gsl_vector_alloc(n);
          weights = gsl_vector_alloc(n);
          x =  gsl_vector_alloc(p);

          for(size_t i=0;i<n;++i){
              gsl_vector_set(t,i,_file->file()[i][0]);
              gsl_vector_set(y,i,_file->file()[i][1]);
              gsl_vector_set(weights,i,1.0/pow(_file->file()[i][2],2));
          }
          int ind=1;
          gsl_vector_set(x,0,A0);
          for(size_t i=0;i<nfreq;++i){
              if(ind_ind[i]){
                 gsl_vector_set(x,ind,freq_all[i+p0]);
                 //gsl_vector_set(x,ind+1,_A[i+p0]);
                 gsl_vector_set(x,ind+1,_A[i]*cos(_phi[i]));
                 //gsl_vector_set(x,ind+2,_phi[i+p0]);
                 gsl_vector_set(x,ind+2,_A[i]*sin(_phi[i]));
                 ind+=3;
              }else{
                  //gsl_vector_set(x,ind,_A[i+p0]);
                  //gsl_vector_set(x,ind+1,_phi[i+p0]);
                  gsl_vector_set(x,ind,_A[i]*cos(_phi[i]));
                  gsl_vector_set(x,ind+1,_A[i]*sin(_phi[i]));
                  ind+=2;
              }
          }

          //cout<<"doWork: initial data set"<<endl;
          //for(size_t i=0;i<p;++i){
          //    cout<<gsl_vector_get(x,i)<<" ";
          //}
          //cout<<endl;

          //cout<<"p="<<p<<" n="<<n<<endl;
          //cout<<"freq_i="<<freq_i.size()<<" freq_all="<<freq_all.size()<<endl;
          //cout<<"matrix="<<_freq_matrix.size()<<endl;


          struct data d = { n, t, y,freq_i,freq_all,ind_ind,_freq_matrix,_T0,p};

          double chisq, chisq0;
          int status, info;

          //const double xtol = 1e-8;
          //const double gtol = 1e-8;
          const double ftol = 0.0;
          const double xtol = 1e-12;
          const double gtol = 1e-12;

        /* define the function to be minimized */
        //fdf.f = expb_f;
        fdf.f = sinsum;
        //fdf.df = NULL;   /* set to NULL for finite-difference Jacobian */
        //fdf.df=expb_df;
        fdf.df=sinsum_df;
        fdf.fvv = NULL;     /* not using geodesic acceleration */
        fdf.n = n;
        fdf.p = p;
        fdf.params = &d;


        params params;
        params.p=p;
        params.n=n;


        /* allocate workspace with default parameters */
        w = gsl_multifit_nlinear_alloc (T, &fdf_params, n, p);

        cout<<"gsl_multifit_nlinear_alloc"<<endl;

        /* initialize solver with starting point and weights */
        gsl_multifit_nlinear_winit (x, weights, &fdf, w);

        cout<<"gsl_multifit_nlinear_winit"<<endl;

        /* compute initial cost function */
        f = gsl_multifit_nlinear_residual(w);

        cout<<"gsl_multifit_nlinear_residual"<<endl;
        gsl_blas_ddot(f, f, &chisq0);

        cout<<"init ok"<<endl;

        /* solve the system with a maximum of 100 iterations */
        //status = gsl_multifit_nlinear_driver(NLSF_max_iteration, xtol, gtol, ftol, callback, &params, &info, w);
        status = gsl_multifit_nlinear_driver(NLSF_max_iteration, xtol, gtol, ftol, NULL, &params, &info, w);

        /* compute covariance of best fit parameters */
        J = gsl_multifit_nlinear_jac(w);
        gsl_multifit_nlinear_covar (J, 0.0, covar);

        /*
        ofstream fo{"cov_J_diff_test"+to_string(0)+".dat"};
        for(size_t j=0;j<p;++j){
           fo<<gsl_matrix_get(covar, j,j)<<endl;
        }
        fo<<endl;
        for(size_t i=0;i<p;++i){
         for(size_t j=0;j<p;++j){
            fo<<gsl_matrix_get(covar, i,j)<<" ";
         }
         fo<<endl;
        }
        fo<<endl;
        for(size_t i=0;i<n;++i){
         for(size_t j=0;j<p;++j){
            fo<<gsl_matrix_get(J, i,j)<<" ";
         }
         fo<<endl;
        }
        cout<<endl;
        //*/

        /* compute final cost */
        gsl_blas_ddot(f, f, &chisq);

        #define FIT(i) gsl_vector_get(w->x, i)
        #define ERR(i) sqrt(gsl_matrix_get(covar,i,i))

        fprintf(stderr, "summary from method '%s/%s'\n",gsl_multifit_nlinear_name(w),gsl_multifit_nlinear_trs_name(w));
        fprintf(stderr, "number of iterations: %zu\n", gsl_multifit_nlinear_niter(w));
        fprintf(stderr, "function evaluations: %zu\n", fdf.nevalf);
        fprintf(stderr, "Jacobian evaluations: %zu\n", fdf.nevaldf);
        fprintf(stderr, "reason for stopping: %s\n", (info == 1) ? "small step size" : "small gradient");
        fprintf(stderr, "initial |f(x)| = %f\n", sqrt(chisq0));
        fprintf(stderr, "final   |f(x)| = %f\n", sqrt(chisq));

        double dof = n - p;
        double c = GSL_MAX_DBL(1, sqrt(chisq / dof));
        c=sqrt(chisq / dof);

        //cout<<"c="<<c<<endl;
        fprintf(stderr, "chisq/dof = %g\n", chisq / dof);
        fprintf (stderr, "status = %s\n", gsl_strerror (status));

         double _A0=gsl_vector_get(w->x,0);
         double _sA0=c*ERR(0);

         results.iteration=gsl_multifit_nlinear_niter(w);
         results.chisqrt=sqrt(chisq / dof);
         results.status=gsl_strerror (status);

         vector<double>_f;
         vector<double>_sf;
         vector<double>_A;
         vector<double>_sA;
         vector<double>_phi;
         vector<double>_sphi;

        ind=1;
        for(size_t j=0;j<ind_ind.size();++j){
            //cout<<"jjjj="<<j<<endl;
            if(ind_ind[j]){
                //cout<<"aaadd "<<ind_ind.size()<<endl;
                _f.push_back(gsl_vector_get(w->x,ind));
                _sf.push_back(c*ERR(ind));

                /*
                _A.push_back(gsl_vector_get(w->x,ind+1));
                _sA.push_back(c*ERR(ind+1));
                double phi=gsl_vector_get(w->x,ind+2);
                if(phi<0){
                    while(phi<0){
                        phi+=2*M_PI;
                    }
                }
                if(phi>2*M_PI){
                    while(phi>2*M_PI){
                        phi-=2*M_PI;
                    }
                }//*/
                /*
                _phi.push_back(phi);
                double sphi=c*ERR(ind+2);
                if(sphi>2*M_PI){
                    while(sphi>2*M_PI){
                        sphi-=2*M_PI;
                    }
                }
                _sphi.push_back(sphi);
                //*/

                _A.push_back(sqrt(pow(gsl_vector_get(w->x,ind+1),2)+pow(gsl_vector_get(w->x,ind+2),2)));
                _sA.push_back(1.0/_A.back()*(sqrt(pow(gsl_vector_get(w->x,ind+1)*c*ERR(ind+1),2)+pow(gsl_vector_get(w->x,ind+2)*c*ERR(ind+2),2)) ));                
                double phi=atan2(gsl_vector_get(w->x,ind+2),gsl_vector_get(w->x,ind+1));
                if(phi<0){
                    while(phi<0){
                        phi+=2*M_PI;
                    }
                }
                _phi.push_back(phi);
                _sphi.push_back(sqrt(pow(gsl_vector_get(w->x,ind+2)*c*ERR(ind+1)/(gsl_vector_get(w->x,ind+1)*gsl_vector_get(w->x,ind+1)),2) + pow(c*ERR(ind+2)/gsl_vector_get(w->x,ind+1),2) )/(1+(pow(gsl_vector_get(w->x,ind+2)/gsl_vector_get(w->x,ind+1),2))));
                //*/

                //cout<<"dddd"<<endl;
                ind+=3;
            }else{
                double freq=0;
                for(size_t k=0;k<_freq_matrix[j].size();++k){
                    //cout<<"k="<<k<<endl;
                    freq+=_freq_matrix[j][k]*freq_i[k];//
                }
                _f.push_back(freq);
                _sf.push_back(0);

                /*
                _A.push_back(gsl_vector_get(w->x,ind));
                _sA.push_back(c*ERR(ind));
                double phi=gsl_vector_get(w->x,ind+1);
                if(phi<0){
                    while(phi<0){
                        phi+=2*M_PI;
                    }
                }
                if(phi>2*M_PI){
                    while(phi>2*M_PI){
                        phi-=2*M_PI;
                    }
                }//*/
                /*
                _phi.push_back(phi);
                double sphi=c*ERR(ind+1);
                if(sphi>2*M_PI){
                    while(sphi>2*M_PI){
                        sphi-=2*M_PI;
                    }
                }
                _sphi.push_back(sphi);
                //*/

                _A.push_back(sqrt(pow(gsl_vector_get(w->x,ind),2)+pow(gsl_vector_get(w->x,ind+1),2)));
                _sA.push_back(1.0/_A.back()*(sqrt(pow(gsl_vector_get(w->x,ind)*c*ERR(ind),2)+pow(gsl_vector_get(w->x,ind+1)*c*ERR(ind+1),2)) ));
                double phi=atan2(gsl_vector_get(w->x,ind+1),gsl_vector_get(w->x,ind));
                if(phi<0){
                    while(phi<0){
                        phi+=2*M_PI;
                    }
                }
                _phi.push_back(phi);
                _sphi.push_back(sqrt(pow(gsl_vector_get(w->x,ind+1)*c*ERR(ind)/(gsl_vector_get(w->x,ind)*gsl_vector_get(w->x,ind)),2) + pow(c*ERR(ind+1)/gsl_vector_get(w->x,ind),2) )/(1+(pow(gsl_vector_get(w->x,ind+1)/gsl_vector_get(w->x,ind),2))));
                //*/

                ind+=2;
             }
        }


        results._A0=_A0;
        results._sA0=_sA0;
        results._f=_f;
        results._sf=_sf;
        results._A=_A;
        results._sA=_sA;
        results._phi=_phi;
        results._sphi=_sphi;
        results.p0=p0;
        results.nreallyfitted=nreallyfitted;


        gsl_multifit_nlinear_free (w);
        gsl_matrix_free (covar);
        gsl_vector_free(t);
        gsl_vector_free(y);
        gsl_vector_free(x);
        gsl_vector_free(weights);


        //cout<<"finish"<<endl;

        emit resultReady(results);
}


void MainWindow::fitsin_nonlinear_thread(){
    //cout<<"fitsin_nonlinear_thread"<<endl;

    if(table->rowCount()>0){

       vector<double>freq_i;
       vector<double>freq_all;
       vector<double>freq_c;
       int ind_freq=-1;
       int ind_sfreq=-1;
       int ind_status=-1;
       int ind_A=-1;
       int ind_sA=-1;
       int ind_phi=-1;
       int ind_sphi=-1;
       vector<bool> ind_ind;
       for(auto i=0;i<table->columnCount();++i){
           if(table->horizontalHeaderItem(i)->text()=="status"){
               ind_status=i;
           }
           if(table->horizontalHeaderItem(i)->text()=="freq"){
               ind_freq=i;
           }
           if(table->horizontalHeaderItem(i)->text()=="e_freq"){
               ind_sfreq=i;
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
       //cout<<"fitsin_nonlinear_thread: ind_status="<<ind_status<<" ind_freq="<<ind_freq<<endl;
       vector<double> A_t;
       vector<double> phi_t;
       if(ind_status!=-1 && ind_freq!=-1){
           for(int i=0;i<table->rowCount();++i){
               if(table->item(i,ind_status)!=nullptr){
                   if(table->item(i,ind_status)->text()=="" || table->item(i,ind_status)->text()=="i"){
                       freq_i.push_back(table->item(i,ind_freq)->text().toDouble());
                       ind_ind.push_back(true);
                   }else{
                       freq_c.push_back(table->item(i,ind_freq)->text().toDouble());
                       ind_ind.push_back(false);
                   }
               }
               if(table->item(i,ind_A)!=nullptr){
                   A_t.push_back(table->item(i,ind_A)->text().toDouble());
               }
               if(table->item(i,ind_phi)!=nullptr){
                   phi_t.push_back(table->item(i,ind_phi)->text().toDouble());
               }
               freq_all.push_back(table->item(i,ind_freq)->text().toDouble());
           }
       }
       //cout<<"fitsin_nonlinear_thread: freq_i="<<freq_i<<" --- n = "<<freq_i.size()<<endl;
       //cout<<"fitsin_nonlinear_thread: freq_c="<<freq_c<<" --- n = "<<freq_c.size()<<endl;
       //cout<<"fitsin_nonlinear_thread: freq_all="<<freq_all<<" --- n = "<<freq_all.size()<<endl;
       if(freq_all.size()!=A_t.size() || freq_all.size()!=phi_t.size()){
           cout<<"problem with input data"<<endl;
           cout<<"freq_all="<<freq_all<<endl;
           cout<<"A_t="<<A_t<<endl;
           cout<<"phi_t="<<phi_t<<endl;
       }

       //frequency_manager.set_frequencies(freq_all);
       //frequency_manager.set_martix(_freq_matrix);

       gsl_multifit_nlinear_parameters fdf_params = gsl_multifit_nlinear_default_parameters();
       //if(_NLSF_solver="cholesky";)
       if(!_combo_settings_action_NLSF_dialog_init){
         //fdf_params.solver=gsl_multifit_nlinear_solver_mcholesky;
       }else{
           if(radio_NLSF_1->isChecked()){
               fdf_params.solver=gsl_multifit_nlinear_solver_mcholesky;
           }
           if(radio_NLSF_2->isChecked()){
               fdf_params.solver=gsl_multifit_nlinear_solver_cholesky;
           }
           if(radio_NLSF_3->isChecked()){
               fdf_params.solver=gsl_multifit_nlinear_solver_qr;
               //cout<<"QR solver set"<<endl;
           }
           if(radio_NLSF_4->isChecked()){
               fdf_params.solver=gsl_multifit_nlinear_solver_svd;
               //cout<<"SVD solver set"<<endl;
           }

       }
       if(!_combo_settings_action_NLSF_dialog_init){
         //fdf_params.trs=gsl_multifit_nlinear_trs_lm;
       }else{
           if(radio_NLSF_trs_1->isChecked()){
               fdf_params.trs=gsl_multifit_nlinear_trs_lm;
           }
           if(radio_NLSF_trs_2->isChecked()){
               fdf_params.trs = gsl_multifit_nlinear_trs_lmaccel;
           }
           if(radio_NLSF_trs_3->isChecked()){
               fdf_params.trs=gsl_multifit_nlinear_trs_dogleg;
           }
           if(radio_NLSF_trs_4->isChecked()){
               fdf_params.trs=gsl_multifit_nlinear_trs_ddogleg;
           }
           if(radio_NLSF_trs_5->isChecked()){
               fdf_params.trs=gsl_multifit_nlinear_trs_subspace2D;
           }
       }

       //cout<<"fdf_params h_df="<<fdf_params.h_df<<endl;
       //fdf_params.trs = gsl_multifit_nlinear_trs_subspace2D;
       //fdf_params.solver=gsl_multifit_nlinear_solver_cholesky;
       //fdf_params.solver=gsl_multifit_nlinear_solver_mcholesky;
       //fdf_params.solver=gsl_multifit_nlinear_solver_qr;
       //fdf_params.solver=gsl_multifit_nlinear_solver_svd;
       //fdf_params.factor_up=4;
       fdf_params.fdtype=GSL_MULTIFIT_NLINEAR_FWDIFF;
       fdf_params.fdtype=GSL_MULTIFIT_NLINEAR_CTRDIFF;

       //QThread *thread = new QThread(this);
       Worker *worker = new Worker();
       worker->freq_i=freq_i;
       worker->freq_all=freq_all;
       worker->freq_c=freq_c;
       worker->_freq_matrix=_freq_matrix;
       worker->_file=&_file;
       worker->fdf_params=fdf_params;
       worker->ind_ind=ind_ind;
       worker->_A_lin=_A_lin;
       worker->_phi_lin=_phi_lin;
       worker->_A=A_t;
       worker->_phi=phi_t;
       worker->nmaxfittet=_General_n_last_freq;
       worker->A0=_A0;
       worker->NLSF_max_iteration=_NLSF_max_iteration;
       worker->_T0=_T0;


       qRegisterMetaType<Worker_data_out>("Worker_data_out");

       worker->moveToThread(&workerThread);
       //worker->moveToThread(thread);
               connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
               //connect(&workerThread, &QThread::started, worker, &Worker::doWork);
               connect(this, &MainWindow::operate, worker, &Worker::doWork);
       //        connect(this, &MainWindow::start, worker, &Worker::doWork);
               connect(worker, &Worker::resultReady, this, &MainWindow::handleResults);
               workerThread.start();


    }

}



void MainWindow::fitsin_nonlinear_thread_init(){   
    if(table->rowCount()>0){
       pushB_fitsin->setDisabled(true);
       pushB_fitsin_only_nonlin->setDisabled(true);
       info_table->horizontalHeader()->setDisabled(true);
       pushB_auto->setDisabled(true);
       pushB_fitsin_only_lin->setDisabled(true);
    }
    _time_start_nonlinear_thread=time(NULL);
    fitsin_nonlinear_thread();
    emit(operate("start"));
    //cout<<"workerThread done"<<endl;
}

void MainWindow::handleResults(const Worker_data_out results){
    cout<<"nonlinear thread done"<<endl;

    int ind_freq=-1;
    int ind_sfreq=-1;
    int ind_status=-1;
    int ind_A=-1;
    int ind_sA=-1;
    int ind_phi=-1;
    int ind_sphi=-1;
    vector<bool> ind_ind;
    for(auto i=0;i<table->columnCount();++i){
        if(table->horizontalHeaderItem(i)->text()=="status"){
            ind_status=i;
        }
        if(table->horizontalHeaderItem(i)->text()=="freq"){
            ind_freq=i;
        }
        if(table->horizontalHeaderItem(i)->text()=="e_freq"){
            ind_sfreq=i;
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

    _A0=results._A0;
    _sA0=results._sA0;

    int rowmax=table->rowCount();
    int p0=results.p0;
    int nreallyfitted=results.nreallyfitted;
    rowmax=rowmax-p0;

    if(ind_A!=-1 && ind_sA!=-1 && ind_phi && ind_sphi){
        for(int i=0;i<rowmax;++i){
            if(table->item(i+p0,ind_A)!=nullptr){
                table->item(i+p0,ind_A)->setText( to_string_pw(results._A[i],8).c_str());
            }
            if(table->item(i+p0,ind_sA)!=nullptr){
                table->item(i+p0,ind_sA)->setText( to_string_pw(results._sA[i],6).c_str());
            }
            if(table->item(i+p0,ind_phi)!=nullptr){
                table->item(i+p0,ind_phi)->setText( to_string_pw(results._phi[i],8).c_str());
            }
            if(table->item(i+p0,ind_sphi)!=nullptr){
                table->item(i+p0,ind_sphi)->setText( to_string_pw(results._sphi[i],6).c_str());
            }
            if(table->item(i+p0,ind_freq)!=nullptr){
                table->item(i+p0,ind_freq)->setText( to_string_pw(results._f[i],8).c_str());
            }
            if(table->item(i+p0,ind_freq)!=nullptr){
                table->item(i+p0,ind_sfreq)->setText( to_string_pw(results._sf[i],6).c_str());
            }
        }
        table->resizeColumnsToContents();
    }//*/

    //cout<<"A0="<<_A0<<endl;
    //cout<<"sA0="<<_sA0<<endl;


   // workerThread.deleteLater();

    pushB_fitsin->setDisabled(false);
    pushB_fitsin_only_nonlin->setDisabled(false);
    info_table->horizontalHeader()->setDisabled(false);
    pushB_auto->setDisabled(false);
    pushB_fitsin_only_lin->setDisabled(false);


    _time_stop_nonlinear_thread=time(NULL);
    cout<<"time = "<<f_time(_time_stop_nonlinear_thread-_time_start_nonlinear_thread)<<endl;;

    label_info_fitting->setText(label_info_fitting2->text());
    string text;
    text="<font color="+NLSF_info_color_font.toStdString()+">nonlinear: chisq="+to_string(results.chisqrt)+", iteration="+to_string(results.iteration);
    string status=results.status;
    if(results.iteration<_NLSF_max_iteration && status.find("exceeded max number of iteration")!=string::npos){
        status="success";
    }
    text+=", "+status;
    text+=", time = "+f_time(_time_stop_nonlinear_thread-_time_start_nonlinear_thread);
    label_info_fitting2->setText(text.c_str());



    workerThread.quit();
    workerThread.wait();


    get_residuals();

    update_sn();

    //check_for_combination();

   if(_full_auto){
       auto_clicked();
   }

}

void MainWindow::get_residuals(){
    //cout<<"get_residuals"<<endl;
    if(table->rowCount()>0){
        _resolution_for_combination=spinBox_resolution_for_combination->value();


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
       //cout<<"get_residuals: ind_status="<<ind_status<<" ind_freq="<<ind_freq<<endl;
       if(ind_status!=-1 && ind_freq!=-1){
           for(int i=0;i<table->rowCount();++i){
               if(table->item(i,ind_status)!=nullptr){
                   if(table->item(i,ind_status)->text()=="" || table->item(i,ind_status)->text()=="i"){
                       freq_i.push_back(table->item(i,ind_freq)->text().toDouble());
                   }
               }
               freq_all.push_back(table->item(i,ind_freq)->text().toDouble());
               A.push_back(table->item(i,ind_A)->text().toDouble());
               phi.push_back(table->item(i,ind_phi)->text().toDouble());
           }
       }
       //cout<<"get_residuals: freq_i="<<freq_i<<" ---"<<freq_i.size()<<endl;
       //cout<<"get_residuals: freq_all="<<freq_all<<" ---"<<freq_all.size()<<endl;

       int nfreq=freq_all.size();
       int n=_file.file().size();

       _fitted_curve.clear();
       for(size_t i=0;i<n;++i){
           double y=_A0;
           for(size_t j=0;j<nfreq;++j){
              //if(i==0) cout<<setprecision(10)<<freq_all[j]<<" "<<A[j]<<" "<<phi[j]<<endl;
              y+=A[j]*sin(2*M_PI*freq_all[j]*(_file.file()[i][0]-_T0)+phi[j]);
           }
           _fitted_curve.push_back(y);
       }
       _fitted_curve_ok=true;

       //cout<<"get_residuals: add_fitted_curve ..."<<endl;
       add_fitted_curve();
       //cout<<"done"<<endl;


       //_residuals_old=_residuals;
       //cout<<"_residuals_old="<<_residuals_old<<endl;
       _residuals.clear();
       _residuals.reserve(n);
       for(size_t i=0;i<n;++i){
           _residuals.push_back(_file.file()[i][1]-_fitted_curve[i]);
       }
       _residuals_ok=true;


       cout<<"residuals done"<<endl;

       plot_lc_residuals();

       if(_init_customPlot_phase){
           get_phase_diagram();
       }


    }
}

void MainWindow::get_freq_number(){
    if(table->rowCount()>0){
       vector<double>freq_i;
       vector<double>freq_all;
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
       //cout<<"get_residuals: ind_status="<<ind_status<<" ind_freq="<<ind_freq<<endl;
       if(ind_status!=-1 && ind_freq!=-1){
           for(int i=0;i<table->rowCount();++i){
               if(table->item(i,ind_status)!=nullptr){
                   if(table->item(i,ind_status)->text()=="" || table->item(i,ind_status)->text()=="i"){
                       freq_i.push_back(table->item(i,ind_freq)->text().toDouble());
                   }
               }
               freq_all.push_back(table->item(i,ind_freq)->text().toDouble());
           }
           _n_ind_freq=freq_i.size();
           _n_comb_freq=freq_all.size()-freq_i.size();
       }else{
           _n_ind_freq=0;
           _n_comb_freq=0;
       }
    }else{
       _n_ind_freq=0;
       _n_comb_freq=0;
    }
}

void MainWindow::update_freq_number(){
    get_freq_number();
    label_ind_freq->setText("<font color = "+basic_color_font+"> ind. freq.: "+to_string(_n_ind_freq).c_str());
    label_comb_freq->setText("<font color = "+basic_color_font+"> comb. freq.: "+to_string(_n_comb_freq).c_str());
}



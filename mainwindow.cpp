#include "mainwindow.h"
#include "ui_mainwindow.h"



void MainWindow::set_defaults(){
   _f0=0;
   _fe=10;
   _df=0.001;

   max_table_backup=10;

   _box_number=2;

   _General_n_s=5;
   _General_n_h=10;
   _General_n_c2_1=4;
   _General_n_c2_2=4;
   _General_n_c3_1=3;
   _General_n_c3_2=3;
   _General_n_c3_3=3;

   _resolution_for_combination_factor=0.25;
   _resolution_for_combination_step=0.1;

   _use_first_combination=true;

   _skipp_peaks_closer_than_resolution=true;
   _resolution=0.1;

   _use_highest_peaks=true;

   _NLSF_max_iteration=1000;

   _crit_stop=5;

   CP_Layout_width=3;
   out_Layout_width=2;
   out_Layout_width=3;

   pushB_border_color="beige";
   //pushB_border_color="black";
   pushB_background_color="white";
   pushB_background_color="#edddc5";


   basic_color_font="orange";
   basic_color_font="#ff8000";
   basic_color_font="#b2ff66";
   basic_color_font="#ffff66";
   basic_color_font="#ffd000";
   basic_color_font="#ffa300";
   basic_color_font="#ffd839";
   basic_color_font="#FFB13B";

   NLSF_info_color_font="#ffff66";
   NLSF_info_color_font="#b2ff66";

   trf_line_color="blue";
   //trf_line_color="#ff33ff";
   trf_line_width=1;

   lc_line_color="blue";
   lc_point_color="green";
   lc_point_color="#80FF00";
   lc_detrend_line_color="red";
   lc_fitted_line_color="yellow";
   lc_fitted_line_color="#CCCC00";
   lc_fitted_line_color="#FFFF66";
   lc_fitted_line_color="#CACD0A";

   table_color_selection_background="#d9fffb";
   table_color_selection_background="#FAD7A0";
   table_color_selection_background_children="#FEF5E7";
   table_color_selection_background_parents="#C67D0A";

   main_background_color=QColor(14, 10, 74);

}


MainWindow::MainWindow(QWidget *parent):QMainWindow(parent), ui(new Ui::MainWindow){
    this->setGeometry(0,0,1600,600);
    ui->setupUi(this);

    init();
}

MainWindow::~MainWindow(){
    delete ui;
    workerThread.quit();
    workerThread.wait();
}


void MainWindow::resizeEvent(QResizeEvent* event){
    //QPixmap bkgnd(":/img/img/picture.jpg");
    //    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
        QPalette palette;
    //    palette.setBrush(QPalette::Background, bkgnd);
        //palette.setColor(QPalette::Window, Qt::black);
        palette.setColor(QPalette::Window,main_background_color);
        this->setPalette(palette);


}

void MainWindow::clearLayout(QLayout* layout, bool deleteWidgets){
    while (QLayoutItem* item = layout->takeAt(0)){
        if (deleteWidgets){
            if (QWidget* widget = item->widget()){
                widget->deleteLater();
            }
        }
        if (QLayout* childLayout = item->layout()){
            clearLayout(childLayout, deleteWidgets);
        }
        delete item;
    }
}



double MainWindow::f_min(vector<double>&v){
  T r;
  if(v.size()>0){
     r=v[0];
     for(size_t i=1;i<v.size();++i){
       if(v[i]<r)r=v[i];
     }
  }else{
     cout<<"f_min: Vector has to have at least one element"<<endl;
  }
  return(r);
}

double MainWindow::f_max(vector<double>&v){
  T r;
  if(v.size()>0){
     r=v[0];
     for(size_t i=1;i<v.size();++i){
       if(v[i]>r)r=v[i];
     }
  }else{
     cout<<"f_max: Vector has to have at least one element"<<endl;;
  }
  return(r);
}

void MainWindow::reset(){
    //this function shoud be called after changing an input data;
    cout<<"reset"<<endl;
    _file_loaded=false;
    detrend_splines.clear();
    detrended_ok=false;
    detrended_current_nbox=-1;
    _trf_ok=false;
    first_lc=true;

    customPlotLc->clearPlottables();
    for(int i=customPlotLc->graphCount()-1;i>=0;--i){
        customPlotLc->removeGraph(i);
    }
    customPlotLc->replot();
    customPlotLc_residuals->clearPlottables();
    for(int i=customPlotLc_residuals->graphCount()-1;i>=0;--i){
        customPlotLc_residuals->removeGraph(i);
    }
    customPlotLc_residuals->replot();

    for(int i=customPlotLc->layerCount()-1;i>=0;--i){
       //customPlot->removeLayer()
    }
    cout<<"reset"<<endl;
    _ind_graph_lc_detrend_inter=-1;
    _ind_graph_lc_detrend_points=-1;
    _ind_graph_lc=-1;
    customPlot->clearPlottables();
    for(int i=customPlot->graphCount()-1;i>=0;--i){
        customPlot->removeGraph(i);
    }
    if(customPlot->hasItem(trfTracer)){
        customPlot->removeItem(trfTracer);
    }
    _trf_ok=false;

    for(int i=0;i<Textpeaks.size();++i){
          if(customPlot->hasItem(Textpeaks[i])){
              cout<<"item found = "<<i<<endl;
              customPlot->removeItem(Textpeaks[i]);
          }
    }
    Textpeaks.clear();


    cout<<"reset"<<endl;
    _ind_graph_noise_sn4=-1;
    _ind_graph_noise_sn5=-1;
    _ind_graph_trf=-1;
    _ind_graph_line=-1;
    _ind_graph_noise=-1;

    _box_width=-1;
    _noise_ok=false;
    _linebar_ok=false;
    _markbar_ok=false;
    pushB_get_Noise->setText("get noise");

    cout<<"reset 3"<<endl;
    if(qcpit_info!=nullptr){
        qcpit_info->setText("");
    }
    cout<<"reset 4"<<endl;
    cout<<"reset done"<<endl;
    customPlot->replot();


    detrend_splines.clear();
    pushB_restore->setText("restore");

    table->clear();
    while(table->rowCount()>0){
      table->removeRow(0);
    }
    while(table->columnCount()>0){
      table->removeColumn(0);
    }
    info_table->clear();
    while(info_table->rowCount()>0){
      info_table->removeRow(0);
    }
    while(info_table->columnCount()>0){
      info_table->removeColumn(0);
    }
    for(size_t i=0;i<table_backup.size();++i){
        while(table_backup[i]->rowCount()>0){
          table_backup[i]->removeRow(0);
        }
        while(table_backup[i]->columnCount()>0){
          table_backup[i]->removeColumn(0);
        }
    }
    table_backup.clear();
    pushB_table_forward->setDisabled(true);
    pushB_table_back->setDisabled(true);

    _residuals.clear();
    _residuals_ok=false;
    _ind_graph_lc_residuals=-1;

    _fitted_curve.clear();
    _fitted_curve_ok=false;
    _ind_graph_fitted_curve_lc=-1;

    _info_table_column_sort=2;
    _info_table_column_sort_ascending=true;

    //_combo_settings_action_NLSF_dialog_init=false;

    _ind_graph_peaks_fwpeaks=-1;
    _full_auto=false;

    _residuals_old_ok=false;

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
    }

    _use_data=true;
    pushB_spec_wind_data->setText("spec. win.");
    _copy_residuals_ok=false;


}


void MainWindow::init(){
    _init_layout=false;

    setlocale(LC_ALL, "en_US.utf8");

    this->setWindowTitle("Fourier Transform");
    this->setGeometry(0,0,1200,600);

    set_defaults();

    QFileDialog dialog_open_file(this);

    //******* menu bar*********



    QFont font;
    ui->menubar->setFont(font);
    ui->menubar->setStyleSheet("color: black");
    ui->menubar->setStyleSheet("background-color: rgb(224,224,224)");
    QMenu *combo_file = new QMenu("File");
    //combo_file->addAction("Open",this, SLOT(open_file()));
    QAction * action = new QAction("Open",this);
    action->setIcon(QIcon(":/img/img/icons8-opened-folder-48.png"));
    action->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));
    action->setStatusTip("Open a file with pre-defined parameters");
    action->setWhatsThis("Open a file containing a needed data");
    connect(action,SIGNAL(triggered()),this,SLOT(open_file()));
    combo_file->addAction(action);
    //combo_file->actionAt(QPoint(0,0))->setIcon(QIcon(":/img/img/icons8-opened-folder-48.png"));
    //combo_file->addAction("Exit",this, SLOT(exit()));
    QAction * actionexit = new QAction("Exit",this);
    actionexit->setIcon(QIcon(":/img/img/winfo-icon-exit-16.png"));
    actionexit->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_E));
    actionexit->setStatusTip("Quit the application");
    connect(actionexit,SIGNAL(triggered()),this,SLOT(exit()));
    combo_file->addAction(actionexit);
    //combo_file->addAction("Save pdf", this, SLOT(savepdf()));
    QAction * actionpdf = new QAction("Save data",this);
    actionpdf->setIcon(QIcon(":/img/img/pdf-icon-16.png"));
    actionpdf->setStatusTip("Save data to files and pdfs");
    connect(actionpdf,SIGNAL(triggered()),this,SLOT(main_save_data_clicked()));
    actionpdf->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_P));
    combo_file->addAction(actionpdf);

    QMenu *combo_settings = new QMenu("Settings");
    QAction * combo_settings_action_NLSF = new QAction("Nonlinear Least Square options",this);
    actionpdf->setStatusTip("Set option for nonlinear least squere fitting");
    connect(combo_settings_action_NLSF,SIGNAL(triggered()),this,SLOT(combo_settings_action_NLSF_clicked()));
    actionpdf->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));
    combo_settings->addAction(combo_settings_action_NLSF);
    QAction * combo_settings_action_General = new QAction("General",this);
    actionpdf->setStatusTip("Set option for nonlinear least squere fitting");
    connect(combo_settings_action_General,SIGNAL(triggered()),this,SLOT(combo_settings_action_General_clicked()));
    actionpdf->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_G));
    combo_settings->addAction(combo_settings_action_General);


    ui->menubar->addMenu(combo_file);

    ui->menubar->addAction("Help", this, SLOT(help()) );

    ui->menubar->addMenu(combo_settings);


    //**** main layout ****

    //ui->centralwidget->setStyleSheet("QPushButton { background-color:"+pushB_background_color+"; border-style: outset; border-width: 2px; border-radius: 2px; border-color: "+pushB_border_color+"; font: bold 12px; min-width: 1px; padding: 1px; }");
    //ui->centralwidget->setStyleSheet("QPushButton { font: bold}");
    //ui->centralwidget->setStyleSheet("QPushButton { border-style: outset; }");
    ui->centralwidget->setStyleSheet("QPushButton { border-color: "+pushB_border_color+";}");

    v_main_Layout = new QVBoxLayout(ui->centralwidget);



    button_Layout = new QGridLayout();
    button_Layout2 = new QGridLayout();
    h_main_Layout = new QHBoxLayout();

    QSplitter *splitter_main_H = new QSplitter(Qt::Orientation::Horizontal);

    label_info = new QLabel("");
    v_main_Layout->addWidget(label_info);

    label_info_fitting = new QLabel("");
    v_main_Layout->addWidget(label_info_fitting);
    label_info_fitting2 = new QLabel("");
    v_main_Layout->addWidget(label_info_fitting2);


    v_main_Layout->addLayout(button_Layout,0);
    v_main_Layout->addLayout(button_Layout2,0);

    //v_main_Layout->addLayout(h_main_Layout,1);
    v_main_Layout->addWidget(splitter_main_H,1);

    v_CP_Layout = new QVBoxLayout();
    v_out_Layout = new QVBoxLayout();

    //h_main_Layout->addLayout(v_CP_Layout,CP_Layout_width);
    //h_main_Layout->addLayout(v_out_Layout,out_Layout_width);

    customPlotLc = new QCustomPlot();
    init_customPlotLc("HJD","A");
    //v_CP_Layout->addWidget(customPlotLc,1);

    customPlotLc_residuals = new QCustomPlot();
    init_customPlotLc_residuals("HJD","A");
    //v_CP_Layout->addWidget(customPlotLc_residuals,1);

    customPlot = new QCustomPlot();
    init_customPlot("Frequency","P");
    //v_CP_Layout->addWidget(customPlot,3);


    //QWidget *widget = new QWidget();
    //QDialog *dialog = new QDialog(this);
    //v_CP_Layout->addWidget(splitter);
    //v_CP_Layout->addWidget(dialog);
    //         widget->setMinimumWidth(200);
    //QSplitter *splitter = new QSplitter(Qt::Orientation::Vertical,dialog);
    splitter = new QSplitter(Qt::Orientation::Vertical);


    //v_CP_Layout->addWidget(splitter);

    splitter_main_H->addWidget(splitter);
    splitter_main_H->setStretchFactor(0,5);

    splitter->addWidget(customPlotLc);
    //splitter->setMinimumWidth(600);
    splitter->setStretchFactor(0,1);
    splitter->addWidget(customPlotLc_residuals);
    splitter->setStretchFactor(1,1);
    splitter->addWidget(customPlot);
    splitter->setStretchFactor(2,3);
    //*/



    pushB_table_back = new QPushButton(" back  ");
    connect(pushB_table_back,SIGNAL(clicked()),this,SLOT(table_back_clicked()));
    pushB_table_back->setDisabled(true);
    //<a href="https://www.flaticon.com/free-icons/back" title="back icons">Back icons created by Jesus Chavarria - Flaticon</a>
    pushB_table_back->setIcon(QIcon(":/img/img/return.png"));

    pushB_table_forward = new QPushButton("forward");
    connect(pushB_table_forward,SIGNAL(clicked()),this,SLOT(table_forward_clicked()));
    pushB_table_forward->setDisabled(true);
    //<a href="https://www.flaticon.com/free-icons/user-interface" title="user interface icons">User interface icons created by See Icons - Flaticon</a>
    pushB_table_forward->setIcon(QIcon(":/img/img/arrow.png"));


    label_ind_freq = new QLabel();
    label_comb_freq = new QLabel();
    label_ind_freq->setText("<font color = "+basic_color_font+"> ind. freq.: "+to_string(_n_ind_freq).c_str());
    label_comb_freq->setText("<font color = "+basic_color_font+"> comb. freq.: "+to_string(_n_comb_freq).c_str());
    label_comb_freq->setToolTip("Number of independent frequencies");
    label_comb_freq->setToolTip("Number of combination/harmonic/subharmonic frequencies");

    QHBoxLayout *hlayout_table_button = new QHBoxLayout();
    QSplitter *splitter_table_button_H = new QSplitter(Qt::Orientation::Horizontal);
    //hlayout_table_button->addWidget(pushB_table_back);
    //hlayout_table_button->addWidget(pushB_table_forward);
    //hlayout_table_button->addWidget(label_ind_freq);
    //hlayout_table_button->addWidget(label_comb_freq);
    splitter_table_button_H->addWidget(pushB_table_back);
    splitter_table_button_H->addWidget(pushB_table_forward);
    splitter_table_button_H->addWidget(label_ind_freq);
    splitter_table_button_H->addWidget(label_comb_freq);


    //v_out_Layout->addLayout(hlayout_table_button,0);


    QSplitter *splitter_table = new QSplitter(Qt::Orientation::Vertical);
    //v_out_Layout->addWidget(splitter_table);
    splitter_main_H->addWidget(splitter_table);
    splitter_main_H->setStretchFactor(1,1);
    //splitter_main_H->setStretchFactor(2,2);
    table = new QTableWidget();
    //v_out_Layout->addWidget(table,8);

    splitter_table->addWidget(splitter_table_button_H);
    splitter_table->setStretchFactor(0,0);

    splitter_table->addWidget(table);
    splitter_table->setStretchFactor(1,8);
    table->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(table, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(table_ContextMenuRequested(const QPoint&)));
    connect(table, SIGNAL(itemSelectionChanged()), this, SLOT(table_selectionChanged()));
    connect(table, SIGNAL(currentCellChanged(int, int, int, int)),this,SLOT(table_currentItemChange(int, int, int ,int)));
    connect(table, SIGNAL(cellChanged(int,int)),this,SLOT(table_cellChanged(int,int)));

    QFont tfont;
    //tfont.setPointSize(2);
    table->setFont(tfont);
    //table->setMaximumHeight(10);
    table->resizeColumnsToContents();
    //connect(table->horizontalHeader(),SIGNAL(sectionClicked(int)), this,SLOT(selectionColumn_ud(int)));
    //connect(table->horizontalHeader(),SIGNAL(selectionPressed(int)), this,SLOT(selectionColumn_ud(int)));
    //connect(table->horizontalHeader(),SIGNAL(clicked(int)), this,SLOT(selectionColumn_ud(int)));
    //connect(table->horizontalHeader(),SIGNAL(pressed(int)), this,SLOT(selectionColumn_ud(int)));
    table->horizontalHeader()->setSelectionMode(QAbstractItemView::NoSelection);


    QSizePolicy qsp=QSizePolicy();
    qsp.setHorizontalPolicy(QSizePolicy::Maximum);
    qsp.setVerticalPolicy(QSizePolicy::Maximum);
    //table->setSizePolicy(qsp);

    info_table = new QTableWidget();
    //v_out_Layout->addWidget(info_table,5);
    splitter_table->addWidget(info_table);
    splitter_table->setStretchFactor(2,5);
    connect(info_table, SIGNAL(itemSelectionChanged()), this, SLOT(info_table_selectionChanged()));
    connect(info_table, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(info_table_doubleclicked(int,int)));
    connect(info_table->horizontalHeader(),SIGNAL(sectionClicked(int)), this,SLOT(horizontalHeaderClicked(int)));
    //info_table->horizontalHeader()->SingleSelection;

    // label info and buttons
    //pushB_trf1 = new QPushButton("fwpeaks");
    //connect(pushB_trf1,SIGNAL(clicked()),this,SLOT(get_trf_fwpeaks()));
    //button_Layout2->addWidget(pushB_trf1,0,1);

    pushB_trf_FastFourier_WS = new QPushButton("FF WS");
    connect(pushB_trf_FastFourier_WS,SIGNAL(clicked()),this,SLOT(get_trf_FastFourier_WS()));
    button_Layout2->addWidget(pushB_trf_FastFourier_WS,0,2);


    pushB_show_phase_diagram = new QPushButton("show phase diagram");
    connect(pushB_show_phase_diagram,SIGNAL(clicked()),this,SLOT(show_phase_clicked()));
    button_Layout->addWidget(pushB_show_phase_diagram,0,0);

    pushB_showPeaks = new QPushButton("show peaks");
    connect(pushB_showPeaks,SIGNAL(clicked()),this,SLOT(show_peaks_clicked()));
    button_Layout->addWidget(pushB_showPeaks,0,1);

    pushB_spec_wind_data = new QPushButton("spectral window");
    connect(pushB_spec_wind_data,SIGNAL(clicked()),this,SLOT(data_spectral_window_clicked()));
    button_Layout->addWidget(pushB_spec_wind_data,0,2);


    QLabel *label_f0 = new QLabel("<font color="+basic_color_font+">f0");
    label_f0->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    button_Layout->addWidget(label_f0,0,3);

    spinbox_f0 = new QDoubleSpinBox();
    spinbox_f0->setLocale(QLocale::C);
    spinbox_f0->setDecimals(6);
    spinbox_f0->setSingleStep(1);
    spinbox_f0->setMinimum(0);
    spinbox_f0->setMaximum(1e4);
    spinbox_f0->setValue(_f0);
    connect(spinbox_f0,SIGNAL(valueChanged(double)),this,SLOT(spinbox_setf0(double)));
    button_Layout->addWidget(spinbox_f0,0,4);



    QLabel *label_fe = new QLabel("<font color="+basic_color_font+">fe");
    label_fe->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    button_Layout->addWidget(label_fe,0,5);

    spinbox_fe = new QDoubleSpinBox();
    spinbox_fe->setLocale(QLocale::C);
    spinbox_fe->setDecimals(6);
    spinbox_fe->setSingleStep(1);
    spinbox_fe->setMinimum(0);
    spinbox_fe->setMaximum(1e4);
    //spinbox_fe->setValue(10);
    spinbox_fe->setValue(_fe);
    connect(spinbox_fe,SIGNAL(valueChanged(double)),this,SLOT(spinbox_setfe(double)));
    button_Layout->addWidget(spinbox_fe,0,6);


    QLabel *label_df = new QLabel("<font color="+basic_color_font+">df");
    label_df->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    button_Layout->addWidget(label_df,0,7);

    spinbox_df = new QDoubleSpinBox();
    spinbox_df->setLocale(QLocale::C);
    spinbox_df->setDecimals(6);
    spinbox_df->setSingleStep(0.0005);
    spinbox_df->setMinimum(0);
    spinbox_df->setMaximum(1e3);
    spinbox_df->setValue(0.001);
    connect(spinbox_df,SIGNAL(valueChanged(double)),this,SLOT(spinbox_setdf(double)));
    button_Layout->addWidget(spinbox_df,0,8);

    _f0=spinbox_f0->value();
    _fe=spinbox_fe->value();
    _df=spinbox_df->value();

    pushB_get_Noise = new QPushButton("get noise");
    connect(pushB_get_Noise,SIGNAL(clicked()),this,SLOT(pushB_calculate_noise()));
    button_Layout->addWidget(pushB_get_Noise,0,9);
    QLabel *label_noise = new QLabel("<font color="+basic_color_font+">Box width");
    label_noise->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    button_Layout->addWidget(label_noise,0,10);
    spinbox_box_width = new QDoubleSpinBox();
    spinbox_box_width->setLocale(QLocale::C);
    spinbox_box_width->setDecimals(2);
    spinbox_box_width->setSingleStep(1);
    spinbox_box_width->setMinimum(-spinbox_box_width->singleStep());
    spinbox_box_width->setMaximum(1e4);
    _box_width=2*(spinbox_fe->value()-spinbox_f0->value());
    spinbox_box_width->setValue(_box_width);
    connect(spinbox_box_width,SIGNAL(valueChanged(double)),this,SLOT(spinbox_box_width_valueChanged(double)));
    button_Layout->addWidget(spinbox_box_width,0,11);
    pushB_calculate_noise();

    button_Layout->setSpacing(1);

    detrend_Layout = new QGridLayout();
    button_Layout->addLayout(detrend_Layout,0,12,2,4);
    label_no_box = new QLabel("<font  color="+basic_color_font+">Box No.");
    label_no_box->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    detrend_Layout->addWidget(label_no_box,0,0);
    spinbox_no_box = new QSpinBox();
    spinbox_no_box->setMinimum(2);
    spinbox_no_box->setMaximum(1e4);
    spinbox_no_box->setValue(_box_number);
    connect(spinbox_no_box,SIGNAL(valueChanged(int)),this,SLOT(spinbox_no_box_valueChanged(int)));
    detrend_Layout->addWidget(spinbox_no_box,0,1);
    pushB_detrend = new QPushButton("detrend");
    connect(pushB_detrend,SIGNAL(clicked()),this,SLOT(pushB_detrend_clicked()));
    detrend_Layout->addWidget(pushB_detrend,0,2);
    pushB_restore = new QPushButton("restore");
    connect(pushB_restore,SIGNAL(clicked()),this,SLOT(pushB_restore_clicked()));
    detrend_Layout->addWidget(pushB_restore,0,3);
    /*
    slider_no_box = new  QSlider(this);
    slider_no_box->setOrientation(Qt::Horizontal);
    int nmax=50;
    int step=round((nmax*1.0-2.0)/5);
    step = 1;
    slider_no_box->setSingleStep(step);
    slider_no_box->setMinimum(2);
    slider_no_box->setMaximum(nmax);
    slider_no_box->setSliderPosition(_box_number);
    slider_no_box->setTickPosition(QSlider::TicksBelow);
    slider_no_box->setTickInterval(step*5);
    connect(slider_no_box,SIGNAL(valueChanged(int)),this,SLOT(slider_no_box_valueChanged(int)));
    //detrend_Layout->addWidget(slider_no_box,0,2,1,1);
    */
    detrend_Layout->setColumnStretch(0,0);
    detrend_Layout->setColumnStretch(1,0);
    detrend_Layout->setColumnStretch(2,0);
    detrend_Layout->setColumnStretch(3,0);

    qcpit_info = new QCPItemText(customPlot);
    qcpit_info->setText("");
    qcpit_info->setPadding(QMargins(5,5,5,5));
    qcpit_info->position->setTypeX(QCPItemPosition::ptPlotCoords);
    qcpit_info->position->setTypeY(QCPItemPosition::ptAxisRectRatio);
    qcpit_info->setPositionAlignment(Qt::AlignLeft|Qt::AlignTop);
    qcpit_info->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    qcpit_info->setClipToAxisRect(false);

    pushB_open_simulation_dialog = new QPushButton("simulation");
    connect(pushB_open_simulation_dialog,SIGNAL(clicked()),this,SLOT(pushB_open_simulation_dialog_slot()));
    button_Layout2->addWidget(pushB_open_simulation_dialog,0,0);

    pushB_fitsin = new QPushButton("Fit Sin");
    pushB_fitsin->setToolTip("Perform linear and then nonlinear fitting");
    connect(pushB_fitsin,SIGNAL(clicked()),this,SLOT(pushB_fitsin_function()));
    button_Layout2->addWidget(pushB_fitsin,0,3);
    QPalette pal = pushB_fitsin->palette();
    pal.setColor(QPalette::Button, QColor(20,20,255,80));
    pushB_fitsin->setAutoFillBackground(true);
    pushB_fitsin->setPalette(pal);
    pushB_fitsin->update();
    //pushB_fitsin->setStyleSheet("QPushButton:checked { background-color: gray; }");

    pushB_fitsin_only_lin = new QPushButton("Fit Sin OL");
    pushB_fitsin_only_lin->setToolTip("Perform ONLY linear fitting");
    connect(pushB_fitsin_only_lin,SIGNAL(clicked()),this,SLOT(fitsin_only_linear_thread_init()));
    //button_Layout2->addWidget(pushB_fitsin_only_lin,0,4);
    pushB_fitsin_only_lin->setAutoFillBackground(true);
    pushB_fitsin_only_lin->setPalette(pal);
    pushB_fitsin_only_lin->update();


    pushB_fitsin_only_nonlin = new QPushButton("Fit Sin ON");
    pushB_fitsin_only_nonlin->setToolTip("Perform ONLY nonlinear fitting");
    connect(pushB_fitsin_only_nonlin,SIGNAL(clicked()),this,SLOT(fitsin_nonlinear_thread_init()));
    //button_Layout2->addWidget(pushB_fitsin_only_nonlin,0,4);
    pushB_fitsin_only_nonlin->setAutoFillBackground(true);
    pushB_fitsin_only_nonlin->setPalette(pal);
    pushB_fitsin_only_nonlin->update();
    //pushB_fitsin_only_nonlin->setStyleSheet("QPushButton {border-style: outset;border-width: 2px;border-radius: 10px;border-color: beige;font: bold 14px;min-width: 10em;padding: 6px;}");

    QHBoxLayout *hlayout_fit_only = new QHBoxLayout();
    hlayout_fit_only->addWidget(pushB_fitsin_only_lin);
    hlayout_fit_only->addWidget(pushB_fitsin_only_nonlin);
    button_Layout2->addLayout(hlayout_fit_only,0,4);



    PushB_check_for_combination = new QPushButton("check comb.");
    connect(PushB_check_for_combination,SIGNAL(clicked()),this,SLOT(check_for_combination()));
    label_resolution_for_combination = new QLabel("<font  color="+basic_color_font+">comb. res");
    label_resolution_for_combination->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    spinBox_resolution_for_combination = new QDoubleSpinBox();
    spinBox_resolution_for_combination->setLocale(QLocale::C);
    spinBox_resolution_for_combination->setDecimals(6);
    spinBox_resolution_for_combination->setSingleStep(0.01);
    spinBox_resolution_for_combination->setMinimum(0);
    spinBox_resolution_for_combination->setMaximum(1e4);
    spinBox_resolution_for_combination->setValue(0);
    connect(spinBox_resolution_for_combination,SIGNAL(valueChanged(double)),this,SLOT(spinbox_comb_res_valueChanged(double)));
    button_Layout2->addWidget(PushB_check_for_combination,0,5);
    button_Layout2->addWidget(label_resolution_for_combination,0,6);
    button_Layout2->addWidget(spinBox_resolution_for_combination,0,7);

    pushB_auto = new QPushButton("auto");
    connect(pushB_auto,SIGNAL(clicked()),this,SLOT(auto_clicked()));
    button_Layout2->addWidget(pushB_auto,0,8);

    pushB_full_auto = new QPushButton("full auto");
    connect(pushB_full_auto,SIGNAL(clicked()),this,SLOT(full_auto_clicked()));
    button_Layout2->addWidget(pushB_full_auto,0,9);

    QHBoxLayout* hl_save_b=new QHBoxLayout();
    button_Layout2->addLayout(hl_save_b,0,10);
    pushB_save_data = new QPushButton("Save data");
    connect(pushB_save_data,SIGNAL(clicked()),this,SLOT(main_save_data_clicked()));
    //button_Layout2->addWidget(pushB_save_data,0,10);
    hl_save_b->addWidget(pushB_save_data,0);
    pushB_save_pdf = new QPushButton("Save pdf");
    connect(pushB_save_pdf,SIGNAL(clicked()),this,SLOT(main_save_pdf_clicked()));
     hl_save_b->addWidget(pushB_save_pdf,0);


    _init_layout=true;

    //to erase
    string fname="aCen_tess38_AK.txt";
    _file.init(fname,0,-1," ",true,false,true);
    if(_file.ok()){
        if(_file.file().size()>0){
            cout<<_file.head()<<endl;
            _file_loaded=true;
            if(_init_customPlotLc_ok){
                plot_lc();
                calculate_trend();
            }
        }
    }

}

void MainWindow::keyPressEvent(QKeyEvent *event){
    //cout<<"QKeyEvent "<<event->key()<<endl;
    //if( event->key() == Qt::Key_F2 ){
        //emit F2isPressed(/* some signature */); // connected elsewhere
    //}
    if( event->key() == Qt::Key_Control){
        cout<<"QKeyEvent Key_Control "<<event->key()<<endl;
        //emit signal_selection_mode(true);
        change_selection_mode(true);
        _key_control_pressed=true;
    }
    if( event->key() == Qt::Key_M){
        cout<<"QKeyEvent Key_M "<<event->key()<<endl;
        //emit signal_selection_mode(true);
        if(_show_peaks){
            add_max_peak();
        }
    }
}
void MainWindow::keyReleaseEvent(QKeyEvent *event){
    //cout<<"QKeyEvent "<<event->key()<<endl;
    //if( event->key() == Qt::Key_F2 ){
        //emit F2isPressed(/* some signature */); // connected elsewhere
    //}
    if( event->key() == Qt::Key_Control){
        cout<<"keyReleaseEvent Key_Control QKeyEvent "<<event->key()<<endl;
        //emit signal_selection_mode(true);
        change_selection_mode(false);
        _key_control_pressed=false;
        if(_markbar_ok){
        //    _markbar->setVisible(false);
            _start_point_ok=false;
        }
    }

}

void MainWindow::change_selection_mode(bool ok){
    if(_init_customPlotLc_ok){
        if(ok){
            customPlotLc->setSelectionRectMode(QCP::SelectionRectMode::srmSelect);
            _selection_mode=true;
        }else{
            customPlotLc->setSelectionRectMode(QCP::SelectionRectMode::srmNone);
            _selection_mode=false;
        }
    }
}



void MainWindow::f_convert_data(vector<double>&x,vector<double>&y,QVector<double>&qx,QVector<double>&qy){
    for(size_t i=0;i<x.size();++i){
        qx[i]=x[i];
        qy[i]=y[i];
    }
}

void MainWindow::f_convert_data(vector<double>&x,vector<double>&y,QVector<double>&qx,QVector<double>&qy,int n){
    if(x.size()>n){
        for(size_t i=0;i<n;++i){
          qx[i]=x[i];
          qy[i]=y[i];
        }
    }else{
      for(size_t i=0;i<x.size();++i){
        qx[i]=x[i];
        qy[i]=y[i];
      }
    }
}
template <class T>
void f_convert_data_ytimes(vector<T>&x,vector<T>&y,QVector<T>&qx,QVector<T>&qy, T m){
    for(size_t i=0;i<x.size();++i){
        qx[i]=x[i];
        qy[i]=y[i]*m;
    }
}
void MainWindow::calculate_trend(){
    //cout<<"detrending"<<endl;
    //cout<<"_file.ok()="<<_file.ok()<<endl;
    if(_file.ok() && _init_customPlotLc_ok){
        if( !detrended_ok || (detrended_current_nbox!=_box_number && detrended_ok) ){
            //cout<<"  detrending 2"<<endl;
            vector<double> x=f_get_column(_file.file(),_file.head(),"1");
            vector<double> y=f_get_column(_file.file(),_file.head(),"2");
            size_t n=x.size();
            if(n>0){
                if(_box_number>n){
                    _box_number=n;
                    cout<<"to small number of data point or to large nbumber of boxes"<<endl;
                    cout<<"n="<<n<<" _box_number="<<_box_number<<endl;
                }
                vector<T>xb,yb;
                int nb=ceil(n*1.0/(_box_number*1.0));
                //cout<<"nb="<<nb<<endl;
                int i0=0;
                int iabs=0;
                for(size_t i=0;i<_box_number;++i){
                   double xbt=0;
                   double ybt=0;
                   int iperbox=0;
                   for(size_t j=0;j<nb;++j){
                      if(iabs<n){
                         xbt+=x[iabs];
                         ybt+=y[iabs];
                         ++iperbox;
                         ++iabs;
                      }else{
                         break;
                      }
                   }
                   xb.push_back(xbt/(1.0*iperbox));
                   yb.push_back(ybt/(1.0*iperbox));
                   i0+=nb;
                   //cout<<"i="<<i<<" iperbox="<<iperbox<<endl;
                   if(iabs>=n-1){
                       _box_number=i+1;
                       //ui->lineEdit->setText(to_string(_box_number).c_str());
                       //ui->horizontalSlider->setSliderPosition(_box_number);
                       break;
                   }
                }
                //cout<<"xb="<<xb<<endl;
                //cout<<"yb="<<yb<<endl;
                //cout<<"iabs="<<iabs<<" n="<<n<<endl;
                //QCPLayer *layertrendpoints= new ui->customPlotLc->layer;
                if(_ind_graph_lc_detrend_points==-1){
                    _ind_graph_lc_detrend_points=customPlotLc->graphCount();
                    string name="trendpoints";
                    if(customPlotLc->layer(name.c_str())==nullptr){
                        customPlotLc->addLayer(name.c_str());
                    }
                    customPlotLc->addGraph();
                    customPlotLc->graph(_ind_graph_lc_detrend_points)->setLayer(name.c_str());
                }
                //customPlotLc->graph(_ind_graph_lc_detrend_points)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, Qt::blue,QColor(250,10,10), 10));
                customPlotLc->graph(_ind_graph_lc_detrend_points)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QColor(lc_line_color),QColor(lc_detrend_point_color), 10));
                customPlotLc->graph(_ind_graph_lc_detrend_points)->setLineStyle(QCPGraph::lsNone);
                QVector<double> qx(_box_number),qy(_box_number);
                f_convert_data(xb,yb,qx,qy,_box_number);
                customPlotLc->graph(_ind_graph_lc_detrend_points)->setData(qx,qy);
                customPlotLc->graph(_ind_graph_lc_detrend_points)->setSelectable(QCP::stMultipleDataRanges);
                customPlotLc->graph(_ind_graph_lc_detrend_points)->setSelectable(QCP::stNone);
                QPen selectedpen;
                selectedpen.setStyle(Qt::SolidLine);
                selectedpen.setWidth(3);
                selectedpen.setColor(QColor(180,180,180));
                customPlotLc->graph(_ind_graph_lc_detrend_points)->selectionDecorator()->setPen(selectedpen);
                customPlotLc->graph(_ind_graph_lc_detrend_points)->selectionDecorator()->setScatterStyle(QCPScatterStyle::ssSquare);
                customPlotLc->graph(_ind_graph_lc_detrend_points)->selectionDecorator()->setBrush(QColor(180,180,180,50));
                customPlotLc->graph(_ind_graph_lc_detrend_points)->removeFromLegend();
                //spline.help();
                string interp_type="akima";
                string opt="sort";
                opt="check_edges_and_reverse";
                detrend_spline.init(xb,yb);
                detrend_spline.cspline(interp_type,opt);
                QVector<double>qxs(n),qys(n);
                for(size_t i=0;i<n;++i){
                    qxs[i]=x[i];
                    qys[i]=detrend_spline.e(x[i]);
                }
                if(_ind_graph_lc_detrend_inter==-1){
                    _ind_graph_lc_detrend_inter=customPlotLc->graphCount();
                    string name="trendspline";
                    if(customPlotLc->layer(name.c_str())==nullptr){
                        customPlotLc->addLayer(name.c_str());
                    }
                    customPlotLc->addGraph();
                    customPlotLc->graph(_ind_graph_lc_detrend_inter)->setLayer(name.c_str());
                }
                //customPlotLc->graph(_ind_graph_lc_detrend_inter)->setLineStyle((QCPGraph::LineStyle)1);
                QPen pen;
                //pen.setStyle(Qt::DotLine);
                pen.setStyle(Qt::SolidLine);
                pen.setWidthF(1);
                pen.setColor(QColor(250, 20, 20));
                pen.setColor(QColor(lc_detrend_line_color));
                customPlotLc->graph(_ind_graph_lc_detrend_inter)->setPen(pen);
                customPlotLc->graph(_ind_graph_lc_detrend_inter)->setData(qxs,qys);
                customPlotLc->graph(_ind_graph_lc_detrend_inter)->selectionDecorator()->setPen(selectedpen);
                customPlotLc->graph(_ind_graph_lc_detrend_inter)->setSelectable(QCP::stNone);
                //ui->pushButton_9->setText( ("restore ("+to_string(spline.size())+")").c_str());
                QCPLayer *l = customPlotLc->layer("trendspline");
                customPlotLc->moveLayer(l, customPlotLc->layer(customPlotLc->layerCount()-1));
                QCPLayer *lp = customPlotLc->layer("trendpoints");
                customPlotLc->moveLayer(lp, customPlotLc->layer(customPlotLc->layerCount()-1));
                customPlotLc->graph(_ind_graph_lc_detrend_inter)->setName("trend");
                customPlotLc->replot();
                detrended_ok=true;
                detrended_current_nbox=_box_number;
                already_added=false;
            }
        }else{
            cout<<"a new detrending not applied"<<endl;
        }
    }else{
       cout<<"problem with input data"<<endl;
    }
}

void MainWindow::pushB_calculate_noise(){
    if(_noise_ok){
        _noise.clear();
        _noise_ok=false;
        if(_ind_graph_noise!=-1){
            if(_ind_graph_peaks_fwpeaks>_ind_graph_noise_sn5){
                _ind_graph_peaks_fwpeaks-=3;
            }

            customPlot->removeGraph(_ind_graph_noise_sn5);
            customPlot->removeGraph(_ind_graph_noise_sn4);
            customPlot->removeGraph(_ind_graph_noise);
            _ind_graph_noise_sn5=-1;
            _ind_graph_noise_sn4=-1;
            _ind_graph_noise=-1;
            customPlot->replot();
            pushB_get_Noise->setText("get noise");

        }

    }else{
        calculate_noise();
        plot_noise();
        if(_noise_ok){
           pushB_get_Noise->setText("hide noise");
        }
    }
}

void MainWindow::calculate_noise(){
    //cout<<"calculate_noise"<<endl;
    if(_fr.size()>0){
       _noise_ok=true;

       //cout<<"_xmax="<<_xmax<<" _xmin="<<_xmin<<endl;
       if(_box_width>2*abs(_fe-_f0)){
          _box_width=abs(0);
          spinbox_box_width->setValue(_box_width);
       }
       if(_box_width<0){
          _box_width=2*abs(_fe-_f0);
          spinbox_box_width->setValue(_box_width);
       }

       /*
       vector<double>xn;
       vector<double>yn;
       for(size_t i=0;i<_fr.size();++i){
          xn.push_back(_fr[i]);
          yn.push_back(_ampl[i]);
       }
       /*
       if(xn.size()>0){
         if(xn[0]==0){
            for(int i=1;i<_n;++i){
               if(xn[i]<xn[0]+_box_width){
                   //cout<<"i="<<i<<endl;
                   xn.push_back(-xn[i]);
                   yn.push_back(yn[i]);
                   qx2a.push_back(-xn[i]);
                   qy2a.push_back(yn[i]);
               }else{
                   break;
               }
            }
         }
       }*/
       /*
       int n=(int)xn.size();

       cout<<"noise:"<<endl;
       double dx=_box_width/2.0;
       Box box(xn,yn,dx);

       _noise.resize(n);
       box.init(xn[0]);
       cout<<"init ok"<<endl;
       for(int i=0;i<n;++i){
           //cout<<i<<endl;
           box.refresh(xn[i]);
           _noise[i]=box.Sum()/box.np();
       }
       */
       int n=_fr.size();
       double dx=_box_width/2.0;
       Box box(_fr,_ampl,dx);
       _noise.resize(n);
       box.init(_fr[0]);
       //cout<<"Box init ok"<<endl;
       for(int i=0;i<n;++i){
           box.refresh(_fr[i]);
           _noise[i]=box.Sum()/box.np();
           //cout<<i<<" "<<_noise[i]<<" "<<_fr[i]<<endl;
       }
       //cout<<"noise="<<_noise<<endl;

       spline_noise.init(_fr,_noise);
       spline_noise.cspline("akima","check_edges_and_reverse");
    }
}

void MainWindow::plot_noise(){
    int n=_noise.size();
    if(n>0){
       QVector<double> qxn(n), qyn(n);
       f_convert_data(_fr,_noise,qxn,qyn);
       //cout<<"_customPlot->graphCount()" <<ui->customPlot->graphCount()<<endl;
       if(_ind_graph_noise==-1){
           _ind_graph_noise=customPlot->graphCount();
           customPlot->addGraph();
       }
       customPlot->graph(_ind_graph_noise)->setData(qxn, qyn);
       //ui->customPlot->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1.5), QBrush(Qt::white), 9));
       //ui->customPlot->graph(2)->setPen(QPen(QColor(120, 120, 120), 2));
       QPen pen3;
       //pen.setStyle(Qt::DotLine);
       pen3.setStyle(Qt::SolidLine);
       pen3.setWidthF(2);
       pen3.setColor(QColor(25,25, 10));
       customPlot->graph(_ind_graph_noise)->setPen(pen3);
       customPlot->graph(_ind_graph_noise)->setName("noise");
       customPlot->graph(_ind_graph_noise)->setSelectable(QCP::stNone);
       QVector<double> qxn4(n), qyn4(n);
       f_convert_data_ytimes(_fr,_noise,qxn,qyn,4.0);
       if(_ind_graph_noise_sn4==-1){
           _ind_graph_noise_sn4=customPlot->graphCount();
           customPlot->addGraph();
       }
       customPlot->graph(_ind_graph_noise_sn4)->setData(qxn, qyn);
       pen3.setColor(QColor(150,25, 10));
       pen3.setWidthF(1);
       customPlot->graph(_ind_graph_noise_sn4)->setPen(pen3);
       customPlot->graph(_ind_graph_noise_sn4)->setName("noise x4");
       customPlot->graph(_ind_graph_noise_sn4)->setSelectable(QCP::stNone);
       QVector<double> qxn5(n), qyn5(n);
       f_convert_data_ytimes(_fr,_noise,qxn,qyn,5.0);
       if(_ind_graph_noise_sn5==-1){
           _ind_graph_noise_sn5=customPlot->graphCount();
           customPlot->addGraph();
       }
       customPlot->graph(_ind_graph_noise_sn5)->setData(qxn, qyn);
       pen3.setColor(QColor(150,125, 10));
       pen3.setWidthF(0.8);
       customPlot->graph(_ind_graph_noise_sn5)->setPen(pen3);
       customPlot->graph(_ind_graph_noise_sn5)->setName("noise x5");
       customPlot->graph(_ind_graph_noise_sn5)->setSelectable(QCP::stNone);
       customPlot->replot();
    }
}

void MainWindow::spinbox_box_width_valueChanged(double k){
     if(spinbox_box_width->value()!=_box_width){
         _box_width=k;
         if(_noise_ok){
            calculate_noise();
            plot_noise();
         }
     }

}



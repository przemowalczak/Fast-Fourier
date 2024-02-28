#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMetaType>
#include "lib/qcustomplot.h"
#include <QPushButton>
#include <QTextTable>
#include <QListView>
#include <QListWidget>
#include <QTableView>
#include <QColumnView>
#include <QTableWidget>
#include <QTableWidgetItem>

#include <gsl/gsl_fit.h>
#include <gsl/gsl_multifit.h>
#include <gsl/gsl_multifit_nlinear.h>
#include <gsl/gsl_blas.h>


#include "lib/operators_pwh.hpp"
#include "lib/klunkry_pwh.hpp"
#include "lib/box_pwh.hpp"
#include "lib/sort_pwh.hpp"
#include "lib/histogram_pwh.hpp"
#include "lib/stat_pwh.hpp" //require  sort_pw.hpp, <gsl/gsl_cdf.h>
#include "lib/read_file_pwh.hpp"
#include "lib/fwpeaks.hpp"
#include "lib/gsl_spline_v3_pwh.hpp"

#include "simstat.h"

#include "lib/fast_LS.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


/*
class Worker : public QObject {
    Q_OBJECT

public:
    Worker();
    ~Worker();

    string name="it0";

public slots:
    void process();
signals:
    void finished();
private:
    // add your variables here
};*/

class Worker_data_out{
public:
    double _A0;
    double _sA0;
    vector<double>_f;
    vector<double>_sf;
    vector<double>_A;
    vector<double>_sA;
    vector<double>_phi;
    vector<double>_sphi;
    int p0=0;
    int nreallyfitted=-1;
    double chisqrt;
    string status;
    int iteration;
};
Q_DECLARE_METATYPE(Worker_data_out)



class Worker_data_out_linear{
public:
    double _A0_lin;
    double _sA0_lin;
    vector<double>_A_lin;
    vector<double>_phi_lin;
    vector<double>_sA_lin;
    vector<double>_sphi_lin;
    int p0=0;
    double chisqrt;
};
Q_DECLARE_METATYPE(Worker_data_out_linear)



class Worker : public QThread{
    Q_OBJECT
public slots:
    void doWork(const QString &parameter);
    //void doWork();
    //void run() override;
signals:
    void resultReady(Worker_data_out results);
//private:
//    void make_reduced_ind_ind();

public:
    vector<double>freq_i;
    vector<double>freq_all;
    vector<double>freq_c;
    vector<vector<double> >_freq_matrix;
    cl_read_file *_file;
    gsl_multifit_nlinear_parameters fdf_params;
    vector<bool> ind_ind;
    vector<double> _A_lin;
    vector<double> _phi_lin;
    vector<double> _A;
    vector<double> _phi;
    int nmaxfittet=-1;
    int nreallyfitted=0;
    double A0;
    int NLSF_max_iteration=100;
    double _T0;

};


class Worker_linear : public QThread{
    Q_OBJECT
public slots:
    void doWork(const QString &parameter);
    //void doWork();
    //void run() override;
signals:
    void resultReady_linear(Worker_data_out_linear results);
//private:
//    void make_reduced_ind_ind();

public:
    vector<double>freq_i;
    vector<double>freq_all;
    vector<double>freq_c;
    cl_read_file *_file;
    vector<bool> ind_ind;
    vector<double> _A_lin;
    vector<double> _phi_lin;
    double A0_lin;
    double _T0;


};


class Frequency_manager{
private:
    vector<vector<double> > _matrix;
    vector<double> _frequencies;
    vector<bool> _is_independent;
    vector<int>_entries;
    vector<vector<int> >_entries_v;
    vector<int> independent_index;
    vector<int> independent_general_index;

    int _nfreq=_frequencies.size();
    int _nmatrix=_matrix.size();

public:
    void set_martix(vector<vector<double> >&matrix);
    void set_frequencies(vector<double>&frequencies);
    void analyse();
    bool is_independent(int ind);
    vector<int> children(int ind);
    vector<int> parents(int ind);
    int index_of_independent_freq(int ind);


};


class MainWindow : public QMainWindow{
    Q_OBJECT


//private:
//    Worker *worker;
public slots:
    void handleResults(const Worker_data_out );
    void handleResults_linear(const Worker_data_out_linear );
signals:
    void operate(const QString &);
    void operate_linear(const QString &);
    //void operate();
private:
    void fitsin_nonlinear_thread();
    QThread workerThread;
    void fitsin_linear_thread();
    QThread workerThread_linear;

    Frequency_manager frequency_manager;

private slots:
    void fitsin_nonlinear_thread_init();
    void fitsin_linear_thread_init();

private:
    void init();
    void init_data();
    void clearLayout(QLayout* layout, bool deleteWidgets);

private:
    void set_defaults();
    bool _init_layout=false;
    QFileDialog dialog_open_file;
    cl_read_file _file;
    QCustomPlot *customPlot;
    void init_customPlot(string xlabel="",string ylabel="");
    QCustomPlot *customPlotLc;
    void init_customPlotLc(string xlabel="",string ylabel="");
    vector<double> _key_selected;
    vector<double> _value_selected;
    QCustomPlot *customPlotLc_residuals;
    void init_customPlotLc_residuals(string xlabel="",string ylabel="");
    void init_customPlot_simulation(string xlabel="",string ylabel="");
    bool _init_customPlot_simulation_ok=false;

    QVBoxLayout* v_main_Layout;
    QHBoxLayout* h_main_Layout;
    QVBoxLayout* v_CP_Layout;
    QVBoxLayout* v_out_Layout;
    QGridLayout* button_Layout;
    QGridLayout* button_Layout2;

    QPushButton* pushB_trf1;
    QPushButton* pushB_trf_FastFourier_WS;
    int _chosen_trf=0;

    QLabel *label_info;
    QLabel *label_info_fitting;
    QLabel *label_info_fitting2;

    QPushButton* pushB_spec_wind_data;
    bool _use_data=true;
    vector<double> _data_file_copy;
    vector<double> _e_data_file_copy;
    bool _copy_residuals_ok=false;


    bool _fit_linear_only=false;

    double _time_start_linear_thread=0;
    double _time_stop_linear_thread=0;
    double _time_start_nonlinear_thread=0;
    double _time_stop_nonlinear_thread=0;

    QString basic_color_font="orange";
    QString NLSF_info_color_font="red";
    QString trf_line_color="blue";
    int trf_line_width=1;
    QString pushB_border_color="beige";
    QString pushB_background_color="white";
    QString lc_line_color="blue";
    QString lc_point_color="green";
    QString lc_detrend_point_color="red";
    QString lc_detrend_line_color="red";
    QString lc_fitted_line_color="yellow";
    QString table_color_selection_background="blue";
    QString table_color_selection_background_children="red";
    QString table_color_selection_background_parents="green";
    QColor main_background_color="black";

    void table_changed(int ind,int opt);

    QCPBars* simulation_bar;
    vector<double>SN;
    vector<double>SNfr;
    vector<double>SNAmpl;
    vector<double>SNsn;

    bool _selection_mode=false;
    double f_min(vector<double>&v);
    double f_max(vector<double>&v);

    QDialog *dialog_NLSF;
    QGridLayout *dialog_NLSF_layout;
    bool _combo_settings_action_NLSF_dialog_init=false;
    QRadioButton *radio_NLSF_1;
    QRadioButton *radio_NLSF_2;
    QRadioButton *radio_NLSF_3;
    QRadioButton *radio_NLSF_4;
    string _NLSF_solver="cholesky";
    QRadioButton *radio_NLSF_trs_1;
    QRadioButton *radio_NLSF_trs_2;
    QRadioButton *radio_NLSF_trs_3;
    QRadioButton *radio_NLSF_trs_4;
    QRadioButton *radio_NLSF_trs_5;
    QSpinBox *spinB_NLSF_maxiter;


    QDialog *dialog_General;
    QGridLayout *dialog_General_layout;
    bool _combo_settings_action_General_dialog_init=false;
    int _General_n_last_freq=-1;
    QSpinBox *spinB_General_nfreq;
    QSpinBox *spinB_General_n_s;
    int _General_n_s=10;
    QSpinBox *spinB_General_n_h;
    int _General_n_h=10;
    QSpinBox *spinB_General_n_c2_1;
    QSpinBox *spinB_General_n_c2_2;
    int _General_n_c2_1=10;
    int _General_n_c2_2=10;
    QSpinBox *spinB_General_n_c3_1;
    QSpinBox *spinB_General_n_c3_2;
    QSpinBox *spinB_General_n_c3_3;
    int _General_n_c3_1=10;
    int _General_n_c3_2=10;
    int _General_n_c3_3=10;
    QRadioButton *radio_General_use_combination;
    QRadioButton *radio_General_use_independent;
    QDoubleSpinBox *spinB_General_auto_stop_crit_SN;
    double _crit_stop=5;
    bool _use_highest_peaks=true;


    int _n_peaks=5;
    int _ind_graph_peaks_fwpeaks=-1;
    vector<QCPItemText*> Textpeaks;
    QPushButton *pushB_showPeaks;
    bool _show_peaks=false;
    void get_peaks();


    bool _key_control_pressed=false;

    QPushButton *pushB_auto;
    QPushButton *pushB_full_auto;
    bool _full_auto=false;
    int _iter_auto=0;
    bool _use_first_combination=false;


    bool _skipp_peaks_closer_than_resolution=false;
    bool is_closer_than_freqs_from_table(double freq);
    double _resolution=0.01;
    QRadioButton *radio_General_use_all_peaks;
    QRadioButton *radio_General_use_selected_peaks;
    QDoubleSpinBox *_skipp_peaks_resolution;    
    QRadioButton *radio_General_use_h_peaks;
    QRadioButton *radio_General_use_h_SN;


    int _NLSF_max_iteration=150;
    QPushButton *pushB_save_data;
    QPushButton *pushB_save_pdf;
    double _T0=0;

    QSplitter *splitter;

    QPushButton *pushB_show_phase_diagram;
    QCustomPlot *customPlot_phase;
    bool _init_customPlot_phase=false;
    void init_customPlot_phase(string xlabel="",string ylabel="");
    void plot_phase_diagram();
    bool _residuals_old_ok=false;
    int _ind_graph_lc_phase=-1;
    double _xmin_Lc_phase;
    double _xmax_Lc_phase;
    double _ymin_Lc_phase;
    double _ymax_Lc_phase;

private slots:
    void show_phase_clicked();
    void get_phase_diagram();
    void data_spectral_window_clicked();
    void simulation_analyse(int);

private slots:
    void combo_settings_action_General_clicked();
    void spinB_General_nfreq_changed(int);
    void spinB_General_n_s_changed(int);
    void spinB_General_n_h_changed(int);
    void spinB_General_n_c2_1_changed(int);
    void spinB_General_n_c2_2_changed(int);
    void spinB_General_n_c3_1_changed(int);
    void spinB_General_n_c3_2_changed(int);
    void spinB_General_n_c3_3_changed(int);
    void spinB_NLSF_maxiter_changed(int);
    void radio_General_use_h_peaks_changed(bool);
    void radio_General_use_h_SN_changed(bool);


    void spinB_General_auto_stop_crit_SN_changed(double);

    void show_peaks();
    void hide_peaks();
    void show_peaks_clicked();
    void add_max_peak();

    void auto_clicked();
    void full_auto_clicked();

    void radio_General_use_combination_changed(bool);
    void radio_General_use_independent_changed(bool);
    void radio_General_use_all_peaks_changed(bool);
    void radio_General_use_selected_peaks_changed(bool);
    void skipp_peaks_resolution_changed(double);

    void main_save_data_clicked();
    void main_save_pdf_clicked();

private:

    void f_convert_data(vector<double>&x,vector<double>&y,QVector<double>&qx,QVector<double>&qy);
    void f_convert_data(vector<double>&x,vector<double>&y,QVector<double>&qx,QVector<double>&qy,int n);

    //cuctomPlot
    bool first_lc=true;
    string first_lc_add="";
    bool _init_customPlot_ok=false;
    double _xmin;
    double _xmax;
    double _ymin;
    double _ymax;
    vector<double>_fr;
    vector<double>_ampl;
    vector<double>_noise;
    vector<double> _frpeaks;
    vector<double> _amplpeaks;
    vector<double> _Ppeaks;
    vector<double> _SNpeaks;
    int _ind_graph_noise_sn4=-1;
    int _ind_graph_noise_sn5=-1;
    int _ind_graph_trf=-1;
    int _ind_graph_line=-1;
    bool _trf_ok=false;
    double _box_width=-1;
    bool _noise_ok=false;
    int _ind_graph_noise=-1;
    bool _log_scale_y=false;
    QCPItemTracer* trfTracer;
    bool _linebar_ok=false;
    QCPBars* linebar;
    QCPItemText* qcpit_info;
    QDoubleSpinBox* spinbox_f0;
    QDoubleSpinBox* spinbox_fe;
    QDoubleSpinBox* spinbox_df;
    double _f0=0;
    double _fe=10;
    double _df=0.001;
    cl_spline spline_noise;
    bool _resize_x_axix=true;
    bool _resize_y_axix=true;

    QStatusBar *simulation_statusBar;
    QSlider *simulation_slider;
    QSpinBox *simulation_SpinBox;

private slots:
    void set_const_xAxis();
    void set_rescale_xAxis();
    void trf_save_trf();
    void simulation_spinBox_changed(int);
    void simulation_slider_changed(int);


private:
    //cuctomPlotLc
    bool _init_customPlotLc_ok=false;
    bool _file_loaded=false;
    int _ind_graph_lc=-1;
    double _xmin_Lc;
    double _xmax_Lc;
    double _ymin_Lc;
    double _ymax_Lc;
    double _dT;
    vector<double> data_for_removing_x;
    vector<double> data_for_removing_y;
    int _box_number=10;
    int _ind_graph_lc_detrend_points=-1;
    int _ind_graph_lc_detrend_inter=-1;
    cl_spline detrend_spline;
    bool detrended_ok=false;
    vector<cl_spline> detrend_splines;
    int detrended_current_nbox=-1;
    bool already_added=false;
    QCPErrorBars *ErrorBars;

    QPushButton *pushB_fitsin;
    QPushButton *pushB_fitsin_only_nonlin;
    QPushButton *pushB_fitsin_only_lin;
    private slots:
    void pushB_fitsin_function();
    void fitsin_function();
    void get_residuals();
    void add_fitted_curve();
    void fitsin_only_linear_thread_init();



private:

     double _A0_lin;
     double _sA0_lin;
     vector<double> _A_lin;
     vector<double> _sA_lin;
     vector<double> _phi_lin;
     vector<double> _sphi_lin;
     vector<double> _residuals;
     vector<double> _residuals_old;
     vector<double> _phase;
     QCPErrorBars *ErrorBars_phase;
     vector<double> _fitted_curve;
     bool _residuals_ok=false;
     bool _fitted_curve_ok=false;
     int _ind_graph_fitted_curve_lc=-1;
     bool _init_customPlotLc_residuals_ok=false;
     int _ind_graph_lc_residuals=-1;
     double _xmin_Lc_residuals;
     double _xmax_Lc_residuals;
     double _ymin_Lc_residuals;
     double _ymax_Lc_residuals;
     QCPErrorBars *ErrorBars_residuals;
     double _A0;
     double _sA0;
     vector<double> _A;
     vector<double> _sA;
     vector<double> _phi;
     vector<double> _sphi;
     vector<double> _f;
     vector<double> _sf;



     //buttons
     QLabel* label_no_box;
     QSpinBox* spinbox_no_box;
     QPushButton* pushB_detrend;
     QPushButton* pushB_restore;
     QSlider* slider_no_box;
     QGridLayout* detrend_Layout;
     QPushButton* pushB_get_Noise;
     QDoubleSpinBox* spinbox_box_width;

     //simulation
     QPushButton *pushB_open_simulation_dialog;
     QDialog *dialog_simulation;
     QPushButton *pushB_start_simulation;
     bool _dialog_simulation_ok=false;
     QGridLayout *simulation_dialog_layout;
     QSpinBox* spinbox_simulationNO;
     QSpinBox* spinbox_simulation_sigma;
     QRadioButton* radioB_plot_interactively_no;
     QRadioButton* radioB_plot_interactively_yes;
     SimStat* simstatMW;
     QCustomPlot* simstst_customPlotsn;
     QCustomPlot* simstst_customPlotf;
     QRadioButton* radioB_hlayout_trf_fwpeaks;
     QRadioButton* radioB_hlayout_trf_FF;
     QLabel *simulation_label;
     QCustomPlot *customPlot_simulation;


     int CP_Layout_width=5;
     int out_Layout_width=4;


     int _n_ind_freq=0;
     int _n_comb_freq=0;
     void update_freq_number();
     void get_freq_number();

     void update_frequency_manager();


     //table
     vector<QTableWidget*> table_backup;
     int max_table_backup=5;
     void copy_table_to_backup();
     QPushButton *pushB_table_back;
     QPushButton *pushB_table_forward;
     QLabel *label_ind_freq;
     QLabel *label_comb_freq;
     QTableWidget *table;
     QTableWidget* info_table;
     int _table_back_iter=0;
     vector<QTableWidget*> Vtable;
     vector<double> _freq;
     vector<double> _signal;
     void add_freq_to_table(double f,double sn);
     void init_freq_table();
     void init_info_table();
     bool pushB_start_simulation_ok=false;
     vector<vector<double> >_freq_matrix;
     void update_matrix();
     QList<QTableWidgetItem*> takeRow(int row);
     void setRow(int row, const QList<QTableWidgetItem*>& rowItems);
     int _info_table_column_sort=2;
     bool _info_table_column_sort_ascending=true;
     bool info_table_compare_1c(QString c1,QString c2);
     bool info_table_sorting=false;

     bool _cell_changed_triggered_by_selection_change=false;
     bool _cell_selection_triggered_by_horizontalheader=false;

     QPushButton *PushB_check_for_combination;
     QLabel *label_resolution_for_combination;
     QDoubleSpinBox *spinBox_resolution_for_combination;
     double _resolution_for_combination=0;
     void update_table_status(double freq, QString text);
     void update_table_status(QString text);
     double _resolution_for_combination_factor=0.25;
     double _resolution_for_combination_step=0.25;

     void fitsin_linear();
     void fitsin_nonlinear();


     double _start_point;
     bool _start_point_ok=false;
     void plot_bar(double x0, double xe);
     bool _markbar_ok=false;
     QCPBars* _markbar;
     void get_half_width(double x0, double xe);
     vector<double>_half_width;
     vector<double> _midx;

private slots:
     void check_for_combination();
     void info_table_selectionChanged();
     void spinbox_comb_res_valueChanged(double);
     void info_table_doubleclicked(int,int);
     void table_cellChanged(int,int);
     void horizontalHeaderClicked(int);
     void sort_info_table();
     void table_back_clicked();
     void table_forward_clicked();

     void selectionColumn_ud(int icol);

     //QTableWidget *table;

private slots:
    void resizeEvent(QResizeEvent* event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void open_file();
    void exit();
    void help();
    void reset();
    void plot_lc();
    void change_selection_mode(bool);
    void calculate_trend();
    void spinbox_no_box_valueChanged(int);
    void slider_no_box_valueChanged(int);
    void pushB_detrend_clicked();
    void pushB_restore_clicked();
    void plot_trf();
    void calculate_noise();
    void pushB_calculate_noise();
    void plot_noise();
    void spinbox_box_width_valueChanged(double);
    void plot_line(double x);
    void spinbox_setf0(double);
    void spinbox_setfe(double);
    void spinbox_setdf(double);
    void pushB_open_simulation_dialog_slot();
    void pushB_start_simulation_slot();
    void pushB_start_simulation_slot_graph();
    void pushB_start_simulation_slot_nograph();
    void table_ContextMenuRequested(const QPoint&);
    void table_selectionChanged();
    void table_currentItemChange(int, int, int ,int);
    void table_remove_last_row();
    void table_remove_this_row();
    void table_remove_all_rows();
    void table_save_data();
    void plot_lc_residuals();
    void combo_settings_action_NLSF_clicked();

private:
    bool xrplot=false;
    bool yrplot=false;

private slots:
    //button slots
    void get_trf_fwpeaks();
    void get_trf_FastFourier_WS();

    void update_sn();



private slots:
    //standard customPlot slots
    void titleDoubleClick(QMouseEvent *event);
    void axisLabelDoubleClick(QCPAxis* axis, QCPAxis::SelectablePart part);
    void legendDoubleClick(QCPLegend* legend, QCPAbstractLegendItem* item);
    void selectionChanged();
    void mousePress(QMouseEvent* event);
    void mouseDoubleClick(QMouseEvent *event);
    void mouseWheel();
    void removeSelectedGraph();
    void removeAllGraphs();
    void contextMenuRequest(QPoint pos);
    void moveLegend();
    void graphClicked(QCPAbstractPlottable *plottable, int dataIndex);
    void graphDoubleClicked(QCPAbstractPlottable*plottable,int dataIndex);
    void onMouseMove(QMouseEvent *event);
    void mouseRelease(QMouseEvent* event);
    void clear_selected_data();
    void reverse_xAxis();
    void reverse_yAxis();
    void savepdf();
    void set_logscale_yAxis();


    //standard customPlotLc slots
    void titleDoubleClickLc(QMouseEvent *event);
    void axisLabelDoubleClickLc(QCPAxis* axis, QCPAxis::SelectablePart part);
    void legendDoubleClickLc(QCPLegend* legend, QCPAbstractLegendItem* item);
    void selectionChangedLc();
    void mousePressLc(QMouseEvent* event);
    void mouseDoubleClickLc(QMouseEvent *event);
    void mouseWheelLc();
    void removeSelectedGraphLc();
    void removeAllGraphsLc();
    void contextMenuRequestLc(QPoint pos);
    void moveLegendLc();
    void graphClickedLc(QCPAbstractPlottable *plottable, int dataIndex);
    void graphDoubleClickedLc(QCPAbstractPlottable*plottable,int dataIndex);
    void onMouseMoveLc(QMouseEvent *event);
    void mouseReleaseLc(QMouseEvent* event);
    void clear_selected_dataLc();
    void reverse_xAxisLc();
    void reverse_yAxisLc();
    void savepdfLc();
    void remove_selected_data();
    void lc_save_lc();

    //standard customPlotLc_residuals slots
    void titleDoubleClickLc_residuals(QMouseEvent *event);
    void axisLabelDoubleClickLc_residuals(QCPAxis* axis, QCPAxis::SelectablePart part);
    void legendDoubleClickLc_residuals(QCPLegend* legend, QCPAbstractLegendItem* item);
    void selectionChangedLc_residuals();
    void mousePressLc_residuals(QMouseEvent* event);
    void mouseDoubleClickLc_residuals(QMouseEvent *event);
    void mouseWheelLc_residuals();
    void removeSelectedGraphLc_residuals();
    void removeAllGraphsLc_residuals();
    void contextMenuRequestLc_residuals(QPoint pos);
    void moveLegendLc_residuals();
    void graphClickedLc_residuals(QCPAbstractPlottable *plottable, int dataIndex);
    void graphDoubleClickedLc_residuals(QCPAbstractPlottable*plottable,int dataIndex);
    void onMouseMoveLc_residuals(QMouseEvent *event);
    void mouseReleaseLc_residuals(QMouseEvent* event);
    void clear_selected_dataLc_residuals();
    void reverse_xAxisLc_residuals();
    void reverse_yAxisLc_residuals();
    void savepdfLc_residuals();
    void remove_selected_dataLc_residuals();
    void resid_save_resid();

    //standard customPlot_phase slots
    void titleDoubleClickLc_phase(QMouseEvent *event);
    void axisLabelDoubleClickLc_phase(QCPAxis* axis, QCPAxis::SelectablePart part);
    void legendDoubleClickLc_phase(QCPLegend* legend, QCPAbstractLegendItem* item);
    void selectionChangedLc_phase();
    void mousePressLc_phase(QMouseEvent* event);
    void mouseDoubleClickLc_phase(QMouseEvent *event);
    void mouseWheelLc_phase();
    void removeSelectedGraphLc_phase();
    void removeAllGraphsLc_phase();
    void contextMenuRequestLc_phase(QPoint pos);
    void moveLegendLc_phase();
    void graphClickedLc_phase(QCPAbstractPlottable *plottable, int dataIndex);
    void graphDoubleClickedLc_phase(QCPAbstractPlottable*plottable,int dataIndex);
    void onMouseMoveLc_phase(QMouseEvent *event);
    void mouseReleaseLc_phase(QMouseEvent* event);
    void clear_selected_dataLc_phase();
    void reverse_xAxisLc_phase();
    void reverse_yAxisLc_phase();
    void savepdfLc_phase();
    void remove_selected_dataLc_phase();
    void phase_save_phase();

    //standard customPlot_simulation slots
    void titleDoubleClick_simulation(QMouseEvent *event);
    void axisLabelDoubleClick_simulation(QCPAxis* axis, QCPAxis::SelectablePart part);
    void legendDoubleClick_simulation(QCPLegend* legend, QCPAbstractLegendItem* item);
    void selectionChanged_simulation();
    void mousePress_simulation(QMouseEvent* event);
    void mouseDoubleClick_simulation(QMouseEvent *event);
    void mouseWheel_simulation();
    void removeAllGraphs_simulation();
    void contextMenuRequest_simulation(QPoint pos);
    void moveLegend_simulation();
    void graphClicked_simulation(QCPAbstractPlottable *plottable, int dataIndex);
    void graphDoubleClicked_simulation(QCPAbstractPlottable*plottable,int dataIndex);
    void onMouseMove_simulation(QMouseEvent *event);
    void mouseRelease_simulation(QMouseEvent* event);
    void reverse_xAxis_simulation();
    void reverse_yAxis_simulation();
    void savepdf_simulation();
    void simulation_save();


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H

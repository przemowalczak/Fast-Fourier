//g++ -Wall -O2 -finline-functions    fast_LS.cpp   -lnfft3 -lfftw3 -lm -lc



/*
 * Based on Leroy, A&A 545, A50 (2012)
 */

#include <fstream>
#include <complex>
#include <nfft3.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <sstream>
#include "sort_pwh.hpp"


using namespace std;



class light_curve
{
public:
    vector<double> date, flux, flux_err, flux_resid;
    int data_points;
    int n_sines=0;
    vector<vector<double> > sine_parameters; // in vector are stored parameters of nonlinear fitted sines, ie.
                                             //sine_parameters[0][0] - first frequency, sine_parameters[0][1] - amplitude of the first frequency, 
                                             //sine_parameters[0][2] - phase of the first frequency, sine_parameters[0][3] - frequency error, 
                                             //sine_parameters[0][4] - amplitude error, sine_parameters[0][5] - phase error, sine_parameters[1][0] - second frequency etc
    vector<vector<int> > fit_control; // control whether to fit a given parameter for a given frequency, in order frequency, amplitude, phase
    void read_data(string file_name);
    
    void print();
private:
    int count_columns(string file_name);
    int columns;
};




class fast_LS_periodogram
{
public:
    /* Computes the Lomb - Scargle normalised periodogram of a times - series .
    t the times , reduced to [ -1/2 ,1/2).    y the measurements , centred around <y >.
    npts the length of the times -series .     over the oversampling factor .
    hifac the highest frequency in units of " average " Nyquist frequency .
    This function returns the results in a structure , LS ( see text ).    */
    void calculate_LS(const vector<double> & t, const vector<double> & y, const int npts ,double f0,double fe,double df, double over=4 , const double hifac=1, bool save_trf=true,bool use_data=true);
    void find_nu_max_amp(double StoNlimit=4, bool noise_in_window=true, double window_size=1);
    
    vector<double>  freqs; // (>0) frequencies
    vector<double> Pn;  // periodogram ordinates (amplitude periodogram)
    vector<double> Pn_window;
    vector<double> Pn_noise;
    double noise_full;
    int nfreqs ; // number of frequencies
    double var, mean;
    double nu_max_amp, SN_nu_max_amp, SN_nu_max_amp_full;

    vector<double> &fr();
    vector<double> &ampl();

    vector<double> &frpeaks();
    vector<double> &amplpeaks();
    vector<double> &Ppeaks();
    vector<double> &SNpeaks();

    
private:
    void meanAndVariance(const int npts, const vector<double> &y);
    void centerData(const int npts, const vector<double> & y);
    void reduce(const vector<double> & t, const int npts, const double oversampling);
    void nfft ( const vector<double> & t, const vector<double> & y, int n, int m, vector< complex<double> > &d, bool window_spectrum);
    void calculate_noise(bool noise_in_window, double window_size);
    
    vector<double> y_centered, t_reduced;
    vector< complex<double> > sp, win;
    int output_file_number=0;
    int noise_window_points_div_2;
    bool calculate_nfft_win=true;
    bool cal_noise_window_points=true;
    bool save_trf_and_noise_files=false;

    vector<double> _fr;
    vector<double> _ampl;
    vector<double> _frpeaks;
    vector<double> _amplpeaks;
    vector<double> _Ppeaks;
    vector<double> _SNpeaks;

};





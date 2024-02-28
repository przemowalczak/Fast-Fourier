#ifndef stat_pw
#define stat_pw

#include <stdlib.h>
#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip> //setprecision
#include <complex>
#include <regex>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <sstream>
#include <random>
#include <gsl/gsl_cdf.h>

#include "operators_pwh.hpp"
#include "klunkry_pwh.hpp"
#include "sort_pwh.hpp"

//require sort_pw.hpp


//****cl_stat****

typedef double T;

class cl_stat{
  protected:
	bool _compute_ok;
	bool _mean_ok;
	bool _sd_ok;
	bool _init_ok;
	bool _mediana_ok;
	bool _moda_ok;
    bool _min_ok;
    bool _max_ok;
    bool _sort_ok=false;
	T meanv;
	T sdv;
	size_t nv;
	size_t _n;
	T _sum;
	T _mediana;
	T _moda;
    T _D; //nieobciazony
    T _D2;
    T _Do; //obciazony
    T _Do2;  
    T _g1; //skosnosc
    T _g2;//splaszczenie, kurtoza, skupienie
    T _g2no;//kurtoza nieobciążona
    T _g1no;//skosnosc nieobciążona
    T _m;
    T _mc;
    T _min;
    T _max;

    //for K2 test, D'Agostino-Pearsona
    bool _K2_test_ok=false;
    T _mu1g1;
    T _mu2g1;
    T _gamma1g1;
    T _gamma2g1;

    T _mu1g2;
    T _mu2g2;
    T _gamma1g2;
    T _gamma2g2;

    T _W2;
    T _delta;
    T _alpha2;
    T _Z1g1;
    T _Z2g2;
    T _A;
    T _K2=0;

    //For Jarque-Bera test
    T _JB=0;
    bool _JB_test_ok=false;

  public:
    vector<T>::iterator x0;
    vector<T>::iterator xe;
	size_t dt;
	//vector<T> *x;
    T mean();
    T sd();//sd^2=1/(n-1) sum(xi-meanx)^2
	T s();//S^2=1/n sum(xi-meanx)^2
    T D();  //sqrt(1/(n-1)sum (x-mean)^2)
    T D2();  //1/(n-1)sum (x-mean)^2
	T Do();  //sqrt(1/n sum (x-mean)^2)
    T Do2();// 1/n sum (x-mean)^2
    T cmean();
    T max();
    T min();
    T csd();//standard deviation
	T sum();
	T mediana();
	T cmediana();
	T moda();
	T cmoda();
	T g1();
    T g2();
    T g2no();
    T g1no();
    T moment(int r);
    T moment_cen(int r);

    T cquantile(double alpha);

    T cK2();
    bool K2_test_ok();
    T mu1g1();
    T mu2g1();
    T gamma1g1();
    T gamma2g1();

    T mu1g2();
    T mu2g2();
    T gamma1g2();
    T gamma2g2();

    T W2();
    T delta();
    T alpha2();
    T Z1g1();
    T K2();

    T JB();
    T cJB();
    bool JB_test_ok();

	size_t n();
    void compute();
	void init(vector<T>&x);
	void print();
    void printtex();
	void help();
	bool mean_ok();
	bool sd_ok();
	bool compute_ok();
	bool mediana_ok();
	bool moda_ok();
    bool sort();
    T cmax();
    T cmin();
	cl_stat():
	    _min_ok{false},_max_ok{false},dt(1),_compute_ok{false},_mean_ok{false},_sd_ok{false},_init_ok{false},_mediana_ok{false},_moda_ok{false}{
	}
    cl_stat( vector<T>::iterator _x0, vector<T>::iterator _xe):
	    _min_ok{false},_max_ok{false},dt(1),_compute_ok{false},_mean_ok{false},_sd_ok{false},_init_ok{true},_mediana_ok{false},_moda_ok{false},x0{_x0},xe{_xe}{
			_n=distance(x0,xe);
	}
	cl_stat(vector<T> &_x):
	    _min_ok{false},_max_ok{false},dt(1),_compute_ok{false},_mean_ok{false},_sd_ok{false},_init_ok{true},_mediana_ok{false},_moda_ok{false},x0{_x.begin()},xe{_x.end()},_n{_x.size()}{	
	}
    ~cl_stat(){
    }
};



//****cl_statxy****
//require: cl_stat and sort_pw.hpp
class cl_statxy{
  protected:
	bool _compute_ok;
	bool cov_ok;
	bool rho_ok;
	bool _init_ok;
	bool spearman_ok;
	T covv;
	T rhov;
	T spearmanv;
	T pzv;
	T ptv;
	T pz2v;
	size_t n;
    cl_stat _xs,_ys;
  public:
    cl_stat *x;
    cl_stat *y;
	size_t dt;
	T cov();
	T ccov();
	T rho();
	T crho();
	void compute();
    void init(cl_stat *xs,cl_stat *ys);
	void init(vector<T> &x,vector<T> &y);
	void help();
	//void init(vector<T>&x);
	//T cspearman(bool out=false);
	//T spearman();
	T pz();
	//T pz2();
	T pt();
    cl_statxy():
       dt{1},cov_ok{false},rho_ok{false},_compute_ok{false},_init_ok{false},spearman_ok{false}{
    }
    cl_statxy(vector<T> &_x,vector<T> &_y):
       dt{1},cov_ok{false},rho_ok{false},_compute_ok{false},_init_ok{true},spearman_ok{false},_xs{_x},_ys{_y}{
        _xs.cmean();
        _xs.csd();
        //_xs.print();
        x=&(_xs);
        _ys.cmean();
        _ys.csd();
        //_ys.print();  
        y=&(_ys);

    }
    cl_statxy(cl_stat *_x,cl_stat *_y):
       dt{1},cov_ok{false},rho_ok{false},_compute_ok{false},_init_ok{true},spearman_ok{false},x{_x},y{_y}{
		 if(!((*x).mean_ok()))(*x).cmean();
         if(!((*x).sd_ok()))(*x).csd();
         if(!((*y).mean_ok()))(*y).cmean();
         if(!((*y).sd_ok()))(*y).csd();
    }
    ~cl_statxy(){
    }
};


//**** cl_GESD ****




class cl_GESD{
  private:
     bool _init_ok;
	 bool _ind_ok;
	 bool _xwo_ok;
     cl_stat _stat;
     vector<size_t>_ind;
	 vector<T>_xwo;
	 size_t _nind;
  public:
     //Warning. In this version we make a copy of the vector. Time consuming
     //class vector<T>::iterator x0;
     //class vector<T>::iterator xe;
     //vector<T> x;
	 T max_outliers;//maximal number if outliers in units of  sample size (0-1)
     vector<size_t> cind(T alpha=0.1, bool out=false);//calculate the indexes of outliers
	 vector<size_t> ind();
	 vector<T> xwo();//vector without outliers
     vector<T> cvwo(vector<T>&v);//calculate vector without outliers
     void init(vector<T>&x);
	 void help();
     cl_GESD():_init_ok{false},_ind_ok{false},_xwo_ok{false},max_outliers{0.2}{
     }
     cl_GESD(vector<T>&_x):_init_ok{true},_ind_ok{false},_xwo_ok{false},max_outliers{0.2},_xwo{_x}{
     }
};


#endif

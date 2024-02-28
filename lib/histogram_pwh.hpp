#ifndef histogram_pw
#define histogram_pw


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
#include <gsl/gsl_integration.h>

#include "operators_pwh.hpp"
#include "klunkry_pwh.hpp"


typedef double T;



class cl_histogram{
    private:
       typename vector<T>::iterator x0; 
	   typename vector<T>::iterator xe;
	   bool _init_ok;
	   bool his_ok;
	   T xmax;
	   T xmin;
       T _Nmax;
       T _Nmin;
	   vector<T> Nv;
	   vector<T> xv;
       vector<T> Pv;
       vector<T> Nnormv;
	   vector<vector<T> > xrangev;
       vector<vector<T> > nrangev;
	   vector<T>_xF;
	   vector<T>_yF;
	   vector<T>_xFN;
	   vector<T>_yFN;
	   T _dx;
       T _sum=0;
	   bool _eF_ok;
       bool _eFN_ok;
	   int _n;
       long unsigned int _nelements;
	   bool _mean_ok;
	   bool _D_ok;
	   T _D; //nieobciazony
       T _D2;
       T _Do; //obciazony
       T _Do2;       
	   T _mean;
	   bool _mediana_ok;
	   bool _moda_ok;
       T _mediana;
	   T _moda;
	   bool _compute_ok;
	   T _R;
       FILE *_g_potok;
       bool _g_potok_ok;
       T _g1; //skosnosc
       T _g2;//splaszczenie, kurtoza, skupienie
       T _g2no;//kurtoza nieobciążona
       T _g1no;//skosnosc nieobciążona
       bool _sd_ok;
       void TopDownMerge3_histogram(typename vector<T>::iterator A, size_t iBegin, size_t iMiddle, size_t iEnd, typename vector<T>::iterator B);
       void TopDownSplitMerge3_histogram(typename vector<T>::iterator B, size_t iBegin, size_t iEnd, typename vector<T>::iterator A);
       void f_sort_mi_histogram(vector<T> &A);
       T _quantile=0;
       T _alpha=-1;
	public:
       //cl_histogram(vector<T> &x,int n=10){
       //    init(x);
       //    his(n,false);
       //}
       T g1o(); //skosnosc
       T g2o();//splaszczenie, kurtoza, skupienie
       T g2();//kurtoza nieobciążona
       T g1();//skosnosc nieobciążona
       bool init(vector<T> &x);
       void his(int n, bool out=false);
       void counts(bool out=false);
	   void his2(int n, bool out=false);
       void his(int n, double xmini,double xmaxi,double dx,bool out=false);
	   void adopt(vector<T>&x,vector<T>&N ,bool out=false);
	   //void replot(string gi="yes",string gs="no",string line=" ",string tit="histogram", string xtit="x", string ytit="N",string colbackground="white",string coltext="black");
	   //void plot(string gi="yes",string gs="no",string line=" ",string tit="histogram", string xtit="x", string ytit="N",string colbackground="white",string coltext="black");
	   //void ploteps(string name="",string line=" ",string tit="histogram", string xtit="x", string ytit="N",string colbackground="white",string coltext="black");
	   //void plot2(string gi="yes",string gs="no",string line=" ",string tit="histogram", string xtit="x", string ytit="N",string colbackground="white",string coltext="black");
	   //void plotF(string gi="yes",string gs="no",string line=" ",string tit="empirical distribuant", string xtit="x", string ytit="N",string colbackground="white",string coltext="black");
       vector<T>& xF(); //distribuant
	   vector<T>& yF();
	   T yFx(T x);
	   vector<T>& xFN(); //disribuant of the normal  distribution
	   vector<T>& yFN();
	   void F();
	   vector<T>& N();
	   vector<T>& x();
       vector<T>& P();
       vector<T>& Nnorm();
       T mean();
	   T sd(); //sqrt(1/(n-1)sum (x-mean)^2)
       T D();  //sqrt(1/(n-1)sum (x-mean)^2)
       T D2();  //1/(n-1)sum (x-mean)^2
	   T Do();  //sqrt(1/n sum (x-mean)^2)
       T Do2();// 1/n sum (x-mean)^2
	   T cmean();
	   T csd();
	   T R();
	   T dx();
       T cquantile(T alpha);
       T cquantile_li(T alpha);
       T quantile();
       T alpha();
       T Nmax();
       T Nmin();
	   bool isF();
	   vector<vector<T> >& xrange();
	   vector<vector<T> >& nrange();
       void save(string name="histogram.dat");
	   void ceF();
       void cFN();
       void cFN(T m, T S2);
       void cFN_center();
	   void ceF_for_Kolmogorov();
	   void print();
       void printall();
       void printtex();
	   void compute();
	   T cmediana();
	   T cmoda();
	   T mediana();
	   T moda();
       T sum();
	   cl_histogram():_init_ok(false),his_ok(false),_eF_ok{false},_g_potok_ok{false}{
	   }
	   cl_histogram(typename vector<T>::iterator xt0,typename vector<T>::iterator xte):
	      _sd_ok{false},x0{xt0},xe{xte},_init_ok{true},his_ok{false},_eF_ok{false},_mediana_ok{false},_moda_ok{false},_mean_ok{false},_D_ok{false},_compute_ok{false}{
			  _nelements=distance(xt0,xte);
	   }
	   cl_histogram(vector<T>&xt):
	      _sd_ok{false},x0{xt.begin()},xe{xt.end()},_init_ok{true},his_ok{false},_eF_ok{false},_mediana_ok{false},_moda_ok{false},_mean_ok{false},_D_ok{false},_compute_ok{false}{
			  _nelements=xt.size();
	   }
	   ~cl_histogram(){
		   Nv.clear();
		   xv.clear();
		   xrangev.clear();
       }
};


ostream & operator<< (ostream &ret, cl_histogram &rf);



struct st_params_F_dist_histogram{
   T x0;
   T xe;
   int n;
   int n1;
   int n2;
   T lambda;
   T m;
   T sigma2;
};   

double f_Nms2_histogram(double x, void *parameters);



T F_integrate_histogram(double(*f)(double x,void *params),st_params_F_dist_histogram &params,T x0, T xe,int ni=100,int key=6,T eps=1e-6);

T F_Nms2_histogram(T x,T m,T sigma2);







class cl_histogramxy{
    private:
       typename vector<T>::iterator _x0; 
	   typename vector<T>::iterator _xe;
	   typename vector<T>::iterator _y0; 
	   typename vector<T>::iterator _ye;
	   bool _init_ok;
	   bool _his_ok;
	   T _xmax;
	   T _xmin;
	   T _xNmax;
	   T _xNmin;
	   T _ymax;
	   T _ymin;
	   T _yNmax;
	   T _yNmin;
       T _Nmax;
       T _Nmin;
	   vector<vector<T> > _N;
	   vector<T> _Nx;
	   vector<T> _Ny;
	   vector<T> _x;
	   vector<T> _y;
	   vector<vector<T> > _xrangev;
       vector<vector<T> > _nxrangev;
	   vector<vector<T> > _yrangev;
       vector<vector<T> > _nyrangev;
	   vector<T>_xF;
	   vector<T>_yF;
	   T _dx;
       T _dy;
       T _sum;
       T _sumx;
       T _sumy;
	   bool _eF_ok;
	   int _nx;
       int _ny;
       long unsigned int _nelements;
	   bool _mean_ok;
	   bool _D_ok;
	   T _D;
	   T _mean;
	   bool _mediana_ok;
	   bool _moda_ok;
       T _mediana;
	   T _moda;
	   bool _compute_ok;
	public:
	   void init(vector<T> &x,vector<T> &y);
       void his(int nx,int ny, bool out=false);
	   vector<T>& xF();
	   vector<T>& yF();
	   void F();
	   vector<vector<T> >& N();
	   vector<T> & Nx();
	   vector<T> & Ny();
	   vector<T>& x();
	   vector<T>& y();
	   T mean();
	   T sd();
	   T cmean();
	   T csd();
	   bool isF();
	   vector<vector<T> >& xrange();
       vector<vector<T> >& yrange();
	   vector<vector<T> >& nxrange();
       vector<vector<T> >& nyrange();
       void save(string name="histogram.dat");
	   void ceF();
	   void ceF_for_Kolmogorov();
	   void print();
	   void compute();
	   T cmediana();
	   T cmoda();
	   T s();
       T sum();
       T dx();
       T dy();
	   cl_histogramxy():_init_ok(false),_his_ok(false),_eF_ok{false}{
	   }
	   cl_histogramxy(typename vector<T>::iterator xt0,typename vector<T>::iterator xte,typename vector<T>::iterator yt0,typename vector<T>::iterator yte):
	      _x0{xt0},_xe{xte},_init_ok{true},_his_ok{false},_eF_ok{false},_mediana_ok{false},_moda_ok{false},_mean_ok{false},_D_ok{false},_compute_ok{false}{
			  _nelements=distance(xt0,xte);
              if(_nelements!=distance(yt0,yte)){
                 _init_ok=false;
                 f_alert("cl_histogramxy problem, vectors a and y have to have the same size");
              }
	   }
	   cl_histogramxy(vector<T>&xt,vector<T>&yt):
	      _x0{xt.begin()},_xe{xt.end()},_y0{yt.begin()},_ye{yt.end()},_init_ok{true},_his_ok{false},_eF_ok{false},_mediana_ok{false},_moda_ok{false},_mean_ok{false},_D_ok{false},_compute_ok{false}{
			  _nelements=xt.size();
              if(_nelements!=yt.size()){
                 _init_ok=false;
                 f_alert("cl_histogramxy problem, vectors a and y have to have the same size");
              }
	   }
	   ~cl_histogramxy(){
		   _N.clear();
		   _x.clear();
		   _xrangev.clear();
       }
};


ostream & operator<< (ostream &ret, cl_histogramxy &rf);





#endif

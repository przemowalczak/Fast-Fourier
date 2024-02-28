#ifndef gsl_spline_pw
#define gsl_spline_pw


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
#include <gsl/gsl_spline.h>
#include <gsl/gsl_interp.h>


#include "klunkry_pwh.hpp"


typedef double T;

//**** gsl_spline declaration ****

class cl_spline{
  private:
	 gsl_spline *_spline;
     gsl_interp_accel *_acc;
	 size_t _nx;
	 size_t _ny;
	 T _xmin;
	 T _xmax;
	 bool _init_ok;
	 bool _spline_ok; 
	 bool _ok;
	 vector<bool> _okv;
	 string _interp_type;
     vector<T> _yiv;
	 vector<T> _xiv;
     T _yi;
	 T _xi;
	 int _iv;
	 double _time;
     vector<T>::iterator x0;
     vector<T>::iterator xe;
     vector<T>::iterator y0;
     vector<T>::iterator ye;
  public:
	 size_t np;
	 void help();
	 void init(vector<T>&x,vector<T>&y);
     void init(vector<T>::iterator _x0, vector<T>::iterator _xe, vector<T>::iterator _y0, vector<T>::iterator _ye);
     void cspline(string interp_type="akima",string opt="check_edges_and_reverse",bool out=false);
	 void free();
	 string name;
     T e(T x);
     vector<T>& e(vector<T> &x);
	 vector<bool>& okv();
     T ed(T x);
     vector<T>& ed(vector<T> &x);
     T ed2(T x);
     vector<T>& ed2(vector<T> &x);
	 T xmin();
     T xmax();
	 double time(){return _time;}
	 bool ok();
	 bool spline_ok();
	 bool out;
	 void show();
     int n();
     T nearestx(T x);
     T nearesty(T y);
     cl_spline():_init_ok{false},_spline_ok{false},np{5},_ok{false},out{false},_interp_type{""},_iv{0}{ 
		 //name=__func__;
	 }
	 cl_spline(vector<T>&_x,vector<T>&_y):
	    _nx{_x.size()},_ny{_y.size()},_init_ok{true},_spline_ok{false},np{5},_ok{false},out{false},_interp_type{""},x0{_x.begin()},xe{_x.end()},y0{_y.begin()},ye{_y.end()},_iv{0}{ 
            
	 }
     cl_spline( vector<T>::iterator _x0, vector<T>::iterator _xe, vector<T>::iterator _y0, vector<T>::iterator _ye):
	    _init_ok{true},_spline_ok{false},np{5},_ok{false},out{false},_interp_type{""},x0{_x0},xe{_xe},y0{_y0},ye{_ye},_iv{0}{ 
            _nx=distance(_x0,_xe);
		    _ny=distance(_y0,_ye);
	 }
	 //Copy constructor
	 cl_spline(const cl_spline &spline){
		 clock_t begin=clock();
		 //cout << "Copy constructor called"<<endl;
		 //cout<<"name="<<spline.name<<endl;
		 if(spline._spline_ok){	
            if((spline._interp_type == "akima") && (spline._nx>5))_spline= gsl_spline_alloc (gsl_interp_akima,spline._nx);
            else if ((((spline._interp_type == "cspline") && (spline._nx>2)) || ((spline._interp_type == "akima") && (spline._nx<=5))) && (spline._nx>2))_spline= gsl_spline_alloc (gsl_interp_cspline,spline._nx);
            else if ((spline._interp_type == "linear") || (spline._nx==2))_spline= gsl_spline_alloc (gsl_interp_linear,spline._nx);
            else{
	           f_alert("cl_spline: interp_type = "+spline._interp_type+" is unknown ");
            }    
            _acc=gsl_interp_accel_alloc();
		    //*_spline=*(spline._spline);
		    *_acc=*(spline._acc);
			gsl_spline_init(_spline,spline._spline->x,spline._spline->y,spline._spline->size);
			
		 }
		 if(spline._init_ok){
			x0=spline.x0; 
			xe=spline.xe;
			y0=spline.y0;
			ye=spline.ye;
		 }
		 _init_ok=spline._init_ok;
	     _spline_ok=spline._spline_ok;
	     _nx=spline._nx;
	     _ny=spline._ny;
	     _xmin=spline._xmin;
	     _xmax=spline._xmax;
	     _ok=spline._ok;
		 for(size_t i=0;i<spline._okv.size();++i){
	          _okv[i]=spline._okv[i];
			  _yiv[i]=spline._yiv[i];
			  _xiv[i]=spline._xiv[i];
		 }
	     _interp_type=spline._interp_type;
	     _yi=spline._yi;
	     _xi=spline._xi;
		 _iv=spline._iv;
		 np=spline.np;
		 out=spline.out;
		 name=spline.name;
		 //name=spline.name+"c";
		 //cout<<"name="<<name<<" "<<_init_ok<<" "<<_spline_ok<<" "<<spline._spline_ok<<endl;
		 //cout << "Copy constructor end"<<endl;
		 _time=double(clock() - begin) / CLOCKS_PER_SEC;
	 }
	 // Overloaded assignment
     cl_spline& operator= (const cl_spline &spline);
		
	 ~cl_spline(){
		if(_spline_ok){
		   _spline_ok=false;
		   _init_ok=false;
		   //cout<<"free memory"<<" name="<<name<<endl;
	       free();
		   //cout<<"end free memory"<<endl;
		}
	 }
};



int f_find_ind_s_root(int &i0,int &im,int &ie,T *it0,int n,T &v);
int f_find_ind_s(T *it0,int ie,T v);

//  Left source half is A[ iBegin:iMiddle-1].
// Right source half is A[iMiddle:iEnd-1   ].
// Result is            B[ iBegin:iEnd-1   ].

void TopDownMerge4_spline(vector<T>::iterator A,vector<T>::iterator C, size_t iBegin, size_t iMiddle, size_t iEnd, vector<T>::iterator B,vector<T>::iterator D);


void TopDownSplitMerge4_spline(T B,T D, size_t iBegin, size_t iEnd, T A, T C);

void f_sort_m_spline(T typex, T typey, vector<T>::iterator A0, vector<T>::iterator Ae, vector<T>::iterator C0,  vector<T>::iterator Ce);

string spline_gsl_to_string(T value,int prec=6);


  
#endif 

/*			 
			 typedef struct {
  gsl_interp * interp;
  double  * x;
  double  * y;
  size_t  size;
} gsl_spline;*//*
typedef struct {
  size_t  cache;        // cache of index   
  size_t  miss_count;   // keep statistics  
  size_t  hit_count;
}
gsl_interp_accel;*/

/* interpolation object type 
typedef struct {
  const char * name;
  unsigned int min_size;
  void *  (*alloc) (size_t size);
  int     (*init)    (void *, const double xa[], const double ya[], size_t size);
  int     (*eval)    (const void *, const double xa[], const double ya[], size_t size, double x, gsl_interp_accel *, double * y);
  int     (*eval_deriv)  (const void *, const double xa[], const double ya[], size_t size, double x, gsl_interp_accel *, double * y_p);
  int     (*eval_deriv2) (const void *, const double xa[], const double ya[], size_t size, double x, gsl_interp_accel *, double * y_pp);
  int     (*eval_integ)  (const void *, const double xa[], const double ya[], size_t size, gsl_interp_accel *, double a, double b, double * result);
  void    (*free)         (void *);

} gsl_interp_type;

 general interpolation object 
typedef struct {
  const gsl_interp_type * type;
  double  xmin;
  double  xmax;
  size_t  size;
  void * state;
} gsl_interp;
*/
//*(_spline->interp)=*(spline._spline->interp);
			//(_spline->interp->xmin)=(spline._spline->interp->xmin);
			//(_spline->interp->xmax)=(spline._spline->interp->xmax);
			//(_spline->interp->size)=(spline._spline->interp->size);
			//*(_spline->interp->type)=*(spline._spline->interp->type);
			
			//*(_spline->x)=*(spline._spline->x);
			//*(_spline->y)=*(spline._spline->y);
			//_spline->size = spline._spline->size;
			/*cout<<"x="<<*(_spline->x)<<endl;
			cout<<"y="<<*(_spline->y)<<endl;
			cout<<"size="<<(_spline->size)<<endl;
			cout<<"cache="<<_acc->cache<<endl;
			cout<<"miss="<<_acc->miss_count<<endl;
			cout<<"hit="<<_acc->hit_count<<endl;
			cout<<"(_spline->interp->xmin)="<<(_spline->interp->xmin)<<endl;
			cout<<"(_spline->interp->xmax)="<<(_spline->interp->xmax)<<endl;
			cout<<"(_spline->interp->size)="<<(_spline->interp->size)<<endl;
			cout<<"*(_spline->interp->type->name)="<<*(_spline->interp->type->name)<<endl;
			cout<<"(_spline->interp->type->min_size)="<<(_spline->interp->type->min_size)<<endl;
			*/

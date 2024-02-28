#ifndef box_pw
#define box_pw

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

#include "klunkry_pwh.hpp"

using namespace std;

typedef double T;

//require klunkry.hpp

class Box{
   private:
	  bool _init_ok;
       vector<T>::iterator x0;
       vector<T>::iterator xe;
       vector<T>::iterator y0;
       vector<T>::iterator ye;
	  int _i0,_ie,_n;
	  T _dT;
	  T _Tc;
	  T _sum;
	  int _np;
   public:
	  Box(vector<T>&x,vector<T>&y, T __dT):_init_ok{false},x0{x.begin()},xe{x.end()},y0{y.begin()},ye{y.end()},_dT{__dT},_i0{0},_ie{0},_sum{0}{
		_n=x.size();  
	  }
	  void init(T Tc);
       void init2(T Tc);
	  void refresh(T Tc);
	  int i0();
	  int ie();
	  T Tc();
	  T Sum();
	  int np();
	  T f_sum(int, int);
	   
	
};

#endif

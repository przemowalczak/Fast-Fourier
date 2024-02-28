#ifndef operators
#define operators

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

using namespace std;



//*************  operators *******************************8


vector<long double> operator * (long double const &c1, vector<long  double> const &c2);
vector<long double> operator * (vector<long  double> const &c2,long double const &c1);
vector<long double> operator / (vector<long  double> const &c2,long double const &c1);
vector<long double> operator + (vector<long double> const &c1, vector<long  double> const &c2);
vector<long double> operator - (vector<long double> const &c1, vector<long  double> const &c2);
vector<double> operator * (double const &c1, vector< double> const &c2);
vector<double> operator * (vector< double> const &c2,double const &c1);
vector<double> operator + (vector<double> const &c1, vector< double> const &c2);
vector<double> operator - (vector<double> const &c1, vector< double> const &c2);



ostream & operator<< (ostream &ret, vector<string> &vec);
ostream & operator<< (ostream &ret, vector<vector<string> >&vec);
ostream & operator<< (ostream &ret, vector<vector<vector<string> > >&vec);
ostream & operator<< (ostream &ret, vector<vector<vector<vector<string> > > >&vec);
ostream & operator<< (ostream &ret, vector<vector<vector<vector<vector<string> > > > >&vec);



ostream & operator<< (ostream &ret, vector<bool> &vec);
ostream & operator<< (ostream &ret, vector<vector<bool> >&vec);
ostream & operator<< (ostream &ret, vector<vector<vector<bool> > >&vec);
ostream & operator<< (ostream &ret, vector<vector<vector<vector<bool> > > >&vec);
ostream & operator<< (ostream &ret, vector<vector<vector<vector<vector<bool> > > > >&vec);
ostream & operator<< (ostream &ret, vector<int> &vec);
ostream & operator<< (ostream &ret, vector<vector<int> >&vec);
ostream & operator<< (ostream &ret, vector<vector<vector<int> > >&vec);
ostream & operator<< (ostream &ret, vector<vector<vector<vector<int> > > >&vec);
ostream & operator<< (ostream &ret, vector<vector<vector<vector<vector<int> > > > >&vec);

ostream & operator<< (ostream &ret, vector<size_t> &vec);
ostream & operator<< (ostream &ret, vector<vector<size_t> >&vec);
ostream & operator<< (ostream &ret, vector<vector<vector<size_t> > >&vec);
ostream & operator<< (ostream &ret, vector<vector<vector<vector<size_t> > > >&vec);
ostream & operator<< (ostream &ret, vector<vector<vector<vector<vector<size_t> > > > >&vec);
ostream & operator<< (ostream &ret, vector<double> &vec);
ostream & operator<< (ostream &ret, vector<vector<double> >&vec);
ostream & operator<< (ostream &ret, vector<vector<vector<double> > >&vec);
ostream & operator<< (ostream &ret, vector<vector<vector<vector<double> > > >&vec);
ostream & operator<< (ostream &ret, vector<vector<vector<vector<vector<double> > > > >&vec);
ostream & operator<< (ostream &ret, vector<vector<vector<vector<vector<vector<double> > > > > >&vec);
ostream & operator<< (ostream &ret, vector<long double> &vec);
ostream & operator<< (ostream &ret, vector<vector<long double> >&vec);
ostream & operator<< (ostream &ret, vector<vector<vector<long double> > >&vec);
ostream & operator<< (ostream &ret, vector<vector<vector<vector<long double> > > >&vec);
ostream & operator<< (ostream &ret, vector<vector<vector<vector<vector<long double> > > > >&vec);
ostream & operator<< (ostream &ret, vector<vector<vector<vector<vector<vector<long double> > > > > >&vec);

ostream & operator<< (ostream &ret, vector<complex<double> >&vec);
ostream & operator<< (ostream &ret, vector<vector<complex<double> > >&vec);
ostream & operator<< (ostream &ret, vector<vector<vector<complex<double> > > >&vec);
ostream & operator<< (ostream &ret, vector<vector<vector<vector<complex<double> > > > >&vec);
ostream & operator<< (ostream &ret, vector<vector<vector<vector<vector<complex<double> > > > > >&vec);
ostream & operator<< (ostream &ret, vector<vector<vector<vector<vector<vector<complex<double> > > > > > >&vec);

ostream & operator<< (ostream &ret, vector<complex<long double> >&vec);
ostream & operator<< (ostream &ret, vector<vector<complex<long double> > >&vec);
ostream & operator<< (ostream &ret, vector<vector<vector<complex<long double> > > >&vec);
ostream & operator<< (ostream &ret, vector<vector<vector<vector<complex<long double> > > > >&vec);
ostream & operator<< (ostream &ret, vector<vector<vector<vector<vector<complex<long double> > > > > >&vec);
ostream & operator<< (ostream &ret, vector<vector<vector<vector<vector<vector<complex<long double> > > > > > >&vec);
//****

#endif

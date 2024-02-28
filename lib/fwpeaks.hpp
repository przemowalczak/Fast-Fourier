#ifndef fwpeaks_pw
#define fwpeaks_pw

//#define _GNU_SOURCE
#define SNL 3.5
#define Nstep 128
#define NTI (Nstep*Nstep)
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<locale.h>
#include<vector>
#include <iostream>
#include "operators_pwh.hpp"



#if !defined(MaxNofChars)
#define MaxNofChars 456
#endif



#if 0
typedef float FLOAT_VEC;
#define FLOAT_VEC_ZERO 0
typedef struct {FLOAT_VEC cos, sin;} sincos_struct;

#define VEC_SIZE 1
#else
#if 1
//typedef float FLOAT_VEC __attribute__ ((mode(V4SF)));
typedef float FLOAT_VEC __attribute__ ((vector_size(16)));
#define FLOAT_VEC_ZERO {0, 0, 0, 0}
#define VEC_SIZE 4
#else
typedef float FLOAT_VEC __attribute__ ((mode(V2SF)));
#define FLOAT_VEC_ZERO {0, 0}
#define VEC_SIZE 2
#endif
#endif

#define ALIGN_TO(step, size) ((size+(step)-1)&~((step)-1))

using namespace std;


class FWPeaks{
private:
    bool ok=false;

    vector<double> _fr;
    vector<double> _ampl;
    vector<double> _frpeaks;
    vector<double> _amplpeaks;
    vector<double> _Ppeaks;
    vector<double> _SNpeaks;

    public:

    bool fourier(int narg, char **argv);
    bool fourier(vector<string> f);
    bool fourier(vector<double>&x,vector<double>&y,vector<double>&e_y,double f0,double fe,double df,bool use_data=true);
    vector<double> &fr();
    vector<double> &ampl();

    vector<double> &frpeaks();
    vector<double> &amplpeaks();
    vector<double> &Ppeaks();
    vector<double> &SNpeaks();



};

#endif

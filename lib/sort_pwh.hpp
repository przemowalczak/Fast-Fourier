#ifndef sort_pw
#define sort_pw

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
#include <iterator>     // std::distance


using namespace std;


typedef double T;



void f_sort(vector<T> &x);
void f_sort(vector<T> &x, vector<T> &y);
void f_sort(vector<T> &x, vector<T> &y, vector<T> &z);


void TopDownMerge3(typename vector<T>::iterator A, size_t iBegin, size_t iMiddle, size_t iEnd, typename vector<T>::iterator B);
void TopDownSplitMerge3(typename vector<T>::iterator B, size_t iBegin, size_t iEnd, typename vector<T>::iterator A);
void f_sort_mi(vector<T> &A);
void f_sort_mi(T type, typename vector<T>::iterator A0, typename vector<T>::iterator Ae);

//  Left source half is A[ iBegin:iMiddle-1].
// Right source half is A[iMiddle:iEnd-1   ].
// Result is            B[ iBegin:iEnd-1   ].

void TopDownMerge(vector<T> &A, size_t iBegin, size_t iMiddle, size_t iEnd, vector<T> &B);
// Sort the given run of array A[] using array B[] as a source.
// iBegin is inclusive; iEnd is exclusive (A[iEnd] is not in the set).

void TopDownSplitMerge(vector<T> &B, size_t iBegin, size_t iEnd, vector<T> &A);
// Array A[] has the items to sort; array B[] is a work array.

void f_sort_m(vector<T> &A);
//  Left source half is A[ iBegin:iMiddle-1].
// Right source half is A[iMiddle:iEnd-1   ].
// Result is            B[ iBegin:iEnd-1   ].

void TopDownMerge2(vector<T> &A, size_t iBegin, size_t iMiddle, size_t iEnd, vector<T> &B);
// Sort the given run of array A[] using array B[] as a source.
// iBegin is inclusive; iEnd is exclusive (A[iEnd] is not in the set).

void TopDownSplitMerge2(vector<T> &B, size_t iBegin, size_t iEnd, vector<T> &A);
// Array A[] has the items to sort; array B[] is a work array.

void f_sort_m2(vector<T> &A);








//  Left source half is A[ iBegin:iMiddle-1].
// Right source half is A[iMiddle:iEnd-1   ].
// Result is            B[ iBegin:iEnd-1   ].

void TopDownMerge(vector<T> &A,vector<T> &C, size_t iBegin, size_t iMiddle, size_t iEnd, vector<T> &B,vector<T> &D);
// Sort the given run of array A[] using array B[] as a source.
// iBegin is inclusive; iEnd is exclusive (A[iEnd] is not in the set).

void TopDownSplitMerge(vector<T> &B,vector<T> &D, size_t iBegin, size_t iEnd, vector<T> &A,vector<T> &C);

void f_sort_m(vector<T> &A,vector<T> &C);




//  Left source half is A[ iBegin:iMiddle-1].
// Right source half is A[iMiddle:iEnd-1   ].
// Result is            B[ iBegin:iEnd-1   ].

void TopDownMerge(vector<vector<T> > &A,vector<vector<T> > &C, size_t iBegin, size_t iMiddle, size_t iEnd, vector<vector<T> > &B,vector<vector<T> > &D);
// Sort the given run of array A[] using array B[] as a source.
// iBegin is inclusive; iEnd is exclusive (A[iEnd] is not in the set).

void TopDownSplitMerge(vector<vector<T> > &B,vector<vector<T> > &D, size_t iBegin, size_t iEnd, vector<vector<T> > &A,vector<vector<T> > &C);

void f_sort_m(vector<vector<T> > &A,vector<vector<T> > &C);




//  Left source half is A[ iBegin:iMiddle-1].
// Right source half is A[iMiddle:iEnd-1   ].
// Result is            B[ iBegin:iEnd-1   ].

void TopDownMerge4(T A,T C, size_t iBegin, size_t iMiddle, size_t iEnd, T B,T D);
// Sort the given run of array A[] using array B[] as a source.
// iBegin is inclusive; iEnd is exclusive (A[iEnd] is not in the set).

void TopDownSplitMerge4(T B,T D, size_t iBegin, size_t iEnd, T A, T C);

void f_sort_mi(vector<T> &A,vector<T> &C);




//  Left source half is A[ iBegin:iMiddle-1].
// Right source half is A[iMiddle:iEnd-1   ].
// Result is            B[ iBegin:iEnd-1   ].

void TopDownMerge(vector<T> &A,vector<T> &C,vector<T> &E, size_t iBegin, size_t iMiddle, size_t iEnd, vector<T> &B,vector<T> &D,vector<T> &F);
// Sort the given run of array A[] using array B[] as a source.
// iBegin is inclusive; iEnd is exclusive (A[iEnd] is not in the set).
void TopDownSplitMerge(vector<T> &B,vector<T> &D,vector<T> &F, size_t iBegin, size_t iEnd, vector<T> &A,vector<T> &C,vector<T> &E);
// Array A[] has the items to sort; array B[] is a work array.
void f_sort_m(vector<T> &A,vector<T> &C,vector<T> &E);


//  Left source half is A[ iBegin:iMiddle-1].
// Right source half is A[iMiddle:iEnd-1   ].
// Result is            B[ iBegin:iEnd-1   ].

void TopDownMerge4(T A,T C, T E, size_t iBegin, size_t iMiddle, size_t iEnd, T B,T D, T F);
// Sort the given run of array A[] using array B[] as a source.
// iBegin is inclusive; iEnd is exclusive (A[iEnd] is not in the set).
void TopDownSplitMerge4(T B,T D, T F, size_t iBegin, size_t iEnd, T A, T C, T E);
void f_sort_mi(vector<T> &A,vector<T> &C,vector<T> &E);
//void f_sort_m4(T A0, T Ae){//iterator to the begining and end of tha A table


//  Left source half is A[ iBegin:iMiddle-1].
// Right source half is A[iMiddle:iEnd-1   ].
// Result is            B[ iBegin:iEnd-1   ].

void TopDownMerge(vector<T> &A,vector<T> &C,vector<T> &E,vector<T> &G, size_t iBegin, size_t iMiddle, size_t iEnd, vector<T> &B,vector<T> &D,vector<T> &F,vector<T> &H);
// Sort the given run of array A[] using array B[] as a source.
// iBegin is inclusive; iEnd is exclusive (A[iEnd] is not in the set).
void TopDownSplitMerge(vector<T> &B,vector<T> &D,vector<T> &F,vector<T> &H, size_t iBegin, size_t iEnd, vector<T> &A,vector<T> &C,vector<T> &E,vector<T> &G);
// Array A[] has the items to sort; array B[] is a work array.
void f_sort_m(vector<T> &A,vector<T> &C,vector<T> &E,vector<T> &G);
void f_sort_mr(vector<T> &A,vector<T> &C,vector<T> &E,vector<T> &G);





#endif

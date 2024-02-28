#ifndef klunkry_pwh
#define klunkry_pwh

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
#include <dirent.h>//directories

#include "operators_pwh.hpp"

using namespace std;

typedef double T;

bool isNumber(const std::string & s);
string f_get_path_from_file_name(string fname);
vector<T> vector_db_from_vector_str(vector<string>&str);
vector<T> vector_db_from_str(string str);
vector<T> autocorr(vector<T>&x);
void print_progres(T percent);
string f_c(string color);
string f_b(string color);
string f_u(string color);
string f_reset();
void print_progres(T percent,string txt);
void print_progres2(T percent);
void f_alert(string text,bool end=true,bool save=false);
T roundoff(T value, unsigned char prec);
vector<string> f_get_format(T x, T ex);
string convert(vector<T> v,int n=-1);
bool present(vector<T> &v, T x);
bool present_eps(vector<T> &v, T x,T eps);
bool present(vector<vector<T> > &v, vector<T> x);
void f_replace(string &str, string patin, string patout);
bool equal(vector<T> &v, vector<T> x);
string str_from_vector(vector<string> &v);
string str_from_vector(vector<T> &v);
vector<string> vector_from_str(string s);
bool is_true(vector<bool> &ok);
bool present(vector<T> &v, vector<T> &x);
void f_get_file_name(string &path);
string f_get_file_name_from_path(string path);
//**** get column ****
int f_get_column_head_nr_col(vector<string> head, string pattern,string approach="match");
vector<T> f_get_column(vector<vector<T> >&x,vector<string>head,string pattern);
vector<double> f_get_column_db_from_str(vector<vector<string> >&x,vector<string>head,string pattern);
vector<int> f_get_column_int_from_db(vector<vector<double> >&x,vector<string>head,string pattern);
//** get column **
//**** f head no col ****
int f_head_nr_col(vector<string> head, string pattern,string approach="match");
int f_no(vector<string> head, string pattern, bool reverse=false, bool out=false,bool match=true);
int f_no(vector<T> head, T pattern, bool reverse=false, bool out=false);
int f_head_nr_col_na(vector<string> head, string pattern,string approach="match");
vector<int> f_head_nr_col(vector<string> head, vector<string> pattern,string approach="match");
vector<int> f_no(vector<string> head, vector<string> pattern,string approach="match");
int f_head_nr_col_n(vector<T> head, T pattern,bool show=true);
vector<vector<T> >f_get_columns(vector<vector<T> > &tab,vector<string>head,vector<string>patterns);
vector<vector<T> >f_get_columns(vector<vector<string> > &tab,vector<string>head,vector<string>patterns);
bool f_get_col(vector<vector<string> > &tab,vector<string> &head,string pat,vector<T> &x);
bool f_get_col(vector<vector<string> > &tab,vector<string> &head,vector<string> &patterns,vector<vector<T> > &x);
bool f_get_col(vector<vector<T> > &tab,vector<string> &head,string pat,vector<T> &x);
bool f_get_col(vector<vector<T> > &tab,vector<string> &head,vector<string> &patterns,vector<vector<T> > &x);
bool f_get_col(vector<vector<T> > &tab,vector<string> &head,vector<string> &patterns,vector<T> &x,vector<T> &y);
//** get columns **
bool f_reverse(vector<vector<T> > &tab,vector<vector<T> > &tabrev);
bool f_reverse(vector<vector<T> > &tab);
string to_string_pw(T value) ;
string to_string_pw(T value,int prec);
void f_erase_white_spac_void(string &str);
string f_erase_white_spac(string str);
void f_erase_white_spac_void(vector<string> &str);
vector<string> f_erase_white_spac(vector<string> str);
string f_erase_sign_from_str(string str,const char c);
bool f_create_directories(string path,bool out=false);
void f_add_slash(string &s,bool out=false);
void f_add_slash(vector<string> &s,bool out=false);
void Tfree(T &v);
double f_get_db(string line,string pattern);
double f_get_db_and_erase(string &line,string pattern);
double f_get_db_and_erase2(string &line,string pattern);
double f_get_db(string line);
void f_extract_params(string s, vector<string> &head, vector<T> &x);
void f_ad_slash(string &s);
void f_erase_slash(string &s);
void f_print_time(T t);
string f_time(T t);
string f_add_ext(string fname,string ext);
string f_remove_ext(string fname);
//**** find ****
int f_find_ind(vector<T> &x,T v);
int f_find_ind2(vector<T> &x,T v);
int f_find_ind2(vector<T>::iterator it0,vector<T>::iterator ite,T v);
int f_find_ind_s_root(int &i0,int &im,int &ie,vector<T> &x,T &v);
int f_find_ind_s(vector<T> &x,T v);
int f_find_ind_s_root(int &i0,int &im,int &ie, vector<T>::iterator it0, vector<T>::iterator ite,T &v);
int f_find_ind_s(vector<T>::iterator it0, vector<T>::iterator ite,T v);
int f_find_ind_s_root_s(int &i0,int &im,int &ie,vector<T> &x,int col,T &v);
int f_find_ind_ss(vector<vector<T> > &x,int col,T v);
int f_find_ind_ss(vector<vector<T> > &x,int i0,int col,T v);
int f_find_ind_sl(vector<vector<T> > &x,int col,T v);
int f_find_ind_sl(vector<vector<T> > &x,int i0,int col,T v);
//**find**

bool present(vector<string> &v, string x);
bool present(vector<int> &v, int x);

#endif

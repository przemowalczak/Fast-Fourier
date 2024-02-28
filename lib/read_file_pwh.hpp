#ifndef read_file_pwh
#define read_file_pwh

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>

#include "operators_pwh.hpp"
#include "klunkry_pwh.hpp"


using namespace std;


typedef double T;


class cl_read_file{
private:
	bool _init_ok;
	bool _nhead_ok;
	bool _ihead_ok;	
	bool _read_ok;
	bool _reads_ok;
    bool _ok=false;
	vector<int>_nc;
	vector<int>_ne;
	int _nr;
	vector<string> _head;
	vector<string> _whead;
	vector<vector<T> >_file;
	vector<string>_files;
    string _fname;
public:

	int nhead;
	int ihead;
	string sep;
	bool out;
	bool ok();
	bool check;
	bool read_ok();
	bool reads_ok();
	int nr();
	void free();
	bool cc();
	void help();
	void info();
	vector<int>& nc();
	vector<int>& ne();
	cl_read_file& read();
	cl_read_file& readmap();
	cl_read_file& reads();//read into simple string
	vector<string>& head();
	vector<string>& whead();
	vector<vector<T> >& file();
	vector<string>& files();
	cl_read_file& sort(string pattern);
	cl_read_file& init(string __fname, int _nhead, int _ihead,string _sep,bool _check=true,bool _out=false,bool read_now=true);
    cl_read_file():_init_ok{false},_nhead_ok{false},_ihead_ok{false},out{false},_read_ok{false},_reads_ok{false},sep{' '},check{true},_nr{0},nhead{0},ihead{0}{
        _head.clear();
        _whead.clear();
        _file.clear();
    }
	/*
	cl_read_file(string __fname,int _nhead, int _ihead):
	     _init_ok{true},_nhead_ok{true},_ihead_ok{true},out{false},_read_ok{false},sep{' '},check{true},
		 _fname{__fname},nhead{_nhead},ihead{_ihead}{
		_head.clear();
		_whead.clear();
		_file.clear();
	}
	cl_read_file(string __fname,int _nhead, int _ihead,string _sep):
	     _init_ok{true},_nhead_ok{true},_ihead_ok{true},out{false},_read_ok{false},
		 _fname{__fname},nhead{_nhead},ihead{_ihead},sep{_sep},check{true}{
		 _head.clear();
		_whead.clear();
		_file.clear();
	}
	cl_read_file(string __fname,int _nhead, int _ihead,bool _check, bool _out=false):
	     _init_ok{true},_nhead_ok{true},_ihead_ok{true},out{_out},_read_ok{false},sep{' '},check{_check},
		_fname{__fname},nhead{_nhead},ihead{_ihead}{
		_head.clear();
		_whead.clear();
		_file.clear();	 
	}*/
	cl_read_file(string __fname,int _nhead, int _ihead,string _sep=" ",bool _check=true, bool _out=false,bool read_now=true):
	     _init_ok{true},_nhead_ok{true},_ihead_ok{true},out{_out},_read_ok{false},_reads_ok{false},
		 _fname{__fname},nhead{_nhead},ihead{_ihead},sep{_sep},check{_check},_nr{0}{
		 _head.clear();
		 _whead.clear();
		 _file.clear();	
		 if(read_now){
		   read();
		 }
		 //readmap();
	}
	~cl_read_file(){	
		//if(out)cout<<"free memory"<<endl;
		free();
	}
	string file_name();
};


ostream & operator<< (ostream &ret, cl_read_file &rf);


string to_string_rf(T value);
void f_extract(string &line,string separator,vector<T>&v,bool check,int il,string &_fname);

void f_extract(string &line,string separator,vector<string> &v,bool check, int il,string &_fname);
vector<T> f_get_column(cl_read_file&file,string pattern);





class cl_read_file_str{
private:
	bool _init_ok;
	bool _nhead_ok;
	bool _ihead_ok;
	bool _read_ok;
	bool _reads_ok;
    bool _ok=false;
	vector<int>_nc;
	vector<int>_ne;
	int _nr;
	vector<string> _head;
	vector<string> _whead;
	vector<vector<string> >_file;
	vector<string>_files;
    string _fname;
public:

	int nhead;
	int ihead;
	string sep;
	bool out;
	bool ok();
	bool check;
	bool read_ok();
	bool reads_ok();
	int nr();
	void free();
	bool cc();
	void help();
	void info();
	vector<int>& nc();
	vector<int>& ne();
	cl_read_file_str& read();
	cl_read_file_str& readmap();
	cl_read_file_str& reads();//read into simple string
	vector<string>& head();
	vector<string>& whead();
    vector<vector<string> >& file();
	vector<string>& files();
	cl_read_file_str& sort(string pattern);
    cl_read_file_str& init(string __fname, int _nhead, int _ihead,string _sep,bool _check=true,bool _out=false,bool read_now=true);
    cl_read_file_str():_init_ok{false},_nhead_ok{false},_ihead_ok{false},out{false},_read_ok{false},_reads_ok{false},sep{' '},check{true},_nr{0},nhead{0},ihead{0}{
		_head.clear();
		_whead.clear();
		_file.clear();
	}
	/*
	cl_read_file_str(string __fname,int _nhead, int _ihead):
	     _init_ok{true},_nhead_ok{true},_ihead_ok{true},out{false},_read_ok{false},sep{' '},check{true},
		 _fname{__fname},nhead{_nhead},ihead{_ihead}{
		_head.clear();
		_whead.clear();
		_file.clear();
	}
	cl_read_file_str(string __fname,int _nhead, int _ihead,string _sep):
	     _init_ok{true},_nhead_ok{true},_ihead_ok{true},out{false},_read_ok{false},
		 _fname{__fname},nhead{_nhead},ihead{_ihead},sep{_sep},check{true}{
		 _head.clear();
		_whead.clear();
		_file.clear();
	}
	cl_read_file_str(string __fname,int _nhead, int _ihead,bool _check, bool _out=false):
	     _init_ok{true},_nhead_ok{true},_ihead_ok{true},out{_out},_read_ok{false},sep{' '},check{_check},
		_fname{__fname},nhead{_nhead},ihead{_ihead}{
		_head.clear();
		_whead.clear();
		_file.clear();
	}*/
    cl_read_file_str(string __fname,int _nhead, int _ihead,string _sep=" ",bool _check=true, bool _out=false,bool read_now=true):
	     _init_ok{true},_nhead_ok{true},_ihead_ok{true},out{_out},_read_ok{false},_reads_ok{false},
		 _fname{__fname},nhead{_nhead},ihead{_ihead},sep{_sep},check{_check},_nr{0}{
		 _head.clear();
		 _whead.clear();
		 _file.clear();
		 if(read_now){
		   read();
		 }
		 //readmap();
	}
    ~cl_read_file_str(){
		//if(out)cout<<"free memory"<<endl;
		free();
	}
	string file_name();
};

ostream & operator<< (ostream &ret, cl_read_file_str &rf);

string to_string_rf(string value);
void f_extract(string &line,string separator,vector<string>&v,bool check,int il,string &_fname);

void f_extract(string &line,string separator,vector<string> &v,bool check, int il,string &_fname);
vector<string> f_get_column(cl_read_file_str&file,string pattern);




#endif


#include "gsl_spline_v3_pwh.hpp"

//**** gsl_spline declaration ****



void cl_spline::help(){
   cout<<"cl_spline:"<<endl;
   cout<<"This class can be used to calculated spline polynomial fitted to the vector_x and vector_y"<<endl;
   cout<<"Initialisation methods:"<<endl;
   cout<<"   cl_spline<T> spline;"<<endl;
   cout<<"   spline.init(vector_x,vector_y);"<<endl;
   cout<<endl;
   cout<<"   cl_spline<T> spline(vector_x,vector_y);"<<endl;
   cout<<endl;
   cout<<"   cl_spline<T> spline(iterator x0,iterator xe,iterator y0,iterator ye);"<<endl;
   
   cout<<"   cspline(string interp_type, string opt) - calculate spline polynomial"<<endl; 
   cout<<"           interp_type = linear, cspline, akima (default = akima)"<<endl;
   cout<<"   plot() - plot data and fitted spline"<<endl;
   cout<<"   plot(gi,gs,line1,line2,line3,title,xtitle,ytitle,xsize ysize,color_background,color_text) "<<endl;
   cout<<"   plotd() - plot derivative of the fitted spline"<<endl;
   cout<<"   plotd(gi,gs,line1,line2,line3,title,xtitle,ytitle,xsize ysize,color_background,color_text) "<<endl;
   cout<<"   plotd2() - plot second derivative of the  fitted spline"<<endl;
   cout<<"   plotd2(gi,gs,line1,line2,line3,title,xtitle,ytitle,xsize ysize,color_background,color_text) "<<endl;
   cout<<"   np - intiger, number of additional points beween original data used in the plot() function, (default = 5)"<<endl;  
   cout<<"   out - if true some output will be given"<<endl;
   cout<<"   e(T x) - return a value of the spline polynomial at argument x"<<endl;
   cout<<"   ed(T x) - return a derivative of the spline polynomial at argument x"<<endl;
   cout<<"   ed2(T x) - return second derivative of the spline polynomial at argument x"<<endl;
   cout<<"   ok() - check if the last use of e() or ed() was a success"<<endl;
   cout<<"   xmin(),xmax() - minimal and maximal values of the vector_x"<<endl; 
}

// Overloaded assignment
cl_spline& cl_spline::operator=(const cl_spline &spline){
	 clock_t begin=clock();
	 if(this == &spline)return (*this);
	 
		 //cout << "Copy constructor called"<<endl;
		 //cout<<"name="<<spline.name<<endl;
		 //cout<<"spline._nx="<<spline._nx<<endl;
		 if(spline._spline_ok){	
		    if((spline._interp_type == "akima") && (spline._nx>5))_spline= gsl_spline_alloc (gsl_interp_akima,spline._nx);
            else if ((((spline._interp_type == "cspline") && (spline._nx>2)) || ((spline._interp_type == "akima") && (spline._nx<=5))) && (spline._nx>2))_spline= gsl_spline_alloc (gsl_interp_cspline,spline._nx);
            else if ((spline._interp_type == "linear") || (spline._nx==2))_spline= gsl_spline_alloc (gsl_interp_linear,spline._nx);
            else{
	           f_alert("cl_spline: interp_type = "+spline._interp_type+" is unknown ");
            }    
            _acc=gsl_interp_accel_alloc();
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
			//name=spline.name+"c";
			//cout<<"name="<<name<<" "<<_init_ok<<" "<<_spline_ok<<" "<<spline._spline_ok<<endl;
		    //cout << "Copy constructor end"<<endl;
	_time=double(clock() - begin) / CLOCKS_PER_SEC;		
	return(*this);
}


void cl_spline::show(){
   if(_spline_ok){
	  cout<<"to be determined"<<endl;
   }else{
	  f_alert("cl_spline: show() problem, use cspline() first");   
   }
}


T cl_spline::e(T x){
   if(_spline_ok){
     if(x>=_xmin && x<= _xmax){
        _ok=true;
		  _iv=1;
		  _xi=x;
          _yi=static_cast<T>(gsl_spline_eval(_spline,x,_acc));
		  return(_yi);
      }else{
		  _ok=false;
		  _iv=false;
          if(x<_xmin){
              _spline->interp->xmin=x;
              _yi=static_cast<T>(gsl_spline_eval(_spline,x,_acc));
          }else{
              _spline->interp->xmax=x;
              _yi=static_cast<T>(gsl_spline_eval(_spline,x,_acc));
          }
		  if(out)f_alert("cl_spline: gsl_spline_eval problem, x out of range; y set to 0",false);
	  }
   }else{
	   f_alert("cl_spline: e() problem, use cspline() first");   
   }
   return(_yi);
}

vector<bool>& cl_spline:: okv(){
	if(_spline_ok){
		return(_okv);
	}else{
	   f_alert("cl_spline: okv() problem, use cspline) first",false);
	}
	return(_okv);
}

vector<T>& cl_spline::e(vector<T> &x){
   if(x.size()>0){
	  size_t n=x.size();
	  //_okv.clear();
	  _okv.resize(n);
          //vector<T>yi(n);
	  _yiv.resize(n);
	  _xiv.resize(n);
      if(_spline_ok){
	     _ok=true;
	     for(size_t i=0;i<n;++i){
	        if(x[i]>=_xmin && x[i]<= _xmax){
			   _xiv[i]=x[i];
               _yiv[i]=static_cast<T>(gsl_spline_eval(_spline,x[i],_acc));
			   _okv[i]=true;
            }else{
			   _yiv[i]=0;
			   _xiv[i]=x[i];
		       _ok=false;
			   _okv[i]=false;
		       if(out)f_alert("cl_spline: gsl_spline_eval problem, x out of range; y set to 0",false);
	        }
	     }
         _iv=2;
         return(_yiv);
	  }else{
	     f_alert("cl_spline: e() problem, use cspline() first");   
      }
   }else{
	 f_alert("cl_spline: e(vector_x) - empty vector");   
   }
    return(_yiv);
}


template<class T>
int f_find_ind_s_root(int &i0,int &im,int &ie,T *it0,int n,T &v){
	if( ie-i0 >=2 ){
	 if(*(it0+im)>v){
	   ie=im;
	   im=(i0+im)/2;
	   f_find_ind_s_root(i0,im,ie,it0,n,v);	
	 }else{
	   i0=im;
	   im=(im+ie)/2;
	   f_find_ind_s_root(i0,im,ie,it0,n,v);		   
	 }
    }
    return(i0);	
}
template<class T>
int f_find_ind_s(T *it0,int ie,T v){
    //cout<<*it0<<" "<<*(it0+ie-1)<<endl;
	if(v<*it0)return(-1);
	if(v>*(it0+ie-1))return(-2);
	int i0=0;
	int im=ie/2;
	int ind=f_find_ind_s_root(i0,im,ie,it0,ie,v);
	return(ind);
}


T cl_spline::nearestx(T x){
   if(!_init_ok){
      f_alert("cl_spline: nearestx() problem, use init() first");     
   }
   int ind=f_find_ind_s(_spline->x,_nx,x);
   if(ind<_nx-1){
      if(abs(x-*(_spline->x+ind+1))<abs(x-*(_spline->x+ind))){
        ++ind;   
      }
   }
   //cout<<"ind="<<ind<<endl;
   return(*(_spline->x+ind));
}

T cl_spline::nearesty(T y){
   if(!_init_ok){
      f_alert("cl_spline: nearestx() problem, use init() first");     
   }
   int ind=f_find_ind_s(_spline->y,_nx,y);
   //cout<<"ind="<<ind<<endl;
   if(ind<_nx-1){
      if(abs(y-*(_spline->y+ind+1))<abs(y-*(_spline->y+ind))){
        ++ind;   
      }
   }
   return(*(_spline->y+ind));
}


T cl_spline::ed(T x){
   if(_spline_ok){
	  if(x>=_xmin && x<= _xmax){
		  _ok=true;
		  _iv=3;
		  _xi=x;
          _yi=static_cast<T>(gsl_spline_eval_deriv(_spline,x,_acc));
		  return(_yi);
      }else{
		  _ok=false;
		  _iv=false;
          if(x<_xmin){
              _spline->interp->xmin=x;
              _yi=static_cast<T>(gsl_spline_eval_deriv(_spline,x,_acc));
          }else{
              _spline->interp->xmax=x;
              _yi=static_cast<T>(gsl_spline_eval_deriv(_spline,x,_acc));
          }
		  if(out)f_alert("cl_spline: gsl_spline_eval_deriv problem, x out of range; y set to 0",false);
	  }
   }else{
	   f_alert("cl_spline: ed() problem, use cspline() first");   
   }
   return(_yi);
}


vector<T>& cl_spline::ed(vector<T> &x){
   if(x.size()>0){
	  size_t n=x.size();
	  //_okv.clear();
	  _okv.resize(n);
      //vector<T>yi(n);
	  _yiv.resize(n);
	  _xiv.resize(n);
      if(_spline_ok){
	     _ok=true;
	     for(size_t i=0;i<n;++i){
	        if(x[i]>=_xmin && x[i]<= _xmax){
			   _xiv[i]=x[i];
               _yiv[i]=static_cast<T>(gsl_spline_eval_deriv(_spline,x[i],_acc));
			   _okv[i]=true;
            }else{
			   _yiv[i]=0;
			   _xiv[i]=x[i];
		       _ok=false;
			   _okv[i]=false;
		       if(out)f_alert("cl_spline: gsl_spline_eval_deriv problem, x out of range; y set to 0",false);
	        }
	     }
         _iv=4;
         return(_yiv);
	  }else{
	     f_alert("cl_spline: ed() problem, use cspline() first");   
      }
   }else{
	 f_alert("cl_spline: e(vector_x) - empty vector");   
   }
   return(_yiv);
}

T cl_spline::ed2(T x){
   if(_spline_ok){
	  if(x>=_xmin && x<= _xmax){
		  _ok=true;
		  _iv=5;
		  _xi=x;
          _yi=static_cast<T>(gsl_spline_eval_deriv2(_spline,x,_acc));
		  return(_yi);
      }else{
		  _ok=false;
          if(x<_xmin){
              _spline->interp->xmin=x;
              _yi=static_cast<T>(gsl_spline_eval_deriv2(_spline,x,_acc));
          }else{
              _spline->interp->xmax=x;
              _yi=static_cast<T>(gsl_spline_eval_deriv2(_spline,x,_acc));
          }
		  if(out)f_alert("cl_spline: gsl_spline_eval_deriv2 problem, x out of range; y set to 0",false);
		  return(0);
	  }
   }else{ 
	  f_alert("cl_spline: ed2() problem, use cspline() first");   
   }
}

vector<T>& cl_spline::ed2(vector<T> &x){
   if(x.size()>0){
	  size_t n=x.size();
	  //_okv.clear();
	  _okv.resize(n);
      //vector<T>yi(n);
	  _yiv.resize(n);
	  _xiv.resize(n);
      if(_spline_ok){
	     _ok=true;
	     for(size_t i=0;i<n;++i){
	        if(x[i]>=_xmin && x[i]<= _xmax){
			   _xiv[i]=x[i];
               _yiv[i]=static_cast<T>(gsl_spline_eval_deriv2(_spline,x[i],_acc));
			   _okv[i]=true;
            }else{
			   _yiv[i]=0;
			   _xiv[i]=x[i];
		       _ok=false;
			   _okv[i]=false;
		       if(out)f_alert("cl_spline: gsl_spline_eval_deriv2 problem, x out of range; y set to 0",false);
	        }
	     }
         _iv=6;
//          return(_yiv);
	  }else{
	     f_alert("cl_spline: ed2() problem, use cspline() first");   
      }
   }else{
	 f_alert("cl_spline: e(vector_x) - empty vector");   
   }
   return(_yiv);
}

bool cl_spline::ok(){
   return(_ok);
}
bool cl_spline::spline_ok(){
   return(_spline_ok);
}

T cl_spline::xmax(){
   if(!_spline_ok){
	  f_alert("cl_spline: xmax problem, use cpline() first");   
   }
   return(_xmax);
}

T cl_spline::xmin(){
   if(!_spline_ok){
	  f_alert("cl_spline: xmin problem, use cpline() first");   
   }
    return(_xmin);
}
int cl_spline::n(){
   if(!_spline_ok){
	  f_alert("cl_spline: n() problem, use cpline() first");   
   }
    return(_nx);
}	

void cl_spline::free(){
   gsl_interp_accel_free(_acc);
   //cout<<"acc free ok"<<endl;
   gsl_spline_free(_spline);
   //cout<<"free spline ok"<<endl;
   
}

void cl_spline::init(vector<T>&x,vector<T>&y){
    x0=x.begin();
	xe=x.end();
	y0=y.begin();
	ye=y.end();
	_init_ok=true;
    if(_spline_ok)free();
	_spline_ok=false;
    _iv=0;
}

void cl_spline::init( vector<T>::iterator _x0, vector<T>::iterator _xe, vector<T>::iterator _y0, vector<T>::iterator _ye){
    x0=_x0;
	xe=_xe;
	y0=_y0;
	ye=_ye;
	_init_ok=true;
    if(_spline_ok)free();
	_spline_ok=false;
    _iv=0;
}


//  Left source half is A[ iBegin:iMiddle-1].
// Right source half is A[iMiddle:iEnd-1   ].
// Result is            B[ iBegin:iEnd-1   ].
void TopDownMerge4_spline(vector<T>::iterator A,vector<T>::iterator C, size_t iBegin, size_t iMiddle, size_t iEnd, vector<T>::iterator B,vector<T>::iterator D){
    size_t i = iBegin, j = iMiddle;
    // While there are elements in the left or right runs...
    vector<T>::iterator itB=B+iBegin;
    vector<T>::iterator itD=D+iBegin;
    vector<T>::iterator itBe=B+iEnd;
    vector<T>::iterator itAi=A+iBegin;
    vector<T>::iterator itAj=A+iMiddle;
    vector<T>::iterator itCi=C+iBegin;
    vector<T>::iterator itCj=C+iMiddle;
  
	for (; itB < itBe; itB++,itD++) {
        // If left run head exists and is <= existing right run head.
        if (i < iMiddle && (j >= iEnd || *itAi <= *itAj)) {
            *itB = *itAi;
			*itD = *itCi;
            i = i + 1;
			itAi++;
			itCi++;
        } else {
            *itB = *itAj;
			*itD = *itCj;
			j = j + 1; 
			itAj++;
			itCj++;
        }
    } 
}
// Sort the given run of array A[] using array B[] as a source.
// iBegin is inclusive; iEnd is exclusive (A[iEnd] is not in the set).

void TopDownSplitMerge4_spline(vector<T>::iterator B,vector<T>::iterator D, size_t iBegin, size_t iEnd, vector<T>::iterator A, vector<T>::iterator C){
    if(iEnd - iBegin < 2) {                      // if run size == 1
        return;                                 //   consider it sorted
	}
    // split the run longer than 1 item into halves
    size_t iMiddle = (iEnd + iBegin) / 2;              // iMiddle = mid point
    // recursively sort both runs from array A[] into B[]
    TopDownSplitMerge4_spline(A,C, iBegin,  iMiddle, B,D);  // sort the left  run
    TopDownSplitMerge4_spline(A,C, iMiddle,    iEnd, B,D);  // sort the right run
    // merge the resulting runs from array B[] into A[]
    TopDownMerge4_spline(B,D, iBegin, iMiddle, iEnd, A,C);
}

void f_sort_m_spline(T typex, T typey,  vector<T>::iterator A0,  vector<T>::iterator Ae, vector<T>::iterator C0,  vector<T>::iterator Ce){//iterator to the begining and end of tha A table
	size_t n=distance(A0,Ae);
	//cout<<"n="<<n<<endl;
	//class vector<T>::iterator it;
    vector<T> B(n);
    vector<T> D(n);     // duplicate array A[] into B[]
    vector<T>::iterator it=A0,itB=B.begin();
    vector<T>::iterator itD=D.begin(),itC=C0;
	for(;it<Ae;it++,itB++,itD++,itC++){
	  *itB=*it;	
	  *itD=*itC;
	}
	//cout<<"B:="<<B<<endl;
    TopDownSplitMerge4_spline(B.begin(),D.begin(), 0, n, A0,C0);   // sort data from B[] into A[]
}


void cl_spline::cspline(string interp_type,string opt,bool out){
	clock_t begin=clock();
    if(_init_ok){
		_nx=distance(x0,xe);
		_ny=distance(y0,ye);
		if(_nx!=_ny){
			f_alert("cl_spline: vector size problem, x size is not equal to the y size");
		}else if (_nx==0){
		    f_alert("cl_spline: empty vectors x and y");	
		}else if (_nx==1){
		    f_alert("cl_spline: nearly empty vectors x and y, n = 1; et least two elements are necessary");	
		}else{
			_spline_ok=true;
			_interp_type=interp_type;
			T typex=0;
			T typey=0;
			if(opt=="sort"){
	           if(out)cout<<"sorting"<<endl;
               f_sort_m_spline(typex,typey,x0,xe,y0,ye);
            }else if(opt=="check_edges_and_sort"){
	           if(*x0>*(xe-1)){
	              if(out)cout<<"sorting"<<endl;
	              f_sort_m_spline(typex,typey,x0,xe,y0,ye);
	           }
            }else if(opt=="check_edges_and_reverse"){
	           if(*x0>*(xe-1)){
	              if(out)cout<<"reversing"<<endl;
	              reverse(x0,xe);
	              reverse(y0,ye);
	           }
            }else if(opt=="dn"){
	           //do nothing
	           }else{
			   f_alert("cl_spline: opt = "+opt+" is unknown");	
			}
			
			_xmin=*x0;
			_xmax=*(xe-1);
			
			//for(class vector<T>::iterator it=x0,ity=y0;it<xe;it++,ity++){
			//  cout<<"x="<<*it<<endl;
			//  cout<<"y="<<*ity<<endl;
			//}
			//cout<<"_nx="<<_nx<<endl;
			//cout<<"_ny="<<_ny<<endl;
			
			if((interp_type == "akima") && (_nx>5))_spline= gsl_spline_alloc (gsl_interp_akima,_nx);
            else if ((((interp_type == "cspline") && (_nx>2)) || ((interp_type == "akima") && (_nx<=5))) && (_nx>2))_spline= gsl_spline_alloc (gsl_interp_cspline,_nx);
            else if ((interp_type == "linear") || (_nx==2))_spline= gsl_spline_alloc (gsl_interp_linear,_nx);
            else{
	           f_alert("cl_spline: interp_type = "+interp_type+" is unknown ");
            }
            
            _acc=gsl_interp_accel_alloc();
            int ok=gsl_spline_init(_spline, &*x0, &*y0, _nx);
            if(ok!=0)if(out)cout<<"ok="<<ok<<" "<<*x0<<endl;

		}
	}else{
	   f_alert("cl_spline: problem with cspline(), use init(vector_x,vector_y) first");	
	}
	_time=double(clock() - begin) / CLOCKS_PER_SEC;
}




int f_find_ind_s_root(int &i0,int &im,int &ie,T *it0,int n,T &v){
    if( ie-i0 >=2 ){
     if(*(it0+im)>v){
       ie=im;
       im=(i0+im)/2;
       f_find_ind_s_root(i0,im,ie,it0,n,v);
     }else{
       i0=im;
       im=(im+ie)/2;
       f_find_ind_s_root(i0,im,ie,it0,n,v);
     }
    }
    return(i0);
}
int f_find_ind_s(T *it0,int ie,T v){
    //cout<<*it0<<" "<<*(it0+ie-1)<<endl;
    if(v<*it0)return(-1);
    if(v>*(it0+ie-1))return(-2);
    int i0=0;
    int im=ie/2;
    int ind=f_find_ind_s_root(i0,im,ie,it0,ie,v);
    return(ind);
}


//** spline gsl **
  
  

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

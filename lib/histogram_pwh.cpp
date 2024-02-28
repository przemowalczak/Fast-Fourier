#include "histogram_pwh.hpp"
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

typedef double T;

ostream & operator<< (ostream &ret, cl_histogram &rf){
   ret<<" x_mid   N  "<<endl;	
   for(size_t i=0;i<rf.x().size();++i){
      ret<<rf.x()[i]<<" "<<rf.N()[i]<<" "<<endl;
   }
   if(rf.isF()){
	 ret<<" empirical distribuant:"<<endl;
	 ret<<" x   n  "<<endl;	
	 for(size_t i=0;i<rf.x().size();++i){
        ret<<rf.xF()[i]<<" "<<rf.yF()[i]<<" "<<endl;
     }   
   }
   return(ret);
}        


//  Left source half is A[ iBegin:iMiddle-1].
// Right source half is A[iMiddle:iEnd-1   ].
// Result is            B[ iBegin:iEnd-1   ].
void cl_histogram::TopDownMerge3_histogram(typename vector<T>::iterator A, size_t iBegin, size_t iMiddle, size_t iEnd, typename vector<T>::iterator B){
    size_t i = iBegin, j = iMiddle;

    // While there are elements in the left or right runs...
    typename vector<T>::iterator itB=B+iBegin;
	typename vector<T>::iterator itBe=B+iEnd;
	typename vector<T>::iterator itAi=A+iBegin;
	typename vector<T>::iterator itAj=A+iMiddle;

    for (; itB < itBe;itB++) {
        // If left run head exists and is <= existing right run head.
        if (i < iMiddle && (j >= iEnd || itAi <= itAj)) {
            itB = itAi;
            i = i + 1;
			itAi++;
        } else {
            *itB = *itAj;
            j = j + 1;
			itAj++;
        }
    }
}
// Sort the given run of array A[] using array B[] as a source.
// iBegin is inclusive; iEnd is exclusive (A[iEnd] is not in the set).
void cl_histogram::TopDownSplitMerge3_histogram(typename vector<T>::iterator B, size_t iBegin, size_t iEnd, typename vector<T>::iterator A){

    if(iEnd - iBegin < 2) {                      // if run size == 1
        return;                                 //   consider it sorted
	}
    // split the run longer than 1 item into halves
    size_t iMiddle = (iEnd + iBegin) / 2;              // iMiddle = mid point
    // recursively sort both runs from array A[] into B[]
    TopDownSplitMerge3_histogram(A, iBegin,  iMiddle, B);  // sort the left  run
    TopDownSplitMerge3_histogram(A, iMiddle,    iEnd, B);  // sort the right run
    // merge the resulting runs from array B[] into A[]
    TopDownMerge3_histogram(B, iBegin, iMiddle, iEnd, A);
}
// Array A[] has the items to sort; array B[] is a work array.
void cl_histogram::f_sort_mi_histogram(vector<T> &A){//iterator to the begining and end of tha A table
	//size_t n=distance(A0,Ae);
	//cout<<"n="<<n<<endl;
	vector<T> B(A.size());//=A;     // duplicate array A[] into B[]
	for(typename vector<T>::iterator it=A.begin(),itB=B.begin();it<A.end();it++,itB++){
	  *itB=*it;
	}
	//cout<<"B:="<<B<<endl;
    TopDownSplitMerge3_histogram(B.begin(), 0, A.size(), A.begin());   // sort data from B[] into A[]
}



void cl_histogram::compute(){
   _mean=cmean();
   _D=csd();
   _mediana=cmediana();
   _moda=cmoda();
   _compute_ok=true;
}

void cl_histogram::print(){
   cout<<"cl_histogram: class: n = "<<f_c("cyan")<<_n<<f_reset()<<endl;
   cout<<"cl_histogram: elements = "<<f_c("cyan")<<_nelements<<f_reset()<<endl;
   if(_mean_ok){
     cout<<"cl_histogram: Mean = "<<f_c("cyan")<<_mean<<f_reset()<<endl;
   }
   if(his_ok){
     cout<<"cl_histogram: sum = "<<f_c("cyan")<<_sum<<f_reset()<<endl;
   }
   if(_D_ok){
     cout<<"cl_histogram: Standard deviation (S*) = "<<f_c("cyan")<<_D<<f_reset()<<"  S*2 = "<<f_c("red")<<_D2<<f_reset()<<endl;
	 cout<<"cl_histogram: Standard deviation (S) = "<<f_c("cyan")<<Do()<<f_reset()<<"  S2 = "<<f_c("red")<<Do2()<<f_reset()<<endl;
   }
   if(_mediana_ok){
	  cout<<"cl_histogram: mediana = "<<f_c("cyan")<<_mediana<<f_reset()<<endl;  
   }
   if(_moda_ok){
	  cout<<"cl_histogram: moda = "<<f_c("cyan")<<_moda<<f_reset()<<endl;  
   }
   if(his_ok){
     cout<<"cl_histogram: xmax = "<<f_c("cyan")<<xmax<<f_reset()<<endl;
     cout<<"cl_histogram: xmin = "<<f_c("cyan")<<xmin<<f_reset()<<endl;
     cout<<"cl_histogram: Nmax = "<<f_c("cyan")<<_Nmax<<f_reset()<<endl;
     cout<<"cl_histogram: Nmin = "<<f_c("cyan")<<_Nmin<<f_reset()<<endl;
   }
    if(_sd_ok){
       
      cout<<"\033[0;35;49m";  	
	  cout<<"Podobnie jak trzeci moment centralny, współczynnik asymetrii przyjmuje wartość zero dla rozkładu symetrycznego, wartości ujemne dla rozkładów o lewostronnej asymetrii (wydłużone lewe ramię rozkładu) i wartości dodatnie dla rozkładów o prawostronnej asymetrii (wydłużone prawe ramię rozkładu)"<<endl;
	  cout<<"Współczynnik asymetrii ma tę przewagę nad trzecim momentem centralnym, że można porównywać jego bezwzględne wartości z różnych rozkładów."<<endl;
	  cout<< "\033[0m";
      cout.flush();
       
      cout<<"cl_histogram: asymmetry factor (g1) = "<<f_c("yellow")<<_g1<<f_reset();
      if(_g1==0){cout<<"  /\\";}
      else if(_g1<0){cout<<"  /|";}
      else{cout<<"  |\\";}
      cout<<endl;
      cout<<"cl_histogram: asymmetry factor (g1*) = "<<f_c("yellow")<<_g1no<<f_reset();
      if(_g1no==0){cout<<"  /\\";}
      else if(_g1no<0){cout<<"  /|";}
      else{cout<<"  |\\";}
      cout<<endl;
   }
   if(_sd_ok){
      cout<<"\033[0;35;49m"; 
      cout<<"Wbrew stwierdzeniom obecnym w niektórych podręcznikach, kurtoza nie mierzy \"spłaszczenia\", \"wysmukłości\" ani \"spiczastości\" rozkładu. Na kurtozę ma wpływ intensywność występowania wartości skrajnych, mierzy więc ona, co się dzieje w \"ogonach\" rozkładu, natomiast kształt \"czubka\" rozkładu jest praktycznie bez znaczenia. "<<endl;

      cout<<"Rozkłady prawdopodobieństwa można podzielić ze względu na wartość kurtozy na rozkłady:"<<endl;

      cout<<"mezokurtyczne (K = 0) – wartość kurtozy wynosi 0, intensywność wartości skrajnych jest podobna do intensywności wartości skrajnych rozkładu normalnego (dla którego kurtoza wynosi dokładnie 0)"<<endl;
      cout<<"leptokurtyczne (K > 0) – kurtoza jest dodatnia, intensywność wartości skrajnych jest większa niż dla rozkładu normalnego (ogony rozkładu są grubsze)"<<endl;
      cout<<"platykurtyczne (K < 0) – kurtoza jest ujemna, intensywność wartości skrajnych jest mniejsza niż w przypadku rozkładu normalnego (ogony rozkładu są węższe). "<<endl;
      cout<< "\033[0m";
      cout.flush();
      cout<<"cl_histogram: kurtosis (g2) = "<<f_c("green")<<_g2<<f_reset()<<endl;
      cout<<"cl_histogram: kurtosis (g2*) = "<<f_c("green")<<_g2no<<f_reset()<<endl;
   }
   
}


void cl_histogram::printtex(){
   cout<<endl;
   cout<<"n = "<<_n<<" \\\\"<<endl;
   cout<<"elements = "<<_nelements<<" \\\\"<<endl;
   if(_mean_ok){
     cout<<"Mean = "<<_mean<<" \\\\"<<endl;
   }
   if(his_ok){
     cout<<"sum = "<<_sum<<" \\\\"<<endl;
   }
   if(_D_ok){
     cout<<"Standard deviation (S$^*$) = "<<_D<<"  S$^{*2}$ = "<<_D2<<" \\\\"<<endl;
     cout<<"Standard deviation (S) = "<<Do()<<"  S$^2$ = "<<Do2()<<" \\\\"<<endl;
   }
   if(_mediana_ok){
      cout<<"mediana = "<<_mediana<<" \\\\"<<endl;
   }
   if(_moda_ok){
      cout<<"moda = "<<_moda<<" \\\\"<<endl;
   }
   if(his_ok){
     cout<<"$x_{\\rm{max}} = "<<xmax<<"$ \\\\"<<endl;
     cout<<"$x_{\\rm{min}}  = "<<xmin<<"$ \\\\"<<endl;
     cout<<"$N_{\\rm{max}} = "<<_Nmax<<"$ \\\\"<<endl;
     cout<<"$N_{\\rm{min}} = "<<_Nmin<<"$ \\\\"<<endl;
   }
    if(_sd_ok){
       
      cout<<"asymmetry factor ($g_1) = "<<_g1<<"$";
      //if(_g1==0){cout<<"  /\\";}
      //else if(_g1<0){cout<<"  /|";}
      //else{cout<<"  |\\";}
      cout<<" \\\\"<<endl;
      cout<<"asymmetry factor ($g_{1}^*) = "<<_g1no<<"$";
      //if(_g1no==0){cout<<"  /\\";}
      //else if(_g1no<0){cout<<"  /|";}
      //else{cout<<"  |\\";}
      cout<<" \\\\"<<endl;
   }
   if(_sd_ok){
      cout<<"kurtosis ($g_2) = "<<_g2<<"$ \\\\"<<endl;
      cout<<"kurtosis ($g_2^*) = "<<_g2no<<"$ \\\\"<<endl;
   }
   cout<<endl;
   
}


void cl_histogram:: printall(){
   if(!his_ok){
	    f_alert("cl_histogram:save() proble, use his() first"); 
   }else{
      cout<<" xmid_i  n_i  i  x_0 x_e n_i/N n_i/N/dx"<<endl;
      for(size_t i=0;i<xv.size();++i){
         cout<<xv[i]<<" "<<Nv[i]<<" "<<i<<" "<<xrangev[i][0]<<" "<<xrangev[i][1]<<" "<<Nv[i]/_sum<<" "<<Nv[i]/_sum/_dx<<endl;
      }
      cout<<endl;
   }
}



T cl_histogram:: sum(){
   return(_sum);
}

bool cl_histogram:: isF(){
   return(_eF_ok);
}


T cl_histogram:: g1(){
   return(_g1no);
}
T cl_histogram:: g1o(){
    return(_g1);
}
T cl_histogram:: g2(){
   return(_g2no);
}
T cl_histogram:: g2o(){
   return(_g2);
}

vector<T>& cl_histogram:: yF(){
   if(!_eF_ok){
	   f_alert("use eF() first");   
   }
   return(_yF);
}

T cl_histogram:: yFx(T x){
   if(!_eF_ok){
	   f_alert("use eF() first");   
   }
   
   bool ok=false;
   int ind=-1;
   
   T r=0;
   
   if(x<xrangev[0][0]){
     r=0;    
   }else if(x>xrangev.back()[1]){
     r=1;   
   }else{
   
    for(size_t i=0;i<xv.size();++i){
      if(xrangev[i][0]<=x && xrangev[i][1]>=x){
          ind=i;
          //cout<<"x="<<setprecision(6)<<x<<" xrange="<<xrangev[i]<<" "<<setprecision(6)<<_yF[i]<<endl;
          ok=true;
          r=_yF[i];
          break;
      }
       
    }
   
   }
   
   return(r);
}



vector<T>& cl_histogram:: xF(){
   if(!_eF_ok){
	   f_alert("use eF() first");   
   }
   return(_xF);
}

vector<T>& cl_histogram:: yFN(){
   if(!_eFN_ok){
	   f_alert("use eFN() first");   
   }
   return(_yFN);
}

vector<T>& cl_histogram:: xFN(){
   if(!_eFN_ok){
	   f_alert("use eFN() first");   
   }
   return(_xFN);
}

T cl_histogram:: R(){
   if(!his_ok){
	   f_alert("use his() first");   
   }
   return(_R);
}

T cl_histogram:: dx(){
   if(!his_ok){
	   f_alert("use his() first");   
   }
   return(_dx);
}

vector<T>& cl_histogram:: N(){
   if(!his_ok){
	   f_alert("use his() first");   
   }
   return(Nv);
}

vector<T>& cl_histogram:: x(){
   if(!his_ok){
	   f_alert("use his() first");   
   }
   return(xv);
}

T cl_histogram:: mean(){
   if(!his_ok){
	   f_alert("use his() first");   
   }else if(!_mean_ok){
	   //f_alert("use cmean() first");
	   cmean();
   }
   return(_mean);
}

T cl_histogram:: mediana(){
   if(!his_ok){
	   f_alert("use his() first");   
   }else if(!_mediana_ok){
	   //f_alert("use cmean() first");
	   cmediana();
   }
   return(_mediana);
}

T cl_histogram:: moda(){
   if(!his_ok){
	   f_alert("use his() first");   
   }else if(!_moda_ok){
	   //f_alert("use cmean() first");
	   cmoda();
   }
   return(_moda);
}


T cl_histogram:: sd(){
   if(!his_ok){
	   f_alert("use his() first");   
   }else if(!_D_ok){
	   //f_alert("use csd() first");   	   
	   csd();
   }
   return(_D);
}

T cl_histogram::D(){
   if(!_D_ok){
     csd();
   }
   return(_D);
}

T cl_histogram::D2(){
   if(!_D_ok){
     csd();
   }
   return(_D2);
}

T cl_histogram::Do(){
   if(!_D_ok){
     csd();
   }
   return(_Do);
}

T cl_histogram::Do2(){
   if(!_D_ok){
     csd();
   }
   return(_Do2);
}

vector<vector<T> >& cl_histogram:: xrange(){
   if(!his_ok){
	   f_alert("use his() first");   
   }
   return(xrangev);
}

vector<vector<T> >& cl_histogram:: nrange(){
   if(!his_ok){
	   f_alert("use his() first");   
   }
   return(nrangev);
}
vector<T> &cl_histogram::Nnorm(){
    return (Nnormv);
}
vector<T> &cl_histogram::P(){
    return (Pv);
}
T cl_histogram::quantile(){
    return (_quantile);
}
T cl_histogram::alpha(){
    return (_alpha);
}
T cl_histogram::Nmax(){
    return (_Nmax);
}
T cl_histogram::Nmin(){
    return (_Nmin);
}
T cl_histogram::cquantile(T alpha){
    _alpha=alpha;
    if(his_ok){
        if(!_eF_ok){
            ceF();
        }
        _quantile=_xF[0];
        for(size_t i=0;i<_n;++i){
            if(_yF[i]>alpha){
                if(i>0){
                  if(abs(_yF[i]-alpha)<abs(_yF[i-1]-alpha)){
                       _quantile=_xF[i];
                       //cout<<"taking higher quantile"<<endl;
                  }
                }
                break;
            }
            _quantile=_xF[i];
        }
    }
    return (_quantile);
}
T cl_histogram::cquantile_li(T alpha){
    _alpha=alpha;
    if(his_ok){
        if(!_eF_ok){
            ceF();
        }
        _quantile=_xF[0];

        if(_yF[0]>alpha){
            _quantile=_xF[0];
        }else if(_yF.back()<alpha){
            _quantile=_xF.back();
        }else{

           for(size_t i=0;i<_n;++i){
             if(_yF[i]>=alpha ){
                if(i>0){

                    T a=(_xF[i-1]-_xF[i])/(_yF[i-1]-_yF[i]);
                    T b=_xF[i-1]-a*_yF[i-1];
                    _quantile=a*alpha+b;
                }
                break;
             }

          }
        }
    }
    return (_quantile);
}
void cl_histogram:: ceF(){
    if(his_ok){
	  //cout<<"Empirical distribuant:"<<endl;
	   
	   //_n=xrangev.size();	   
	   _xF.resize(_n);
	   _yF.resize(_n);
       _xF[0]=xrangev[0][1];
       //_xF[0]=xv[0];
       //_yF[0]=Nv[0];
       _yF[0]=Nnormv[0];
       for(int i=1;i<_n;++i){
           _xF[i]=xrangev[i][1];
           //_xF[i]=xv[i];
           //_yF[i]=Nv[i]+_yF[i-1];
           //_yF[i-1]/=_nelements;
           _yF[i]=_yF[i-1]+Nnormv[i];
	   }
	   //for(size_t i=0;i<_n;++i){			 
        //  _yF[_n-1]/=_nelements;
	   //} 
	  _eF_ok=true;
    }else{
      f_alert("cl_histogram:init() ceF() problem: use his() first");
      _eF_ok=false;
    }        
}




double f_Nms2_histogram(double x, void *parameters){
   double f;
   st_params_F_dist_histogram *params= (st_params_F_dist_histogram *)parameters;
   double m=params->m;
   double sigma2=params->sigma2; 
   f=exp(-pow(x-m,2)/(2.0*sigma2))/sqrt(2*M_PI*sigma2);   
   
   return(f);
}



T F_integrate_histogram(double(*f)(double x,void *params),st_params_F_dist_histogram &params,T x0, T xe,int ni,int key,T eps){
    T _fi=0;
    T _error=0;
       size_t nintervals=1e7;
       bool _integrate_ok{false};
	   //st_params_quantile_dist<T> params;

       //**integration Gauss–Legendre quadrature *
       gsl_function F;
   	   //F.function = &quantile_fdist;
	   F.function = f;
	   F.params = &params;
	   gsl_integration_workspace *w=gsl_integration_workspace_alloc(nintervals);
	   T fit,errort;
	   T x0t;
	   T xet;
       if(ni<=0){
		    cout<<"distribution()::integrate() problem, ni nas to be grater than 0"<<endl;
	   }else if(ni>1){
	     T dx=(xe-x0)/(ni-1);
         for(int i=0;i<ni;++i){
		   x0t=x0+i*dx;
		   xet=x0+(i+1)*dx;
		   if(i==ni-1)xet=xe;
	       gsl_integration_qag(&F,x0t,xet,eps,eps,nintervals,key,w,&fit,&errort);
		   _fi+=fit;
		   _error+=errort;
           //cout<<"i="<<i<<setprecision(6)<< _fi<<endl;
	     }
       }else{
		  gsl_integration_qag(&F,x0,xe,eps,eps,nintervals,key,w,&_fi,&_error);
       }
	   gsl_integration_workspace_free (w);
       _integrate_ok=true;
    
    return(_fi);
}


T F_Nms2_histogram(T x,T m,T sigma2){
   T F{0};
   st_params_F_dist_histogram params;
   params.m=m;
   params.sigma2=sigma2;
   T x0=-10*sqrt(sigma2);
   T xe=10*sqrt(sigma2);
   //int ni=round((xe-x0));
   
   //if(ni<1)ni=1;
   int ni=1;
   //cout<<"ni="<<ni<<x0<<" "<<xe<<endl;
   F=F_integrate_histogram(f_Nms2_histogram,params,x0,x,ni,6,1e-6);
   
   
   return(F);
}
  


void cl_histogram::cFN(){
    if(his_ok){
	  //cout<<"Standard Normal  distribuant:"<<endl;
	   //_n=xrangev.size();	   
	   _xFN.resize(_n);
	   _yFN.resize(_n);
       for(int i=0;i<_n;++i){
		   _xFN[i]=xrangev[i][1];
           //_xFN[i]=xv[i];
           _yFN[i]=F_Nms2_histogram(_xFN[i],mean(),D2());
           //_yFN[i]=F_Nms2_histogram(xrangev[i][1],mean(),D2());   
           //cout<<setprecision(6)<< _xFN[i]<<" "<<_yFN[i]<<" mean="<<setprecision(6)<<mean()<<" s2="<<setprecision(6)<<s2()<<endl;
	   }
	  _eFN_ok=true;
    }else{
      f_alert("cl_histogram:init() ceN01() problem: use his() first");
      _eFN_ok=false;
    }        
    
}

void cl_histogram::cFN_center(){
    if(his_ok){
	  //cout<<"Standard Normal  distribuant:"<<endl;
	   //_n=xrangev.size();	   
	   _xFN.resize(_n);
	   _yFN.resize(_n);
       for(int i=0;i<_n;++i){
		   //_xFN[i]=xrangev[i][1];
           _xFN[i]=xv[i];
           //cout<<"_xFN[i]="<<_xFN[i]<<endl;
           _yFN[i]=F_Nms2_histogram(_xFN[i],mean(),D2());
           //_yFN[i]=F_Nms2_histogram(xrangev[i][1],mean(),D2());   
           //cout<<setprecision(6)<< _xFN[i]<<" "<<_yFN[i]<<" mean="<<setprecision(6)<<mean()<<" s2="<<setprecision(6)<<s2()<<endl;
	   }
	  _eFN_ok=true;
    }else{
      f_alert("cl_histogram:init() ceN01() problem: use his() first");
      _eFN_ok=false;
    }        
    
}

void cl_histogram::cFN(T m, T S2){
    if(his_ok){
	  //cout<<"Standard Normal  distribuant:"<<endl;
	   //_n=xrangev.size();	   
	   _xFN.resize(_n);
	   _yFN.resize(_n);
       for(int i=0;i<_n;++i){
		   _xFN[i]=xrangev[i][1];
           //_xFN[i]=xv[i];
           _yFN[i]=F_Nms2_histogram(_xFN[i],m,S2);
           //_yFN[i]=F_Nms2_histogram(xrangev[i][1],mean(),D2());   
           //cout<<setprecision(6)<< _xFN[i]<<" "<<_yFN[i]<<" mean="<<setprecision(6)<<mean()<<" s2="<<setprecision(6)<<s2()<<endl;
	   }
	  _eFN_ok=true;
    }else{
      f_alert("cl_histogram:init() ceN01() problem: use his() first");
      _eFN_ok=false;
    }        
    
}

void cl_histogram:: ceF_for_Kolmogorov(){
    if(his_ok){
	  cout<<"Empirical distribuant:"<<endl;
	   
	   //_n=xrangev.size();	   
	   _xF.resize(_n);
	   _yF.resize(_n);
       for(int i=0;i<_n;++i){
		   _xF[i]=xrangev[i][1];
		     _yF[i]=i+1;
	   }
       for(int i=0;i<_n;++i){
 		  _yF[i]/=_n;
	   } 
	  _eF_ok=true;
    }else{
      f_alert("cl_histogram:init() ceF() problem: use his() first");
      _eF_ok=false;
    }        
}


bool cl_histogram:: init(vector<T> &x){
    if(x.size()>0){
      x0=x.begin();
      xe=x.end();
	  _nelements=x.size();
	  _mediana_ok=false;
	  _moda_ok=false;
	  _mean_ok=false;
	  _D_ok=false;
      _init_ok=true;
	  _compute_ok=false;      
       _eF_ok=false;;
       _eFN_ok=false;;
	   
    }else{
      f_alert("cl_histogram:init() proiblem: x vector has to have at least one element");
      _init_ok=false;
    }
    return (_init_ok);
}




void cl_histogram::his2(int n, bool out){
   if(_init_ok){
      xmax=*x0;
	  xmin=*x0;
      _Nmax=0;
      _Nmin=0;
	  _n=n;
	  typename vector<T>::iterator it;
	  for(it=x0;it<xe;it++){
		  if(*it>xmax)xmax=*it;
		  if(*it<xmin)xmin=*it;
	  }
	  _dx=(xmax-xmin)/(n);
	  _R=xmax-xmin;
      if(out)cout<<"dx = "<<setprecision(6)<< _dx<<" max = "<<xmax<<" min = "<<xmin<<" k="<<n<<endl;
	  if(out)cout<<endl;
	  Nv.clear();
	  //cout<<"x.capacity()="<<x.capacity()<<endl;
	  xv.clear();
	  xrangev.clear();
      nrangev.clear();
	  nrangev.resize(n,vector<T>(2));
	  Nv.resize(n);
	  xv.reserve(n);
	  xrangev.reserve(n);
      //nrangev.reserve(n);
	  //cout<<"x.capacity()="<<x.capacity()<<endl;
      //int nt;
      //bool first=true;
	  vector<T> xrt(2),ntv(2);
      T xc=xmin;
      
      
      vector<T> xv0;
      xv0.reserve(n+1);
      for(int i=0;i<n-1;i++){
          if(out)if(i%100==0)print_progres(i*1.0/(n-1.0),"i="+to_string(i)+" from n="+to_string(n));
		  //if(out)cout<<"i="<<i<<" "<<"xmin="<<min+i*_dx<<" xmax="<<min+(i+1)*_dx<<endl;
		  xv.push_back(xc+_dx/2.0);
          xv0.push_back(xc);
		  xrt[0]=xc;
		  xrt[1]=xc+_dx;
          xc+=_dx;
		  xrangev.push_back(xrt);
		  
	  }
	  //if(out)cout<<"i="<<n<<" "<<"xmin="<<min+n*_dx<<" xmax="<<min+(n+1)*_dx<<endl;
	  xv.push_back(xmax-_dx/2);
	  xv0.push_back(xmax-_dx);
	  xv0.push_back(xmax);
	  xrt[0]=xmax-_dx;
	  xrt[1]=xmax;
	  xrangev.push_back(xrt);
      
	  //cout<<"xv0"<<xv0<<endl;
	  
      for(it=x0;it!=xe;it++){
           int ind=f_find_ind(xv0,*it);
           //cout<<ind<<" xrangev.size()="<<xrangev.size()<<" "<<*it<<endl;
           //cout<<"ind="<<ind<<" "<<setprecision(6)<< *it<<" "<<xrangev[ind][0]<<" -- "<<xrangev[ind][1]<<endl;
           ++Nv[ind];
           //++nrangev[ind][0];
           //++nrangev[ind][1];
      }
      
      for(int i=0;i<n;i++){
        nrangev[i][0]=Nv[i];
        nrangev[i][1]=Nv[i];
        //cout<<setprecision(6)<< xv[i]<<" "<<Nv[i]<<" "<<xrangev[i][0]<<" -- "<<xrangev[i][1]<<" "<<nrangev[i]<<endl;
      }
      
           
      //out<<"N size="<<Nv.size()<<" x size = "<<xv.size()<<endl;
      
      

	  //cout<<"x:"<<endl;
	  //cout<<x<<endl;
	  //cout<<"N(x):"<<endl;
	  //cout<<N<<endl;
	  
	  _sum=0;
      for(int i=0;i<n;i++){
		 _sum+=Nv[i];
	  }
      if(out)cout<<"N max = "<<_Nmax<<" N min = "<<_Nmin<<endl;
	  if(out)cout<<"N sum = "<<_sum<<endl;
      //if(_sum!=_nelements)f_alert("_sum!=_nelements");
	  his_ok=true;
      
      if(out)      cout<<"i  xrangev  xcenter  N_i"<<endl;      
      if(out){
          T sumn=0;
          for(int i=0;i<n;++i){
              sumn+=Nv[i];
              cout<<setprecision(0)<< i<<" "<<setprecision(6)<< xrangev[i]<<" "<<setprecision(6)<< xv[i]<<" "<<setprecision(0)<<Nv[i]<<" "<<setprecision(6)<<Nv[i]/_nelements<<" "<<sumn<<" "<<sumn/_nelements<<endl;
          }
      }
      if(out)      cout<<"xv"<<endl;      
      if(out)cout<<xv<<endl;
      
   }else{
	  f_alert("use init(vector) first");   
   }
}

void cl_histogram::his(int n, bool out){
   if(_init_ok){
      xmax=*x0;
	  xmin=*x0;
      _Nmax=0;
      _Nmin=0;
	  _n=n;
	  typename vector<T>::iterator it;
	  for(it=x0;it<xe;it++){
		  if(*it>xmax)xmax=*it;
		  if(*it<xmin)xmin=*it;
	  }
	  _dx=(xmax-xmin)/(n);
	  _R=xmax-xmin;
      if(out)cout<<"dx = "<<setprecision(6)<< _dx<<" max = "<<xmax<<" min = "<<xmin<<" k="<<n<<endl;
	  if(out)cout<<endl;
	  Nv.clear();
	  //cout<<"x.capacity()="<<x.capacity()<<endl;
	  xv.clear();
	  xrangev.clear();
	  nrangev.clear();
      Nnormv.clear();
      Pv.clear();
	  Nv.reserve(n);
	  xv.reserve(n);
	  xrangev.reserve(n);
      nrangev.reserve(n);
      Nnormv.reserve(n);
      Pv.reserve(n);
	  //cout<<"x.capacity()="<<x.capacity()<<endl;
	  int nt;
	  bool first=true;
	  vector<T> xrt(2),ntv(2);
      T xc=xmin;
      for(int i=0;i<n-1;i++){
          if(out)if(i%100==0)print_progres(i*1.0/(n-1.0),"i="+to_string(i)+" from n="+to_string(n));
		  //if(out)cout<<"i="<<i<<" "<<"xmin="<<min+i*_dx<<" xmax="<<min+(i+1)*_dx<<endl;
		  //xv.push_back(xmin+i*_dx+_dx/2.0);
          xv.push_back(xc+_dx/2.0);
		  xrt[0]=xc;
		  xrt[1]=xc+_dx;
          xc+=_dx;
		  xrangev.push_back(xrt);
		  nt=0;
		  for(it=x0;it<xe;it++){
		    if(*it>=xrt[0] && *it<xrt[1]){
				nt++;
			}
		  }
		  if(first){
             _Nmin=nt;
			 first=false;
		  }
          if(nt>_Nmax)_Nmax=nt;
          if(nt<_Nmin)_Nmin=nt;
		  Nv.push_back(nt);
          ntv[0]=nt;
          ntv[1]=nt;
          nrangev.push_back(ntv);
		  
	  }
	  //if(out)cout<<"i="<<n<<" "<<"xmin="<<min+n*_dx<<" xmax="<<min+(n+1)*_dx<<endl;
	  xv.push_back(xmax-_dx/2);
	  xrt[0]=xmax-_dx;
	  xrt[1]=xmax;
	  xrangev.push_back(xrt);
	  nt=0;
	  for(it=x0;it<xe;it++){
		 if(*it>=xrt[0] && *it<=xrt[1]){
			nt++;
		 }
	  }
      if(nt>_Nmax)_Nmax=nt;
	  Nv.push_back(nt);
      ntv[0]=nt;
      ntv[1]=nt;
      nrangev.push_back(ntv);
	  //cout<<"x:"<<endl;
	  //cout<<x<<endl;
	  //cout<<"N(x):"<<endl;
	  //cout<<N<<endl;
	  
	  _sum=0;
      for(int i=0;i<n;i++){
		 _sum+=Nv[i];
	  }
      for(int i=0;i<n;i++){
         Pv.push_back(Nv[i]/_sum/_dx);
         Nnormv.push_back(Nv[i]/_sum);
      }
      if(out)cout<<"N max = "<<_Nmax<<" N min = "<<_Nmin<<endl;
	  if(out)cout<<"N sum = "<<_sum<<endl;
      //if(_sum!=_nelements)f_alert("_sum!=_nelements");
	  his_ok=true;
      
      if(out)      cout<<"i  xrangev  xcenter  N_i"<<endl;      
      if(out){
          T sumn=0;
          for(int i=0;i<n;++i){
              sumn+=Nv[i];
              cout<<setprecision(0)<< i<<" "<<setprecision(6)<< xrangev[i]<<" "<<setprecision(6)<< xv[i]<<" "<<setprecision(0)<<Nv[i]<<" "<<setprecision(6)<<Nv[i]/_nelements<<" "<<sumn<<" "<<sumn/_nelements<<endl;
          }
      }
      if(out)      cout<<"xv"<<endl;      
      if(out)cout<<xv<<endl;
      
   }else{
	  f_alert("use init(vector) first");   
   }
}

void cl_histogram::his(int n, double xmini,double xmaxi,double dx,bool out){
   if(_init_ok){
      xmax=xmaxi;
	  xmin=xmini;
      _Nmax=0;
      _Nmin=0;
	  _n=n;
	  _dx=dx;
	  _R=xmax-xmin;
      if(out)cout<<"dx = "<<setprecision(6)<< _dx<<" max = "<<xmax<<" min = "<<xmin<<" k="<<n<<endl;
	  if(out)cout<<endl;
	  Nv.clear();
	  //cout<<"x.capacity()="<<x.capacity()<<endl;
	  xv.clear();
	  xrangev.clear();
	  nrangev.clear();
      Nnormv.clear();
      Pv.clear();
	  Nv.reserve(n);
	  xv.reserve(n);
	  xrangev.reserve(n);
      nrangev.reserve(n);
      Nnormv.reserve(n);
      Pv.reserve(n);
	  //cout<<"x.capacity()="<<x.capacity()<<endl;
	  int nt;
	  bool first=true;
	  vector<T> xrt(2),ntv(2);
      T xc=xmin;
      typename vector<T>::iterator it;
      for(int i=0;i<n-1;i++){
          if(out)if(i%100==0)print_progres(i*1.0/(n-1.0),"i="+to_string(i)+" from n="+to_string(n));
		  //if(out)cout<<"i="<<i<<" "<<"xmin="<<min+i*_dx<<" xmax="<<min+(i+1)*_dx<<endl;
		  //xv.push_back(xmin+i*_dx+_dx/2.0);
          xv.push_back(xc+_dx/2.0);
		  xrt[0]=xc;
		  xrt[1]=xc+_dx;
          xc+=_dx;
		  xrangev.push_back(xrt);
		  nt=0;
		  for(it=x0;it<xe;it++){
		    if(*it>=xrt[0] && *it<xrt[1]){
				nt++;
			}
		  }
		  if(first){
             _Nmin=nt;
			 first=false;
		  }
          if(nt>_Nmax)_Nmax=nt;
          if(nt<_Nmin)_Nmin=nt;
		  Nv.push_back(nt);
          ntv[0]=nt;
          ntv[1]=nt;
          nrangev.push_back(ntv);

	  }
	  //if(out)cout<<"i="<<n<<" "<<"xmin="<<min+n*_dx<<" xmax="<<min+(n+1)*_dx<<endl;
	  xv.push_back(xmax-_dx/2);
	  xrt[0]=xmax-_dx;
	  xrt[1]=xmax;
	  xrangev.push_back(xrt);
	  nt=0;
	  for(it=x0;it<xe;it++){
		 if(*it>=xrt[0] && *it<=xrt[1]){
			nt++;
		 }
	  }
      if(nt>_Nmax)_Nmax=nt;
	  Nv.push_back(nt);
      ntv[0]=nt;
      ntv[1]=nt;
      nrangev.push_back(ntv);
	  //cout<<"x:"<<endl;
	  //cout<<x<<endl;
	  //cout<<"N(x):"<<endl;
	  //cout<<N<<endl;

	  _sum=0;
      for(int i=0;i<n;i++){
		 _sum+=Nv[i];
	  }
      for(int i=0;i<n;i++){
         Pv.push_back(Nv[i]/_sum/_dx);
         Nnormv.push_back(Nv[i]/_sum);
      }

      if(out)cout<<"N max = "<<_Nmax<<" N min = "<<_Nmin<<endl;
	  if(out)cout<<"N sum = "<<_sum<<endl;
      //if(_sum!=_nelements)f_alert("_sum!=_nelements");
	  his_ok=true;

      if(out)      cout<<"i  xrangev  xcenter  N_i"<<endl;
      if(out){
          T sumn=0;
          for(int i=0;i<n;++i){
              sumn+=Nv[i];
              cout<<setprecision(0)<< i<<" "<<setprecision(6)<< xrangev[i]<<" "<<setprecision(6)<< xv[i]<<" "<<setprecision(0)<<Nv[i]<<" "<<setprecision(6)<<Nv[i]/_nelements<<" "<<sumn<<" "<<sumn/_nelements<<endl;
          }
      }
      if(out)      cout<<"xv"<<endl;
      if(out)cout<<xv<<endl;

   }else{
	  f_alert("use init(vector) first");
   }
}

void cl_histogram::counts(bool out){
   if(_init_ok){
      xmax=*x0;
	  xmin=*x0;
      _Nmax=0;
      _Nmin=0;
      vector<T> _xu;
	  typename vector<T>::iterator it;
	  for(it=x0;it!=xe;++it){
		  if(*it>xmax)xmax=*it;
		  if(*it<xmin)xmin=*it;
          
          //cout<<"bif _xut=";
          //for(size_t i=0;i<_xu.size();++i){
          //  cout<<setprecision(6)<< _xu[i]<<" ";
         // }
          //cout<<" ---> "<<*it<<" presetn = "<<present(_xu,*it)<<endl;
          if(!present_eps(_xu,*it,1e-8)){
              
              //cout<<"x="<<setprecision(6)<< *it<<endl;
              
             _xu.push_back(*it);   
             
              //cout<<"_xut="<<_xu<<" "<<endl;
             
          }
	  }
	  
	  
	  int n=_xu.size();
	  _n=n;
      
      f_sort_mi_histogram(_xu);
	  
      cout<<"_xu="<<_xu<<endl;
	  
	  _dx=(xmax-xmin)/(n);
	  _R=xmax-xmin;
      if(out)cout<<"dx = "<<setprecision(6)<< _dx<<" max = "<<xmax<<" min = "<<xmin<<" k="<<n<<endl;
	  if(out)cout<<endl;
	  Nv.clear();
	  //cout<<"x.capacity()="<<x.capacity()<<endl;
	  xv.clear();
	  xrangev.clear();
	  nrangev.clear();
	  Nv.reserve(n);
	  xv.reserve(n);
	  xrangev.reserve(n);
      nrangev.reserve(n);
	  //cout<<"x.capacity()="<<x.capacity()<<endl;
	  int nt;
	  bool first=true;
	  vector<T> xrt(2),ntv(2);
      T xc=xmin;
      for(int i=0;i<n;i++){
          if(out)if(i%100==0)print_progres(i*1.0/(n-1.0),"i="+to_string(i)+" from n="+to_string(n));
		  //if(out)cout<<"i="<<i<<" "<<"xmin="<<min+i*_dx<<" xmax="<<min+(i+1)*_dx<<endl;
		  //xv.push_back(xmin+i*_dx+_dx/2.0);
          xv.push_back(_xu[i]);
		  xrt[0]=xc;
		  xrt[1]=xc+_dx;
          xc+=_dx;
		  xrangev.push_back(xrt);
		  nt=0;
          if(i==n-1){
		    for(it=x0;it<xe;it++){
		      if(xrangev[i][0]<=*it && *it<=xrangev[i][1]){
				nt++;
			  }
		    }
          }else{
            for(it=x0;it<xe;it++){
		      if(xrangev[i][0]<=*it && *it< xrangev[i][1]){
				nt++;
			  }
		    }                
          }
		  if(first){
             _Nmin=nt;
			 first=false;
		  }
          if(nt>_Nmax)_Nmax=nt;
          if(nt<_Nmin)_Nmin=nt;
		  Nv.push_back(nt);
          ntv[0]=nt;
          ntv[1]=nt;
          nrangev.push_back(ntv);
		  
	  }
	  //if(out)cout<<"i="<<n<<" "<<"xmin="<<min+n*_dx<<" xmax="<<min+(n+1)*_dx<<endl;
	  //xv.push_back(xmax-_dx/2);
	  /*xrt[0]=xmax-_dx;
	  xrt[1]=xmax;
	  xrangev.push_back(xrt);
	  nt=0;
	  for(it=x0;it<xe;it++){
		 if(*it>=xrt[0] && *it<=xrt[1]){
			nt++;
		 }
	  }
      if(nt>_Nmax)_Nmax=nt;
	  Nv.push_back(nt);
      ntv[0]=nt;
      ntv[1]=nt;
      nrangev.push_back(ntv);
	  */
      //cout<<"x:"<<endl;
	  //cout<<x<<endl;
	  //cout<<"N(x):"<<endl;
	  //cout<<N<<endl;
	  
	  _sum=0;
      for(int i=0;i<n;i++){
		 _sum+=Nv[i];
	  }
      if(out)cout<<"N max = "<<_Nmax<<" N min = "<<_Nmin<<endl;
	  if(out)cout<<"N sum = "<<_sum<<endl;
      //if(_sum!=_nelements)f_alert("_sum!=_nelements");
	  his_ok=true;
      
      if(out)      cout<<"i     xrangev   xcenter   N_i    N_i/N   Sum_0^i  Sum_0^i/N"<<endl;      
      if(out){
          T sumn=0;
          for(int i=0;i<n;++i){
              sumn+=Nv[i];
              cout<<setprecision(0)<< i<<" "<<setprecision(6)<< xrangev[i]<<" "<<setprecision(6)<< xv[i]<<" "<<setprecision(0)<<Nv[i]<<" "<<setprecision(6)<<Nv[i]/_nelements<<" "<<sumn<<" "<<sumn/_nelements<<endl;
          }
      }
      if(out)      cout<<"xv"<<endl;      
      if(out)cout<<xv<<endl;
      
   }else{
	  f_alert("use init(vector) first");   
   }
}




void cl_histogram::adopt(vector<T> &x,vector<T>&N, bool out){
    if(x.size()>0){
	  x0=x.begin();
	  xe=x.end();
      xmax=*x0;
	  xmin=*x0;
      _Nmax=0;
      _Nmin=0;
	  _n=x.size();
	  if(_n!=N.size()){
		  f_alert("cl_histogram::adopt() problem, vectors x and N have to have the same sizes");
	  }
	  typename vector<T>::iterator it;
	  for(it=x0;it<xe;it++){
		  if(*it>xmax)xmax=*it;
		  if(*it<xmin)xmin=*it;
	  }
	  
	  T sumdx=0;
      for(it=x0+1;it<xe;it++){
		  sumdx+=*it-*(it-1);
          //cout<<*it-*(it-1)<<endl;
	  }
	  
	  
	  //_dx=(xmax-xmin)/(_n);
      _dx=sumdx/(_n-1);
      
      if(out)cout<<"dx = "<<_dx<<" max = "<<xmax<<" min = "<<xmin<<endl;
	  if(out)cout<<endl;
	  Nv.clear();
	  //cout<<"x.capacity()="<<x.capacity()<<endl;
	  xv.clear();
	  xrangev.clear();
	  nrangev.clear();
	  Nv.reserve(_n);
	  xv.reserve(_n);
	  xrangev.reserve(_n);
	  //cout<<"x.capacity()="<<x.capacity()<<endl;
	  int nt;
	  bool first=true;
	  vector<T> xrt(2),ntv(2);
      for(int i=0;i<_n;i++){
		  xv.push_back(x[i]);
		  xrt[0]=x[i]-_dx/2.0;
		  xrt[1]=x[i]+_dx/2.0;
		  xrangev.push_back(xrt);
		  nt=N[i];
		  if(first){
             _Nmin=nt;
			 first=false;
		  }
          if(nt>_Nmax)_Nmax=nt;
          if(nt<_Nmin)_Nmin=nt;
		  Nv.push_back(nt);
          ntv[0]=nt;
          ntv[1]=nt;
          nrangev.push_back(ntv);
	  }
	  _sum=0;
      for(int i=0;i<_n;i++){
		 _sum+=Nv[i];
	  }
      for(int i=1;i<_n;i++){
		 if(xrangev[i][0]!=xrangev[i-1][1]){
             xrangev[i][0]=(xrangev[i][0]+xrangev[i-1][1])/2.0;
             xrangev[i-1][1]=xrangev[i][0];
         }
	  }
	  
	  
	  _nelements=_sum;
	  _mediana_ok=false;
	  _moda_ok=false;
	  _mean_ok=false;
	  _D_ok=false;
      _init_ok=true;
	  _compute_ok=false;
	  
      if(out)cout<<"N max = "<<_Nmax<<" N min = "<<_Nmin<<endl;
	  if(out)cout<<"N sum = "<<_sum<<endl;
	  his_ok=true;
      
      if(out)      cout<<"xrangev"<<endl;      
      if(out)cout<<xrangev<<endl;
      if(out)      cout<<"xv"<<endl;      
      if(out)cout<<xv<<endl;
    }
}


T cl_histogram:: cmean(){
    _mean=0;
	if(!his_ok){
	    f_alert("cl_histogram:save() proble, use his() first"); 
     }else{

       for(int i=0;i<_n;++i){
		  _mean+=Nv[i]*xv[i];
		  //cout<<_mean<<" "<<Nv[i]<<" "<<xv[i]<<endl;
	   }
	   _mean/=_nelements;
	   _mean_ok=true;
    }
  	return(_mean);
}

T cl_histogram:: csd(){
    _D2=0;
    _D=0;
    _Do2=0;
    _Do=0;
    _sd_ok=false;
	if(!his_ok){
	    f_alert("cl_histogram:save() proble, use his() first"); 
     }else{
	   if(_nelements>1){
	       if(!_mean_ok)cmean();
           
           T sg3=0;
           T sg4=0;
           for(int i=0;i<_n;++i){
		        _D2+=Nv[i]*pow(xv[i]-_mean,2);
                sg3+=Nv[i]*pow(xv[i]-_mean,3);  
                sg4+=Nv[i]*pow(xv[i]-_mean,4);  
	       }
	       _D2/=(_nelements-1);
           _D=sqrt(_D2);
           _D2=_D*_D;
           _Do=_D*(_nelements-1)/_nelements;
           _Do2=_Do*_Do;  	
		   _D_ok=true;
           
           long unsigned int n=_nelements;
           _g1=sg3/(n*pow(_Do2,1.5));//skupienie
            if(_nelements>2){
                 _g1no=_g1*sqrt(n*(n-1)*1.0)/(n-2.0);
            }else{
                 _g1no=0;   
            }
            cout<<"g1="<<_g1<<" "<<_g1no<<" n="<<n<<" "<<sqrt(n*(n-1.0)*1.0)<<endl;
             // _K=sg2/(n*pow(_Do2,2)); //Kurtoza
            _g2=sg4/(n*pow(_Do2,2))-3.0; // kurtoza, skupienie, splaszczenie
            if(_nelements>3){
                _g2no=n*(n+1)*sg4/(pow(_D2,2)*(n-1)*(n-2)*(n-3))-3*(n-1)*(n-1)/( (n-2)*(n-3));
            }else{
                _g2no=0;   
            }     
           _sd_ok=true;                                 
	   }else{
          f_alert("cl_histogram:csd() problem, vector has to have at least 2 elements",false);
       }
    }
    return(_D);
}



T cl_histogram::cmediana(){
   if(!_init_ok){
	  f_alert("cl_stat:: cmediana problem, use init() first");   
   }

   int nt=0;
   for(int i=0;i<_n;++i){
	  //cout<<"nt="<<nt<<" Nv[i]="<<Nv[i]<<" nt+Nv[i]="<<nt+Nv[i]<<" n/2="<<_nelements/2.0<<endl;;
	  if(nt<=_nelements/2.0 &&  nt+Nv[i]>=_nelements/2.0){
		 if(i>0){
			 _mediana=(xv[i]+xv[i-1])/2.0;
	      }else if(_n>1){
			  _mediana=(xv[i]+xv[i+1])/2.0;
		  }else{
			  _mediana=xv[i];
		  }
		  break;
	  }
      nt+=Nv[i];
   }
   _mediana_ok=true;
   return(_mediana);
}


T cl_histogram::cmoda(){
   if(!_init_ok){
	  f_alert("cl_stat:: cmoda problem, use init() first");   
   }

   int nt=0;
   _moda=0;
   for(int i=0;i<_n;++i){
	  //cout<<"nt="<<nt<<" Nv[i]="<<Nv[i]<<" nt+Nv[i]="<<nt+Nv[i]<<" n/2="<<_nelements/2.0<<endl;;
	  if(nt<Nv[i]){
		 nt=Nv[i];  
		 _moda=xv[i];
	  }
   }
   _moda_ok=true;
   return(_moda);
}


void cl_histogram:: save(string name){
   if(!his_ok){
	    f_alert("cl_histogram:save() proble, use his() first"); 
   }else{
      ofstream file{name};
      file<<" xmid_i  n_i  i  x_0 x_e n_i/N n_i/N/dx"<<endl;
      for(size_t i=0;i<xv.size();++i){
         file<<xv[i]<<" "<<Nv[i]<<" "<<i<<" "<<xrangev[i][0]<<" "<<xrangev[i][1]<<" "<<Nv[i]/_sum<<" "<<Nv[i]/_sum/_dx<<endl;
      }
      
      file.close();
   }
}





















bool cl_histogramxy:: isF(){
   return(_eF_ok);
}

vector<T> &cl_histogramxy:: Ny(){
   if(!_his_ok){
	   f_alert("use his() first");
   }
   return(_Ny);
}
vector<T> &cl_histogramxy:: xF(){
   if(!_his_ok){
	   f_alert("use his() first");
   }
   return(_xF);
}
vector<T> &cl_histogramxy:: yF(){
   if(!_his_ok){
	   f_alert("use his() first");
   }
   return(_yF);
}
vector<T> &cl_histogramxy:: Nx(){
   if(!_his_ok){
	   f_alert("use his() first");
   }
   return(_Nx);
}

T cl_histogramxy:: sum(){
   if(!_his_ok){
	   f_alert("use his() first");   
   }
   return(_sum);
}

T cl_histogramxy:: dx(){
   if(!_his_ok){
	   f_alert("use his() first");   
   }
   return(_dx);
}

T cl_histogramxy:: dy(){
   if(!_his_ok){
	   f_alert("use his() first");   
   }
   return(_dy);
}


vector<vector<T> >& cl_histogramxy:: xrange(){
   if(!_his_ok){
	   f_alert("use his() first");   
   }
   return(_xrangev);
}

vector<vector<T> >& cl_histogramxy:: yrange(){
   if(!_his_ok){
	   f_alert("use his() first");   
   }
   return(_yrangev);
}

vector<vector<T> >& cl_histogramxy:: nxrange(){
   if(!_his_ok){
	   f_alert("use his() first");   
   }
   return(_nxrangev);
}

vector<vector<T> >& cl_histogramxy:: nyrange(){
   if(!_his_ok){
	   f_alert("use his() first");   
   }
   return(_nyrangev);
}

ostream & operator<< (ostream &ret, cl_histogramxy &rf){
   ret<<" x_mid   N  "<<endl;	
   for(size_t i=0;i<rf.x().size();++i){
      ret<<rf.x()[i]<<" "<<rf.Nx()[i]<<" "<<endl;
   }
   for(size_t i=0;i<rf.y().size();++i){
      ret<<rf.y()[i]<<" "<<rf.Ny()[i]<<" "<<endl;
   }
   for(size_t i=0;i<rf.x().size();++i){
     for(size_t j=0;j<rf.y().size();++j){
        ret<<rf.x()[i]<<" "<<rf.y()[i]<<" "<<rf.N()[i][j]<<" "<<endl;
     }
   }
   if(rf.isF()){
	 ret<<" empirical distribuant:"<<endl;
	 ret<<" x   n  "<<endl;	
	 for(size_t i=0;i<rf.x().size();++i){
        ret<<rf.xF()[i]<<" "<<rf.yF()[i]<<" "<<endl;
     }   
   }
   return(ret);
}



vector<T>& cl_histogramxy::x(){
    return(_x);
}

vector<T>& cl_histogramxy::y(){
    return(_y);
}

vector<vector<T> >& cl_histogramxy::N(){
    return(_N);
}

void cl_histogramxy:: init(vector<T> &x,vector<T> &y){
    if(x.size()>0){
      _x0=x.begin();
      _xe=x.end();
	  _y0=y.begin();
      _ye=y.end();
	  _nelements=x.size();
	  _mediana_ok=false;
	  _moda_ok=false;
	  _mean_ok=false;
	  _D_ok=false;
      _init_ok=true;
	  _compute_ok=false;
      _eF_ok=false;
    }else{
      f_alert("cl_histogram:init() proiblem: x vector has to have at least one element");
      _init_ok=false;
    }        
}

void cl_histogramxy::his(int nx,int ny, bool out){
   if(_init_ok){
      _xmax=*_x0;
	  _xmin=*_x0;
	  _ymax=*_y0;
	  _ymin=*_y0;
      _Nmax=0;
      _Nmin=0;
      _xNmax=0;
      _xNmin=0;
      _yNmax=0;
      _yNmin=0;
	  _nx=nx;
      _ny=ny;
	  typename vector<T>::iterator ix;
      typename vector<T>::iterator iy;
	  for(ix=_x0,iy=_y0;ix<_xe;++ix,++iy){
		  if(*ix>_xmax)_xmax=*ix;
		  if(*ix<_xmin)_xmin=*ix;
          if(*iy>_ymax)_ymax=*iy;
		  if(*iy<_ymin)_ymin=*iy;
	  }
	  _dx=(_xmax-_xmin)/(_nx);
      _dy=(_ymax-_ymin)/(_ny);
      if(out)cout<<"dx = "<<_dx<<" max x = "<<_xmax<<" min x = "<<_xmin<<endl;
	  if(out)cout<<"dy = "<<_dy<<" max y = "<<_ymax<<" min y = "<<_ymin<<endl;
	  if(out)cout<<endl;
	  _Nx.clear();
      _Ny.clear();
      _N.clear();
	  _x.clear();
	  _xrangev.clear();
	  _nxrangev.clear();
	  _y.clear();
	  _yrangev.clear();
	  _nyrangev.clear();
	  
      int nt;
	  bool first=true;
	  vector<T> xrt(2),xntv(2);
	  vector<T> yrt(2),yntv(2);
      for(int i=0;i<_nx;i++){
          _x.push_back(_xmin+i*_dx+_dx/2.0);
	      xrt[0]=_xmin+i*_dx;
		  xrt[1]=_xmin+(i+1)*_dx;
		  _xrangev.push_back(xrt);
          vector<T>Nt;
          for(int j=0;j<_ny;j++){
             if(i==0){
                 _y.push_back(_ymin+j*_dy+_dy/2.0);
		         yrt[0]=_ymin+j*_dy;
		         yrt[1]=_ymin+(j+1.0)*_dy;
		         _yrangev.push_back(yrt);
             }
		     //if(out)cout<<"i="<<i<<" "<<"xmin="<<min+i*dx<<" xmax="<<min+(i+1)*dx<<endl;
		     nt=0;
             if(i<_nx-1 && j<_ny-1){
		       for(ix=_x0,iy=_y0;ix<_xe;++ix,++iy){
                  //cout<<*ix<<" "<<_xrangev[i][0]<<" "<<*ix<<" "<<_xrangev[i][1]<<"  y="<<*iy<<" r=y"<<_yrangev[j][0]<<" "<<_yrangev[j][1]<<endl;				
		          if( (*ix>=_xrangev[i][0] && *ix<_xrangev[i][1]) &&  (*iy>=_yrangev[j][0] && *iy<_yrangev[j][1]) ){
				     nt++;
			      }
		       }
             }
             if(i<_nx-1 && j==_ny-1){
		       for(ix=_x0,iy=_y0;ix<_xe;++ix,++iy){
                  //cout<<*ix<<" "<<_xrangev[i][0]<<" "<<*ix<<" "<<_xrangev[i][1]<<"  y="<<*iy<<" r=y"<<_yrangev[j][0]<<" "<<_yrangev[j][1]<<endl;				
		          if( (*ix>=_xrangev[i][0] && *ix<_xrangev[i][1]) &&  (*iy>=_yrangev[j][0] && *iy<=_yrangev[j][1]) ){
				     nt++;
			      }
		       }
             }
             if(i==_nx-1 && j<_ny-1){
		       for(ix=_x0,iy=_y0;ix<_xe;++ix,++iy){
                  //cout<<*ix<<" "<<_xrangev[i][0]<<" "<<*ix<<" "<<_xrangev[i][1]<<"  y="<<*iy<<" r=y"<<_yrangev[j][0]<<" "<<_yrangev[j][1]<<endl;				
		          if( (*ix>=_xrangev[i][0] && *ix<=_xrangev[i][1]) &&  (*iy>=_yrangev[j][0] && *iy<_yrangev[j][1]) ){
				     nt++;
			      }
		       }
             }
             if(i==_nx-1 && j==_ny-1){
		       for(ix=_x0,iy=_y0;ix<_xe;++ix,++iy){
                  //cout<<*ix<<" "<<_xrangev[i][0]<<" "<<*ix<<" "<<_xrangev[i][1]<<"  y="<<*iy<<" r=y"<<_yrangev[j][0]<<" "<<_yrangev[j][1]<<endl;				
		          if( (*ix>=_xrangev[i][0] && *ix<=_xrangev[i][1]) &&  (*iy>=_yrangev[j][0] && *iy<=_yrangev[j][1]) ){
				     nt++;
			      }
		       }
             }
		     
		     if(first){
               _Nmax=nt;
               _Nmin=nt;
			   first=false;
		     }
             if(nt>_Nmax)_Nmax=nt;
             if(nt<_Nmin)_Nmin=nt;
		     Nt.push_back(nt);
             //ntv[0]=nt;
             //ntv[1]=nt;
             //nrangev.push_back(ntv);
          }
          _N.push_back(Nt);
	  }
	  
	  
	  
	  _sum=0;
      for(int i=0;i<_nx;i++){
         int  nt=0; 
         for(size_t j=0;j<_ny;j++){
             nt+=_N[i][j];
             _sum+=_N[i][j];
         }
         _Nx.push_back(nt);
      }
      //cout<<"Nx"<<_Nx<<endl;
      for(int i=0;i<_ny;i++){
         int  nt=0; 
         for(size_t j=0;j<_nx;j++){
             nt+=_N[j][i];
         }
         _Ny.push_back(nt);
      }
      
      if(out)cout<<"x"<<endl;
      if(out)cout<<_x<<endl;
      if(out)cout<<"y"<<endl;
      if(out)cout<<_y<<endl;
      if(out)cout<<"N"<<endl;
      if(out)cout<<_N<<endl;
      if(out)cout<<"Nx"<<endl;
      if(out)cout<<_Nx<<endl;
      if(out)cout<<"Ny"<<endl;
      if(out)cout<<_Ny<<endl;
      if(out)cout<<endl;
      
      
      //ntv[0]=nt;
      //ntv[1]=nt;
      //nrangev.push_back(ntv);
	  //cout<<"x:"<<endl;
	  //cout<<x<<endl;
	  //cout<<"N(x):"<<endl;
	  //cout<<N<<endl;
	  
	  //_sum=0;
	  //for(size_t i=0;i<=n;i++){
	//	 _sum+=_N[i];
	  //}
      if(out)cout<<"N max = "<<_Nmax<<" N min = "<<_Nmin<<endl;
	  if(out)cout<<"N sum = "<<_sum<<endl;
	  _his_ok=true;
      
      if(out)      cout<<"xrangev"<<endl;      
      if(out)cout<<_xrangev<<endl;
      if(out)      cout<<"x"<<endl;      
      if(out)cout<<_x<<endl;
      if(out)      cout<<"yrangev"<<endl;      
      if(out)cout<<_yrangev<<endl;
      if(out)      cout<<"y"<<endl;      
      if(out)cout<<_y<<endl;
      
   }else{
	  f_alert("use init(vector) first");   
   }
}


void cl_histogramxy:: save(string name){
   if(!_his_ok){
        f_alert("cl_histogram:save() problem, use his() first");
   }else{
      ofstream file{name};
      file<<" xmid_i  n_i  i  x_0 x_e n_i/N n_/N/dx"<<endl;
      file<<"x\\y"<<" ";
          for(int j=0;j<_ny;++j){
             file<<_y[j]<<" ";   
          }
          
      for(int i=0;i<_nx;++i){
          file<<_x[i]<<" ";
          for(size_t j=0;j<_ny;++j){
             file<<_N[i][j]<<" ";
          }
          file<<endl;
      }
      file.close();
      
      name=f_remove_ext(name)+"_2.dat";
      ofstream file2{name};
      file2<<"x y  N"<<" "<<endl;;
      for(int i=0;i<_nx;++i){
          for(int j=0;j<_ny;++j){
             file2<<_x[i]<<" "<<_y[j]<<" "<<_N[i][j]<<endl;;
          }
          file2<<endl;
      }
      file2.close();
      
   }
}






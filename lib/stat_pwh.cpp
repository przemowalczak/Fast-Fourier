
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

//require sort_pw.hpp
#include "stat_pwh.hpp"
#include "operators_pwh.hpp"
#include "klunkry_pwh.hpp"
#include "sort_pwh.hpp"

typedef double T;


void cl_stat::help(){
	cout<<"cl_stat:"<<endl;
    cout<<"This class can be used to calculate different statistical values:"<<endl;
	cout<<"  mean() - mean value, calculated with cmean() "<<endl;
	cout<<"  sd() - standard deviation (n-1), calculated with csd() "<<endl;
	cout<<"  n() - number of elements, calculated with cmean()" <<endl;
	cout<<"  sum() - sum od elements, calculated with cmean()" <<endl;
	cout<<"All values can be calculated with compute()"<<endl;	
	cout<<"  "<<endl;
	cout<<"Initialization methods:"<<endl;
	cout<<"  cl_stat<Type> stat;"<<endl;
	cout<<"  stat.init(vector_x)"<<endl;
	cout<<"  stat.compute();"<<endl;
	cout<<"  "<<endl;
	cout<<"  cl_stat<Type> stat(vector_x);"<<endl;
	cout<<"  stat.compute();"<<endl;
	cout<<"  "<<endl;
	cout<<"  cl_stat<Type> stat(x.begin(),x.end());"<<endl;
	cout<<"  stat.compute();"<<endl;
	
}


bool cl_stat::mean_ok(){
   if(_mean_ok)return(true);
   else return(false);
}

bool cl_stat::sd_ok(){
   if(_sd_ok)return(true);
   else return(false);
}

bool cl_stat::compute_ok(){
   if(_compute_ok)return(true);
   else return(false);
}

bool cl_stat::mediana_ok(){
   if(_mediana_ok)return(true);
   else return(false);
}

bool cl_stat::moda_ok(){
   if(_moda_ok)return(true);
   else return(false);
}

void cl_stat::print(){
   if(_mean_ok){
     cout<<"cl_stat: Mean = "<<f_c("cyan")<<meanv<<f_reset()<<endl;
   }
   if(_sd_ok){
     cout<<"cl_stat: Standard deviation (S*) = "<<f_c("cyan")<<sdv<<f_reset()<<"  S*2 = "<<f_c("red")<<sdv*sdv<<f_reset()<<endl;
	 cout<<"cl_stat: Standard deviation (S) = "<<f_c("cyan")<<s()<<f_reset()<<"  S2 = "<<f_c("red")<<s()*s()<<f_reset()<<endl;
   }
   if(_mean_ok){
     cout<<"cl_stat: n = "<<f_c("cyan")<<nv<<f_reset()<<endl;
	 cout<<"cl_stat: sum = "<<f_c("cyan")<<_sum<<f_reset()<<endl;
	 
   }
   if(_mediana_ok){
	  cout<<"cl_stat: mediana = "<<f_c("cyan")<<_mediana<<f_reset()<<endl;  
   }
   if(_moda_ok){
	  cout<<"cl_stat: moda = "<<f_c("cyan")<<_moda<<f_reset()<<endl;  
   }
   if(_sd_ok){
       
      cout<<"\033[0;35;49m";  	
	  cout<<"Podobnie jak trzeci moment centralny, współczynnik asymetrii przyjmuje wartość zero dla rozkładu symetrycznego, wartości ujemne dla rozkładów o lewostronnej asymetrii (wydłużone lewe ramię rozkładu) i wartości dodatnie dla rozkładów o prawostronnej asymetrii (wydłużone prawe ramię rozkładu)"<<endl;
	  cout<<"Współczynnik asymetrii ma tę przewagę nad trzecim momentem centralnym, że można porównywać jego bezwzględne wartości z różnych rozkładów."<<endl;
	  cout<< "\033[0m";
      cout.flush();
       
      cout<<"cl_stat: asymmetry factor (g1) = "<<f_c("yellow")<<_g1<<f_reset();
      if(_g1==0){cout<<"  /\\";}
      else if(_g1<0){cout<<"  /|";}
      else{cout<<"  |\\";}
      cout<<endl;
      cout<<"cl_stat: asymmetry factor (g1*) = "<<f_c("yellow")<<_g1no<<f_reset();
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
      cout<<"cl_stat: kurtosis (g2) = "<<f_c("green")<<_g2<<f_reset()<<endl;
      cout<<"cl_stat: kurtosis (g2*) = "<<f_c("green")<<_g2no<<f_reset()<<endl;
   }
   if(_K2_test_ok){
       cout<<"For K2 test (D'Agostino-Pearson)"<<endl;
       cout<<"mu1(g1) = "<<setprecision(10)<< _mu1g1<<endl;
       cout<<"mu2(g1) = "<<_mu2g1<<endl;
       cout<<"gamma1(g1) = "<<_gamma1g1<<endl;
       cout<<"gamma2(g1) = "<<_gamma2g1<<endl;
       cout<<"mu1(g2) = "<<setprecision(10)<< _mu1g2<<endl;
       cout<<"mu2(g2) = "<<_mu2g2<<endl;
       cout<<"gamma1(g2) = "<<_gamma1g2<<endl;
       cout<<"gamma2(g2) = "<<_gamma2g2<<endl;
       cout<<"W2 = "<<_W2<<endl;
       cout<<"delta = "<<_delta<<endl;
       cout<<"alpha2 = "<<_alpha2<<endl;
       cout<<"Z1(g1) = "<<_Z1g1<<endl;
       cout<<"Z2(g2) = "<<_Z2g2<<endl;
       cout<<"K2 = "<<_K2<<endl;
       cout<<endl;
   }
   if(_JB_test_ok){
       cout<<"JB test (Jarque-Bera)"<<endl;
       cout<<"JB = "<<_JB<<endl;
   }

   
}

void cl_stat::printtex(){
   if(_mean_ok){
     cout<<"Mean = "<<meanv<<" \\\\"<<endl;
   }
   if(_sd_ok){
     cout<<"Standard deviation $(S^*) = "<<sdv<<"$,  $S^{*2} = "<<sdv*sdv<<"$ \\\\"<<endl;
     cout<<"Standard deviation $(S) = "<<s()<<"$,  $S^2 = "<<s()*s()<<"$ \\\\"<<endl;
   }
   if(_mean_ok){
     cout<<"n = "<<nv<<" \\\\"<<endl;
	 cout<<"sum = "<<_sum<<" \\\\"<<endl;
	 
   }
   if(_mediana_ok){
	  cout<<"mediana = "<<_mediana<<" \\\\"<<endl;  
   }
   if(_moda_ok){
	  cout<<"moda = "<<_moda<<" \\\\"<<endl;  
   }
   if(_max_ok){
	  cout<<"max = "<<_max<<" \\\\"<<endl;  
   }
   if(_min_ok){
	  cout<<"min = "<<_min<<" \\\\"<<endl;  
   }
   if(_min_ok){
         cout<<"asymmetry factor $(g_1) = "<<_g1<<"$ \\\\"<<endl;
         cout<<"asymmetry factor $(g_1^*) = "<<_g1no<<"$ \\\\"<<endl;
         cout<<"kurtosis (g2) = "<<_g2<<"\\\\"<<endl;
         cout<<"kurtosis (g2*) = "<<_g2no<<"\\\\"<<endl;
   }
   if(_K2_test_ok){
       cout<<"D'Agostino-Pearson test, K2 = "<<_K2<<" \\\\"<<endl;
   }
   if(_JB_test_ok){
       cout<<"Jarque-Bera test, JB = "<<_JB<<" \\\\"<<endl;
   }
   
}

T cl_stat::sum(){
   if(_mean_ok){
     return(_sum);
   }else{
	 f_alert("cl_stat: sum value problem: use cmean() or compute() first");
	 return(1);
   }
}

T cl_stat::mediana(){
   if(!_mediana_ok){
     f_alert("cl_stat: mediana value problem: use cmediana() or compute() first");
   }
   return(_mediana);
}

T cl_stat::moda(){
   if(!_moda_ok){
     //f_alert("cl_stat: mediana value problem: use cmediana() or compute() first");
     //cmoda();
     cmax();
   }
   return(_moda);
}

T cl_stat::mean(){
   if(_mean_ok){
     return(meanv);
   }else{
	 f_alert("cl_stat: mean value problem: use cmean() or compute() first");
	 return(1);
   }
}

T cl_stat::max(){
   if(!_max_ok){
      cmax();
   }
   return(_max);
}

T cl_stat::min(){
   if(!_min_ok){
      cmin();
   }
   return(_min);
}

size_t cl_stat::n(){
   if(_mean_ok){
     return(_n);
   }else{
	 f_alert("cl_stat: n value problem: use cmean() or compute() first");
	 return(1);
   }
}

T cl_stat::sd(){
   if(_sd_ok){
     return(sdv);
   }else{
	 f_alert("cl_stat: standard deviation problem: use csd() or compute() first");
	 return(1);
   }
}

T cl_stat::s(){
   if(!_sd_ok){
     csd();
   }
   return(sdv*sqrt((_n*1.0-1.0)/_n));
}

T cl_stat::D(){
   if(!_sd_ok){
     csd();
   }
   return(_D);
}

T cl_stat::D2(){
   if(!_sd_ok){
     csd();
   }
   return(_D2);
}

T cl_stat::Do(){
   if(!_sd_ok){
     csd();
   }
   return(_Do);
}

T cl_stat::Do2(){
   if(!_sd_ok){
     csd();
   }
   return(_Do2);
}

T cl_stat::g1(){
   if(!_sd_ok){
     csd();
   }
   return(_g1);
}

T cl_stat::g1no(){
   if(!_sd_ok){
     csd();
   }
   return(_g1no);
}

T cl_stat::g2(){
   if(!_sd_ok){
     csd();
   }
   return(_g2);
}

T cl_stat::g2no(){
   if(!_sd_ok){
     csd();
   }
   return(_g2no);
}

T cl_stat::cmean(){
   _sum=0;
   nv=0;
   for( vector<T>::iterator it=x0;it<xe;it+=dt){
	  _sum+=*it;  
	  nv++;
   }
   meanv=_sum/nv;
   _mean_ok=true;
   return(meanv);
}

T cl_stat::cmediana(){
   if(!_init_ok){
	  f_alert("cl_stat:: cmediana problem, use init() first");   
   }
   T t;
   if(!_sort_ok){
      f_sort_mi(t,x0,xe);
   }

   if(!_min_ok){
     _min=*x0;
     _min_ok=true;
   }
   if(!_max_ok){
     _max=*(xe-1);
     _max_ok=true;
   }
   int n=distance(x0,xe);
   int i=n/2;
   
   if(n%2==0)_mediana=(*(x0+i)+*(x0+i+1))/2.0;
   else _mediana=*(x0+i);
   _mediana_ok=true;
   return(_mediana);
}

bool cl_stat::sort(){
   if(!_init_ok){
	  f_alert("cl_stat:: sort problem, use init() first");   
   }
   T t;
   f_sort_mi(t,x0,xe);
   bool ok=true;
   _sort_ok=true;
   return(ok);
}

T cl_stat::cquantile(double alpha){
    double q=0;
    double s=0;
    if(!_init_ok){
        f_alert("cl_stat:: cquantile problem, use init() first");
    }
    T t;
    if(!_sort_ok){
        f_sort_mi(t,x0,xe);
    }
    T nd=_n*1.0;
    T ds=0;
    if(_n>0){
        q=*x0;
    }
    for(int i=1;i<_n;++i){
        ds=*(x0+i)/nd;
        if(s+ds<=alpha){
           s+=ds;
           q=*(x0+i);
        }else{
            break;
        }
    }



    return(q);
}

T cl_stat::cmax(){
       
     _max=*x0;
     for( vector<T>::iterator it=x0+1;it<xe;it+=dt){
	    if(*it>_max)_max=*it;
     }
     _max_ok=true;
     return(_max);
     _moda_ok=true;
     _moda=_max;
}

T cl_stat::cmin(){
       
     _min=*x0;
     for( vector<T>::iterator it=x0+1;it<xe;it+=dt){
	    if(*it<_min)_min=*it;
     }
     _min_ok=true;
     return(_min);
}

T cl_stat::csd(){
   sdv=0;
   T sg1=0;
   T sg2=0;
   size_t n=0;
   if(!_mean_ok){
        cmean();
   }
       
     for( vector<T>::iterator it=x0;it<xe;it+=dt){
	    sdv+=pow((*it-meanv),2.0);
        sg1+=pow((*it-meanv),3.0);  
        sg2+=pow((*it-meanv),4.0);  
	    n++;
	    //cout<<"x="<<*it<<" n="<<n<<endl;  
     }
     _D2=sdv/(n-1);
     _D=sqrt(_D2);
     _Do2=sdv/(n);
     _Do=sqrt(_Do2);
     
     _g1=sg1/(n*pow(_Do2,1.5));//skupienie
      if(n>2){
        _g1no=_g1*sqrt(n*(n-1)*1.0)/(n-2.0);
      }else{
        _g1no=0;   
      }
     // _K=sg2/(n*pow(_Do2,2)); //Kurtoza
     _g2=sg2/(n*pow(_Do2,2))-3.0; // kurtoza, skupienie, splaszczenie
     if(n>3){
      _g2no=n*(n+1)*sg2/(pow(_D2,2)*(n-1)*(n-2)*(n-3))-3*(n-1)*(n-1)/( (n-2)*(n-3));
     }else{
       _g2no=0;   
     }
     
     sdv=sqrt(sdv/(n-1));

   _sd_ok=true;
   return(sdv);
}

T cl_stat::moment_cen(int r){
   T sm=0;
   size_t n=0;
   if(_mean_ok){
       
     for( vector<T>::iterator it=x0;it<xe;it+=dt){
	    sm+=pow((*it-meanv),r); 
	    n++;
	    //cout<<"x="<<*it<<" n="<<n<<endl;  
     }
     _mc=sm/n;
     
   }else{
	  f_alert("cl_stat: standard deviation problem: use cmean() or compute first");   
   }
   return(_mc);
}

T cl_stat::moment(int r){
   T sm=0;
   size_t n=0;
   if(_mean_ok){
       
     for( vector<T>::iterator it=x0;it<xe;it+=dt){
	    sm+=pow(*it,r); 
	    n++;
	    //cout<<"x="<<*it<<" n="<<n<<endl;  
     }
     _m=sm/n;
     
   }else{
	  f_alert("cl_stat: standard deviation problem: use cmean() or compute first");   
   }
   return(_m);
}

void cl_stat::compute(){
   meanv=cmean();
   sdv=csd();
   _mediana=cmediana();
   _K2=cK2();
   _JB=cJB();
   _compute_ok=true;
}

void cl_stat::init(vector<T>&x){
    x0=x.begin();
	xe=x.end();
	_init_ok=true;
	_compute_ok=false;
	_mean_ok=false;
	_sd_ok=false;
	_mediana_ok=false;
	_moda_ok=false;
	_n=x.size();
    _sort_ok=false;
}






T cl_stat::cK2(){
    _K2_test_ok=false;

    if(_n>3){

        if(!_sd_ok){
            csd();
        }

       _mu1g1=0.0;
       _mu2g1=6.0*(_n-2.0)/((_n+1.0)*(_n+3.0));
       _gamma1g1=0.0;
       _gamma2g1=36.0*(_n-7.0)*(1.0*_n*_n-2.0*_n-5.0)/( (_n-2.0)*(_n+5.0)*(_n+7.0)*(_n+9.0) );

       _mu1g2=-6.0/(_n+1.0);
       _mu2g2=24.0*_n*(_n-2.0)*(_n-3.0)/( (_n+1.0)*(_n+1.0)*(_n+3.0)*(_n+5.0) );
       _gamma1g2=6.0*(1.0*_n*_n-5.0*_n+2.0)*sqrt(6.0*(_n+3.0)*(_n+5.0)/( _n*(_n-2.0)*(_n-3.0) ))/( (_n+7.0)*(_n+9.0) );
       _gamma2g2=36.0*(15.0*pow(_n*1.0,6)-36.0*pow(_n*1.0,5)-628.0*pow(_n*1.0,4)+982.0*pow(_n*1.0,3)+5777.0*pow(_n*1.0,2)-6402.0*_n+900.0)/( _n*(_n-3.0)*(_n-2.0)*(_n+7.0)*(_n+9.0)*(_n+11.0)*(_n+13.0)  );

       _W2=sqrt(2*_gamma2g1+4)-1;
       _delta=1.0/sqrt(log(sqrt(_W2)));
       _alpha2=2.0/(_W2-1.0);
       _Z1g1=_delta*asinh(_g1/(sqrt(_alpha2*_mu2g1)) );

       _A=6.0+(8.0/_gamma1g2)*( 2.0/_gamma1g2+sqrt(1.0+4.0/(_gamma1g2*_gamma1g2) ) );
       _Z2g2=sqrt(9.0*_A/2.0)*(1.0-2.0/(9.0*_A)-pow( (1-2.0/_A)/(1.0+(_g2-_mu1g2)*sqrt(2.0/(_A-4.0))/sqrt(_mu2g2) ) ,1.0/3.0) );

       _K2=_Z1g1*_Z1g1+_Z2g2*_Z2g2;

       _K2_test_ok=true;
    }else{
       _K2_test_ok=false;
    }
    return(_K2);
}
T cl_stat::K2(){
    if(!_K2_test_ok){
        cK2();
    }
    return(_K2);
}
bool cl_stat::K2_test_ok(){
    return (_K2_test_ok);
}
T cl_stat::mu1g1(){
    return (_mu1g1);
}
T cl_stat::mu2g1(){
    return (_mu2g1);
}
T cl_stat::gamma1g1(){
    return (_gamma1g1);
}
T cl_stat::gamma2g1(){
    return (_gamma2g1);
}
T cl_stat::mu1g2(){
    return (_mu1g2);
}
T cl_stat::mu2g2(){
    return (_mu2g2);
}
T cl_stat::gamma1g2(){
    return (_gamma1g2);
}
T cl_stat::gamma2g2(){
    return (_gamma2g2);
}
T cl_stat::W2(){
    return (_W2);
}
T cl_stat::delta(){
    return (_delta);
}
T cl_stat::alpha2(){
    return (_alpha2);
}
T cl_stat::Z1g1(){
    return (_Z1g1);
}

T cl_stat::cJB(){
    _JB_test_ok=false;
    if(_n>1){
       if(!_sd_ok){
          csd();
       }
       _JB=_n*(_g1*_g1+_g2*_g2/4.0)/6.0;
       _JB_test_ok=true;
    }

    return (_JB);
}

T cl_stat::JB(){
    if(!_JB_test_ok){
        cJB();
    }
    return (_JB);
}
bool cl_stat::JB_test_ok(){
    return(_JB_test_ok);
}


//**cl_stat**




//****cl_statxy****


void cl_statxy::help(){
	cout<<"cl_statxy:"<<endl;\
	cout<<"require: sort_pw.hpp and -lboost_math_c99f library"<<endl;
    cout<<"This class can be used to calculate different statistical value of two vectors:"<<endl;
	cout<<"  cov() - covariance, calculated with ccov()"<<endl;
	cout<<"  rho() - corelation coefficient, calculated with crho()"<<endl;
	cout<<"  spearman() - Spearman corelation coefficient, calculated with cspearman()"<<endl;
	cout<<"  pt() - p-value from t-student test (0-1 scale), calculated with cspearman(), zero hipothesis: data are not corelated"<<endl;
	cout<<"  pz() - p-value from N(0,1) test (0-1 scale), calculated with cspearman(),zero hipothesis: data are not corelated"<<endl;
	cout<<"cov and rho values can be calculated with compute()"<<endl;
	cout<<endl;
	cout<<"Initialization methods:"<<endl;
	cout<<"  cl_statxy<Type> statxy;"<<endl;
	cout<<"  statxy.init(&statx,&staty)"<<endl;
	cout<<"  statxy.compute()"<<endl;
	cout<<"  "<<endl;
	cout<<"  cl_statxy<Type> statxy(vector_x,vector_y)"<<endl;
	cout<<"  statxy.compute()"<<endl;
	cout<<"  "<<endl;
	cout<<"  cl_statxy<Type> statxy(&statx,&staty)"<<endl;
	cout<<"  statxy.compute()"<<endl;
	
	
}

T cl_statxy::cov(){
   if(cov_ok){
     return(covv);
   }else{
	 f_alert("cl_statxy: covariance problem: use ccov() or compute() first");
	 return(1);
   }
}

T cl_statxy::rho(){
   if(rho_ok){
     return(rhov);
   }else{
	 f_alert("cl_statxy: corelation coefficient problem: use crho() or compute() first");
	 return(1);
   }
}

T cl_statxy::ccov(){
   covv=0;	
   cout<<"cl_statxy: x.mean="<<(*x).mean()<<endl;
   n=0;
   vector<T>::iterator itx;
   vector<T>::iterator ity;
   for(itx=(*x).x0,ity=(*y).x0;itx<(*x).xe;itx+=dt,ity+=dt){
	  if(ity>=(*y).xe)f_alert("cl_statxy: Mess in vector sizes; staty size is not equal to statx size"); 
	  covv+=(*itx-(*x).mean())*(*ity-(*y).mean());  
	  n++;
	  //cout<<"x="<<*itx<<" y="<<*ity<<" "<<" cov="<<covv<<" n="<<n<<endl;  
   }
   //cout<<"n="<<n<<" "<<*xe<<endl;
   //*xe indicates to unexisting data!!
   covv/=n;
   cov_ok=true;
   return(covv);
}

T cl_statxy::crho(){
	if(cov_ok){
	   rhov=covv/((*x).sd()*(*y).sd());	
       rho_ok=true;
	}else{
	   f_alert("cl_statxy: covariance problem: use ccov() or compute() first");
	}
    return(rhov);
}

void cl_statxy::compute(){
   T covv=ccov();	
   T rhov=crho();
   _compute_ok=true;
}

void cl_statxy::init(cl_stat *_x,cl_stat *_y){
   x=_x;
   y=_y;
   _init_ok=true;
   if(!((*x).mean_ok()))(*x).cmean();
   if(!((*x).sd_ok()))(*x).csd();   
   if(!((*y).mean_ok()))(*y).cmean();
   if(!((*y).sd_ok()))(*y).csd();
}

void cl_statxy::init(vector<T> &_x,vector<T> &_y){
   _init_ok=true;
   _xs.init(_x);
   _ys.init(_y);
   _xs.cmean();
   _xs.csd();
   //_xs.print();
   x=&(_xs);
   _ys.cmean();
   _ys.csd();
   //_ys.print();  
   y=&(_ys);
   
}
/*

T cl_statxy::spearman(){
   if(spearman_ok){
     return(spearmanv);
   }else{
	 f_alert("cl_statxy: Spearman coefficient problem: use cspearman() first");
	 return(1);
   }
}*/

T cl_statxy::pz(){
   if(spearman_ok){
     return(pzv);
   }else{
	 f_alert("cl_statxy: Spearman coefficient problem: use cspearman() first");
	 return(1);
   }
}
/*
T cl_statxy::pz2(){
   if(spearman_ok){
     return(pz2v);
   }else{
	 f_alert("cl_statxy: Spearman coefficient problem: use cspearman() first");
	 return(1);
   }
}*/

T cl_statxy::pt(){
   if(spearman_ok){
     return(ptv);
   }else{
	 f_alert("cl_statxy: Spearman coefficient problem: use cspearman() first");
	 return(1);
   }
}
/*

T cl_statxy::cspearman(bool out){ //warning, this will destroy the x and y data (they will be sorted); use fast sorting
   
	vector<T> indx(n);
	vector<T> indy(n);
	//for(size_t i=0;i<n;i++){
//	   indx[i]=i;
//	   indy[i]=i;
	//}
	
	size_t i=0,j=0;
	class vector<T>::iterator itx;
    class vector<T>::iterator ity;
	for(itx=(*x).x0,i=0;itx<(*x).xe;itx++,ity++,i++){
	  indx[i]=i;
	  indy[i]=i;
	}
	
	//cout<<"(*x).x0="<<*(*x).x0<<endl;
	T type=0;
	f_sort_mi(type,(*x).x0,(*x).xe,(*y).x0,(*y).xe);
	f_sort_mi(type,(*y).x0,(*y).xe,(*x).x0,(*x).xe,indx.begin(),indx.end());
	//cout<<"sort2"<<endl;
	//cout<<"indx="<<indx<<endl;
	

	T sumd=0;
	for(i=0;i<n;i++){
	   //d.push_back(pow((indx[i]-indy[i])*1.0,2.0));	
	   //cout<<"d="<<d.back()<<" "<<indx[i]-indy[i]<<" "<<" i="<<i<<endl; 
	   //sumd+=d.back();
	   sumd+=pow((indx[i]-indy[i])*1.0,2.0);
	}
	
	spearmanv= 1.0-6.0*sumd/(n*(n*n-1.0));
	T t=spearmanv*sqrt((n-2.0)/(1.0-spearmanv*spearmanv));
	T z=atanh(spearmanv)*sqrt((n-3.0)/(1.06));
	//cout<<"spearman="<<spearmanv<<" n="<<n<<" sumd="<<sumd<<" t="<<t<<" z="<<z<<endl;
	if(out)cout<<"cl_statxy: Spearman coefficient="<<spearmanv<<" n="<<n<<" gsl_statistics: t (t-student)="<<t<<" z (N(0,1))="<<z<<endl;
	
	pzv=0.5 * erfc(-z * M_SQRT1_2);
	if(z>0)pzv=1-pzv;
	//if(out)cout<<"cl_statxy: p-value from N(0,1) (one-sided)="<<pzv<<" (two sided)="<<pzv*2<<endl;
	pzv*=2;//two-sided!!
    if(out)cout<<"cl_statxy: p-value from N(0,1) = "<<pzv<<endl;

	boost::math::students_t dist(n-2);
	ptv= boost::math:: cdf(complement(dist, fabs(t)));
    //if(out)cout<<"cl_statxy: p-value from t-student (one-sided)="<<ptv<<" (two sided)="<<ptv*2<<endl;
	ptv*=2;//two-sided
    if(out)cout<<"cl_statxy: p-value from t-student = "<<ptv<<endl;

	//boost::math::normal ndist(0,1);
	//pz2v= boost::math:: cdf(complement(ndist, fabs(z)));
	//if(out)cout<<"cl_statxy: p-value from N(0,1) (v2) (one-sided)="<<pz2v<<" (two sided)="<<pz2v*2<<endl;
	//cout<<"p-value from N(0,1) (one-sided)="<<cdf(complement(ndist, (z)))<<" (two sided)="<<2*(1-cdf(complement(ndist, (z))))<<endl;
	//cout<<"p-value from N(0,1) (one-sided)="<<cdf(ndist, (z))<<" (two sided)="<<2*(1-cdf(complement(ndist, (z))))<<endl;
	//cout<<"p-value from N(0,1) (one-sided)="<<pdf(ndist, (z))<<" (two sided)="<<2*(1-cdf(complement(ndist, (z))))<<endl;
	  
	spearman_ok=true;
	return(spearmanv);
}
*/
//**cl_statxy**


//**** cl_GESD ****


void cl_GESD::help(){
   cout<<"cl_GESD:"<<endl;
   cout<<"require:  <gsl/gsl_cdf.h>, -lgsl -lgslcblas"<<endl;
   cout<<"This class can be used to find outliers using GESD algorithm."<<endl;
   cout<<"Initialization methods:"<<endl;
   cout<<"   cl_GESD<Type> GESD;"<<endl;
   cout<<"   GESD.init(vector_x);"<<endl;
   cout<<"  "<<endl;
   cout<<"   cl_GEST<Type> GESD(vector_x);"<<endl;
   cout<<"  "<<endl;   
   cout<<"   GESD.cind(alpha,output(true or false)) - find outliers "<<endl;
   cout<<"   GESD.ind() return a vector<size_t> of indexes of outliers"<<endl;
   cout<<"   GESD.xwo() return an input vector<Type>x  without outliers"<<endl;
   cout<<"   GESD.cvwo(vector_y) return a vector<Type>y  without elements corresponding to outliers of the vector_x"<<endl;
   cout<<"   max_outliers - optional parameter, default value = 0.2 (20\%)"<<endl;
	
}

void cl_GESD::init(vector<T>&_x){
   _xwo=_x;
   _init_ok=true;
}

vector<size_t> cl_GESD:: ind(){
   if(_ind_ok){
	  return(_ind);
   }else{
	  f_alert("cl_GESD: ind() problem, use cind() first");   
   }
}

vector<T> cl_GESD:: xwo(){
   if(_ind_ok){
	  return(_xwo);
   }else{
	  f_alert("cl_GESD: xwo() problem, use cind() first");   
   }
}


vector<size_t> cl_GESD:: cind(T alpha,bool out){
   size_t n0=_xwo.size();
   vector<T> lambda;
   vector<T> x2=_xwo;
   vector<T> R;	 
   for(size_t r=1;r<n0*max_outliers;r++){
      _stat.init(_xwo);
      _stat.cmean();
      _stat.csd();
   
      size_t n=_xwo.size();
      size_t imax=0;
      T Rt=0,Rt2;
      for(size_t i=0;i<n;i++){
         Rt2=abs(((_xwo[i]-_stat.mean())))/_stat.sd();
         if(Rt<Rt2){
	       imax=i;
	       Rt=Rt2;
         }
      }
      R.push_back(Rt);
      //ind.push_back(imax);
      _xwo.erase(_xwo.begin()+imax);
   
      T nu=n0-r-1;
      T p=1.0-(alpha/(2.0*(n0-r+1.0)));
      T tx=gsl_cdf_tdist_Pinv(p,nu);
	  //double T = quantile(complement(dist, alpha[i] / 2));
      lambda.push_back(tx*(n0-r)/sqrt((n0-r-1.0+tx*tx)*(n0-r+1.0)));
   
      //cout<<"Rt="<<Rt<<" lambda = "<<lambda.back()<<" p="<<p<<" nu="<<nu<<endl;
      //cout<<"imax="<<imax<<" x[imax] = "<<x[imax]<<" r = "<<r<<" "<<x.size()<<endl;
   
      if(R.back()<lambda.back())break;
   
   }
   size_t j=0;
   for(size_t i=0;i<x2.size();i++){
      if(x2[i]==_xwo[j]){
	    j++;
      }else{
	    _ind.push_back(i);
      }
   }
   //ind -indexes of the erased elements 
   sort(_ind.begin(),_ind.end());
   _nind=_ind.size();
   if(out){
	 cout<<"  initial number of points = "<<n0<<endl;
     cout<<"  number of outliers       = "<<_nind<<endl;
	 cout<<"  final number of points = "<<_xwo.size()<<endl;
     //cout<<_ind<<endl;
     cout<<"  number of outliers/all = "<<_nind*1.0/n0<<" "<<_nind*100.0/n0<<"%"<<endl;
   }
   _ind_ok=true;
   return(_ind);
   
}


vector<T> cl_GESD:: cvwo(vector<T> &v){
   if(_ind_ok){
	  size_t j=0;
	  vector<T>vwa;
      for(size_t i=0;i<v.size();i++){
		if(j<_nind){
           if(i!=_ind[j]){
		     vwa.push_back(v[i]);
		   }else{
	         j++; 
           }
           //cout<<"i="<<i<<" j="<<j<<" "<<_ind[j]<<endl;
		}else{
		   vwa.push_back(v[i]);
		}
	  }
	  return(vwa);
   }else{
      f_alert("cl_GESD: cvwo() problem, use cind() first");
   }
}
		 
//** cl_GESD **

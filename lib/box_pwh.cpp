#include "box_pwh.hpp"


T Box:: f_sum(int i0,int ie){
	T Sum=0;
	for(int i=i0;i<=ie;++i){
	  	Sum+=*(y0+i);
		//cout<<"Sum="<<Sum<<" i="<<i<<" "<<*(y0+i)<<endl;
	}
    return(Sum);
}

void Box:: refresh(T Tc){
  if(_init_ok){
    //cout<<"Box::refresh"<<endl;
	_Tc=Tc;
	
	//cout<<"dT="<<setprecision(8)<< _dT<<endl;
	//cout<<"Tc="<<setprecision(8)<<Tc<<endl;
	//cout<<"T0="<<setprecision(8)<<_Tc-_dT<<" Te="<<setprecision(8)<<_Tc+_dT<<endl;
	
	
        //int _icr=f_find_ind_s(x0,xe,Tc);
	//cout<<"ic="<<_icr<<endl;
	int _i0r=f_find_ind_s(x0,xe,_Tc-_dT);
	int _ier=f_find_ind_s(x0,xe,_Tc+_dT);
	
	if(_i0r<0){
	  //cout<<"out of table"<<endl;
	  _i0r=0;
	}
	if(_ier<0){
	  //cout<<"out of table"<<endl;
	  _ier=_n-1;
	}
	
	if(_i0r==0){
	  T ddT=_dT-(_Tc-*x0);
      //cout<<"ddT="<<ddT<<" ier="<<_ier<<endl;
//	  _ier=f_find_ind_s(x0,xe,_Tc+_dT+ddT);
	  if(_ier<0){
	     //cout<<"out of table"<<endl;
	     _ier=_n-1;
	  }
	  //cout<<"new ddT="<<ddT<<" ier="<<_ier<<endl;
	}
	
	
	if(_ier==_n-1){
	  T ddT=_dT-(*(xe-1)-_Tc);
	  //cout<<"ddT="<<ddT<<" ier="<<_i0r<<endl;
      _i0r=f_find_ind_s(x0,xe,_Tc-_dT-ddT);
	  //cout<<"new ddT="<<ddT<<" ier="<<_i0r<<endl;
	  if(_i0r<0){
	     //cout<<"out of table"<<endl;
	     _i0r=0;
	  }
	}
	
	//cout<<"_i0r="<<_i0r<<" ier="<<_ier<<endl;
	if(*(x0+_i0r)<_Tc-_dT)++_i0r;
	if(*(x0+_ier)>_Tc+_dT)--_ier;
	//cout<<"_i0r="<<_i0r<<" ier="<<_ier<<endl;
	
	//cout<<"Sum="<<_sum<<" np="<<_np<<endl;
	
	if( (_ier<_i0) || (_i0r>_ie) ){//the refreshed bos is disjoint from the old one. Ineeficient case
		_sum=f_sum(_i0r,_ier);
	    _np=_ier-_i0r+1;
	}else{
  	    if(_i0<=_i0r){
	      _sum-=f_sum(_i0,_i0r-1);
	      _np-=(_i0r-_i0);
	      //cout<<"-f_sum(_i0,_i0r-1)="<<f_sum(_i0,_i0r-1)<<" np- (_i0r-_i0)="<<(_i0r-_i0)<<endl;
	    }else{
	      _sum+=f_sum(_i0r,_i0-1);
	      _np+=(_i0-_i0r);
	    }
	    //cout<<"-Sum="<<_sum<<" np="<<_np<<endl;
	
	    if(_ie<=_ier){
	      _sum+=f_sum(_ie+1,_ier);
	      _np+=(_ier-_ie);
	      //cout<<"+f_sum(_ie+1,_ier)="<<f_sum(_ie+1,_ier)<<" np+ (_ier-_ie)="<<(_ier-_ie)<<endl;
	    }else{
	      _sum-=f_sum(_ier+1,_ie);
	      _np-=(_ie-_ier);	
	    }
	}
	
	//cout<<"-+Sum="<<_sum<<" np="<<_np<<" noise="<<_sum/_np<<endl;

	_i0=_i0r;
	_ie=_ier;
	
  }else{
	  f_alert("Box::refresh problem; use init first");  
  }
}



void Box:: init(T Tc){
    //cout<<"Box::init"<<endl;
   	_init_ok=true;
	_Tc=Tc;
	
	//cout<<"dT="<<setprecision(8)<< _dT<<endl;
	//cout<<"Tc="<<setprecision(8)<<Tc<<endl;
	//cout<<"T0="<<setprecision(8)<<_Tc-_dT<<" Te="<<setprecision(8)<<_Tc+_dT<<endl;
	//cout<<"x0="<<*x0<<" Xe="<<*xe<<endl;

	//int _ic=f_find_ind_s(x0,xe,Tc);
	//cout<<"ic="<<_ic<<endl;
	_i0=f_find_ind_s(x0,xe,_Tc-_dT);
	_ie=f_find_ind_s(x0,xe,_Tc+_dT);
	
	if(_i0<0){
      //cout<<"out of table"<<endl;
	  _i0=0;
	}
	if(_ie<0){
      //cout<<"out of table"<<endl;
	  _ie=_n-1;
	}
	
    //cout<<"_i0="<<_i0<<" ie="<<_ie<<endl;
    if(*(x0+_i0)<_Tc-_dT)++_i0;
	if(*(x0+_ie)>_Tc+_dT)--_ie;
	//cout<<"_i0="<<_i0<<" ie="<<_ie<<endl;
	
	_sum=f_sum(_i0,_ie);
	_np=_ie-_i0+1;
	
	//cout<<"Sum="<<_sum<<" np="<<_np<<" noise="<<_sum/_np<<endl;
}

void Box:: init2(T Tc){
 	cout<<"Box::init"<<endl;
   	_init_ok=true;
	_Tc=Tc;


     if(*x0==_Tc-_dT){
         _i0=0;
     }else if(*x0<_Tc-_dT){
         _i0=-1;
     }else{
       _i0=0;
     for(typename vector<T>::iterator it=x0;it!=(xe-1);++it,++_i0){
        if(*it>=_Tc-_dT && *(it+1)<=_Tc-_dT){
          break;
        }
     }
     }


     if(*x0==_Tc+_dT){
         _ie=0;
     }else if(*x0<_Tc+_dT){
         _ie=-1;
     }else{
       _ie=0;
     for(typename vector<T>::iterator it=x0;it!=(xe-1);++it,++_ie){
        if(*it>=_Tc+_dT && *(it+1)<=_Tc+_dT){
          break;
        }
     }
     }

	if(_i0<0){
	  //cout<<"out of table"<<endl;
	  _i0=0;
	}
	if(_ie<0){
	  //cout<<"out of table"<<endl;
	  _ie=_n-1;
	}

	//cout<<"_i0="<<_i0<<" ie="<<_ie<<endl;
    if(*(x0+_i0)<_Tc-_dT)++_i0;
	if(*(x0+_ie)>_Tc+_dT)--_ie;
	//cout<<"_i0="<<_i0<<" ie="<<_ie<<endl;

	_sum=f_sum(_i0,_ie);
	_np=_ie-_i0+1;

	//cout<<"Sum="<<_sum<<" np="<<_np<<" noise="<<_sum/_np<<endl;
}

T Box::Tc(){
   if(!_init_ok){
	   f_alert("box::Tc() problem; use init() first");  
   }
   return(_Tc);
}

int Box::i0(){
   if(!_init_ok){
	   f_alert("box::i0() problem; use init() first");  
   }
   return(_i0);
}

int Box::ie(){
   if(!_init_ok){
	   f_alert("box::ie() problem; use init() first");  
   }
   return(_ie);
}

T Box::Sum(){
   if(!_init_ok){
	   f_alert("box::Sum() problem; use init() first");  
   }
   return(_sum);
}

int Box::np(){
   if(!_init_ok){
	   f_alert("box::np() problem; use init() first");  
   }
   return(_np);
}
//** Box end **




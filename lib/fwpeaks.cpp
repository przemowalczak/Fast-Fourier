#include "fwpeaks.hpp"


vector<double>& FWPeaks::fr(){
    return (_fr);
}

vector<double>& FWPeaks::ampl(){
    return (_ampl);
}
vector<double>& FWPeaks::amplpeaks(){
    return (_amplpeaks);
}
vector<double>& FWPeaks::frpeaks(){
    return (_frpeaks);
}
vector<double>& FWPeaks::Ppeaks(){
    return (_Ppeaks);
}
vector<double>& FWPeaks::SNpeaks(){
    return (_SNpeaks);
}



bool FWPeaks::fourier(vector<double>&x,vector<double>&y,vector<double>&e_y,double f0,double fe,double df,bool use_data){
  //t.b.d.

   return ok;
}


bool FWPeaks::fourier(int narg, char **arg){
    //t.b.d.

     return ok;
}

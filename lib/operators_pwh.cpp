#include "operators_pwh.hpp"



//*************  operators *******************************8

vector<long double> operator * (long double const &c1, vector<long  double> const &c2){ 
    vector<long double> v(c2.size());
    for(size_t i=0;i<c2.size();++i){
        v[i]=c2[i]*c1;
    }
    return (v); 
} 
vector<long double> operator * (vector<long  double> const &c2,long double const &c1){ 
    vector<long double> v(c2.size());
    for(size_t i=0;i<c2.size();++i){
        v[i]=c2[i]*c1;
    }
    return (v); 
}
vector<long double> operator / (vector<long  double> const &c2,long double const &c1){ 
    vector<long double> v(c2.size());
    for(size_t i=0;i<c2.size();++i){
        v[i]=c2[i]/c1;
    }
    return (v); 
}
vector<long double> operator + (vector<long double> const &c1, vector<long  double> const &c2){ 
    vector<long double> v(c2.size());
    for(size_t i=0;i<c2.size();++i){
        v[i]=c2[i]+c1[i];
    }
    return (v); 
} 
vector<long double> operator - (vector<long double> const &c1, vector<long  double> const &c2){ 
    vector<long double> v(c2.size());
    for(size_t i=0;i<c2.size();++i){
        v[i]=c2[i]-c1[i];
    }
    return (v); 
} 
vector<double> operator * (double const &c1, vector< double> const &c2){ 
    vector<double> v(c2.size());
    for(size_t i=0;i<c2.size();++i){
        v[i]=c2[i]*c1;
    }
    return (v); 
} 
vector<double> operator * (vector< double> const &c2,double const &c1){ 
    vector<double> v(c2.size());
    for(size_t i=0;i<c2.size();++i){
        v[i]=c2[i]*c1;
    }
    return (v); 
} 
vector<double> operator + (vector<double> const &c1, vector< double> const &c2){ 
    vector<double> v(c2.size());
    for(size_t i=0;i<c2.size();++i){
        v[i]=c2[i]+c1[i];
    }
    return (v); 
} 
vector<double> operator - (vector<double> const &c1, vector< double> const &c2){ 
    vector<double> v(c2.size());
    for(size_t i=0;i<c2.size();++i){
        v[i]=c2[i]-c1[i];
    }
    return (v); 
} 








ostream & operator<< (ostream &ret, vector<string> &vec){
   ostringstream ret2;
   for(unsigned int i=0;i<vec.size();i++){
      ret2<<vec[i]<<" ";//<<endl;
   }
   ret<<ret2.str();
   return(ret);
}
ostream & operator<< (ostream &ret, vector<vector<string> >&vec){
   ostringstream ret2;
   for(unsigned int i=0;i<vec.size();i++){
     for(unsigned int j=0;j<vec[i].size();j++){
      ret2<<vec[i][j]<<" ";//<<endl;
     }
     ret2<<endl;
   }
   ret<<ret2.str();
   return(ret);
}
ostream & operator<< (ostream &ret, vector<vector<vector<string> > >&vec){
   ostringstream ret2;
   for(unsigned int i=0;i<vec.size();i++){
     for(unsigned int j=0;j<vec[i].size();j++){
       for(unsigned int k=0;k<vec[i][j].size();k++){
         ret2<<vec[i][j][k]<<" ";//<<endl;
       }
       ret2<<endl;
     }
     ret2<<endl;
   }
   ret<<ret2.str();
   return(ret);
}
ostream & operator<< (ostream &ret, vector<vector<vector<vector<string> > > >&vec){
   ostringstream ret2;
   int con=1;
   for(unsigned int i=0;i<vec.size();i++){
     con=1;
     for(unsigned int j=0;j<vec[i].size();j++){
       con=1;
       for(unsigned int k=0;k<vec[i][j].size();k++){
	 con=1;
	 for(unsigned int l=0;l<vec[i][j][k].size();l++){
            //if(*max_element(vec[i][j][k].begin(),vec[i][j][k].end())!=0){	   
	      ret2<<vec[i][j][k][l]<<" ";//<<endl;
              //ret2<<i<<" "<<j<<" "<<k<<" "<<l<<" "<<vec[i][j][k][l]<<" ";//<<endl;
	      con=0;
	    //}
	 }
	 if(con==0)ret2<<endl;
       }
       if(con==0)ret2<<endl;
     }
     if(con==0)ret2<<endl;
   }
   ret<<ret2.str();
   return(ret);
}
ostream & operator<< (ostream &ret, vector<vector<vector<vector<vector<string> > > > >&vec){
   ostringstream ret2;
   if(vec.size()>0){
   //cout<<" 5 dimentions"<<endl;
   int con=1;
   for(unsigned int i=0;i<vec.size();i++){
     con=1;
     for(unsigned int j=0;j<vec[i].size();j++){
       con=1;
       for(unsigned int k=0;k<vec[i][j].size();k++){
	 con=1;
	 for(unsigned int l=0;l<vec[i][j][k].size();l++){
	    con=1;
	    for(unsigned int m=0;m<vec[i][j][k][l].size();m++){
              //if(*max_element(vec[i][j][k][l].begin(),vec[i][j][k][l].end())!=0){	   
	        ret2<<vec[i][j][k][l][m]<<" ";//<<endl;
                //ret2<<i<<" "<<j<<" "<<k<<" "<<l<<" "<<vec[i][j][k][l]<<" ";//<<endl;
	        con=0;
	      //}
	    }
	    if(con==0)ret2<<endl;
	 }
	 if(con==0)ret2<<endl;
       }
       if(con==0)ret2<<endl;
     }
     if(con==0)ret2<<endl;
   }
   ret<<ret2.str();
   }
   return(ret);
}



ostream & operator<< (ostream &ret, vector<bool> &vec){
   ostringstream ret2;
   for(unsigned int i=0;i<vec.size();i++){
      ret2<<vec[i]<<" ";//<<endl;
   }
   ret<<ret2.str();
   return(ret);
}
ostream & operator<< (ostream &ret, vector<vector<bool> >&vec){
   ostringstream ret2;
   for(unsigned int i=0;i<vec.size();i++){
     for(unsigned int j=0;j<vec[i].size();j++){
      ret2<<vec[i][j]<<" ";//<<endl;
     }
     ret2<<endl;
   }
   ret<<ret2.str();
   return(ret);
}
ostream & operator<< (ostream &ret, vector<vector<vector<bool> > >&vec){
   ostringstream ret2;
   for(unsigned int i=0;i<vec.size();i++){
     for(unsigned int j=0;j<vec[i].size();j++){
       for(unsigned int k=0;k<vec[i][j].size();k++){
         ret2<<vec[i][j][k]<<" ";//<<endl;
       }
       ret2<<endl;
     }
     ret2<<endl;
   }
   ret<<ret2.str();
   return(ret);
}
ostream & operator<< (ostream &ret, vector<vector<vector<vector<bool> > > >&vec){
   ostringstream ret2;
   int con=1;
   for(unsigned int i=0;i<vec.size();i++){
     con=1;
     for(unsigned int j=0;j<vec[i].size();j++){
       con=1;
       for(unsigned int k=0;k<vec[i][j].size();k++){
	 con=1;
	 for(unsigned int l=0;l<vec[i][j][k].size();l++){
            //if(*max_element(vec[i][j][k].begin(),vec[i][j][k].end())!=0){	   
	      ret2<<vec[i][j][k][l]<<" ";//<<endl;
              //ret2<<i<<" "<<j<<" "<<k<<" "<<l<<" "<<vec[i][j][k][l]<<" ";//<<endl;
	      con=0;
	    //}
	 }
	 if(con==0)ret2<<endl;
       }
       if(con==0)ret2<<endl;
     }
     if(con==0)ret2<<endl;
   }
   ret<<ret2.str();
   return(ret);
}
ostream & operator<< (ostream &ret, vector<vector<vector<vector<vector<bool> > > > >&vec){
   ostringstream ret2;
   if(vec.size()>0){
   //cout<<" 5 dimentions"<<endl;
   int con=1;
   for(unsigned int i=0;i<vec.size();i++){
     con=1;
     for(unsigned int j=0;j<vec[i].size();j++){
       con=1;
       for(unsigned int k=0;k<vec[i][j].size();k++){
	 con=1;
	 for(unsigned int l=0;l<vec[i][j][k].size();l++){
	    con=1;
	    for(unsigned int m=0;m<vec[i][j][k][l].size();m++){
              //if(*max_element(vec[i][j][k][l].begin(),vec[i][j][k][l].end())!=0){	   
	        ret2<<vec[i][j][k][l][m]<<" ";//<<endl;
                //ret2<<i<<" "<<j<<" "<<k<<" "<<l<<" "<<vec[i][j][k][l]<<" ";//<<endl;
	        con=0;
	      //}
	    }
	    if(con==0)ret2<<endl;
	 }
	 if(con==0)ret2<<endl;
       }
       if(con==0)ret2<<endl;
     }
     if(con==0)ret2<<endl;
   }
   ret<<ret2.str();
   }
   return(ret);
}




ostream & operator<< (ostream &ret, vector<int> &vec){
   ostringstream ret2;
   for(unsigned int i=0;i<vec.size();i++){
      ret2<<vec[i]<<" ";//<<endl;
   }
   ret<<ret2.str();
   return(ret);
}
ostream & operator<< (ostream &ret, vector<vector<int> >&vec){
   ostringstream ret2;
   for(unsigned int i=0;i<vec.size();i++){
     for(unsigned int j=0;j<vec[i].size();j++){
      ret2<<vec[i][j]<<" ";//<<endl;
     }
     ret2<<endl;
   }
   ret<<ret2.str();
   return(ret);
}
ostream & operator<< (ostream &ret, vector<vector<vector<int> > >&vec){
   ostringstream ret2;
   for(unsigned int i=0;i<vec.size();i++){
     for(unsigned int j=0;j<vec[i].size();j++){
       for(unsigned int k=0;k<vec[i][j].size();k++){
         ret2<<vec[i][j][k]<<" ";//<<endl;
       }
       ret2<<endl;
     }
     ret2<<endl;
   }
   ret<<ret2.str();
   return(ret);
}
ostream & operator<< (ostream &ret, vector<vector<vector<vector<int> > > >&vec){
   ostringstream ret2;
   int con=1;
   for(unsigned int i=0;i<vec.size();i++){
     con=1;
     for(unsigned int j=0;j<vec[i].size();j++){
       con=1;
       for(unsigned int k=0;k<vec[i][j].size();k++){
	 con=1;
	 for(unsigned int l=0;l<vec[i][j][k].size();l++){
            //if(*max_element(vec[i][j][k].begin(),vec[i][j][k].end())!=0){	   
	      ret2<<vec[i][j][k][l]<<" ";//<<endl;
              //ret2<<i<<" "<<j<<" "<<k<<" "<<l<<" "<<vec[i][j][k][l]<<" ";//<<endl;
	      con=0;
	    //}
	 }
	 if(con==0)ret2<<endl;
       }
       //if(con==0)ret2<<endl;
     }
     //if(con==0)ret2<<endl;
   }
   ret<<ret2.str();
   return(ret);
}
ostream & operator<< (ostream &ret, vector<vector<vector<vector<vector<int> > > > >&vec){
   ostringstream ret2;
   if(vec.size()>0){
   //cout<<" 5 dimentions"<<endl;
   int con=1;
   for(unsigned int i=0;i<vec.size();i++){
     con=1;
     for(unsigned int j=0;j<vec[i].size();j++){
       con=1;
       for(unsigned int k=0;k<vec[i][j].size();k++){
	 con=1;
	 for(unsigned int l=0;l<vec[i][j][k].size();l++){
	    con=1;
	    for(unsigned int m=0;m<vec[i][j][k][l].size();m++){
              //if(*max_element(vec[i][j][k][l].begin(),vec[i][j][k][l].end())!=0){	   
	        ret2<<vec[i][j][k][l][m]<<" ";//<<endl;
                //ret2<<i<<" "<<j<<" "<<k<<" "<<l<<" "<<vec[i][j][k][l]<<" ";//<<endl;
	        con=0;
	      //}
	    }
	    if(con==0)ret2<<endl;
	 }
	 if(con==0)ret2<<endl;
       }
       if(con==0)ret2<<endl;
     }
     if(con==0)ret2<<endl;
   }
   ret<<ret2.str();
   }
   return(ret);
}

ostream & operator<< (ostream &ret, vector<size_t> &vec){
   ostringstream ret2;
   for(unsigned int i=0;i<vec.size();i++){
      ret2<<vec[i]<<" ";//<<endl;
   }
   ret<<ret2.str();
   return(ret);
}
ostream & operator<< (ostream &ret, vector<vector<size_t> >&vec){
   ostringstream ret2;
   for(unsigned int i=0;i<vec.size();i++){
     for(unsigned int j=0;j<vec[i].size();j++){
      ret2<<vec[i][j]<<" ";//<<endl;
     }
     ret2<<endl;
   }
   ret<<ret2.str();
   return(ret);
}
ostream & operator<< (ostream &ret, vector<vector<vector<size_t> > >&vec){
   ostringstream ret2;
   for(unsigned int i=0;i<vec.size();i++){
     for(unsigned int j=0;j<vec[i].size();j++){
       for(unsigned int k=0;k<vec[i][j].size();k++){
         ret2<<vec[i][j][k]<<" ";//<<endl;
       }
       ret2<<endl;
     }
     ret2<<endl;
   }
   ret<<ret2.str();
   return(ret);
}
ostream & operator<< (ostream &ret, vector<vector<vector<vector<size_t> > > >&vec){
   ostringstream ret2;
   int con=1;
   for(unsigned int i=0;i<vec.size();i++){
     con=1;
     for(unsigned int j=0;j<vec[i].size();j++){
       con=1;
       for(unsigned int k=0;k<vec[i][j].size();k++){
	 con=1;
	 for(unsigned int l=0;l<vec[i][j][k].size();l++){
            //if(*max_element(vec[i][j][k].begin(),vec[i][j][k].end())!=0){	   
	      ret2<<vec[i][j][k][l]<<" ";//<<endl;
              //ret2<<i<<" "<<j<<" "<<k<<" "<<l<<" "<<vec[i][j][k][l]<<" ";//<<endl;
	      con=0;
	    //}
	 }
	 if(con==0)ret2<<endl;
       }
       //if(con==0)ret2<<endl;
     }
     //if(con==0)ret2<<endl;
   }
   ret<<ret2.str();
   return(ret);
}
ostream & operator<< (ostream &ret, vector<vector<vector<vector<vector<size_t> > > > >&vec){
   ostringstream ret2;
   if(vec.size()>0){
   //cout<<" 5 dimentions"<<endl;
   int con=1;
   for(unsigned int i=0;i<vec.size();i++){
     con=1;
     for(unsigned int j=0;j<vec[i].size();j++){
       con=1;
       for(unsigned int k=0;k<vec[i][j].size();k++){
	 con=1;
	 for(unsigned int l=0;l<vec[i][j][k].size();l++){
	    con=1;
	    for(unsigned int m=0;m<vec[i][j][k][l].size();m++){
              //if(*max_element(vec[i][j][k][l].begin(),vec[i][j][k][l].end())!=0){	   
	        ret2<<vec[i][j][k][l][m]<<" ";//<<endl;
                //ret2<<i<<" "<<j<<" "<<k<<" "<<l<<" "<<vec[i][j][k][l]<<" ";//<<endl;
	        con=0;
	      //}
	    }
	    if(con==0)ret2<<endl;
	 }
	 if(con==0)ret2<<endl;
       }
       if(con==0)ret2<<endl;
     }
     if(con==0)ret2<<endl;
   }
   ret<<ret2.str();
   }
   return(ret);
}

ostream & operator<< (ostream &ret, vector<double> &vec){
   ostringstream ret2;
   for(unsigned int i=0;i<vec.size();i++){
      ret2<<vec[i]<<" ";//<<endl;
   }
   ret<<ret2.str();
   return(ret);
}
ostream & operator<< (ostream &ret, vector<vector<double> >&vec){
   ostringstream ret2;
   for(unsigned int i=0;i<vec.size();i++){
     for(unsigned int j=0;j<vec[i].size();j++){
      ret2<<vec[i][j]<<" ";//<<endl;
     }
     ret2<<endl;
   }
   ret<<ret2.str();
   return(ret);
}
ostream & operator<< (ostream &ret, vector<vector<vector<double> > >&vec){
   ostringstream ret2;
   for(unsigned int i=0;i<vec.size();i++){
     for(unsigned int j=0;j<vec[i].size();j++){
       for(unsigned int k=0;k<vec[i][j].size();k++){
         ret2<<vec[i][j][k]<<" ";//<<endl;
       }
       ret2<<endl;
     }
     if(i<vec.size()-1)ret2<<endl;
   }
   ret<<ret2.str();
   return(ret);
}
ostream & operator<< (ostream &ret, vector<vector<vector<vector<double> > > >&vec){
   ostringstream ret2;
   int con=1;
   for(unsigned int i=0;i<vec.size();i++){
     con=1;
     for(unsigned int j=0;j<vec[i].size();j++){
       con=1;
       for(unsigned int k=0;k<vec[i][j].size();k++){
	 con=1;
	 for(unsigned int l=0;l<vec[i][j][k].size();l++){
            //if(*max_element(vec[i][j][k].begin(),vec[i][j][k].end())!=0){	   
	      ret2<<vec[i][j][k][l]<<" ";//<<endl;
              //ret2<<i<<" "<<j<<" "<<k<<" "<<l<<" "<<vec[i][j][k][l]<<" ";//<<endl;
	      con=0;
	    //}
	 }
	 if(con==0)ret2<<endl;
       }
       if(con==0)ret2<<endl;
     }
     if(con==0)ret2<<endl;
   }
   ret<<ret2.str();
   return(ret);
}
ostream & operator<< (ostream &ret, vector<vector<vector<vector<vector<double> > > > >&vec){
   ostringstream ret2;
   if(vec.size()>0){
   //cout<<" 5 dimentions"<<endl;
   int con=1;
   for(unsigned int i=0;i<vec.size();i++){
     con=1;
     for(unsigned int j=0;j<vec[i].size();j++){
       con=1;
       for(unsigned int k=0;k<vec[i][j].size();k++){
	 con=1;
	 for(unsigned int l=0;l<vec[i][j][k].size();l++){
	    con=1;
	    for(unsigned int m=0;m<vec[i][j][k][l].size();m++){
              //if(*max_element(vec[i][j][k][l].begin(),vec[i][j][k][l].end())!=0){	   
	        ret2<<vec[i][j][k][l][m]<<" ";//<<endl;
                //ret2<<i<<" "<<j<<" "<<k<<" "<<l<<" "<<vec[i][j][k][l]<<" ";//<<endl;
	        con=0;
	      //}
	    }
	    if(con==0)ret2<<endl;
	 }
	 if(con==0)ret2<<endl;
       }
       if(con==0)ret2<<endl;
     }
     if(con==0)ret2<<endl;
   }
   ret<<ret2.str();
   }
   return(ret);
}
ostream & operator<< (ostream &ret, vector<vector<vector<vector<vector<vector<double> > > > > >&vec){
   ostringstream ret2;
   if(vec.size()>0){
   //cout<<" 5 dimentions"<<endl;
   int con=1;
   for(unsigned int i=0;i<vec.size();i++){
     con=1;
     for(unsigned int j=0;j<vec[i].size();j++){
       con=1;
       for(unsigned int k=0;k<vec[i][j].size();k++){
	 con=1;
	 for(unsigned int l=0;l<vec[i][j][k].size();l++){
	    con=1;
	    for(unsigned int m=0;m<vec[i][j][k][l].size();m++){
	      con=1;
	      for(unsigned int n=0;n<vec[i][j][k][l][m].size();n++){
              //if(*max_element(vec[i][j][k][l].begin(),vec[i][j][k][l].end())!=0){	   
	        ret2<<vec[i][j][k][l][m][n]<<" ";//<<endl;
                //ret2<<i<<" "<<j<<" "<<k<<" "<<l<<" "<<vec[i][j][k][l]<<" ";//<<endl;
	        con=0;
	      //}
	      }
	      if(con==0)ret2<<endl;
	    }
	    if(con==0)ret2<<endl;
	 }
	 if(con==0)ret2<<endl;
       }
       if(con==0)ret2<<endl;
     }
     if(con==0)ret2<<endl;
   }
   ret<<ret2.str();
   }
   return(ret);
}

ostream & operator<< (ostream &ret, vector<long double> &vec){
   ostringstream ret2;
   for(unsigned int i=0;i<vec.size();i++){
      ret2<<vec[i]<<" ";//<<endl;
   }
   ret<<ret2.str();
   return(ret);
}
ostream & operator<< (ostream &ret, vector<vector<long double> >&vec){
   ostringstream ret2;
   for(unsigned int i=0;i<vec.size();i++){
     for(unsigned int j=0;j<vec[i].size();j++){
      ret2<<vec[i][j]<<" ";//<<endl;
     }
     ret2<<endl;
   }
   ret<<ret2.str();
   return(ret);
}
ostream & operator<< (ostream &ret, vector<vector<vector<long double> > >&vec){
   ostringstream ret2;
   for(unsigned int i=0;i<vec.size();i++){
     for(unsigned int j=0;j<vec[i].size();j++){
       for(unsigned int k=0;k<vec[i][j].size();k++){
         ret2<<vec[i][j][k]<<" ";//<<endl;
       }
       ret2<<endl;
     }
     ret2<<endl;
   }
   ret<<ret2.str();
   return(ret);
}
ostream & operator<< (ostream &ret, vector<vector<vector<vector<long double> > > >&vec){
   ostringstream ret2;
   int con=1;
   for(unsigned int i=0;i<vec.size();i++){
     con=1;
     for(unsigned int j=0;j<vec[i].size();j++){
       con=1;
       for(unsigned int k=0;k<vec[i][j].size();k++){
	 con=1;
	 for(unsigned int l=0;l<vec[i][j][k].size();l++){
            //if(*max_element(vec[i][j][k].begin(),vec[i][j][k].end())!=0){	   
	      ret2<<vec[i][j][k][l]<<" ";//<<endl;
              //ret2<<i<<" "<<j<<" "<<k<<" "<<l<<" "<<vec[i][j][k][l]<<" ";//<<endl;
	      con=0;
	    //}
	 }
	 if(con==0)ret2<<endl;
       }
       if(con==0)ret2<<endl;
     }
     if(con==0)ret2<<endl;
   }
   ret<<ret2.str();
   return(ret);
}
ostream & operator<< (ostream &ret, vector<vector<vector<vector<vector<long double> > > > >&vec){
   ostringstream ret2;
   if(vec.size()>0){
   //cout<<" 5 dimentions"<<endl;
   int con=1;
   for(unsigned int i=0;i<vec.size();i++){
     con=1;
     for(unsigned int j=0;j<vec[i].size();j++){
       con=1;
       for(unsigned int k=0;k<vec[i][j].size();k++){
	 con=1;
	 for(unsigned int l=0;l<vec[i][j][k].size();l++){
	    con=1;
	    for(unsigned int m=0;m<vec[i][j][k][l].size();m++){
              //if(*max_element(vec[i][j][k][l].begin(),vec[i][j][k][l].end())!=0){	   
	        ret2<<vec[i][j][k][l][m]<<" ";//<<endl;
                //ret2<<i<<" "<<j<<" "<<k<<" "<<l<<" "<<vec[i][j][k][l]<<" ";//<<endl;
	        con=0;
	      //}
	    }
	    if(con==0)ret2<<endl;
	 }
	 if(con==0)ret2<<endl;
       }
       if(con==0)ret2<<endl;
     }
     if(con==0)ret2<<endl;
   }
   ret<<ret2.str();
   }
   return(ret);
}
ostream & operator<< (ostream &ret, vector<vector<vector<vector<vector<vector<long double> > > > > >&vec){
   ostringstream ret2;
   if(vec.size()>0){
   //cout<<" 5 dimentions"<<endl;
   int con=1;
   for(unsigned int i=0;i<vec.size();i++){
     con=1;
     for(unsigned int j=0;j<vec[i].size();j++){
       con=1;
       for(unsigned int k=0;k<vec[i][j].size();k++){
	 con=1;
	 for(unsigned int l=0;l<vec[i][j][k].size();l++){
	    con=1;
	    for(unsigned int m=0;m<vec[i][j][k][l].size();m++){
	      con=1;
	      for(unsigned int n=0;n<vec[i][j][k][l][m].size();n++){
              //if(*max_element(vec[i][j][k][l].begin(),vec[i][j][k][l].end())!=0){	   
	        ret2<<vec[i][j][k][l][m][n]<<" ";//<<endl;
                //ret2<<i<<" "<<j<<" "<<k<<" "<<l<<" "<<vec[i][j][k][l]<<" ";//<<endl;
	        con=0;
	      //}
	      }
	      if(con==0)ret2<<endl;
	    }
	    if(con==0)ret2<<endl;
	 }
	 if(con==0)ret2<<endl;
       }
       if(con==0)ret2<<endl;
     }
     if(con==0)ret2<<endl;
   }
   ret<<ret2.str();
   }
   return(ret);
}

ostream & operator<< (ostream &ret, vector<complex<double> >&vec){
   ostringstream ret2;
   for(unsigned int i=0;i<vec.size();i++){
      ret2<<vec[i]<<" ";//<<endl;
   }
   ret<<ret2.str();
   return(ret);
}
ostream & operator<< (ostream &ret, vector<vector<complex<double> > >&vec){
   ostringstream ret2;
   for(unsigned int i=0;i<vec.size();i++){
     for(unsigned int j=0;j<vec[i].size();j++){
      ret2<<vec[i][j]<<" ";//<<endl;
      //ret2<<setw(16)<<setprecision(2)<<vec[i][j]<<" ";
     }
     ret2<<endl;
   }
   ret<<ret2.str();
   return(ret);
}
ostream & operator<< (ostream &ret, vector<vector<vector<complex<double> > > >&vec){
   ostringstream ret2;
   for(unsigned int i=0;i<vec.size();i++){
     for(unsigned int j=0;j<vec[i].size();j++){
       for(unsigned int k=0;k<vec[i][j].size();k++){
         ret2<<vec[i][j][k]<<" ";//<<endl;
       }
       ret2<<endl;
     }
     ret2<<endl;
   }
   ret<<ret2.str();
   return(ret);
}
ostream & operator<< (ostream &ret, vector<vector<vector<vector<complex<double> > > > >&vec){
   ostringstream ret2;
   int con=1;
   for(unsigned int i=0;i<vec.size();i++){
     con=1;
     for(unsigned int j=0;j<vec[i].size();j++){
       con=1;
       for(unsigned int k=0;k<vec[i][j].size();k++){
	 con=1;
	 for(unsigned int l=0;l<vec[i][j][k].size();l++){
            //if(*max_element(vec[i][j][k].begin(),vec[i][j][k].end())!=0){	   
	      ret2<<vec[i][j][k][l]<<" ";//<<endl;
              //ret2<<i<<" "<<j<<" "<<k<<" "<<l<<" "<<vec[i][j][k][l]<<" ";//<<endl;
	      con=0;
	    //}
	 }
	 if(con==0)ret2<<endl;
       }
       //if(con==0)ret2<<endl;
     }
     //if(con==0)ret2<<endl;
   }
   ret<<ret2.str();
   return(ret);
}
ostream & operator<< (ostream &ret, vector<vector<vector<vector<vector<complex<double> > > > > >&vec){
   ostringstream ret2;
   if(vec.size()>0){
   //cout<<" 5 dimentions"<<endl;
   int con=1;
   for(unsigned int i=0;i<vec.size();i++){
     con=1;
     for(unsigned int j=0;j<vec[i].size();j++){
       con=1;
       for(unsigned int k=0;k<vec[i][j].size();k++){
	 con=1;
	 for(unsigned int l=0;l<vec[i][j][k].size();l++){
	    con=1;
	    for(unsigned int m=0;m<vec[i][j][k][l].size();m++){
              //if(*max_element(vec[i][j][k][l].begin(),vec[i][j][k][l].end())!=0){	   
	        ret2<<vec[i][j][k][l][m]<<" ";//<<endl;
                //ret2<<i<<" "<<j<<" "<<k<<" "<<l<<" "<<vec[i][j][k][l]<<" ";//<<endl;
	        con=0;
	      //}
	    }
	    if(con==0)ret2<<endl;
	 }
	 if(con==0)ret2<<endl;
       }
       if(con==0)ret2<<endl;
     }
     if(con==0)ret2<<endl;
   }
   ret<<ret2.str();
   }
   return(ret);
}
ostream & operator<< (ostream &ret, vector<vector<vector<vector<vector<vector<complex<double> > > > > > >&vec){
   ostringstream ret2;
   if(vec.size()>0){
   //cout<<" 5 dimentions"<<endl;
   int con=1;
   for(unsigned int i=0;i<vec.size();i++){
     con=1;
     for(unsigned int j=0;j<vec[i].size();j++){
       con=1;
       for(unsigned int k=0;k<vec[i][j].size();k++){
	 con=1;
	 for(unsigned int l=0;l<vec[i][j][k].size();l++){
	    con=1;
	    for(unsigned int m=0;m<vec[i][j][k][l].size();m++){
	      con=1;
	      for(unsigned int n=0;n<vec[i][j][k][l][m].size();n++){
              //if(*max_element(vec[i][j][k][l].begin(),vec[i][j][k][l].end())!=0){	   
	        ret2<<vec[i][j][k][l][m][n]<<" ";//<<endl;
                //ret2<<i<<" "<<j<<" "<<k<<" "<<l<<" "<<vec[i][j][k][l]<<" ";//<<endl;
	        con=0;
	      //}
	      }
	      if(con==0)ret2<<endl;
	    }
	    if(con==0)ret2<<endl;
	 }
	 if(con==0)ret2<<endl;
       }
       if(con==0)ret2<<endl;
     }
     if(con==0)ret2<<endl;
   }
   ret<<ret2.str();
   }
   return(ret);
}

ostream & operator<< (ostream &ret, vector<complex<long double> >&vec){
   ostringstream ret2;
   for(unsigned int i=0;i<vec.size();i++){
      ret2<<vec[i]<<" ";//<<endl;
   }
   ret<<ret2.str();
   return(ret);
}
ostream & operator<< (ostream &ret, vector<vector<complex<long double> > >&vec){
   ostringstream ret2;
   for(unsigned int i=0;i<vec.size();i++){
     for(unsigned int j=0;j<vec[i].size();j++){
      ret2<<vec[i][j]<<" ";//<<endl;
      //ret2<<setw(16)<<setprecision(2)<<vec[i][j]<<" ";
     }
     ret2<<endl;
   }
   ret<<ret2.str();
   return(ret);
}
ostream & operator<< (ostream &ret, vector<vector<vector<complex<long double> > > >&vec){
   ostringstream ret2;
   for(unsigned int i=0;i<vec.size();i++){
     for(unsigned int j=0;j<vec[i].size();j++){
       for(unsigned int k=0;k<vec[i][j].size();k++){
         ret2<<vec[i][j][k]<<" ";//<<endl;
       }
       ret2<<endl;
     }
     ret2<<endl;
   }
   ret<<ret2.str();
   return(ret);
}
ostream & operator<< (ostream &ret, vector<vector<vector<vector<complex<long double> > > > >&vec){
   ostringstream ret2;
   int con=1;
   for(unsigned int i=0;i<vec.size();i++){
     con=1;
     for(unsigned int j=0;j<vec[i].size();j++){
       con=1;
       for(unsigned int k=0;k<vec[i][j].size();k++){
	 con=1;
	 for(unsigned int l=0;l<vec[i][j][k].size();l++){
            //if(*max_element(vec[i][j][k].begin(),vec[i][j][k].end())!=0){	   
	      ret2<<vec[i][j][k][l]<<" ";//<<endl;
              //ret2<<i<<" "<<j<<" "<<k<<" "<<l<<" "<<vec[i][j][k][l]<<" ";//<<endl;
	      con=0;
	    //}
	 }
	 if(con==0)ret2<<endl;
       }
       //if(con==0)ret2<<endl;
     }
     //if(con==0)ret2<<endl;
   }
   ret<<ret2.str();
   return(ret);
}
ostream & operator<< (ostream &ret, vector<vector<vector<vector<vector<complex<long double> > > > > >&vec){
   ostringstream ret2;
   if(vec.size()>0){
   //cout<<" 5 dimentions"<<endl;
   int con=1;
   for(unsigned int i=0;i<vec.size();i++){
     con=1;
     for(unsigned int j=0;j<vec[i].size();j++){
       con=1;
       for(unsigned int k=0;k<vec[i][j].size();k++){
	 con=1;
	 for(unsigned int l=0;l<vec[i][j][k].size();l++){
	    con=1;
	    for(unsigned int m=0;m<vec[i][j][k][l].size();m++){
              //if(*max_element(vec[i][j][k][l].begin(),vec[i][j][k][l].end())!=0){	   
	        ret2<<vec[i][j][k][l][m]<<" ";//<<endl;
                //ret2<<i<<" "<<j<<" "<<k<<" "<<l<<" "<<vec[i][j][k][l]<<" ";//<<endl;
	        con=0;
	      //}
	    }
	    if(con==0)ret2<<endl;
	 }
	 if(con==0)ret2<<endl;
       }
       if(con==0)ret2<<endl;
     }
     if(con==0)ret2<<endl;
   }
   ret<<ret2.str();
   }
   return(ret);
}
ostream & operator<< (ostream &ret, vector<vector<vector<vector<vector<vector<complex<long double> > > > > > >&vec){
   ostringstream ret2;
   if(vec.size()>0){
   //cout<<" 5 dimentions"<<endl;
   int con=1;
   for(unsigned int i=0;i<vec.size();i++){
     con=1;
     for(unsigned int j=0;j<vec[i].size();j++){
       con=1;
       for(unsigned int k=0;k<vec[i][j].size();k++){
	 con=1;
	 for(unsigned int l=0;l<vec[i][j][k].size();l++){
	    con=1;
	    for(unsigned int m=0;m<vec[i][j][k][l].size();m++){
	      con=1;
	      for(unsigned int n=0;n<vec[i][j][k][l][m].size();n++){
              //if(*max_element(vec[i][j][k][l].begin(),vec[i][j][k][l].end())!=0){	   
	        ret2<<vec[i][j][k][l][m][n]<<" ";//<<endl;
                //ret2<<i<<" "<<j<<" "<<k<<" "<<l<<" "<<vec[i][j][k][l]<<" ";//<<endl;
	        con=0;
	      //}
	      }
	      if(con==0)ret2<<endl;
	    }
	    if(con==0)ret2<<endl;
	 }
	 if(con==0)ret2<<endl;
       }
       if(con==0)ret2<<endl;
     }
     if(con==0)ret2<<endl;
   }
   ret<<ret2.str();
   }
   return(ret);
}


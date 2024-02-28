
#include "klunkry_pwh.hpp"



typedef double T;

bool isNumber(const std::string & s){
    bool isN=false;
    bool isIntiger=std::regex_match(s, std::regex("[(-|+)|]?[0-9]+"));
    bool isDouble=std::regex_match(s, std::regex("[(-|+)|]?[0-9]+.[0-9]*e?[(-|+)|]?[0-9]*"));
    //cout<<"s="<<s<<" isIntiger="<<isIntiger<<"  isDouble="<<isDouble<<endl;
    if(isIntiger || isDouble){
        isN=true;
    }
    return isN;
}

string f_get_path_from_file_name(string fname){
  string fnamet=f_get_file_name_from_path(fname);
  int ind=fname.find(fnamet);
  string path=fname.substr(0,ind);
  return(path);
}

vector<T> vector_db_from_vector_str(vector<string>&str){
    setlocale(LC_ALL, "en_US.utf8");
    vector<T>v;
    for(size_t i=0;i<str.size();++i){
        v.push_back(stof(str[i]));
    }
    return(v);
}
vector<T> vector_db_from_str(string str){
    setlocale(LC_ALL, "en_US.utf8");
    vector<string> strv=vector_from_str(str);
    vector<T>v;
    for(size_t i=0;i<strv.size();++i){
        v.push_back(stof(strv[i]));
    }
    return(v);
}

vector<T> autocorr(vector<T>&x){
    int order=x.size();
    vector<T> R(order);
    for (int i=0;i<order;i++) {
        T sum=0;
        for (int j=0;j<order-i;j++) {
            sum+=x[j]*x[j+i];
        }
        R[i]=sum;
    }
    return(R);
}


void print_progres(T percent){
  int barwidth=120;
  cout<<"\33[2K"; //erase previous line
  cout<<"  \033[0;35;45m|\033[0m";
  int pos=barwidth*percent;
  for(int i=0;i<barwidth;++i){
	 if(i<=pos)cout<<"\033[0;32;45m \033[0m";
	 else cout<<" ";
  }
  cout<<"\033[0;35;49m| "<<setprecision(0)<<setw(3)<<fixed<<percent*100<<" \033[0;35;49m\% \033[0m \r";
  cout.flush();
}

string f_c(string color){
   string s="";
   //https://gist.github.com/vratiu/9780109
   //Customize BASH PS1 prompt to show current GIT repository and branch.
   //#  by Mike Stewart - http://MediaDoneRight.com
  /* 
   Black="\[\033[0;30m\]"        # Black
Red="\[\033[0;31m\]"          # Red
Green="\[\033[0;32m\]"        # Green
Yellow="\[\033[0;33m\]"       # Yellow
Blue="\[\033[0;34m\]"         # Blue
Purple="\[\033[0;35m\]"       # Purple
Cyan="\[\033[0;36m\]"         # Cyan
White="\[\033[0;37m\]"        # White
   */
   if(color=="black"){
      s="\033[0;30m";   
   }else if(color=="red"){
      s="\033[0;31m";   
   }else if(color=="green"){
      s="\033[0;32m";   
   }else if(color=="yellow"){
      s="\033[0;33m";   
   }else if(color=="blue"){
      s="\033[0;34m";   
   }else if(color=="purple"){
      s="\033[0;35m";   
   }else if(color=="cyan"){
      s="\033[0;36m";   
   }else if(color=="white"){
      s="\033[0;37m";   
   }else if(color=="t1"){
      s="\033[0;45m";   
   }else if(color=="t2"){
      s="\033[0;39m";   
   }
   
   return(s);    
}

string f_b(string color){
   string s="";
   //https://gist.github.com/vratiu/9780109
   //Customize BASH PS1 prompt to show current GIT repository and branch.
   //#  by Mike Stewart - http://MediaDoneRight.com
  /* 
   Black="\[\033[0;30m\]"        # Black
Red="\[\033[0;31m\]"          # Red
Green="\[\033[0;32m\]"        # Green
Yellow="\[\033[0;33m\]"       # Yellow
Blue="\[\033[0;34m\]"         # Blue
Purple="\[\033[0;35m\]"       # Purple
Cyan="\[\033[0;36m\]"         # Cyan
White="\[\033[0;37m\]"        # White
   */
   if(color=="black"){
      s="\033[1;30m";   
   }else if(color=="red"){
      s="\033[1;31m";   
   }else if(color=="green"){
      s="\033[1;32m";   
   }else if(color=="yellow"){
      s="\033[1;33m";   
   }else if(color=="blue"){
      s="\033[1;34m";   
   }else if(color=="purple"){
      s="\033[1;35m";   
   }else if(color=="cyan"){
      s="\033[1;36m";   
   }else if(color=="white"){
      s="\033[1;37m";   
   }
   
   return(s);    
}
string f_u(string color){
   string s="";
   //https://gist.github.com/vratiu/9780109
   //Customize BASH PS1 prompt to show current GIT repository and branch.
   //#  by Mike Stewart - http://MediaDoneRight.com
  /* 
   Black="\[\033[0;30m\]"        # Black
Red="\[\033[0;31m\]"          # Red
Green="\[\033[0;32m\]"        # Green
Yellow="\[\033[0;33m\]"       # Yellow
Blue="\[\033[0;34m\]"         # Blue
Purple="\[\033[0;35m\]"       # Purple
Cyan="\[\033[0;36m\]"         # Cyan
White="\[\033[0;37m\]"        # White
   */
   if(color=="black"){
      s="\033[4;30m";   
   }else if(color=="red"){
      s="\033[4;31m";   
   }else if(color=="green"){
      s="\033[4;32m";   
   }else if(color=="yellow"){
      s="\033[4;33m";   
   }else if(color=="blue"){
      s="\033[4;34m";   
   }else if(color=="purple"){
      s="\033[4;35m";   
   }else if(color=="cyan"){
      s="\033[4;36m";   
   }else if(color=="white"){
      s="\033[4;37m";   
   }
   
   return(s);    
}


string f_reset(){
   return("\033[0m");   
}



void print_progres(T percent,string txt){
  int barwidth=50;
  int len=95;
  cout<<"\33[2K"; //erase previous line
  cout<<"  \033[0;35;49m|\033[0m";
  int pos=barwidth*percent;
  for(int i=0;i<barwidth;++i){
	 if(i<=pos)cout<<"\033[0;32;45m \033[0m";
	 else cout<<" ";
  }
  cout<<"\033[0;35;49m| "<<setprecision(0)<<setw(3)<<fixed<<percent*100<<" \033[0;35;49m\% \033[0m ";
  if(txt.length()>len){
     txt.erase(txt.begin(),txt.begin()+txt.length()-len);  
     txt="..."+txt;
  }
  cout<<txt;
  cout<<"\r";
  cout.flush();
}



void print_progres2(T percent){
  int barwidth=120;
  cout<<"[";
  int pos=barwidth*percent;
  for(int i=0;i<barwidth;++i){
	 if(i<pos)cout<<"=";
	 else if(i==pos)cout<<">";
	 else cout<<" ";
  }
  cout<<"] "<<setprecision(2)<<setw(6)<<fixed<<percent*100<<" \%\r";
  cout.flush();
}


void f_alert(string text,bool end,bool save){
   cout<<"\33[2K  !!!! "<<text<<" !!!!"<<endl;
   if(save){
      ofstream f_save;
      f_save.open("alert_report.log",fstream::app);
      f_save<<"  !!!! "<<text<<" !!!!"<<" "<<__DATE__<<" "<<__TIME__<<endl;
      f_save.close();
   }
   if(end)exit(1);
}


T roundoff(T value, unsigned char prec){
  T pow_10 = pow(10.0, prec);
  return round(value * pow_10) / pow_10;
}
long double roundoff(long double value, unsigned char prec){
  T pow_10 = pow(10.0, prec);
  return round(value * pow_10) / pow_10;
}


vector<string> f_get_format(T x, T ex){
    vector<string> s;
    
    int idot=-1;
    int idd;
    string sx=to_string(ex);
    
    int inonzero=0;
    for(size_t i=0;i<sx.length();++i){
        if(sx[i]!='0' && sx[i]!='.'){
            inonzero=i;
            break;
        }
    }
    //cout<<"inonzero="<<inonzero<<endl;
    
    for(size_t i=0;i<sx.length();++i){
        if(sx[i]=='.'){
            idot=i;
            break;
        }
    }
    if(idot==-1){
       idot=sx.length()-1;   
    }
    //cout<<"idot="<<idot<<endl;
    
    //cout<<"inonzero-idot"<<inonzero-idot<<endl;
    
    T acc=inonzero-idot;
    if(acc<0)acc=0;
    acc+=1;
    
    T xr=roundoff(x,acc);
    T exr=roundoff(ex,acc);
    
    string sxr=to_string(xr);
    string sexr=to_string(exr);
    
    for(int i=sxr.length()-1;i>=0;--i){
        bool ok=true;
        if(sxr[i]=='0'){
            if(i>0){
                if(sxr[i-1]=='.'){
                    ok=false;
                }
            }

            if(ok)sxr.erase(sxr.begin()+i);
        }else{
           break;   
        }
    }
     for(int i=sexr.length()-1;i>=0;--i){
         bool ok=true;
         if(sexr[i]=='0'){
                if(i>0){
                    if(sexr[i-1]=='.'){
                        ok=false;
                    }
                }
                if(i>1){
                    if(sexr[i-2]=='0' && sexr[i-1]!='0'){
                        ok=false;
                    }
                }
                if(ok)sexr.erase(sexr.begin()+i);
        }else{
           break;   
        }
    }
    
    //cout<<"s="<<s<<endl;
    
    if(stof(sxr)==0){
        if(sexr.length()>sxr.length()){
          sxr="0.";
        }
        while(sexr.length()>sxr.length()){
           //if(sexr.length()>sxr.length()){
              sxr+="0";

          // }
       }
    }else{

        //cout<<"acc="<<acc<<endl;
        for(size_t i=0;i<sxr.length();++i){
            if(sx[i]=='.'){
                idot=i;
                break;
            }
        }
        if(idot==-1){
           idot=sx.length()-1;
        }
        //cout<<"idot="<<idot<<endl;
        //cout<<"slength="<<sxr.length()<<endl;
        for(size_t i=0;i<acc;++i){
            if(sxr.length()<=i+idot+1){
                sxr+="0";
            }
        }

    }

    s.push_back(sxr);
    s.push_back(sexr);
    
    return(s);
}


string convert(vector<T> v,int n){
	string s{""};
	ostringstream o;
	for(size_t i=0;i<v.size();++i){
		o<<v[i]<<" ";
		if(n>0){
		   if ((i+1)%n==0)o<<"\n";	
		}
		//s+=to_string(v[i])+" ";
		
	}
	return(o.str());
}
bool present(vector<T> &v, T x){
	bool r=false;
	for(size_t i=0;i<v.size();++i){
        //cout<<"v="<<v[i]<<" x="<<x<<" "<<v[i]-x<<endl;
		if(v[i]==x){
		  r=true;
          //cout<<"r="<<r<<endl;
		  break;
		}
	}
	return(r);
}
bool present_eps(vector<T> &v, T x,T eps){
	bool r=false;
	for(size_t i=0;i<v.size();++i){
        //cout<<"v="<<v[i]<<" x="<<x<<" "<<v[i]-x<<endl;
		if(abs(v[i]-x)<eps){
		  r=true;
          //cout<<"r="<<r<<endl;
		  break;
		}
	}
	return(r);
}

bool present(vector<vector<T> > &v, vector<T> x){
	bool r=false;
	for(size_t i=0;i<v.size();++i){
        bool rr=true;
        for(size_t j=0;j<v[i].size();++j){
		   if(v[i][j]!=x[j]){
		      rr=false;
		      break;
           }
		}
		if(rr){
          r=true;
          break;
        }
	}
	return(r);
}

void f_replace(string &str, string patin, string patout){
    int pos=-patout.length();
    while((pos = str.find(patin,pos+patout.length()))!=string::npos){
        str.replace(str.begin()+pos,str.begin()+pos+patin.length(),patout);
        //cout<<str<<"--->"<<pos<<endl;   
    }
    
    //exit(1);
}



bool equal(vector<T> &v, vector<T> x){
	bool r=true;
	for(size_t i=0;i<v.size();++i){
        if(v[i]!=x[i]){
           r=false;
           break;
        }
	}
	return(r);
}

string str_from_vector(vector<string> &v){
   string s{""};
   for(size_t i=0;i<v.size();++i){
	  s+=v[i]+" ";   
   }
   return(s);
}

string str_from_vector(vector<T> &v){
   string s{""};
   for(size_t i=0;i<v.size();++i){
       ostringstream o;
       o<<v[i];
	   s+=o.str()+" ";   
   }
   return(s);
}
vector<string> vector_from_str(string s){
   vector<string> v;
   for(size_t i=0;i<=s.length();i++){
		 if(isspace(s[i])){
	  	    s.erase(i,1);
		    i--;
	     }else{
            break;
         }
   }
   for(int i=s.length()-1;i>=0;i--){
		 if(isspace(s[i])){
	  	    s.erase(i,1);
            //i--;
	     }else{
            break;
         }
   }
   if(s.length()>0){
      istringstream c{s};
      string x;
      //cout<<"s="<<s<<"---"<<endl;
      while(!c.eof()){
  	     c>>x;
	     v.push_back(x);
         //cout<<v.back()<<endl;
      }
   }
   return(v);
}


bool is_true(vector<bool> &ok){
	bool r=true;
	for(size_t i=0;i<ok.size();++i){
	  if(!ok[i]){
		 r=false;
		 break;
	  }
	}
	return(r);
}

bool present(vector<T> &v, vector<T> &x){
	bool r=false;
	vector<bool> is(x.size(),false);
	for(size_t i=0;i<v.size();++i){
		for(size_t j=0;j<x.size();++j){
		    if(v[i]==x[j]){
		       is[j]=true;
			}
		}
		if(is_true(is)){
		  r=true;
		  break;
		}
	}
	return(r);
}
void f_get_file_name(string &path){
  int  i0=-1;
  for(size_t i=0;i<path.length();i++){
      if(path[i]=='/'){
	 i0=i;
      }
  }
  //cout<<"parh="<<path<<" i0="<<i0<<" path.end()="<<path.length()<<endl;
  if(i0>-1){
    path.erase(path.begin(),path.begin()+i0+1);
  }
  //cout<<"parh="<<path<<endl;
  
}
string f_get_file_name_from_path(string path){
  int  i0=-1;
  for(size_t i=0;i<path.length();i++){
      if(path[i]=='/'){
	 i0=i;
      }
  }
  //cout<<"parh="<<path<<" i0="<<i0<<" path.end()="<<path.length()<<endl;
  if(i0>-1){
    path.erase(path.begin(),path.begin()+i0+1);
  }
  //cout<<"parh="<<path<<endl;
  return(path);
}
//**** get column ****
int f_get_column_head_nr_col(vector<string> head, string pattern,string approach){
  int n=0;
  for(size_t i=0;i<head.size();i++){
    if(approach=="match"){
      if(head[i]==pattern)return(n);
      n++;
    }
    if(approach=="find"){
      if(head[i].find(pattern)!=string::npos)return(n);
      n++;
    }
  }
  cout<<"missing column= "<<pattern<<" in head= "<<head<<endl;
  return(-1);
}
vector<T> f_get_column(vector<vector<T> >&x,vector<string>head,string pattern){
   vector<T> vec;
   int col=f_get_column_head_nr_col(head,pattern);
   if(col!=-1){
     if(x.size()>0){
       if(x[0].size()>0){
         for(size_t i=0;i<x.size();i++){
	   vec.push_back(x[i][col]);
	 }
       }
     }
   }//col!=-1
   return(vec);
}
vector<double> f_get_column_db_from_str(vector<vector<string> >&x,vector<string>head,string pattern){
    setlocale(LC_ALL, "en_US.utf8");
   vector<double> vec;
   int col=f_get_column_head_nr_col(head,pattern);
   if(col!=-1){
     if(x.size()>0){
       if(x[0].size()>0){
         for(size_t i=0;i<x.size();++i){
	       vec.push_back(atof(x[i][col].c_str()));
	     }
       }
     }
   }//col!=-1
   return(vec);
}
vector<int> f_get_column_int_from_db(vector<vector<double> >&x,vector<string>head,string pattern){
   vector<int> vec;
   int col=f_get_column_head_nr_col(head,pattern);
   if(col!=-1){
     if(x.size()>0){
       if(x[0].size()>0){
         for(size_t i=0;i<x.size();i++){
	   //double v=round(x[i][col]);
	   //int *ii=reinterpret_cast<int*>(&v);
	   //vec.push_back(*ii);
	   //vec.push_back(*reinterpret_cast<int*>(&v));
	   vec.push_back(round(x[i][col]));
	 }
       }
     }
   }//col!=-1
   return(vec);
}
//** get column **

//**** f head no col ****
int f_head_nr_col(vector<string> head, string pattern,string approach){
  int n=0;
  for(size_t i=0;i<head.size();i++){
    if(approach=="match"){
      if(head[i]==pattern)return(n);
      n++;
    }
    if(approach=="find"){
      if(head[i].find(pattern)!=string::npos)return(n);
      n++;
    }
  }
  cout<<"missing column= "<<pattern<<" in head= "<<head<<endl;
  return(-1);
}
int f_no(vector<string> head, string pattern, bool reverse, bool out,bool match){
  if(reverse){
	for(int i=head.size()-1;i>=0;i--){
      if(match){
        if(head[i]==pattern)return(i);
      }else{
        if(head[i].find(pattern)!=string::npos)return(i);
      }
    }
  }else{
    for(size_t i=0;i<head.size();i++){
      if(match){
        if(head[i]==pattern)return(i);
      }else{
        if(head[i].find(pattern)!=string::npos)return(i);
      }
    }
  }
  if(out)cout<<"missing column= "<<pattern<<" in head= "<<head<<endl;
  return(-1);
}

int f_no(vector<T> head, T pattern, bool reverse, bool out){
  if(reverse){
	for(int i=head.size()-1;i>=0;i--){
        if(head[i]==pattern)return(i);
    }
  }else{
    for(size_t i=0;i<head.size();i++){
        if(head[i]==pattern)return(i);
    }
  }
  if(out)cout<<"missing column= "<<pattern<<" in head= "<<head<<endl;
  return(-1);
}
int f_head_nr_col_na(vector<string> head, string pattern,string approach){//no allert
  int n=0;
  for(size_t i=0;i<head.size();i++){
    if(approach=="match"){
      if(head[i]==pattern)return(n);
      n++;
    }
    if(approach=="find"){
      if(head[i].find(pattern)!=string::npos)return(n);
      n++;
    }
  }
  return(-1);
}
vector<int> f_head_nr_col(vector<string> head, vector<string> pattern,string approach){
  vector<int> n;
  for(size_t i=0;i<head.size();i++){
    for(size_t j=0;j<pattern.size();j++){
      if(approach=="match"){
        if(head[i]==pattern[j]){
           n.push_back(i);
        }
      }
      if(approach=="find"){
        if(head[i].find(pattern[j])!=string::npos){
           n.push_back(i);
        }
      }
    }
    
  }
  if(n.size()==0)n.push_back(-1);
  return(n);
}
vector<int> f_no(vector<string> head, vector<string> pattern,string approach){
  vector<int> n;
  for(size_t i=0;i<head.size();i++){
    for(size_t j=0;j<pattern.size();j++){
      if(approach=="match"){
        if(head[i]==pattern[j]){
           n.push_back(i);
        }
      }
      if(approach=="find"){
        if(head[i].find(pattern[j])!=string::npos){
           n.push_back(i);
        }
      }
    }
    
  }
  if(n.size()==0)n.push_back(-1);
  return(n);
}



int f_head_nr_col_n(vector<T> head, T pattern,bool show){
  int n=0;
  for(size_t i=0;i<head.size();i++){
      if(head[i]==pattern)return(n);
      n++;
  }
  if(show)cout<<"missing column= "<<pattern<<" in head= "<<head<<endl;
  return(-1);
}

//** f head nr col ***

//**** get columns ****

vector<vector<T> >f_get_columns(vector<vector<T> > &tab,vector<string>head,vector<string>patterns){
    size_t nhead=patterns.size();
	size_t ntab=tab.size();
    vector<int>ind(nhead);
	int ii;
	for(size_t i=0;i<nhead;i++){
		if((ii=f_no(head,patterns[i]))!=-1){
		  ind[i]=ii;	
		}else{
		  ind[i]=0;	
		}
	}
	vector<vector<T> > columns(ntab,vector<T>(nhead));
	for(size_t i=0;i<tab.size();i++){
		for(size_t j=0;j<nhead;j++){
	       columns[i][j]=tab[i][ind[j]];
		}
	}
	return(columns);
}

vector<vector<T> >f_get_columns(vector<vector<string> > &tab,vector<string>head,vector<string>patterns){
    setlocale(LC_ALL, "en_US.utf8");
    size_t nhead=patterns.size();
	size_t ntab=tab.size();
    vector<int>ind(nhead);
	int ii;
	for(size_t i=0;i<nhead;i++){
		if((ii=f_no(head,patterns[i]))!=-1){
		  ind[i]=ii;	
		}else{
		  ind[i]=0;	
		}
	}
	vector<vector<T> > columns(ntab,vector<T>(nhead));
	for(size_t i=0;i<tab.size();i++){
		for(size_t j=0;j<nhead;j++){
	       columns[i][j]=atof(tab[i][ind[j]].c_str());
		}
	}
	return(columns);
}

bool f_get_col(vector<vector<string> > &tab,vector<string> &head,string pat,vector<T> &x){
    setlocale(LC_ALL, "en_US.utf8");
   size_t nr=tab.size();
   if(nr>0){
	   x.resize(nr);
	   int col=-1;
	   for(size_t i=0;i<head.size();i++){
		   if(head[i]==pat){
			  col=i;   
		   }
	   }
	   if(col==-1)return(false);
	   for(size_t i=0;i<nr;++i){
		  x[i]=atof(tab[i][col].c_str());
	   }
	   return(true);
   }else{
	  return(false);   
   }	
}

bool f_get_col(vector<vector<string> > &tab,vector<string> &head,vector<string> &patterns,vector<vector<T> > &x){
    setlocale(LC_ALL, "en_US.utf8");
   size_t nr=tab.size();
   size_t nc=patterns.size();
   if(nr>0){
	   vector<int>ind(nc);
	   int ii;
	   bool ok=false;
	   for(size_t i=0;i<nc;i++){
		  if((ii=f_no(head,patterns[i]))!=-1){
		     ind[i]=ii;
			 ok=true;
		  }else{
		     ind[i]=0;	
		  }
	   }
	   if(ok){
	     x.resize(nr,vector<T>(nc));
	     for(size_t i=0;i<tab.size();i++){
		    for(size_t j=0;j<nc;j++){
	           x[i][j]=atof(tab[i][ind[j]].c_str());
		    }
	     }
	     return(true);
	   }else{
		 return(false);   
	   }
   }else{
	  return(false);   
   }	
}

bool f_get_col(vector<vector<T> > &tab,vector<string> &head,string pat,vector<T> &x){
   size_t nr=tab.size();
   if(nr>0){
	   x.resize(nr);
	   int col=-1;
	   for(size_t i=0;i<head.size();i++){
		   if(head[i]==pat){
			  col=i;   
		   }
	   }
	   if(col==-1)return(false);
	   for(size_t i=0;i<nr;++i){
		  x[i]=(tab[i][col]);
	   }
	   return(true);
   }else{
	  return(false);   
   }	
}

bool f_get_col(vector<vector<T> > &tab,vector<string> &head,vector<string> &patterns,vector<vector<T> > &x){
   size_t nr=tab.size();
   size_t nc=patterns.size();
   if(nr>0){
	   vector<int>ind(nc);
	   int ii;
	   bool ok=false;
	   for(size_t i=0;i<nc;i++){
		  if((ii=f_no(head,patterns[i]))!=-1){
		     ind[i]=ii;
			 ok=true;
		  }else{
		     ind[i]=0;	
		  }
	   }
	   if(ok){
	     x.resize(nr,vector<T>(nc));
	     for(size_t i=0;i<tab.size();i++){
		    for(size_t j=0;j<nc;j++){
	           x[i][j]=(tab[i][ind[j]]);
		    }
	     }
	     return(true);
	   }else{
		 return(false);   
	   }
   }else{
	  return(false);   
   }	
}

bool f_get_col(vector<vector<T> > &tab,vector<string> &head,vector<string> &patterns,vector<T> &x,vector<T> &y){
   size_t nr=tab.size();
   size_t nc=patterns.size();
   if(nc<2)f_alert("f_get_col: you  need to provide at least two patterns");
   if(nr>0){
	   vector<int>ind(2);
	   int ii;
	   bool ok=false;
	   for(size_t i=0;i<2;i++){
		  if((ii=f_no(head,patterns[i]))!=-1){
		     ind[i]=ii;
			 ok=true;
		  }else{
		     ind[i]=0;	
		  }
	   }
	   if(ok){
	     if(x.size()<nr)x.resize(nr);
		 if(x.size()<nr)y.resize(nr);
	     for(size_t i=0;i<tab.size();i++){
		    x[i]=(tab[i][ind[0]]);
		    x[i]=(tab[i][ind[1]]);   
	     }
	     return(true);
	   }else{
		 return(false);   
	   }
   }else{
	  return(false);   
   }	
}
//** get columns **




bool f_reverse(vector<vector<T> > &tab,vector<vector<T> > &tabrev){
	bool ok=false;
	size_t nr=tab.size();
    if(nr>0){
	    size_t nc=tab[0].size();
		if(nc<2){
 		   f_alert("f_reverse: you  need to provide at least two columns");
 	    }
	    tabrev.resize(nc,vector<T>(nr));
		
		for(size_t i=0;i<nc;++i){
 	 	   for(size_t j=0;j<nr;++j){
			  tabrev[i][j]=tab[j][i];   
		   }
		}
		
		ok=true;
	}
	
	return(ok);
}


bool f_reverse(vector<vector<T> > &tab){
	vector<vector<T> > tabrev;
	bool ok=false;
	size_t nr=tab.size();
    if(nr>0){
	    size_t nc=tab[0].size();
		if(nc<2){
 		   f_alert("f_reverse: you  need to provide at least two columns");
 	    }
	    tabrev.resize(nc,vector<T>(nr));
		
		for(size_t i=0;i<nc;++i){
 	 	   for(size_t j=0;j<nr;++j){
			  tabrev[i][j]=tab[j][i];   
		   }
		}
		
		ok=true;
	}
	tab=tabrev;
	return(ok);
}

/*template <typename T>
string to_string(T value,int prec=6) {
    stringstream sstr;
    sstr << setprecision(prec)<< value;
    return sstr.str();
}*/

string to_string_pw(T value) {
    stringstream sstr;
    sstr<< value;
    return sstr.str();
}

string to_string_pw(T value,int prec) {
    stringstream sstr;
    sstr<<setprecision(prec)<<value;
    return sstr.str();
}


void f_erase_white_spac_void(string &str){
	for(size_t i=0;i<=str.length();i++){
		if(isspace(str[i])){
		  str.erase(i,1);
		  i--;
	   }
   }
}
string f_erase_white_spac(string str){
	for(size_t i=0;i<=str.length();i++){
		if(isspace(str[i])){
	  	  str.erase(i,1);
		  i--;
	   }
	}
	return(str);
}  

void f_erase_white_spac_void(vector<string> &str){
  for(size_t j=0;j<str.size();j++){
      for(size_t i=0;i<=str[j].length();i++){
	    if(isspace(str[j][i])){
		  str[j].erase(i,1);
		  i--;
	    }
       }
  }
}
vector<string> f_erase_white_spac(vector<string> str){
  for(size_t j=0;j<str.size();j++){
      for(size_t i=0;i<=str[j].length();i++){
	    if(isspace(str[j][i])){
		  str[j].erase(i,1);
		  i--;
	    }
       }
  }
  return(str);
}

string f_erase_sign_from_str(string str,const char c){
   for(size_t i=0;i<=str.length();i++){
       //cout<<str<<" c="<<c<<endl;
       if(str[i]==c){
	      str.erase(i,1);
	      i--;
       }
   }
   return(str);
}  

bool f_create_directories(string path,bool out){
   bool ok=false;
   if(path[path.length()-1]!='/')path+="/";
   vector<string> dirs;
   string str;
   int i0=0;
   for(unsigned int i=0;i<path.length();i++){
      if(path[i]=='/'){  
          str=path.substr(i0,i-i0);
	     if(i>0){
             dirs.push_back(str);
	     i0=i+1;
	     //cout<<"dirs["<<i<<"]="<<dirs.back()<<endl;
	  }
      }
   }
   //cout<<"dirs = "<<dirs<<endl;
   string path_temp;
   for(int i=0;i<dirs.size();i++){
      string csys;
      path_temp+=dirs[i];
      csys="mkdir "+path_temp;
      DIR *dir_mod=opendir(path_temp.c_str());
      if(!dir_mod){
	       if(out)cout<<"fcd creating = "<<path_temp<<endl;
		   if(out)cout<<csys<<endl;
           int r=system(csys.c_str());
		   ok=true;
      }else{
		   ok=false;
	       closedir(dir_mod);
	       if(out)cout<<"fcd directory = "<<path_temp<<" exists"<<endl;
      }
      path_temp+="/";
   }
   return(ok);
}

void f_add_slash(string &s,bool out){
   if(s.length()>0){
      if(s[s.length()-1]!='/'){
	    if(out)cout<<"adding / to "<<s<<endl;
	    s+="/";
      }
   }
}
   
void f_add_slash(vector<string> &s,bool out){
	for(size_t i=0;i<s.size();++i){
      if(s[i].length()>0){
        if(s[i][s[i].length()-1]!='/'){
	      if(out)cout<<"adding / to "<<s[i]<<endl;
	      s[i]+="/";
        }
      }
	}
}


void Tfree(vector<T> &v){
  vector<T> tmp;
  v.swap(tmp);
}

double f_get_db(string line,string pattern){
    setlocale(LC_ALL, "en_US.utf8");
   double x; 
   int n0=line.find(pattern)+pattern.length();
   //cout<<n0<<endl;
   int i=0;
   while(!isdigit(line[i+n0]) && line[i+n0]!='-' && line.length()>i+n0){
      //cout<<line[i+n0]<<endl;
      i++;
   }
   //cout<<"i="<<i<<endl;
   n0+=i;
   i=0;
   while(isdigit(line[i+n0]) || line[i+n0]=='.' || line[i+n0]=='-'  && line.length()>i+n0){
      //cout<<line[i+n0]<<endl;
      i++;
   }
   //cout<<"i="<<i<<endl;
   string p;
   p=line.substr(n0,i);
   //cout<<p<<endl;
   return(atof(p.c_str()));
}

double f_get_db_and_erase(string &line,string pattern){
    setlocale(LC_ALL, "en_US.utf8");
   //cout<<"line="<<line<<endl;
   //cout<<"line.lenght()="<<line.length()<<endl;
   int n0=line.find(pattern)+pattern.length();
   //cout<<"n0="<<n0<<" "<<line[n0]<<endl;
   int i=0;
   while(!isdigit(line[i+n0]) && line[i+n0]!='\n' && i+n0<line.length()){
        //cout<<"l1="<<line[i+n0]<<endl;
        i++;
   }
   //cout<<"i="<<i<<endl;
   n0+=i;
   i=0;
   while(isdigit(line[i+n0]) || line[i+n0]=='.'){
      //cout<<line[i+n0]<<endl;
      i++;
   }
   //cout<<"i="<<i<<endl;
   string p;
   p=line.substr(n0,i);
   line.erase(0,n0+i);
   //cout<<p<<endl;
   return(atof(p.c_str()));
}
double f_get_db_and_erase2(string &line,string pattern){
    setlocale(LC_ALL, "en_US.utf8");
   //cout<<"line="<<line<<endl;
   //cout<<"line.lenght()="<<line.length()<<endl;
   int n0=line.find(pattern)+pattern.length();
   //cout<<"n0="<<n0<<" "<<line[n0]<<endl;
   int i=0;
   while(!isdigit(line[i+n0]) && line[i+n0]!='\n' && i+n0<line.length()){
        //cout<<"l1="<<line[i+n0]<<endl;
        i++;
   }
   //cout<<"i="<<i<<endl;
   n0+=i;
   i=0;
   while(isdigit(line[i+n0]) || line[i+n0]=='.' || line[i+n0]=='-' || line[i+n0]=='+' || (i>0 && (line[i+n0]=='e') || line[i+n0]=='E' ) ){
      //cout<<line[i+n0]<<endl;
      i++;
   }
   //cout<<"i="<<i<<endl;
   string p;
   p=line.substr(n0,i);
   line.erase(0,n0+i);
   //cout<<p<<endl;
   return(atof(p.c_str()));
}
double f_get_db(string line){
    setlocale(LC_ALL, "en_US.utf8");
   //cout<<"line="<<line<<endl;
   //cout<<"line.lenght()="<<line.length()<<endl;
   int n0=0;
   //cout<<"n0="<<n0<<" "<<line[n0]<<endl;
   int i=0;
   while(!isdigit(line[i+n0]) && line[i+n0]!='\n' && i+n0<line.length() && line[i+n0]!='-'){
        //cout<<"l1="<<line[i+n0]<<endl;
        i++;
   }
   //cout<<"i="<<i<<endl;
   n0+=i;
   i=0;
   while(isdigit(line[i+n0]) || line[i+n0]=='.' || line[i+n0]=='-'){
      //cout<<line[i+n0]<<endl;
      i++;
   }
   //cout<<"i="<<i<<endl;
   string p;
   p=line.substr(n0,i);
    //cout<<p<<endl;
   return(atof(p.c_str()));
}



void f_extract_params(string s, vector<string> &head, vector<T> &x){
	//head.clear();
	//x.clear();
	int n;
	while(((n=s.find("=")))!=string::npos){
      //cout<<"s="<<s<<endl;
	  //cout<<"n="<<n<<endl;
	  string ht=s.substr(0,n);
	  ht.erase(remove_if(ht.begin(),ht.end(),::isspace),ht.end());
	  T xt=f_get_db_and_erase2(s,"=");
	  //cout<<"ht="<<ht<<endl;
	  //cout<<"xt="<<xt<<endl;
	  //s.erase(0,n);
	  x.push_back(xt);
	  head.push_back(ht);
	
	}
	
}

void f_ad_slash(string &s){
      if(s[s.length()-1]!='/'){
	 s+="/";
      }
}
void f_erase_slash(string &s){
      if(s[s.length()-1]=='/'){
	 s.erase(s.end());
      }
}

void f_print_time(T t){
   //cout<<"time="<<(t)<<" second"<<endl;
   if(t<60){
     cout<<t<<"s";//<<endl; 
   }
   if(t>=60 && t<60*60){
      int tm=t/60;
      T ts=t-tm*60;
      cout<<tm<<"m "<<ts<<"s";//<<endl;
   }
   if(t>=60*60 && t<60*60*24){
      int th=t/(60*60);
      int tm=t-th*(60*60);
      tm/=60;
      T ts=t-th*(60*60)-tm*60;
      cout<<th<<"h "<<tm<<"m "<<ts<<"s";//<<endl;
   }
   if(t>=60*60*24){
      int td=t/(60*60*24);
      int th=t-td*(60*60*24);
      th/=(60*60);
      int tm=t-td*(60*60*24)-th*(60*60);
      tm/=60;
      T ts=t-td*(60*60*24)-th*(60*60)-tm*60;
      cout<<td<<"d "<<th<<"h "<<tm<<"m "<<ts<<"s";//<< endl;
   }
   
}



string f_time(T t){
   ostringstream out;
   //cout<<"time="<<(t)<<" second"<<endl;
   if(t<60){
     out<<t<<"s";//<<endl; 
   }
   if(t>=60 && t<60*60){
      int tm=t/60;
      T ts=t-tm*60;
      out<<tm<<"m "<<ts<<"s";//<<endl;
   }
   if(t>=60*60 && t<60*60*24){
      int th=t/(60*60);
      int tm=t-th*(60*60);
      tm/=60;
      T ts=t-th*(60*60)-tm*60;
      out<<th<<"h "<<tm<<"m "<<ts<<"s";//<<endl;
   }
   if(t>=60*60*24){
      int td=t/(60*60*24);
      int th=t-td*(60*60*24);
      th/=(60*60);
      int tm=t-td*(60*60*24)-th*(60*60);
      tm/=60;
      T ts=t-td*(60*60*24)-th*(60*60)-tm*60;
      out<<td<<"d "<<th<<"h "<<tm<<"m "<<ts<<"s";//<< endl;
   }
   return(out.str());
}


string f_add_ext(string fname,string ext){
    /*
	int i=0;
	if(((i=fname.find_last_of(".")))!=string::npos){
		if(i>0){
	      fname=fname.substr(0,i);  
		}
    } 
    */
    fname+=ext;
	return(fname);
	
}

string f_remove_ext(string fname){
    int i=0;
	if(((i=fname.find_last_of(".")))!=string::npos){
		if(i>0){
	      fname=fname.substr(0,i);  
		}
    }
	return(fname);
}



//**** find ****

int f_find_ind(vector<T> &x,T v){
	if(v<x.front())return(-1);
	if(v>x.back())return(-2);
	int ind=0;
	for(vector<T>::iterator it=x.begin();it<x.end()-1;++it,++ind){
	   if(*it<=v && *(it+1)>=v){
		    return(ind);	
	   }
	}
	return(-1);
}

int f_find_ind2(vector<T> &x,T v){
	if(v<x.front())return(-1);
	if(v>x.back())return(-2);
	int ind=0;
	for( vector<T>::iterator it=x.begin(),ite=x.end();it<x.end()-1;++it,++ind,--ite){
	   if(*it<=v && *(it+1)>=v){
		    return(ind);	
	   }
	   if(*(ite-2)<=v && *(ite-1)>=v){
		    return(ind);	
	   }
	}
	return(-1);
}


int f_find_ind2(vector<T>::iterator it0,vector<T>::iterator ite,T v){
	if(v<*it0)return(-1);
	if(v>*(ite-1))return(-2);
	int ind=0;
	int ind2=distance(it0,ite)-1;
	for( vector<T>::iterator it=it0;it<ite;++it,++ind,--ite,--ind2){
	   if(*it<=v && *(it+1)>=v){
		    return(ind);	
	   }
	   if(*(ite-2)<=v && *(ite-1)>=v){
		    return(ind2);	
	   }
	}
	return(-1);
}

int f_find_ind_s_root(int &i0,int &im,int &ie,vector<T> &x,T &v){
	if( ie-i0 <2 ){
	  return(i0);	
	}
	if(x[im]>v){
	   ie=im;
	   im=(i0+im)/2;
	   f_find_ind_s_root(i0,im,ie,x,v);	
	}else{
	   i0=im;
	   im=(im+ie)/2;
	   f_find_ind_s_root(i0,im,ie,x,v);		   
	}
	return(i0);
}
	

int f_find_ind_s(vector<T> &x,T v){
	if(v<x.front())return(-1);
	if(v>x.back())return(-2);
	int i0=0;
	int ie=x.size()-1;
	int im=ie/2;
	int ind=f_find_ind_s_root(i0,im,ie,x,v);
	return(ind);
}


int f_find_ind_s_root(int &i0,int &im,int &ie, vector<T>::iterator it0, vector<T>::iterator ite,T &v){
	if( ie-i0 <2 ){
	  return(i0);
	}
	if(*(it0+im)>v){
	   ie=im;
	   im=(i0+im)/2;
	   f_find_ind_s_root(i0,im,ie,it0,ite,v);	
	}else{
	   i0=im;
	   im=(im+ie)/2;
	   f_find_ind_s_root(i0,im,ie,it0,ite,v);		   
	}
	return(i0);
}
	

int f_find_ind_s( vector<T>::iterator it0, vector<T>::iterator ite,T v){
	if(v<*it0)return(-1);
	if(v>*(ite-1))return(-2);
    if(v==*it0){return(0);}

	int i0=0;
	int ie=distance(it0,ite)-1;
	int im=ie/2;
	int ind=f_find_ind_s_root(i0,im,ie,it0,ite,v);
	return(ind);
}


int f_find_ind_s_root_s(int &i0,int &im,int &ie,vector<vector<T> > &x,int col,T &v){
	if( ie-i0 <2 ){
	  return(i0);	
	}
	if(x[im][col]>=v){
	   ie=im;
	   im=(i0+im)/2;
	   f_find_ind_s_root_s(i0,im,ie,x,col,v);	
	}else{
	   i0=im;
	   im=(im+ie)/2;
	   f_find_ind_s_root_s(i0,im,ie,x,col,v);		   
	}
	return(i0);
}
	

int f_find_ind_ss(vector<vector<T> > &x,int col,T v){
	if(v<x.front()[col])return(-1);
	if(v>x.back()[col])return(-2);
	int i0=0;
	int ie=x.size()-1;
	int im=ie/2;
	int ind=f_find_ind_s_root_s(i0,im,ie,x,col,v);
	return(ind);
}



int f_find_ind_ss(vector<vector<T> > &x,int i0,int col,T v){
	if(v<x[i0][col])return(-1);
	if(v>x.back()[col])return(-2);
	int ie=x.size()-1;
	int im=(ie-i0)/2;
    if(v==x[i0][col]){
       return(0);   
    }
	int ind=f_find_ind_s_root_s(i0,im,ie,x,col,v);
    //if(x.size()>ind+1){
    //   if(x[ind+1][col]==v)++ind;   
   // }
	return(ind);
}

int f_find_ind_s_root_l(int &i0,int &im,int &ie,vector<vector<T> > &x,int col,T &v){
	if( ie-i0 <2 ){
	  return(i0);	
	}
	if(x[im][col]>v){
	   ie=im;
	   im=(i0+im)/2;
	   f_find_ind_s_root_l(i0,im,ie,x,col,v);	
	}else{
	   i0=im;
	   im=(im+ie)/2;
	   f_find_ind_s_root_l(i0,im,ie,x,col,v);		   
	}
	return(i0);
}
	

int f_find_ind_sl(vector<vector<T> > &x,int col,T v){
	if(v<x.front()[col])return(-1);
	if(v>x.back()[col])return(-2);
	int i0=0;
	int ie=x.size()-1;
	int im=ie/2;
	int ind=f_find_ind_s_root_l(i0,im,ie,x,col,v);
	return(ind);
}


int f_find_ind_sl(vector<vector<T> > &x,int i0,int col,T v){
	if(v<x[i0][col])return(-1);
	if(v>x.back()[col])return(-2);
	int ie=x.size()-1;
	int im=(ie-i0)/2;
    if(v==x[i0][col]){
       return(0);   
    }
	int ind=f_find_ind_s_root_l(i0,im,ie,x,col,v);
    //if(x.size()>ind+1){
    //   if(x[ind+1][col]==v)++ind;   
   // }
	return(ind);
}






bool present(vector<string> &v, string x){
	bool r=false;
	for(size_t i=0;i<v.size();++i){
        //cout<<"v="<<v[i]<<" x="<<x<<" "<<v[i]-x<<endl;
		if(v[i]==x){
		  r=true;
          //cout<<"r="<<r<<endl;
		  break;
		}
	}
	return(r);
}
bool present(vector<int> &v, int x){
	bool r=false;
	for(size_t i=0;i<v.size();++i){
        //cout<<"v="<<v[i]<<" x="<<x<<" "<<v[i]-x<<endl;
		if(v[i]==x){
		  r=true;
          //cout<<"r="<<r<<endl;
		  break;
		}
	}
	return(r);
}

#ifndef argv_conf_pw
#define argv_conf_pw

//c++ argv.cpp -o argv

#include <stdlib.h>
#include <iostream>
#include <string>
#include <string.h>
#include <math.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <algorithm>    // std::remove_if

using namespace std;




//**** cl_argv ****

class cl_argv{
private:
      //define field separator; '-' is a standard value but when set you can not type the negative numbers
      static const char argv_sep='-'; 
      //static const char argv_sep='\\';
      //static const char argv_sep='+';
      void argv_def_arg_add(string pattern);
      string argv_to_string(char c);
public:
      int argc;
      char **argv;
      string help;
      vector<string> def_arg;
      cl_argv(){
	 help="  "+argv_to_string(argv_sep)+"h or "+argv_to_string(argv_sep)+argv_to_string(argv_sep)+"help this info \n";
	 def_arg.push_back("h");
	 def_arg.push_back(argv_to_string(argv_sep)+"help");
      }
      void f_cout();
      int argv_int_pattern_isonly_no(string pattern,int pat_default_isonly,int pat_default_no); 
      int argv_int_pattern_isonly_no(string pattern,string pat_default_isonly,string pat_default_no); 
      double argv_db_pattern_isonly_no(string pattern,double pat_default_isonly,double pat_default_no);
      double argv_db_pattern_isonly_no(string pattern,string pat_default_isonly,string pat_default_no);
      string argv_str_pattern_isonly_no(string pattern,string pat_default_isonly,string pat_default_no);
      vector<string> argv_str_v_pattern_isonly_no(string pattern,string pat_default_isonly,string pat_default_no);
      vector<int>  argv_int_v_pattern_isonly_no(string pattern,string pat_default_isonly,string pat_default_no);
      vector<double> argv_db_v_pattern_isonly_no(string pattern,string pat_default_isonly,string pat_default_no);
      bool argv_bool(string pattern);
      void argv_help_add(string c);   
      bool argv_help();
      bool is_help();
      //void argv_search_for_undefined_arguments();
      bool argv_search_for_undefined_arguments();
      vector<string> argv_extract_st_v(string &line);
};
//*** argv def ***
vector<string> cl_argv:: argv_extract_st_v(string &line){
  vector<string> v;
  //cout<<" ll="<<line<<"uu"<<endl;
  //erase multispaces
  //line.erase(unique(line.begin(), line.end(), BothAre<' '>),line.end());   
  //if(line.find("a")!=string::npos){
  //   line.erase(line.find("a"),2);
  //}
  //while(isspace(line[0])){line.erase(line.begin());}//erase white spaces at the bigining af the string
  int i=0;while(isspace(line[i])){i++;}if(i>0)line.erase(line.begin(),line.begin()+i);//erase white spaces at the bigining af the string(version more efficient)
  while(isspace(line[line.length()-1]) || line[line.length()-1]=='\n'){line.erase(line.end()-1);}//erase white spaces and new line sign at the end af the string

  //cout<<" ll="<<line<<endl;
  istringstream c;
  c.str(line);
  string x;
  while(!c.eof()){
  	c>>x;
	v.push_back(x);
	//cout<<v.back()<<endl;
  }
  return(v);
}
string cl_argv:: argv_to_string(char c){
     ostringstream o;
     o<<c;
     return(o.str());
}
void cl_argv:: argv_help_add(string c){
     help+=c+"\n";
}
void cl_argv:: f_cout(){
    for(int i=0;i<argc;i++){
       cout<<argv[i]<<endl;
    }
}
bool cl_argv:: argv_search_for_undefined_arguments(){
    //cout<<"def_arg="<<def_arg<<endl;
    bool ok=true;
    for(int i=1;i<argc;i++){
       bool isnot=true;
       for(size_t j=0;j<def_arg.size();j++){
	  //cout<<"def_arg="<<argv_to_string(argv_sep)+def_arg[j]<<" argv[i]="<<argv[i]<<endl;
	  if(argv_to_string(argv_sep)+def_arg[j]==argv[i] || argv[i][0]!=argv_sep){
	    isnot=false;
	    break;
	  }
       }
       if(isnot){
	    cout<<"  !! undefined command line option: "<<argv[i]<<endl;
	    ok=false;
       }
    }
    return(ok);
}
void cl_argv:: argv_def_arg_add(string pattern){
   def_arg.push_back(pattern);  
}
bool cl_argv:: argv_help(){
   //cout<<"help="<<help<<endl;
   argv_def_arg_add("h");
   argv_def_arg_add(argv_to_string(argv_sep)+"help");
   bool var=false;
   string pat1=argv_to_string(argv_sep)+"h";
   string pat2=argv_to_string(argv_sep)+argv_to_string(argv_sep)+"help";
   //cout<<"sep="<<argv_sep+"h"<<" "<<pat1<<endl;
   for(int i=1;i<argc;i++){
     //cout<<"help i="<<i<<" argc="<<argc<<" argv[i]="<<argv[i]<<" pat1="<<pat1<<endl;
     if(argv[i]==pat1 || argv[i]==pat2){
        var=true;
        cout<<help<<endl;
        break;
     }
   }
   return(var);
}
bool cl_argv:: is_help(){
   //cout<<"help="<<help<<endl;
   argv_def_arg_add("h");
   argv_def_arg_add(argv_to_string(argv_sep)+"help");
   bool var=false;
   string pat1=argv_to_string(argv_sep)+"h";
   string pat2=argv_to_string(argv_sep)+argv_to_string(argv_sep)+"help";
   //cout<<"sep="<<argv_sep+"h"<<" "<<pat1<<endl;
   for(int i=1;i<argc;i++){
     //cout<<"help i="<<i<<" argc="<<argc<<" argv[i]="<<argv[i]<<" pat1="<<pat1<<endl;
     if(argv[i]==pat1 || argv[i]==pat2){
        var=true;
        break;
     }
   }
   return(var);
}
bool cl_argv:: argv_bool(string pattern){
   argv_def_arg_add(pattern);
   bool var=false;
   for(int i=1;i<argc;i++){
     //cout<<"help i="<<i<<" argc="<<argc<<" argv[i]="<<argv[i]<<endl;
     if(argv[i]==argv_sep+pattern){
        var=true;
        break;
     }
   }
   return(var);
}
string cl_argv:: argv_str_pattern_isonly_no(string pattern,string pat_default_isonly,string pat_default_no){
   argv_def_arg_add(pattern);
   string var=pat_default_no;
   for(int i=1;i<argc;i++){
     //cout<<"i="<<i<<" argc="<<argc<<"argv[i]="<<argv[i]<<endl;
     if(argv[i]==argv_sep+pattern){
       bool defa=true;
       if(argc>i+1){
	     if(argv[i+1][0]!=argv_sep){
	        var=(argv[i+1]);
	        defa=false;
	        break;
	     } 
       }
       if(defa){
         var=pat_default_isonly;      
       }
     }  
   }
   return(var);
}
int cl_argv:: argv_int_pattern_isonly_no(string pattern,int pat_default_isonly,int pat_default_no){
   setlocale(LC_ALL, "en_US.utf8");
   argv_def_arg_add(pattern);
   double var=pat_default_no;
   for(int i=1;i<argc;i++){
     //cout<<"i="<<i<<" argc="<<argc<<"argv[i]="<<argv[i]<<endl;
     if(argv[i]==argv_sep+pattern){
       bool defa=true;
       if(argc>i+1){
	     if(argv[i+1][0]!=argv_sep){
	        var=atof(argv[i+1]);
	        defa=false;
	        break;
	     } 
       }
       if(defa){
         var=pat_default_isonly;      
       }
     }  
   }
   return(round(var));
}
int cl_argv:: argv_int_pattern_isonly_no(string pattern,string pat_default_isonly,string pat_default_no){
   setlocale(LC_ALL, "en_US.utf8");
   argv_def_arg_add(pattern);
   double var=atof(pat_default_no.c_str());
   double sign=1.0;
   for(int i=1;i<argc;i++){
     //cout<<"i="<<i<<" argc="<<argc<<"argv[i]="<<argv[i]<<endl;
     if(argv[i]==argv_sep+pattern){
       bool defa=true;
       if(argc>i+1){
	     if(argv[i+1][0]!=argv_sep){
			if(strlen(argv[i+1])>0){  
			  if(argv[i+1][0]=='m'){
				sign=-1.0;
				memmove(argv[i+1], argv[i+1]+1, strlen(argv[i+1]));
			  }
	          var=atof(argv[i+1])*sign;
	          defa=false;
			  break;
	        } 
	     } 
       }
       if(defa){
         var=atof(pat_default_isonly.c_str());      
       }
     }  
   }
   return(round(var));
}
double cl_argv:: argv_db_pattern_isonly_no(string pattern,double pat_default_isonly,double pat_default_no){
   setlocale(LC_ALL, "en_US.utf8");
   argv_def_arg_add(pattern);
   double var=pat_default_no;
   for(int i=1;i<argc;i++){
     //cout<<"i="<<i<<" argc="<<argc<<"argv[i]="<<argv[i]<<endl;
     if(argv[i]==argv_sep+pattern){
        bool defa=true;
        if(argc>i+1){
	     if(argv[i+1][0]!=argv_sep){
	        var=atof(argv[i+1]);
	        defa=false;
	        break;
		 } 
        }
        if(defa){
           var=pat_default_isonly;      
        }
     }  
   }
   return(var);
}
double cl_argv:: argv_db_pattern_isonly_no(string pattern,string pat_default_isonly,string pat_default_no){
   setlocale(LC_ALL, "en_US.utf8");
   argv_def_arg_add(pattern);
   double var=atof(pat_default_no.c_str());
   double sign=1.0;
   for(int i=1;i<argc;i++){
     //cout<<"i="<<i<<" argc="<<argc<<"argv[i]="<<argv[i]<<endl;
     if(argv[i]==argv_sep+pattern){
        bool defa=true;
        if(argc>i+1){
		  if(argv[i+1][0]!=argv_sep){
			if(strlen(argv[i+1])>0){  
			  if(argv[i+1][0]=='m'){
				sign=-1.0;
				memmove(argv[i+1], argv[i+1]+1, strlen(argv[i+1]));
			  }
	          var=atof(argv[i+1])*sign;
	          defa=false;
			  break;
	        } 
		  }
        }
        if(defa){
           var=atof(pat_default_isonly.c_str());      
        }
     }  
   }
   return(var);
}
vector<string> cl_argv:: argv_str_v_pattern_isonly_no(string pattern,string pat_default_isonly,string pat_default_no){
   argv_def_arg_add(pattern);
   vector<string> file;
   bool defa2=true;
   for(int i=1;i<argc;i++){
     //cout<<"i="<<i<<" argc="<<argc<<endl;
     if(argv[i]==argv_sep+pattern){
       //cout<<argv[i]<<endl;
       bool defa=true;
       defa2=false;
       int j;
       for(j=i+1;j<argc;j++){
	     if(argv[j][0]!=argv_sep){
	       file.push_back(argv[j]); 
	       defa=false;
	     }else{
	       break;
	     }
       }
       if(defa && (pat_default_isonly!="")){
	   vector<string> vstr=argv_extract_st_v(pat_default_isonly);
           for(size_t j=0;j<vstr.size();j++){
                file.push_back(vstr[j]);
	   }
       }
       //cout<<"j="<<j<<endl;
       i=j;
     }
   }
   if(defa2 && (pat_default_no!="")){
           vector<string> vstr=argv_extract_st_v(pat_default_no);
           for(size_t j=0;j<vstr.size();j++){
                    file.push_back(vstr[j]);
           }
   }  
   return(file);
}
vector<int> cl_argv:: argv_int_v_pattern_isonly_no(string pattern,string pat_default_isonly,string pat_default_no){
   setlocale(LC_ALL, "en_US.utf8");
   argv_def_arg_add(pattern);
   vector<int> file;
   double sign=1.0;
   bool defa2=true;
   for(int i=1;i<argc;i++){
     //cout<<"i="<<i<<" argc="<<argc<<endl;
     if(argv[i]==argv_sep+pattern){
       //cout<<argv[i]<<endl;
       bool defa=true;
       defa2=false;
       int j;
       for(j=i+1;j<argc;j++){
	     if(argv[j][0]!=argv_sep){
			 if(strlen(argv[j])>0){  
			    if(argv[j][0]=='m'){
				   sign=-1.0;
				   memmove(argv[j], argv[j]+1, strlen(argv[j]));
			    }
	            file.push_back(round(atof(argv[j])*sign));
				sign=1.0;
				defa=false;
	         } 
	     }else{
	       break;
	     }
       }
       if(defa && (pat_default_isonly!="")){
	      vector<string> vstr=argv_extract_st_v(pat_default_isonly);
              for(size_t j=0;j<vstr.size();j++){
                file.push_back(round(atof(vstr[j].c_str())));
	      }
       }
       i=j;
     }
   }
   if(defa2 && (pat_default_no!="")){
           vector<string> vstr=argv_extract_st_v(pat_default_no);
           for(size_t j=0;j<vstr.size();j++){
                    file.push_back(round(atof(vstr[j].c_str())));
           }
   }  
   return(file);
}
vector<double> cl_argv:: argv_db_v_pattern_isonly_no(string pattern,string pat_default_isonly,string pat_default_no){
   setlocale(LC_ALL, "en_US.utf8");
   argv_def_arg_add(pattern);
   vector<double> file;
   double sign=1.0;
   bool defa2=true;
   for(int i=1;i<argc;i++){
     //cout<<"i="<<i<<" argc="<<argc<<endl;
     if(argv[i]==argv_sep+pattern){
       //cout<<argv[i]<<endl;
       bool defa=true;
       defa2=false;
       int j;
       for(j=i+1;j<argc;j++){
	     if(argv[j][0]!=argv_sep){
			 if(strlen(argv[j])>0){  
			    if(argv[j][0]=='m'){
				   sign=-1.0;
				   memmove(argv[j], argv[j]+1, strlen(argv[j]));
			    }
	            file.push_back(atof(argv[j])*sign);
				sign=1.0;
				defa=false;
	         } 
	     }else{
	       break;
	     }
       }
       if(defa && (pat_default_isonly!="")){
           vector<string> vstr=argv_extract_st_v(pat_default_isonly);
           for(size_t j=0;j<vstr.size();j++){
                file.push_back(atof(vstr[j].c_str()));
	   }
       }
       i=j;
     }
   }
   if(defa2 && (pat_default_no!="")){
       vector<string> vstr=argv_extract_st_v(pat_default_no);
       for(size_t j=0;j<vstr.size();j++){
                file.push_back(atof(vstr[j].c_str()));
       }
   }  
   return(file);
}
//** argv def **

//**** cl_conf ****
vector<string> f_conf_extract_str_v(string line){
  vector<string> v;
  //erase multispaces
  //line.erase(unique(line.begin(), line.end(), BothAre<' '>),line.end());   
  //if(line.find("a")!=string::npos){
  //   line.erase(line.find("a"),2);
  //}
  //while(isspace(line[0])){line.erase(line.begin());}//erase white spaces at the bigining af the string
  int i=0;while(isspace(line[i])){i++;}if(i>0)line.erase(line.begin(),line.begin()+i);//erase white spaces at the bigining af the string(version more efficient)
  if(line.length()>0)while(isspace(line[line.length()-1]) || line[line.length()-1]=='\n'){line.erase(line.end()-1);}//erase white spaces and new line sign at the end af the string
  for(size_t i=0;i<line.length();i++){if(line[i]=='=')line[i]=' ';}
  //cout<<" ll="<<line<<endl;
  istringstream c;
  c.str(line);
  string x;
  while(!c.eof()){
  	c>>x;
	v.push_back(x);
	//cout<<v.back()<<endl;
  }
  return(v);
}

class cl_conf{
  public: 
  string n_conf;//the name of the conf file 
  bool ok(string show="show");
  bool conf_bool(string pattern,string show="show");
  int conf_int(string pattern,int default_value,string show="show");
  int conf_int(string pattern,string default_value,string show="show");
  double conf_db(string pattern,double default_value,string show="show");
  double conf_db(string pattern,string default_value,string show="show");
  string conf_str(string pattern,string default_value,string show="show");
  vector<int> conf_int_v(string pattern,string default_value,string show="show");
  vector<double> conf_db_v(string pattern,string default_value,string show="show");
  vector<string> conf_str_v(string pattern,string default_value,string show="show");
};
bool cl_conf::ok(string show){
  ifstream f_conf; 
  f_conf.open(n_conf.c_str());
  if(!f_conf.good()){
    if(show=="show")cout<<"Missing file: "<< n_conf<<endl;   
    return(false);
  }else{
    return(true);
  }
}
bool cl_conf::conf_bool(string pattern,string show){
  ifstream f_conf;
  bool cc=false;
  string line,p;
  f_conf.open(n_conf.c_str());
  if( f_conf.good() != true ){
    if(show=="show")cout<<"Missing file: "<< n_conf<<endl;   
  }else{
    while(getline(f_conf,line)){
      string line2=line;
      line2.erase(remove_if(line2.begin(),line2.end(),::isspace),line2.end());//erase white spaces
      if(line2.length()>0){
	vector<string>vec=f_conf_extract_str_v(line);
        for(size_t i=0;i<vec.size();i++){
          if((vec[i]==pattern)&&(line.find(";")==string::npos)&&((line.find("%"))==string::npos)&&((line.find("!"))==string::npos)){
            cc=true;
	  }
	}
      }
    }
  }
  return(cc);
}
double cl_conf::conf_db(string pattern,double default_value,string show){
  setlocale(LC_ALL, "en_US.utf8");
  ifstream f_conf;
  string line,p;
  f_conf.open(n_conf.c_str());
  double cc=default_value;
  if( f_conf.good() != true ){
    if(show=="show")cout<<"Missing file: "<< n_conf<<endl;   
  }else{
    while(getline(f_conf,line)){
      if(line.length()>0){
        vector<string>vec=f_conf_extract_str_v(line);
        for(size_t i=0;i<vec.size();i++){
          if((vec[i]==pattern)&&(line.find(";")==string::npos)&&((line.find("%"))==string::npos)&&((line.find("!"))==string::npos)){
            p=line.substr(line.find("=")+1,line.length()-(line.find("=")+1));
	    if(p.size()!=0){cc=atof(p.c_str());}
           //cout<<"Vrot_split="<<Vrot_split<<endl;   
	  }
	}
      }
    }
  }
  return(cc);
}
double cl_conf::conf_db(string pattern,string default_value,string show){
  setlocale(LC_ALL, "en_US.utf8");
  ifstream f_conf;
  string line,p;
  f_conf.open(n_conf.c_str());
  double cc=atof(default_value.c_str());
  if( f_conf.good() != true ){
    if(show=="show")cout<<"Missing file: "<< n_conf<<endl;   
  }else{
    while(getline(f_conf,line)){
      if(line.length()>0){
        vector<string>vec=f_conf_extract_str_v(line);
        for(size_t i=0;i<vec.size();i++){
           if((vec[i]==pattern)&&(line.find(";")==string::npos)&&((line.find("%"))==string::npos)&&((line.find("!"))==string::npos)){
             p=line.substr(line.find("=")+1,line.length()-(line.find("=")+1));
	         if(p.size()!=0){cc=atof(p.c_str());}
             //cout<<"Vrot_split="<<Vrot_split<<endl;   
	       } 
	    }
      }
    }
  }
  return(cc);
}
int cl_conf::conf_int(string pattern,int default_value,string show){
  setlocale(LC_ALL, "en_US.utf8");
  ifstream f_conf;
  string line,p;
  f_conf.open(n_conf.c_str());
  int cc=default_value;
  if( f_conf.good() != true ){
    if(show=="show")cout<<"Missing file: "<< n_conf<<endl;
  }else{
    while(getline(f_conf,line)){
      if(line.length()>0){
        vector<string>vec=f_conf_extract_str_v(line);
        for(size_t i=0;i<vec.size();i++){
          if((vec[i]==pattern)&&(line.find(";")==string::npos)&&((line.find("%"))==string::npos)&&((line.find("!"))==string::npos)){
            p=line.substr(line.find("=")+1,line.length()-(line.find("=")+1));
	    if(p.size()!=0){cc=round(atof(p.c_str()));}
            //cout<<"p="<<p<<endl;   
	  }
	}
      }
    }
  }
  return(cc);
}
int cl_conf::conf_int(string pattern,string default_value,string show){
  setlocale(LC_ALL, "en_US.utf8");
  ifstream f_conf;
  string line,p;
  f_conf.open(n_conf.c_str());
  double cc=atof(default_value.c_str());
  if( f_conf.good() != true ){
    if(show=="show")cout<<"Missing file: "<< n_conf<<endl;   
  }else{
    while(getline(f_conf,line)){
      if(line.length()>0){
        vector<string>vec=f_conf_extract_str_v(line);
        for(size_t i=0;i<vec.size();i++){
           if((vec[i]==pattern)&&(line.find(";")==string::npos)&&((line.find("%"))==string::npos)&&((line.find("!"))==string::npos)){
             p=line.substr(line.find("=")+1,line.length()-(line.find("=")+1));
	         if(p.size()!=0){cc=atof(p.c_str());}
             //cout<<"Vrot_split="<<Vrot_split<<endl;   
	       } 
	    }
      }
    }
  }
  return(round(cc));
}
string cl_conf::conf_str(string pattern,string default_value,string show){
  ifstream f_conf;
  string line,p,cc=default_value;
  f_conf.open(n_conf.c_str());
  if( f_conf.good() != true ){
    if(show=="show")cout<<"Missing file: "<< n_conf<<endl;   
  }else {
    while(getline(f_conf,line)){
      if(line.length()>0){
	//cout<<line<<endl;
        vector<string>vec=f_conf_extract_str_v(line);
	//cout<<"vec="<<vec[0]<<endl;
        for(size_t i=0;i<vec.size();i++){
	  //cout<<"line="<<vec[i]<<" pattern="<<pattern<<endl;
          if((vec[i]==pattern)&&(line.find(";")==string::npos)&&((line.find("%"))==string::npos)&&((line.find("!"))==string::npos)){
	    //cout<<"line="<<line<<" pattern="<<pattern<<endl;
            p=line.substr(line.find("=")+1,line.length()-(line.find("=")+1));
	    if(p.size()!=0){cc=p;}
	    //cout<<"p="<<p<<endl;  
  	  }
        }
      }
    }
  }
  return(cc); 
}
vector<int> cl_conf::conf_int_v(string pattern,string default_value,string show){
  setlocale(LC_ALL, "en_US.utf8");
  ifstream f_conf;
  string line,p;
  f_conf.open(n_conf.c_str());
  vector<int> cc;
  if( f_conf.good() != true ){
    if(show=="show")cout<<"Missing file: "<< n_conf<<endl;  
    while(getline(f_conf,line)){
      if(line.length()>0){
        vector<string>vec=f_conf_extract_str_v(line);
        for(size_t i=0;i<vec.size();i++){
          if((vec[i]==pattern)&&(line.find(";")==string::npos)&&((line.find("%"))==string::npos)&&((line.find("!"))==string::npos)){
            cc.clear();
            p=line.substr(line.find("[")+1,line.rfind("]")-(line.find("[")+1));
	        int wpsl=0;
                for(size_t i=0;i<p.length();i++){
	           if(isspace(p[i]))wpsl++; 
	        }
	        if(wpsl!=p.length() && p.length()>0){
               while(p.find(",")!=string::npos){
                  cc.push_back(round(atof(p.substr(0,p.find(",")).c_str())));
                  p=p.substr(p.find(",")+1,p.length()-(p.find(","))-1);        
               }
               cc.push_back(round(atof(p.c_str())));
	        }
	      }
	    }
      }
    }
  }
  if(default_value!="" && cc.size()==0)cc.push_back(round(atof(default_value.c_str())));
  return(cc);
}
vector<double> cl_conf::conf_db_v(string pattern,string default_value,string show){
  setlocale(LC_ALL, "en_US.utf8");
  ifstream f_conf;
  string line,p;
  f_conf.open(n_conf.c_str());
  vector<double> cc;
  if( f_conf.good() != true ){
    if(show=="show")cout<<"Missing file: "<< n_conf<<endl;
  }else{
    while(getline(f_conf,line)){
      if(line.length()>0){
        vector<string>vec=f_conf_extract_str_v(line);
        for(size_t i=0;i<vec.size();i++){
          if((vec[i]==pattern)&&(line.find(";")==string::npos)&&((line.find("%"))==string::npos)&&((line.find("!"))==string::npos)){
	    cc.clear();
            p=line.substr(line.find("[")+1,line.rfind("]")-(line.find("[")+1));
	    int wpsl=0;
            for(size_t i=0;i<p.length();i++){
	       if(isspace(p[i]))wpsl++; 
	    }
	    if(wpsl!=p.length() && p.length()>0){
              while(p.find(",")!=string::npos){
                cc.push_back((atof(p.substr(0,p.find(",")).c_str())));
                p=p.substr(p.find(",")+1,p.length()-(p.find(","))-1);        
              }
              cc.push_back((atof(p.c_str())));   
	    }
	  }
        }
      }
    }
  }
  if(default_value!="" && cc.size()==0)cc.push_back(atof(default_value.c_str()));
  return(cc);
} 
vector<string> cl_conf::conf_str_v(string pattern,string default_value,string show){
  ifstream f_conf;
  string line,p;
  f_conf.open(n_conf.c_str());
  vector<string> cc;
  if( f_conf.good() != true ){
      if(show=="show")cout<<"Missing file: "<< n_conf<<endl;    
  }else{
    while(getline(f_conf,line)){
      if(line.length()>0){
        vector<string>vec=f_conf_extract_str_v(line);
        for(size_t i=0;i<vec.size();i++){
          if((vec[i]==pattern)&&(line.find(";")==string::npos)&&((line.find("%"))==string::npos)&&((line.find("!"))==string::npos)){
            cc.clear();
            p=line.substr(line.find("[")+1,line.rfind("]")-(line.find("[")+1));
	    int wpsl=0;
            for(size_t i=0;i<p.length();i++){
	       if(isspace(p[i]))wpsl++; 
	    }
	    if(wpsl!=p.length() && p.length()>0){
               while(p.find(",")!=string::npos){
                  cc.push_back(p.substr(0,p.find(",")));
                  p=p.substr(p.find(",")+1,p.length()-(p.find(","))-1);        
               }
               //cout<<"p="<<p<<endl;  
               cc.push_back(p);
	    }
	  }
	}
      }
    }
  }
  if(default_value!="" && cc.size()==0)cc.push_back(default_value);
  f_conf.close();
  return(cc);
}
//**cl_conf**



class cl_argv_conf{
public:
  cl_argv &argv_cl;
  cl_conf &conf;
  bool ac_bool(string pattern);
  string ac_str_pattern_isonly_no(string pattern,string pat_default_isonly,string pat_default_no);
  int ac_int_pattern_isonly_no(string pattern,int pat_default_isonly,int pat_default_no);
  int ac_int_pattern_isonly_no(string pattern,string pat_default_isonly,string pat_default_no);
  double ac_db_pattern_isonly_no(string pattern,double pat_default_isonly,double pat_default_no);
  double ac_db_pattern_isonly_no(string pattern,string pat_default_isonly,string pat_default_no);
  vector<string> ac_str_v_pattern_isonly_no(string pattern,string pat_default_isonly,string pat_default_no);
  vector<int> ac_int_v_pattern_isonly_no(string pattern,string pat_default_isonly,string pat_default_no);
  vector<double> ac_db_v_pattern_isonly_no(string pattern,string pat_default_isonly,string pat_default_no);
};

bool cl_argv_conf:: ac_bool(string pattern){
   bool v_ok=argv_cl.argv_bool(pattern);
   bool conf_v_ok=conf.conf_bool(pattern,"noshow");
   if(!v_ok && conf_v_ok){
     v_ok=conf_v_ok;
   }
   return(v_ok);
}
string cl_argv_conf:: ac_str_pattern_isonly_no(string pattern,string pat_default_isonly,string pat_default_no){
   bool v_ok=argv_cl.argv_bool(pattern);
   string v=argv_cl.argv_str_pattern_isonly_no(pattern,pat_default_isonly,pat_default_no);
   bool conf_v_ok=conf.conf_bool(pattern,"noshow");
   string conf_v=conf.conf_str(pattern,pat_default_no,"noshow");
   if(!v_ok && conf_v_ok){
     v=conf_v;
     v_ok=conf_v_ok;
   }
   return(v);
}
int cl_argv_conf:: ac_int_pattern_isonly_no(string pattern,int pat_default_isonly,int pat_default_no){
   setlocale(LC_ALL, "en_US.utf8");
   bool v_ok=argv_cl.argv_bool(pattern);
   int v=argv_cl.argv_int_pattern_isonly_no(pattern,pat_default_isonly,pat_default_no);
   bool conf_v_ok=conf.conf_bool(pattern,"noshow");
   int conf_v=conf.conf_int(pattern,pat_default_no,"noshow");
   if(!v_ok && conf_v_ok){
     v=conf_v;
     v_ok=conf_v_ok;
   }
   return(v);
}
int cl_argv_conf:: ac_int_pattern_isonly_no(string pattern,string pat_default_isonly,string pat_default_no){
   setlocale(LC_ALL, "en_US.utf8");
   bool v_ok=argv_cl.argv_bool(pattern);
   int v=argv_cl.argv_int_pattern_isonly_no(pattern,pat_default_isonly,pat_default_no);
   bool conf_v_ok=conf.conf_bool(pattern,"noshow");
   int conf_v=conf.conf_int(pattern,pat_default_no,"noshow");
   if(!v_ok && conf_v_ok){
     v=conf_v;
     v_ok=conf_v_ok;
   }
   return(v);
}
double cl_argv_conf:: ac_db_pattern_isonly_no(string pattern,double pat_default_isonly,double pat_default_no){
   setlocale(LC_ALL, "en_US.utf8");
   bool v_ok=argv_cl.argv_bool(pattern);
   double v=argv_cl.argv_db_pattern_isonly_no(pattern,pat_default_isonly,pat_default_no);
   bool conf_v_ok=conf.conf_bool(pattern,"noshow");
   double conf_v=conf.conf_db(pattern,pat_default_no,"noshow");
   if(!v_ok && conf_v_ok){
     v=conf_v;
     v_ok=conf_v_ok;
   }
   return(v);
}
double cl_argv_conf:: ac_db_pattern_isonly_no(string pattern,string pat_default_isonly,string pat_default_no){
   setlocale(LC_ALL, "en_US.utf8");
   bool v_ok=argv_cl.argv_bool(pattern);
   double v=argv_cl.argv_db_pattern_isonly_no(pattern,pat_default_isonly,pat_default_no);
   bool conf_v_ok=conf.conf_bool(pattern,"noshow");
   double conf_v=conf.conf_db(pattern,pat_default_no,"noshow");
   if(!v_ok && conf_v_ok){
     v=conf_v;
     v_ok=conf_v_ok;
   }
   return(v);
}
vector<string> cl_argv_conf:: ac_str_v_pattern_isonly_no(string pattern,string pat_default_isonly,string pat_default_no){
   bool v_ok=argv_cl.argv_bool(pattern);
   vector<string> v=argv_cl.argv_str_v_pattern_isonly_no(pattern,pat_default_isonly,pat_default_no);
   bool conf_v_ok=conf.conf_bool(pattern,"noshow");
   vector<string> conf_v=conf.conf_str_v(pattern,pat_default_no,"noshow");
   if(!v_ok && conf_v_ok){
     v=conf_v;
     v_ok=conf_v_ok;
   }
   return(v);
}
vector<int> cl_argv_conf:: ac_int_v_pattern_isonly_no(string pattern,string pat_default_isonly,string pat_default_no){
   setlocale(LC_ALL, "en_US.utf8");
   bool v_ok=argv_cl.argv_bool(pattern);
   vector<int> v=argv_cl.argv_int_v_pattern_isonly_no(pattern,pat_default_isonly,pat_default_no);
   bool conf_v_ok=conf.conf_bool(pattern,"noshow");
   vector<int> conf_v=conf.conf_int_v(pattern,pat_default_no,"noshow");
   if(!v_ok && conf_v_ok){
     v=conf_v;
     v_ok=conf_v_ok;
   }
   return(v);
}
vector<double> cl_argv_conf:: ac_db_v_pattern_isonly_no(string pattern,string pat_default_isonly,string pat_default_no){
   setlocale(LC_ALL, "en_US.utf8");
   bool v_ok=argv_cl.argv_bool(pattern);
   vector<double> v=argv_cl.argv_db_v_pattern_isonly_no(pattern,pat_default_isonly,pat_default_no);
   bool conf_v_ok=conf.conf_bool(pattern,"noshow");
   vector<double> conf_v=conf.conf_db_v(pattern,pat_default_no,"noshow");
   if(!v_ok && conf_v_ok){
     v=conf_v;
     v_ok=conf_v_ok;
   }
   return(v);
}

#endif



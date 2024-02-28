

#include "read_file_pwh.hpp"




typedef double T;


string cl_read_file::file_name(){
    return(_fname);   
}

void cl_read_file::help(){
  cout<<endl<<"cl_read_file:"<<endl;
  cout<<"This class can be used to read data from a file."<<endl;
  cout<<"Initialization:"<<endl;
  cout<<"cl_read_file<Type> file;"<<endl;
  cout<<"file.init(string file_name, int nhead, int ihead, string sepparation, bool check=true, bool out=false)"<<endl;
  cout<<"cl_read_file<Type> file{string file_name, int nhead, int ihead, string sepparation, bool check=true, bool out=false)"<<endl;
  cout<<endl;
  cout<<"file.read() - read data and save into internal variables; you can acces them through file(), head() and whead()"<<endl;
  cout<<"file.reads() - read data and save into internal vector<string> variable; you can acces them through files(), head() and whead()"<<endl;
  cout<<"file.help() - this output"<<endl;
  cout<<"bool file.cc() - check whether all columns have the same size"<<endl;
  cout<<"file.ne() - numbers of the empty rows"<<endl;
  cout<<endl;
}

void cl_read_file::info(){
   cout<<"cl_read_file:"<<endl;
   cout<<"file = "<<_fname<<endl;
   cout<<"nr = "<<nr()<<endl;
   if(cc()){
      cout<<"nc = "<<nc().front()<<endl;
   }else{
      cout<<"nc = "<<nc().front()<<endl;
   }
}

bool cl_read_file::cc(){
   if(_read_ok || _reads_ok){
	   bool okc=true;
	   if(_nr>1){
	     for(size_t i=0;i<_nr-1;++i){
		   if(_nc[i]!=_nc[i+1]){
		 	 okc=false;
		 	 cout<<"nc["<<i<<"] = "<<_nc[i]<<" nc["<<i+1<<"] = "<<_nc[i+1]<<endl;
		   }
	     }
	   }
	   return(okc);
   }else{
	  f_alert("cl_read_file: cc() problem, use read() first");   
	  return(false);
   }
}

void cl_read_file::free(){
   	_head.clear();
	_file.clear();
	_whead.clear();
}

ostream & operator<< (ostream &ret, cl_read_file &rf){
   for(size_t i=0;i<rf.whead().size();i++){
      ret<<rf.whead()[i]<<endl;
   }	
   for(size_t i=0;i<rf.head().size();i++){
      ret<<rf.head()[i]<<" ";
   }
   if(rf.whead().size()>0 || rf.head().size()>0)ret<<endl;
   if(rf.read_ok()){
     for(size_t i=0;i<rf.file().size();i++){
       for(size_t j=0;j<rf.file()[i].size();j++){
          ret<<rf.file()[i][j]<<" ";
	   }
	   ret<<endl;
     }
   }
   if(rf.reads_ok()){
	   //cout<<"sasas"<<endl;
     for(size_t i=0;i<rf.files().size()-1;i++){
          ret<<rf.files()[i]<<endl;
     }
     if(rf.files().size()>0)ret<<rf.files().back();
   }
   //ret<<endl;
   //for(size_t i=0;i<rf.nc().size();i++){
   //   ret<<rf.nc()[i]<<" ";//<<endl;
   //}
   //ret<<ret2.str();
   return(ret);
}


cl_read_file& cl_read_file::sort(string pattern){
  	if(!_read_ok){
	   f_alert("cl_read_file: sort() problem, use read() first");
	}
	for(size_t i=0;i<_nr;++i){
		
		
	}
}


cl_read_file& cl_read_file::init(string __fname, int _nhead, int _ihead,string _sep,bool _check,bool _out,bool read_now){
   if(!_init_ok){ 
	 free();
   }
   _init_ok=true;
   _read_ok=false;
   _fname=__fname;
   nhead=_nhead;
   ihead=_ihead;
   sep=_sep;
   check=_check;
   out=_out;
   _ok=false;
   if(read_now){
		   read();
   }

   return(*this);
}

int cl_read_file::nr(){
	if(!_read_ok && !_reads_ok){
	  f_alert("cl_read_file: nr() problem, use read() first");
	}
	return(_nr);	
}

vector<int>& cl_read_file::nc(){
	if(!_read_ok && !_reads_ok){
	  f_alert("cl_read_file: nc() problem, use read() first");	
	}
	return(_nc);	
}

vector<int>& cl_read_file::ne(){
	if(!_read_ok && !_reads_ok){
	  f_alert("cl_read_file: nc() problem, use read() first");	
	}
	return(_ne);	
}

bool cl_read_file::ok(){
	if(!_read_ok && !_reads_ok){
      f_alert("cl_read_file: ok() problem, use read() first",false);
	}
    return(_ok);
}

bool cl_read_file::read_ok(){
	return(_read_ok);
}

bool cl_read_file::reads_ok(){
	return(_reads_ok);
}

vector<string>& cl_read_file::head(){
	if(!_read_ok && !_reads_ok){
	  f_alert("cl_read_file: head() problem, use read() first");	
	}
    return(_head);	
}

vector<string>& cl_read_file::whead(){
	if(!_read_ok && !_reads_ok){
	  f_alert("cl_read_file: whead() problem, use read() first");	
	}
	return(_whead);	
}

vector<vector<T> >& cl_read_file::file(){
	if(!_read_ok){
	  f_alert("cl_read_file: file() problem, use read() first");	
	}
	return(_file);	
}

vector<string>& cl_read_file::files(){
	if(!_reads_ok){
	  f_alert("cl_read_file: files() problem, use reads() first");	
	}
	return(_files);	
}

string to_string_rf(T value) {
    stringstream sstr;
    sstr<< value;
    return sstr.str();
}

void f_extract(string &line,string separator,vector<T>&v,bool check,int il,string &_fname){
  /*
  if(check){
	  for(int i=0;i<line.length();i++){
         //if( isalpha(line[i]) && (line[i]!='.' && line[i]!='e' && line[i]!='E') ){
		 //   f_alert("cl_read_file: f_extract problem, alpha sing was found in line = "+line);
         //}
         if( isalpha(line[i]) && (line[i]!='.') ){
			 if( line[i]=='e' || line[i]=='E' ){
				//cout<<"line="<<line<<" i="<<i<<" "<<line.length()<<endl;
			    if(i<line.length()-1){
				   if( isalpha(line[i+1]) || isspace(line[i+1]) ){
				      f_alert("cl_read_file: f_extract problem 1, alpha sing was found in line = "+line+" \n No "+to_string_rf(il) );	    
				   }
				}else{
		           f_alert("cl_read_file: f_extract problem 2, alpha sing was found in line = "+line+" \n No "+to_string_rf(il));
				}
		     }else{
				f_alert("cl_read_file: f_extract problem 3, alpha sing was found in line = "+line+" \n No "+to_string_rf(il)); 
			 }
         }
	  }
  }*/
  if(check){
	  //cout<<"separator="<<separator<<"-->"<<separator.length()<<endl;
      for(size_t i=0;i<line.length();i++){
         if( !isdigit(line[i]) && (line[i]!='.') && (line[i]!='+') && (line[i]!='-') && !isspace(line[i]) ){
			 bool es=true;
			 if(separator.length()==0){
				 es=false;
			 }else{
				 if(i+separator.length()<line.length()){
                    for(size_t j=0;j<separator.length();j++){
				       if(line[i+j]!=separator[j]){
						   es=false;
					   }
			        }
				 }else{
					 es=false;
				 }
			 }		    	
			 if( !es ){
			      if( line[i]=='e' || line[i]=='E' ){
				    //cout<<"line="<<line<<" i="<<i<<" "<<line.length()<<endl;
			        if( (i<line.length()-1) && (i>0) ){
				      if( (!isdigit(line[i+1]) && (line[i+1]!='-') && (line[i+1]!='+')) ){
				          f_alert("cl_read_file: f_extract problem 1a, not a digit sing was found in line = "+line+" \n line No = "+to_string_rf(il)+" column = "+to_string_rf(i)+" sign = "+to_string_rf(line[i])+"\n in a file = "+_fname) ;	    
				      }else if(!isdigit(line[i-1])){
						  if(line[i-1]!='.'){
						     f_alert("cl_read_file: f_extract problem 1b, not a digit sing was found in line = "+line+" \n line No = "+to_string_rf(il)+" column = "+to_string_rf(i)+" sign = "+to_string_rf(line[i])+"\n in a file = "+_fname) ;	    
						  }else{
							  if(i==1){
							    f_alert("cl_read_file: f_extract problem 1c, not a digit sing was found in line = "+line+" \n line No = "+to_string_rf(il)+" column = "+to_string_rf(i)+" sign = "+to_string_rf(line[i])+"\n in a file = "+_fname) ;	     
							  }else{
								  if( !isdigit(line[i-2])){
									     f_alert("cl_read_file: f_extract problem 1d, not a digit sing was found in line = "+line+" \n line No = "+to_string_rf(il)+" column = "+to_string_rf(i)+" sign = "+to_string_rf(line[i])+"\n in a file = "+_fname) ;	    
								  }
							  }
						  }
					  }
				    }else{
		                f_alert("cl_read_file: f_extract problem 2, not a digit sing was found in line = "+line+" \n line No = "+to_string_rf(il)+" column = "+to_string_rf(i)+" sign = "+to_string_rf(line[i])+"\n in a file = "+_fname);
				    }
		          }else{
					  
					 bool term=true;
					  
					 //cout<<"llll="<<line<<endl;
					 //cout<<"i="<<i<<" "<<line.length()<<" "<<separator.length()<<" "<<line.length()-i<<endl;
					  if(line.length()-i>=separator.length()){
						  //cout<<"llll="<<line<<endl;
						  //cout<<"separator="<<separator<<endl;
						   bool ok=true;
                          for(size_t j=0;j<separator.length();++j){
						     if(line[i+j]!=separator[j]){
							   ok=false;	 
							   break;
							 }
						  
						  }
						  if(ok)term=false;
					  }
					  
					  if(term){
				        f_alert("cl_read_file: f_extract problem 3, not a digit sing was found in line = "+line+" \n line No = "+to_string_rf(il)+" column = "+to_string_rf(i)+" sign = "+to_string_rf(line[i])+"\n in a file = "+_fname);
					  }
			      }
			 }
		 }
	  }
  }
  v.clear();
  if(separator==" " || separator=="\t" || separator==""){
    istringstream c{line};
    T x;
    while(!c.eof()){
  	  c>>x;
	  v.push_back(x);
	  //cout<<v.back()<<endl;
    }
  }else{
  	 int n=0;
  	 while((n=line.find(separator))!=string::npos){
  	 	string p=line.substr(0,n);
  	 	//cout<<p<<endl;
  	 	line=line.substr(n+separator.length(),line.length());
  	 	v.push_back(atof(p.c_str()));
  	 }
  	 if(line.length()>0)v.push_back(atof(line.c_str()));
  	
  }
}

void f_extract(string &line,string separator,vector<string> &v,bool check, int il,string &_fname){
  v.clear();
  if(line.length()>0){
      while(isspace(line[line.length()-1])){line.erase(line.end()-1);}//erase white spaces and new line sign at the end af the string
	  int i=0;while(isspace(line[i])){i++;}if(i>0)line.erase(line.begin(),line.begin()+i);//erase white spaces at the bigining af the string(version more efficient)
      //cout<<"line="<<line<<"***"<<line.length()<<endl;
  }
  if(line.length()>0){
    if(separator==" " || separator=="\t" || separator==""){
      istringstream c{line};
      string x;
      while(!c.eof()){
  	     c>>x;
	     v.push_back(x);
	     //cout<<v.back()<<endl;
      }
    }else{
  	   int n=0;
  	   while((n=line.find(separator))!=string::npos){
  	    	string p=line.substr(0,n);
  	   	    //cout<<p<<endl;
  	 	    line=line.substr(n+separator.length(),line.length());
  	 	    v.push_back(p);
  	   }
  	   if(line.length()>0)v.push_back(line);
  	
    }
  }
}


cl_read_file& cl_read_file::read(){
   _read_ok=false;
   _file.clear();
   _head.clear();
   _whead.clear();
   if(_init_ok){
	    ifstream f_file;
        f_file.open(_fname.c_str());
        if( !f_file.good() ){
            if(out)f_alert("cl_read_file: read() problem, Missing file = "+_fname,false);
	        _ok=false;
        }else{
	        _ok=true;
	        vector<T>xxx;
	        string line;
			bool defhead=false,defihed=false;
			if(nhead>0){
	           for(int i=0;i<nhead;++i){ 
		           if(!f_file.eof()){
	                  getline(f_file,line);
					  //if(line.length()>0){
		              //   i=0;while(isspace(line[i])){i++;}if(i>0)line.erase(line.begin(),line.begin()+i);//erase white spaces at the bigining af the string(version more efficient)
			          //}
			          //if(line.length()>0){
		              //   while(isspace(line[line.length()-1])){line.erase(line.end()-1);}//erase white spaces and new line sign at the end af the string
			          //}
					  if(out)cout<<line<<"-->"<<line.length()<<endl;
					  _whead.push_back(line);
					  if(i==ihead){
						  if(out)cout<<"head line = "<<line<<"-->"<<line.length()<<endl;
						  f_extract(line,sep,_head,check,i,_fname);
						  defihed=true;
					  }
	               }else{
	                  if(out)f_alert("cl_read_file:  headers are missing, file = "+_fname+", using default header",false);
				      defhead=true;
	              }
			   }
	        }else{//missing column names
			   defhead=true;	
			}
			if(!defihed){//missing column names
			   defhead=true;	
			}
			int i,nct,il=0;
			_nr=0;
			if(defhead){//default column names
               //cout<<"default column names"<<endl;
			   while(!f_file.eof()){
	              getline(f_file,line);
				  if(line.length()>0){
		             i=0;while(isspace(line[i])){i++;}if(i>0)line.erase(line.begin(),line.begin()+i);//erase white spaces at the bigining af the string(version more efficient)
			      }
			      if(line.length()>0){
		             while(isspace(line[line.length()-1])){line.erase(line.end()-1);}//erase white spaces and new line sign at the end af the string
			      }
			      if(out)cout<<line<<"-->"<<line.length()<<endl;
	              if(line.length()!=0){
	       	         f_extract(line,sep,xxx,check,il,_fname);
					 if( ((nct=xxx.size()))>0 ){
						 _nc.push_back(nct);
		                _file.push_back(xxx);
					    ++_nr;
						for(i=0;i<nct;++i){
						  _head.push_back(to_string_rf(i+1));	
						}
						break;
					 }
	              }else{
				     _ne.push_back(il);
			      }
                  ++il;
			   }	
			}
	        //while(!f_file.eof()){
	        //   getline(f_file,line);
	        //const int MAX_LENGTH = 524288;
            //char* linec = new char[MAX_LENGTH];

	        //while(f_file.getline(linec,MAX_LENGTH)){
				//line=linec;
			while(getline(f_file,line)){	
               //cout<<line<<endl;
			   //if(line.length()>0){
		       //   i=0;while(isspace(line[i])){i++;}if(i>0)line.erase(line.begin(),line.begin()+i);//erase white spaces at the bigining af the string(version more efficient)
			   //}
			   if(line.length()>0){
		          while(isspace(line[line.length()-1])){line.erase(line.end()-1);}//erase white spaces and new line sign at the end af the string
			   }
			   if(out)cout<<line<<"-->"<<line.length()<<endl;
	           if(line.length()!=0){
	       	         f_extract(line,sep,xxx,check,il,_fname);
					 if( ((nct=xxx.size()))>0 ){
						 _nc.push_back(nct);
		                _file.push_back(xxx);
					    ++_nr;
					 }
	           }else{
				  _ne.push_back(il);
			   }
               ++il;
			}
      }
      if(_ok && _nr>0)_ok=true;
	  else _ok=false;
      f_file.close();
      _read_ok=true;
   }else{
	  f_alert("cl_read_file: read() problem, use init() first");   
   }
   return(*this);	
}


cl_read_file& cl_read_file::readmap(){
   _read_ok=false;
   _file.clear();
   _head.clear();
   _whead.clear();
   if(_init_ok){
	    ifstream f_file;
        f_file.open(_fname.c_str());
        if( !f_file.good() ){
            if(out)f_alert("cl_read_file: read() problem, Missing file = "+_fname,false);
	        _ok=false;
        }else{
	        _ok=true;
	        vector<T>xxx;
	        string line;
			bool defhead=false,defihed=false;
			if(nhead>0){
	           for(int i=0;i<nhead;++i){ 
		           if(!f_file.eof()){
	                  getline(f_file,line);
					  //if(line.length()>0){
		              //   i=0;while(isspace(line[i])){i++;}if(i>0)line.erase(line.begin(),line.begin()+i);//erase white spaces at the bigining af the string(version more efficient)
			          //}
			          //if(line.length()>0){
		              //   while(isspace(line[line.length()-1])){line.erase(line.end()-1);}//erase white spaces and new line sign at the end af the string
			          //}
					  if(out)cout<<line<<"-->"<<line.length()<<endl;
					  _whead.push_back(line);
					  if(i==ihead){
						  if(out)cout<<"head line = "<<line<<"-->"<<line.length()<<endl;
						  f_extract(line,sep,_head,check,i,_fname);
						  defihed=true;
					  }
	               }else{
	                  if(out)f_alert("cl_read_file:  headers are missing, file = "+_fname+", using default header",false);
				      defhead=true;
	              }
			   }
	        }else{//missing column names
			   defhead=true;	
			}
			if(!defihed){//missing column names
			   defhead=true;	
			}
			int i,nct,il=0;
			_nr=0;
			if(defhead){//default column names
			   while(!f_file.eof()){
	              getline(f_file,line);
				  if(line.length()>0){
		             i=0;while(isspace(line[i])){i++;}if(i>0)line.erase(line.begin(),line.begin()+i);//erase white spaces at the bigining af the string(version more efficient)
			      }
			      if(line.length()>0){
		             while(isspace(line[line.length()-1])){line.erase(line.end()-1);}//erase white spaces and new line sign at the end af the string
			      }
			      if(out)cout<<line<<"-->"<<line.length()<<endl;
	              if(line.length()!=0){
	       	         f_extract(line,sep,xxx,check,il,_fname);
					 if( ((nct=xxx.size()))>0 ){
						 _nc.push_back(nct);
		                _file.push_back(xxx);
					    ++_nr;
						for(i=0;i<nct;++i){
						  _head.push_back(to_string_rf(i+1));	
						}
						break;
					 }
	              }else{
				     _ne.push_back(il);
			      }
                  ++il;
			   }	
			}
	        
	        //f_file.close();
			
			//cout<<"file="<<_fname<<endl;
			//cout<<"file="<<_head<<endl;
	        struct stat sb;
            long cntr = 0;
            int fd, lineLen;
            char *data;
            char *linec,*data2;
            // map the file
            fd = open(_fname.c_str(), O_RDONLY);
     
			if(fstat(fd, &sb)==-1){
                 cerr << "Could not stat \"" << _fname << "\" for reading (" << strerror(errno) << ")." << endl;
                 close(fd);
                 exit(1);
            }  
            //cout<<"sb.st_size="<<sb.st_size<<endl;
			if(sb.st_size>0){
            //// int pageSize;
            //// pageSize = getpagesize();
            //// data = mmap((caddr_t)0, pageSize, PROT_READ, MAP_PRIVATE, fd, pageSize);
            data = reinterpret_cast <char*>(mmap((caddr_t)0, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0));
            if(data == MAP_FAILED){
                cerr << "Could not memory map file \"" << _fname << "\" (" << strerror(errno) << ")." << endl;
                close(fd);
                exit(1);
            }
            data2=data;
			//linec = data;
			//line=linec;
			//cout<<line<<endl;
            // get lines
			int iline=0;
            //int l0=0;
            while(cntr < sb.st_size) {
              lineLen = 0;
              linec = data2;
              // find the next line
			  //line=linec;
			  //cout<<endl<<line<<endl<<endl;;
			   
              while(*data2 != '\n' && cntr < sb.st_size) {
				  //cout<<"d="<<*data<<endl;
                data2++;
                cntr++;
                lineLen++;
              }
              if(*data2 == '\n'){
                 ++data2;
			     cntr++;
                 lineLen++;
			  }
              /***** PROCESS LINE *****/
			  
			  line.resize(lineLen);
			  //for(int ii=l0;ii<l0+lineLen;++ii){
			  for(int ii=0;ii<lineLen;++ii){
				  //cout<<linec[ii]<<" -- "<<ii<<endl;
			      //line.push_back((linec[ii]));			  
				  //line=data[ii];
				  line[ii]=linec[ii];
			  }
			  //cout<<"data="<<*(data+1)<<" lineLen="<<lineLen<<endl;
              //cout<<"line="<<line<<" "<<iline<<endl;
			  //if(iline==1)exit(1);
			  if(iline>=nhead){
				  //cout<<"line="<<line<<" "<<iline<<endl;
			      if(line.length()>0){
		             while(isspace(line[line.length()-1])){line.erase(line.end()-1);}//erase white spaces and new line sign at the end af the string
			      }
			      if(out)cout<<line<<"-->"<<line.length()<<endl;
	              if(line.length()!=0){
	       	         f_extract(line,sep,xxx,check,il,_fname);
					 if( ((nct=xxx.size()))>0 ){
						 _nc.push_back(nct);
		                _file.push_back(xxx);
					    ++_nr;
					 }
	              }else{
				    _ne.push_back(il);
			      }
                   ++il;
			  }			  
              // ... processLine(line, lineLen);
              ++iline;
            }
			close(fd);
			munmap(data,sb.st_size);
			//munmap(linec,sb.st_size);
			//if(data!=NULL){
			//std::free(data);
			//std::free(linec);			
			//}
			//delete[] (data);
			//delete[] (linec);
			
			/*
	        while(f_file.getline(linec,MAX_LENGTH)){
				line=linec;
               //cout<<line<<endl;
			   //if(line.length()>0){
		       //   i=0;while(isspace(line[i])){i++;}if(i>0)line.erase(line.begin(),line.begin()+i);//erase white spaces at the bigining af the string(version more efficient)
			   //}
			   if(line.length()>0){
		          while(isspace(line[line.length()-1])){line.erase(line.end()-1);}//erase white spaces and new line sign at the end af the string
			   }
			   if(out)cout<<line<<"-->"<<line.length()<<endl;
	           if(line.length()!=0){
	       	         f_extract(line,sep,xxx,check,il,_fname);
					 if( ((nct=xxx.size()))>0 ){
						 _nc.push_back(nct);
		                _file.push_back(xxx);
					    ++_nr;
					 }
	           }else{
				  _ne.push_back(il);
			   }
               ++il;
			}
			*/
			}
			
			
      }
      if(_ok && _nr>0)_ok=true;
	  else _ok=false;
      f_file.close();
      _read_ok=true;
   }else{
	  f_alert("cl_read_file: read() problem, use init() first");   
   }
   return(*this);	
}



cl_read_file& cl_read_file::reads(){
   _reads_ok=false;
   if(_init_ok){
	    ifstream f_file;
        f_file.open(_fname.c_str());
        if( !f_file.good() ){
            if(out)f_alert("cl_read_file: read() problem, Missing file = "+_fname,false);
	        _ok=false;
        }else{
	        _ok=true;
	        vector<T>xxx;
	        string line;
			bool defhead=false,defihed=false;
			if(nhead>0){
	           for(int i=0;i<nhead;++i){ 
		           if(!f_file.eof()){
	                  getline(f_file,line);
					  if(out)cout<<line<<"-->"<<line.length()<<endl;
					  _whead.push_back(line);
					  if(i==ihead){
						  if(out)cout<<"head line = "<<line<<"-->"<<line.length()<<endl;
						  f_extract(line,sep,_head,check,i,_fname);
						  defihed=true;
					  }
	               }else{
	                  if(out)f_alert("cl_read_file:  headers are missing, file = "+_fname+", using default header",false);
				      defhead=true;
	              }
			   }
	        }else{//missing column names
			   defhead=true;	
			}
			if(!defihed){//missing column names
			   defhead=true;	
			}
            int il=0;
			_nr=0;
			//while(!f_file.eof()){
	        //   getline(f_file,line);
			while(getline(f_file,line)){
			   //if(line.length()>0){
		       //   i=0;while(isspace(line[i])){i++;}if(i>0)line.erase(line.begin(),line.begin()+i);//erase white spaces at the bigining af the string(version more efficient)
			   //}
			   //if(line.length()>0){
		       //   while(isspace(line[line.length()-1])){line.erase(line.end()-1);}//erase white spaces and new line sign at the end af the string
			   //}
			   //if(out)cout<<line<<"-->"<<line.length()<<endl;
	           //if(line.length()!=0){
	       	         //f_extract(line,sep,xxx,check,il);
					 //if( ((nct=xxx.size()))>0 ){
					 //	 _nc.push_back(nct);
		             _files.push_back(line);
					 ++_nr;
					 _nc.push_back(1);
					 //}
	           //}else{
			   //	  _ne.push_back(il);
			   //}
               ++il;
			}
      }
      if(_ok && _nr>0)_ok=true;
	  else _ok=false;
      f_file.close();
      _reads_ok=true;
   }else{
	  f_alert("cl_read_file: read() problem, use init() first");   
   }
   return(*this);	
}


vector<T> f_get_column(cl_read_file&file,string pattern){
   vector<T> vec;
   int col=f_get_column_head_nr_col(file.head(),pattern);
   if(col!=-1){
     if(file.file().size()>0){
         for(int i=0;i<file.file().size();i++){
             if(file.file()[i].size()>col){       
	            vec.push_back(file.file()[i][col]);
	     }
       }
     }
   }//col!=-1
   return(vec);
}






//**********************************************8

string cl_read_file_str::file_name(){
    return(_fname);
}

void cl_read_file_str::help(){
  cout<<endl<<"cl_read_file:"<<endl;
  cout<<"This class can be used to read data from a file."<<endl;
  cout<<"Initialization:"<<endl;
  cout<<"cl_read_file<Type> file;"<<endl;
  cout<<"file.init(string file_name, int nhead, int ihead, string sepparation, bool check=true, bool out=false)"<<endl;
  cout<<"cl_read_file<Type> file{string file_name, int nhead, int ihead, string sepparation, bool check=true, bool out=false)"<<endl;
  cout<<endl;
  cout<<"file.read() - read data and save into internal variables; you can acces them through file(), head() and whead()"<<endl;
  cout<<"file.reads() - read data and save into internal vector<string> variable; you can acces them through files(), head() and whead()"<<endl;
  cout<<"file.help() - this output"<<endl;
  cout<<"bool file.cc() - check whether all columns have the same size"<<endl;
  cout<<"file.ne() - numbers of the empty rows"<<endl;
  cout<<endl;
}

void cl_read_file_str::info(){
   cout<<"cl_read_file:"<<endl;
   cout<<"file = "<<_fname<<endl;
   cout<<"nr = "<<nr()<<endl;
   if(cc()){
      cout<<"nc = "<<nc().front()<<endl;
   }else{
      cout<<"nc = "<<nc().front()<<endl;
   }
}

bool cl_read_file_str::cc(){
   if(_read_ok || _reads_ok){
	   bool okc=true;
	   if(_nr>1){
	     for(size_t i=0;i<_nr-1;++i){
		   if(_nc[i]!=_nc[i+1]){
		 	 okc=false;
		 	 cout<<"nc["<<i<<"] = "<<_nc[i]<<" nc["<<i+1<<"] = "<<_nc[i+1]<<endl;
		   }
	     }
	   }
	   return(okc);
   }else{
	  f_alert("cl_read_file: cc() problem, use read() first");
	  return(false);
   }
}

void cl_read_file_str::free(){
   	_head.clear();
	_file.clear();
	_whead.clear();
}

ostream & operator<< (ostream &ret, cl_read_file_str &rf){
   for(size_t i=0;i<rf.whead().size();i++){
      ret<<rf.whead()[i]<<endl;
   }
   for(size_t i=0;i<rf.head().size();i++){
      ret<<rf.head()[i]<<" ";
   }
   if(rf.whead().size()>0 || rf.head().size()>0)ret<<endl;
   if(rf.read_ok()){
     for(size_t i=0;i<rf.file().size();i++){
       for(size_t j=0;j<rf.file()[i].size();j++){
          ret<<rf.file()[i][j]<<" ";
	   }
	   ret<<endl;
     }
   }
   if(rf.reads_ok()){
	   //cout<<"sasas"<<endl;
     for(size_t i=0;i<rf.files().size()-1;i++){
          ret<<rf.files()[i]<<endl;
     }
     if(rf.files().size()>0)ret<<rf.files().back();
   }
   //ret<<endl;
   //for(size_t i=0;i<rf.nc().size();i++){
   //   ret<<rf.nc()[i]<<" ";//<<endl;
   //}
   //ret<<ret2.str();
   return(ret);
}


cl_read_file_str& cl_read_file_str::sort(string pattern){
  	if(!_read_ok){
	   f_alert("cl_read_file: sort() problem, use read() first");
	}
	for(size_t i=0;i<_nr;++i){


	}
}


cl_read_file_str& cl_read_file_str::init(string __fname, int _nhead, int _ihead,string _sep,bool _check,bool _out,bool read_now){
   if(!_init_ok){
	 free();
   }
   _init_ok=true;
   _read_ok=false;
   _fname=__fname;
   nhead=_nhead;
   ihead=_ihead;
   sep=_sep;
   check=_check;
   out=_out;
   _ok=false;
   if(read_now){
       read();
    }
   return(*this);
}

int cl_read_file_str::nr(){
	if(!_read_ok && !_reads_ok){
	  f_alert("cl_read_file: nr() problem, use read() first");
	}
	return(_nr);
}

vector<int>& cl_read_file_str::nc(){
	if(!_read_ok && !_reads_ok){
	  f_alert("cl_read_file: nc() problem, use read() first");
	}
	return(_nc);
}

vector<int>& cl_read_file_str::ne(){
	if(!_read_ok && !_reads_ok){
	  f_alert("cl_read_file: nc() problem, use read() first");
	}
	return(_ne);
}

bool cl_read_file_str::ok(){
	if(!_read_ok && !_reads_ok){
      f_alert("cl_read_file: ok() problem, use read() first",false);
	}
    return(_ok);
}

bool cl_read_file_str::read_ok(){
	return(_read_ok);
}

bool cl_read_file_str::reads_ok(){
	return(_reads_ok);
}

vector<string>& cl_read_file_str::head(){
	if(!_read_ok && !_reads_ok){
	  f_alert("cl_read_file: head() problem, use read() first");
	}
    return(_head);
}

vector<string>& cl_read_file_str::whead(){
	if(!_read_ok && !_reads_ok){
	  f_alert("cl_read_file: whead() problem, use read() first");
	}
	return(_whead);
}

vector<vector<string> >& cl_read_file_str::file(){
	if(!_read_ok){
	  f_alert("cl_read_file: file() problem, use read() first");
	}
	return(_file);
}

vector<string>& cl_read_file_str::files(){
	if(!_reads_ok){
	  f_alert("cl_read_file: files() problem, use reads() first");
	}
	return(_files);
}

string to_string_rf(string value) {
    stringstream sstr;
    sstr<< value;
    return sstr.str();
}


cl_read_file_str& cl_read_file_str::read(){
   _read_ok=false;
   _file.clear();
   _head.clear();
   _whead.clear();
   if(_init_ok){
	    ifstream f_file;
        f_file.open(_fname.c_str());
        if( !f_file.good() ){
            if(out)f_alert("cl_read_file: read() problem, Missing file = "+_fname,false);
	        _ok=false;
        }else{
	        _ok=true;
            vector<string>xxx;
	        string line;
			bool defhead=false,defihed=false;
			if(nhead>0){
	           for(int i=0;i<nhead;++i){
		           if(!f_file.eof()){
	                  getline(f_file,line);
					  //if(line.length()>0){
		              //   i=0;while(isspace(line[i])){i++;}if(i>0)line.erase(line.begin(),line.begin()+i);//erase white spaces at the bigining af the string(version more efficient)
			          //}
			          //if(line.length()>0){
		              //   while(isspace(line[line.length()-1])){line.erase(line.end()-1);}//erase white spaces and new line sign at the end af the string
			          //}
					  if(out)cout<<line<<"-->"<<line.length()<<endl;
					  _whead.push_back(line);
					  if(i==ihead){
						  if(out)cout<<"head line = "<<line<<"-->"<<line.length()<<endl;
						  f_extract(line,sep,_head,check,i,_fname);
						  defihed=true;
					  }
	               }else{
	                  if(out)f_alert("cl_read_file:  headers are missing, file = "+_fname+", using default header",false);
				      defhead=true;
	              }
			   }
	        }else{//missing column names
			   defhead=true;
			}
			if(!defihed){//missing column names
			   defhead=true;
			}
			int i,nct,il=0;
			_nr=0;
			if(defhead){//default column names
			   while(!f_file.eof()){
	              getline(f_file,line);
				  if(line.length()>0){
		             i=0;while(isspace(line[i])){i++;}if(i>0)line.erase(line.begin(),line.begin()+i);//erase white spaces at the bigining af the string(version more efficient)
			      }
			      if(line.length()>0){
		             while(isspace(line[line.length()-1])){line.erase(line.end()-1);}//erase white spaces and new line sign at the end af the string
			      }
			      if(out)cout<<line<<"-->"<<line.length()<<endl;
	              if(line.length()!=0){
	       	         f_extract(line,sep,xxx,check,il,_fname);
					 if( ((nct=xxx.size()))>0 ){
						 _nc.push_back(nct);
		                _file.push_back(xxx);
					    ++_nr;
						for(i=0;i<nct;++i){
						  _head.push_back(to_string_rf(i+1));
						}
						break;
					 }
	              }else{
				     _ne.push_back(il);
			      }
                  ++il;
			   }
			}
	        //while(!f_file.eof()){
	        //   getline(f_file,line);
	        //const int MAX_LENGTH = 524288;
            //char* linec = new char[MAX_LENGTH];

	        //while(f_file.getline(linec,MAX_LENGTH)){
				//line=linec;
			while(getline(f_file,line)){
               //cout<<line<<endl;
			   //if(line.length()>0){
		       //   i=0;while(isspace(line[i])){i++;}if(i>0)line.erase(line.begin(),line.begin()+i);//erase white spaces at the bigining af the string(version more efficient)
			   //}
			   if(line.length()>0){
		          while(isspace(line[line.length()-1])){line.erase(line.end()-1);}//erase white spaces and new line sign at the end af the string
			   }
			   if(out)cout<<line<<"-->"<<line.length()<<endl;
	           if(line.length()!=0){
	       	         f_extract(line,sep,xxx,check,il,_fname);
					 if( ((nct=xxx.size()))>0 ){
						 _nc.push_back(nct);
		                _file.push_back(xxx);
					    ++_nr;
					 }
	           }else{
				  _ne.push_back(il);
			   }
               ++il;
			}
      }
      if(_ok && _nr>0)_ok=true;
	  else _ok=false;
      f_file.close();
      _read_ok=true;
   }else{
	  f_alert("cl_read_file: read() problem, use init() first");
   }
   return(*this);
}


cl_read_file_str& cl_read_file_str::readmap(){
   _read_ok=false;
   _file.clear();
   _head.clear();
   _whead.clear();
   if(_init_ok){
	    ifstream f_file;
        f_file.open(_fname.c_str());
        if( !f_file.good() ){
            if(out)f_alert("cl_read_file: read() problem, Missing file = "+_fname,false);
	        _ok=false;
        }else{
	        _ok=true;
            vector<string>xxx;
	        string line;
			bool defhead=false,defihed=false;
			if(nhead>0){
	           for(int i=0;i<nhead;++i){
		           if(!f_file.eof()){
	                  getline(f_file,line);
					  //if(line.length()>0){
		              //   i=0;while(isspace(line[i])){i++;}if(i>0)line.erase(line.begin(),line.begin()+i);//erase white spaces at the bigining af the string(version more efficient)
			          //}
			          //if(line.length()>0){
		              //   while(isspace(line[line.length()-1])){line.erase(line.end()-1);}//erase white spaces and new line sign at the end af the string
			          //}
					  if(out)cout<<line<<"-->"<<line.length()<<endl;
					  _whead.push_back(line);
					  if(i==ihead){
						  if(out)cout<<"head line = "<<line<<"-->"<<line.length()<<endl;
						  f_extract(line,sep,_head,check,i,_fname);
						  defihed=true;
					  }
	               }else{
	                  if(out)f_alert("cl_read_file:  headers are missing, file = "+_fname+", using default header",false);
				      defhead=true;
	              }
			   }
	        }else{//missing column names
			   defhead=true;
			}
			if(!defihed){//missing column names
			   defhead=true;
			}
			int i,nct,il=0;
			_nr=0;
			if(defhead){//default column names
			   while(!f_file.eof()){
	              getline(f_file,line);
				  if(line.length()>0){
		             i=0;while(isspace(line[i])){i++;}if(i>0)line.erase(line.begin(),line.begin()+i);//erase white spaces at the bigining af the string(version more efficient)
			      }
			      if(line.length()>0){
		             while(isspace(line[line.length()-1])){line.erase(line.end()-1);}//erase white spaces and new line sign at the end af the string
			      }
			      if(out)cout<<line<<"-->"<<line.length()<<endl;
	              if(line.length()!=0){
	       	         f_extract(line,sep,xxx,check,il,_fname);
					 if( ((nct=xxx.size()))>0 ){
						 _nc.push_back(nct);
		                _file.push_back(xxx);
					    ++_nr;
						for(i=0;i<nct;++i){
						  _head.push_back(to_string_rf(i+1));
						}
						break;
					 }
	              }else{
				     _ne.push_back(il);
			      }
                  ++il;
			   }
			}

	        //f_file.close();

			//cout<<"file="<<_fname<<endl;
			//cout<<"file="<<_head<<endl;
	        struct stat sb;
            long cntr = 0;
            int fd, lineLen;
            char *data;
            char *linec,*data2;
            // map the file
            fd = open(_fname.c_str(), O_RDONLY);

			if(fstat(fd, &sb)==-1){
                 cerr << "Could not stat \"" << _fname << "\" for reading (" << strerror(errno) << ")." << endl;
                 close(fd);
                 exit(1);
            }
            //cout<<"sb.st_size="<<sb.st_size<<endl;
			if(sb.st_size>0){
            //// int pageSize;
            //// pageSize = getpagesize();
            //// data = mmap((caddr_t)0, pageSize, PROT_READ, MAP_PRIVATE, fd, pageSize);
            data = reinterpret_cast <char*>(mmap((caddr_t)0, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0));
            if(data == MAP_FAILED){
                cerr << "Could not memory map file \"" << _fname << "\" (" << strerror(errno) << ")." << endl;
                close(fd);
                exit(1);
            }
            data2=data;
			//linec = data;
			//line=linec;
			//cout<<line<<endl;
            // get lines
			int iline=0;
            //int l0=0;
            while(cntr < sb.st_size) {
              lineLen = 0;
              linec = data2;
              // find the next line
			  //line=linec;
			  //cout<<endl<<line<<endl<<endl;;

              while(*data2 != '\n' && cntr < sb.st_size) {
				  //cout<<"d="<<*data<<endl;
                data2++;
                cntr++;
                lineLen++;
              }
              if(*data2 == '\n'){
                 ++data2;
			     cntr++;
                 lineLen++;
			  }
              /***** PROCESS LINE *****/

			  line.resize(lineLen);
			  //for(int ii=l0;ii<l0+lineLen;++ii){
			  for(int ii=0;ii<lineLen;++ii){
				  //cout<<linec[ii]<<" -- "<<ii<<endl;
			      //line.push_back((linec[ii]));
				  //line=data[ii];
				  line[ii]=linec[ii];
			  }
			  //cout<<"data="<<*(data+1)<<" lineLen="<<lineLen<<endl;
              //cout<<"line="<<line<<" "<<iline<<endl;
			  //if(iline==1)exit(1);
			  if(iline>=nhead){
				  //cout<<"line="<<line<<" "<<iline<<endl;
			      if(line.length()>0){
		             while(isspace(line[line.length()-1])){line.erase(line.end()-1);}//erase white spaces and new line sign at the end af the string
			      }
			      if(out)cout<<line<<"-->"<<line.length()<<endl;
	              if(line.length()!=0){
	       	         f_extract(line,sep,xxx,check,il,_fname);
					 if( ((nct=xxx.size()))>0 ){
						 _nc.push_back(nct);
		                _file.push_back(xxx);
					    ++_nr;
					 }
	              }else{
				    _ne.push_back(il);
			      }
                   ++il;
			  }
              // ... processLine(line, lineLen);
              ++iline;
            }
			close(fd);
			munmap(data,sb.st_size);
			//munmap(linec,sb.st_size);
			//if(data!=NULL){
			//std::free(data);
			//std::free(linec);
			//}
			//delete[] (data);
			//delete[] (linec);

			/*
	        while(f_file.getline(linec,MAX_LENGTH)){
				line=linec;
               //cout<<line<<endl;
			   //if(line.length()>0){
		       //   i=0;while(isspace(line[i])){i++;}if(i>0)line.erase(line.begin(),line.begin()+i);//erase white spaces at the bigining af the string(version more efficient)
			   //}
			   if(line.length()>0){
		          while(isspace(line[line.length()-1])){line.erase(line.end()-1);}//erase white spaces and new line sign at the end af the string
			   }
			   if(out)cout<<line<<"-->"<<line.length()<<endl;
	           if(line.length()!=0){
	       	         f_extract(line,sep,xxx,check,il,_fname);
					 if( ((nct=xxx.size()))>0 ){
						 _nc.push_back(nct);
		                _file.push_back(xxx);
					    ++_nr;
					 }
	           }else{
				  _ne.push_back(il);
			   }
               ++il;
			}
			*/
			}


      }
      if(_ok && _nr>0)_ok=true;
	  else _ok=false;
      f_file.close();
      _read_ok=true;
   }else{
	  f_alert("cl_read_file: read() problem, use init() first");
   }
   return(*this);
}



cl_read_file_str& cl_read_file_str::reads(){
   _reads_ok=false;
   if(_init_ok){
	    ifstream f_file;
        f_file.open(_fname.c_str());
        if( !f_file.good() ){
            if(out)f_alert("cl_read_file: read() problem, Missing file = "+_fname,false);
	        _ok=false;
        }else{
	        _ok=true;
	        vector<string >xxx;
	        string line;
			bool defhead=false,defihed=false;
			if(nhead>0){
	           for(int i=0;i<nhead;++i){
		           if(!f_file.eof()){
	                  getline(f_file,line);
					  if(out)cout<<line<<"-->"<<line.length()<<endl;
					  _whead.push_back(line);
					  if(i==ihead){
						  if(out)cout<<"head line = "<<line<<"-->"<<line.length()<<endl;
						  f_extract(line,sep,_head,check,i,_fname);
						  defihed=true;
					  }
	               }else{
	                  if(out)f_alert("cl_read_file:  headers are missing, file = "+_fname+", using default header",false);
				      defhead=true;
	              }
			   }
	        }else{//missing column names
			   defhead=true;
			}
			if(!defihed){//missing column names
			   defhead=true;
			}
            int il=0;
			_nr=0;
			//while(!f_file.eof()){
	        //   getline(f_file,line);
			while(getline(f_file,line)){
			   //if(line.length()>0){
		       //   i=0;while(isspace(line[i])){i++;}if(i>0)line.erase(line.begin(),line.begin()+i);//erase white spaces at the bigining af the string(version more efficient)
			   //}
			   //if(line.length()>0){
		       //   while(isspace(line[line.length()-1])){line.erase(line.end()-1);}//erase white spaces and new line sign at the end af the string
			   //}
			   //if(out)cout<<line<<"-->"<<line.length()<<endl;
	           //if(line.length()!=0){
	       	         //f_extract(line,sep,xxx,check,il);
					 //if( ((nct=xxx.size()))>0 ){
					 //	 _nc.push_back(nct);
		             _files.push_back(line);
					 ++_nr;
					 _nc.push_back(1);
					 //}
	           //}else{
			   //	  _ne.push_back(il);
			   //}
               ++il;
			}
      }
      if(_ok && _nr>0)_ok=true;
	  else _ok=false;
      f_file.close();
      _reads_ok=true;
   }else{
	  f_alert("cl_read_file: read() problem, use init() first");
   }
   return(*this);
}


vector<string> f_get_column(cl_read_file_str&file,string pattern){
   vector<string> vec;
   int col=f_get_column_head_nr_col(file.head(),pattern);
   if(col!=-1){
     if(file.file().size()>0){
         for(int i=0;i<file.file().size();i++){
             if(file.file()[i].size()>col){
	            vec.push_back(file.file()[i][col]);
	     }
       }
     }
   }//col!=-1
   return(vec);
}

#include "mainwindow.h"





void MainWindow::update_frequency_manager(){

    vector<double>freq_i;
    vector<double>freq_all;
    int ind_freq=-1;
    int ind_status=-1;
    for(auto i=0;i<table->columnCount();++i){
        if(table->horizontalHeaderItem(i)->text()=="status"){
            ind_status=i;
        }
        if(table->horizontalHeaderItem(i)->text()=="freq"){
            ind_freq=i;
        }
    }
    //cout<<"update_frequency_manager: ind_status="<<ind_status<<" ind_freq="<<ind_freq<<endl;
    if(ind_status!=-1 && ind_freq!=-1){
        for(int i=0;i<table->rowCount();++i){
            if(table->item(i,ind_status)!=nullptr){
                if(table->item(i,ind_status)->text()=="" || table->item(i,ind_status)->text()=="i"){
                    freq_i.push_back(table->item(i,ind_freq)->text().toDouble());
                }
            }
            freq_all.push_back(table->item(i,ind_freq)->text().toDouble());
        }
    }

    frequency_manager.set_martix(_freq_matrix);
    frequency_manager.set_frequencies(freq_all);
    frequency_manager.analyse();

}


void Frequency_manager::set_martix(vector<vector<double> >&matrix){
    _matrix=matrix;
}
void Frequency_manager::set_frequencies(vector<double>&frequencies){
    _frequencies=frequencies;
}
void Frequency_manager::analyse(){
    cout<<"Frequency_manager::analyse()"<<endl;

    _nfreq=_frequencies.size();
    _nmatrix=_matrix.size();

    if(_nfreq==_nmatrix){
        _entries.clear();
        _entries_v.clear();
        _is_independent.clear();
        for(int i=0;i<_nmatrix;++i){
            int entries=0;
            vector<int> entries_v;
            for(int j=0;j<_matrix[i].size();++j){
                if(_matrix[i][j]!=0){
                    ++entries;
                    entries_v.push_back(_matrix[i][j]);
                }
            }
            _entries.push_back(entries);
            _entries_v.push_back(entries_v);
        }

        //cout<<"entries:"<<endl;
        //cout<<_entries<<endl;
        //cout<<"entries_v:"<<endl;
        //cout<<_entries_v<<endl;

        independent_index.clear();
        independent_general_index.clear();
        int indnumber=0;
        for(int i=0;i<_nfreq;++i){
            bool isind=false;
            if(_entries[i]==1){
                if(_entries_v[i][0]==1){
                    isind=true;
                }
            }
            _is_independent.push_back(isind);
            if(isind){
                independent_index.push_back(indnumber);
                ++indnumber;
                independent_general_index.push_back(i);
            }else{
                independent_index.push_back(-1);
            }
        }
        //cout<<"independent"<<endl;
        //cout<<_is_independent<<endl;

        //cout<<"independent_general_index="<<independent_general_index<<endl;

        //for(int i=0;i<_nfreq;++i){
        //    vector<int> cv=children(i);
        //    cout<<_frequencies[i]<<" "<<is_independent(i)<<" c: "<<cv<<" -- "<<independent_index[i]<<" "<<endl;
        //}

    }else{
        cout<<"nfreq != nmatrix"<<endl;
    }
}


bool Frequency_manager::is_independent(int ind){
    bool r=false;
    if(ind<_is_independent.size()){
        r=_is_independent[ind];
    }
    return(r);
}

vector<int> Frequency_manager::children(int ind){
    vector<int> r;
    if(is_independent(ind)){
        int indep_ind=independent_index[ind];
        //cout<<"indep_ind="<<indep_ind<<endl;
        for(int i=0;i<_nfreq;++i){
               if(_matrix[i].size()>indep_ind){
                  if(_matrix[i][indep_ind]!=0){
                      if(i!=ind){
                          r.push_back(i);
                      }
                  }
               }
        }
    }
    return (r);
}


vector<int> Frequency_manager::parents(int ind){
    vector<int> r;
    if(!is_independent(ind)){
       for(int i=0;i<_matrix[ind].size();++i){
             if(_matrix[ind][i]!=0){
                   r.push_back(independent_general_index[i]);
              }

       }

    }
    return(r);
}
int Frequency_manager::index_of_independent_freq(int ind){
    return(independent_index[ind]);
}

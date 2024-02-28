#include "sort_pwh.hpp"

typedef double T;




//  Left source half is A[ iBegin:iMiddle-1].
// Right source half is A[iMiddle:iEnd-1   ].
// Result is            B[ iBegin:iEnd-1   ].

void TopDownMerge3(typename vector<T>::iterator A, size_t iBegin, size_t iMiddle, size_t iEnd, typename vector<T>::iterator B){
    size_t i = iBegin, j = iMiddle;

    // While there are elements in the left or right runs...
    typename vector<T>::iterator itB=B+iBegin;
    typename vector<T>::iterator itBe=B+iEnd;
    typename vector<T>::iterator itAi=A+iBegin;
    typename vector<T>::iterator itAj=A+iMiddle;

    for (; itB < itBe;itB++) {
        // If left run head exists and is <= existing right run head.
        if (i < iMiddle && (j >= iEnd || *itAi <= *itAj)) {
            *itB = *itAi;
            i = i + 1;
            itAi++;
        } else {
            *itB = *itAj;
            j = j + 1;
            itAj++;
        }
    }
}
void TopDownSplitMerge3(typename vector<T>::iterator B, size_t iBegin, size_t iEnd, typename vector<T>::iterator A){

    if(iEnd - iBegin < 2) {                      // if run size == 1
        return;                                 //   consider it sorted
    }
    // split the run longer than 1 item into halves
    size_t iMiddle = (iEnd + iBegin) / 2;              // iMiddle = mid point
    // recursively sort both runs from array A[] into B[]
    TopDownSplitMerge3(A, iBegin,  iMiddle, B);  // sort the left  run
    TopDownSplitMerge3(A, iMiddle,    iEnd, B);  // sort the right run
    // merge the resulting runs from array B[] into A[]
    TopDownMerge3(B, iBegin, iMiddle, iEnd, A);
}
// Array A[] has the items to sort; array B[] is a work array.

void f_sort_mi(vector<T> &A){//iterator to the begining and end of tha A table
    //size_t n=distance(A0,Ae);
    //cout<<"n="<<n<<endl;
    vector<T> B(A.size());//=A;     // duplicate array A[] into B[]
    for(typename vector<T>::iterator it=A.begin(),itB=B.begin();it<A.end();it++,itB++){
      *itB=*it;
    }
    //cout<<"B:="<<B<<endl;
    TopDownSplitMerge3(B.begin(), 0, A.size(), A.begin());   // sort data from B[] into A[]
}


//void f_sort_m4(T A0, T Ae){//iterator to the begining and end of tha A table
void f_sort_mi(T type, typename vector<T>::iterator A0, typename vector<T>::iterator Ae){//iterator to the begining and end of tha A table
    size_t n=distance(A0,Ae);
    //cout<<"n="<<n<<endl;
    //typename vector<T>::iterator it;
    vector<T> B(n);     // duplicate array A[] into B[]
    for(typename vector<T>::iterator it=A0,itB=B.begin();it<Ae;it++,itB++){
      *itB=*it;
    }
    //cout<<"B:="<<B<<endl;
    TopDownSplitMerge3(B.begin(), 0, n, A0);   // sort data from B[] into A[]
}//*/


void f_sort(vector<T> &x, vector<T> &y){
    typename vector<T>::iterator itx;
    typename vector<T>::iterator ity;
	typename vector<T>::iterator itx2;
	typename vector<T>::iterator ity2;
    typename vector<T>::iterator itxe=x.end();
    
	for(itx=x.begin(),ity=y.begin();itx<itxe;itx++,ity++){
	  //if(ity>=y.end())f_alert(" Mess in vector sizes; y size is not equal to x size");
	  for(itx2=itx+1,ity2=ity+1;itx2<itxe;itx2++,ity2++){
         //if(ity>=y.end())f_alert(" Mess in vector sizes; y size is not equal to x size");
	     if((*itx2)<(*itx)){
			 swap(*itx,*itx2); 
			 swap(*ity,*ity2);
			 //swap(indx[i],indx[j]);
			 //swap(indy[i],indy[j]);
		 }
		 
	  }
	  //cout<<"x="<<*itx<<" y="<<*ity<<" "<<" cov="<<covv<<" n="<<n<<endl;  
	}
}

void f_sort(vector<T> &x){
    typename vector<T>::iterator itx,itx2,itxe=x.end();
    for(itx=x.begin();itx<itxe;itx++){
	    for(itx2=itx+1;itx2<itxe;itx2++){
	     if((*itx2)<(*itx)){
			 swap(*itx,*itx2); 
		 }
		 
	  }
	  //cout<<"x="<<*itx<<" y="<<*ity<<" "<<" cov="<<covv<<" n="<<n<<endl;  
	}
}


void f_sort(vector<T> &x, vector<T> &y, vector<T> &z){
    typename vector<T>::iterator itx;
    typename vector<T>::iterator ity;
	typename vector<T>::iterator itz;
	typename vector<T>::iterator itx2;
	typename vector<T>::iterator ity2;
    typename vector<T>::iterator itz2;
	typename vector<T>::iterator itxe=x.end();
    
	for(itx=x.begin(),ity=y.begin(),itz=z.begin();itx<itxe;itx++,ity++,itz++){
	  //if(ity>=y.end())f_alert(" Mess in vector sizes; y size is not equal to x size");
	  for(itx2=itx+1,ity2=ity+1,itz2=itz+1;itx2<itxe;itx2++,ity2++,itz2++){
	     //if(ity>=y.end())f_alert(" Mess in vector sizes; y size is not equal to x size"); 
	     if((*itx2)<(*itx)){
			 swap(*itx,*itx2); 
			 swap(*ity,*ity2);
			 swap(*itz,*itz2);
			 //swap(indx[i],indx[j]);
			 //swap(indy[i],indy[j]);
		 }
		 
	  }
	  //cout<<"x="<<*itx<<" y="<<*ity<<" "<<" cov="<<covv<<" n="<<n<<endl;  
	}
}




//  Left source half is A[ iBegin:iMiddle-1].
// Right source half is A[iMiddle:iEnd-1   ].
// Result is            B[ iBegin:iEnd-1   ].
void TopDownMerge(vector<T> &A, size_t iBegin, size_t iMiddle, size_t iEnd, vector<T> &B){
    size_t i = iBegin, j = iMiddle,k;
    
    // While there are elements in the left or right runs...
    for (k = iBegin; k < iEnd; k++) {
        // If left run head exists and is <= existing right run head.
        if (i < iMiddle && (j >= iEnd || A[i] <= A[j])) {
            B[k] = A[i];
            i = i + 1;
        } else {
            B[k] = A[j];
            j = j + 1;    
        }
    } 
}
// Sort the given run of array A[] using array B[] as a source.
// iBegin is inclusive; iEnd is exclusive (A[iEnd] is not in the set).
void TopDownSplitMerge(vector<T> &B, size_t iBegin, size_t iEnd, vector<T> &A){
	
    if(iEnd - iBegin < 2) {                      // if run size == 1
        return;                                 //   consider it sorted
	}
    // split the run longer than 1 item into halves
    size_t iMiddle = (iEnd + iBegin) / 2;              // iMiddle = mid point
    // recursively sort both runs from array A[] into B[]
    TopDownSplitMerge(A, iBegin,  iMiddle, B);  // sort the left  run
    TopDownSplitMerge(A, iMiddle,    iEnd, B);  // sort the right run
    // merge the resulting runs from array B[] into A[]
    TopDownMerge(B, iBegin, iMiddle, iEnd, A);
}
// Array A[] has the items to sort; array B[] is a work array.
void f_sort_m(vector<T> &A){
	size_t n=A.size();
	vector<T> B=A;     // duplicate array A[] into B[]
    TopDownSplitMerge(B, 0, n, A);   // sort data from B[] into A[]
}




//  Left source half is A[ iBegin:iMiddle-1].
// Right source half is A[iMiddle:iEnd-1   ].
// Result is            B[ iBegin:iEnd-1   ].
void TopDownMerge2(vector<T> &A, size_t iBegin, size_t iMiddle, size_t iEnd, vector<T> &B){
    size_t i = iBegin, j = iMiddle;
    
    // While there are elements in the left or right runs...
    typename vector<T>::iterator itB=B.begin()+iBegin;	
	typename vector<T>::iterator itBe=B.begin()+iEnd;	
	typename vector<T>::iterator itAi=A.begin()+iBegin;
	typename vector<T>::iterator itAj=A.begin()+iMiddle;
	
    for (; itB < itBe;itB++) {
        // If left run head exists and is <= existing right run head.
        if (i < iMiddle && (j >= iEnd || *itAi <= *itAj)) {
            *itB = *itAi;
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
void TopDownSplitMerge2(vector<T> &B, size_t iBegin, size_t iEnd, vector<T> &A){
	
    if(iEnd - iBegin < 2) {                      // if run size == 1
        return;                                 //   consider it sorted
	}
    // split the run longer than 1 item into halves
    size_t iMiddle = (iEnd + iBegin) / 2;              // iMiddle = mid point
    // recursively sort both runs from array A[] into B[]
    TopDownSplitMerge2(A, iBegin,  iMiddle, B);  // sort the left  run
    TopDownSplitMerge2(A, iMiddle,    iEnd, B);  // sort the right run
    // merge the resulting runs from array B[] into A[]
    TopDownMerge2(B, iBegin, iMiddle, iEnd, A);
}
// Array A[] has the items to sort; array B[] is a work array.
void f_sort_m2(vector<T> &A){//iterator to the begining and end of tha A table
	//size_t n=distance(A0,Ae);
	//cout<<"n="<<n<<endl;
	vector<T> B=A;
	//vector<T> B(A.size());//=A;     // duplicate array A[] into B[]
	//for(typename vector<T>::iterator it=A.begin(),itB=B.begin();it<A.end();it++,itB++){ //this is faster than vector<T>B=A !!
	//  *itB=*it;	
	//}
	//cout<<"B:="<<B<<endl;
    TopDownSplitMerge2(B, 0, A.size(), A);   // sort data from B[] into A[]
}




//  Left source half is A[ iBegin:iMiddle-1].
// Right source half is A[iMiddle:iEnd-1   ].
// Result is            B[ iBegin:iEnd-1   ].
void TopDownMerge(vector<T> &A,vector<T> &C, size_t iBegin, size_t iMiddle, size_t iEnd, vector<T> &B,vector<T> &D){
    size_t i = iBegin, j = iMiddle,k;

    // While there are elements in the left or right runs...
    for (k = iBegin; k < iEnd; k++) {
        // If left run head exists and is <= existing right run head.
        if (i < iMiddle && (j >= iEnd || A[i] <= A[j])) {
            B[k] = A[i];
            D[k]= C[i];
            i = i + 1;
        } else {
            B[k] = A[j];
            D[k] = C[j];
            j = j + 1;
        }
    }
}
// Sort the given run of array A[] using array B[] as a source.
// iBegin is inclusive; iEnd is exclusive (A[iEnd] is not in the set).
void TopDownSplitMerge(vector<T> &B,vector<T> &D, size_t iBegin, size_t iEnd, vector<T> &A,vector<T> &C){

    if(iEnd - iBegin < 2) {                      // if run size == 1
        return;                                 //   consider it sorted
    }
    // split the run longer than 1 item into halves
    size_t iMiddle = (iEnd + iBegin) / 2;              // iMiddle = mid point
    // recursively sort both runs from array A[] into B[]
    TopDownSplitMerge(A,C, iBegin,  iMiddle, B,D);  // sort the left  run
    TopDownSplitMerge(A,C, iMiddle,    iEnd, B,D);  // sort the right run
    // merge the resulting runs from array B[] into A[]
    TopDownMerge(B,D, iBegin, iMiddle, iEnd, A,C);
}
void f_sort_m(vector<T> &A,vector<T> &C){//sort data from A and C according to A
    size_t n=A.size();
    vector<T> B=A;     // duplicate array A[] into B[]
    vector<T> D=C;     // duplicate array A[] into B[]
    TopDownSplitMerge(B,D, 0, n, A,C);   // sort data from B[] and D into A[] and C
}


//  Left source half is A[ iBegin:iMiddle-1].
// Right source half is A[iMiddle:iEnd-1   ].
// Result is            B[ iBegin:iEnd-1   ].
void TopDownMerge(vector<vector<T> > &A,vector<vector<T> > &C, size_t iBegin, size_t iMiddle, size_t iEnd, vector<vector<T> > &B,vector<vector<T> > &D){
    size_t i = iBegin, j = iMiddle,k;

    // While there are elements in the left or right runs...
    for (k = iBegin; k < iEnd; k++) {
        // If left run head exists and is <= existing right run head.
        if (i < iMiddle && (j >= iEnd || A[i] <= A[j])) {
            B[k] = A[i];
            D[k]= C[i];
            i = i + 1;
        } else {
            B[k] = A[j];
            D[k] = C[j];
            j = j + 1;
        }
    }
}
// Sort the given run of array A[] using array B[] as a source.
// iBegin is inclusive; iEnd is exclusive (A[iEnd] is not in the set).
void TopDownSplitMerge(vector<vector<T> > &B,vector<vector<T> > &D, size_t iBegin, size_t iEnd, vector<vector<T> > &A,vector<vector<T> > &C){

    if(iEnd - iBegin < 2) {                      // if run size == 1
        return;                                 //   consider it sorted
    }
    // split the run longer than 1 item into halves
    size_t iMiddle = (iEnd + iBegin) / 2;              // iMiddle = mid point
    // recursively sort both runs from array A[] into B[]
    TopDownSplitMerge(A,C, iBegin,  iMiddle, B,D);  // sort the left  run
    TopDownSplitMerge(A,C, iMiddle,    iEnd, B,D);  // sort the right run
    // merge the resulting runs from array B[] into A[]
    TopDownMerge(B,D, iBegin, iMiddle, iEnd, A,C);
}
void f_sort_m(vector<vector<T> > &A,vector<vector<T> > &C){//sort data from A and C according to A
    size_t n=A.size();
    vector<vector<T> > B=A;     // duplicate array A[] into B[]
    vector<vector<T> > D=C;     // duplicate array A[] into B[]
    TopDownSplitMerge(B,D, 0, n, A,C);   // sort data from B[] and D into A[] and C
}



//  Left source half is A[ iBegin:iMiddle-1].
// Right source half is A[iMiddle:iEnd-1   ].
// Result is            B[ iBegin:iEnd-1   ].
void TopDownMerge4(typename vector<T>::iterator A,typename vector<T>::iterator C, size_t iBegin, size_t iMiddle, size_t iEnd, typename vector<T>::iterator B,typename vector<T>::iterator D){
    size_t i = iBegin, j = iMiddle;
    
    // While there are elements in the left or right runs...
    typename vector<T>::iterator itB=B+iBegin;
    typename vector<T>::iterator itD=D+iBegin;
    typename vector<T>::iterator itBe=B+iEnd;
    typename vector<T>::iterator itAi=A+iBegin;
    typename vector<T>::iterator itAj=A+iMiddle;
    typename vector<T>::iterator itCi=C+iBegin;
    typename vector<T>::iterator itCj=C+iMiddle;
  
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
void TopDownSplitMerge4(vector<T> B,vector<T> D, size_t iBegin, size_t iEnd, vector<T> A, vector<T> C){
	
    if(iEnd - iBegin < 2) {                      // if run size == 1
        return;                                 //   consider it sorted
	}
    // split the run longer than 1 item into halves
    size_t iMiddle = (iEnd + iBegin) / 2;              // iMiddle = mid point
    // recursively sort both runs from array A[] into B[]
    TopDownSplitMerge4(A,C, iBegin,  iMiddle, B,D);  // sort the left  run
    TopDownSplitMerge4(A,C, iMiddle,    iEnd, B,D);  // sort the right run
    // merge the resulting runs from array B[] into A[]
    TopDownMerge4(B.begin(),D.begin(), iBegin, iMiddle, iEnd, A.begin(),C.begin());
}

void f_sort_mi(vector<T> &A,vector<T> &C){//sort data from A and C according to A
	size_t n=A.size();
	vector<T> B=A;     // duplicate array A[] into B[]
    vector<T> D=C;     // duplicate array A[] into B[]
    TopDownSplitMerge4(B,D, 0, n, A,C);   // sort data from B[] and D into A[] and C
}







//  Left source half is A[ iBegin:iMiddle-1].
// Right source half is A[iMiddle:iEnd-1   ].
// Result is            B[ iBegin:iEnd-1   ].
void TopDownMerge(vector<T> &A,vector<T> &C,vector<T> &E, size_t iBegin, size_t iMiddle, size_t iEnd, vector<T> &B,vector<T> &D,vector<T> &F){
    size_t i = iBegin, j = iMiddle,k;
    
    // While there are elements in the left or right runs...
    for (k = iBegin; k < iEnd; k++) {
        // If left run head exists and is <= existing right run head.
        if (i < iMiddle && (j >= iEnd || A[i] <= A[j])) {
            B[k] = A[i];
			D[k] = C[i];
			F[k] = E[i];
            i = i + 1;
        } else {
            B[k] = A[j];
            D[k] = C[j];
			F[k] = E[j];
            j = j + 1;    
        }
    } 
}
// Sort the given run of array A[] using array B[] as a source.
// iBegin is inclusive; iEnd is exclusive (A[iEnd] is not in the set).
void TopDownSplitMerge(vector<T> &B,vector<T> &D,vector<T> &F, size_t iBegin, size_t iEnd, vector<T> &A,vector<T> &C,vector<T> &E){
	
    if(iEnd - iBegin < 2) {                      // if run size == 1
        return;                                 //   consider it sorted
	}
    // split the run longer than 1 item into halves
    size_t iMiddle = (iEnd + iBegin) / 2;              // iMiddle = mid point
    // recursively sort both runs from array A[] into B[]
    TopDownSplitMerge(A,C,E, iBegin,  iMiddle, B,D,F);  // sort the left  run
    TopDownSplitMerge(A,C,E, iMiddle,    iEnd, B,D,F);  // sort the right run
    // merge the resulting runs from array B[] into A[]
    TopDownMerge(B,D,F, iBegin, iMiddle, iEnd, A,C,E);
}
// Array A[] has the items to sort; array B[] is a work array.
void f_sort_m(vector<T> &A,vector<T> &C,vector<T> &E){//sort data from A, C and E according to A
	size_t n=A.size();
    vector<T> B=A;     // duplicate array A[] into B[]
    vector<T> D=C;     // duplicate array A[] into B[]
    vector<T> F=E;     // duplicate array A[] into B[]
    TopDownSplitMerge(B,D,F, 0, n, A,C,E);   // sort data from B[] and D into A[] and C
}



//  Left source half is A[ iBegin:iMiddle-1].
// Right source half is A[iMiddle:iEnd-1   ].
// Result is            B[ iBegin:iEnd-1   ].
void TopDownMerge4(typename vector<T>::iterator A,typename vector<T>::iterator C,typename vector<T>::iterator E, size_t iBegin, size_t iMiddle, size_t iEnd, typename vector<T>::iterator B,typename vector<T>::iterator D, typename vector<T>::iterator F){
    size_t i = iBegin, j = iMiddle;
    
    // While there are elements in the left or right runs...
    typename vector<T>::iterator itB=B+iBegin;
    typename vector<T>::iterator itD=D+iBegin;
    typename vector<T>::iterator itF=F+iBegin;
    typename vector<T>::iterator itBe=B+iEnd;
    typename vector<T>::iterator itAi=A+iBegin;
    typename vector<T>::iterator itAj=A+iMiddle;
    typename vector<T>::iterator itCi=C+iBegin;
    typename vector<T>::iterator itCj=C+iMiddle;
    typename vector<T>::iterator itEi=E+iBegin;
    typename vector<T>::iterator itEj=E+iMiddle;

	
	for (; itB < itBe; itB++,itD++,itF++) {
        // If left run head exists and is <= existing right run head.
        if (i < iMiddle && (j >= iEnd || *itAi <= *itAj)) {
            *itB = *itAi;
			*itD = *itCi;
            *itF = *itEi;
            i = i + 1;
			itAi++;
			itCi++;
			itEi++;
        } else {
            *itB = *itAj;
			*itD = *itCj;
			*itF = *itEj;
			j = j + 1; 
			itAj++;
			itCj++;
			itEj++;
        }
    } 
}
// Sort the given run of array A[] using array B[] as a source.
// iBegin is inclusive; iEnd is exclusive (A[iEnd] is not in the set).
void TopDownSplitMerge4(vector<T> B,vector<T> D, vector<T> F, size_t iBegin, size_t iEnd, vector<T> A, vector<T> C, vector<T> E){
	
    if(iEnd - iBegin < 2) {                      // if run size == 1
        return;                                 //   consider it sorted
	}
    // split the run longer than 1 item into halves
    size_t iMiddle = (iEnd + iBegin) / 2;              // iMiddle = mid point
    // recursively sort both runs from array A[] into B[]
    TopDownSplitMerge4(A,C,E, iBegin,  iMiddle, B,D,F);  // sort the left  run
    TopDownSplitMerge4(A,C,E, iMiddle,    iEnd, B,D,F);  // sort the right run
    // merge the resulting runs from array B[] into A[]
    TopDownMerge4(B.begin(),D.begin(),F.begin(), iBegin, iMiddle, iEnd, A.begin(),C.begin(),E.begin());
}
void f_sort_mi(vector<T> &A,vector<T> &C,vector<T> &E){//sort data from A and C according to A
	size_t n=A.size();
	vector<T> B=A;     // duplicate array A[] into B[]
    vector<T> D=C;     // duplicate array A[] into B[]
    vector<T> F=E;     // duplicate array A[] into B[]
    TopDownSplitMerge4(B,D,F, 0, n, A,C,E);   // sort data from B[] and D into A[] and C
}













//  Left source half is A[ iBegin:iMiddle-1].
// Right source half is A[iMiddle:iEnd-1   ].
// Result is            B[ iBegin:iEnd-1   ].
void TopDownMerge(vector<T> &A,vector<T> &C,vector<T> &E,vector<T> &G, size_t iBegin, size_t iMiddle, size_t iEnd, vector<T> &B,vector<T> &D,vector<T> &F,vector<T> &H){
    size_t i = iBegin, j = iMiddle,k;
    
    // While there are elements in the left or right runs...
    for (k = iBegin; k < iEnd; k++) {
        // If left run head exists and is <= existing right run head.
        if (i < iMiddle && (j >= iEnd || A[i] <= A[j])) {
            B[k] = A[i];
			D[k] = C[i];
			F[k] = E[i];
			H[k] = G[i];
            i = i + 1;
        } else {
            B[k] = A[j];
            D[k] = C[j];
			F[k] = E[j];
			H[k] = G[j];			
            j = j + 1;    
        }
    } 
}
// Sort the given run of array A[] using array B[] as a source.
// iBegin is inclusive; iEnd is exclusive (A[iEnd] is not in the set).
void TopDownSplitMerge(vector<T> &B,vector<T> &D,vector<T> &F,vector<T> &H, size_t iBegin, size_t iEnd, vector<T> &A,vector<T> &C,vector<T> &E,vector<T> &G){
	
    if(iEnd - iBegin < 2) {                      // if run size == 1
        return;                                 //   consider it sorted
	}
    // split the run longer than 1 item into halves
    size_t iMiddle = (iEnd + iBegin) / 2;              // iMiddle = mid point
    // recursively sort both runs from array A[] into B[]
    TopDownSplitMerge(A,C,E,G, iBegin,  iMiddle, B,D,F,H);  // sort the left  run
    TopDownSplitMerge(A,C,E,G, iMiddle,    iEnd, B,D,F,H);  // sort the right run
    // merge the resulting runs from array B[] into A[]
    TopDownMerge(B,D,F,H, iBegin, iMiddle, iEnd, A,C,E,G);
}
// Array A[] has the items to sort; array B[] is a work array.
void f_sort_m(vector<T> &A,vector<T> &C,vector<T> &E,vector<T> &G){//sort data from A, C and E according to A
	size_t n=A.size();
    vector<T> B=A;     // duplicate array A[] into B[]
    vector<T> D=C;     // duplicate array A[] into B[]
    vector<T> F=E;     // duplicate array A[] into B[]
    vector<T> H=G;     // duplicate array A[] into B[]
    TopDownSplitMerge(B,D,F,H, 0, n, A,C,E,G);   // sort data from B[] and D into A[] and C
}





//  Left source half is A[ iBegin:iMiddle-1].
// Right source half is A[iMiddle:iEnd-1   ].
// Result is            B[ iBegin:iEnd-1   ].
void TopDownMerge_r(vector<T> &A,vector<T> &C,vector<T> &E,vector<T> &G, size_t iBegin, size_t iMiddle, size_t iEnd, vector<T> &B,vector<T> &D,vector<T> &F,vector<T> &H){
    size_t i = iBegin, j = iMiddle,k;

    // While there are elements in the left or right runs...
    for (k = iBegin; k < iEnd; k++) {
        // If left run head exists and is <= existing right run head.
        if (i < iMiddle && (j >= iEnd || A[i] >= A[j])) {
            B[k] = A[i];
            D[k] = C[i];
            F[k] = E[i];
            H[k] = G[i];
            i = i + 1;
        } else {
            B[k] = A[j];
            D[k] = C[j];
            F[k] = E[j];
            H[k] = G[j];
            j = j + 1;
        }
    }
}
// Sort the given run of array A[] using array B[] as a source.
// iBegin is inclusive; iEnd is exclusive (A[iEnd] is not in the set).
void TopDownSplitMerge_r(vector<T> &B,vector<T> &D,vector<T> &F,vector<T> &H, size_t iBegin, size_t iEnd, vector<T> &A,vector<T> &C,vector<T> &E,vector<T> &G){

    if(iEnd - iBegin < 2) {                      // if run size == 1
        return;                                 //   consider it sorted
    }
    // split the run longer than 1 item into halves
    size_t iMiddle = (iEnd + iBegin) / 2;              // iMiddle = mid point
    // recursively sort both runs from array A[] into B[]
    TopDownSplitMerge_r(A,C,E,G, iBegin,  iMiddle, B,D,F,H);  // sort the left  run
    TopDownSplitMerge_r(A,C,E,G, iMiddle,    iEnd, B,D,F,H);  // sort the right run
    // merge the resulting runs from array B[] into A[]
    TopDownMerge_r(B,D,F,H, iBegin, iMiddle, iEnd, A,C,E,G);
}
// Array A[] has the items to sort; array B[] is a work array.
void f_sort_mr(vector<T> &A,vector<T> &C,vector<T> &E,vector<T> &G){//sort data from A, C and E according to A
    size_t n=A.size();
    vector<T> B=A;     // duplicate array A[] into B[]
    vector<T> D=C;     // duplicate array A[] into B[]
    vector<T> F=E;     // duplicate array A[] into B[]
    vector<T> H=G;     // duplicate array A[] into B[]
    TopDownSplitMerge_r(B,D,F,H, 0, n, A,C,E,G);   // sort data from B[] and D into A[] and C
}


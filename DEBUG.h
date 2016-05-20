#include <bits/stdc++.h>
using namespace std;
//#define NODEBUG
#ifdef NODEBUG
#define DEBUG($...) ;
#else
void DEBUG(){}template<class A,class...B>void DEBUG(A _,B...$){cerr<<' '<<_;DEBUG($...);}
#define DEBUG($...) DEBUG(#$,'=',$,'\n')
#endif

template <class T> ostream& operator << (ostream &os, const vector<T> &V) { 
    os << "[ "; 
    for (int i = 0; i < V.size(); i++) 
       os << (i? ", ": "") << V[i];
     os << " ]"; 
    return os; 
}

template <class T> ostream& operator << (ostream &os, const set<T> &S) { 
    os << "{ "; 
    for(auto it = (S).begin(); it!=(S).end(); it++) 
        os << ((it == (S).begin())? "": ", ") << (*it); 
    os << " }"; 
    return os; 
} 

template <class T> ostream& operator << (ostream &os, const multiset<T> &MS) {
    os << "{ "; 
    for(auto it = (MS).begin(); it!=(MS).end(); it++) 
        os << ((it == (MS).begin())? "":", ") << (*it); 
    os << " }"; 
    return os; 
} 

template <class S, class T> ostream& operator << (ostream &os, const pair<S,T> &P) {
    os << "(" << P.first << ", " << P.second << ")"; 
    return os; 
} 

template <class S, class T> ostream& operator << (ostream &os, const map<S,T> &MP) {
    os << "{ "; 
    for(auto it = (MP).begin(); it!=(MP).end(); it++) 
        os << ((it == (MP).begin())? "":", ") << (it->first) << "->" << (it->second); 
    os << " }"; 
    return os; 
}
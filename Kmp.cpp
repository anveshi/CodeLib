#include <bits/stdc++.h>
using namespace std;

#define TRACE
#ifdef TRACE
#define trace1(x)       cerr<< #x <<": "<<x<<endl;
#define trace2(x, y)    cerr<< #x <<": "<<x<<" | "<< #y <<": "<<y<< endl;
#define trace3(x, y, z) cerr<< #x <<": "<<x<<" | "<< #y <<": "<<y<<" | "<< #z <<": "<<z<< endl;
#else
#define trace1(x)
#define trace2(x, y)
#define trace3(x, y, z)
#endif

typedef long long LL;

void fastIO(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

vector <int> naive_prefix_function(string s){
  int n = (int)s.length();
  vector <int> pi(n,0);
  for(int i=0;i<n;i++){
    for(int k=0;k<=i;k++){
      // Values of k for given i, i = 0,1,2,..i (neglect 0) => only i-1 
      // ensuring no proper border
      // st+k-1 = i => st = i-k+1
      if(s.substr(0,k) == s.substr(i-k+1,k))  
        pi[i] = k;                         
    }
  }
  // this is O(n^3)
  return pi;
}

// e-maxx.ru http://e-maxx.ru/algo/prefix_function
vector <int> naive_KMP(const string& haystack, const string& needle){
  vector <int> ret;
  int m = (int)haystack.size();
  int n = (int)needle.size();
  for(int i=0;i+n<=m;i++){
    int j;
    for(j=0;j<n;j++){
      if(haystack[i+j]^needle[j])
        break;
    }
    if(j==n)
      ret.push_back(i);
  }
  return ret;
}

// Takes  string and return vector prefix_function of string
// pf[i] = maximum length proper prefix of S[0..i] that is suffix of S[0...i]

vector <int> Kmp_prefix_function(string s){
  int n = s.length();
  // p[i+1]<=p[i]+1
  vector <int> pi(n,0);
  for(int i=1;i<n;i++){
    int j = pi[i-1];
    while(j>0 && s[i]!=s[j])
      j = pi[j-1];
    if(s[i]==s[j])
      j++;
    pi[i] = j;   
  }
  return pi;
  //s="abcabcd" -> pi = {0,0,0,1,2,3,0};
  //s="aabaaab" -> pi = {0,1,0,1,2,2,3};
}

// takes 2 strings haystack and needle. returns vector that contains
// indexes such that haystack[idx.....idx+n-1] == needle.

vector <int> KMP(const string& haystack, const string& needle){
  vector <int> ret;
  int m = (int)haystack.size();
  int n = (int)needle.size();
  string S = needle + "#" + haystack; // [0,n-1][n][n+1,n+m]
  //trace1(S);
  vector <int> pf = Kmp_prefix_function(S);
  for(int i=n+1;i<=n+m;i++){
    if(pf[i]==n){
      int idx = i - (n+1) - n + 1; // starting index in haystack
      ret.push_back(idx);
    }
  }
  /*for(int i=0;i<ret.size();i++){
    assert(haystack.substr(ret[i],n)  == needle);
  }*/
  return ret;
}


int main(){  
  fastIO();
  string S;
  cin >> S;

  vector <int> ans1 = Kmp_prefix_function(S);
  vector <int> ans2 = naive_prefix_function(S);
  
  for(int i=0;i<ans1.size();i++)
    trace2(ans1.at(i),ans2.at(i));
  
  assert(ans1==ans2);
  return 0;
}

int main2(){
  fastIO();
  string S1,S2;
  cin >> S1 >> S2 ;
  
  vector <int> ans1 = KMP(S1,S2);
  vector <int> ans2 = naive_KMP(S1,S2);

  assert(ans1==ans2);
  
  for(int i=0;i<ans1.size();i++)
    trace2(ans1[i],ans2[i]);
  
  return 0;
}
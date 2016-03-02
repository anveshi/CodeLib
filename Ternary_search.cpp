#include <bits/stdc++.h>
using namespace std;

int const Maxn = 2*100000 + 5;
int n,a[Maxn];
double f(double x){
  
  // Kadane's algorithm 

  double cur_max1 = 0.0, global_max1 = 0.0;
  for(int i=0;i<n;i++){
    cur_max1 = max(0.0,cur_max1+a[i]-x);
    global_max1 = max(global_max1, cur_max1);  
  }

  double cur_max2 = 0.0, global_max2 = 0.0;
  for(int i=0;i<n;i++){
    cur_max2 = max(0.0, cur_max2-a[i]+x);
    global_max2 = max(global_max2, cur_max2);
  }

  return max (global_max1, global_max2);
}


double Ternary_search1(double a, double b){
  // Ternary search /\ type function  //
  double l = a, r = b;
  for(int i=0; i<200; i++) {
    double l1 = (l*2+r)/3;
    double l2 = (l+2*r)/3;
    if(f(l1) > f(l2)) r = l2; else l = l1;
  }
  return l;
}
double Ternary_search(double a, double b){
  // Ternary search \/ type function  //
  double l = a, r = b;
  for(int i=0; i<200; i++) {
    double l1 = (l*2+r)/3;
    double l2 = (l+2*r)/3;
    if(f(l1) < f(l2)) r = l2; else l = l1;
  }
  return l;
}

int main(){
  cin >> n;
  for(int i=0;i<n;i++)
    cin >> a[i];
  cout.precision(10);
  cout << fixed;
  double ans = f(Ternary_search(-20000.0, 200000.0));
  cout << ans << endl;
  return 0;
}

/*
on Integers
int lo = -1, hi = n;
while (hi - lo > 1){
    int mid = (hi + lo)>>1;
    if (f(mid) < f(mid + 1)) 
         hi = mid;
    else 
         lo = mid; 
}
//lo + 1 is the answer
*/
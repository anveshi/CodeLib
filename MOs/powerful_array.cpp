// Anve$hi $hukla
// http://codeforces.com/contest/86/problem/D
#include <bits/stdc++.h>
using namespace std;
// Mo's Algorithm
const int Maxn = 1000005;

inline void fastIO(){
   ios_base::sync_with_stdio(false);
   cin.tie(NULL);
}

typedef pair <int,int> pii;
typedef pair <pii, int> ppii;
int BLOCK_SIZE, A[Maxn], cnt[Maxn];  
long long cur_ans, Ans[Maxn]; 
ppii Query[Maxn];

inline bool Mo_cmp(ppii P1, ppii P2){
   int L1 = P1.first.first, R1 = P1.first.second;
   int L2 = P2.first.first, R2 = P2.first.second;
   int block_p1 = L1/BLOCK_SIZE;
   int block_p2 = L2/BLOCK_SIZE;
   if(block_p1 != block_p2)
      return block_p1 < block_p2;
   return R1 > R2;
}

inline void add(long long x){
   cur_ans -= (long long)(cnt[x]*(long long)cnt[x]*x);
   cnt[x]++;
   cur_ans += (long long)(cnt[x]*(long long)cnt[x]*x);
   return;
}

inline void remove(long long x){
   cur_ans -= (long long)(cnt[x]*(long long)cnt[x]*x);
   cnt[x]--;
   cur_ans += (long long)(cnt[x]*(long long)cnt[x]*x);
   return;
}

int main(){
   fastIO();
   int N,Q;
   cin >> N >> Q;

   BLOCK_SIZE = sqrt(N);
   for(int i=0;i<N;i++)
      cin >> A[i];

   for(int i=0;i<Q;i++){
      cin >> Query[i].first.first >> Query[i].first.second;
      Query[i].first.first--;
      Query[i].first.second--;
      Query[i].second = i; 
   }
   sort(Query, Query+Q, Mo_cmp);
   int mo_left = 0, mo_right = -1;
   
   for(int i=0;i<Q;i++){
      int left = Query[i].first.first, right = Query[i].first.second;

      while(mo_right < right){
         mo_right++;
         add(A[mo_right]);
      }
      while(mo_right > right){
         remove(A[mo_right]);
         mo_right--;
      }
      while(mo_left < left){
         remove(A[mo_left]);
         mo_left++;
      }
      while(mo_left > left){
         mo_left--;
         add(A[mo_left]);
      }
      Ans[Query[i].second] = cur_ans;
   }

   for(int i=0;i<Q;i++)
      cout << Ans[i] << endl;
   return 0;
}
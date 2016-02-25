// Anve$hi $hukla
// http://codeforces.com/problemset/problem/617/E
#include <bits/stdc++.h>
using namespace std;

const long long Maxn = 1LL<<21;

inline void fastIO(){
   ios_base::sync_with_stdio(false);
   cin.tie(NULL);
}

int SQN, K, A[Maxn], Cnt[Maxn], prefix[Maxn];
long long Ans[Maxn], CurAns;

struct query{
   int l, r, idx;
   bool operator < (const query &b) const{
      if(l/SQN != b.l/SQN)
         return(l/SQN < b.l/ SQN);
      return r > b.r;
   }
} Query[Maxn];

void Update(int x, long long val){
   val < 0 ? Cnt[x]-- : 0;
   CurAns += ((val)*Cnt[x^K]);
   Cnt[x]++;
   return;
}

void Add(int x){
   //Update(x, 1);
   CurAns += Cnt[x^K];
   Cnt[x]++;
   return;
}
void Remove(int x){
   //Update(x, -1)
   Cnt[x]--;
   CurAns -= Cnt[x^K];
   return;
}

int main(){
   fastIO();
   int N, Q, L, R;
   cin >> N >> Q >> K;
   SQN = sqrt(N);
   for(int i=0;i<N;i++){
      cin >> A[i];
      prefix[i] = (i==0?A[i]:prefix[i-1]^A[i]);
   }
   for(int i=0;i<Q;i++){
      cin >> L >> R;
      Query[i].l = L - 2;
      Query[i].r = R - 1;
      Query[i].idx = i;
   }
   sort(Query, Query + Q);
   int mo_left = 0, mo_right = -1;

   for(int i=0;i<Q;i++){
      int left = Query[i].l, right = Query[i].r;
      while(mo_left < left){
         Remove(prefix[mo_left]);
         mo_left++;
      }
      while(mo_left > left){
         mo_left--;
         Add(prefix[mo_left]);
      }
      while(mo_right < right){
         mo_right++;
         Add(prefix[mo_right]);
      }
      while(mo_right > right){
         Remove(prefix[mo_right]);
         mo_right--;
      }
      Ans[Query[i].idx] = CurAns;
   }
   for(int i=0;i<Q;i++)
      cout << Ans[i] << '\n';
   
   return 0;
}
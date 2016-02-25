// Anve$hi $hukla
// http://codeforces.com/contest/220/problem/B
#include <bits/stdc++.h>
using namespace std;

const int Maxn = 100005;
int BLOCK_SIZE, Ans[Maxn], A[Maxn];

struct MOQuery{
    int l;
    int r;
    int idx;
    bool operator < (const MOQuery &b) const {
        return ( (l / BLOCK_SIZE) == (b.l / BLOCK_SIZE) ) ? r < b.r : l < b.l;
    }
};
MOQuery Query[Maxn]; 

class Mo{
   private:
      int Cnt[Maxn];
      int CurAns;
   public:
      Mo(){
         memset(Cnt, 0, sizeof Cnt);
         CurAns = 0;
      }
      void Add(int x){
         if(x >= Maxn)
            return;
         if(Cnt[x] == x)
            CurAns--;
         Cnt[x]++;
         if(Cnt[x] == x)
            CurAns++;
      }
      void Remove(int x){
         if(x >= Maxn)
            return;
         if(Cnt[x] == x)
            CurAns--;
         Cnt[x]--;
         if(Cnt[x] == x)
            CurAns++;
      }
      int get_answer(){
         return CurAns;
      }
};

int main(){
   int N, L, R, Q;
   scanf("%d %d",&N, &Q);
   BLOCK_SIZE = sqrt(N);
   for(int i=0;i<N;i++)
      scanf("%d",&A[i]);

   for(int i=0;i<Q;i++){
      scanf("%d %d",&L, &R);
      Query[i].l = L-1;
      Query[i].r = R-1;
      Query[i].idx = i;
   }

   sort(Query, Query + Q);
   Mo Mosolver;
   int mo_left = 0, mo_right = -1;
   for(int i=0;i<Q;i++){
      int left = Query[i].l, right = Query[i].r;
      while(mo_left < left){
         Mosolver.Remove(A[mo_left]);
         mo_left++;
      }
      while(mo_left > left){
         mo_left--;
         Mosolver.Add(A[mo_left]);
      }
      while(mo_right < right){
         mo_right++;
         Mosolver.Add(A[mo_right]);
      }
      while(mo_right > right){
         Mosolver.Remove(A[mo_right]);
         mo_right--;
      }
      Ans[Query[i].idx] = Mosolver.get_answer();
   }
   for(int i=0;i<Q;i++)
      printf("%d\n",Ans[i]);
   return 0;
}
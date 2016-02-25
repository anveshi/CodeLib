// Anve$hi $hukla
// http://www.spoj.com/problems/DQUERY/
#include <bits/stdc++.h>
using namespace std;

const int Maxn = 1000005;
int A[30003];
typedef pair<int, int> pii;
typedef pair<pii, int> ppii;

ppii Query[200000]; 
int BLOCK_SIZE, Ans[Maxn];

inline bool Mo_cmp(ppii X, ppii Y){
   int block1 = X.first.first / BLOCK_SIZE;
   int block2 = Y.first.first / BLOCK_SIZE;
   if(block1 != block2)
      return block1 < block2;
   return X.first.second > Y.first.second;
}
class Mo{
   private:
      int Cnt[Maxn], CurAns;
   public:
      Mo(){
         memset(Cnt, 0, sizeof Cnt);
         CurAns = 0;
      }
      void Add(int x){
         Cnt[x]++;
         if(Cnt[x] == 1)
            CurAns++;
      }
      void Remove(int x){
         Cnt[x]--;
         if(Cnt[x] == 0)
            CurAns--;
      }
      int get_answer(){
         return CurAns;
      }
};
int main(){
   int N, L, R, Q;
   scanf("%d",&N);
   BLOCK_SIZE = sqrt(N);
   for(int i=0;i<N;i++)
      scanf("%d",&A[i]);
   scanf("%d",&Q);
   for(int i=0;i<Q;i++){
      scanf("%d %d",&L, &R);
      Query[i].first.first = L-1;
      Query[i].first.second = R-1;
      Query[i].second = i;
   }
   sort(Query, Query + Q, Mo_cmp);
   Mo Mosolver;
   int mo_left = 0, mo_right = -1;
   for(int i=0;i<Q;i++){
      int left = Query[i].first.first, right = Query[i].first.second;
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
      Ans[Query[i].second] = Mosolver.get_answer();
   }
   for(int i=0;i<Q;i++)
      printf("%d\n",Ans[i]);
   return 0;
}
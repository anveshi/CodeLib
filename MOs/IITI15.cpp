// Anve$hi $hukla
// http://www.codechef.com/problems/IITI15
#include <bits/stdc++.h>
using namespace std;
const int Maxn = 20005;
struct ${$(){ios_base::sync_with_stdio(0);cin.tie(NULL);}}$;
int SQN, tree[Maxn];

void update(int idx, int val){
   while(idx < Maxn){
      tree[idx] += val;
      idx += idx & -idx;
   }
   return;
}

int read(int idx){
   int Ret;
   while(idx > 0){
      Ret += tree[idx];
      idx -= idx & -idx;
   }
   return Ret;
}

vector <int> A;
map <int, int> M;
long long Ans[Maxn], CurAns;

struct query{
   int l,r,idx;
   bool operator < (const query &b) const{
      if(l/SQN != b.l/SQN)
         return (l/SQN) < (b.l/SQN);
      return r > b.r;
   }
} Query[Maxn];

int main(){
   int N, Q;
   cin >> N;
   SQN = sqrt(N);
   A.resize(N);
   for(int i=0;i<N;i++)
      cin >> A[i];
   
   set <int> B(A.begin(), A.end());
   auto available = 1;
   for(auto x: B)
      M[x] = available++;
   
   for(int i=0;i<N;i++)
      A[i] = M[A[i]];
   
   cin >> Q;
   for(int i=0;i<Q;i++){
      cin >> Query[i].l >> Query[i].r;
      Query[i].l--, Query[i].r--, Query[i].idx = i;
   }

   sort(Query, Query+Q);

   int mo_left = 0, mo_right = -1;   
   for(int i=0;i<Q;i++){

      int left = Query[i].l, right = Query[i].r;
      while(mo_left < left){
         int ret = read(A[mo_left] - 1);
         CurAns -= ret;
         update(A[mo_left], -1);
         mo_left++;

      }
      while(mo_left > left){
         mo_left--;
         update(A[mo_left], 1);
         int ret = read(A[mo_left] - 1);
         CurAns += ret;         
      }
      while(mo_right < right){
         mo_right++;
         update(A[mo_right], 1);
         int ret = read(A[mo_right]);
         CurAns += (mo_right - mo_left + 1) - ret;
      }
      while(mo_right > right){
         int ret = read(A[mo_right]);
         CurAns -= (mo_right - mo_left + 1) - ret;
         update(A[mo_right], -1);
         mo_right--;
      }
      Ans[Query[i].idx] = CurAns;
   }
   for(int i=0;i<Q;i++)
      cout << Ans[i] << endl;
   return 0;
}
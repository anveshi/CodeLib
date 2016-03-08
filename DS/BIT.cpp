#include <bits/stdc++.h>
using namespace std;

class BIT{
  // 1 indexed

  int *tree, sz; 
  public:
  BIT(){
    sz = 200005;
    tree = new int[sz+1];
  }
  BIT(int N) {
    sz = N;
    tree = new int[N+1];
  }

  ~BIT() {
    delete [] tree;
  }

  // Update idx'th element by Val 
  // increment or decrement idx'th element by Val 
  void update(int idx, int Val){
    if(idx<1 || idx>sz)
      return;
    while(idx<=sz){
      tree[idx] += Val;
      idx += idx&-idx;
    }
  }

  // returns sum of range[1.....idx]

  int read(int idx){
    int Sum = 0;
    while(idx>0){
      Sum += tree[idx];
      idx -= (idx&-idx);
    }
    return Sum;
  }

  // returns sum of range[l.....r]
  int rangeSum(int l, int r){
    return read(r) - read(l-1);
  }

  // returns same as 
  // RangeSum(idx,idx) or read(idx) - read(idx-1)
  // O(log(n)); instead of 2*O(log(n))

  int readSingle(int idx){
    int sum = tree[idx]; // sum will be decreased
    if (idx > 0){ // special case
      int z = idx - (idx & -idx); // make z first
      idx--; // idx is no important any more, so instead y, you can use idx
      while (idx != z){ // at some iteration idx (y) will become z
        sum -= tree[idx]; 
        // substruct tree frequency which is between y and "the same path"
        idx -= (idx & -idx);
      }
    }
    return sum;
  }

  int size(){
    return sz;
  }
};

int main(){
  int Maxn = 100;
  BIT b(Maxn);

  assert(b.read(b.size())==0);
  for(int i=1;i<=b.size();i++){
    b.update(i,i*i);
  }
  for(int i=0;i<=b.size();i++){
    assert(b.readSingle(i) == b.rangeSum(i,i));
    assert(b.readSingle(i) == i*i);
  }
  for(int i=0;i<=b.size();i++){
    for(int j=i;j<=b.size();j++){
      int val = b.rangeSum(i,j);
      int temp = 0;
      for(int k=i;k<=j;k++)temp+=k*k;
      assert(temp==val);
    }
  }
  return 0;
}

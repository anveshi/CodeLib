// Anve$hi $hukla

#include <bits/stdc++.h>
using namespace std;
#define SWAP(a, b) (((a) ^= (b)), ((b) ^= (a)), ((a) ^= (b)))

struct ${$(){ios_base::sync_with_stdio(false);cin.tie(NULL);}}$;
typedef long long LL;
const int Maxn = 200005;

unsigned snoob(unsigned int x){   // Next number with same number of set bits
   unsigned int smallest, ripple, ones;
   smallest = x & -x;
   ripple = x + smallest;
   ones = x ^ ripple;
   ones = (ones >> 2)/smallest;
   return ripple | ones;
}

string toBits(unsigned long long x){
   bitset <64> B(x);
   stringstream S; 
   S << B;
   string Ret;
   S >> Ret;
   cout << Ret << endl;
   return Ret;
}

void printBits(unsigned long long x){
   bitset <64> B(x);
   cout << B << endl;
}

bool isPoweofTwo(unsigned long long x){
   return __builtin_popcountll(x) == 1;
   //return (x && (!(x&(x-1))));
}

bool samesign(long long x, long long y){
   return ((x^y) >= 0); // 0 is considered as +ve sign here
}

long long Min(long long x, long long y){
   return (y ^ ((x ^ y) & -(x < y)));
}

long long Max(long long x, long long y){
   return (x ^ ((x ^ y) & -(x < y)));
}

int CountSetBits(unsigned long long x){
   int t = __builtin_popcountll(x);
   unsigned int c;      // c accumulates the total bits set in x
   for (c = 0; x; c++)
      x &= x - 1;       // clear the least significant bit set
   return c; 
}

int Log(unsigned long long x){
   unsigned long long t = log2(x);     // x==0 log2(x) is not defined
   unsigned long long r = 0;           // r will be log(x)
   while (x >>= 1) {
      r++;
   }
   assert(r == t || x<=0);
   return r;
}

unsigned int higher_power_of_two(unsigned int v){ // v>1
   // compute the next highest power of 2 which is >=v 
   v--;  
   v |= v >> 1;
   v |= v >> 2;
   v |= v >> 4;
   v |= v >> 8;
   v |= v >> 16;
   v++;
   return v;
}
int lower_power_of_two(unsigned int v) { // v>1
   // computes previous power of 2 which is strictly less than v
   return (higher_power_of_two(v))>>1;
}

int main(){

   unsigned long long x = 174;                    // 10101110
   printBits(x); 
   printBits(-x);                //    -x == ~(x-1)
   printBits(x & (x-1));        //    Remove the smallest element/bit from x:
   printBits(x&~(x-1));        //    Remove all but the smallest element from x: Lsb of x
   printBits(x&-x);           //    (x&-x == (x&~(x-1))) ==> lsb with 1

   unsigned long long trailing = __builtin_ctz(x);   //  Trailing zeros
   unsigned long long leading = __builtin_clz(x); //  leading zeros Note: return value is undefined for argument 0
   unsigned long long nos = __builtin_popcount(x);

   cout << trailing << " " << leading << " " << nos << endl;
   for(int i=1;i<10000;i++){
      assert(-i == ~(i-1));
      assert((1<<(__builtin_ctz(i))) == (i&-i)); // not true for i = 0
      assert((i&-i) == (i&(~(i-1))));
   }
   x = 7;
   while(x<20){
      x = snoob(x);
      printBits(x);
   }
   x = (1LL<<39) - 1;
   cout << (__builtin_popcountll(x)) << " ";
   cout << (__builtin_ctzll(x)) << " ";
   cout << (__builtin_clzll(x)) << endl;
   
   for(int i=2;i<10;i++){
      cout << lower_power_of_two(i)  <<  " " << i << " " << higher_power_of_two(i) << endl;
   }
   return 0;
}
// A & ~B :: Set subtraction
// ((1 << N) - 1) & ~A ::  Set negation
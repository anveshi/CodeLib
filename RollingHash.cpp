//http://www.spoj.com/problems/NUMOFPAL/
// Anve$hi $hukla
#include <bits/stdc++.h>
using namespace std;
//#include "DEBUG.h"
const int Maxn = 5000005;

void fastIO(){
   ios_base::sync_with_stdio(false);
   cin.tie(NULL);
}

struct RollingHash1 {
   static const unsigned long long p = 1000000007ULL;
   string s;
   int n;
   vector <unsigned long long> pow, phash;
   RollingHash1(string s): s(s), n(s.length()), pow(n + 1), phash(n + 1) {
      pow[0] = 1;
      phash[0] = 0;
      for(int i = 0; i < n; i++) {
         phash[i + 1] = phash[i] * p + s[i];
         pow[i + 1] = pow[i] * p;
      }
   }
   unsigned long long getHash(int i) const {
      return phash[i];
   }
   unsigned long long getHash(int i, int j) const {
      return getHash(j + 1) - getHash(i) * pow[j - i + 1];
   }   
};

struct RollingHash2 {
   static const unsigned long long p1 = 1000000007ULL;
   static const unsigned long long p2 = 1000000009ULL;
   string s;
   int n;
   vector <unsigned long long> pow1, pow2, phash1, phash2;
   RollingHash2(string s): s(s), n(s.length()), pow1(n + 1), pow2(n + 1), phash1(n + 1), phash2(n + 1) {
      pow1[0] = 1, pow2[0] = 1;
      phash1[0] = 0, phash2[0] = 0;
      for(int i = 0; i < n; i++) {
         phash1[i + 1] = phash1[i] * p1 + s[i];
         phash2[i + 1] = phash2[i] * p2 + s[i];
         pow1[i + 1] = pow1[i] * p1;
         pow2[i + 1] = pow2[i] * p2;
      }
   }
   pair <unsigned long long, unsigned long long> getHash(int i) const {
      return {phash1[i], phash2[i]};
   }
   pair <unsigned long long, unsigned long long> getHash(int i, int j) const {
      return {getHash(j + 1).first - getHash(i).first * pow1[j - i + 1], getHash(j + 1).second - getHash(i).second * pow2[j - i + 1]};
   }
};

struct RollingHash3 {
   static const unsigned long long p = 1000000007ULL;
   string s;
   int n;
   vector <unsigned long long> pow, forHash, revHash;

   RollingHash3() {}
   RollingHash3(string s): s(s), n(s.length()), pow(n + 1), forHash(n + 1), revHash(n + 1) {
      pow[0] = 1;
      forHash[0] = 0;
      for(int i = 0; i < n; i++) {
         forHash[i + 1] = forHash[i] * p + s[i];
         pow[i + 1] = pow[i] * p;
      } 
      revHash[n] = 0;
      for(int i = n - 1; i >= 0; i--) {
         revHash[i] = revHash[i + 1] * p + s[i];
      }
   }
   void init(string s) {
      s = s; n = s.length(); pow.resize(n + 1); forHash.resize(n + 1); revHash.resize(n + 1);
      pow[0] = 1;
      forHash[0] = 0;
      for(int i = 0; i < n; i++) {
         forHash[i + 1] = forHash[i] * p + s[i];
         pow[i + 1] = pow[i] * p;
      } 
      revHash[n] = 0;
      for(int i = n - 1; i >= 0; i--) {
         revHash[i] = revHash[i + 1] * p + s[i];
      }
   }
   unsigned long long getForHash(int i) const {
      return forHash[i];
   }
   unsigned long long getRevHash(int i) const {
      return revHash[i];
   }
   unsigned long long getForHash(int i, int j) const {
      return getForHash(j + 1) - getForHash(i) * pow[j - i + 1];
   }
   unsigned long long getRevHash(int i, int j) const {
      return getRevHash(i) - getRevHash(j + 1) * pow[j - i + 1];
   }
   bool isPalindrome(int i, int j) {
      return (getForHash(i, j) == getRevHash(i, j));
   }   
};

struct RollingHash4 {
   // Can give MLE if array size is big
   // http://www.codeforces.com/contest/7/problem/D
   static const unsigned long long p1 = 1000000007ULL;
   static const unsigned long long p2 = 1000000009ULL;
   string s;
   int n;
   vector <unsigned long long> pow1, pow2, forHash1, forHash2, revHash1, revHash2;

   RollingHash4() {}
   RollingHash4(string s): s(s), n(s.length()), pow1(n + 1), pow2(n + 1), forHash1(n + 1) \
                                       ,forHash2(n + 1), revHash1(n + 1), revHash2(n + 1) {
      pow1[0] = 1;
      pow2[0] = 1;

      forHash1[0] = 0;
      forHash2[0] = 0;
      for(int i = 0; i < n; i++) {
         forHash1[i + 1] = forHash1[i] * p1 + s[i];
         forHash2[i + 1] = forHash2[i] * p2 + s[i];
         pow1[i + 1] = pow1[i] * p1;
         pow2[i + 1] = pow2[i] * p2;
      } 
      revHash1[n] = 0;
      revHash2[n] = 0;
      for(int i = n - 1; i >= 0; i--) {
         revHash1[i] = revHash1[i + 1] * p1 + s[i];
         revHash2[i] = revHash2[i + 1] * p2 + s[i];
      }
   }

   void init(string s) {
      s = s; n = s.length(); pow1.resize(n + 1); forHash1.resize(n + 1); revHash1.resize(n + 1);
      pow2.resize(n + 1); forHash2.resize(n + 1); revHash2.resize(n + 1);
      pow1[0] = 1;
      pow2[0] = 1;
      forHash2[0] = 0;
      forHash2[0] = 0;
      for(int i = 0; i < n; i++) {
         forHash1[i + 1] = forHash1[i] * p1 + s[i];
         forHash2[i + 1] = forHash2[i] * p2 + s[i];
         pow1[i + 1] = pow1[i] * p1;
         pow2[i + 1] = pow2[i] * p2;
      } 
      revHash1[n] = 0;
      revHash2[n] = 0;
      for(int i = n - 1; i >= 0; i--) {
         revHash1[i] = revHash1[i + 1] * p1 + s[i];
         revHash2[i] = revHash2[i + 1] * p2 + s[i];
      }
   }

   pair < unsigned long long, unsigned long long> getForHash(int i) const {
      return {forHash1[i], forHash2[i]};
   }
   pair < unsigned long long, unsigned long long> getRevHash(int i) const {
      return {revHash1[i], revHash2[i]};
   }

   pair < unsigned long long, unsigned long long> getForHash(int i, int j) const {
      return { getForHash(j + 1).first - getForHash(i).first * pow1[j - i + 1], 
               getForHash(j + 1).second - getForHash(i).second * pow2[j - i + 1]};
   }
   pair < unsigned long long, unsigned long long> getRevHash(int i, int j) const {
      return { getRevHash(i).first - getRevHash(j + 1).first * pow1[j - i + 1], 
               getRevHash(i).second - getRevHash(j + 1).second * pow2[j - i + 1]};
   }
   bool isPalindrome(int i, int j) {
      return (getForHash(i, j) == getRevHash(i, j));
   }   
};

int main() {
   fastIO();
   string s;
   cin >> s;
   RollingHash4 rh;
   rh.init(s);
   int ans = 0;
   for(int i = 0; i < s.length(); i++) {
      for(int j = i; j < s.length(); j++) {
         if(rh.isPalindrome(i, j)) {
            ans++;
         }
      }
   }
   cout << ans << endl;
   return 0;
}
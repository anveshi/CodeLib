#include <bits/stdc++.h>
using namespace std;
const int Mod = 1e9 + 7;

typedef vector <int> vi;
typedef vector <vi> Matrix;

void printMatrix(Matrix &X){
   for(int i=0;i<X.size();i++){
      for(int j=0;j<X[i].size();j++){
         cout << X[i][j] << " \n"[(j+1==(X[i].size()))?1:0];
      }
   }
   return;
}

Matrix matrixZero(int n, int m){
   Matrix Ret(n, vi(m));
   for(int i=0;i<n;i++){
      for(int j=0;j<m;j++){
         Ret[i][j] = 0;
      }
   }
   return Ret;
}

Matrix matrixUnit(int n){
   Matrix Ret = matrixZero(n, n);
   for(int i=0;i<n;i++){
      Ret[i][i] = 1;
   }
   return Ret;
}

Matrix matrixAdd(const Matrix &A, const Matrix &B){
   int n = A.size();
   int m = A[0].size();
   assert(n == B.size() && m == B[0].size());
   Matrix Ret(n, vi(m));

   for(int i=0;i<n;i++){
      for(int j=0;j<m;j++){
         Ret[i][j] = (0LL + A[i][j] + B[i][j])%Mod;
      }
   }
   return Ret;
}

Matrix matrixMult(const Matrix &A, const Matrix &B){
   int n = A.size();
   int m = A[0].size();
   int k = B[0].size();
   assert(m == B.size());
   Matrix Ret(n, vi(k));
   for(int i=0;i<n;i++){
      for(int j=0;j<k;j++){
         for(int p=0;p<m;p++){
            Ret[i][j] = (Ret[i][j] + 1LL * A[i][p] * B[p][j])%Mod;
         }
      }
   }
   return Ret;
}

Matrix matrixPow(const Matrix &A, int p){
   if(p==0)
      return matrixUnit(A.size());
   Matrix temp = matrixPow(A, p/2);
   temp = matrixMult(temp, temp);
   if(p&1)
      return matrixMult(temp, A);
   else
      return temp;
}
int main(){
   int n = 4;
   Matrix M(2, vi(2));
   M[0][0] = M[1][0] = M[0][1] = 1;
   printMatrix(M);
   
   Matrix K = matrixMult(matrixMult(M, M), matrixMult(M, M));
   printMatrix(K);

   Matrix T = matrixPow(M, 4);
   printMatrix(T);
   return 0;
}
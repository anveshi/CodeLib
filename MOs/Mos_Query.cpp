struct query{
   int l,r,idx;
   bool operator < (const query &b) const{
      if(l/SQN != b.l/SQN)
         return (l/SQN) < (b.l/SQN);
      return (r < b.r)^((l/SQN)%2);
   }
} Query[Maxn];

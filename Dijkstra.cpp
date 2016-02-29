// Anve$hi $hukla
// Until the lion learns how to write, every story will glorify the hunter.
// http://codeforces.com/contest/20/problem/C
// Dijkstra algorithm self loop and multiple edges allowed, but negative weights NOT allowed
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair <LL,int> pii;

inline void fastIO(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

vector <int> Dijkstra(int src, const vector <vector <pii> > &graph){

  vector <int> from(graph.size(), -1);
  vector <LL> dist(graph.size(), -1);
  dist[src] = 0;
  priority_queue< pii, vector<pii>, greater<pii> > PQ;

  PQ.push(pii(0,src));

  while(PQ.size()){
    LL D = PQ.top().first;
    int U = PQ.top().second;
    PQ.pop();

    if(dist[U] != D) 
      continue;

    for(int i=0;i<graph[U].size();i++){

      LL D = graph[U][i].first;
      int V = graph[U][i].second;

      if(dist[V]==-1 || dist[V]>dist[U]+D){
        from[V] = U;
        dist[V] = dist[U] + D;
        PQ.push(pii(dist[V],V));
      }

    }
  }
  return from;
}

void printVector(vector <int> &V){
  for(auto node: V)
    cout << node << " ";
  cout << endl;
}

int main(){
  fastIO();

  int N,M,u,v,w;
  cin >> N >> M;

  vector < vector <pii> > graph(N);
  for(int i=0;i<M;i++){
    cin >> u >> v >> w;
    u--;v--;
    graph[u].emplace_back(pii(w, v));
    graph[v].emplace_back(pii(w, u));
  }

  vector <int> from = Dijkstra(0,graph);

  if(from[N-1] == -1){
    cout << -1 << endl;
    return 0;
  }

  vector <int> Ans;

  for(int i=N-1;i!=-1;i=from[i])
    Ans.emplace_back(i+1);

  reverse(Ans.begin(), Ans.end());
  printVector(Ans);
  
  return 0;
}

// Anve$hi $hukla
#include <bits/stdc++.h>

//#define NODEBUG
#ifdef NODEBUG
#define DEBUG($...) ;
#else
#include "DEBUG.h"
#endif

using namespace std;
struct ${$(){ios_base::sync_with_stdio(false);cin.tie(NULL);}}$;



// Sparse Table
const int Maxn = 205000;
const int Maxl = 20;
int table[Maxl][Maxn];
int numlog[Maxn]; // numlog[i] = log2(i)
int n, a[Maxn]; // orignal array 1 indexed

void buildTable() {
	numlog[1] = 0;
	for(int i = 2; i <= n; i++) {
		numlog[i] = numlog[i >> 1] + 1;
		int tlog = log2(i);
		assert(tlog == numlog[i]);
	}
	for(int i = 0; i <= numlog[n]; i++) {
		int curlen = 1 << i;
		for(int j = 1; (j + curlen - 1) <= n; j++) {
			if(i == 0) {
				table[i][j] = j; // stores indices
				continue;
			} else {
				if(a[table[i - 1][j]] < a[table[i - 1][j + (curlen >> 1)]]) { // RMQ
					table[i][j] = table[i - 1][j];
				} else {
					table[i][j] = table[i - 1][j + (curlen >> 1)];
				}
			}
		}
	}
}

int getMinIndex(int l, int r) { // [1....N]
	int curlog = numlog[r - l + 1];
	if(a[table[curlog][l]] < a[table[curlog][r - (1 << curlog) + 1]]) { // RMQ
		return table[curlog][l];
	} else {
		return table[curlog][r - (1 << curlog) + 1];
	}
}

int RMQ(int l, int r) {
	return a[getMinIndex(l, r)];
} // O(1)


// 2. Using Segment tree
const int inf = 1e9;

int tree[4 * Maxn];
void build(int node, int st, int end){ // build(1, 0, n - 1)
    if(st == end) { 
        tree[node] = a[st];
        return;
    }
    int mid = (st + end) / 2;
    build(2 * node, st, mid);
    build(2 * node + 1, mid + 1, end);
    tree[node]= min(tree[2 * node], tree[2 * node + 1]);
}

int find_min(int node, int st, int end, int l, int r) { // find_min(1, 0, n - 1, l, r)
    if(r < st || end < l) {
        return inf;
    }
    if(l <= st && end <= r) {
        return tree[node];
    }
    int mid = (st + end) / 2;
    int Q1 = find_min(node * 2, st, mid, l, r);
    int Q2 = find_min(node * 2 + 1, mid + 1, end, l, r);
    return min(Q1, Q2);
}
//

// 3. Bruteforce
int Bruteforce(int l, int r) {
	int ret = inf;
	for(int i = l; i <= r; i++) {
		ret = min(ret, a[i]);
	}
	return ret;
}
//

int getMin(int l, int r) { // general O(log(n)) apporoach
	int ret = inf; // min(inf, x) = x;
	while(l <= r) {
		int curlog = numlog[r - l + 1];
		ret = min(ret, a[table[curlog][l]]);
		l += (1 << curlog);
	}
	return ret;
}


int main() {


	n = 2e5;
	for(int i = 1; i <= n; i++) {
		a[i] = rand() % n;
	}

	buildTable();
	build(1, 0, n);
	
	int Q = 1e5;
	for(int i = 0; i < Q; i++) {
		int l = rand() % n + 1; // 1 indexed
		int r = rand() % n + 1;
		if(l > r)
			swap(l, r);

		int x = getMin(l, r);
		int xx = RMQ(l, r); 
		int y = find_min(1, 0, n, l, r);
		int z = Bruteforce(l, r);
		assert(xx == x);
		assert(x == y);
		assert(y == z);
		DEBUG(x, l, r, y);
	}
	return 0;
}

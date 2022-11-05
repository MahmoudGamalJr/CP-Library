#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> ii;
typedef pair<int, ii> edge;
vector<edge> edge_list; //cost , to , from
vector<bool> in_mst;
vector<vector<ii> > adj;
int E, V, T, u, v, w, mx;

//connected, undirected, weighted graph

class DSU {
private:
    vector<int> p, rank, set_size;
    int num_sets;
public:
    DSU(int N) {
        num_sets = N;
        rank.assign(N, 0);
        p.assign(N, 0);
        set_size.assign(N, 1); //each set is initially 1
        for (int i = 0; i < N; i++) {
            p[i] = i;
        }
    }

    int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }

    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }

    void unionSet(int i, int j) {
        if (!isSameSet(i, j)) {
            num_sets--;
            int x = findSet(i), y = findSet(j);
            if (rank[x] > rank[y]) {
                p[y] = x;
                set_size[x] += set_size[y];
            } else {
                p[x] = y;
                set_size[y] += set_size[x];
                if (rank[x] == rank[y]) rank[y]++;
            }
        }
    }

    int num() { return num_sets; }

    int size(int i) { return set_size[findSet(i)]; }
};

int mst(int k) {
    sort(edge_list.begin(), edge_list.end());
    int mst_cost = 0;
    DSU uf(V); //initially all nodes form a disjoint set
    for (int i = 0; i < E; i++) {
        edge cur = edge_list[i];
        if (!uf.isSameSet(cur.second.first, cur.second.second)) {
            in_mst[i] = true;
            mst_cost += cur.first; //add weight
            uf.unionSet(cur.second.first, cur.second.second);
        }
        if (uf.num() == k) break;    //for minimum spanning forest
    }
    return mst_cost;
}

void construct() {
    for (int i = 0; i < E; i++) {
        if (in_mst[i]) {
            edge cur = edge_list[i];
            adj[cur.second.first].push_back(make_pair(cur.second.second, cur.first));
            adj[cur.second.second].push_back(make_pair(cur.second.first, cur.first));
        }
    }
}
//dfs the minimum spanning tree and save the maximum edge within the mst
bool dfs(int u, int p) {    //T==>target node
    if (u == T) return true;
    bool reach = false;
    for (ii edge : adj[u]) {
        if (edge.first != p && dfs(edge.first, u)) {
            reach = true;
            mx = max(mx, edge.second);
        }
    }
    return reach;
}

int main() {
    cin >> E >> V >> T; //constructing edge list
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &u, &v, &w);
        edge_list.push_back(make_pair(w, make_pair(u, v)));
    }
    in_mst.assign(E, false);
    mst(1); //1 for connected graph (no forrest)

    //for solving the mini-max problem
    adj.resize(V);
    mx = 0;
    construct();
    bool reach = dfs(0, -1); //set parent initially to -1
}


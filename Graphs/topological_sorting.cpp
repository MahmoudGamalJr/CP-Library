#include <bits/stdc++.h>

using namespace std;
int N;
vector<vector<int> > adj;
vector<int> sorted_array, parent;
stack<int> st;
vector<bool> vis;

//if not DAG algorithms will fail!

void toposort_dfs(int u) {
    for (int v:adj[u]) {
        if (!vis[v]) {
            vis[v] = 1;
            toposort_dfs(v);
        }
    }
    st.push(u);
}

void toposort_bfs() {
    for (int i = 0; i < N; i++) {    //constructing parent array
        for (int v:adj[i]) {
            parent[v]++;
        }
    }
    queue<int> roots; //PriorityQueue for smallest lexiographical sorting kahn's algorithm
    for (int i = 0; i < N; i++) {
        if (!parent[i]) roots.push(i);
    }
    while (!roots.empty()) {
        int u = roots.front();
        roots.pop();
        sorted_array.push_back(u);
        for (int v: adj[u]) {
            if (--parent[v] == 0)
                roots.push(v);
        }
    }
}

int main() {
    vis.assign(N, false);
    parent.assign(N, 0);
    for (int i = 0; i < N; ++i) { //preTraversal for dfs algorithm
        if (!vis[i]) {
            toposort_dfs(i);
            st.push(i);
        }
    }
    toposort_bfs();
    return 0;
}

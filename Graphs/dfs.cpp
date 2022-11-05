#include <bits/stdc++.h>

using namespace std;
int N;
vector<vector<int> > adj;
vector<bool> vis;

void dfs(int u) 
{
    for (int v:adj[u]) 
    {
        if (!vis[v]) {
            vis[v] = 1;
            dfs(v);
        }
    }
}

int main() {
    adj.resize(N);
    vis.assign(N, false);
    for (int i = 0; i < N; ++i)
    {   
        //preTraversal:
        if (!vis[i]) dfs(i);         //for non-connected graphs, Spanning Forest
    }
    return 0;
}

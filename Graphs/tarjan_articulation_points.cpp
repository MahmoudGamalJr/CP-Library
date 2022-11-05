#include <bits/stdc++.h>

using namespace std;
int N;
vector<vector<int> > adj;
vector<bool> vis, art_point;
vector<int> parent, dfs_num, dfs_low;
int n, cnt, root, root_children;

void dfs(int u) 
{
    dfs_num[u] = dfs_low[u] = ++cnt;   //update dfs low & dfs num
    for (int v: adj[u]) {
        if (!dfs_num[v]) {    //not visited
            parent[v] = u;
            if (u == root) {  //special case
                root_children++;
            }
            dfs(v);
            if (dfs_low[v] >= dfs_num[u]) {
                art_point[u] = true;
            }
            if (dfs_low[v] > dfs_num[u]) {
                printf("Bridge between %d %d", u, v);
            }
            dfs_low[u] = min(dfs_low[u], dfs_low[v]); //update dfs low of u during backtracking
        } else {
            if (parent[u] != v) {  //cycle
                dfs_low[u] = min(dfs_low[u], dfs_num[v]);
            }
        }
    }
}

void artpoints_and_bridges() {
    for (int i = 0; i < n; i++) {
        if (!dfs_num[i]) {
            root = i;
            root_children = 0;
            dfs(i);
            if (root_children <= 1)
                art_point[root] = false;
        }
    }
}

int main() {
    n = cnt = root = root_children = 0;
    vis.assign(N, false);
    art_point.assign(N, false);
    parent.assign(N, 0);
    dfs_low.assign(N, 0);
    dfs_num.assign(N, 0);
    adj.resize(N);
    artpoints_and_bridges();
    return 0;
}

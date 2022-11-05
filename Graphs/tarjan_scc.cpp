#include <bits/stdc++.h>

using namespace std;
int N;
vector<vector<int> > adj;
vector<bool> in_scc;
vector<int> parent, dfs_num, dfs_low;
int cnt, scc;
stack<int> st;

void tarjan_scc(int u) {
    dfs_num[u] = dfs_low[u] = ++cnt;
    st.push(u);
    for (int v:adj[u]) {
        if (!dfs_num[v])
            tarjan_scc(v);
        if (!in_scc[v])  //not taken in another component
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
    }
    if (dfs_num[u] == dfs_low[u]) {    //scc found
        scc++;
        while (true) {
            int v = st.top();
            st.pop();
            in_scc[v] = true;
            if (v == u) break; //reached head of the cycle
        }
    }

}

void tarjan_scc() {
    for (int i = 0; i < N; ++i) {
        if (!dfs_num[i])    //preTraversal
            tarjan_scc(i);
    }
}

int main() {
    cnt = scc = 0;
    in_scc.assign(N, false);
    dfs_num.assign(N, 0);
    dfs_low.assign(N, 0);
    adj.resize(N);
    tarjan_scc();
    return 0;
}


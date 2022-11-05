#include <bits/stdc++.h>

using namespace std;
int N;
vector<vector<int> > adj;
vector<int> dist;

void bfs(int u) {
    queue<int> q;
    q.push(u);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int v:adj[cur]) {
            if (dist[v] == -1) {
                dist[v] = dist[cur] + 1;
                q.push(v);
            }
        }
    }
}

int main() {
    adj.resize(N);
    dist.assign(N, -1);
    for (int i = 0; i < N; ++i) {   //preTraversal:
        if (dist[i] == -1) {
            dist[i] = 0;
            bfs(i);         //for non-connected graphs, Spanning Forest
        }
    }
    return 0;
}

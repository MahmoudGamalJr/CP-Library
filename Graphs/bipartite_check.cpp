#include <bits/stdc++.h>

using namespace std;
int N;
vector<vector<int> > adj;
vector<int> color;

bool bipartite_check(int u) 
{
    for (int v: adj[u]) {
        if (color[v] == -1) {
            color[v] = 1 ^ color[u];
            if (!bipartite_check(v)) return false;
        } else if (color[v] == color[u]) {
            return false;
        }
    }
    return true;
}

int main() {
    
    color.assign(N, -1);
    adj.resize(N);
    color[0] = 0;
    bool valid = bipartite_check(0);
    return 0;
}

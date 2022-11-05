#include <bits/stdc++.h>

using namespace std;
int N;
const int VISITED = 2, EXPLORED = 1, UNVISITED = 0;
vector<vector<int> > adj;
vector<int> parent, status;


void edge_type(int u) 
{
    status[u] = EXPLORED;
    for (int v:adj[u]) {
        if (!status[v]) {    //UNVISITED
            printf("Edge from %d to %d is %s", u, v, "tree edge");
            parent[v] = u;
            edge_type(v); //dfs
        } else if (status[v] == VISITED) {   //forward edge with directed graphs only
            printf("Edge from %d to %d is %s", u, v, "forward/cross edge");
        } else if (parent[u] == v) {
            printf("Edge from %d to %d is %s", u, v, "bidirectional edge");
        } else {
            printf("Edge from %d to %d is %s", u, v, "back edge");    //cycle
        }
    }
    status[u] = VISITED;
}

int main() 
{
    status.assign(N, UNVISITED);
    parent.assign(N, 0);
    adj.resize(N);
    for (int i = 0; i < N; ++i) {   //preTraversal
        if (!status[i]) edge_type(i);
    }
    return 0;
}


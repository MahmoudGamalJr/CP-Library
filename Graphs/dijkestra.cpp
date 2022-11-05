#include <bits/stdc++.h>

using namespace std;
const int INF = (int) 1e9;
typedef vector<int> vi;
typedef pair<int, int> ii;
vector<vector<ii> > adj;
int N, S;
vi dist;

//for all other nodes
void dijkestra() 
{
    dist.assign(N, INF);
    dist[S] = 0;
    priority_queue<ii, vector<ii>, greater<ii> > pq;
    pq.push(ii(0, S));
    while (!pq.empty()) {
        int cost = pq.top().first, u = pq.top().second;
        pq.pop();
        if (cost > dist[u]) continue;
        for (ii v: adj[u]) { //relax
            if (cost + v.second < dist[v.first]) {
                dist[v.first] = cost + v.second;
                pq.push(ii(dist[v.first], v.first));
            }
        }

    }
}

//sssp to target node:
int dijkestra(int T)
{
    dist.assign(N, INF);
    dist[S] = 0;
    priority_queue<ii, vector<ii>, greater<ii> > pq;
    pq.push(ii(0, S));
    while (!pq.empty()) {
        int cost = pq.top().first, u = pq.top().second;
        if (u == T)
            return dist[T];
        pq.pop();
        if (cost > dist[u]) continue;
        for (ii v: adj[u]) { //relax
            if (cost + v.second < dist[v.first]) {
                dist[v.first] = cost + v.second;
                pq.push(ii(dist[v.first], v.first));
            }
        }

    }
    return -1;
}

int main() {
    adj.resize(N);
    dijkestra();
    return 0;
}


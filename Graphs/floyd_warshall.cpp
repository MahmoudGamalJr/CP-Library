const int N = 10, INF = int(1e9);
int diameter = 0, n;
vi adj[N], dist[N][N];

//construct the graph with INF > |path|
//diagonals must be equal to 0
//if there is edge i -> j then adj[i][j] = cost(i -> j)
//time complexity O(V^3)

void floyd() {
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (adj[i][k] < INF && adj[k][j] < INF) { //incase of overflow
					adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
				}
			}
		}
	}
}

//alternatives:
//------------

//shortest path (doesn't work with neg cycles)
//adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);

//longest path (doesn't work with cycles)
//adj[i][j] = max(adj[i][j], adj[i][k] + adj[k][j]);

//transitive closure
//adj[i][j] |= (adj[i][k] & adj[k][j]);

//minimax (the path such that the max cost on the path is min)
//adj[i][j] = min(adj[i][j], max(adj[i][k], adj[k][j]) );

//maximin (the path such that the min cost on the path is max)
//adj[i][j] = max(adj[i][j], min(adj[i][k], adj[k][j]) );

//count paths from i -> j
//adj[i][j] += adj[i][k] * adj[k][j];

//preprocess prev during floyd
//prev[i][j] is initially i
//if k is an intermediary between i and j then prev[i][j] = k
void trace(int i, int j) {
	if(i != j)) trace(i, prev[i][j]);
	cout << j << ' ';
}

//checks if the graph contains any neg cycles
//flip the signs for searching for pos cycles
bool isNegativeCycle() {
	for (int i = 0; i < n; i++) {
		if (adj[i][i] < 0)
			return true;
	}
	return false;
}

// Longest path among all shortest ones
int graphDiameter() {
	floyd();

	int mx = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			mx = max(mx, adj[i][j]);
		}
	}

	return mx;
}

//can be used to find scc (shorter code than tarjan)
//find cycles between every 2 nodes O(N^2)
//put each cycles in a single component


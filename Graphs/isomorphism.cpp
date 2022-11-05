const int N = 10;
int diameter = 0;
vi adj[N];


//can also be done using the 2 dfs/bfs to obtain start and end of diameter

int get_diameter(int u, int p = -1)
{
	int mxheight[3] = {-1,-1,-1};

	for(int v : adj[u]){
		if(v != p){
			mxheight[0] = get_diameter(v, u) + 1;
			sort(mxheight, mxheight + 3);

		}
	}

	for(int &x : mxheight) x = max(x,0);
	diameter = max(diameter, mxheight[1] + mxheight[2]);

	return mxheight[2];
}

//tree isomorphism O(nlog(n))
//if trees have no roots find roots using tree centers
//both trees should have either 1 center or 2
//or find roots using tree shrinking

string canonical_form(int u, int p = -1)
{
	vector<string> children;

	for(int v : adj[u])
	{
		children.push_back(canonical_form(v,u));
	}

	string canonical = "(";
	sort(children.begin(), children.end());

	for(string child : children){
		canonical += child;
	}

	canonical += ")";
	return canonical;
}


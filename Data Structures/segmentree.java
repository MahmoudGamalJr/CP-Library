class SegmentTree {

	int N;
	long[] array, stree, lazy;
	static final long INF = (long) 1e15;
 
	SegmentTree(long[] in) {
		array = in;
		N = in.length;
		stree = new long[N << 2];
		lazy = new long[N << 2];
		build(1, 1, N);
	}
 
	void build(int node, int b, int e) {
		if (b == e)
			stree[node] = array[b - 1];
		else {
			int mid = b + e >> 1;
			build(node << 1, b, mid);
			build(node << 1 | 1, mid + 1, e);
			stree[node] = Math.max(stree[node << 1],stree[node << 1 | 1]);
		}
	}
 
	long query(int i, int j) {
		return query(1, 1, N, i, j);
	}
 
	long query(int node, int b, int e, int i, int j) // O(log n)
	{
		if (i > e || j < b)
			return -INF;
		if (b >= i && e <= j)
			return stree[node];
		int mid = b + e >> 1;
		long q1 = query(node << 1, b, mid, i, j);
		long q2 = query(node << 1 | 1, mid + 1, e, i, j);
		return Math.max(q1, q2);
 
	}
	
	void updatePoint(int node, int l, int r, int idx, long val) {
        if (l == r) {
            stree[node] += val;
            return;
        }
        int mid = (l + r) >> 1;
        if (idx <= mid)
            updatePoint(node << 1, l, mid, idx, val);
        else
            updatePoint(node << 1 | 1, mid + 1, r, idx, val);
        stree[node] = Math.max(stree[node << 1], stree[node << 1 | 1]);
    }

    void updatePoint(int idx, long val) {  //Input index 1-based
        updatePoint(1, 1, N, idx, val);
    }

    void propagate(int node, int l, int mid, int r) {
        lazy[node << 1] += lazy[node];
        lazy[node << 1 | 1] += lazy[node];
        stree[node << 1] += (mid - l + 1) * lazy[node];
        stree[node << 1 | 1] += (r - mid) * lazy[node];
        lazy[node] = 0;
    }

    void updateRange(int node, int l, int r, int rangeStart, int rangeEnd, long val)
    {
        if (r < rangeStart || l > rangeEnd)
            return;
        if (l >= rangeStart && r <= rangeEnd) {
            stree[node] += (r - l + 1) * val;
            lazy[node] += val;
            return;
        }
        int mid = (l + r) >> 1;
        propagate(node, l, mid, r);
        updateRange(node << 1, l, mid, rangeStart, rangeEnd, val);
        updateRange(node << 1 | 1, mid + 1, r, rangeStart, rangeEnd, val);
        stree[node] = Math.max(stree[node << 1], stree[node << 1 | 1]);
    }

    void updateRange(int l, int r, long val) {
        updateRange(1, 1, N, l, r, val);
    }
	
}

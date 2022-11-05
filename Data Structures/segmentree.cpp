template<typename T>
struct segmentree
{
    int N;
    T *in;
    vector<T> stree, lazy;

    inline T combine(T a, T b)
    {
        return a + b; 
        
    }

    void build(int node, int l, int r)
    {
        if (l == r) 
        {
            stree[node] = in[l - 1];
            return;
        }
        int mid = (l + r) >> 1;
        build(node << 1, l, mid);
        build(node << 1 | 1, mid + 1, r);
        stree[node] = combine(stree[node << 1], stree[node << 1 | 1]);
    }

    segmentree(T arr[], int n) 
    {
        in = arr; // 0-based
        N = n;
        stree.assign(4 * N, 0); //or pad
        lazy.assign(4 * N, 0);
        build(1, 1, N);
    }

    void updatePoint(int node, int l, int r, int idx, T val)
    {
        if (l == r) {
            stree[node] += val;
            return;
        }
        int mid = (l + r) >> 1;
        if (idx <= mid)
            updatePoint(node << 1, l, mid, idx, val);
        else
            updatePoint(node << 1 | 1, mid + 1, r, idx, val);
        stree[node] = combine(stree[node << 1], stree[node << 1 | 1]);
    }

    void updatePoint(int idx, T val) {  //Input index 1-based
        updatePoint(1, 1, N, idx, val);
    }

    void propagate(int node, int l, int mid, int r) {
        lazy[node << 1] += lazy[node];
        lazy[node << 1 | 1] += lazy[node];
        stree[node << 1] += (mid - l + 1) * lazy[node];
        stree[node << 1 | 1] += (r - mid) * lazy[node];
        lazy[node] = 0;
    }

    void updateRange(int node, int l, int r, int rangeStart, int rangeEnd, T val) {
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
        stree[node] = combine(stree[node << 1], stree[node << 1 | 1]);
    }

    void updateRange(int l, int r, T val) {
        updateRange(1, 1, N, l, r, val);
    }

    T query(int node, int l, int r, int queryStart, int queryEnd)
    {
        if (r < queryStart || l > queryEnd)
            return 0; //dummy variable
        if (l >= queryStart && r <= queryEnd)
            return stree[node];
        int mid = (l + r) >> 1;
        propagate(node, l, mid, r);
        T q1 = query(node << 1, l, mid, queryStart, queryEnd);
        T q2 = query(node << 1 | 1, mid + 1, r, queryStart, queryEnd);
        return combine(q1, q2);
    }

    T query(int l, int r) 
    {
        return query(1, 1, N, l, r);
    }

};


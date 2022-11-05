class DSU {
private:
    vector<int> p, rank, set_size;
    int num_sets;
public:
    DSU(int N) {
        num_sets = N;
        rank.assign(N, 0);
        p.assign(N, 0);
        set_size.assign(N, 1); //each set is initially 1
        for (int i = 0; i < N; i++) {
            p[i] = i;
        }
    }

    int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }

    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }

    void unionSet(int i, int j) {
        if (!isSameSet(i, j)) {
            num_sets--;
            int x = findSet(i), y = findSet(j);
            if (rank[x] > rank[y]) {
                p[y] = x;
                set_size[x] += set_size[y];
            } else {
                p[x] = y;
                set_size[y] += set_size[x];
                if (rank[x] == rank[y]) rank[y]++;
            }
        }
    }

    int num() { return num_sets; }

    int size(int i) { return set_size[findSet(i)]; }
};

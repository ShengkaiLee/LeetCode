class UnionFind {
    private:
        vector<int> parent, rank;
        int cnt;
    public:
        UnionFind(int cnt) : cnt(cnt) {
            parent = vector<int>(cnt);
            rank = vector<int>(cnt, 0);
            for (int i = 0; i < cnt; ++i) parent[i] = i;
        }
        int find(int p) {
            if (parent[p] == p) return p;
            return parent[p] = find(parent[p]);
        }
        bool connected(int p, int q) { 
            return find(p) == find(q); 
        }
        void connect(int p, int q) {
            int i = find(p), j = find(q);
            if (i == j) return;
            if (rank[i] < rank[j]) {
                parent[i] = j;  
            } else {
                parent[j] = i;
                if (rank[i] == rank[j]) rank[j]++;
            }
            --cnt;
        }
};
class Solution {
private:
    vector<int> dir {0, -1, 0, 1, 0};
    vector<int> parent;
    int find(int x) {
        if (x != parent[x]) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    void connect(int x, int y) {
        int px = find(x), py = find(y);
        parent[py] = px;
    }
public:
    vector<int> numIslands2(int m, int n, vector<vector<int>>& positions) {
        parent.resize(m*n);
        for (int i = 0; i < parent.size(); i++) parent[i] = i;
        vector<vector<int>> grid(m, vector<int>(n, 0));
        int counter = 0;
        vector<int> res;
        for (const auto& pos : positions) {
            int x = pos[0], y = pos[1];
            if (grid[x][y] == 0) counter++; 
            grid[x][y] = 1;
            for (int k = 0; k < 4; k++) {
                int dx = x + dir[k], dy = y + dir[k+1];
                if (dx < 0 or dx >= m or dy < 0 or dy >= n or grid[dx][dy] == 0) continue;
                if (find(x*n+y) != find(dx*n+dy)) {
                    counter--;
                    connect(x*n+y, dx*n+dy);
                }
            }
            res.push_back(counter);
        }
        return res;
    }
};
func1 { // 4-Ways
        vector<int> dir {0, -1, 0, 1, 0};
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dist(m, vector<int>(n, INT_MAX));
        dist[0][0] = grid[0][0] == 0 ? 0 : 1;
        priority_queue<pair<int,array<int,2>>,vector<pair<int,array<int,2>>>,greater<>> pq;
        pq.push({dist[0][0],{0,0}});
        while (not pq.empty()) {
            auto [total, a] = pq.top(); 
            auto [x, y] = a;
            pq.pop();
            if (total > dist[x][y]) continue;
            for (int k = 0; k < 4; k++) {
                int dx = x + dir[k], dy = y + dir[k+1];
                if (dx < 0 or dx >= m or dy < 0 or dy >= n) continue;
                int cost = total + (grid[dx][dy] == 1 ? 1 : 0);
                if (cost < dist[dx][dy]) {
                    dist[dx][dy] = cost;
                    pq.push({cost,{dx,dy}});
                }
            }
        }
        return dist[m-1][n-1]; 
}

func2 { // directed graph
        vector<vector<pair<int,int>>> graph(n+1);
        for (const auto& v : times) {
            int f = v[0], t = v[1], c = v[2];
            graph[f].push_back({c, t});
        }
        vector<int> dist(n+1, INT_MAX);
        dist[0] = 0, dist[k] = 0;
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
        pq.push({dist[k], k});
        while (not pq.empty()) {
            pair<int,int> p = pq.top(); pq.pop();
            int total = p.first, curr = p.second;;
            if (total > dist[curr]) continue;
            for (auto [cost, next] : graph[curr]) {
                if (cost + total < dist[next]) {
                    dist[next] = cost + total;
                    pq.push({dist[next], next});
                }
            }
        }
        int res = *max_element(dist.begin(), dist.end());
        return res == INT_MAX ? -1 : res;
}
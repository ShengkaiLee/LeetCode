
int numNodes;
int visited[numNodes];
vector<vector<int>> next;

main()
{
  // prepare next; // next[i][j]: there is a directional path i->j

  // dfs 判断有环
  for (int i=0; i<numNodes; i++)
  {            
      if (dfs(i)==false) return false;            
  }
  return true;

  // bfs 判断有环
  return bfs();
}

bool dfs(int cur)
{
    if (visited[cur]==1) return true;

    visited[cur] = 2;
    for (int next: next[cur])
    {
        if (visited[next]==1) continue;
        if (visited[next]==2) return false;
        if (dfs(next)==false)  return false;
    }
    visited[cur] = 1;
    return true;
}



bool bfs() 
{        
    queue<int>q;
    int count = 0;

    vector<int>InDegree(numNodes,0);
    for (int i=0; i<numNodes; i++)
    	for (int j: next[i])
    		InDegree[j]++;

    for (int i=0; i<numNodes; i++)
    {
        if (InDegree[i]==0) 
        {
            q.push(i);
            count++;
        }
    }
                
    while (!q.empty())
    {
        int curCourse = q.front();
        q.pop();
        for (auto child: next[curCourse])
        {
            InDegree[child]--;
            if (InDegree[child]==0)
            {
                q.push(child);
                count++;
            }                    
        }
    }        
    
    return count==numNodes;        
}

// Find longest cycle
class Solution {
private:
    int ans = -1;
    unordered_set<int> seen;
public:
    int longestCycle(vector<int>& edges) {
        for (int i = 0; i < edges.size(); i++) {
            if (seen.count(i)) continue;
            unordered_map<int,int> dis;
            dfs(edges, i, 0, dis);
        }
        return ans;
    }
    
    void dfs(vector<int>& edges, int curr, int len, unordered_map<int,int>& dis) {
        if (curr == -1) return;
        if (not seen.count(curr)) {
            seen.insert(curr);
            dis[curr] = len;
            dfs(edges, edges[curr], len+1, dis);
        } else {
            if (dis.count(curr)) {
                ans = max(ans, len - dis[curr]);
            }
        }
    }
};
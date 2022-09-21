// 1. Using Loop and bitmask
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ans;
        int total = 1 << (nums.size());
        for (int state = 0; state < total; state++) {
            vector<int> v;
            for (int i = 0; i < nums.size(); i++) {
                if (state & (1 << i)) {
                    v.push_back(nums[i]);
                }
            }
            ans.push_back(v);
        }
        return ans;
    }
};
// 2. Using recursion
class Solution {
private:
    vector<vector<int>> res;
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> v;
        dfs(nums, 0, v);
        return res;
    }
    
    void dfs(vector<int>& nums, int index, vector<int> v) {
        res.push_back(v);
        for (int i = index; i < nums.size(); i++) {
            v.push_back(nums[i]);
            dfs(nums, i+1, v);
            v.pop_back();
        }
    }
};
// 3. Using recursion II (get rid of duplicate elements)
class Solution {
private:
    vector<vector<int>> res;
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<int> v;
        dfs(nums, 0, v);
        return res;
    }
    
    void dfs(vector<int>& nums, int index, vector<int> v) {
        res.push_back(v);
        for (int i = index; i < nums.size(); i++) {
            if (i - 1 >= index and nums[i-1] == nums[i]) 
                continue;
            v.push_back(nums[i]);
            dfs(nums, i+1, v);
            v.pop_back();
        }
    }
};
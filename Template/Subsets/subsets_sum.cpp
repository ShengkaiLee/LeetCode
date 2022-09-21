// 1.
class Solution {
private:
    vector<vector<int>> res;
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<int> v;
        dfs(candidates, 0, 0, target, v);
        return res;
    }
    
    void dfs(vector<int>& arr, int index, int sum, int target, vector<int>& v) {
        if (sum >= target) {
            if (sum == target) {
                res.push_back(v);
            }
            return;
        }
        
        for (int i = index; i < arr.size(); i++) {
            sum += arr[i];
            v.push_back(arr[i]);
            dfs(arr, i, sum, target, v);
            v.pop_back();
            sum -= arr[i];
        }
    }
};

// 2. Find K-th subsets sum
class Solution {
public:
    long long kSum(vector<int>& nums, int k) {
        auto add = [](long long& a, int& b) {
            if (b <= 0) b = abs(b);
            else a = a + (long long) b;
            return a;
        };
        long long largest = accumulate(nums.begin(), nums.end(), 0LL, add);
        sort(nums.begin(), nums.end());
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
        pq.push({nums[0], 0});
        long long subtract = 0, counter = 0;
        while (not pq.empty() and counter < k-1) {
            auto [var, index] = pq.top();
            pq.pop();
            subtract = var;
            if (index < nums.size() - 1) {
                pq.push({var - nums[index] + nums[index+1], index+1});
                pq.push({var + nums[index+1], index+1});
            }
            counter++;
        }
        return largest - subtract;
    }
};

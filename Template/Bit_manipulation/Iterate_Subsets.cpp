// Get info for every possible subset
for (int state = 1; state < total; state++) {
   int info = 0;
   for (int i = 0; i < N; i++) {
         if ((state >> i) & 1) {
            info += v[i];
         }
   }
   subsetState[state] = info;
}

// Get Every possible subset of currect set
for (int sub = state; sub > 0; sub = (sub-1)&state) {
   doSomething();
}
// Example
// *************************************************************************
class Solution {
public:
    int minimumTimeRequired(vector<int>& jobs, int k) {
        int N = jobs.size(), total = 1 << N;
        vector<vector<int>> dp(k+1, vector<int>(total, INT_MAX));
        dp[0][0] = 0;
        vector<int> stateTime(total);
        for (int state = 1; state < total; state++) {
            int sum = 0;
            for (int i = 0; i < N; i++) {
                if ((state >> i) & 1) {
                    sum += jobs[i];
                }
            }
            stateTime[state] = sum;
        }
        for (int state = 0; state < total; state++)
            for (int i = 1; i <= k; i++) {
                for (int sub = state; sub > 0; sub = (sub-1)&state) {
                    dp[i][state] = min(dp[i][state], max(dp[i-1][state-sub], stateTime[sub]));
                }
            }
        return dp[k][total-1];
    }
};
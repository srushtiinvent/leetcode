class Solution {
public:
    int minOperations(vector<int>& nums, int sum) {
        vector<int> dp(sum + 1, 1e9);
        dp[0] = 0;
        
        for (int x : nums) {
            unordered_map<int, int> min_cost;
            int d = 0;
            int curr = x;
            
            while (true) {
                int m = 0;
                long long val = curr;
                
                while (val <= sum) {
                    if (min_cost.find(val) == min_cost.end()) {
                        min_cost[val] = d + m;
                    } else {
                        min_cost[val] = min(min_cost[val], d + m);
                    }
                    
                    if (val == 0) break; 
                    val *= 2;
                    m++;
                }
                
                if (curr == 0) break;
                curr /= 2;
                d++;
            }
            
            vector<int> next_dp = dp;
            for (auto& pair : min_cost) {
                int v = pair.first;
                int c = pair.second;
                
                if (v == 0) continue; 
                
                for (int j = 0; j <= sum - v; ++j) {
                    if (dp[j] != 1e9) {
                        next_dp[j + v] = min(next_dp[j + v], dp[j] + c);
                    }
                }
            }
            
            dp = next_dp;
        }
        
        return dp[sum] == 1e9 ? -1 : dp[sum];
    }
};
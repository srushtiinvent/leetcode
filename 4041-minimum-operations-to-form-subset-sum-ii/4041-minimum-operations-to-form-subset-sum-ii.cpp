class Solution {
public:
    int minOperations(vector<int>& nums, int sum) {
        vector<int> dp(sum + 1, 1e9);
        dp[0] = 0;
        
        int current_max_sum = 0; 
        vector<int> min_cost(sum + 1, 1e9);
        vector<int> valid_vals; 
        valid_vals.reserve(150); 
        for (int x : nums) {
            valid_vals.clear();
            
            int d = 0;
            int curr = x;
            int max_val_from_x = 0;
            
            while (true) {
                int m = 0;
                long long val = curr;
                
                while (val <= sum) {
                    if (min_cost[val] > d + m) {
                        if (min_cost[val] == 1e9 && val > 0) {
                            valid_vals.push_back(val);
                        }
                        min_cost[val] = d + m;
                        if (val > max_val_from_x) max_val_from_x = val;
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
            
            for (int v : valid_vals) {
                int c = min_cost[v];
                
                for (int j = 0; j <= current_max_sum; ++j) {
                    if (dp[j] != 1e9 && j + v <= sum) {
                        if (dp[j] + c < next_dp[j + v]) {
                            next_dp[j + v] = dp[j] + c;
                        }
                    }
                }
                
                min_cost[v] = 1e9;
            }
            
            dp = std::move(next_dp);
            
            current_max_sum = min(sum, current_max_sum + max_val_from_x);
        }
        
        return dp[sum] == 1e9 ? -1 : dp[sum];
    }
};
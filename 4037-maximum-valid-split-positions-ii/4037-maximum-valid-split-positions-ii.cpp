class Solution {
public:
    int maxValidSplits(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return 0;

        vector<int> log2_val(n + 1, 0);
        for (int i = 2; i <= n; i++) {
            log2_val[i] = log2_val[i / 2] + 1;
        }

        int K = log2_val[n] + 1;
        vector<vector<int>> st(n, vector<int>(K));
        for (int i = 0; i < n; i++) {
            st[i][0] = nums[i];
        }
        for (int j = 1; j < K; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                st[i][j] = gcd(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }

        auto get_gcd = [&](int l, int r) {
            if (l > r) return 0;
            int j = log2_val[r - l + 1];
            return gcd(st[l][j], st[r - (1 << j) + 1][j]);
        };

        int max_score = 0;

        for (int k = -1; k < n; ++k) {
            int m = (k == -1) ? n : n - 1;
            if (m <= 1) continue;

            int G = (k == -1) ? get_gcd(0, n - 1) 
                              : gcd(get_gcd(0, k - 1), get_gcd(k + 1, n - 1));

            int ans_L = m - 1;
            int low = 0, high = m - 2;
            
            while (low <= high) {
                int mid = low + (high - low) / 2;
                int p_gcd;
                if (k == -1) {
                    p_gcd = get_gcd(0, mid);
                } else {
                    if (mid < k) p_gcd = get_gcd(0, mid);
                    else p_gcd = gcd(get_gcd(0, k - 1), get_gcd(k + 1, mid + 1));
                }

                if (p_gcd <= G) {
                    ans_L = mid;
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }

            int ans_R = -1;
            low = 0; high = m - 2;
            
            while (low <= high) {
                int mid = low + (high - low) / 2;
                int s_gcd;
                if (k == -1) {
                    s_gcd = get_gcd(mid + 1, n - 1);
                } else {
                    if (mid + 1 > k) s_gcd = get_gcd(mid + 2, n - 1);
                    else s_gcd = gcd(get_gcd(mid + 1, k - 1), get_gcd(k + 1, n - 1));
                }

                if (s_gcd <= G) {
                    ans_R = mid;
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }

            int current_score = max(0, ans_R - ans_L + 1);
            if (current_score > max_score) {
                max_score = current_score;
            }
        }

        return max_score;
    }
};
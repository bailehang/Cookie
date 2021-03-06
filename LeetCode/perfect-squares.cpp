class Solution {
public:
    int numSquares(int n) {
        static vector<int> dp(1, 0);
        while (dp.size() <= n) {
            int m = dp.size();
            int val = INT_MAX;
            for (int i = 1; i*i <= m; ++i)
                val = min(val, dp[m - i*i] + 1);
            dp.push_back(val);
        }
        return dp[n];
    }
};

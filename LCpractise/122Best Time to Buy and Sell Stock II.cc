class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() < 2) return 0;
        
        for (unsigned ii = prices.size() - 1; ii > 0; --ii) {
            prices[ii] -= prices[ii-1];
            if (prices[ii] < 0) prices[ii] = 0;
        }
        prices[0] = 0;
        return accumulate(prices.begin(), prices.end(), 0);
    }
};
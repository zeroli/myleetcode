class Solution {
public:
// keep an record of the maxProfit one can get so far, and the max profit one curbnf can get end with current event. One observation: once curbnf <0, the current end will be a good start point to buy stock
    int maxProfit(vector<int>& prices) {
        if (prices.size() < 2) return 0;
        
        int maxbnf = 0;
        int curbnf = 0;
        for (unsigned ii = 1; ii < prices.size(); ++ii) {
            curbnf += prices[ii] - prices[ii-1];
            if (curbnf < 0) curbnf = 0;
            if (maxbnf < curbnf) maxbnf = curbnf;
        }
        
        return maxbnf;
    }
};
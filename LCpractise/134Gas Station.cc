class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        assert(gas.size() == cost.size());
        if (gas.size() == 1) return cost[0]>gas[0]? -1:0;
        
        vector<int> residual(gas.size(), 0);
        transform(gas.begin(), gas.end(), cost.begin(), residual.begin(), std::minus<int>());
        int overallleft = accumulate(residual.begin(), residual.end(), 0);
        if (overallleft < 0) return -1;
        
        int gsize = residual.size();
        residual.resize(gsize * 2);
        copy_n(residual.begin(), gsize, back_inserter(residual));
        
        // find longest subsequence, that the summation so far always non-negative
        int sum = 0;
        int startpoint = 0;
        int length = 0;
        for (unsigned ii = 0; ii < residual.size(); ++ii) {
            sum += residual[ii];
            length++;
            if (sum < 0) {
                startpoint = ii + 1;
                sum = 0;
                length = 0;
            } 
            if (length == gsize) break;
        }
        return startpoint;
        
    }
};
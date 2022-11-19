class Solution {
public:
//We can always assign a neighbor with 1 more if the neighbor has higher a rating value. However, to get the minimum total number, we should always start adding 1s in the ascending order. We can solve this problem by scanning the array from both sides. First, scan the array from left to right, and assign values for all the ascending pairs. Then scan from right to left and assign values to descending pairs
    int candy(vector<int>& ratings) {
        vector<int> candies(ratings.size(), 1);
        // from left to right
        for (int ii = 0; ii < ratings.size()-1; ++ii) {
            if (ratings[ii+1] > ratings[ii]) candies[ii+1] = candies[ii]+1;
        }
        // from right to left
        for (int ii = ratings.size()-1; ii > 0; --ii) {
            if (ratings[ii-1] > ratings[ii] && candies[ii-1] <= candies[ii]) candies[ii-1] = candies[ii]+1;
        }
        
        return accumulate(candies.begin(), candies.end(), 0);
    }
};
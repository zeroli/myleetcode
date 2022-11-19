class Solution {
public:
// use bottom-up to get the miminal sum path candidates so far
    int minimumTotal(vector<vector<int> > &triangle) {
        if (triangle.empty()) return 0;
        if (triangle.size() == 1) return triangle[0][0];
        return minimumTotalRe(triangle);
    }
    
private:
// or use recursive: do have run time issue
    int minimumTotalRe(vector<vector<int> >& triangle) {
        return minimumTotalUtil(triangle, 0, 0);
    }

    int minimumTotalUtil(vector<vector<int> >& triangle, int level, int start) {
        if (level == triangle.size()) {// reach leaf
            return triangle.back()[start];
        }
        
        int rootval = triangle[level][start];
        int leftval = minimumTotalUtil(triangle, level+1, start);
        int rightval = minimumTotalUtil(triangle, level+1, start+1);
        return rootval + leftval + rightval;
    }
    
// use DP
    int minimumTotalDP(vector<vector<int>>& triangle) {
        if (triangle.empty()) return 0;
        if (triangle.size() == 1) return triangle[0][0];
            
        vector<int> minV(triangle.back()); 
        
        for(int i =triangle.size()-2; i>=0; --i)  
        {  
            for(int j =0; j<triangle[i].size(); ++j)  
            {  
              minV[j] = min(minV[j], minV[j+1]) + triangle[i][j];  
            }  
        } 
        return minV[0];
    }
};
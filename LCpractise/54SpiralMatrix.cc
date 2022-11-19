class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if (matrix.empty()) return vector<int>();
        if (matrix.size() == 1) return matrix[0];
        
        int xs = 0; 
        int ys = 0;
        int xe = matrix.size();
        int ye = matrix[0].size();
        vector<int> r;
        while (xs < xe && ys < ye) {
            int x, y;
            for (y = ys; y < ye; ++y) {
                r.push_back(matrix[xs][y]);
            }
            for (x = xs+1; x < xe; ++x) {
                r.push_back(matrix[x][ye-1]);
            }
            if (xs < xe-1) {
                for (y = ye-2; y >= ys; --y) {
                    r.push_back(matrix[xe-1][y]);
                }
            }
            if (ys < ye-1) {
                for (x = xe-2; x > xs; --x) {
                    r.push_back(matrix[x][ys]);
                }
            }
            ++xs;
            ++ys;
            --xe;
            --ye;
        }
        return r;
    }
};
class Solution {
public:
// do the BFS and flip visited 1 to 0 to avoid back visited again. 
    struct POINT {
        unsigned irow, icol;
        POINT(int _irow, int _icol): irow(_irow), icol(_icol) {};
        friend bool operator<(const POINT& a, const POINT& b) {
            if (a.irow < b.irow) return true;
            if (a.irow == b.irow && a.icol < b.icol) return true;
            return false;
        } 
    };
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty()) return 0;
        int count = 0;
        unsigned NROW = grid.size();
        unsigned NCOL = grid[0].size();
        
        set<POINT> unvi_n; 
        for (unsigned irow = 0; irow < NROW; ++irow)
        for (unsigned icol = 0; icol < NCOL; ++icol) {
            if (grid[irow][icol] == '1') {
                unvi_n.insert(POINT(irow, icol));
                ++count;
            }
            while (!unvi_n.empty()) {
                set<POINT>::iterator it = unvi_n.begin();
                unvi_n.erase(it);
                POINT curp = *it;
                grid[curp.irow][curp.icol] = '0';
                insertNeighbors(grid, curp, unvi_n);
            }
        }
        
        return count;
    }

private:
    void insertNeighbors(const vector<vector<char> >& grid, const POINT& curp, set<POINT>& unvi_n) {
        int upp = curp.icol + 1;
        if (upp < grid[0].size() && grid[curp.irow][upp] == '1') unvi_n.insert(POINT(curp.irow, upp));
        
        int downp = curp.icol - 1;
        if (upp >= 0 && grid[curp.irow][downp] == '1') unvi_n.insert(POINT(curp.irow, downp));
        
        int leftp = curp.irow - 1;
        if (leftp >= 0 && grid[leftp][curp.icol] == '1') unvi_n.insert(POINT(leftp, curp.icol));
        
        int rightp = curp.irow + 1;
        if (rightp < grid.size() && grid[rightp][curp.icol] == '1') unvi_n.insert(POINT(rightp, curp.icol));
    }
};
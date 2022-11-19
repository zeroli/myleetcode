class Solution {
public:
    struct POINT {
        unsigned irow, icol;
        POINT(int _irow, int _icol): irow(_irow), icol(_icol) {};
        friend bool operator<(const POINT& a, const POINT& b) {
            if (a.irow < b.irow) return true;
            if (a.irow == b.irow && a.icol < b.icol) return true;
            return false;
        } 
    };
    
    void solve(vector<vector<char>>& grid) {
        if (grid.empty()) return;
        unsigned NROW = grid.size();
        unsigned NCOL = grid[0].size();
        
        // do the transverse and flip O to X, if the block reach boundary, set to Y to avoid flip again
        for (unsigned irow = 0; irow < NROW; ++irow)
        for (unsigned icol = 0; icol < NCOL; ++icol) {
            set<POINT> unvi_n, vi_n;
            if (grid[irow][icol] == 'O') {
                unvi_n.insert(POINT(irow, icol));
            }
            bool reach_boundary = false;
            while (!unvi_n.empty()) {
                set<POINT>::iterator it = unvi_n.begin();
                POINT curp = *it;
                if (reachBoundary(curp, NROW, NCOL)) reach_boundary = true;
                vi_n.insert(curp);
                unvi_n.erase(it);
                grid[curp.irow][curp.icol] = 'X';
                insertNeighbors(grid, curp, unvi_n);
            }
            if (reach_boundary) {
                for (set<POINT>::iterator it = vi_n.begin(); it != vi_n.end(); ++it) {
                    grid[it->irow][it->icol] = 'Y';
                }
            }
        }
        
        for (unsigned irow = 0; irow < NROW; ++irow)
        for (unsigned icol = 0; icol < NCOL; ++icol) {
            if (grid[irow][icol] == 'Y') grid[irow][icol] = 'O';
        }
    }
    
private:
    bool reachBoundary(const POINT& curp, unsigned nrow, unsigned ncol) {
        if (curp.irow == 0 || curp.irow == nrow-1) return true;
        if (curp.icol == 0 || curp.icol == ncol-1) return true;
        return false;
    }
    
    void insertNeighbors(const vector<vector<char> >& grid, const POINT& curp, set<POINT>& unvi_n) {
        int upp = curp.icol + 1;
        if (upp < grid[0].size() && grid[curp.irow][upp] == 'O') unvi_n.insert(POINT(curp.irow, upp));
        
        int downp = curp.icol - 1;
        if (upp >= 0 && grid[curp.irow][downp] == 'O') unvi_n.insert(POINT(curp.irow, downp));
        
        int leftp = curp.irow - 1;
        if (leftp >= 0 && grid[leftp][curp.icol] == 'O') unvi_n.insert(POINT(leftp, curp.icol));
        
        int rightp = curp.irow + 1;
        if (rightp < grid.size() && grid[rightp][curp.icol] == 'O') unvi_n.insert(POINT(rightp, curp.icol));
    }
};
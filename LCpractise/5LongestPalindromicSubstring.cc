class Solution {
public:
// create a matrix with M(i,j) denotes whether s(i..j) is a palindrome
    string longestPalindrome(string s) {
        int M [s.size() * s.size()];
        partitions(&s[0], s.size(), M);
        
        string lp;
        for (unsigned ii = 0; ii < s.size(); ++ii)
        for (unsigned jj = ii; jj < s.size(); ++jj) {
            if (M[jj*s.size()+ii] && lp.size() < jj-ii+1) lp = s.substr(ii, jj-ii+1); 
        }
        return lp;
    }
    
private:
    //M[ii][jj]: bool for wheterh s[ii:jj] is a palindrome
    void partitions(char* s, int n, int M[]) {
        memset(M, 0, n*n*sizeof(int));
        for (int ii = 0; ii < n; ++ii) M[ii*n+ii] = 1;
        for (int ii = 0; ii < n-1; ++ii) {
            if (s[ii] == s[ii+1]) M[(ii+1)*n+ii] = 2;
        }
        
        for (int ii = n-3; ii >=0 ; --ii)
        for (int jj = ii+2; jj < n; ++jj) {
            if (s[ii] != s[jj]) M[jj*n+ii] = 0;
            else if (M[(jj-1)*n+ii+1]) M[jj*n+ii] = M[(jj-1)*n+ii+1] + 2;
            else M[jj*n+ii] = 0;
        }
    }
};
};
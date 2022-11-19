class Solution {
public:
// tracing left and right digit by devide and module to avoid overflow
    bool isPalindrome_p(int x) {
        assert (x > 0);
        int div = 1;
        while (x / div >= 10) {div *= 10;}
    
        while (x > 0 && div > 0) {
            if (x%10 != x / div) return false;
            else {
                x = (x % div) / 10;
                div /= 100;
            }
        }
        return true;
    }
    
    bool isPalindrome(int x){
        if (x > 0) return isPalindrome_p(x);
        if (x == 0) return true;
        if (x < 0) return false;
    }

};
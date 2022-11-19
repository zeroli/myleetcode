class Solution {
public:
    int reverse_p(int x)
    {
        assert( x >0 );
        // how to deal with > INT_MAX;
        int y = 0;
        while (x > 0) {
            if (y > (INT_MAX - x %10) / 10) return 0;
            y = y * 10 + x % 10;
            x /= 10;
        }
        return y;
    }
    
    int reverse(int x){
        if (x > 0) return reverse_p(x);
        if (x == 0) return 0;
        if (x < 0 && x > INT_MIN) return -1 * reverse_p(-x);
        if (x == INT_MIN) return 0;
    }
};
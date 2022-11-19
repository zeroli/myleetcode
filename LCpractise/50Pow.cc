class Solution {
public:
    double myPow(double x, int n) {
        if (x == 0) return 0; // what if n < 0
        if (n == 0) return 1;
        if (n < 0) return myPow(1.0/x, static_cast<unsigned>(-1*n));
        return myPow(x, static_cast<unsigned>(n));
    }

private:
    double myPow(double x, unsigned n) {
        double sum = 1.;
        double base = x;
        while(n > 0) {
            if (n & 1) sum *= base;
            base *= base;
            n /= 2;
        }
        return sum;
    }

};
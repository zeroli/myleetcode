class Solution {
public:
// since a number with digit abc = a*99+b*9 + a+b+c; therefore the final result is the different between n and 9(n-1)/9
    int addDigits(int num) {
        if (num < 10) return num;
        return num - 9*((num-1)/9);
    }
};
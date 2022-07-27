#include <iostream>

// return which one is bigger of 2 numbers(32bits) without using if condition check

// return 0 if n is 1, return 1 otherwise (=0)
int flip(int n)
{
    return 1 ^ n;
}

// return 1 if n is positive, return 0 otherwise (negative)
int sign(int n)
{
    return flip((n >> 31) & 1);
}

int selectBigger(int a, int b)
{
    int sign_a = sign(a);
    int sign_b = sign(b);
    int sign_c = sign(a - b);
    // if a and b have different sign, it might be overflow for a - b
    // then 1) a > 0, b < 0, then a-b has same sign of a (positive)
    // then 2) a < 0, b > 0, then a-b has same sign of a (negative)
    // else
    //   a and b have same sign, choose *sign_c*
    int a_b_different_sign = sign_a ^ sign_b;
    int a_b_same_sign = flip(a_b_different_sign);
    int k = a_b_different_sign * sign_a + a_b_same_sign * sign_c;
    return k * a + flip(k) * b;
}

int main()
{
    std::cout << "bigger one of (3, 2) is " << selectBigger(3, 1) << "\n";
    std::cout << "bigger one of (-12, -1) is " << selectBigger(-12, -1) << "\n";
    std::cout << "bigger one of (2^31, -1) is " << selectBigger(~(1<<31), -1) << "\n";
}

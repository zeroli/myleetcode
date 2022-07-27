/*
Write a program to compute and return the square root of an integer num.

Problem Note

    Where num is guaranteed to be a non-negative integer.
    If num is not a perfect square, then return floor(√num)

Example 1

Input: 4
Output: 2
Explanation: The square root of 4 is 2 as it is a perfect square.

Example 2

Input: 11
Output: 3
Explanation: The square root of 11 is 3.3166….., and since 11 is not a perfect square, then return only integer part of it.
*/

#include "utils.h"

// right choose "n/2" as start
// if sqrt(x) > x / 2 => x > x^2 / 4 => x < 4
// sqrt(2) = sqrt(3) = 1 = x / 2
int sqrtOfInt(int n)
{
    if (n < 2) return 1;

    int last_mid;
    int left = 1, right = n / 2;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (n / mid > mid) {  // prevent overflow for multiply
            left = mid + 1;
            last_mid = mid;
        } else if (n / mid < mid) {
            right = mid - 1;
        } else {
            return mid;
        }
    }
    return last_mid;
}

int main()
{
    {
        int n = 1;
        std::cout << "sqrt of " << n << ": " << sqrtOfInt(n) << "\n";
    }
    {
        int n = 2;
        std::cout << "sqrt of " << n << ": " << sqrtOfInt(n) << "\n";
    }
    {
        int n = 3;
        std::cout << "sqrt of " << n << ": " << sqrtOfInt(n) << "\n";
    }
    {
        int n = 4;
        std::cout << "sqrt of " << n << ": " << sqrtOfInt(n) << "\n";
    }
    {
        int n = 15;
        std::cout << "sqrt of " << n << ": " << sqrtOfInt(n) << "\n";
    }
    {
        int n = 16;
        std::cout << "sqrt of " << n << ": " << sqrtOfInt(n) << "\n";
    }
}

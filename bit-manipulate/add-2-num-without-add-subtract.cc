#include "utils.h"

// 求解两个整数的和，不能使用+/-符号
// 这题目就是想要模拟CPU中的ALU加法器的运算规则
/*
+ a  b carry sum
   0  0   0       0
   0  1    0       1
   1  0    0       1
   1  1     1       0
  通过观察发现：
   carry = a & b
   sum = a ^ b
   carry向左移动一位之后，然后再跟sum相加，就是最后的结果
   从而递归的调用add(a, b)，直到a/b其中一个为0
*/
int add(int a, int b)
{
    if (a == 0) return b;
    if (b == 0) return a;

    return add((a ^ b), ((a & b) << 1));
}

int main()
{
    {
        std::cout << "add(1+2)=" << add(1, 2) << "\n";
        std::cout << "add(-1+-1)=" << add(-1, -1) << "\n";
        std::cout << "add(+1+-1)=" << add(+1, -1) << "\n";
        std::cout << "add(-1+6)=" << add(-1, 6) << "\n";
        std::cout << "add(100+-6)=" << add(100, -6) << "\n";
        std::cout << "add(100+-600)=" << add(100, -600) << "\n";
    }
}

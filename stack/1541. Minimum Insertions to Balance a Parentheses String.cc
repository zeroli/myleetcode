#include "utils.h"

/*
Given a parentheses string s containing only the characters '(' and ')'.
 A parentheses string is balanced if:

    Any left parenthesis '(' must have a corresponding two consecutive right parenthesis '))'.
    Left parenthesis '(' must go before the corresponding two consecutive right parenthesis '))'.

In other words, we treat '(' as an opening parenthesis and '))' as a closing parenthesis.

    For example, "())", "())(())))" and "(())())))" are balanced, ")()", "()))" and "(()))" are not balanced.

You can insert the characters '(' and ')' at any position of the string to balance it if needed.

Return the minimum number of insertions needed to make s balanced.
*/

int MinInsertion(const std::string& str)
{
    int needs_left = 0;  // 我们需要让这个变量的值变大，
    int needs_right = 0;  // 这个值变小，即使它们的和一样
    // 因为一个左括号顶两个右括号
    #if 1  // 这是labuladong的方案
    for (auto c : str) {
        if (c == '(') {
            needs_right += 2;  // 需要2个右括号
            if (needs_right % 2 == 1) {  // 对左右括号的需求没影响啊
                needs_left++;  // 插入一个左括号，满足2个右括号
                needs_right--;  // 减少一个右括号的需求
            }
        } else {
            needs_right--;  // 提供一个右括号，右括号需求少了一个
            if (needs_right == -1) {  // 现在多了1个右括号
                needs_left++;  // 需要一个左括号与之对应
                needs_right = 1;  // 插入一个左括号之后，对应2个右括号，有了一个，还需要一个
            }
        }
    }
    #else  // 这是我自己的方案，有问题，case：只有一个右括号时needs_right=-1
    for (auto c : str) {
        if (c == '(') {
            needs_right += 2;
        } else {
            needs_right--;
            if (needs_right == -2) {
                needs_left++;
                needs_right = 0;
            }
        }
    }
    #endif
    return needs_left + needs_right;
}

int main()
{
    {
        std::string str = ")";
        std::cout << MinInsertion(str) << "\n";  // 2
    }
    {
        std::string str = "()";
        std::cout << MinInsertion(str) << "\n";  // 1
    }
    {
        std::string str = "()(";
        std::cout << MinInsertion(str) << "\n";  // 3
    }
    {
        std::string str = "(()))";
        std::cout << MinInsertion(str) << "\n";  // 1
    }
    {
        std::string str = "())";
        std::cout << MinInsertion(str) << "\n";  // 0
    }
    {
        std::string str = "))())(";
        std::cout << MinInsertion(str) << "\n";  // 3
    }
}

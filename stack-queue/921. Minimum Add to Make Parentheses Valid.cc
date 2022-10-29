#include "utils.h"

/*
A parentheses string is valid if and only if:

    It is the empty string,
    It can be written as AB (A concatenated with B), where A and B are valid strings, or
    It can be written as (A), where A is a valid string.

You are given a parentheses string s. In one move, you can insert a parenthesis at any position of the string.

    For example, if s = "()))", you can insert an opening parenthesis to be "(()))" or a closing parenthesis to be "())))".

Return the minimum number of moves required to make s valid.

Example 1:

Input: s = "())"
Output: 1

Example 2:

Input: s = "((("
Output: 3

*/

int Inserts(const std::string& str)
{
    int needs_left = 0;  // needs for "("
    int needs_right = 0;  // needs for ")"
    for (auto c : str) {
        if (c == '(') {
            needs_right++;  // 需要一个右括号
        } else {
            needs_right--;  // 对右括号的需求减少一个
            if (needs_right == -1) {  // 如果右括号现在提供多了
                needs_left++;  // 我们就需要左括号插入来匹配这些右括号
                needs_right = 0;  // reset，我们没有更多的右括号了，因为转移到对左括号的需求上了
            }
        }
    }
    return needs_left + needs_right;
}

int main()
{
    {
        std::string str = "())";
        std::cout << Inserts(str) << "\n";  // 1
    }
    {
        std::string str = "(((";
        std::cout << Inserts(str) << "\n";  // 3
    }
}

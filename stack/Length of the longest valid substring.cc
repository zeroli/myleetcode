#include "utils.h"

/*
Given a string consisting of opening and closing parenthesis,
 find the length of the longest valid parenthesis substring.

Examples:

Input : ((()
Output : 2
Explanation : ()

Input: )()())
Output : 4
Explanation: ()()

Input:  ()(()))))
Output: 6
Explanation:  ()(())
*/

int LongestValidSubstr(const std::string& str)
{
    std::stack<int> stk;
    stk.push(-1);

    int maxLen = 0;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == '(') {
            stk.push(i);
        } else {
            if (!stk.empty()) {  // "(" might be the first one
                stk.pop();  // must be one "(" or -1
            }
            // ( ..... ()，stack中当前有两个(，期间已经匹配了很多()。
            // 上面会弹出一个(，与当前这个)进行匹配，
            // 之后stk.top存储着就是最早的那个(。
            if (!stk.empty()) {
                maxLen = std::max(maxLen, i - stk.top());
            } else {
                // 如果stack没有了，说明我们遇到了一个单独的)，
                // 它是无论如何都无法匹配的，作为一个anchor存在。
                stk.push(i);
            }
        }
    }
    return maxLen;
}

int main()
{
    {
        std::string str = "((()";
        std::cout << LongestValidSubstr(str) << "\n";  // 2
    }
    {
        std::string str = ")()())";
        std::cout << LongestValidSubstr(str) << "\n";  // 4
    }
    {
        std::string str = "()(()))))";
        std::cout << LongestValidSubstr(str) << "\n";  // 6
    }
}

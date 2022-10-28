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

int LongestValidLength(const std::string& s)
{
    std::stack<std::pair<char, int>> stk;
    stk.push({')', -1});  // 只要不是'('就行
    int len = 0;
    for (int i = 0; i < s.size(); i++) {
        char c = s[i];
        if (c == '(') {
            stk.push({c, i});
        } else {
            // stk肯定不为空，不用判断empty
            // 因为我们已经push一个base了
            if (stk.top().first == '(') {
                stk.pop();
                // pop完之后，stk肯定也不为空
                // 因为'('肯定是我们之前push进去的
                // 我们已经push了一个base了
                len = std::max(len, i - stk.top().second);
            } else {
                // 如果当前stk top是非'('，则不能匹配当前的右括号)
                // 代表我们开始一个片段了，不能连续了。
                // 后面的将以这个')'为底
                stk.push({c, i});
            }
        }
    }
    return len;
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
    {
        assert(2 == LongestValidLength("()"));
        assert(0 == LongestValidLength("))))"));
        assert(0 == LongestValidLength("(((("));
        assert(2 == LongestValidLength("(((()"));
        assert(4 == LongestValidLength("()()"));
        assert(4 == LongestValidLength("(())"));
        assert(2 == LongestValidLength(")()"));
        assert(4 == LongestValidLength("(()))"));
        assert(4 == LongestValidLength(")(()))"));
        assert(2 == LongestValidLength("((()"));
        assert(4 == LongestValidLength(")()())"));
        assert(6 == LongestValidLength("()(()))))"));
        assert(6 == LongestValidLength("()())((()))))"));
    }
}

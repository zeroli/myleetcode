#include "utils.h"

/*
Given a string s containing just the characters '(', ')', '{', '}', '[' and ']',
determine if the input string is valid.

An input string is valid if:

    Open brackets must be closed by the same type of brackets.
    Open brackets must be closed in the correct order.

*/

bool CheckStkTop(char c, char top)
{
    if (c == ')' && top == '(') {
        return true;
    }
    if (c == ']' && top == '[') {
        return true;
    }
    if (c == '}' && top == '{') {
        return true;
    }
    return false;
}

bool IsValid(const std::string& str)
{
    std::stack<char> stk;
    for (auto c : str) {
        if (c == '(' || c == '[' || c == '{') {
            stk.push(c);
        } else {
            if (stk.empty())  {
                return false;
            }
            if (!CheckStkTop(c, stk.top())) {
                return false;
            }
            stk.pop();
        }
    }
    return stk.empty();
}

int main()
{
    {
        std::string str = "()";
        std::cout << std::boolalpha << IsValid(str) << "\n";
    }
    {
        std::string str = "()[]{}";
        std::cout << std::boolalpha << IsValid(str) << "\n";
    }
    {
        std::string str = "(]";
        std::cout << std::boolalpha << IsValid(str) << "\n";
    }
}

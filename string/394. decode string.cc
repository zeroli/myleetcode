#include "utils.h"

/*
给定一个经过编码的字符串，返回它解码后的字符串。

编码规则为: k[encoded_string]，表示其中方括号内部的 encoded_string 正好重复 k 次。
注意 k 保证为正整数。

你可以认为输入字符串总是有效的；
输入字符串中没有额外的空格，且输入的方括号总是符合格式要求的。

此外，你可以认为原始数据不包含数字，所有的数字只表示重复的次数 k ，
例如不会出现像 3a 或 2[4] 的输入。

示例 1：

输入：s = "3[a]2[bc]"
输出："aaabcbc"
示例 2：

输入：s = "3[a2[c]]"
输出："accaccacc"
示例 3：

输入：s = "2[abc]3[cd]ef"
输出："abcabccdcdcdef"
示例 4：

输入：s = "abc3[cd]xyz"
输出："abccdcdcdxyz"
*/

// 上述解法有点繁琐
// 其实这个就是一个表达式评估求值
// 比如: a + (b * 2 + 3) + (c + d * 3 + e)
// 表达式评估求值，需要借助栈数据结构
// 遍历原字符串时，不断的压栈，这里不区分不同的类型
// 碰到')'时，得要开始进行评估求值了，这里就是获取[]里面得字符串
// 然后根据[前面的数字获取重复次数
std::string DecodeStr1(const std::string& str)
{
    std::stack<std::string> stk;
    std::string repeatStr;
    int repeatCnt = 0;
    for (auto c : str) {
        if (c == ']') {
            while (!stk.empty() && stk.top() != "[") {
                repeatStr = stk.top() + repeatStr;
                stk.pop();
            }
            stk.pop();  // pop '['
            // 获取重复次数
            while (!stk.empty() && std::isdigit(stk.top()[0])) {
                repeatCnt *= 10;
                repeatCnt = stk.top()[0] - '0';
                stk.pop();
            }
            // 将重复的字符串，进行拼接，然后重新放入栈中
            std::string newStr;
            while (repeatCnt--) {
                newStr += repeatStr;
            }
            stk.push(newStr);
            repeatStr.clear();
            repeatCnt = 0;
        } else {
            stk.push(std::string(1, c));
        }
    }
    // 将stk中的字符进行拼接，形成解码的字符串
    std::string dstr;
    while (!stk.empty()) {
        dstr = stk.top() + dstr;
        stk.pop();
    }
    return dstr;
}

int main()
{
    {
        std::string str = "3[a]2[bc]";
        std::cout << DecodeStr1(str) << "\n";  // aaabcbc
    }
    {
        std::string str = "3[a2[c]]";
        std::cout << DecodeStr1(str) << "\n";  // accaccacc
    }
    {
        std::string str = "2[abc]3[cd]ef";
        std::cout << DecodeStr1(str) << "\n";  // abcabccdcdcdef
    }
    {
        std::string str = "abc3[cd]xyz";
        std::cout << DecodeStr1(str) << "\n";  // abccdcdcdxyz
    }

}

#if 0
// 这题需要考虑嵌套字符串中也需要解码，可采用递归实现。
// 注意的是我们需要先遍历一遍，
// 计算出所有字符所需要的内存空间，然后一次性分配内存，
// 之后根据各个字符串出现的次数填充解码字符串
// 我们可以将第一遍遍历到的字符串，保存到hash表中
int ParseNum(const std::string& str, int& i)
{
    int n = str.size();
    int num = 0;
    while (i < n && std::isdigit(str[i])) {
        num = num * 10 + str[i] - '0';
        i++;
    }
    // i points to '['
    return num;
}

// 解析[xyz]中括号中的字符串，主要字符串本身可能包括嵌套的]
std::string ParseStr(const std::string& str, int& i)
{
    int n = str.size();
    std::stack<char> stk;
    assert(str[i] == '[');
    int j = i + 1;
    while (i < n) {
        auto c = str[i];
        if (c == '[') {
            stk.push(c);
        } else {
            if (c == ']') {
                stk.pop(); // match [
            }
        }
        i++;
        if (stk.empty()) {
            break;
        }
    }
    // i points to after ']'
    return str.substr(j, i - j - 1);
}

std::string ParseStr1(const std::string& str, int& i)
{
    int n = str.size();
    int j = i;
    while (i < n) {
        if (std::isdigit(str[i])) {
            break;
        }
        i++;
    }
    // i points to digit
    return str.substr(j, i - j);
}

std::string DecodeStr(const std::string& str)
{
    std::map<std::string, int> map;  // 字符串 => 出现的次数
    int encode_total = 0;
    int n = str.size();

    for (int i = 0; i < n; ) {
        int num = 1;
        std::string ds;
        if (std::isdigit(str[i])) {
            num = ParseNum(str, i);
            ds = DecodeStr(ParseStr(str, i));
        } else {
            ds = ParseStr1(str, i);
        }
        map[ds] = num;
        encode_total += num * ds.size();
    }
    std::string decodeStr;
    decodeStr.reserve(encode_total);
    for (auto& m : map) {
        for (int i = 0; i < m.second; i++) {
            decodeStr.append(m.first);
        }
    }
    return decodeStr;
}
#endif

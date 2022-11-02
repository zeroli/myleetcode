/*
反转一个语句中的每个单词
*/

#include "utils.h"

std::string ReverseAllWords(std::string str)
{
    // 反转每个单词
    size_t start = 0, pos = 0;
    while ((pos = str.find(' ', start)) != std::string::npos) {
        std::reverse(str.begin() + start, str.begin() + pos);
        // 跳过所有的空格
        while (str[++pos] != ' ') {
            break;
        }
        start = pos;
    }
    std::reverse(str.begin() + start, str.end());  // 不要忘记最后一个单词
    // 反转整个字符串
    std::reverse(str.begin(), str.end());
    return str;
}

int main()
{
    {
        std::string str = "this is a sentence";
        assert("sentence a is this" == ReverseAllWords(str));
    }
    {
        std::string str = "this is a sentence ";
        assert(" sentence a is this" == ReverseAllWords(str));
    }
}

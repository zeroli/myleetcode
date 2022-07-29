#include "utils.h"

// next数组存储着以i为结尾的最大前后缀的长度
// 因此一个位置不匹配时，查看前面字符串是否又最长前后缀
// 就是看下next[j-1]对应的值(代表长度),
// 然后让这个长度对应的位置(index)与之前的字符进行匹配
std::vector<int> GetNext(const std::string& t)
{
    int j = 0;
    std::vector<int> next(t.size());
    next[0] = 0;
    for (int i = 1; i < t.size(); i++) {
        while (j > 0 && t[i] != t[j]) {
            j = next[j - 1];  // length，也就是下一个对齐匹配的位置
        }
        if (t[i] == t[j]) {
            j++;
        }
        next[i] = j;
    }
    std::cout << "next: " << next << "\n";
    return next;
}

int KmpStrstr(const std::string& s, const std::string& t)
{
    auto next = GetNext(t);
    int j = 0;
    for (int i = 0; i < s.size(); i++) {
        while (j > 0 && s[i] != t[j]) {
            j = next[j - 1];
        }
        if (s[i] == t[j]) {
            j++;
        }
        if (j == t.size()) {
            return i + 1 - j;
        }
    }
    return -1;
}
int main()
{
    std::string s = "abcdefdfaabaafedfgea";
    std::string t = "aabaaf";
    std::cout << KmpStrstr(s, t) << "\n";
    std::cout << KmpStrstr(s, "dfgea") << "\n";
}

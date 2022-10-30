#include "utils.h"

/*
Given three strings S1, S2 and S3,
 write a program which checks whether S3 is an interleaving of S1 and S2.

Problem Note

    S3 is said to be interleaving S1 and S2 if it contains all characters of S1 and S2
     and the order of all characters in individual strings is preserved.
*/

struct Indexes {
    int index1, index2;
    // index3 = index1 + index2
    friend std::ostream& operator<<(std::ostream& outstr, const Indexes& indexes)
    {
        return outstr << "(" << indexes.index1
            << "," << indexes.index2 << ")";
    }
    friend bool operator <(const Indexes& d1, const Indexes& d2)
    {
        if (d1.index1 != d2.index1) return d1.index1 < d2.index1;
        if (d1.index2 != d2.index2) return d1.index2 < d2.index2;
        return false;
    }
};
using Memo_t = std::map<Indexes, bool>;

bool Interleave(const std::string& str1, int index1,
            const std::string& str2, int index2,
            const std::string& str3, int index3,
            Memo_t& memo)
{
    if (memo.find({index1, index2}) != memo.end()) {
        return memo[{index1, index2}];
    }
    // base case
    if (index3 == str3.size()) {
        return true;
    }
    if (index1 >= str1.size() && index2 >= str2.size()) {
        return false;
    }

    auto c3 = str3[index3];

    // 有n1+n2格子，每个格子从str1或者str2中选一个当前字符进行填充
    bool ret = false;
    if (index1 < str1.size() && c3 == str1[index1]) {  // use c1 from str1
        if (Interleave(str1, index1 + 1, str2, index2, str3, index3 + 1, memo)) {
            memo[{index1, index2}] = true;
            return true;
        }
    }
    if (index2 < str2.size() && c3 == str2[index2]) {  // use c2 from str2
        if (Interleave(str1, index1, str2, index2 + 1, str3, index3 + 1, memo)) {
            memo[{index1, index2}] = true;
            return true;
        }
    }
    memo[{index1, index2}] = false;
    //std::cout << "memo: " << memo << "\n";
    return ret;
}

bool Interleave(const std::string& str1, const std::string& str2, const std::string& str3)
{
    if (str3.size() != str1.size() + str2.size()) {
        return false;
    }
    Memo_t memo;
    return Interleave(str1, 0, str2, 0, str3, 0, memo);
}

// 动态规划算法，迭代
class Solution {
public:
    bool isInterleave(const std::string& s1, const std::string& s2, const std::string& s3) {
        int n1 = s1.size(), n2 = s2.size(), n3 = s3.size();
        if (n3 != n1 + n2) {
            return false;
        }

        // 定义dp[i][j]为长度为i的s1，和长度为j的s2，
        // 交叉形成的字符串是否等于s3中的i+j长度的前缀
        std::vector<std::vector<bool>> dp(n1 + 1, std::vector<bool>(n2 + 1, true));

        for (size_t i = 1; i <= n1; ++i) {
            for (size_t j = 1; j <= n2; ++j) {
                // 如果长度为i的s1的最后一个字符与s3最后一个字符相等
                // 那么子问题就是s1前面i-1的字符串，与s2的整个字符串
                if (s1[i - 1] == s3[i + j - 1]) {  // s1 = s3
                    dp[i][j] = dp[i - 1][j];
                } else if (s2[j-1] == s3[i + j - 1]) {  // s2 = s3
                    dp[i][j] = dp[i][j - 1];
                } else {  // 没有一个相等，这条路走不通
                    dp[i][j] = false;
                }
            }
        }
        return dp[n1][n2];
    }
};

int main()
{
    {
        std::string str1 = "xxyzz";
        std::string str2 = "wyyzx";
        std::string str3 = "xxwyyzyzxz";
        std::cout << std::boolalpha << Interleave(str1, str2, str3) << "\n";  // true
        std::cout << std::boolalpha << Solution().isInterleave(str1, str2, str3) << "\n";
    }
    {
        std::string str1 = "xxyzz";
        std::string str2 = "wyyzx";
        std::string str3 = "xxwyyyxzzz";
        std::cout << std::boolalpha << Interleave(str1, str2, str3) << "\n";  // false
        std::cout << std::boolalpha << Solution().isInterleave(str1, str2, str3) << "\n";
    }
}

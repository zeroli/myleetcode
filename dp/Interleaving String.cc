#include "utils.h"

/*
Given three strings S1, S2 and S3,
 write a program which checks whether S3 is an interleaving of S1 and S2.

Problem Note

    S3 is said to be interleaving S1 and S2 if it contains all characters of S1 and S2
     and the order of all characters in individual strings is preserved.
*/

struct Indexes {
    int index1, index2, index3;

    friend std::ostream& operator<<(std::ostream& outstr, const Indexes& indexes)
    {
        return outstr << "(" << indexes.index1
            << "," << indexes.index2 << "," << indexes.index3 << ")";
    }
    friend bool operator <(const Indexes& d1, const Indexes& d2)
    {
        if (d1.index1 != d2.index1) return d1.index1 < d2.index1;
        if (d1.index2 != d2.index2) return d1.index2 < d2.index2;
        return d1.index3 < d2.index3;
    }
};
using Memo_t = std::map<Indexes, bool>;

bool Interleave(const std::string& str1, int index1,
            const std::string& str2, int index2,
            const std::string& str3, int index3,
            Memo_t& memo)
{
    if (memo.find({index1, index2, index3}) != memo.end()) {
        return memo[{index1, index2, index3}];
    }
    // base case
    if (index3 == str3.size()) {
        return true;
    }
    if (index1 >= str1.size() && index2 >= str2.size()) {
        return false;
    }

    auto c3 = str3[index3];

    bool ret = false;
    if (!ret && index1 < str1.size() && c3 == str1[index1]) {  // use c1 from str1
        ret = ret || Interleave(str1, index1 + 1, str2, index2, str3, index3 + 1, memo);
    }
    if (!ret && index2 < str2.size() && c3 == str2[index2]) {  // use c2 from str2
        ret = ret || Interleave(str1, index1, str2, index2 + 1, str3, index3 + 1, memo);
    }
    memo[{index1, index2, index3}] = ret;
    std::cout << "memo: " << memo << "\n";
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
    bool isInterleave(const string& s1, const string& s2, const string& s3) {
        if (s3.length() != s1.length() + s2.length())
            return false;
        std::vector<std::vector<bool>> f(s1.length() + 1,
                        std::vector<bool>(s2.length() + 1, true));
        for (size_t i = 1; i <= s1.length(); ++i)
            f[i][0] = f[i - 1][0] && s1[i - 1] == s3[i - 1];
        for (size_t i = 1; i <= s2.length(); ++i)
            f[0][i] = f[0][i - 1] && s2[i - 1] == s3[i - 1];
        for (size_t i = 1; i <= s1.length(); ++i)
            for (size_t j = 1; j <= s2.length(); ++j)
                f[i][j] = (s1[i - 1] == s3[i + j - 1] && f[i - 1][j])
                                || (s2[j - 1] == s3[i + j - 1] && f[i][j - 1]);
        return f[s1.length()][s2.length()];
    }
};

int main()
{
    {
        std::string str1 = "xxyzz";
        std::string str2 = "wyyzx";
        std::string str3 = "xxwyyzyzxz";
        std::cout << std::boolalpha << Interleave(str1, str2, str3) << "\n";  // true
    }
    {
        std::string str1 = "xxyzz";
        std::string str2 = "wyyzx";
        std::string str3 = "xxwyyyxzzz";
        std::cout << std::boolalpha << Interleave(str1, str2, str3) << "\n";  // false
    }
}

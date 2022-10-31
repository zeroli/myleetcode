#include "utils.h"

/*
Given a string of lowercase alphabets, count all possible substrings
 (not necessarily distinct) that has exactly k distinct characters.

Input: abc, k = 2
Output: 2
Possible substrings are {"ab", "bc"}

Input: aba, k = 2
Output: 3
Possible substrings are {"ab", "ba", "aba"}

Input: aa, k = 1
Output: 3
Possible substrings are {"a", "a", "aa"}
*/

// 这个题目与另一个固定窗口长度为k的题目，有所不同。
// 窗口长度不固定，不过肯定要大于等于k，因为它要求里面有k个不同的字符
// 所以在向右滑动窗口时，要看下是否unique字符个数>k了。
// >k时，我们需要收缩窗口左边，去除那些重复的字符，或者去除一个不同的字符，
// 从而重新达到k个不同字符的窗口

//  这个题目与992.Subarrays-with-K-Different-Integers，一样的思路。
// sliding-window\992.Subarrays-with-K-Different-Integers.cc
int CountSubstr(const std::string& str, int k)
{
    int start = 0;
    int cnt = 0;
    int prefix = 0;
    std::map<char, int> freqs;
    for (int i = 0; i < str.size(); i++) {
        freqs[str[i]]++;

#if 1  // 采用跟题目992的一样的代码样式
        // 遇到一个使窗口不平衡的字符了
        // 收缩窗口左边，重置prefix=0
        if (freqs.size() > k) {
            // prefix区域对于窗口属性不影响，收缩
            while (freqs[str[start]] > 1) {
                if (--freqs[str[start]] == 0) {
                    freqs.erase(str[start]);
                }
                start++;
            }
            // 找到左边界，继续收缩，使窗口平衡
            if (--freqs[str[start]] == 0) {
                freqs.erase(str[start]);
            }
            start++;
            prefix = 0;
        }

        if (freqs.size() == k) {
            while (freqs[str[start]] > 1) {
                if (--freqs[str[start]] == 0) {
                    freqs.erase(str[start]);
                }
                start++;
                prefix++;
            }
            cnt += prefix + 1;
        }
#else
        //   窗口不同字符个数>k了，
        // 看下收缩窗口左边是否还可以达到不同字符个数为k
        if (freqs.size() > k) {
            if (--freqs[str[start]] == 0) {
                freqs.erase(str[start]);
            }
            start++;
            prefix = 0;
        }
        // 开始统计前面有几个字符有重复，可以安全的去除
        while (freqs[str[start]] > 1) {
            if (--freqs[str[start]] == 0) {
                freqs.erase(str[start]);
            }
            prefix++;
            start++;
        }

        if (freqs.size() == k) {
            cnt += 1 + prefix;
        }
#endif
    }
    return cnt;
}

int main()
{
    {
        std::string str = "abc";
        int k = 2;
        std::cout << CountSubstr(str, k) << "\n";  // 2
    }
    {
        std::string str = "aba";
        int k = 2;
        std::cout << CountSubstr(str, k) << "\n";  // 3
    }
    {
        std::string str = "aa";
        int k = 1;
        std::cout << CountSubstr(str, k) << "\n";  // 3
    }
    {
        std::string str = "ababa";
        int k = 2;
        std::cout << CountSubstr(str, k) << "\n";  // 10
    }
}

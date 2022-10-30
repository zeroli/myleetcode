#include "utils.h"

/*
Given an input string s and a dictionary of words wordDict,
 write a program to determine if s can be divided into a space-separated
  sequence of one or more words that are present in the wordDict.

    Assume that both s and wordDict are non-empty.
    The same word in the dictionary may be reused multiple times in the division.
    You may assume the dictionary does not contain duplicate words.
*/

using Memo_t = std::map<int, bool>;
bool CanBreak(const std::string& word, int startIdx,
    const std::set<std::string>& wordDict, Memo_t& memo)
{
    if (memo.find(startIdx) != memo.end()) {
        return memo[startIdx];
    }

    if (startIdx >= word.size()) {
        return true;
    }

    for (int i = startIdx; i < word.size(); i++) {
        auto prefix = word.substr(startIdx, i - startIdx + 1);
        if (wordDict.find(prefix) != wordDict.end()) {
            if (CanBreak(word, i + 1, wordDict, memo)) {
                memo[startIdx] = true;
                return true;
            }
        }
    }
    memo[startIdx] = false;
    return false;
}

bool WordBreak(const std::string& word, const std::set<std::string>& wordDict)
{
    Memo_t memo;
    return CanBreak(word, 0, wordDict, memo);
}

bool WordBreakDP(const std::string& word, const std::set<std::string>& wordDict)
{
    int n = word.size();
    // substr with length of i could be broken into words??
    std::vector<bool> dp(n + 1);
    dp[0] = true;

    /*
    当我们拿到一个字符串，要判断它是否可以被break一些单词时，
    我们应该能想到它的子问题：
    一个字符串，最后一个字符，如果前面部分的字符串可以被break，
    而且同时最后一个字符也是一个单词，那么整个字符串就可以break，
    如果最后一个字符不是单词，那么最后两个单词呢？
    所以整个字符串就被划分了2个部分：
    1. 已知前面一部分字符串已经确定可以被break；
    2. 现在要判断后面一部分字符串作为整体，是否是一个单词
    如果同时满足，那么整个字符串就可以break
    对于这个过程，就要涉及到遍历
    */
    // dp[i] = dp[j] && str[j ... i) in wordDict, for any j in range [0, i)
    for (int i = 1; i <= n; i++) {
        // solve dp[i] ??
        for (int j = 0; j < i; j++) {
            if (dp[j]) {  // if prefix j length in wordDict, then check suffix
                auto suffix = word.substr(j, i - j);
                if (wordDict.find(suffix) != wordDict.end()) {
                    dp[i] = true;  // suffix in wordDict, then this break at location j is good
                    break;  // for i length, we're ok to have one result
                }
            }
        }
    }
    return dp[n];
}


int main()
{
    {
        std::string s = "AfterAcademy";
        std::set<std::string> dict = { "After", "Academy" };
        std::cout << std::boolalpha << WordBreak(s, dict) << "\n";  // true
        std::cout << std::boolalpha << WordBreakDP(s, dict) << "\n";
    }
    {
        std::string s = "HardThingAboutHardThings";
        std::set<std::string> dict = { "Hard", "Things", "Thing", "About" };
        std::cout << std::boolalpha << WordBreak(s, dict) << "\n";  // true
        std::cout << std::boolalpha << WordBreakDP(s, dict) << "\n";
    }
    {
        std::string s = "catsandog";
        std::set<std::string> dict = { "cats", "dog", "sand", "and", "cat" };
        std::cout << std::boolalpha << WordBreak(s, dict) << "\n";  // false
        std::cout << std::boolalpha << WordBreakDP(s, dict) << "\n";
    }
}

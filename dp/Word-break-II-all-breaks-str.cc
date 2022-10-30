/*
一个字符串和一个单词列表
break这个字符串成一个个单词，单词必须存在单词列表里面
返回所有的可能break的单词序列
这题是word break的加强版，那题目只要求判断是否可以break

s = "catsanddog",
dict = ["cat", "cats", "and", "sand", "dog"].
A solution is ["cats and dog", "cat sand dog"].
*/

#include "utils.h"

/*
仍然是动态规划+回溯递归给出路径
当然也可以递归dfs+memo
我们采用动态规划+回溯递归
*/

using Seq_t = std::vector<std::string>;
using Result_t = std::vector<Seq_t>;

void GenPaths(const std::string& s, int cur,
    const std::vector<std::vector<bool>>& prev,
    Seq_t& seq, Result_t& results)
{
    // 终止条件
    if (cur == 0) {
        // 反向给出切割的单词序列
        results.push_back({});
        for (auto it = seq.rbegin(); it != seq.rend(); ++it) {
            results.back().push_back(*it);
        }
        return;
    }
    for (int j = 0; j < cur; j++) {
        if (prev[cur][j]) {  // 长度为cur，可以从j处切开，整个字符串都可以break
            seq.push_back(s.substr(j, cur - j));  // 后面是一个单词
            GenPaths(s, j, prev, seq, results);
            seq.pop_back();
        }
    }
}

Result_t AllWordBreaks(const std::string& s,
    const std::unordered_set<std::string>& dict)
{
    int n = s.size();
    // 动态规划dp
    // 定义dp[i]为长度为i的字符串是否可以break：true/false
    std::vector<bool> dp(n+1, false);
    dp[0] = true;  // 0长度的字符串可以break

    // 记录长度为i的字符串，哪些位置可以满足
    // 前部分j长度可以break，同时后面[j,i)是一个单词
    std::vector<std::vector<bool>> prev(n+1, std::vector<bool>(n, false));

    for (int i = 1; i <= n; i++) {
        // 一次判断前面的长度j的前缀是否可以break
        for (int j = 0; j < i; j++) {
            if (dp[j] && dict.count(s.substr(j, i-j)) > 0) {
                dp[i] = true;
                prev[i][j] = true;
            }
        }
    }
    if (!dp[n]) {  // 判断整个字符串是否可以break？
        return {};
    }

    Result_t results;
    Seq_t seq;
    GenPaths(s, s.size(), prev, seq, results);
    return results;
}

int main()
{
    {
        std::string s = "catsanddog";
        std::unordered_set<std::string> dict = {
            "cat", "cats", "and", "sand", "dog"
        };
        std::cout << AllWordBreaks(s, dict) << "\n";
    }
    {
        std::string s = "AfterAcademy";
        std::unordered_set<std::string> dict = { "After", "Academy" };
        std::cout << AllWordBreaks(s, dict) << "\n";
    }
    {
        std::string s = "HardThingAboutHardThings";
        std::unordered_set<std::string> dict = { "Hard", "Things", "Thing", "About" };
        std::cout << AllWordBreaks(s, dict) << "\n";
    }
}

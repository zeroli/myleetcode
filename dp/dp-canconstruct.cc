#include "utils.h"

#if 0
using Memo_t = std::map<int, bool>;
using WordBank_t = std::set<std::string>;
bool canConstruct_(const std::string& word, const WordBank_t& wordBank, Memo_t& memo, int startIdx)
{
    if (memo.find(startIdx) != memo.end()) {
        return memo[startIdx];
    }
    if (startIdx == word.size()) {
        return true;  // empty string, always can construct
    }

    for (int i = startIdx; i < word.size(); i++) {
        auto prefix = word.substr(startIdx, i - startIdx + 1);
        if (wordBank.find(prefix) != wordBank.end()) {
            if (canConstruct_(word, wordBank, memo, i+1)) {
                memo[startIdx] = true;
                return true;
            }
        }
    }
    memo[startIdx] = false;
    return false;
}

#else
using Memo_t = std::map<std::string, bool>;
using WordBank_t = std::set<std::string>;
bool canConstruct_(const std::string& word, const WordBank_t& wordBank, Memo_t& memo)
{
    if (word.empty()) {
        return true;
    }
    if (memo.find(word) != memo.end()) {
        return memo[word];
    }
    for (auto&& wb : wordBank) {
        if (word.compare(0, wb.size(), wb) == 0) {
            if (canConstruct_(word.substr(wb.size()), wordBank, memo)) {
                memo[word] = true;
                return true;
            }
        }
    }
    memo[word] = false;
    return false;
}

#endif
bool canConstruct(const std::string& word, const WordBank_t& wordBank)
{
    Memo_t memo;
    return canConstruct_(word, wordBank, memo);
}

int main()
{
    {
        WordBank_t wordBank = {
            "ab", "abc", "cd", "def", "abcd"
        };
        std::cout << std::boolalpha << canConstruct("abcdef", wordBank) << "\n";
    }
}

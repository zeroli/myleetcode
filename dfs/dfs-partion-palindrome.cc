#include "utils.h"

using Pat_t = std::vector<std::string>;
using Results_t = std::vector<Pat_t>;
using Memo_t = std::map<int, std::vector<Pat_t>>;

bool isPalindrome(const std::string& str, int start, int end)
{
    while (start < end) {
        if (str[start++] != str[end--]) return false;
    }
    return true;
}

Results_t partitionPalindrome_(const std::string& str, int startIdx, Memo_t& memo)
{
    if (memo.find(startIdx) != memo.end()) {
        return memo[startIdx];
    }

    // base case
    if (startIdx == str.size()) {
        return {{}};
    }

    for (int i = startIdx; i < str.size(); i++) {
        // partition at location i to see prefix and suffx are able to be partitioned
        if (isPalindrome(str, startIdx, i)) {
            auto prefix = str.substr(startIdx, i - startIdx + 1);
            auto res = partitionPalindrome_(str, i + 1, memo);
            for (auto& pat : res) {
                pat.insert(pat.begin(), prefix);
                memo[startIdx].push_back(pat);
            }
        }
    }
    if (!memo[startIdx].empty()) {
        return memo[startIdx];
    }
    return {};
}

Results_t partitionPalindrome(const std::string& str)
{
    Memo_t memo;
    return partitionPalindrome_(str, 0, memo);
}

int main()
{
    std::string str = "aab";
    auto results = partitionPalindrome(str);
    std::cout << "partition palindromes as below:\n"
        << results << "\n";
}

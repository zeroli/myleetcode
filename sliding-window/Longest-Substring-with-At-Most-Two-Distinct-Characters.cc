#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cmath>

// 这题目与sliding-window\max-fruits-count-2-types.cc类似，那么K=2
int longestSubstrNoMoreK(const std::string& str, int k)
{
    int len = 0;
    int startIdx = 0;
    std::map<char, int> charFreq;
    for (int endIdx = 0; endIdx < str.size(); endIdx++) {
        charFreq[str[endIdx]]++;
        // extend until we reach the k occurrences
        // and then we need shrink
        while (charFreq.size() > k) {
            if (0 == --charFreq[str[startIdx]]) {
                charFreq.erase(str[startIdx]);
            }
            startIdx++;  // shrink
        }
        int newLen = endIdx - startIdx + 1;
        if (newLen > len) {
            std::cout << "max length: " << newLen
                << ": " << str.substr(startIdx, newLen)
                << "(" << startIdx << " => " << endIdx << ")\n";
            len = newLen;
        }
    }
    return len;
}

int main()
{
    std::string str = "araaci";
    std::cout << longestSubstrNoMoreK(str, 2) << "\n";
}

/*
Given a string str and an integer K, the task is to find the length of
 the longest sub-string S’ such that every character in S’ appears at least K times.


    Input: s = “xyxyyz”, k = 2
    Output: 5
    “xyxyy” is the longest sub-string where
    every character appears at least twice.
    Input: s = “geeksforgeeks”, k = 2
    Output: 2
*/

#include "utils.h"

// Divide & concur
class Solution {
    public:
    int longestSubstring(string s, int k) {
        int n = s.size();
        return longestSubstringUtil(s, 0, n, k);
    }
    int longestSubstringUtil(string &s, int start, int end, int k) {
        if (end < k) return 0;
        int countMap[26] = {0};
        // update the countMap with the count of each character
        for (int i = start; i < end; i++)
            countMap[s[i] - 'a']++;
        for (int mid = start; mid < end; mid++) {
            if (countMap[s[mid] - 'a'] >= k) continue;
            int midNext = mid + 1;
            while (midNext < end && countMap[s[midNext] - 'a'] < k) midNext++;
            return max(longestSubstringUtil(s, start, mid, k),
                    longestSubstringUtil(s, midNext, end, k));
        }
        return (end - start);
    }
};

// sliding window algorithm
class Solution {
public:
    int longestSubstring(string s, int k) {
        int countMap[26];
        int maxUnique = getMaxUniqueLetters(s);
        int result = 0;
        for (int currUnique = 1; currUnique <= maxUnique; currUnique++) {
            // reset countMap
            memset(countMap, 0, sizeof(countMap));
            int windowStart = 0, windowEnd = 0, idx = 0, unique = 0, countAtLeastK = 0;
            while (windowEnd < s.size()) {
                // expand the sliding window
                if (unique <= currUnique) {
                    idx = s[windowEnd] - 'a';
                    if (countMap[idx] == 0) unique++;
                    countMap[idx]++;
                    if (countMap[idx] == k) countAtLeastK++;
                    windowEnd++;
                }
                // shrink the sliding window
                else {
                    idx = s[windowStart] - 'a';
                    if (countMap[idx] == k) countAtLeastK--;
                    countMap[idx]--;
                    if (countMap[idx] == 0) unique--;
                    windowStart++;
                }
                if (unique == currUnique && unique == countAtLeastK)
                    result = max(windowEnd - windowStart, result);
            }
        }

        return result;
    }

    // get the maximum number of unique letters in the string s
    int getMaxUniqueLetters(string s) {
        bool map[26] = {0};
        int maxUnique = 0;
        for (int i = 0; i < s.length(); i++) {
            if (!map[s[i] - 'a']) {
                maxUnique++;
                map[s[i] - 'a'] = true;
            }
        }
        return maxUnique;
    }
};

/* DOESN'T WORK!!!  ==> hard
int LargestSubstrAtLeast(const std::string& str, int k)
{
    std::map<char, int> charFreqs;
    int match = 0;
    int beg = 0;
    int maxLen = 0;
    for (int i = 0; i < str.size(); i++) {
        auto c = str[i];
        if (charFreqs.find(c) != charFreqs.end()) {
            if (++charFreqs[c] == k) {  // we have new one match with freq >= k
                match++;
            }
        } else {
            ++charFreqs[c];
        }
        if (match == charFreqs.size()) {
            maxLen = std::max(maxLen, i - beg + 1);
        }

        // all chars are mathed with freq >= k
        while (match == charFreqs.size()) {
            // update length
            maxLen = std::max(maxLen, i - beg + 1);
            // shrink beg ?
            auto freq = --charFreqs[str[beg]];
            if (freq == (k-1)) {  // from k => k-1
                match--;
            }
            if (freq == 0) {
                charFreqs.erase(str[beg]);
            }
            beg++;
        }
    }
    return maxLen;
}
*/

int main()
{
    {
        std::string str = "xyxyyz";
        int k = 2;
        std::cout << LargestSubstrAtLeast(str, k) << "\n";  // 5
    }
}

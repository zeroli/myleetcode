class Solution {
public:

// assume there is no space inside, 
// s breakable is equivalent to find a k such that s[0..k] and s[k+1..] are both breakable. therefore there is subproblem inside which is suitable for DP
// (s, true) = (s[0..i], true) && (s[i+1], true) i = 0.. len-1
// array[i] means s[0..i] is true then s[0...i+1] = s[0..k] + s[k+1..i+1] for k = 0..i+1, or s[0...i+1] itself
    bool wordBreak(string s, unordered_set<string>& wordDict) {
        if (s.empty()) return false;
        vector<bool> breakable(s.size(), false);
        if (wordDict.find(s.substr(0,1)) != wordDict.end()) breakable[0] = true;
        
        for (int ii = 1; ii < s.size(); ++ii) {
            if (wordDict.find(s.substr(0, ii+1)) != wordDict.end()) { // substr as itself a word
                breakable[ii] = true;
                continue;
            }
            for (int kk = 0; kk < ii+1; ++kk) { // seperate into two substr
                if (breakable[kk] && wordDict.find(s.substr(kk+1, ii-kk)) != wordDict.end()) {
                    breakable[ii] = true;
                    break;
                }
            }
        }
        return breakable.back();
    }
};
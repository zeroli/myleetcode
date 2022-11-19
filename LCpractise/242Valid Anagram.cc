class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.size() != t.size()) return false;
        vector<int> count(32, 0); // seems 26 will be enough for lowercase alphabets
        for (int ii = 0; ii < s.size(); ++ii) ++count[s[ii]-'a'];
        for (int ii = 0; ii < t.size(); ++ii) {
            if (--count[t[ii]-'a'] < 0) return false;
        }
        return true;
    }
};
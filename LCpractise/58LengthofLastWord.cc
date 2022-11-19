class Solution {
public:
    int lengthOfLastWord(string s) {
        if (s.empty()) return NULL;
        int lastnonempty = s.size() - 1;
        for (unsigned int ii = s.size(); ii > 0; --ii) {
            if (s[ii-1] != ' ') {lastnonempty = ii - 1; break;}
        }
        if (lastnonempty < 0) return 0;
        unsigned found = s.substr(0, lastnonempty+1).find_last_of(" ");
        return lastnonempty - found;
    }
};
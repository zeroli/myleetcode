class Solution {
public:
    bool isValid(char c){
        if (c >= 'a' && c <= 'z') return true;
        if (c >= 'A' && c <= 'Z') return true;
        if (c >= '0' && c <= '9') return true;
        return false;
    }
    
    string preprocess(string& s){
        unsigned int jj = 0;
        unsigned int ii = 0;
        unsigned int len = 0;
        for (; ii < s.size() && jj < s.size(); ++ii){
            if(isValid(s[ii])) {len++; continue;}
            if (jj < ii) jj = ii;
            while(jj < s.size() && !isValid(s[jj])) {++jj;}
            if (jj < s.size()) {s[ii] = s[jj]; s[jj] = ' '; ++jj; len++;}
        }
        return s.substr(0, len);
    }
    
    bool isPalindrome(string s) {
        string s2 = preprocess(s);
        if(s2.empty()) return true;
        if(s2.size() == 1) return true;
    
        for(unsigned int ii = 0; ii < s2.size()/2; ++ii){
            if(tolower(s[ii]) != tolower(s[s2.size() - 1 - ii])) return false;
        }
        return true;
    }
};
class Solution {
public:
// use merge algorithm
    string longestCommonPrefix(const string& s1, const string& s2){
        auto sit = s1.cbegin();
        auto eit = s2.cbegin();
        int len = 0;
        for (; sit != s1.end() && eit != s2.end(); ++sit, ++eit) {
            if (*sit == *eit) ++len;
            else break;
        }
        if (len) {return s1.substr(0, len);}
        else {return "";}
    }
    
    string longestCommonPrefix(string* pstrs [], int start, int end) {
        if (start == end) return *pstrs[start];
        if (end - start == 1) return longestCommonPrefix(*pstrs[start], *pstrs[end]);
    
        int mid = start + (end - start) / 2;
        string cp1 = longestCommonPrefix(pstrs, start, mid);
        string cp2 = longestCommonPrefix(pstrs, mid+1, end);
        return longestCommonPrefix(cp1, cp2);
    }
    
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty()) return "";
        if (strs.size() == 1) return strs[0];
        if (strs.size() == 2) return longestCommonPrefix(strs[0], strs[1]);
        
        string** pstrs = new string* [strs.size()];
        int ii = 0;
        for (vector<string>::iterator it = strs.begin(); it != strs.end(); ++it) {
            pstrs[ii++] = &*it;
        }
        
        return longestCommonPrefix(pstrs, 0, strs.size()-1);
    }

};
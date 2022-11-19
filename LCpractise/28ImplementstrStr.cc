class Solution {
public:
//method: get familiar with the standard substring match algorithms: KMP algorithm prefix = postfix table, boyer-Moore algorithm, and Rabin-Karp

// KMP algorithm: preprocess the pattern to create prefix = postfix table
    int lprepos(const string& s) {
        if (s.empty()) return 0;
        if (s.size() == 1) return 1;
        
        int size = s.size();
        int ii = 0;
        while (ii < size) {
            if (s.substr(0, ii+1) != s.substr(size-ii-1, ii+1)) break;
            ++ii;
        }
        return ii;
    }
    

    vector<int> lpreposs(const string& s) { // could be improved
        vector<int> rv(s.size(), 0);
        for (int ii = 0; ii < s.size(); ++ii) {
            rv[ii] = lprepos(s.substr(0, ii+1));
        }
        return rv;
    }

// search for pattern, and if found unmatch, move to next position according to the table
    int strStr(string haystack, string needle) {
        if (haystack.size() < needle.size()) return -1;
        vector<int> lsp = lpreposs(needle);
        
        int ii = 0;
        int jj = 0;
        while (ii < haystack.size() && jj < needle.size()) {
            if (haystack[ii] == needle[jj]) {
                ++ii; ++jj;
            }
            else {
                if (jj > 0) jj = lsp[jj-1];
                else { jj = 0; ++ii;}
            }
        }
        if (jj == needle.size()-1) return ii - needle.size();
        return -1;
    }
};
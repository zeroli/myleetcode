class Solution {
public:
// simply solution: put into stack and pop out

// one can reverse the string and then reverse each word 
    void reverseWords(string &s) {
        preprocess(s); // remove unnecessary space
        if (s.empty()) return;
        reverseString(&s[0], s.size());
        reverseEachWord(s);
    }
    
private:
// user cases : "", " ", "   ", "1  ", "   1", "  1  2  ", "1"
    void preprocess(string&s) {
        char delimiter = ' ';
        size_t istart = s.find_first_not_of(delimiter);
        size_t ipre = 0;
        while (istart != string::npos) { // a valid word
            size_t iend = s.find_first_of(delimiter, istart);
            if (iend != string::npos) {// not the last valid character, could be the last valid word with some trailing space
                while (istart < iend) { // move this word, iend chould be string::npos
                    swap(s[istart++], s[ipre++]);
                }
                istart = s.find_first_not_of(delimiter, iend);//search next valid word
                if (istart != string::npos) s[ipre++] = ' '; // add space between
            } else {// the last valid word
                while (istart < s.size()) { // move this word
                    swap(s[istart++], s[ipre++]);
                }
                istart = string::npos;
            }
        }
        s.resize(ipre);
    }
    
    void reverseString(char* s, int n) {
        for (int ii = 0; ii < n/2; ++ii) {
            swap(s[ii], s[n-1-ii]);
        }
    }
    
    void reverseEachWord(string &s) {
        if (s.empty()) return;
        char delimiter = ' ';
        size_t istart = s.find_first_not_of(delimiter);
        while (istart != string::npos) {// a valid word
            size_t iend = min(s.size(), s.find_first_of(delimiter, istart)); // could be ::npos = -1
            reverseString(&s[istart], iend-istart);
            istart = s.find_first_not_of(delimiter, iend); // if iend reach end, istart always be string:npos
        }
    }
};
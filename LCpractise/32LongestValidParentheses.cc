class Solution {
public:
// data structure: use a stack to keep recorder the so far unmatched '(' index
// when loop the string, at postion i which is ')' having a matched '(': the way to calculate the lenght: i - the previous '('
    int longestValidParentheses(string s) {
        if (s.empty()) return 0;
        
        stack<int> unmatchlefts;
        int nextstart=0;
        int maxlen = 0;
        for (int ii = 0; ii < s.size(); ++ii) {
            if (s[ii] == '(') unmatchlefts.push(ii);
            else {
                if (unmatchlefts.empty()) {
                    nextstart = ii+1; // invalid ')' rest the start point
                } else {
                    unmatchlefts.pop();
                    if (unmatchlefts.empty()) {
                        maxlen = max(maxlen, ii-nextstart+1);
                    } else {
                        int prestart = unmatchlefts.top() + 1;
                        maxlen = max(maxlen, ii-prestart+1);
                    }
                }
            }
        }
        return maxlen;
    }
};
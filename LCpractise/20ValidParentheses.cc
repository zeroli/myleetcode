class Solution {
public:
    // use a stack to store the left operators, and whenever a right operator comes, check it pairing with the top of stack
    bool isValid(string s) 
    {
        if (s.empty()) return true;
        if (s.length()%2 == 1) return false;
        
        map<char, char> pair;
        pair[')'] = '('; pair[']'] = '['; pair['}'] = '{';
        set<char> lefts;
        lefts.insert('('), lefts.insert('['), lefts.insert('{');
    
        stack<char> unpaired_left;
        string::const_iterator it = s.begin();
        if (lefts.find(*it) == lefts.end()) return false; // ")", "]", "}"
        unpaired_left.push(*it);
        ++it;
    
        for (; it != s.end(); ++it){
            if (lefts.find(*it) == lefts.end()) {// ")", "]", "}"
                if (unpaired_left.empty()) return false;
                if (unpaired_left.top() != pair[*it]) return false;
                unpaired_left.pop();
            }
            else { // "(", "[", "{"
                unpaired_left.push(*it);
            }
        }
        
        if (unpaired_left.empty()) return true;
        return false;
    }
};
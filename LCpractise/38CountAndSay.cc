class Solution {
public:

// use two vectors, one store the char, the other one count, and generate the say by combine them
    string findnext(const string& A)
    {
        if (A.empty()) return "";
        
        // count
        vector<char> ch; // char to be said
        vector<int> count; // count
        string::const_iterator it = A.begin();
    
        while (it != A.end()) {
            char c = *it++;
            int ic = 1;
            while (it != A.end() && *it == c) {++ic; ++it;}
            ch.push_back(c);
            count.push_back(ic);
        }
    
        // say
        string next;
        for (unsigned int ii = 0; ii < ch.size(); ++ii){
            next += to_string(count[ii]) + string(1, ch[ii]);
        }
        return next;
    }
    
    string countAndSay(int n)
    {
        if (n == 0) return "";
        if (n == 1) return "1";
        
        string in = "11";
        n -= 2;
        while (n > 0){
            in = findnext(in);
            --n;
        } 
        return in;
    }
};
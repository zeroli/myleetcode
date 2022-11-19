class Solution {
public:
// sort the string , and use a map to count
    vector<string> anagrams(vector<string>& strs) {
        if (strs.empty()) return vector<string>();
        
        map<string, vector<string*>> count;
        for (int ii = 0; ii < strs.size(); ++ii) {
            string temp = strs[ii];
            sort(temp.begin(), temp.end());
            count[temp].push_back(&strs[ii]);
        }
        
        vector<string> r;
        for (map<string, vector<string*>>::const_iterator it =  count.begin(); it != count.end(); ++it) {
            const vector<string*>& v = it->second;
            if (v.size() > 1) {
                for (int ii = 0; ii < v.size(); ++ii) {
                    r.push_back(*v[ii]);
                }
            }
        }
        return r;
    }
    
};
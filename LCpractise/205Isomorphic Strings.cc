class Solution {
public:
// if use the first occurance of a distinct character as key , and its occurances as a ordered array, then the two strings should have the identical key->val map
    // get a map of the occurance locations of a ith new char
    // first occurance of the character will create the map corresponding relation, and then use count to check whether they are isomorphic
    void calMapChar2Idx(const string& s, map<int, vector<int> >& mchi2idx) {
        map<char, int> mchidx;
        int maxidx = 0;
        for (int ii = 0; ii < s.length(); ++ii) {
            if (mchidx.find(s[ii]) == mchidx.end()) mchidx[s[ii]] = maxidx++;
            int idx = mchidx[s[ii]];
            mchi2idx[idx].push_back(ii);
        }
    }
    
    bool isIsomorphic(string s, string t) {
        if(s.length() != t.length()) return false;
    
        map<int, vector<int> > mch2idx_s, mch2idx_t;
        calMapChar2Idx(s, mch2idx_s);
        calMapChar2Idx(t, mch2idx_t);
        
        // compare the two map
        map<int, vector<int> >::const_iterator sit = mch2idx_s.begin();
        map<int, vector<int> >::const_iterator tit = mch2idx_t.begin();
        for(; sit != mch2idx_s.end() && tit != mch2idx_t.end(); ++sit, ++tit){
            const vector<int>& vs = sit->second;
            const vector<int>& vt = tit->second;
            if (vs.size() != vt.size()) return false;
            if(!equal(vs.begin(), vs.end(), vt.begin())) return false;
        }
        return true;
    }
};
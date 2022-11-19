class Solution {
public:
// very good article: http://yucoding.blogspot.com/2013/02/leetcode-question-123-wildcard-matching.html

//For each element in s
//(1) If *s==*p or *p == ? which means this is a match, then goes to next element s++ p++.
//(2) If p=='*', this is also a match, but one or many chars may be available, so let us save this *'s position and the matched s position.
//(3) If not match, then we check if there is a * previously showed up,
//       if there is no *,  return false;
//       if there is an *,  we set current p to the next element of *, and set current s to the next saved s position
       
    bool isMatch(string s, string p) {
        int start = -1;
        int ss = 0;
        int is = 0, ip = 0;// the index currently point to
      while(is < s.size()) {
          if (s[is] == p[ip] || p[ip] == '?') {++is; ++ip; continue;}
          if (p[ip] == '*') {start = ip; ++ip; ss = is; continue;} // save current location in ss
          if (start >= 0) {// move ss forward, 
              ip = start +1; ++ss; is=ss;continue;}
            return false;
        }
        while (p[ip]=='*'){ip++;} // skip end *
        return ip == p.size();
      
    }
};
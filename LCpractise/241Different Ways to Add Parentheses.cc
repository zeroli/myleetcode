class Solution {
public:
// for each operator, recursively get the vector result for both side, and combine them together
    vector<int> diffWaysToCompute(string input) {
        vector<int> r;
        for (int ii = 0; ii < input.size()-1; ++ii) {
            if (input[ii] == '+' || input[ii] == '-' || input[ii] == '*') {
                vector<int> leftr = diffWaysToCompute(input.substr(0, ii));
                vector<int> rightr = diffWaysToCompute(input.substr(ii+1));
                for (int ll = 0; ll < leftr.size(); ++ll)
                for (int rr = 0; rr < rightr.size(); ++rr) {
                    if (input[ii] == '+') r.push_back(leftr[ll]+rightr[rr]);
                    if (input[ii] == '-') r.push_back(leftr[ll]-rightr[rr]);
                    if (input[ii] == '*') r.push_back(leftr[ll]*rightr[rr]);
                }
            }
        }
        if (r.empty()) r.push_back(atoi(input.c_str()));
        return r;
    }
};
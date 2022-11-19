class Solution {
public:
// use a stack to keep the so far found majority number
    int majorityElement(vector<int> &num) {
        stack<int> remain;
        vector<int>::const_iterator it = num.begin();
        remain.push(*it++);
        for (; it != num.end(); ++it) {
            if (!remain.empty() && *it != remain.top()) {
                remain.pop();
            }
            else {
                remain.push(*it);
            }
        }
        return remain.top();
    }
};
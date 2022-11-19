class Solution {
public:
// use carryover to carry the bit forward
    string addBinary(string a, string b) {
        if (b.size() > a.size()) swap(a, b);
        int minsize = b.size();
        int carryover = 0;
        int asize = a.size();
        int bsize = b.size();
        for (unsigned int ii = 0; ii < minsize; ++ii){
            int sum = (a[asize-ii-1]-'0') + (b[bsize-ii-1]-'0') + carryover;
            carryover = sum / 2;
            sum %= 2;
            a[asize-ii-1] = '0' + sum;
        }
        
        if (carryover) {
            for (unsigned int ii = minsize; ii < a.size(); ++ii){
                int sum = (a[asize-ii-1]-'0') + carryover;
                carryover = sum / 2;
                sum %= 2;
                a[asize-ii-1] = '0' + sum;
            }
        }
        
        if (carryover) a.insert(a.begin(), '1');
        return a;
    }
};
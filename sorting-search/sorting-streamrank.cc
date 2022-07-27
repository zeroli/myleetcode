#include <iostream>
#include <vector>
#include <string>
#include <cassert>

struct RankNode {
    int left_size = 0;
    RankNode* left = nullptr;
    RankNode* right = nullptr;
    int data = -1;

    RankNode(int d)
        : data(d)
    { }

    void Insert(int d)
    {
        if (d < data) {  // go to left
            if (left) {
                left->Insert(d);
            } else {
                left = new RankNode(d);
            }
            left_size++;
        } else {  // go to right
            if (right) {
                right->Insert(d);
            } else {
                right = new RankNode(d);
            }
        }
    }

    // if found it, then it will return >= 0 rank value
    // otherwise, return -1
    int GetRank(int d)
    {
        if (d == data) {
            return left_size;
        } else if (d < data) {  // go to left
            if (left) {
                return left->GetRank(d);
            } else {
                return -1;
            }
        } else {  // go to right
            if (right && right->GetRank(d) >= 0) {
                return left_size + 1 + right->GetRank(d);
            } else {
                return -1;
            }
        }
    }

    ~RankNode() {
        if (left) delete left;
        if (right) delete right;
    }
};

struct StreamTrack {
    RankNode* root = nullptr;

    ~StreamTrack() {
        delete root;
    }

    void Track(int d)
    {
        if (root) {
            root->Insert(d);
        } else {
            root = new RankNode(d);
        }
    }

    int GetRankOfNum(int d)
    {
        assert(root);
        return root->GetRank(d);
    }
};

int main()
{
    auto stream = { 5, 1, 4, 4, 5, 9, 7, 13, 3 };
    StreamTrack st;
    for (int d: stream) {
        st.Track(d);
    }
    std::cout << "GetRankOfNum(1) = " << st.GetRankOfNum(1) << "\n";
    std::cout << "GetRankOfNum(3) = " << st.GetRankOfNum(3) << "\n";
    std::cout << "GetRankOfNum(5) = " << st.GetRankOfNum(5) << "\n";
}

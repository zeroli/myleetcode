/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */
class Solution {
public:
// use two pointers, one pointer on the first level, and the second on the second level, loop through the first level to generate the right links on the second level
    void connect(TreeLinkNode *root) {
        if (!root) return;
        TreeLinkNode* curlevelroot = root;
        TreeLinkNode* nextlevelroot = 0;
        
        nextlevelroot = curlevelroot->left;
        while(nextlevelroot) {
            while(curlevelroot) {
                curlevelroot->left->next = curlevelroot->right;
                if (curlevelroot->next) curlevelroot->right->next = curlevelroot->next->left;
                curlevelroot = curlevelroot->next;
            }
            curlevelroot = nextlevelroot;
            nextlevelroot = curlevelroot->left;    
        }
    }
};
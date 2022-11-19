/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class BSTIterator {
public:

// use inorder to keep a stack with the top as the current iteraotr pointing to
// when construct, goes to the most left one, i.e. the smallest one
// when call next: do the inorder transverse to the next smallest number
// may also implement: operator (), ->, *, 
// BSTIterator operator(BSTIterator& other), TreeNode& operator ->(), TreeNode& operator *().. check iterator book
    explicit BSTIterator(TreeNode *root) {
        if (!d_visited.empty()) {
            stack<TreeNode*> _visited;
            d_visited.swap(_visited);
        }
        push_left(root);
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        if (d_visited.empty()) return false;
        return true;
    }

    /** @return the next smallest number */
    int next() {
        TreeNode* next = d_visited.top();
        d_visited.pop();
        push_left(next->right);
        return next->val;
    }
    
    void push_left(TreeNode* root) {
        while (root) {
            d_visited.push(root);
            root = root->left;
        }
    }
    
private:
    stack<TreeNode*> d_visited;
};

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */
#ifndef INTERNAL_UTIL_H_
#define INTERNAL_UTIL_H_

#include <string>
#include <queue>
#include <vector>
#include <map>

struct TreeNode {
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    int data = 0;
    TreeNode(int d) : data(d) { }
};

std::vector<std::string> SplitBy(const std::string& str, const char d)
{
    std::vector<std::string> arr;
    for (int ic = 0; ic < str.size();) {
        auto c = str[ic];
        if (c == d || c == ' ') {
            ic++;
            continue;
        }
        if (std::isdigit(c) || c == '-') {
            int val = (c == '-') ? 0 : c - '0';
            ic++;
            while (ic < str.size() && std::isdigit(str[ic])) {
                val = 10 * val + str[ic] - '0';
                ic++;
            }
            val = (c == '-') ? -val : val;
            arr.push_back(std::to_string(val));
        } else {  // null
            arr.push_back("null");
            ic += 4;
        }
    }
    return arr;
}

// input format :  [5, 6, 3, 1, 7, 9, 4, null, null, 2, 0]
TreeNode* BuildTree(const std::string& input)
{
    std::string str(input);
    if (str.front() == '[') str.erase(0, 1);
    if (str.back() == ']') str.pop_back();
    auto strs = SplitBy(str, ',');

    auto root = new TreeNode(std::atoi(strs[0].c_str()));
    std::queue<TreeNode*> queue;
    queue.push(root);
    int i = 0;
    while (!queue.empty() && i < strs.size()) {
        auto cur = queue.front();
        queue.pop();
        if (i + 1 < strs.size()) {
            auto&& lv = strs[i + 1];
            if (lv != "null") {
               auto l = new TreeNode(std::atoi(lv.c_str()));
                queue.push(l);
                cur->left = l;
            }
        }
        if (i + 2 < strs.size()) {
            auto&& rv = strs[i + 2];
            if (rv != "null") {
                auto r = new TreeNode(std::atoi(rv.c_str()));
                queue.push(r);
                cur->right = r;
            }
        }
        i += 2;
    }
    return root;
}

#if 0  // python代码反序列化，支持[1,2,3,null,null,4,5,6,7]
def deserialize(self, data):
    if data == 'null': return None
    nodes = data.split(',')
    root = TreeNode(nodes[0])
    q = collections.deque([root])
    i = 0
    while q and i < len(nodes) - 2:
        cur = q.popleft()
        lv = nodes[i + 1]
        rv = nodes[i + 2]
        i += 2
        if lv != 'null':
            l = TreeNode(lv)
            q.append(l)
            cur.left = l
        if rv != 'null':
            r = TreeNode(rv)
            q.append(r)
            cur.right = r

    return root
#endif

std::ostream& operator <<(std::ostream& outstr, TreeNode* root)
{
    outstr << "[ ";
    std::queue<TreeNode*> queue;
    queue.push(root);
    std::vector<std::string> output;
    while (!queue.empty()) {
        auto node = queue.front();
        queue.pop();
        if (node) {
            output.push_back(std::to_string(node->data));
        } else {
            output.push_back("null");
        }
        if (node) {
            queue.push(node->left);
            queue.push(node->right);
        }
    }
    while (!output.empty()) {
        if (output.back() == "null") {
            output.pop_back();
        } else {
            break;
        }
    }
    for (auto&& out : output) {
        outstr << out << ", ";
    }
    outstr << " ]";
    return outstr;
}

#endif  // INTERNAL_UTIL_H_

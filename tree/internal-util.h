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
        if (std::isdigit(c)) {
            int val = 0;
            while (ic < str.size() && std::isdigit(str[ic])) {
                val = 10 * val + str[ic] - '0';
                ic++;
            }
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
    str.erase(0, 1);
    str.pop_back();
    auto strs = SplitBy(str, ',');
    std::map<int, TreeNode*> map;

    for (int i = strs.size() - 1; i >= 0; i--) {
        TreeNode* node = (strs[i] == "null") ? nullptr : new TreeNode(atoi(strs[i].c_str()));
        map[i] = node;
        if (node) {
            TreeNode* left = map[i * 2 + 1];
            TreeNode* right = map[i * 2 + 2];
            node->left = left;
            node->right = right;
        }
    }
    return map[0];
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

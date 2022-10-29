/*
Given two words (start and end), and a dictionary, find all shortest transformation sequence(s) from start
to end, such that:
• Only one letter can be changed at a time
• Each intermediate word must exist in the dictionary
For example, Given:
start = "hit"
end = "cog"
dict = ["hot","dot","dog","lot","log"]
Return
[
["hit","hot","dot","dog","cog"],
["hit","hot","lot","log","cog"]
]
Note:
• All words have the same length.
• All words contain only lowercase alphabetic characters.

*/

#include "utils.h"

/*
层序遍历，遍历到某一层，如果那一层由节点满足目标节点要求了，当遍历完这一层之后，就不再遍历了
遍历每一层时需要记录遍历树的路径

但是这题要求我们输出所有的最短转换路径上的所有单词，如果我们记录这些路径，内存开销比较大
而且一旦分叉，新的path需要clone出来，这种方案不太好
如何才能减少内存使用呢？
我们可以记录从一个节点到下一个节点的变换方法，比如说是把第几个字母变成什么字母
hit => hot(1,'i','o') => dot(0,'h','d') => dog(2,'t','g') => cog(0,'d','c')
用3个字节来表示变换的方法：
第1个字节表示第几个字母变换，第2个字节表示什么字母变换，第3个字节表示变换成什么字母
我们甚至可以用2个字节来表，不要记录由对什么字母进行变换，因为一旦知道一个单词，
根据位置就可以知道对应的字母
我们需要创建这些变换方法节点的对象指针，还需要一个指针指向它的前一个变换方法，
这样一旦我们找到目标单词后，我们可以根据反向指针进行遍历，求出变换的单词序列

VSCODE中要是能有插件支持在C++中注释里显示图片就好了
*/

struct Edit {
    Edit* prev = nullptr;
    char index = 0;
    char letter_from = '\0';

    Edit() = default;
    explicit Edit(Edit* prev_, char index_, char letter_from_)
        : prev(prev_), index(index_), letter_from(letter_from_)
    { }
};

using Seq_t = std::vector<std::string>;

Seq_t BacktracePath(const std::string& end, std::string w, Edit* edit)
{
    Seq_t seq;
    seq.push_back(end);
    seq.push_back(w);
    while (edit) {
        w[edit->index] = edit->letter_from;
        seq.push_back(w);
        edit = edit->prev;
    }
    std::reverse(seq.begin(), seq.end());
    return seq;
}

struct Node {
    std::string w;
    Edit* edit = nullptr;  // Node对象不销毁edit
    Node(const std::string& w_, Edit* edit_)
        : w(w_), edit(edit_)
    { }
};

std::vector<Seq_t> ShortestSequences(const std::string& start, const std::string& end,
        std::set<std::string>& dict)
{
    // 我们会利用dict来继续去重处理，以免进入死循环
    // 一旦发现一个新单词，将它从dict中去除
    dict.erase(start);

    std::vector<Seq_t> seqs;

    std::queue<Node> queue;
    queue.push({start, nullptr});

    while (!queue.empty()) {
        auto sz = queue.size();
        for (int i = 0; i < sz; i++) {
            auto node = queue.front();
            queue.pop();

            auto& w = node.w;
            Edit* edit = node.edit;
            // 去掉这时候才判断的逻辑，可以省去到下一层才遍历到end的开销
            // 一旦发现下一层有目标单词，直接回溯获取转换序列
            // 虽然下一层节点还是会放入queue中，但是我们不用遍历了
            #if 0
            if (node.w == end) {  // find one
                seqs.emplace_back(BacktracePath(end, edit));
                continue;  // 继续下一个同层节点，不再继续下层节点了
            }
            #endif
            for (int ic = 0; ic < w.size(); ic++) {
                auto& c = w[ic];
                auto letter_from = c;
                for (auto d = 'a'; d <= 'z'; d++) {
                    std::swap(c, d);
                    // 如果发现目标单词就在下一层
                    if (w == end) {
                        std::swap(c, d);  // 恢复之前的单词
                        seqs.emplace_back(BacktracePath(end, w, edit));
                    } else {
                        if (dict.count(w) > 0) {
                            queue.push({w, new Edit(edit, ic, letter_from)});
                            dict.erase(w);  // 从dict中去除w，起到去重的功能
                        }
                        std::swap(c, d);
                    }
                }
            }
        }
        // 如果当层节点遍历完之后，已经发现下一层有目标单词，
        // 代表所有最短路径的变换序列已经找到
        if (!seqs.empty()) {
            // 注意，我们并没有delete Edit*
            // 我们可以利用shared_ptr，或者自己实现简单的refcnt based对象来删除所有的Edit*
            // 因为每一层的Edit's prev应该指向了一些相同的父节点Edit*
            break;
        }
    }
    return seqs;
}

int main()
{
    {
        std::string start = "hit", end = "cog";
        std::set<std::string> dict = { "hot", "dot", "dog", "lot", "log" };
        std::cout << ShortestSequences(start, end, dict) << "\n";
        /*
        [
            ["hit","hot","dot","dog","cog"],
            ["hit","hot","lot","log","cog"]
        ]
        */
    }
}

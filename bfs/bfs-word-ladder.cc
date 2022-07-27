#include "utils.h"
#include <memory>
#include <queue>

using Dict_t = std::set<std::string>;
using Path_t = std::vector<std::string>;
using Results_t = std::vector<Path_t>;

struct Node {
    std::string word;
    std::shared_ptr<Node> parent;

    Node(const std::string& word_, const std::shared_ptr<Node>& p = nullptr)
        : word(word_), parent(p)
    { }
};
using NodePtr_t = std::shared_ptr<Node>;

Path_t genLadderSeq(const NodePtr_t& tail)
{
    Path_t path;
    NodePtr_t node = tail;
    while (node) {
        path.push_back(node->word);
        node = node->parent;
    }
    std::reverse(path.begin(), path.end());
    return path;
}

Results_t wordLadder(const std::string& startWord, const std::string& endWord, Dict_t& dict)
{
    std::queue<NodePtr_t> queue;
    queue.push(std::make_shared<Node>(startWord, nullptr));
    Results_t results;
    while (!queue.empty()) {
        auto nodePtr = queue.front();
        queue.pop();

        auto& word = nodePtr->word;
        if (word == endWord) {  // find the target word
            results.push_back(genLadderSeq(nodePtr));
            continue;
            //return results;  // if just need one result, return this one
        }

        for (char& wc : word) {
            for (char c = 'a'; c <= 'z'; c++) {
                if (c == wc) continue;
                std::swap(c, wc);
                if (dict.find(word) != dict.end()) {
                    if (word != endWord) {  // later, we may see endWord again
                        dict.erase(word);  // remove duplicated insertion
                    }
                    queue.push(std::make_shared<Node>(word, nodePtr));
                }
                std::swap(c, wc);
            }
        }
    }
    return results;
}

int main()
{
    std::string startWord = "hit";
    std::string endWord = "cog";
    Dict_t dict = { "hot", "dot", "dog", "lot", "log" };
    //dict.insert(startWord);
    dict.insert(endWord);
    auto results = wordLadder(startWord, endWord, dict);
    for (auto&& result : results) {
        std::cout << result << " : " << result.size() << "\n";
    }
}

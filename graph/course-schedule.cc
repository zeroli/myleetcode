#include "utils.h"
#include "graph-util.h"

using Prerequisites_t = std::vector<std::pair<int, int>>;
using Order_t = std::vector<Node_t>;

Graph_t BuildDAG(const Prerequisites_t& prerequisite)
{
    Graph_t graph;  // DAG
    for (auto&& courses : prerequisite) {
        Node_t from = std::to_string(courses.second);
        Node_t to = std::to_string(courses.first);
        graph[from].push_back(to);
    }
    return graph;
}
// dfs traverse all nodes
bool DetectCycle(Graph_t& graph, const Node_t& node, Visited_t& visited, Visited_t& onpath, Order_t& postorder)
{
    if (onpath.find(node) != onpath.end()) {
        return true;
    }
    if (visited.find(node) != visited.end()) {
        return false;
    }

    visited.insert(node);

    onpath.insert(node);
    for (auto&& neighbor : graph[node]) {
        if (DetectCycle(graph, neighbor, visited, onpath, postorder)) {
            return true;
        }
    }
    onpath.erase(node);
    // after all following courses are done, we add this node in post order
    postorder.push_back(node);
    return false;
}

// detect if there is a cycle ???
bool CanFinish(const Prerequisites_t& prerequisite)
{
    Visited_t visited;
    Visited_t onpath;
    Order_t postorder;
    auto graph = BuildDAG(prerequisite);
    std::cout << "graph as below:\n" << graph << "\n";
    for (auto&& edge : graph) {
        if (DetectCycle(graph, edge.first, visited, onpath, postorder)) {
            return false;
        }
    }
    std::reverse(postorder.begin(), postorder.end());
    std::cout << "in order taking courses: " << postorder << "\n";
    return true;
}

int main()
{
    {
        Prerequisites_t prerequisite = {
            { 1, 0 },
            { 2, 1 },
            { 3, 2}
        };
        std::cout << std::boolalpha << CanFinish(prerequisite) << "\n";
    }
    {
        Prerequisites_t prerequisite = {
            { 1, 0 },
            { 0, 1 }
        };
        std::cout << std::boolalpha << CanFinish(prerequisite) << "\n";
    }
}

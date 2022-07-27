#include "graph-util.h"

int dfs(Graph_t& graph, const Node_t& node, Visited_t& visited)
{
    if (visited.find(node) != visited.end()) {
        return 0;
    }
    visited.insert(node);
    // post-order traversal
    int cnt = 1;  // this node itself
    for (auto&& neighbor : graph[node]) {
        cnt += dfs(graph, neighbor, visited);
    }
    return cnt;
};

int LargestConnectedComponents(Graph_t& graph)
{
    Visited_t visited;
    int largest = 0;

    for (auto&& edge : graph) {
        int cnt = dfs(graph, edge.first, visited);
        if (cnt > largest) {
            largest = cnt;
        }
    }
    return largest;
}

int main()
{
    Graph_t graph = {
        {"0", {"8", "1", "5" }},
        {"1", {"0"}},
        {"5", {"0", "8"}},
        {"8", {"0", "5"}},
        {"2", {"3", "4"}},
        {"3", {"2", "4"}},
        {"4", {"3", "2"}},
    };
    std::cout << graph << "\n";
    int cnt = LargestConnectedComponents(graph);
    std::cout << "largest connected components: " << cnt << "\n";
}

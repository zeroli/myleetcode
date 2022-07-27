#include "graph-util.h"

bool dfs(Graph_t& graph, const Node_t& node, Visited_t& visited)
{
    if (visited.find(node) != visited.end()) {
        return false;
    }
    visited.insert(node);
    for (auto&& neighbor : graph[node]) {
        dfs(graph, neighbor, visited);
    }
    return true;
};

int CountConnectedComponents(Graph_t& graph)
{
    Visited_t visited;
    int cnt = 0;

    for (auto&& edge : graph) {
        if (dfs(graph, edge.first, visited)) {
            cnt++;
        }
    }
    return cnt;
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
    int cnt = CountConnectedComponents(graph);
    std::cout << "connected components: " << cnt << "\n";
}

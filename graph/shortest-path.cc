#include "graph-util.h"

int shortestPath(const Edges_t& edges, const Node_t& source, const Node_t& dest)
{
    auto graph = buildGraph(edges);

    std::set<Node_t> visited = { source };

    std::queue<PathDist_t> queue;
    queue.emplace(source, 0);
    while (!queue.empty()) {
        auto node = queue.front();
        queue.pop();

        if (node.first == dest) {
            return node.second;
        }
        for (const auto& neighbor : graph[node.first]) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                queue.emplace(neighbor, node.second + 1);
            }
        }
    }

    return -1;
}

int main()
{
    Edges_t edges = {
        { "w", "x" },
        { "x", "y" },
        { "z", "y" },
        { "z", "v" },
        { "w", "v" }
    };
    auto shortestPathLen = shortestPath(edges, "w", "z");
    std::cout << "shortest path from 'w' to 'z': " << shortestPathLen << "\n";
}

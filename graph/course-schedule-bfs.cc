#include "utils.h"
#include "graph-util.h"

using Prerequisites_t = std::vector<std::pair<int, int>>;
using Order_t = std::vector<Node_t>;
using Indegrees_t = std::map<Node_t, int>;

Graph_t BuildDAG(int ncourses, const Prerequisites_t& prerequisite, Indegrees_t& indegrees)
{
    Graph_t graph;  // DAG
    for (auto&& courses : prerequisite) {
        Node_t from = std::to_string(courses.second);
        Node_t to = std::to_string(courses.first);
        graph[from].push_back(to);
        indegrees[to]++;
    }
    return graph;
}

// bfs traverse all nodes
bool DetectCycle(Graph_t& graph, int ncourses, Indegrees_t& indegrees, Order_t& inorder)
{
    std::queue<Node_t> queue;
    for (int i = 0; i < ncourses; i++) {
        auto node = std::to_string(i);
        if (indegrees[node] == 0) {  // indegree is 0
            queue.push(node);
        }
    }
    int cnt = 0;
    while (!queue.empty()) {
        auto node = queue.front();
        queue.pop();

        cnt++;
        inorder.push_back(node);
        for (auto&& neighbor : graph[node]) {
            if (--indegrees[neighbor] == 0) {  // no more prerequisite, add to queue
                queue.push(neighbor);
            }
        }
    }
    // if all nodes are traversed, then no cycle
    return cnt != indegrees.size();
}

// detect if there is a cycle ???
bool CanFinish(int ncourses, const Prerequisites_t& prerequisite)
{
    Indegrees_t indegrees;
    Order_t inorder;
    auto graph = BuildDAG(ncourses, prerequisite, indegrees);
    std::cout << "graph as below:\n" << graph << "\n";
    std::cout << "indegree as below:\n" << indegrees << "\n";

    if (DetectCycle(graph, ncourses, indegrees, inorder)) {
        return false;
    }

    std::cout << "in order taking courses: " << inorder << "\n";
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
        std::cout << std::boolalpha << CanFinish(4, prerequisite) << "\n";
    }
    {
        Prerequisites_t prerequisite = {
            { 1, 0 },
            { 0, 1 }
        };
        std::cout << std::boolalpha << CanFinish(2, prerequisite) << "\n";
    }
}

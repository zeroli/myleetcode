#ifndef GRAPH_UTIL_H_
#define GRAPH_UTIL_H_

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <iterator>
#include <algorithm>
#include <queue>
#include <cmath>
#include <cstdlib>
#include <cstdint>

using Node_t = std::string;
using Edge_t = std::pair<Node_t, Node_t>;
using Edges_t = std::vector<Edge_t>;
using Neighbors_t = std::vector<Node_t>;
using Graph_t = std::map<Node_t, Neighbors_t>;
using PathDist_t = std::pair<Node_t, int>;
using Visited_t = std::set<Node_t>;

inline std::ostream& operator <<(std::ostream& ostream, const Neighbors_t& neighbors)
{
    ostream << "[";
    for (const auto& node : neighbors) {
        ostream << node << ", ";
    }
    ostream << "]";
    return ostream;
}

inline std::ostream& operator <<(std::ostream& ostream, const Graph_t& graph)
{
    ostream << "{\n";
    for (const auto& node : graph) {
        ostream << node.first << ": " << node.second << "\n";
    }
    ostream << "}";
    return ostream;
}

inline Graph_t buildGraph(const Edges_t& edges)
{
    Graph_t graph;
    for (auto&& edge : edges) {
        graph[edge.first].push_back(edge.second);
        graph[edge.second].push_back(edge.first);
    }
    std::cout << "graph as below:\n" << graph;
    return graph;
}

#endif  // GRAPH_UTIL_H_

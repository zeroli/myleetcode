#include "utils.h"
#include "graph/graph-util.h"

/*
练习Dijkstra's algorithm for shortest path
*/

template <typename Key, typename Val>
struct MinHeap {
    struct Item {
        Key key;
        Val val;
        Item(const Key& k, const Val& v)
            : key(k), val(v)
        { }

        friend bool operator <(const Item& item1, const Item& item2)
        {
            return item1.val < item2.val;
        }
    };

    void Insert(const Key& key, const Val& val)
    {
        vertices_.emplace_back(key, val);
        ShiftUp(vertices_.size() - 1);
    }

    // return the index which has smallest value
    const Item& Top() const
    {
        return vertices_[0];
    }

    // 弹出堆顶元素，同时调整最小堆
    void Pop()
    {
        std::swap(vertices_[0], vertices_.back());
        vertices_.pop_back();
        ShiftDown(0);
    }
    // 减少index所对应的节点value为`val`
    void UpdateKey(const Key& key, const Val& val)
    {
        auto iter = std::find_if(vertices_.begin(), vertices_.end(), [&key](const Item& item) {
                                return item.key == key;
                        });
        if (iter != vertices_.end()) {
            Item newItem = { key, val };
            if (newItem < *iter) { // update to smaller, shift up
                *iter = newItem;
                ShiftUp(iter - vertices_.begin());
            } else { // update to bigger, shift down
                *iter = newItem;
                ShiftDown(iter - vertices_.begin());
            }
        }
    }

    bool IsEmpty() const
    {
        return vertices_.empty();
    }
private:
    void ShiftUp(int index)
    {
        while (index > 0) {
            const auto& cur = vertices_[index];
            int parentIndex = index / 2;
            if (parentIndex >= 0) {
                const auto& parent = vertices_[parentIndex];
                if (cur < parent) {
                    std::swap(vertices_[parentIndex], vertices_[index]);
                    index = parentIndex;
                } else {
                    break;
                }
            }
        }
    }
    void ShiftDown(int index)
    {
        int n = vertices_.size();
        while (index < n) {
            int leftIndex = index * 2 + 1;
            int rightIndex = index * 2 + 2;
            int smallest = index;
            if (leftIndex < n && vertices_[leftIndex] < vertices_[smallest]) {
                smallest = leftIndex;
            }
            if (rightIndex < n && vertices_[rightIndex] < vertices_[smallest]) {
                smallest = rightIndex;
            }
            if (smallest != index) {
                std::swap(vertices_[smallest], vertices_[index]);
                index = smallest;
            } else {
                break;
            }
        }
    }
private:
    std::vector<Item> vertices_;
};

template <typename T, typename W>
struct WeightedGraph {
    struct ToNode {
        T node;
        W weight;
        ToNode(const T& n, const W& w)
            : node(n), weight(w)
        { }
    };

    WeightedGraph() = default;
    WeightedGraph(const std::vector<T>& vertices)
    {
        for (auto& v : vertices) {
            edges_[v] = {};
        }
    }

    using Neighbors_t = std::vector<ToNode>;

    void AddEdge(const T& from, const T& to, const W& weight) {
        edges_[from].emplace_back(to, weight);
    }

    const Neighbors_t& Neighbors(const T& node) const {
        auto iter = edges_.find(node);
        assert(iter != edges_.end());
        return iter->second;
    }

    using Iter_t = typename std::map<T, Neighbors_t>::const_iterator;
    Iter_t begin() const {
        return edges_.begin();
    }
    Iter_t end() const {
        return edges_.end();
    }
private:
    std::map<T, Neighbors_t> edges_;
};

using Vertex_t = int;
std::vector<Vertex_t> DijkstraShortestPath(WeightedGraph<Vertex_t, int>& graph, const Vertex_t& start, const Vertex_t& end)
{
    std::map<Vertex_t, Vertex_t> prev;
    prev[start] = Vertex_t(-1);

    // value is int for distance starting from `start` to one node
    MinHeap<Vertex_t, int> pq;
    std::map<Vertex_t, int> dist;
    for (const auto& edge : graph) {
        int weight = INT_MAX;
        if (edge.first == start) {
            weight = 0;
        }
        dist[edge.first] = weight;
        pq.Insert(edge.first, weight);
    }
    dist[start] = 0;

    while (!pq.IsEmpty()) {
        auto minItem = pq.Top();
        pq.Pop();

        if (minItem.key == end) {
            break;
        }
        for (const auto& neighbor: graph.Neighbors(minItem.key)) {
            int newDist = dist[minItem.key] + neighbor.weight;
            if (newDist < dist[neighbor.node]) {
                dist[neighbor.node] = newDist;
                pq.UpdateKey(neighbor.node, newDist);
                prev[neighbor.node] = minItem.key;
            }
        }
    }

    std::vector<Vertex_t> path;
    Vertex_t v = end;
    while (prev[v] != -1) {
        path.push_back(v);
        v = prev[v];
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
}


int main()
{
    WeightedGraph<Vertex_t, int> graph({0,1,2,3,4,5});
    graph.AddEdge(0, 1, 6);
    graph.AddEdge(0, 2, 8);
    graph.AddEdge(0, 3, 18);
    graph.AddEdge(1, 4, 11);
    graph.AddEdge(2, 3, 9);
    graph.AddEdge(4, 5, 3);
    graph.AddEdge(5, 3, 4);
    graph.AddEdge(5, 2, 7);

    std::cout << DijkstraShortestPath(graph, 0, 5) << "\n";
}

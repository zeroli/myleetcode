#ifndef UNION_FIND_H_
#define UNION_FIND_H_

struct UnionFind {
    std::vector<int> parent;
    int count;

    explicit UnionFind(int n)
    {
        count = n;
        parent.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    // union of p and q
    void Union(int p, int q)
    {
        int pr = Find(p);
        int pq = Find(p);
        if (pr == pq) {
            return;
        }
        parent[pr] = pq;
        count--;
    }

    // find root of x
    int Find(int x)
    {
        // connect all children of tree rooted at root(x) to its root
        if (parent[x] != x) {
            parent[x] = Find(parent[x]);
        }
        return parent[x];
    }

    // check if p and q are connected
    bool Connected(int p, int q)
    {
        int pr = Find(p);
        int pq = Find(p);
        return pr == pq;
    }

    // connected components count
    int Count() const
    {
        return count;
    }
};

#endif  // UNION_FIND_H_

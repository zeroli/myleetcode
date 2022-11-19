class Solution {
public:
// do topological sort
// step 1: generate the graphy to the form of neighbor list, and the degree of dependence, (three forms of graphs: matrix, neighbor list, and edge)
// step 2: find the possible roots (could be multiple)
// step 3: do the topologic sort eith use BFS using keep pushing into queue or DFS using recursive
    vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
          vector<int> visitedVs;//topologi sort
          if (numCourses < 1) return visitedVs;
          
          vector<queue<int> > G(numCourses, queue<int>());
          vector<int> degree(numCourses, 0);
          for (int ii = 0; ii < prerequisites.size(); ++ii) {
            int u = prerequisites[ii].second; // u->v, learn v must have u ready
            int v = prerequisites[ii].first;
            G[u].push(v);
            ++degree[v];
          }
          
          queue<int> indpVs;
          for (int ii = 0; ii < numCourses; ++ii) {
              if (!degree[ii]) indpVs.push(ii);
          }
          if (indpVs.empty()) return visitedVs;
          
          while(!indpVs.empty()) {
              int u = indpVs.front();
              indpVs.pop();
              visitedVs.push_back(u);
              while(!G[u].empty()) {
                  int v = G[u].front();
                  --degree[v];
                  if (!degree[v]) indpVs.push(v);
                  G[u].pop();
              }
          }
          
          if (visitedVs.size() < numCourses) visitedVs.clear();
          return visitedVs;
    }
};
class Solution {
public:
/*
below is the topologic sorting using BFS
L ← Empty list that will contain the sorted elements
S ← Set of all nodes with no incoming edges
while S is non-empty do
    remove a node n from S
    add n to tail of L
    for each node m with an edge e from n to m do
        remove edge e from the graph
        if m has no other incoming edges then
            insert m into S
if graph has edges then
    return error (graph has at least one cycle)
else 
    return L (a topologically sorted order)
*/

    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
          if (numCourses <=1) return true;
          
          //create the graph
          vector<queue<int> > G(numCourses, queue<int>());
          vector<int> degree(numCourses, 0);
          for (int ii = 0; ii < prerequisites.size(); ++ii) {
            int u = prerequisites[ii].second; // u->v, learn v must have u ready
            int v = prerequisites[ii].first;
            G[u].push(v);
            ++degree[v];
          }
          
          //find the possible forest roots
          queue<int> indpVs;
          for (int ii = 0; ii < numCourses; ++ii) {
              if (!degree[ii]) indpVs.push(ii);
          }
          if (indpVs.empty()) return false;
          
          
          vector<int> visitedVs;//topologi sort, 
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
          if (visitedVs.size() < numCourses) return false;
          return true;
    }
    
};
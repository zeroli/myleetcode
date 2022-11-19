/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */
class Solution {
public:
// to clone the graph, one can create a map<node*, node*> to keep the map from old nodes to new nodes in cloned graph. To create this map, one can use either BFS or DFS, and after the map created, one can transverse the graph again to create the links among the new nodes
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if (!node) return 0;

        map<UndirectedGraphNode*, UndirectedGraphNode*> visitedNodes;
        queue<UndirectedGraphNode*> unvisitedNodes;
        unvisitedNodes.push(node);

        // create nodes
        while (!unvisitedNodes.empty()) {
            UndirectedGraphNode* pn = unvisitedNodes.front();
            unvisitedNodes.pop();
            if (visitedNodes.find(pn) == visitedNodes.end()) {
                UndirectedGraphNode* pcn = new UndirectedGraphNode(pn->label);
                visitedNodes[pn] = pcn;
                
                vector<UndirectedGraphNode *>& neighbors = pn->neighbors;
                for (unsigned ii = 0; ii < neighbors.size(); ++ii) {
                    if (visitedNodes.find(neighbors[ii]) == visitedNodes.end()) {
                        unvisitedNodes.push(neighbors[ii]);
                    }
                }
            }
        }
        
        // establish neighbors
        map<UndirectedGraphNode*, UndirectedGraphNode*>::const_iterator mit = visitedNodes.begin();
        for (; mit != visitedNodes.end(); ++mit) {
            vector<UndirectedGraphNode *>& oneighbors = mit->first->neighbors;
            vector<UndirectedGraphNode *>& cneighbors = mit->second->neighbors;
            for (unsigned ii = 0; ii < oneighbors.size(); ++ii) {
                UndirectedGraphNode* pn = oneighbors[ii];
                cneighbors.push_back(visitedNodes[pn]);
            }
        }
        
        return visitedNodes[node];
    }

};
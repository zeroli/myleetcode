/*
Given the root of a binary tree, the value of a target node target,
 and an integer k, return an array of the values of all nodes that have a distance k from the target node.

You can return the answer in any order.

Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, k = 2
Output: [7,4,1]
Explanation: The nodes that are a distance 2 from the target node (with value 5) have values 7, 4, and 1.

Input: root = [1], target = 1, k = 3
Output: []

*/

// 建立节点跟它父节点之间的连接，树就变成了图，
// 然后利用DFS递归求解，或者建立一个图的邻接表，利用BFS进行求解

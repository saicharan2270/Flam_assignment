#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    bool hasCircularDependency(int n, vector<vector<int>>& edges) {
       vector<vector<int>> graph(n);
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
        }
        vector<int> color(n, 0);
        
       for (int i = 0; i < n; i++) {
            if (color[i] == 0) {
                if (hasCycleDFS(i, graph, color)) {
                    return true;
                }
            }
        }
        
        return false;
    }
    
private:
    bool hasCycleDFS(int node, vector<vector<int>>& graph, vector<int>& color) {
        color[node] = 1;
        
        for (int neighbor : graph[node]) {
            if (color[neighbor] == 1) {
                return true;
            }
            if (color[neighbor] == 0 && hasCycleDFS(neighbor, graph, color)) {
                return true;
            }
        }
        
        // Mark current node as completely processed (black)
        color[node] = 2;
        return false;
    }
};

// Alternative implementation using Kahn's algorithm (Topological Sort)
class SolutionKahn {
public:
    bool hasCircularDependency(int n, vector<vector<int>>& edges) {
        // Build adjacency list and calculate in-degrees
        vector<vector<int>> graph(n);
        vector<int> inDegree(n, 0);
        
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            inDegree[edge[1]]++;
        }
        
        // Initialize queue with nodes having in-degree 0
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }
        
        int processedNodes = 0;
        
        // Process nodes with in-degree 0
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            processedNodes++;
            
            // Reduce in-degree of neighbors
            for (int neighbor : graph[node]) {
                inDegree[neighbor]--;
                if (inDegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }
        
        // If we couldn't process all nodes, there's a cycle
        return processedNodes != n;
    }
};

// Prim's algorithm is a greedy algorithm used to find the minimum spanning tree (MST) of a connected, undirected graph. The algorithm starts with an arbitrary node and grows the MST by adding the shortest edge that connects the tree to a vertex not yet in the tree. This process is repeated until all vertices are included in the MST. 

#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits>

using namespace std;

// Data structure to represent an edge
struct Edge {
    int src, dest, weight;
};

// Function to initialize and add an edge to the adjacency list
void addEdge(vector<vector<pair<int, int>>>& adj, int u, int v, int weight) {
    adj[u].emplace_back(v, weight);
    adj[v].emplace_back(u, weight); // For undirected graph
}

vector<Edge> primMST(vector<vector<pair<int, int>>>& adj) {
    int V = adj.size();
    vector<bool> inMST(V, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<Edge> MST;
    vector<int> dist(V, numeric_limits<int>::max());
    vector<int> parent(V, -1);

    // Start with vertex 0
    pq.push({0, 0}); // {distance, vertex}

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        inMST[u] = true;

        for (const auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (!inMST[v] && weight < dist[v]) {
                dist[v] = weight;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    for (int i = 1; i < V; ++i) {
        MST.push_back({parent[i], i, dist[i]});
    }

    return MST;
}

int main() {
    int V = 5;
    vector<vector<pair<int, int>>> adj(V);

    // Adding edges to the graph
    addEdge(adj, 0, 1, 2);
    addEdge(adj, 0, 3, 6);
    addEdge(adj, 1, 2, 3);
    addEdge(adj, 1, 3, 8);
    addEdge(adj, 1, 4, 5);
    addEdge(adj, 2, 4, 7);
    addEdge(adj, 3, 4, 9);

    vector<Edge> MST = primMST(adj);

    cout << "Edges of Minimum Spanning Tree:\n";
    for (const auto& e : MST) {
        cout << e.src << " - " << e.dest << "  Weight: " << e.weight << "\n";
    }

    return 0;
}

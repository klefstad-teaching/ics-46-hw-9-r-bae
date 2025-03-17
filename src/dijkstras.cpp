#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    vector<int> distances(n, INF);
    previous.resize(n, -1);
    vector<bool> visited(n, false);
    distances[source] = 0;
    
    struct CompareNode {
        bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
            return a.second > b.second;
        }
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, CompareNode> pq;
    pq.push({source, 0});
    
    while (!pq.empty()) {
        auto [current, dist] = pq.top();
        pq.pop();

        if (visited[current])
            continue;
        
        visited[current] = true;
        
        for (const Edge& edge : G[current]) {
            int neighbor = edge.dst;
            int weight = edge.weight;
            
            if (!visited[neighbor] && distances[current] != INF && 
                distances[current] + weight < distances[neighbor]) {
                distances[neighbor] = distances[current] + weight;
                previous[neighbor] = current;
                
                pq.push({neighbor, distances[neighbor]});
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    
    if (distances[destination] == INF)
        return path;
    
    for (int v = destination; v != -1; v = previous[v])
        path.push_back(v);
    
    reverse(path.begin(), path.end());
    return path;
}

// Print the path and total cost
void print_path(const vector<int>& path, int total) {
    if (path.empty()) {
        cout << "No path exists." << endl;
        return;
    }
    
    cout << "Path: ";
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i < path.size() - 1)
            cout << " -> ";
    }
    cout << ", Total Cost: " << total << endl;
}

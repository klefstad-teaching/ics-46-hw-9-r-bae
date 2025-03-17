#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph & G, int source, vector<int>& previous)
{
	int numVerts = G.size();
    vector<int> dists(numVerts, INF);
    vector<bool> visited(numVerts, false);
    auto comparator = [](const pair<int, int>& a, const pair<int, int>& b) {return a.second > b.second;};
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comparator)> mh(comparator);
    dists[source] = 0;
    previous[source] = -1;

    mh.push({source, 0});
    while(!mh.empty()) {
    	int u = mh.top().first;
        mh.pop();
        if(visited[u]) 
            continue;
        visited[u] = true;
        for(Edge e : G[u]) {
        	int v = e.dst;
            int weight = e.weight;
            if (!visited[v]&&dists[u] + weight < dists[v]) {
            	dists[v] = dists[u] + weight;
                previous[v] = u;
                mh.push({v, dists[v]});
            }
        }
    }
    return dists;
}
vector<int> extract_shortest_path(const vector<int>& dists, const vector<int>& previous, int destination) {
	vector<int> path;
    for (int current = destination; current != -1; current = previous[current])
    	path.push_back(current);
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total) {
    for (int i = 0; i < v.size(); ++i)
    	cout << v[i] << " ";
    cout << endl;
    cout << "Total cost is " << total << endl;
}

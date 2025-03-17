#include "dijkstras.h"

// Helper function to print all shortest paths from source to all other vertices
void print_all_paths(const Graph& G, int source) {
    cout << "Shortest paths from vertex " << source << " to all other vertices:" << endl;
    
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, source, previous);
    
    for (int i = 0; i < G.numVertices; ++i) {
        if (i == source)
            continue;
        vector<int> path = extract_shortest_path(distances, previous, i);
        cout << "To vertex " << i << ": ";
        if (distances[i] == INF)
            cout << "No path exists" << endl;
        else
            print_path(path, distances[i]);
    }
}

int main() {
    while (true) {
        cout << "\nChoose a graph file to analyze:" << endl;
        cout << "1. small.txt" << endl;
        cout << "2. medium.txt" << endl;
        cout << "3. large.txt" << endl;
        cout << "4. largest.txt" << endl;
        cout << "5. Enter custom filename" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        
        int choice;
        cin >> choice;
        
        if (choice == 0)
            break;
        
        string filename;
        switch (choice) {
            case 1: filename = "small.txt"; break;
            case 2: filename = "medium.txt"; break;
            case 3: filename = "large.txt"; break;
            case 4: filename = "largest.txt"; break;
            case 5:
                cout << "Enter filename: ";
                cin >> filename;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                continue;
        }
        
        Graph G;
        try {
            file_to_graph(filename, G);
            cout << "Graph loaded successfully with " << G.numVertices << " vertices." << endl;
            int source = 0;
            cout << "Default source vertex is 0. Would you like to change it? (y/n): ";
            char response;
            cin >> response;
            
            if (response == 'y' || response == 'Y') {
                cout << "Enter source vertex (0 to " << G.numVertices - 1 << "): ";
                cin >> source;
                
                if (source < 0 || source >= G.numVertices) {
                    cout << "Invalid vertex. Using vertex 0 instead." << endl;
                    source = 0;
                }
            }
            print_all_paths(G, source);
        } catch (const runtime_error& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
    return 0;
}

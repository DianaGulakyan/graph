#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

// DFS ֆունկցիա՝ երկկողմանիությունը ստուգելու համար
bool dfsCheck(string u, int c, map<string, int>& color, map<string, vector<string>>& adj) {
    color[u] = c;

    for (size_t i = 0; i < adj[u].size(); i++) {
        string v = adj[u][i];
        if (color[v] == 0) {
            if (!dfsCheck(v, 3 - c, color, adj)) {
                return false;
            }
        } else if (color[v] == color[u]) {
            return false;
        }
    }
    return true;
}

int main() {
    int n, e;
    cout << "Մուտքագրեք գագաթների քանակը: ";
    cin >> n;
    cout << "Մուտքագրեք կողերի քանակը: ";
    cin >> e;

    map<string, vector<string>> adj;
    map<string, int> color;

    cout << "Մուտքագրեք կողերը (orinak: 1 2):" << endl;
    for (int i = 0; i < e; i++) {
        string u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        color[u] = 0;
        color[v] = 0;
    }

    bool bipartite = true;
    
    for (map<string, vector<string>>::iterator it = adj.begin(); it != adj.end(); ++it) {
        string node = it->first;
        if (color[node] == 0) {
            if (!dfsCheck(node, 1, color, adj)) {
                bipartite = false;
                break;
            }
        }
    }

    if (bipartite) {
        cout << "\nԱրդյունք։ Գրաֆը երկկողմանի է" << endl;
    } else {
        cout << "\nԱրդյունք։ Գրաֆը երկկողմանի չէ" << endl;
    }

    return 0;
}

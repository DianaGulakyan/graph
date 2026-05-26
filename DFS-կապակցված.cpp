#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
using namespace std;

// DFS ֆունկցիա երկկողմանիություն
void dfs( string u,
    map<string, vector<string>>& adj,
    set<string>& visited,
    vector<string>& comp
) {
    visited.insert(u);
    comp.push_back(u);
    for (size_t i = 0; i < adj[u].size(); i++) {
        string v = adj[u][i];
        if (visited.find(v) == visited.end()) {
            dfs(v, adj, visited, comp);
        }
    }
}
int main() {
    int n, e;
    cout << "--- Կապակցվածության ստուգում (DFS) ---" << endl;
    cout << "Մուտքագրեք գագաթների քանակը: ";
    cin >> n;
    cout << "Մուտքագրեք կողերի քանակը: ";
    cin >> e;
    map<string, vector<string>> adj;
    set<string> allVertices;
    cout << "Մուտքագրեք կողերը (օրինակ՝ A B, 1 2):" << endl;
    for (int i = 0; i < e; i++) {
        string u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        allVertices.insert(u);
        allVertices.insert(v);
    }
    set<string> visited;
    vector<vector<string>> components;

    // DFS բոլոր component-ների համար
    for (
        set<string>::iterator it = allVertices.begin();
        it != allVertices.end();
        ++it
    ) {
        string node = *it;
        if (visited.find(node) == visited.end()) {
            vector<string> comp;
            dfs(node, adj, visited, comp);
            components.push_back(comp);
        }
    }
    cout << "\n-----------------------------------" << endl;

    // Եթե միայն 1 component կա
    if (components.size() == 1) {
        cout << "Արդյունք: Գրաֆը ԿԱՊԱԿՑՎԱԾ է:" << endl;
    }

    // Եթե մեկից ավելի component կա
    else {
        cout << "Արդյունք: Գրաֆը ԿԱՊԱԿՑՎԱԾ ՉԷ:" << endl;
        cout << "\nՊատճառը՝ գրաֆը բաժանված է մի քանի component-ների:\n" << endl;

        // Տպում ենք component-ները
        for (size_t i = 0; i < components.size(); i++) {
            cout << "Component " << i + 1 << ": ";
            for (size_t j = 0; j < components[i].size(); j++) {
                cout << components[i][j] << " ";
            }
            cout << endl;
        }
    }
    return 0;
}

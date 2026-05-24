#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>

using namespace std;

// Ռեկուրսիվ DFS ֆունկցիա
void dfs(string u, map<string, vector<string>>& adj, set<string>& visited) {
    visited.insert(u);
    for (size_t i = 0; i < adj[u].size(); i++) {
        string v = adj[u][i];
        if (visited.find(v) == visited.end()) {
            dfs(v, adj, visited);
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
    cout << "Մուտքագրեք կողերը (օրինակ՝ 1 2):" << endl;
    for (int i = 0; i < e; i++) {
        string u, v;
        cout << i + 1 << "-րդ կողը: ";
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    if (n == 0) return 0;

    set<string> visited;
    string startNode = adj.begin()->first;
    
    // Սկսում ենք DFS փնտրումը
    dfs(startNode, adj, visited);

    cout << "\n-----------------------------------" << endl;
    if (visited.size() == n) {
        cout << "Արդյունք: Գրաֆը ԿԱՊԱԿՑՎԱԾ է:" << endl;
    } else {
        cout << "Արդյունք: Գրաֆը ԿԱՊԱԿՑՎԱԾ ՉԷ:" << endl;
    }

    return 0;
}

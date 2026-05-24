#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <string>

using namespace std;

int main() {
    int n, e;
    cout << "--- Կապակցվածության ստուգում (BFS) ---" << endl;
    cout << "Մուտքագրեք գագաթների քանակը: ";
    cin >> n;
    cout << "Մուտքագրեք կողերի քանակը: ";
    cin >> e;

    map<string, vector<string>> adj;
    cout << "Մուտքագրեք կողերը (օրինակ՝ A B):" << endl;
    for (int i = 0; i < e; i++) {
        string u, v;
        cout << i + 1 << "-րդ կողը: ";
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    if (n == 0) return 0;

    // BFS ալգորիթմի սկիզբը
    set<string> visited;
    queue<string> q;

    string startNode = adj.begin()->first;
    q.push(startNode);
    visited.insert(startNode);

    while (!q.empty()) {
        string u = q.front();
        q.pop();

        for (size_t i = 0; i < adj[u].size(); i++) {
            string v = adj[u][i];
            if (visited.find(v) == visited.end()) {
                visited.insert(v);
                q.push(v);
            }
        }
    }

    cout << "\n-----------------------------------" << endl;
    if (visited.size() == n) {
        cout << "Արդյունք: Գրաֆը ԿԱՊԱԿՑՎԱԾ է:" << endl;
    } else {
        cout << "Արդյունք: Գրաֆը ԿԱՊԱԿՑՎԱԾ ՉԷ:" << endl;
    }
    
    return 0;
}
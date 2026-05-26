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

    // BFS բոլոր component-ների համար
    for (
        set<string>::iterator it = allVertices.begin();
        it != allVertices.end();
        ++it
    ) {
        string startNode = *it;

        // Եթե դեռ այցելված չէ
        if (visited.find(startNode) == visited.end()) {
            vector<string> currentComponent;
            queue<string> q;
            q.push(startNode);
            visited.insert(startNode);
            while (!q.empty()) {
                string u = q.front();
                q.pop();
                currentComponent.push_back(u);
                for (size_t i = 0; i < adj[u].size(); i++) {
                    string v = adj[u][i];
                    if (visited.find(v) == visited.end()) {
                        visited.insert(v);
                        q.push(v);
                    }
                }
            }

            // Պահում ենք component-ը
            components.push_back(currentComponent);
        }
    }
    cout << "\n-----------------------------------" << endl;

    // Եթե միայն 1 component կա
    if (components.size() == 1) {
        cout << "Արդյունք: Գրաֆը ԿԱՊԱԿՑՎԱԾ է:" << endl;
    }

    // Եթե մի քանի component կա
    else {
        cout << "Արդյունք: Գրաֆը ԿԱՊԱԿՑՎԱԾ ՉԷ:" << endl;
        cout << "\nԲաժանված component-ները:\n" << endl;
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

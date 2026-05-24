#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>

using namespace std;

// BFS ֆունկցիա՝ երկկողմանիությունը ստուգելու համար
bool isBipartite(map<string, vector<string>>& adj) {
    map<string, int> color; // 0: չներկված, 1: գույն A, 2: գույն B
    
    // Սկզբնական շրջանում բոլորը չներկված են
    for (auto const& [node, neighbors] : adj) {
        color[node] = 0;
    }

    for (auto const& [startNode, neighbors] : adj) {
        if (color[startNode] == 0) {
            queue<string> q;
            q.push(startNode);
            color[startNode] = 1; // Ներկում ենք առաջին գույնով

            while (!q.empty()) {
                string u = q.front();
                q.pop();

                for (string v : adj[u]) {
                    if (color[v] == 0) {
                        // Ներկում ենք հակառակ գույնով (եթե 1 է՝ դարձնում ենք 2, և հակառակը)
                        color[v] = (color[u] == 1) ? 2 : 1;
                        q.push(v);
                    } else if (color[v] == color[u]) {
                        // Եթե հարևանը նույն գույնն ունի, գրաֆը երկկողմանի չէ
                        return false;
                    }
                }
            }
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
    cout << "Մուտքագրեք կողերը (օրինակ՝ s v):" << endl;
    for (int i = 0; i < e; i++) {
        string u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u); // Երկկողմանիությունը ստուգելիս գրաֆը դիտարկում ենք որպես չուղղորդված
    }

    if (isBipartite(adj)) {
        cout << "\nԱրդյունք: Գրաֆը ԵՐԿԿՈՂՄԱՆԻ է" << endl;
    } else {
        cout << "\nԱրդյունք: Գրաֆը ԵՐԿԿՈՂՄԱՆԻ ՉԷ" << endl;
    }

    return 0;
}

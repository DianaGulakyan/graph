#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

// DFS ֆունկցիա
bool dfsCheck(
    string u,
    int c,
    map<string, int>& color,
    map<string, vector<string>>& adj,
    map<string, string>& parent,
    vector<string>& oddCycle
) {
    color[u] = c;
    for (size_t i = 0; i < adj[u].size(); i++) {
        string v = adj[u][i];

        // Եթե դեռ չայցելված է
        if (color[v] == 0) {
            parent[v] = u;
            if (!dfsCheck(v, 3 - c, color, adj, parent, oddCycle)) {
                return false;
            }
        }

        // Եթե նույն գույնն ունեն և parent չէ
        else if (color[v] == color[u] && parent[u] != v) {

            // -------- ODD CYCLE ԿԱՌՈՒՑՈՒՄ --------

            vector<string> pathU;
            vector<string> pathV;
            string x = u;
            string y = v;

            // u-ից դեպի root
            while (x != "") {
                pathU.push_back(x);
                x = parent[x];
            }

            // v-ից դեպի root
            while (y != "") {
                pathV.push_back(y);
                y = parent[y];
            }
            reverse(pathU.begin(), pathU.end());
            reverse(pathV.begin(), pathV.end());
            int j = 0;

            // Գտնում ենք ընդհանուր ancestor-ը
            while (
                j < pathU.size() &&
                j < pathV.size() &&
                pathU[j] == pathV[j]
            ) {
                j++;
            }
            j--;

            // Կառուցում ենք ցիկլը
            vector<string> cycle;
            for (int k = pathU.size() - 1; k >= j; k--) {
                cycle.push_back(pathU[k]);
            }
            for (int k = j + 1; k < pathV.size(); k++) {
                cycle.push_back(pathV[k]);
            }
            cycle.push_back(u);
            oddCycle = cycle;
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
    cout << "Մուտքագրեք կողերը (օրինակ: A B, 1 2):" << endl;
    for (int i = 0; i < e; i++) {
        string u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        color[u] = 0;
        color[v] = 0;
    }
    map<string, string> parent;
    vector<string> oddCycle;
    bool bipartite = true;

    // DFS բոլոր component-ների համար
    for (
        map<string, vector<string>>::iterator it = adj.begin();
        it != adj.end();
        ++it
    ) {
        string node = it->first;
        if (color[node] == 0) {
            parent[node] = "";
            if (
                !dfsCheck(
                    node,
                    1,
                    color,
                    adj,
                    parent,
                    oddCycle
                )
            ) {
                bipartite = false;
                break;
            }
        }
    }

    // Եթե երկկողմանի է
    if (bipartite) {
        vector<string> setA;
        vector<string> setB;
        for (
            map<string, int>::iterator it = color.begin();
            it != color.end();
            ++it
        ) {
            if (it->second == 1)
                setA.push_back(it->first);
            else if (it->second == 2)
                setB.push_back(it->first);
        }
        cout << "\nԱրդյունք։ Գրաֆը ԵՐԿԿՈՂՄԱՆԻ է\n";
        cout << "\nԱռաջին կողմ (A): ";
        for (size_t i = 0; i < setA.size(); i++) {
            cout << setA[i] << " ";
        }
        cout << "\nԵրկրորդ կողմ (B): ";
        for (size_t i = 0; i < setB.size(); i++) {
            cout << setB[i] << " ";
        }
        cout << endl;
    }
    // Եթե երկկողմանի չէ
    else {
        cout << "\nԱրդյունք։ Գրաֆը ԵՐԿԿՈՂՄԱՆԻ ՉԷ\n";
        cout << "Պատճառը՝ պարունակում է կենտ երկարությամբ պարզ ցիկլ\n";
        cout << "Ցիկլը: ";
        for (size_t i = 0; i < oddCycle.size(); i++) {
            cout << oddCycle[i] << " ";
        }
        cout << endl;
    }
    return 0;
}

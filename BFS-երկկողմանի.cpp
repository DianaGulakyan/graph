#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

// BFS ֆունկցիա՝ երկկողմանիությունը ստուգելու համար
bool isBipartite(
    map<string, vector<string>>& adj,
    map<string, int>& color,
    vector<string>& setA,
    vector<string>& setB,
    vector<string>& oddCycle
) {
    map<string, string> parent;

    // Սկզբում բոլոր գագաթները չներկված են
    for (auto const& [node, neighbors] : adj) {
        color[node] = 0;
        parent[node] = "";
    }

    // Անցնում ենք բոլոր component-ներով
    for (auto const& [startNode, neighbors] : adj) {
        if (color[startNode] == 0) {
            queue<string> q;
            q.push(startNode);
            color[startNode] = 1;
            while (!q.empty()) {
                string u = q.front();
                q.pop();
                for (const string& v : adj[u]) {
                    // Եթե գագաթը դեռ ներկված չէ
                    if (color[v] == 0) {
                        color[v] = (color[u] == 1) ? 2 : 1;
                        parent[v] = u;
                        q.push(v);
                    }
                        
                    // Եթե հարևանները նույն գույնն ունեն
                    else if (color[v] == color[u]) {

                        // ԿԵՆՏ ՑԻԿԼԻ ԿԱՌՈՒՑՈՒՄ
                        vector<string> pathU;
                        vector<string> pathV;
                        string x = u;
                        string y = v;

                        // parent chain u-ի համար
                        while (x != "") {
                            pathU.push_back(x);
                            x = parent[x];
                        }

                        // parent chain v-ի համար
                        while (y != "") {
                            pathV.push_back(y);
                            y = parent[y];
                        }

                        // Գտնում ենք LCA-ն (ընդհանուր ancestor)
                        reverse(pathU.begin(), pathU.end());
                        reverse(pathV.begin(), pathV.end());
                        int i = 0;
                        while (
                            i < pathU.size() &&
                            i < pathV.size() &&
                            pathU[i] == pathV[i]
                        ) {
                            i++;
                        }
                        i--;
                        
                        // odd cycle կառուցում
                        vector<string> cycle;
                        for (int j = pathU.size() - 1; j >= i; j--) {
                            cycle.push_back(pathU[j]);
                        }
                        for (int j = i + 1; j < pathV.size(); j++) {
                            cycle.push_back(pathV[j]);
                        }
                        cycle.push_back(u);
                        oddCycle = cycle;
                        return false;
                    }
                }
            }
        }
    }

    // Եթե երկկողմանի է, բաժանում ենք կողմերի
    for (auto const& [node, c] : color) {
        if (c == 1)
            setA.push_back(node);
        else if (c == 2)
            setB.push_back(node);
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
    cout << "Մուտքագրեք կողերը (օրինակ՝ A B, 1 2):" << endl;
    for (int i = 0; i < e; i++) {
        string u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    map<string, int> color;
    vector<string> setA;
    vector<string> setB;
    vector<string> oddCycle;
    bool result = isBipartite(
        adj,
        color,
        setA,
        setB,
        oddCycle
    );
    if (result) {
        cout << "\nԳրաֆը ԵՐԿԿՈՂՄԱՆԻ է\n";
        cout << "\nԱռաջին կողմ (A): ";
        for (const string& node : setA) {
            cout << node << " ";
        }
        cout << "\nԵրկրորդ կողմ (B): ";
        for (const string& node : setB) {
            cout << node << " ";
        }
        cout << endl;
    }
    else {
        cout << "\nԳրաֆը ԵՐԿԿՈՂՄԱՆԻ ՉԷ\n";
        cout << "Պատճառը՝ պարունակում է կենտ երկարությամբ ցիկլ:\n";
        cout << "Ցիկլը: ";
        for (const string& node : oddCycle) {
            cout << node << " ";
        }
        cout << endl;
    }
    return 0;
}

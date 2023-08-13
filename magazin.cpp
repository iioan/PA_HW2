#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

#define NMAX 100001
int position[NMAX];
int parent[NMAX];
vector <int> adj[NMAX];
vector <int> reordered;

void dfs(int node) {
    stack <int> s;
    s.push(node);
    while (!s.empty()) {
        int curr = s.top();
        s.pop();
        position[curr] = reordered.size();
        reordered.push_back(curr);
        for (int i = adj[curr].size() - 1; i >= 0; i--) {
            s.push(adj[curr][i]);
        }
    }
}

int find_parental(int a, int b) {
    while (b != 0 && a != parent[b]) {
        b = parent[b];
    }
    if (b == 0) {
        return -1;
    } else {
        return 1;
    }
}

int main() {
    ifstream fin("magazin.in");
    ofstream fout("magazin.out");

    int n, m;
    fin >> n >> m;
    for (int i = 2; i <= n; i++) {
        fin >> parent[i];
        adj[parent[i]].push_back(i);
    }

    dfs(1);

    for (int i = 0; i < m; i++) {
        int x, timer;
        fin >> x >> timer;
        if (adj[x].size() == 0) {
            fout << "-1\n";
        } else {
            int pos = position[x];
            if (pos + timer > n) {
                fout << "-1\n";
            } else {
                int next_node = reordered[pos + timer];
                if (find_parental(x, next_node) != -1) {
                    fout << next_node << "\n";
                } else {
                    fout << "-1\n";
                }
            }
        }
    }
}

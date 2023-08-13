#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

#define NMAX 100001
vector <int> adj[NMAX];
vector <int> adj_rev[NMAX];
bool visited[NMAX];
stack <int> reordered;
int component[NMAX];
int grad_int[NMAX];
int no_comp;

void dfs1(int node) {
    visited[node] = true;
    for (int v = 0; v < (int) adj[node].size(); v++) {
        if (!visited[adj[node][v]]) {
            dfs1(adj[node][v]);
        }
    }
    reordered.push(node);
}

void dfs2(int node, int c) {
    component[node] = c;
    for (int v = 0; v < (int) adj_rev[node].size(); v++) {
        if (component[adj_rev[node][v]] == 0) {
            dfs2(adj_rev[node][v], c);
        }
    }
}

void kosaraju(int n) {
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs1(i);
        }
    }

    while (!reordered.empty()) {
        int node = reordered.top();
        reordered.pop();
        if (component[node] == 0) {
            no_comp++;
            dfs2(node, no_comp);
        }
    }
}

int main() {
    ifstream fin("ferate.in");
    ofstream fout("ferate.out");

    int n, m, s;
    fin >> n >> m >> s;
    for (int i = 0; i < m; i++) {
        int x, y;
        fin >> x >> y;
        adj[x].push_back(y);
        adj_rev[y].push_back(x);
    }

    kosaraju(n);

    for (int i = 1; i <= n; i++) {
        for (int v = 0; v < (int) adj[i].size(); v++) {
            if (component[i] != component[adj[i][v]]) {
                grad_int[component[adj[i][v]]]++;
            }
        }
    }

    int sol = 0;
    for (int i = 1; i <= no_comp; i++) {
        if (grad_int[i] == 0 && i != component[s]) {
            sol++;
        }
    }

    fout << sol << "\n";
}

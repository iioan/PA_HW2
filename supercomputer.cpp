#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;
#define NMAX 100001

vector <int> adj[NMAX];
vector <int> topo;
int grad_int[NMAX];
int set[NMAX];

int topologicalSort(int n) {
    int count = 0;
    queue <int> q;
    queue <int> lost;
    for (int i = 1; i <= n; i++) {
        if (grad_int[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        topo.push_back(node);

        for (auto &it : adj[node]) {
            grad_int[it]--;
            if (grad_int[it] == 0) {
                if (set[node] != set[it]) {
                    lost.push(it);
                } else if (set[node] == set[it]) {
                    q.push(it);
                }
            }
        }
        if (q.empty() && !lost.empty()) {
            while (!lost.empty()) {
                q.push(lost.front());
                lost.pop();
            }
            count++;
        }
    }
    return count;
}

int main() {
    int n, m;
    ifstream fin("supercomputer.in");
    ofstream fout("supercomputer.out");
    fin >> n >> m;

    for (int i = 1; i <= n; i++) {
        int x;
        fin >> x;
        set[i] = x;
    }

    for (int i = 1; i <= m; i++) {
        int x, y;
        fin >> x >> y;
        adj[x].push_back(y);
        grad_int[y]++;
    }

    int result = topologicalSort(n);
    fout << result << "\n";
}

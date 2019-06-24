#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool cyclefound = false;
queue<int> cycle;

void dfs(vector<vector<int>>& P, vector<bool>& marked, 
            vector<int>& path, int v, vector<bool>& visited) 
{
    marked[v] = true;
    for (int w : P[v]) {
        if (cyclefound)
            return;
        if (!marked[w]) {
            path[v] = w;
            dfs(P, marked, path, w, visited);
        }
        else if (v != path[w]){
            cyclefound = true;
            int c = w;
            while (c != v) {
                visited[c] = true;
                cycle.push(c);
                c = path[c];
            }
            cycle.push(v);
            visited[v] = true;
        }
    }
}

void findCycle(int N, vector<vector<int>>& P, vector<bool>& visited) {
    vector<int> path(N);
    vector<bool> marked(N, false);
    for (int i = 0; i < N; i++) {
        if (!marked[i])
            dfs(P, marked, path, i, visited);
    }
}

vector<int> planetDistance(int N, vector<vector<int>>& P, vector<bool>& visited) {
    vector<int> dist(N, 0);
    while (!cycle.empty()) {
        int v = cycle.front();
        cycle.pop();
        for (int w : P[v]) {
            if (!visited[w]) {
                dist[w] = dist[v]+1;
                cycle.push(w);
                visited[w] = true;
            }
        }
    }
    return dist;
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        int N;
        cin >> N;
        vector<vector<int>> Planets(N);
        for (int j = 0; j < N; j++) {
            int A, B;
            cin >> A >> B;
            Planets[A-1].push_back(B-1);
            Planets[B-1].push_back(A-1);
        }
        vector<bool> visited(N, false);
        findCycle(N, Planets, visited);
        vector<int> dist = planetDistance(N, Planets, visited);
        printf("Case #%d:", i + 1);
        for (int d : dist)
            cout << " " << d;
        cout << endl;
        cyclefound = false;
    }
}
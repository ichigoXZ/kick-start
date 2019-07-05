#include <iostream>
#include <queue>
#include <set>

using namespace std;

typedef pair<int, pair<int, int>> Edge;

struct comp{
    bool operator()(const Edge &a, const Edge &b)
    {
        return a.first > b.first;
    }
};

void dfs(int u, vector<bool> &marked, vector<vector<int>> &graph)
{
    marked[u] = true;
    for (auto v : graph[u]) {
        if (!marked[v])
            dfs(v, marked, graph);
    }
}

long long devide(int V, priority_queue<Edge, vector<Edge>, comp> &edges)
{
    vector<vector<int>> graph(V);
    vector<bool> marked(V, false);
    int found = 0;
    vector<pair<int, int>> zeros;
    while (!edges.empty() && found < V) {
        Edge e = edges.top();
        edges.pop();
        int u = e.second.first - 1;
        int v = e.second.second - 1;
        int l = e.first;
        if (marked[u] && marked[v]) continue;
        found++;
        if (l == 0)
           zeros.push_back(make_pair(u, v)); 
        marked[u] = true;
        marked[v] = true;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    fill(marked.begin(), marked.end(), false);
    int times = 0;
    for (int i = 0; i < V; i++)
        if (!marked[i]) {
            times++;
            dfs(i, marked, graph);
        }
    set<int> closetozero;
    for (auto zero : zeros) {
        int u = zero.first;
        int v = zero.second;
        for (int p : graph[u])
            if (p != v)
                closetozero.insert(p);
        for (int p : graph[v])
            if (p != u)
                closetozero.insert(p);
    }
    times += closetozero.size();
    return 1L << times;
}

int main()
{
    int T;
    int V, E;
    int u, v, l;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        cin >> V >> E;
        priority_queue<Edge, vector<Edge>, comp> edges;
        for (int j = 0; j < E; j++) {
            cin >> u >> v >> l;
            edges.push(make_pair(l, make_pair(u, v)));
        }
        printf("Case #%d: %ld\n", i, devide(V, edges));
    }
}


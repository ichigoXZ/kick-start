#include <bits/stdc++.h>

#define ALL(x) (x).begin(), (x).end()

using namespace std;

int dfs(vector<vector<int>>& g, int u,  vector<bool>& marked) {
    marked[u] = true;
    int sweet = 1;
    for (int v : g[u]) {
        if(!marked[v]) {
            sweet += dfs(g, v, marked);
        }
    }
    return sweet;
}


int solve(vector<vector<int>>& black, int n, int m) {
    vector<bool> marked(n+1, false);
    vector<vector<int>> g(n+1);
    int sweet =  0;
    for (auto b : black) {
        g[b[0]].push_back(b[1]);
        g[b[1]].push_back(b[0]);
    }
    for (int i = 0; i < n; i++) {
        if (g[i].empty() || marked[i])
            continue;
        sweet += dfs(g, i, marked) - 1;
    }
    sweet += (n - 1 - sweet) * 2;
    return sweet;
}

int main()
{
    int T;
    cin >> T;
    for (int k = 1; k <= T; k++)
    {
        int n, m;
        cin >> n >> m;
        if (m == 0)
            printf("Case #%d: %d\n", k, 2 * (n - 1));
        else {
            vector<vector<int>> black(m);
            for (int i = 0; i < m; i++)
            {
                int c, d;
                cin >> c >> d;
                black[i].push_back(c);
                black[i].push_back(d);
            }
            printf("Case #%d: %d\n", k, solve(black, n, m));
        }
    }
}
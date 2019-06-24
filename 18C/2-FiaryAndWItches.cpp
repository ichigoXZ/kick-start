#include <iostream>
#include <vector>

using namespace std;

int isGoodPolygon(vector<int> &edges)
{
    if (edges.size() < 3)
        return 0;
    int mx = 0;
    int tot = 0;
    for (int e : edges)
    {
        tot += e;
        mx = max(e, mx);
    }
    if (mx * 2 < tot)
        return 1;
    return 0;
}

bool bit(int mask, int i)
{
    return (mask >> i) & 1;
}

int solve(vector<vector<int>> &L, int N, vector<int> &edges, int mask)
{
    int res = 0;
    if (mask + 1 == (1 << N))
    {
        res = isGoodPolygon(edges);
        return res;
    }

    for (int i = 0; i < N; i++)
        if (!bit(mask, i))
        {
            res += solve(L, N, edges, mask | (1 << i)); // not choose i
            for (int j = i + 1; j < N; j++)       // choose i : (i, j)
                if (!bit(mask, j) && L[i][j])
                {
                    edges.push_back(L[i][j]);
                    res += solve(L, N, edges, mask | (1 << i) | (1 << j));
                    edges.pop_back();
                }
            break;
        }
    return res;
}

int polygon(vector<vector<int>> &L, int N)
{
    vector<int> edges;
    int mask = 0;
    return solve(L, N, edges, mask);
}

int main()
{
    int T;
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        int N;
        cin >> N;
        vector<vector<int>> lengths(N);
        for (int j = 0; j < N; j++)
            for (int k = 0; k < N; k++)
            {
                int l;
                cin >> l;
                lengths[j].push_back(l);
            }
        printf("Case #%d: %d\n", i + 1, polygon(lengths, N));
    }
}
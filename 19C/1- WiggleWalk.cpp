#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cstring>
#include <bits/stdc++.h>
#include <cctype>

using namespace std;

struct UF
{
    int F[200010];
    void init()
    {
        memset(F, -1, sizeof(F));
    }
    int find(int x)
    {
        if (F[x] == -1)
            return x;
        else
            return find(F[x]);
    }
    int join(int x, int y)
    {
        int t1 = find(x);
        int t2 = find(y);
        if (t1 != t2)
            F[t2] = t1;
    }
};
UF west, east, north, south;

class Solution
{
private:
    map<pair<int, int>, int> p2id;
    map<int, pair<int, int>> id2p;
    int total = 0;

public:
    void init()
    {
        p2id.clear();
        id2p.clear();
        west.init();
        east.init();
        north.init();
        south.init();
    }

    int getId(int x, int y)
    {
        pair<int, int> p = make_pair(x, y);
        if (!p2id.count(p))
        {
            p2id[p] = total;
            id2p[total] = p;
            total++;
        }
        return p2id[p];
    }

    void add(int x, int y)
    {
        int now = getId(x, y);

        int w = getId(x, y - 1);
        int e = getId(x, y + 1);
        int n = getId(x - 1, y);
        int s = getId(x + 1, y);

        west.join(w, now);
        east.join(e, now);
        north.join(n, now);
        south.join(s, now);
    }

    pair<int, int> getNext(int x, int y, char c)
    {
        int now = getId(x, y);
        int nextid;
        switch (c)
        {
        case 'W':
            nextid = west.find(now);
            break;
        case 'E':
            nextid = east.find(now);
            break;
        case 'N':
            nextid = north.find(now);
            break;
        case 'S':
            nextid = south.find(now);
            break;
        }
        return id2p[nextid];
    }

    pair<int, int> wiggleWalk(int N, int sr, int sc, string s)
    {
        add(sr, sc);
        pair<int, int> now = make_pair(sr, sc);
        for (int i = 0; i < N; i++)
        {
            now = getNext(now.first, now.second, s[i]);
            add(now.first, now.second);
        }
        return now;
    }
};

int main()
{
    int T;
    cin >> T;
    Solution solution;
    for (int k = 1; k <= T; k++)
    {
        int N, R, C, sr, sc;
        cin >> N >> R >> C >> sr >> sc;
        string instruction;
        cin >> instruction;
        solution.init();
        pair<int, int> last = solution.wiggleWalk(N, sr, sc, instruction);
        printf("Case #%d: %d %d\n", k, last.first, last.second);
    }
}
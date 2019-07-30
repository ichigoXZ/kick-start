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

const int N = 3; //1e6 + 6;
int clk[N], anti[N];
int cntclk[N], cntanti[N];

void solve(vector<pair<int, char>> &guests, int n, int g, int m) {
    fill(clk, clk + n, -1);
    fill(anti, anti + n, -1);
    for (auto guest : guests) {
        if (guest.second == 'C') {
            int now = (guest.first + m) % n;
            clk[now] = m;
        }
        else
        {
            int now = (guest.first - m) % n;
            if (now < 0)    // m maybe >> n
                now += n;
            anti[now] = m;
        }
    }

    int cur = -1;
    for (int i = 2 * n - 1; i >= 0; i--) {
        cur = max(cur - 1, clk[i % n]);
        clk[i % n] = cur;
    }
    cur = -1;
    for (int i = 0; i < 2 * n; i++) {
        cur = max(cur - 1, anti[i % n]);
        anti[i % n] = cur;
    }

    fill(cntclk, cntclk + n, 0);
    fill(cntanti, cntanti + n, 0);
    for (int i = 0; i < n; i++) {
        int last = max(clk[i], anti[i]);
        if (last < 0)
            continue;
        if (last == clk[i]) {
            int pos = (i - last) % n;
            if (pos < 0)
                pos += n;
            cntclk[pos]++;
        }
        if (last == anti[i]) {
            int pos = (i + last) % n;
            cntanti[pos]++;
        }
    }

    for (auto guest : guests) {
        int ans;
        if (guest.second == 'C')
            ans = cntclk[guest.first];
        else 
            ans = cntanti[guest.first];
        cout << " " << ans;
    }
}

int main()
{
    int T;
    cin >> T;
    for (int k = 1; k <= T; k++)
    {
        int n, g, m;
        cin >> n >> g >> m;
        vector<pair<int, char>> guests(g);
        for (int i = 0; i < g; i++) {
            cin >> guests[i].first >> guests[i].second;
            guests[i].first -= 1; // 1 <= Hi <= N
        }
        printf("Case #%d:", k);
        solve(guests, n, g, m);
        cout << endl;
    }
}

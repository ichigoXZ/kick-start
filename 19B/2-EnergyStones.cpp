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

struct energyStone {
    int S;
    int E;
    int L;
    void input() {
        scanf("%d%d%d", &S, &E, &L);
    }
};

bool cmp(energyStone &a, energyStone &b) {
    return a.S * b.L < b.S * a.L;
}

int main()
{
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++)
    {
        int N;
        int S, E, L;
        cin >> N;
        vector<energyStone> stones(N);
        for (int k = 0; k < N; k++)
            stones[k].input();
        sort(stones.begin(), stones.end(), cmp);
        // dp[j] : 使用了j秒的最大结果
        int dp[10001];
        memset(dp, 0, sizeof(dp));
        for (int k = 0; k < N; k++) 
            for (int j = 10000 - stones[k].S; j >= 0; j--) {
                int cur = stones[k].E - stones[k].L * j;
                if (cur <= 0)
                    continue;
                dp[j + stones[k].S] = max(dp[j + stones[k].S], dp[j] + cur);
            }
        int ans = 0;
        for (int j = 0; j <= 10000; j++)
            ans = max(ans, dp[j]);
        printf("Case #%d: %d\n", i, ans);
    }
}
#include <iostream>
#include <vector>
#include <bits/stdc++.h>

#define ALL(x) (x).begin(), (x).end()

using namespace std;

int main()
{
    int T;
    cin >> T;
    for (int k = 1; k <= T; k++)
    {
        int N, P;
        cin >> N >> P;
        vector<int> skill(N);
        for (int i = 0; i < N; i++)
            cin >> skill[i];
        
        sort(ALL(skill));
        vector<int> dist(N, 0);
        for (int i = 0; i < N-1; i++) 
            dist[i] = skill[N-1] - skill[i];
        int ans = 0;
        for (int i = N - 1; i >= N - P; i--)
            ans += dist[i];
        int sw = ans;
        for (int i = N - P - 1; i >= 0; i--) {
            sw = sw + dist[i] - dist[i + P];
            ans = min(sw - P * dist[i + P - 1], ans);
        }
        printf("Case #%d: %d\n", k, ans);
    }
    return 0;
}

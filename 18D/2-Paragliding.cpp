#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <bits/stdc++.h>

using namespace std;

vector<int> generate(int g1, int g2, int A, int B, int C, int M ,int num) {
    vector<int> res;
    res.push_back(g1);
    res.push_back(g2);
    for (int i = 2; i < num; i++) 
        res.push_back(((long long)A * res[i-1] + (long long)B * res[i-2] + C) % M + 1);
    return res;
}

// NlongN + (NlogN?) + KlogK
int paragliding(vector<vector<int>>& PHXY, int N, int K)
{
    map<int, int> phshadow;
    int left, right;
    map<int, int> ph;
    for (int i = 0; i < N; i++)
        ph[PHXY[0][i]] = PHXY[1][i];
    for (auto iter = ph.begin(); iter != ph.end(); iter++) {
        left = iter->first - iter->second;
        right = iter->first + iter->second;
        if (!phshadow.empty() && (phshadow.rbegin()->second >= right))
            continue;
        auto it = phshadow.lower_bound(left); 
        phshadow.erase(it, phshadow.end());
        phshadow[left] = right;
    }
    int num = 0;
    for (int i = 0; i < K; i++) {
        left = PHXY[2][i] - PHXY[3][i];
        right = PHXY[2][i] + PHXY[3][i];
        auto itl = phshadow.upper_bound(left);
        if (itl == phshadow.begin())
            continue;
        itl--;
        if (itl->second >= right)
            num++;
    }
    return num;
}

// N + K + NlongN + KlogK + N + K
typedef pair<int,int> coordinate;
int paraglidingTrans(vector<vector<int>>& PHXY, int N, int K) {
    vector<coordinate> ph;
    vector<coordinate> xy;
    int num = 0;
    for (int i = 0; i < N; i++)
        ph.push_back(make_pair(PHXY[0][i] + PHXY[1][i], PHXY[1][i] - PHXY[0][i]));
    for (int i = 0; i < K; i++)
        xy.push_back(make_pair(PHXY[2][i] + PHXY[3][i], PHXY[3][i] - PHXY[2][i]));
    sort(ph.begin(), ph.end(), greater<coordinate>());
    sort(xy.begin(), xy.end(), greater<coordinate>());
    int id = 0, maxY = INT_MIN;
    for (int i = 0; i < K; i++) {
        while (id < N && ph[id].first >= xy[i].first) {
            maxY = max(ph[id].second, maxY);
            id++;
        }
        if (maxY >= xy[i].second)
            num++;
    }
    return num;
}

int paraglidingnk(vector<vector<int>>& PHXY, int N, int K) {
    int num = 0;
    for (int i = 0; i < K; i++)     // x, y
        for (int j = 0; j < N; j++) {   // p, h
            if (abs(PHXY[0][j] - PHXY[2][i]) <= (PHXY[1][j] - PHXY[3][i])) {
                num++;
                break;
            }
        }
    return num;
}

int main()
{
    int T;
    cin >> T;
    int N, K;
    int A[4], B[4], C[4], M[4];
    int phxy[4][2];
    for (int i = 1; i <= T; i++)
    {
        cin >> N >> K;
        vector<vector<int>> PHXY;
        for (int j = 0; j < 4; j++) {
            cin >> phxy[j][0] >> phxy[j][1] >> A[j] >> B[j] >> C[j] >> M[j];
            vector<int> tmp = generate(phxy[j][0], phxy[j][1], A[j], B[j], C[j], M[j], j > 1 ? K : N);
            PHXY.push_back(tmp);
        }
        // printf("Case #%d: %d\n", i, paraglidingnk(PHXY, N, K));
        printf("Case #%d: %d\n", i, paragliding(PHXY, N, K));
        printf("Case #%d: %d\n", i, paraglidingTrans(PHXY, N, K));
    }
}
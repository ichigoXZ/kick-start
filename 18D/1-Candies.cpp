#include <iostream>
#include <vector>
#include <queue>
#include <bits/stdc++.h>

using namespace std;

vector<long long> sweetness(int N, long long x1, long long x2, long long A, long long B, long long C, long long M, long long L)
{
    vector<long long> sweet;
    vector<long long> x;
    x.push_back(0);
    x.push_back(x1);
    x.push_back(x2);
    sweet.push_back(0);
    sweet.push_back(x1 + L);
    sweet.push_back(x2 + L);
    for (int i = 3; i <= N; i++) {
        x.push_back(((long long)A * x[i - 1] + (long long)B * x[i - 2] + C) % M);
        sweet.push_back(x.back() + L);
    }
    return sweet;
}


void choose(vector<long long> candies, int N, int O, long long D)
{
    long long mx = LLONG_MIN;
    int numodd = 0;
    vector<long long> sum(N+1);
    sum[0] = 0;
    for (int i = 1; i <= N; i++)
        sum[i] = sum[i-1] + candies[i];
    multiset<long long> mt;
    int r = 1;
    for (int i = 1; i <= N; i++) {
        while (r <= N && numodd + (candies[r] & 1) <= O) {
            mt.insert(sum[r]);
            numodd += (candies[r] & 1);
            r++;
        }

        if (r <= i) {
            r = i + 1;
        }
        else {
            auto it = mt.upper_bound(D + sum[i-1]);
            if (it != mt.begin()) {
                it--;
                mx = max(mx, (*it) - sum[i-1]);
            }
            mt.erase(mt.find(sum[i]));
            numodd -= (candies[i] & 1);
        }
    }
    if (mx == LLONG_MIN)
        cout << "IMPOSSIBLE\n";
    else
        cout << mx << endl;
}

int main()
{
    int T;
    cin >> T;
    int N, O;
    long long D, x1, x2, A, B, C, M, L;
    for (int i = 1; i <= T; i++)
    {
        cin >> N >> O >> D;
        cin >> x1 >> x2 >> A >> B >> C >> M >> L;
        vector<long long> candies = sweetness(N, x1, x2, A, B, C, M, L);
        printf("Case #%d: ", i);
        choose(candies, N, O, D);
    }
}
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

void solve(int N, int Q, vector<int> &A, vector<int> &P, vector<int> &V)
{
    set<int> mi;
    for (int i = 0; i < N; i++)
        if (__builtin_popcount(A[i]) & 1) 
            mi.insert(i);
    for (int i = 0; i < Q; i++) {
        if (__builtin_popcount(A[P[i]]) & 1) 
            mi.erase(P[i]);
        A[P[i]] = V[i];
        if (__builtin_popcount(A[P[i]]) & 1)
            mi.insert(P[i]);
        if ((mi.size() & 1) == 0)
            cout << " " << N;
        else
            cout << " " << max(*mi.rbegin(), N - *mi.begin() - 1);
    }
}

int main()
{
    int T;
    cin >> T;
    for (int k = 1; k <= T; k++)
    {
        int N, Q;
        cin >> N >> Q;
        vector<int> A(N);
        for (int i = 0; i < N; i++)
            cin >> A[i];
        vector<int> P(Q), V(Q);
        for (int i = 0; i < Q; i++)
            cin >> P[i] >> V[i];
        printf("Case #%d:", k);
        solve(N, Q, A, P, V);
        cout << endl;
    }
    return 0;
}
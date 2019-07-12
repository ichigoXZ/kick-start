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

vector<int> generate(int x1, int x2, int A, int B, int C, int M, int N)
{
    vector<int> X;
    X.push_back(x1);
    X.push_back(x1);
    for (int i = 2; i < N; i++)
    {
        int x = ((long long)A * X[i - 1] + (long long)B * X[i - 2] + C) % M;
        X.push_back(x);
    }
    return X;
}

int main()
{
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++)
    {
        printf("Case #%d: \n", i);
    }
}
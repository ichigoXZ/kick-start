#include <bits/stdc++.h>

#define mp make_pair
#define x first
#define y second
#define pb push_back
#define ALL(x) (x).begin(), (x).end()

using namespace std;

typedef long long LL;
typedef unsigned long long ULL;

const int N = (int)1e6 + 6, mod = (int)1e5, inf = 1e9;

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
    for (int k = 1; k <= T; k++)
    {
        printf("Case #%d: \n", k);
    }
}
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
#define MOD 1000000007

using namespace std;

/* 
 * g(k) = C(2N-k, k) × k! × 2^k × (2(N - K))! 
 *      = (2N - k)! × 2^k
 * C(n, m) = n! / (m! * (n-m)!)
 * Σ[(-1)^k × g(k) × C(M, k) ] 
 */

long long factorial[200001];
long long facInv[200001];
long long power[200001];
int Facmax = 0;
int Powmax = 0;

int ex_gcd(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    int ans = ex_gcd(b, a % b, y, x);
    y -= x * (a / b);
    return ans;
}

int mod_inverse(int a, int m)
{
    int x, y;
    ex_gcd(a, m, x, y);
    return (x % m + m) % m;
}

void getfactorial(int N)
{
    factorial[0] = 1;
    facInv[0] = 1;
    for (int i = Facmax + 1; i <= 2 * N; i++)
    {
        factorial[i] = factorial[i - 1] * i % MOD;
        facInv[i] = mod_inverse(factorial[i], MOD);
    }
    Facmax = max(Facmax, 2 * N);
}

void getpow(int M)
{
    power[0] = 1;
    for (int i = Powmax + 1; i <= M; i++)
    {
        power[i] = (power[i - 1] << 1) % MOD;
    }
    Powmax = max(Powmax, M);
}

long long Combination(int n, int m)
{
    return factorial[n] * facInv[n - m] % MOD * facInv[m] % MOD;
}

long long solve(int N, int M)
{
    getfactorial(N);
    getpow(M);
    long long ans = 0;
    int prefix = 1;
    for (int k = 0; k <= M; k++)
    {
        ans = (ans + prefix * factorial[2 * N - k] * power[k] % MOD * Combination(M, k) % MOD) % MOD;
        prefix = -prefix;
    }
    return (ans + MOD) % MOD;
}

int main()
{
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++)
    {
        int N, M;
        cin >> N >> M;
        printf("Case #%d: %lld\n", i, solve(N, M));
    }
}
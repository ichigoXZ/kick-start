#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cstring>
#include <cctype>
#include <queue>
#include <stack>
#include <bitset>

#define mp make_pair
#define x first
#define y second
#define pb push_back
#define ALL(x) (x).begin(), (x).end()

using namespace std;

typedef long long LL;
typedef unsigned long long ULL;

const int N = (int)1e6 + 6, mod = (int)0;

int trinkets[10000];
int frequency[10000];



int count(int n) {
    unordered_map<int, int> counters;
    for (int i = 0; i < n; i++) {
        counters[trinkets[i]]++;
        frequency[i] = counters[trinkets[i]];
    }
}

int solve(int n, int s) {
    count(n);
    int dp[n];
    int ans = 0;
    for (int i = 0; i < n; i++) {
        unordered_map<int, int> hmap;
        int x = 0;
        for (int j = i; j < n; j++) {
            hmap[trinkets[j]]++; 
            if (hmap[trinkets[j]] > s) {
                if (hmap[trinkets[j]] == s + 1)
                    x -= s;
            }
            else 
                x++;
            ans = max(x, ans);
        }
    }
    return ans;
}

int main()
{
    int T;
    cin >> T;
    for (int k = 1; k <= T; k++)
    {   
        int n, s;
        cin >> n >> s;
        for (int i = 0; i < n; i++)
            cin >> trinkets[i];
        int ans = solve(n, s);
        printf("Case #%d: %d\n", k, ans);
    }
}
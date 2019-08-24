#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

#define ALL(x) (x).begin(), (x).end()

const int N = 10001, inf = 1e9;

int A[N];
int P[N];

int catchSome(int n, int K) {
    unordered_map<int, vector<int>> colors;
    for (int i = 0; i < n; i++)
        colors[A[i]].push_back(P[i]);
    int c = colors.size();
    vector<int> keys;
    for (auto it = colors.begin(); it != colors.end(); it++) {
        sort(ALL(it->second));
        keys.push_back(it->first);
    }
    vector<int> dp0(K + 1, inf);
    vector<int> dp1(K + 1, inf);
    dp0[0] = dp1[0] = 0;
    for (int i = 0; i < c; i++) {
        int nums = colors[keys[i]].size();
        for (int k = K; k >= 1; k--) {
            for (int j = 1; j <= nums && j <= k; j++) {
                int d = colors[keys[i]][j - 1];
                dp0[k] = min(dp0[k], dp0[k - j] + 2 * d);
                dp1[k] = min(dp1[k], dp1[k - j] + 2 * d);
                dp1[k] = min(dp1[k], dp0[k - j] + d);
            }
        }
    }
    return dp1[K];
}

int main()
{
    int T;
    cin >> T;
    for (int k = 1; k <= T; k++)
    {
        int n, K;
        cin >> n >> K;
        for (int i = 0; i < n; i++)
            cin >> P[i];
        for (int i = 0; i < n; i++)
            cin >> A[i];
        printf("Case #%d: %d\n", k, catchSome(n, K));
    }
    return 0;
}
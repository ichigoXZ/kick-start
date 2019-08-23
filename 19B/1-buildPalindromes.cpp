#include <iostream>
#include <vector>

using namespace std;

const int N = 100;
// const int N = (int)1e5 + 5;

int query[N][2];

int buildPalindromes(int n, int q, string s) {
    int ans = 0;
    vector<vector<int>> dictt(n + 1, vector<int>(26, 0));
    dictt[1][s[0] - 'A'] = 1;
    for (int i = 2; i <= n; i++) {
        dictt[i] = dictt[i - 1];
        dictt[i][s[i -  1] - 'A']++;
    }
    for (int i = 0; i < q; i++) {
        int l = query[i][0] - 1, r = query[i][1];
        int odd = 0;
        for (int j = 0; j < 26; j++) {
            if ((dictt[r][j] - dictt[l][j]) & 1)
                odd++;
            if (odd > 1)
                break;
        }
        ans += (odd <= 1);
    }
    return ans;
}

int main()
{
    int T;
    cin >> T;
    for (int k = 1; k <= T; k++)
    {
        int n, q;
        cin >> n >> q;
        string str;
        cin >> str;
        for (int i = 0; i < q; i++)
            cin >> query[i][0] >> query[i][1];
        printf("Case #%d: %d\n", k, buildPalindromes(n, q, str));
    }
    return 0;
}
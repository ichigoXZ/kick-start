#include <bits/stdc++.h>

using namespace std;

bool count(int n) {
    // int alice = 1 + (n & 1), bob = !(n & 1);
    int alice = 0, bob = 0;
    double mid = pow(n, 0.5);
    int num = n;
    for (int i = 1; i <= mid; i++) {
        if (num % i == 0) {
            // cout << i << endl;
            if (i & 1)
                alice++;
            else 
                bob++;
            
            n = num / i;
            if (n == i)
                break;
            if (n & 1)
                alice++;
            else
                bob++;
            // cout << n << endl;
        }
    }
    // cout << endl;
    if (abs(alice - bob) <= 2)
        return true;
    return false;
}

int solve(int l, int r) {
    int ans = 0;
    for (int i = l; i <= r; i++)
        ans += count(i);
    return ans;
}

int main()
{
    int T;
    cin >> T;
    for (int k = 1; k <= T; k++)
    {
        int l, r;
        cin >> l >> r;
        printf("Case #%d: %d\n", k, solve(l, r));
    }
    return 0;
}
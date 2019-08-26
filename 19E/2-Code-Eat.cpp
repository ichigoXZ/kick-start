#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int N = (int)1e5 + 5;

LL days[N][2];
LL slots[N][2];


void solve(int d, int s) {

}

int main()
{
    int T;
    cin >> T;
    for (int k = 1; k <= T; k++)
    {
        int d, s;
        cin >> d >> s;
        for (int i = 0; i < s; i++) {
            cin >> slots[i][0];
            cin >> slots[i][1];
        }
        for (int i = 0; i < d; i++) {
            cin >> days[i][0];
            cin >> days[i][1];
        }
        printf("Case #%d: ", k);
        solve(d, s);
        cout << endl;
    }
}
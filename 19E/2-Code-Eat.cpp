#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int N = (int)1e5 + 5;

LL days[N][2];
LL slots[N][2];

void solve (int d, int s) {
    if (s == 1) {
        int c = slots[0][0];
        int e = slots[0][1];
        for (int i = 0; i < d; i++) {
            double f = (double)days[i][0] / c;
            if ((double)days[i][1] == e * (1 - f))
                cout << "Y";
            else 
                cout << "N";
        }
    }
    if (s == 2) {
        double c1 = slots[0][0], c2 = slots[1][0];
        double e1 = slots[1][0], e2 = slots[1][1];
        for (int i = 0; i < d; i++) {
            double C = days[i][0], E = days[i][1];
            double f1 = (C * e2 + E * c2 - (c2 * e2 - c2 * e1)) / (e2 * c1 - c2 * e1);
            double f2 = (C * e1 + E * c1 - (c1 * e1 - c1 * e2)) / (e1 * c2 - c1 * e2);
            if (c1 * f1 )
        }
    }
}

// void solve(int d, int s) {
//     LL esum = 0, csum = 0;
//     for (int i = 0; i < s; i++) {
//         esum += slots[i][1];
//         csum += slots[i][0];
//     }
//     for (int i = 0; i < d; i++) {
//         LL t1 = days[i][1] + days[i][0] - esum;
//         LL t2 = days[i][1] - days[i][0] - esum;
//         LL sfe = - (t1 + t2) / 2;
//         LL sfc = (t1 - t2) / 2;
//         if (sfe < 0 || sfc < 0 || sfc > csum || sfe > esum)
//             cout << "N";
//         else 
//             cout << "Y";
//     }
// }

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
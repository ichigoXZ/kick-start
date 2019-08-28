#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

void solve(vector<vector<LL>>& slots, vector<vector<LL>> & days, int d, int s) {
    auto comp = [](const vector<LL>& a, const vector<LL> & b) {
        return a[0] * b[1] > b[0] * a[1];
    };
    sort(slots.begin(), slots.end(), comp);
    vector<LL> code(s+1), eat(s+1);
    code[0] = 0;
    for (int i = 1; i <= s; i++)
        code[i] = code[i - 1] + slots[i - 1][0];
    eat[s] = 0;
    for (int i = s - 1; i >= 0; i--)
        eat[i] = eat[i + 1] + slots[i][1];
    for (int i = 0; i < d; i++) {
        int pos = lower_bound(code.begin(), code.end(), days[i][0]) - code.begin();
        if (pos == s + 1)
            cout << "N";
        else if (pos == 0) {
            if (eat[pos] >= days[i][1])
                cout << "Y";
            else 
                cout << "N";
        }
        else {
            if (eat[pos] >= days[i][1]) 
                cout << "Y";
            else {
                double f = (double)(days[i][0]- code[pos - 1]) / slots[pos - 1][0];
                if (eat[pos] + (1 - f) * slots[pos - 1][1] >= days[i][1])
                    cout << "Y";
                else 
                    cout << "N";
            }
        }
    }
}

int main()
{
    int T;
    cin >> T;
    for (int k = 1; k <= T; k++)
    {
        int d, s;
        cin >> d >> s;
        vector<vector<LL>> slots(s, vector<LL>(2));
        vector<vector<LL>> days(d, vector<LL>(2));
        for (int i = 0; i < s; i++) {
            cin >> slots[i][0];
            cin >> slots[i][1];
        }
        for (int i = 0; i < d; i++) {
            cin >> days[i][0];
            cin >> days[i][1];
        }
        printf("Case #%d: ", k);
        solve(slots, days, d, s);
        cout << endl;
    }
}
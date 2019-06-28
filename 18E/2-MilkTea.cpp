#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;
int main() {
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++)
    {
        int N, M, P;
        string str;
        cin >> N >> M >> P;
        vector<string> favours;
        set<string> forbid;
        for (int j = 0; j < N; j++) {
            cin >> str;
            favours.push_back(str);
        }
        for (int j = 0; j < M; j++) {
            cin >> str;
            forbid.insert(str);
        }
        vector<int> complaints(P, 0);
        for (int k = 0; k < N; k++)
            for (int j = 0; j < P; j++) {
                if (favours[k][j] == '1')
                    complaints[j]++;
            }
        vector<pair<int, string>> best;
        best.push_back(make_pair(0, ""));
        for (int k = 0; k < P; k++) {
            vector<pair<int, string>> cur;
            for (auto pre : best) {
                cur.push_back(make_pair(pre.first + complaints[k], pre.second + '0'));
                cur.push_back(make_pair(pre.first + N - complaints[k], pre.second + '1'));
            }
            sort(cur.begin(), cur.end());
            best.assign(cur.begin(), cur.size() > M+1 ? cur.begin() + M + 1 : cur.end());
        }
        int k = 0;
        for (; k < M+1; k++) {
            if (forbid.find(best[k].second) == forbid.end())
                break;
        }
        printf("Case #%d: %d\n", i, best[k].first);
    }
    return 0;
}
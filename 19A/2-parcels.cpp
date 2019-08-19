// 15pts, 20pts

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

#define mp make_pair
#define ALL(x) (x).begin(), (x).end()

using namespace std;

const int inf = 1e9;
int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

void bfs(vector<string>& graph, int R, int C, vector<vector<int>>& d) {
    queue<pair<int, int>> reach;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (graph[i][j] == '1') {
                reach.push(mp(i, j));
                d[i][j] = 0;               
            }
        }
    }
    while (!reach.empty()) {
        int x = reach.front().first, y = reach.front().second;
        reach.pop();
        for (int i = 0; i < 4; i++) {
            int xx = x + directions[i][0], yy = y + directions[i][1];
            if (min(xx, yy) < 0 || xx >= R || yy >= C || d[xx][yy] != -1)
                continue;
            reach.push(mp(xx, yy));
            d[xx][yy] = d[x][y] + 1;
        }
    }
}

bool can(int x, vector<vector<int>>& d, int R, int C) {
    int plus_up = inf, plus_down = -inf, minus_up = inf, minus_down = -inf;
    bool ok = true;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (d[i][j] <= x)
                continue;
            plus_up = min(plus_up, i + j + x);
            plus_down = max(plus_down, i + j - x);
            minus_up = min(minus_up, i - j + x);
            minus_down = max(minus_down, i - j - x);
            ok = false;
        }
    }
    if (ok)
        return true;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            int plus = i + j, minus = i - j;
            if (plus >= plus_down && plus <= plus_up && minus >= minus_down && minus <= minus_up)
                return true;
        }
    }
    return false;
}

int solve(vector<string>& graph, int R, int C) {
    vector<vector<int>> d(R, vector<int>(C, -1));
    bfs(graph, R, C, d);

    int lo = 0, hi = R + C;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (can(mid, d, R, C))
            hi = mid;
        else
            lo = mid + 1;
    }
    return hi;
}

int main() {
    int T;
    cin >> T;
    for (int k = 1; k <= T; k++)
    {
        int R, C;
        cin >> R >> C;
        vector<string> locations(R);
        for (int i = 0; i < R; i++)
            cin >> locations[i];
        printf("Case #%d: %d\n", k, solve(locations, R, C));
    }
}
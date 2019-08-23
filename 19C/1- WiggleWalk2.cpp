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

#define mp make_pair
#define x first
#define y second
#define pb push_back
#define ALL(x) (x).begin(), (x).end()

using namespace std;

typedef long long LL;

const int N = (int)1e6 + 6, mod = (int)0;

struct node {
    int left;
    int right;
    int up;
    int down;
};

pair<int, int> walk(string s, int R, int C, int sr, int sc, int N) {
    struct node nxt[R+2][C+2];
    vector<vector<bool>> visited(R+2, vector<bool>(C+2, false));
    nxt[sr][sc].left = sc - 1;
    nxt[sr][sc].right = sc + 1;
    nxt[sr][sc].up = sr - 1;
    nxt[sr][sc].down = sr + 1;
    int r = sr, c = sc;
    visited[sr][sc] = true;
    for (int i = 0; i < N; i++) {
        if (s[i] == 'W')  // left
            c = nxt[sr][sc].left;
        else if (s[i] == 'E')
            c = nxt[sr][sc].right;
        else if (s[i] == 'N')
            r = nxt[sr][sc].up;
        else 
            r = nxt[sr][sc].down;
        visited[r][c] = true;
        
        nxt[r][c].down = visited[r+1][c] ? nxt[r+1][c].down : r + 1;
        nxt[r][c].up = r-1 >= 0 && visited[r-1][c] ? nxt[r-1][c].up : r - 1;
        nxt[r][c].left = c-1 >= 0 && visited[r][c-1] ? nxt[r][c-1].left : c - 1;
        nxt[r][c].right = visited[r][c+1] ? nxt[r][c+1].right : c + 1;
        
        nxt[r+1][c].up = nxt[r][c].up;
        nxt[r-1][c].down = nxt[r][c].down;
        nxt[r][c+1].left = nxt[r][c].left;
        nxt[r][c-1].right = nxt[r][c].right;
        sr = r, sc = c;
    }
    return mp(r, c);
}


int main()
{
    int T;
    cin >> T;
    for (int k = 1; k <= T; k++)
    {
        int N, R, C, sr, sc;
        cin >> N >> R >> C >> sr >> sc;
        string instruction;
        cin >> instruction;
        pair<int, int> ans = walk(instruction, R, C, sr, sc, N);
        printf("Case #%d: %d %d\n", k, ans.first, ans.second);
    }
    return 0;
}
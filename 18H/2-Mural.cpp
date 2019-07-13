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

using namespace std;

int mural(string s, int N) {
    int num = (N + 1) >> 1;
    int end = num;
    int total = 0;
    for (int i = 0; i < num; i++) 
        total += s[i] - '0';
    int ans = total;
    for (; end < N; end++) {
        int start = end - num + 1;
        total = total + s[end] - '0' - (s[start -1] - '0');
        // if (end + (N - num) < N || start >= (N - num))
            ans = max(total, ans);
    }
    return ans;
}

int main()
{
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++)
    {
        int N;
        cin >> N;
        string s;
        cin >> s;
        printf("Case #%d: %d\n", i, mural(s, N));
    }
}
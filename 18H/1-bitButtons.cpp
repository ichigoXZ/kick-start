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

struct TrieNode {
    int layer;
    bool fin =  false;
    struct TrieNode *R = NULL, *B = NULL;
    TrieNode(int l) {layer = l;}
};

void add(TrieNode* root, string s) {
    int n = s.length();
    TrieNode *p = root;
    for (int i = 1; i <= n; i++) {
        if (p->fin)
            return;
        switch (s[i-1])
        {
        case 'R':
            if (!p->R) {
                TrieNode* node = new TrieNode(i);
                p->R = node;
            }
            p = p->R;
            break;
        case 'B':
            if (!p->B) {
                TrieNode *node = new TrieNode(i);
                p->B = node;
            }
            p = p->B;
            break;
        default:
            break;
        }
    }
    p->fin = true;
}

void dfs(TrieNode *node, long long &nums, int N) {
    if (nums >= (1LL << N))
        return;
    if (node->fin) {
        nums += 1LL << (N - node->layer);
        return;
    }
    if (node->R)
        dfs(node->R, nums, N);
    if (node->B)
        dfs(node->B, nums, N);
}

int main()
{
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++)
    {
        int N, P;
        cin >> N >> P;
        TrieNode* root = new TrieNode(0);
        for (int k = 0; k < P; k++) {
            string s;
            cin >> s;
            add(root, s);
        }
        long long nums = 0;
        dfs(root, nums, N);
        long long ans = (1LL << N) - nums;
        printf("Case #%d: %lld\n", i, ans);
    }
}
#include <bits/stdc++.h>

using namespace std;
typedef long long LL;

vector<int> generate(int x1, int x2, int A, int B, int C, int M, int N) {
    vector<int> X;
    X.push_back(x1);
    X.push_back(x2);
    for (int i = 2; i < N; i++) {
        int x = ((long long)A * X[i - 1] + (long long)B * X[i - 2] + C) % M;
        X.push_back(x);
    }
    return X;
}

// 主要利用扫描线是做一个离散化
long long combiningClasses(vector<int>& L, vector<int>& R, vector<int>& K, int N, int Q) {
    map<int, LL> endpoints;
    for (int l : L)
        endpoints[l]++;
    for (int r : R)
        endpoints[r+1]--;   // 右端点要加一是因为右端点值是有人的。
    
    int n = endpoints.size();
    vector<int> nums(n + 1, 0), counters(n + 1, 0);
    int i = 1;
    // nums是端点的值， counters是这一段里有多少个重叠的interval 
    for (auto it = endpoints.begin(); it != endpoints.end(); it++, i++) {
        nums[i] = it->first;
        counters[i] = it->second + counters[i - 1];
    }
    // 以上都是普通的扫描线的题目的套路，下面的total是一个后缀和数组，因为我们要计算出现的点的次数。
    vector<LL> total(n + 1, 0);
    total[n] = counters[n];
    for (int i = n - 1; i > 0; i--) 
        total[i] = total[i + 1] + (LL)counters[i] * (nums[i + 1] - nums[i]);
    
    LL ans = 0;
    // 用二分搜索找到所在的区间，第K[i]个数在nums[r]到nums[r+1]之间
    for (int i = 0; i < Q; i++) {
        if (K[i] > total[1])
            continue;
        int l = 1, r = n;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (total[mid] >= K[i]) {
                l = mid + 1;
            }
            else 
                r = mid - 1;
        }
        int tmp = nums[r] + (total[r] - K[i]) / counters[r];
        ans += (LL)tmp * (i + 1);
    }
    return ans;
}

int main()
{
    int T;
    cin >> T;
    int N, Q;
    for (int i = 1; i <= T; i++)
    {
        cin >> N >> Q;
        int x1, x2, A, B, C, M;
        cin >> x1 >> x2 >> A >> B >> C >> M;
        vector<int> X = generate(x1, x2, A, B, C, M, N);
        cin >> x1 >> x2 >> A >> B >> C >> M;
        vector<int> Y = generate(x1, x2, A, B, C, M, N);
        cin >> x1 >> x2 >> A >> B >> C >> M;
        vector<int> Z = generate(x1, x2, A, B, C, M, Q);
        vector<int> L, R, K;
        for (int j = 0; j < N; j++) {
            int minimum = min(X[j], Y[j]) + 1;
            int maximum = max(X[j], Y[j]) + 1;
            L.push_back(minimum);
            R.push_back(maximum);
        }
        for (int j = 0; j < Q; j++)
            K.push_back(Z[j]+1);
        printf("Case #%d: %lld\n", i, combiningClasses(L, R, K, N, Q));
    }
}

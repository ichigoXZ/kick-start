#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cstring>

using namespace std;

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

long long combiningClasses(vector<int>& L, vector<int>& R, vector<int>& K, int N, int Q) {
    vector<int> nums;
    long long ans = 0;
    for (int i = 0; i < N; i++) {
        nums.push_back(L[i]);
        nums.push_back(R[i]);
    }
    sort(nums.begin(), nums.end());
    int total = unique(nums.begin(), nums.end()) - nums.begin();
    for (int i = 0; i < N; i++) {
        L[i] = lower_bound(nums.begin(), nums.begin() + total, L[i]) - nums.begin();
        R[i] = lower_bound(nums.begin(), nums.begin() + total, R[i]) - nums.begin();
    }

    vector<int> f(total, 0);
    // frequency
    for (int i = 0; i < N; i++) {
        f[L[i]]++;
        f[R[i]]--;
    }
    for (int i = 1; i < total; i++)
        f[i] += f[i-1];
    
    vector<long long> g(total, 0);
    g[total-1] = f[total -1];
    for (int i = total - 2; i >= 0; i--) {
        g[i] = g[i+1] + (long long)f[i] * (nums[i+1] - nums[i]);
    }

    for (int i = 0; i < Q; i++) {
        if (K[i] > g[0])
            continue;
        int ret = 0, mid;
        int l = 0, r = total - 1;
        while (l <= r) {
            mid = (l+r) / 2;
            if (g[mid] >= K[i]) {
                ret = mid;
                l = mid + 1;
            }
            else 
                r = mid -  1;
        }
        int tmp = nums[ret] + (g[ret] - K[i]) / f[ret];
        ans += (long long)tmp * (i + 1);
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
            R.push_back(maximum+1);
        }
        for (int j = 0; j < Q; j++)
            K.push_back(Z[j]+1);
        printf("Case #%d: %lld\n", i, combiningClasses(L, R, K, N, Q));
    }
}

// TLE
long long combiningClasses1(vector<int> &L, vector<int> &R, vector<int> &K, int N, int Q)
{
    int minimum = *(min_element(L.begin(), L.end()));
    int maximum = *(max_element(R.begin(), R.end()));
    vector<int> KS = K;
    sort(KS.begin(), KS.end());
    map<int, int> kans;
    int index = 1;
    for (int i = 0; i < Q; i++)
    {
        while (index != KS[i])
        {
            int maxpos = max_element(R.begin(), R.end()) - R.begin();
            if (R[maxpos] == -1)
                break;
            if (R[maxpos] > L[maxpos])
                R[maxpos]--;
            else
                R[maxpos] = -1;
            index++;
        }
        int maxpos = max_element(R.begin(), R.end()) - R.begin();
        if (R[maxpos] == -1)
            break;
        kans[KS[i]] = R[maxpos];
    }
    long long ans = 0;
    for (int i = 0; i < Q; i++)
        ans += (i + 1) * (kans.find(K[i]) == kans.end() ? 0 : kans[K[i]]);
    return ans;
}

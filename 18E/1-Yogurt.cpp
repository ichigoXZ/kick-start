#include <iostream>
#include <vector>
#include <set>

using namespace std;

int solve1() {
    int N, K;
    cin >> N >> K;
    multiset<int> A;
    int tmp;
    for (int j = 0; j < N; j++)
    {
        cin >> tmp;
        A.insert(tmp);
    }
    int days = 0;
    int ans = 0;
    while (!A.empty())
    {
        if (A.size() <= K)
        {
            ans += A.size();
            break;
        }
        ans += K;
        for (int i = 0; i < K; i++)
            A.erase(A.begin());
        auto it = A.upper_bound(++days);
        for (auto iter = A.begin(); iter != it; iter++)
            A.erase(iter);
    }
    return ans;
}

int solve2() {
    int N, K;
    cin >> N >> K;
    vector<int> A;
    int tmp;
    for (int j = 0; j < N; j++)
    {
        cin >> tmp;
        A.push_back(tmp);
    }
    vector<int> days(N+1, 0);
    for (int a : A) {
        days[min(a, N)]++;
    }
    int ans = 0;
    for (int i = N; i > 0; i--) {
        ans += min(K, days[i]);
        days[i-1] += max(0, days[i] - K);
    }
    return ans;
}

int main()
{
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++)
    {
        int ans;
        // ans = solve1();
        ans = solve2();
        printf("Case #%d: %d\n", i, ans);
    }
    return 0;
}
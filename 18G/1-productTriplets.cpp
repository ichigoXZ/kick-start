// don't know why large dataset fails...

#include <iostream>
#include <vector>
#include <map>

using namespace std;

long long product(map<long long, long long> A, int N)
{
    long long ans = 0;
    for (auto it = A.begin(); it != A.end(); it++)
    {
        long long num = it->second;
        if (it->first == 0)
            ans += num * (num - 1) / 2 * (N - num) + num * (num - 1) * (num - 2) / 6;
        else if (it->first == 1)
        {
            auto iter = it;
            if (num >= 3)
                ans += num * (num - 1) * (num - 2) / 6;
            iter++;
            for (; iter != A.end(); iter++)
            {
                ans += iter->second * (iter->second - 1) / 2;
            }
        }
        else
        {
            long long mul;
            auto iter = it;
            if (num >= 2)
            {
                mul = iter->first * iter->first;
                if (A.find(mul) != A.end())
                    ans += num * (num - 1) / 2 * A[mul];
            }
            iter++;
            for (; iter != A.end(); iter++)
            {
                mul = it->first * iter->first;
                if (A.find(mul) != A.end())
                    ans += num * iter->second * A[mul];
            }
        }
    }
    return ans;
}

int main()
{
    int T;
    cin >> T;
    int N, A;
    for (int i = 1; i <= T; i++)
    {
        cin >> N;
        map<long long, long long> sequence;
        for (int j = 0; j < N; j++)
        {
            cin >> A;
            sequence[A]++;
        }
        printf("Case #%d: %lld\n", i, product(sequence, N));
    }
}
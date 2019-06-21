#include <iostream>

using namespace std;

long long count(string x)
{
    int n = x.length();
    long long res = 0;
    long long pows = 1;
    for (int i = n - 2; i >= 0; i--)
    {
        res += (x[i] - '0') * pows * 8;
        pows = pows * 9;
    }
    long long llx = stoll(x);
    res += llx % 10 + (llx % 10 < llx % 9);
    return res;
}

int noNine(string F, string L)
{
    return count(L) - count(F) + 1;
}

int main()
{
    int T;
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        string F, L;
        cin >> F >> L;
        printf("Case #%d: %lld\n", i + 1, noNine(F, L));
    }
}
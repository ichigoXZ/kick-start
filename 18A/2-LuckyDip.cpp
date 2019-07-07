/* 
 * https://codingcompetitions.withgoogle.com/kickstart/round/0000000000050edf/0000000000050e1d
 * 
 * E[0] = Σ Vi / N
 * E[k] = xk * E[k - 1] / N + Σi > xk Vi / N
 *
 * Complexity : O(N + N log N + K log N) = O((N + K) log N) 
 */

#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

double luckyDip(vector<int> &v, int n, int K)
{
    sort(v.begin(), v.end());
    vector<long long> sufix(n+1, 0);
    sufix[n] = 0;
    for (int i = n-1; i >= 0; i--) 
        sufix[i] = sufix[i+1] + v[i];
    double expect = double(sufix[0]) / n;
    if (K == 0)
        return expect;
    for (int k = 0; k < K; k++)
    {
        int xk = (lower_bound(v.begin(), v.end(), expect) - v.begin());
        expect = (sufix[xk] + expect * xk) / n;
    }
    return expect;
}

int main()
{
    int T;
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        int n, K;
        cin >> n >> K;
        vector<int> v;
        for (int j = 0; j < n; j++)
        {
            int val;
            cin >> val;
            v.push_back(val);
        }
        printf("Case #%d: %.6lf\n", i + 1, luckyDip(v, n, K));
    }
}
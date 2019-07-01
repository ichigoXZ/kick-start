// small dataset
#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

void combinationFomula(vector<string> &res, string s, int pos, int chosen, int m, int n, char subset)
{
    if (chosen == m)
    {
        if (subset == '2')
            res.push_back(s);
        else
            combinationFomula(res, s, 0, 0, m, n, '2');
        return;
    }
    while (s[pos] != '0' && pos < n)
        pos++;
    if (chosen > m || pos == n)
        return;
    s[pos] = '0';
    combinationFomula(res, s, pos + 1, chosen, m, n, subset);
    s[pos] = subset;
    combinationFomula(res, s, pos + 1, chosen + 1, m, n, subset);
}

vector<string> combinationRecursive(int n, int m)
{
    vector<string> combinations;
    string s(n, '0');
    combinationFomula(combinations, s, 0, 0, m, n, '1');
    return combinations;
}

int Combination(int x) {
    if (x == 3)
        return 1680;
    if (x == 4)
        return 34650;
    if (x == 5)
        return 756756;
}

int battle(vector<int> Bahu, vector<int> Bala) {
    int wins = 0; 
    for (int i = 0; i < 3; i++)
        wins += Bahu[i] > Bala[i];
    return wins > 1;
}

int main()
{
    int T, N, val;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        cin >> N;
        vector<int> Bahu;
        vector<int> Bala; // Bala at the advantage
        for (int j = 0; j < 3 * N; j++) {
            cin >> val;
            Bahu.push_back(val);
        }
        for (int j = 0; j < 3 * N; j++)
        {
            cin >> val;
            Bala.push_back(val);
        }
        double rate = 0;
        vector<string> coms = combinationRecursive(N * 3, N);
        for (auto com : coms) {
            // Bahu
            vector<int> BahuFields(3, 0);
            for (int k = 0; k < N*3; k++)
                BahuFields[com[k] - '0'] += Bahu[k];
            int wintimes = 0;
            for (auto balacom : coms) {
                vector<int> BalaFields(3, 0);
                for (int k = 0; k < N * 3; k++)
                    BalaFields[balacom[k] - '0'] += Bala[k];
                wintimes += battle(BahuFields, BalaFields);
            }
            rate = max(rate, double(wintimes) / Combination(N));
        }
        printf("Case #%d: %.9lf\n", i, rate);
    }
    return 0;
}
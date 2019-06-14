#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;
// aapxjdnrbtvldptfzbbdbbzxtndrvjblnzjfpvhdhhpxjdnrbt
string scramble(char s1, char s2, int N,
                int A, int B, int C, int D)
{
    string S(N,' ');
    vector<int> X(N, 0);
    X[0] = S[0] = s1;
    X[1] = S[1] = s2;
    for (int i = 2; i < N; i++)
    {
        X[i] = ((long long)A * X[i - 1] + (long long)B * X[i - 2] + C) % D;
        S[i] = char(97 + (X[i] % 26));
    }
    return S;
}

unsigned long long gethash(string word) {
    int seed = 17;
    unsigned long long hash = word.front()  * 3117 + word.back() * 31;
    vector<int> nums(26, 0);
    for (int i = 0; i < word.length(); i++)
        nums[word[i] - 'a']++;
    for (int i = 0; i < 26; i++)
        hash = hash * seed + nums[i];
    return hash;
}

unsigned long long gethash(char start, char end, vector<int> &nums)
{
    int seed = 17;
    unsigned long long hash = start * 3117 + end * 31;
    for (int i = 0; i < 26; i++)
        hash = hash * seed + nums[i];
    return hash;
}

int scrambledWords(vector<string> dict, int L, string S, int N) {
    vector<int> lens(L);
    for (int i = 0; i < L; i++)
        lens[i] = dict[i].length();
    sort(lens.begin(),lens.end());
    int lensnum = unique(lens.begin(), lens.end()) - lens.begin();

    unordered_map<long long, int> hashtable;
    for (auto word : dict) 
        hashtable[gethash(word)]++;

    int ans = 0;
    for (int i = 0; i < lensnum; i++) {
        if (lens[i] > N)
            break;
        vector<int> nums(26, 0);
        for (int j = 0; j < lens[i]; j++)
            nums[S[j] - 'a']++;
        unsigned long long hash = gethash(S[0], S[lens[i] - 1], nums);
        if (hashtable.find(hash) != hashtable.end())
        {
            ans += hashtable[hash];
            hashtable.erase(hash);
        }

        for (int j = lens[i]; j < N; j++) {
            nums[S[j] - 'a']++;
            nums[S[j - lens[i]] - 'a']--;

            unsigned long long hash = gethash(S[j - lens[i] + 1], S[j], nums);
            if (hashtable.find(hash) != hashtable.end()) {
                ans += hashtable[hash];
                hashtable.erase(hash);
            }
        }
    }

    return ans;
}

int main()
{
    int T;
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        int L;
        cin >> L;
        vector<string> dict;
        for (int j = 0; j < L; j++)
        {
            string w;
            cin >> w;
            dict.push_back(w);
        }
        char s1, s2;
        int N;
        int A, B, C, D;
        cin >> s1 >> s2 >> N >> A >> B >> C >> D;
        string S = scramble(s1, s2, N, A, B, C, D);
        printf("Case #%d: %d\n", i + 1, scrambledWords(dict, L, S, N));
    }
}
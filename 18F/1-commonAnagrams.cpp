#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

map<string, int> processA(string A) {
    int n = A.length();
    map<string, int> amap;
    for (int len = 1; len <= n; len++)
        for (int i = 0; i <= n - len; i++)
            amap[A.substr(i, len)]++;
    return amap;
}

unsigned long long gethash(string s)
{
    int seed = 17;
    unsigned long long hash = 31;
    vector<int> nums(26, 0);
    for (auto c : s)
        nums[c - 'A']++;
    for (int i = 0; i < 26; i++)
        hash = hash * seed + nums[i];
    return hash;
}

string hashstring(char c, vector<int>& times) {
    string encode;
    times[c - 'A']++;
    for (int i = 0; i < 26; i++)
        encode += times[i] + ',';
    return encode;
}

string hashstring(string s) {
    vector<int> times(26, 0);
    for (int i = 0; i < s.size(); i++)
        times[s[i] - 'A']++;
    string encode;
    for (int i = 0; i < 26; i++)
        encode += times[i] + ',';
    return encode;
}

int anagramsT(map<string, int>& A, string B) {
    int ans = 0;
    int lofb = B.length();
    set<string> Bset;
    for (int i = 0; i < B.length(); i++) {
        vector<int> times(26, 0);
        for (int j = i; j < B.length(); j++)
            Bset.insert(hashstring(B[j], times));
    }
    for (auto a : A)
    {
        int lofa = a.first.length();
        string encodeA = hashstring(a.first);
        if (Bset.find(encodeA) != Bset.end())
            ans += a.second;
    }
    return ans;
}

int anagrams(map<string, int>& A, string B) {
    int ans = 0;
    int lofb = B.length();
    for (auto a : A) {
        int lofa = a.first.length();
        unsigned long long hashA = gethash(a.first);
        for (int pos = 0; pos <= lofb - lofa; pos++)
        {
            if (gethash(B.substr(pos, lofa)) == hashA) {
                ans += a.second;
                break;
            }
        };
    }
    return ans;
}

int main() {
    int T, L;
    string A, B;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        cin >> L;
        cin >> A >> B;
        map<string, int> pA = processA(A);
        printf("Case #%d: %d\n", i, anagramsT(pA, B));
    }
}
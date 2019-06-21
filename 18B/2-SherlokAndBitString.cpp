// small input
#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;

string Sherlock()
{
    int N, K;
    long long P;
    cin >> N >> K;
    cin >> P;
    bitset<100> pbits(0);
    int pos = 0;
    P = P - 1;
    while (P > 0) {
        pbits[pos] = P & 1;
        P = P >> 1;
        pos++;
    }
    bitset<100> mark(0);
    bitset<100> res(0);
    int A, B, C;
    for (int i = 0; i < K; i++)
    {
        cin >> A >> B >> C;
        mark[N-A] = 1;
        res[N-A] = C;
    }
    pos = 0;
    while(pbits.any()) {
        while(mark[pos]) pos++;
        res[pos] = pbits[0];
        pos++;
        pbits = pbits >> 1;
    }
    return res.to_string().substr(100 - N);
}

int main()
{
    int T;
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        string s = Sherlock();
        cout << "Case #" << i + 1 << ": " << s << endl;
    }
}
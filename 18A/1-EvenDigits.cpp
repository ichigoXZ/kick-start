// https://codingcompetitions.withgoogle.com/kickstart/round/0000000000050edf/00000000000510ed? 

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

unsigned long long supervin(string x)
{
    int pos = 0;
    int n = x.length();
    for (; pos < n; pos++)
        if ((x[pos] - '0') & 1)
            break;
    if (pos == n - 1)
        return 1;
    if (pos == n)
        return 0;
    // down
    unsigned long long base = pow(10, n - pos - 1);
    unsigned long long rem = stoull(x.substr(pos + 1));
    string lowbound(n - pos - 1, '8');
    unsigned long long down = base - stoull(lowbound) + rem;
    // up
    if (x[pos] == '9')
        return down;
    unsigned long long up = base - rem;
    return min(up, down);
}

int main()
{
    int n;
    cin >> n;
    string x;
    for (int i = 0; i < n; i++)
    {
        cin >> x;
        cout << "Case #" << i + 1
             << ": " << supervin(x) << endl;
    }
}
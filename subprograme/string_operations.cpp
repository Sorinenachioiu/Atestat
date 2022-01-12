#include <bits/stdc++.h>
using namespace std;

void read_string(string &s)
{
    getline(cin, s);
}

void resize_string(string &s)
{
    while((int)s.size() < 16)
    {
        s += s;
    }
    s.resize(16);
}

void cut_half(string &s)
{
    string t;
    int L = (int)s.size();
    t = s.substr(L/2, L/2+1);
    s.resize(L/2);
    s = t + s;
}

void rev_string(string &s)
{
    reverse(s.begin(), s.end());
}

int main()
{
    string s;
    read_string(s);
    //resize_string(s);
    cout << s <<'\n';

    cut_half(s);
    cout << s;
}

#include<bits/stdc++.h>
using namespace std;

const int P = 666013;
const int MOD = 1'000'000'007;

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
    t = s.substr(8, 15);
    s.resize(8);
    s = t + s;
}

struct Hash
{
    vector <int> h;
    vector <int> pow_p;

    Hash(string s, string t, int row, int col)
    {
        for(int poz_crt = 0; poz_crt <= (int)s.size(); poz_crt++)
        {
            int last = 0;
            if(!h.empty())
                last = h.back();
            h.push_back((1LL * last * P * row * col + s[poz_crt] * t[poz_crt])%MOD);
        }

        pow_p.resize((int)s.size());
        pow_p[0] = 1;

        for(int i = 1; i <= (int)s.size(); i++)
            pow_p[i] = 1LL * pow_p[i-1] * P %MOD;
    }

    string GetHash(int row, int col)
    {
        int temp = (h[(int)h.size() - col] - 1LL * h[row] * pow_p[(int)h.size() - col - row + 1]) % MOD;
        temp = (temp + MOD)%MOD;
        string ans;
        while(temp)
        {
            char c_crt = temp%10 + (int)'0';
            temp /= 10;
            ans.push_back(c_crt);
        }
        return ans;
    }
};

int main()
{
    string s, t;
    read_string(s);
    if((int)s.size() < 16)
        resize_string(s);
    t = s;

    while (1) {
        int x1, y1;
        cout << "X - Y: ";
        cin >> x1 >> y1;
        for(int row = 1; row <= 8; row++)
            for(int col = 1; col <= 8; col++)
            {
                Hash h1(s, t, row, col);
                Hash h2(t, s, row, col);
                s = h1.GetHash(row, col);
                string s2 = h2.GetHash(row, col);
                string s3;
                resize_string(s);
                resize_string(s2);
                s3 = s;
                cut_half(s3);
                cout << s <<" " << s2 <<" " << s3 <<" " << t << '\n'  ;
                s = s + s2 + s3;
                cout << "Hash of " << t.substr((int)t.size() - col, (int)t.size() - col - row + 1) << " is " << s << '\n';
            }   
    }
}

#include <bits/stdc++.h>
using namespace std;
ofstream out("culori.out");

//265355929265355995034281950342819265355926535592
//870749694870749637947583537947584870749687074969
//057157069057157064420430564420439057157005715706
//356741165356741106589346065893465356741135674116
//P*nr%256;

const int P = 666013;

int operator - (const string &a, const string &b)
{
    int z = 0;
    for(auto c_crt:a)
    {
        z = z*10 + (int)(c_crt - '0');
    }
    return z;
}

int from_s_to_int(string s, int crt_poz)
{
    string t;
    t = s.substr(crt_poz, 3);
    int ans;
    ans = t - "";
    return ans;
}

void write_colour(string s)
{
    int to_colour;
    //out <<"let color_" << crt_color <<" = ["; 
    for(int j = 0; j <= 128; j++)
    {
        for(int z = 1 ; z <= 8; z++)
        {
            for(int i = 0; i < 48; i = i + 3)
            {
                to_colour = from_s_to_int(s, i);
                to_colour = P * to_colour % 256;
                out << to_colour << " , " ;
            }
        }
    }
}

int main()
{
    int nr = 0;
    
    string a = "481918747481918708932269108932267481918748191874";
    string t;

    write_colour(a);
    

    return 0;
}
// iubire :
//481918747481918708932269108932267481918748191874
//053485410534854176471469764714690534854105348541
//937051395937051373989295473989295937051393705139
//

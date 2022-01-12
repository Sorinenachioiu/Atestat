#include <bits/stdc++.h>
using namespace std;
ifstream in("crt_word.in");
ofstream red_color("red.out");
ofstream blue_color("blue.out");
ofstream green_color("green.out");


const int MAX_ROWS = 64;
const int P = 666013;
const int MOD = 1'000'000'007;

typedef void *(*functii) (bool op, string s, int nr);//define a pointer to a function

// <-------------- STRING OPERATIONS -------------->
void ReadString(string &s)
{
    getline(in, s);
}

void ResizeString(string &s)
{
    while((int)s.size() < 16)
    {
        s += s;
    }
    s.resize(16);
}

void CutHalf(string &s)
{
    string t;
    int L = (int)s.size();
    t = s.substr(L/2, L/2+1);
    s.resize(L/2);
    s = t + s;
}

void RevString(string &s)
{
    reverse(s.begin(), s.end());
}
//<-------------- END OF STRING OPERATIONS -------------->

//<-------------- HASH STRUCT -------------->
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
//<-------------- END OF HASH STRUCT -------------->


//<-------------- WRITE TO FILE FUNCTIONS -------------->
void *WriteToRed(bool op, string s, int nr)
{
    if(op == 0)
        red_color << s;
    else
        red_color << nr << ", " ; 
}

void *WriteToGreen(bool op, string s, int nr)
{
    if(op == 0)
        green_color << s;
    else
        green_color << nr << ", " ; 
}

void *WriteToBlue(bool op, string s, int nr)
{
    if(op == 0)
        blue_color << s;
    else
        blue_color << nr << ", " ;
}

functii functions[] =
{
    WriteToRed,
    WriteToGreen,
    WriteToBlue
};//create the vector of pointers to functions
//<-------------- END OF WRITE TO FILE FUNCTIONS -------------->


//<-------------- HASHING FUNCTION -------------->
int operator - (const string &a, const string &b)
{
    int z = 0;
    for(auto c_crt:a)
    {
        z = z*10 + (int)(c_crt - '0');
    }
    return z;
}

int FromSToInt(string s, int crt_poz)
{
    string crt_s;
    crt_s = s.substr(crt_poz, 3);
    int ans;
    ans = crt_s - "";
    return ans;
}

void WriteColors(string s, int color, int crt_row, int crt_col)
{
    int to_color;

    for(int crt_poz = 0; crt_poz < 48; crt_poz = crt_poz + 3)
    {
        to_color = FromSToInt(s, crt_poz);
        to_color = (P * to_color + crt_poz * crt_row * crt_col) % 256;
        functions[color](1, "", to_color);
    }

}

string GenerateCurrentHash(string s, string initial_s, int crt_row, int crt_col)
{
    string s2;
    string s3;

    Hash h1(s, initial_s, crt_row, crt_col);
    Hash h2(initial_s, s, crt_row, crt_col);
    
    s = h1.GetHash(crt_row, crt_col);
    s2 = h2.GetHash(crt_row, crt_col);
    ResizeString(s);
    ResizeString(s2);
    
    s3 = s;
    CutHalf(s3);

    s = s + s2 + s3;

    return s;
}

void HashGenerator(string s, int color)
{
    string initial_s;
    initial_s = s;

    for(int crt_row = 1; crt_row <= MAX_ROWS; crt_row++)
    {
        for(int crt_col = 1; crt_col <= MAX_ROWS/16; crt_col++)
        {   
            s = GenerateCurrentHash(s, initial_s, crt_row, crt_col);
            WriteColors(s, color, crt_row, crt_col);
        }
    }
}

void Hashing(string s, int color)
{
    switch(color)
    {
        case 0:
            WriteToRed(0, "let red_colors = [ ", 0);        
            break;
        case 1:
            WriteToGreen(0, "let green_colors = [ ", 0);
            break;
        case 2:
            WriteToBlue(0, "let blue_colors = [ ", 0);
            break;
    }

    HashGenerator(s, color);

    functions[color](0, " ];", 0);
}
/**
*   switch(col):
*       0 red
*       1 green
*       2 blue
*   for 1, MAX_ROWS
*       for 1, MAX_ROWS/16
*           generare_hash();
*           write_colour(h, col);
**/

//<-------------- END OF HASHING FUNCTION -------------->

//<-------------- MAIN FUNCTION -------------->
int main()
{
    string s;
    ReadString(s);
    if((int)s.size() < 16)
        ResizeString(s);
    
    Hashing(s, 0);//0 - red
    
    string s_gr = s;
    RevString(s_gr);
    Hashing(s_gr, 1);//1 - green
    
    string s_bl = s; 
    CutHalf(s_bl); 
    Hashing(s_bl, 2);//2 - blue
/**
* read_string(s);
* resize_string(s);
* hashing(s, 0);
* s_gr = rev_string(s);
* hashing(s_gr, 1);
* s_blue = cut_half(s);
* hashing(s, 2);
**/
}
//<-------------- END OF MAIN FUNCTION -------------->

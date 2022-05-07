#include <bits/stdc++.h>
using namespace std;
ifstream in("crt_word.in");
ofstream red_color("red.out");
ofstream blue_color("blue.out");
ofstream green_color("green.out");

// definim dimensiunea matricei/imaginii finale
const int MAX_ROWS = 64; 

// definim doua variabile numere prime,
// care o sa fie utilizate in calcularea hash-urilor
const int P = 666013; 
const int MOD = 1'000'000'007; 

// definim un pointer spre o functie
typedef void *(*functii) (bool op, string s, int nr);

/* <-------------- STRING OPERATIONS --------------> */

// functie care citeste un sir de caractere
void ReadString(string &s)
{
    getline(in, s);
}

// functie care redimensioneaza un string
// in asa fel incat acesta sa aiba exact 16 caractere
void ResizeString(string &s)
{
    while((int)s.size() < 16)
    {
        s += s;
    }
    s.resize(16);
}

// functie care preia un sir de caractere
// si ii inverseaza prima jumatate cu cea de a doua jumatate
void CutHalf(string &s)
{
    string t;
    int L = (int)s.size();
    t = s.substr(L/2, L/2+1);
    s.resize(L/2);
    s = t + s;
}

// functie care inverseaza un sir de caractere
void RevString(string &s)
{
    reverse(s.begin(), s.end());
}

/* <-------------- END OF STRING OPERATIONS --------------> */

/* <-------------- HASH STRUCT --------------> */

struct Hash
{
    vector <int> h;
    vector <int> pow_p;

    // initializam un Hash in momentul in care il cream
    Hash(string s, string t, int row, int col)
    {
        // parcurgem sirul de caractere s
        for(int poz_crt = 0; poz_crt <= (int)s.size(); poz_crt++)
        {
            int last = 0;
            
            // daca exista cel putin un element in h atunci  
            // acesta va fi folosit in calculul h-ului urmator
            if(!h.empty())
                last = h.back();

            // hash-ul este calculat in functie de randul, coloana curenta,
            // ultimul h, cele doua variabile numere prime si caracterele
            // de pe pozitia curenta in s si t 
            h.push_back((1LL * last * P * row * col + s[poz_crt] * t[poz_crt])%MOD);
        }

        pow_p.resize((int)s.size());
        pow_p[0] = 1;

        // initializam vectorul p cu valori in functie de cele doua variabile numere prime
        for(int i = 1; i <= (int)s.size(); i++)
            pow_p[i] = 1LL * pow_p[i-1] * P %MOD;
    }

    // functie care returneaza Hash-ul
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

/* <-------------- END OF HASH STRUCT --------------> */


/*<-------------- WRITE TO FILE FUNCTIONS --------------> */

/**
 * functie care scrie in fisierul corespunzator 
 * culorii rosii din matricea finala
 * op = 1 => o sa fie scris un numar
 * op = 0 => o sa fie scris un sir de caractere
 **/ 
void *WriteToRed(bool op, string s, int nr)
{
    if(op == 0)
        red_color << s;
    else
        red_color << nr << ", " ; 
}

/** 
 * functie care scrie in fisierul corespunzator 
 * culorii verde din matricea finala
 * op = 1 => o sa fie scris un numar
 * op = 0 => o sa fie scris un sir de caractere
 **/
void *WriteToGreen(bool op, string s, int nr)
{
    if(op == 0)
        green_color << s;
    else
        green_color << nr << ", " ; 
}

/**
 * functie care scrie in fisierul corespunzator 
 * culorii albastru din matricea finala
 * op = 1 => o sa fie scris un numar
 * op = 0 => o sa fie scris un sir de caractere
 **/
void *WriteToBlue(bool op, string s, int nr)
{
    if(op == 0)
        blue_color << s;
    else
        blue_color << nr << ", ";
}

// cream un vector de pointeri spre 
// functiile de scris in fisiere
functii functions[] =
{
    WriteToRed,
    WriteToGreen,
    WriteToBlue
};//create the vector of pointers to functions 

/*<-------------- END OF WRITE TO FILE FUNCTIONS --------------> */


/* <-------------- HASHING FUNCTION --------------> */

/** 
 * declaram un operator "-" intre doua stringuri, 
 * parametrii de intrare sunt doua stringuri prin referinta 
 * primul string o sa contina numai caractere, 
 * caractere >= 0 si <= 9 
 * rezultatul operatiei o sa fie de tip intreg 
**/
int operator - (const string &a, const string &b)
{
    int z = 0;
    for(auto c_crt:a)
    {
        z = z*10 + (int)(c_crt - '0');
    }
    return z;
}

/**
 * functie care primeste ca parametrii de intrare un string si pozitia 
 * curenta in care ne aflam in el 
 * (stringul este format numai din numere intregi) 
 * transforma cele 3 caractere de la pozitia curenta in intr-un numar intreg 
 **/ 
int FromSToInt(string s, int crt_poz)
{
    string crt_s;
    crt_s = s.substr(crt_poz, 3);
    int ans;
    ans = crt_s - "";
    return ans;
}

/**
 * functie care divizeaza hash-ul in grupe de cate 3 valori, 
 * pe care le converteste in valori intregi, 
 * folosite pentru a genera valori intre 0-255, 
 * corespunzatoare unei culori
 **/
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

/**
 * functie care genereaza un hash de 48 de caractere numerice,
 **/
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

/**
 * functie care transforma in mod repetat sirul intr-un hash de 48 de caractere numerice,
 * hash-ul fiind apoi folosit pentru a calcula culorile 
 **/
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

/**
 * functie care scrie valorile generate pentru o anumita culoare  
 * in fisier-ul corespunzator acesteia
 **/
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

/* <-------------- END OF HASHING FUNCTION --------------> */

/*<-------------- MAIN FUNCTION --------------> */
int main()
{
    string s;

    // Citeste un sir de caractere
    ReadString(s);

    // Daca sirul are sub 16 caractere atunci este redimensionat
    if((int)s.size() < 16)
        ResizeString(s);
    
    // Calculeaza valorile din matricea corespunzatoare culorii rosu in functie de sirul s
    Hashing(s, 0);//0 - red
    
    string s_gr = s;
    RevString(s_gr); 
    // Calculeaza valorile din matricea corespunzatoare culorii verde in functie de sirul s_gr
    Hashing(s_gr, 1);//1 - green
    

    string s_bl = s; 
    CutHalf(s_bl); 
    // Calculeaza valorile din matricea corespunzatoare culorii albastru in functie de sirul s_bl
    Hashing(s_bl, 2);//2 - blue
}
/**
* read_string(s);
* resize_string(s);
* hashing(s, 0);
* s_gr = rev_string(s);
* hashing(s_gr, 1);
* s_blue = cut_half(s);
* hashing(s, 2);
**/
/* <-------------- END OF MAIN FUNCTION --------------> */

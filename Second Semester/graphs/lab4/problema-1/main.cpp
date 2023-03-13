#include <iostream>
#include <fstream>

using namespace std;

ifstream f("../4-in.txt");
ofstream fout("../4-out.txt");

int p[101], cod[101], n, varfuri, k;
/*
 * Implementați rutina de codare Prüfer. Implementarea trebuie săfie eficientădin punctul de vedere
 * al memoriei folosite și al timpului de execuție.
 */

void elimina_frunza(int i)
{
    p[i] = -2;
    n--;
}

int frunza_minima()
{
    int i, j, is_parent;
    for(i=0; i<varfuri; i++)
        if(p[i] != -2)
        {
            is_parent = 0;
            for(j=0; j<varfuri; j++)
                if(i == p[j])
                    is_parent = 1;
            if(is_parent == 0)
                return i;
        }
}

void codare_Prufer()
{
    int i;
    while(n > 1)
    {
        i = frunza_minima();
        cod[k++] = p[i];
        elimina_frunza(i);
    }
}

int main()
{
    int i,j;
    f >> n;
    for(i=0; i<n; i++)
        f >> p[i];
    varfuri = n;
    codare_Prufer();
    fout << k << endl;
    for(i=0; i<k; i++)
        fout << cod[i] << " ";
    return 0;
}


#include <iostream>
#include <fstream>

using namespace std;

ifstream f("../4-in.txt");
ofstream fout("../4-out.txt");

int p[101], cod[101], q[101], exista[101], varfuri, k, dr, st;
/*
 * Implementați  rutina  de  decodare  Prüfer.  Implementarea  trebuie  să fie
 * eficientă din  punctul  de  vedere  al memoriei folosite și al timpului de execuție.
 */

int minim()
{
    int mini=10000, i, j;
    bool apare;
    for(i=0; i<varfuri; i++)
    {
        apare=false;
        for(j=st; j<=dr; j++)
        {
            if(i==q[j])
                apare=true;
        }
        if(apare==false && i<mini)
            mini=i;
    }
    return mini;
}

void decodare_Prufer()
{
    int i, x, y;
    st = 0;
    dr = 0;
    q[0]=cod[0];
    //fout<<q[0]<<" ";
    for(i=1;i<k;i++)
    {
        q[++dr]=cod[i];
        //fout<<q[dr]<<" ";
    }
    //fout<<endl;
    for(i=0;i<varfuri-1;i++)
    {
        if(st<=dr)
        {
            x=q[st];
            //fout<<x<<"-";
            y=minim();
            //fout<<y<<"  ";
            p[y]=x;
            st++;
            q[++dr]=y;
        }
    }
}

int main()
{
    int i,j;
    f >> k;
    for(i=0; i<k; i++)
        f >> cod[i];
    varfuri = k+1;
    for(i=0; i<varfuri; i++)
        p[i] = -1;
    decodare_Prufer();
    fout << varfuri << endl;
    for(i=0; i<varfuri; i++)
        fout << p[i] << " ";
    return 0;
}



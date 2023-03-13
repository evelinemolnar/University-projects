#include <fstream>
#include <algorithm>
using namespace std;

ifstream cin("../10-in.txt");
ofstream cout("../10-out.txt");

int n , m , x , y , w , T[10001] , rez , cnt;
struct poz
{
    int i , j , c;
}M[10001];

poz A[10001];

/*
 * Se dăun graf neorientat ponderat, găsiți un arbore minim de acoperirepentru graful dat.
 * Graful dat este conex. Implementarea trebuie săfie eficientădin punctul de vedere al memoriei
 * folosite și al timpului de execuție. (Implementați un algoritm de arbore minim de acoperire: Kruskal, Prim)
 */

int leaga(int a , int b)
{
    T[a] = T[b];
}

int radacina(int a)
{
    if(a == T[a]) return a;
    else return T[a] = radacina(T[a]);
}

void kruskal()
{
    int r1 , r2;
    for(int i = 1 ; i <= m ; i++)
    {
        r1 = radacina(M[i].i);
        r2 = radacina(M[i].j);
        if(r1 != r2)
        {
            rez += M[i].c;
            A[++cnt] = M[i];
            leaga(r1 , r2);
        }
    }
}

int comp(poz a , poz b)
{
    return a.c < b.c;
}

int comp_(poz a , poz b)
{
    if (a.i < b.i) return 1;
    else if(a.i == b.i && a.j < b.j) return 1;
    else return 0;
}

void init()
{
    for(int i = 1 ; i <= n ; i++)
        T[i] = i;
}

int main()
{
    cin >> n >> m;
    for(int i = 1 ; i <= m ; i++)
    {
        cin >> x >> y >> w;
        M[i].i = x , M[i].j = y , M[i].c = w;
    }
    sort(M + 1 , M + m + 1 , comp);
    init();
    kruskal();
    cout << rez << '\n';
    cout << n - 1  << '\n';
    sort(A+1, A+n, comp_);
    for(int i = 1 ; i < n ; i++)
        cout << A[i].i << " " << A[i].j << '\n';
}


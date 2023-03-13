#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <string>

typedef struct parinte {
	std::string st, dr;
};

std::map<std::string, int> fr;
std::map<std::string, std::string> coduri;
std::map<std::string, parinte> fii;

std::string min_char(std::string c) {
	char min = 'z';
	for (auto it : c)
		if (it < min) min = it;

	std::string ret = "";
	ret = ret + min;
	return ret;
}

struct cmp
{
	bool operator()(std::string x, std::string y)
	{
		if (fr[x] != fr[y])
			return fr[x] > fr[y];
		return min_char(x) > min_char(y);
	}
};

void parcurgere(std::string k, std::string nr) {
	if (k.length() == 1) coduri[nr] = k;
	nr = nr + '0';
	if (fii[k].st != "-1")
		parcurgere(fii[k].st, nr);
	nr.pop_back();
	nr = nr + '1';
	if (fii[k].dr != "-1")
		parcurgere(fii[k].dr, nr);
}

int main(int argc, char** argv) {

	std::ifstream fin(argv[1]);
	std::ofstream fout(argv[2]);

	std::string prop = "", prim;
	std::priority_queue<std::string, std::vector<std::string>, cmp > pq;
	int n, x=0;
	std::string cs;
	char c;

	fin >> n;
	getline(fin,cs);
	for (int i = 1; i <= n; i++) {
		std::getline(fin, cs);
		x = 0;
		int j = 2;
		while (j < cs.size()) {
			x = x * 10 + (int)(cs[j] - '0');
			j++;
		}
		cs = cs[0];
		fr[cs] = x;
		pq.push(cs);
	}
	
	std::getline(fin, prop);
	for (int i = 1; i < n; i++) {//construim arborele
		std::string x = pq.top();
		pq.pop();
		std::string y = pq.top();
		pq.pop();
		int sum = fr[x] + fr[y];
		std::string n = x + y;
		fr[n] = sum;
		pq.push(n);

		if (x.length() == 1) {//nod frunza, nu are descendenti
			std::string snull = "-1";
			parinte fnull;
			fnull.st = snull;
			fnull.dr = snull;
			fii[x] = fnull;
		}

		if (y.length() == 1) {//nod frunza, nu are descendenti
			std::string snull = "-1";
			parinte fnull;
			fnull.st = snull;
			fnull.dr = snull;
			fii[y] = fnull;
		}

		prim = n;
		parinte desc;
		if (fr[x] != fr[y]) {
			desc.st = x;
			desc.dr = y;
		}
		else {
			std::string minx = min_char(x);
			std::string miny = min_char(y);

			if (minx < miny) {
				desc.st = x;
				desc.dr = y;
			}
			else {
				desc.st = y;
				desc.dr = x;
			}
		}
		fii[prim] = desc;

	}
	parcurgere(prim, ""); //determinam pt fiecare litera codul ei

	std::string cod = "";
	for (auto& c : prop) {
		cod += c;
		//std::cout << cod<<'\n';
		if (fr[coduri[cod]] > 0) {
			fr[coduri[cod]] --;
			fout << coduri[cod];
			cod = "";
		}
	}

	return 0;
}
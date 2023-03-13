#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
/*
 * Se dă un graf orientat fără circuite. Fiecare arc are asociată o capacitate.
 * Să se determine fluxum maxim care poate fi trimis dintr-un vârf sursă s către un vârf destinație t.
 * Implementați algoritmul Ford-Fulkerson sau Edmonds-Karp pentru rezolvarea problemei.
 * Implementarea trebuie să fie eficientă din punctul de vedere al memoriei folosite și al timpului de execuție.
 */
std::vector<std::vector<std::pair<int, int>>> rezid;
std::vector<bool> vf;
std::vector<int> tati;
std::queue<int> q;
int n, e, x, y, c, s, t, sw, cf,fMax = 0;

void BFS(int k) {
	std::queue<int> C;
	C.push(k);
	vf[k] = 1;
	while (!C.empty())
	{
		k = C.front();
		for (auto& it : rezid[k])
			if (vf[it.first] == 0)
			{
				tati[it.first] = k;
				C.push(it.first);
				vf[it.first] = 1;
				if (it.first == t) sw = 1;
			}
		C.pop();
	}
}

void afla_cf(int k){//aflam cf minim dat de calea reziduala descperita in BFS
	if (tati[k] != -1) {
		int v = tati[k];
		for (auto& it : rezid[v])
			if (it.first == k) {
				if (cf > it.second) cf = it.second;
				afla_cf(v);
				break;
			}
	}
}

void parcurgere(int k) {//rescriem graful rezidual
	int c;
	if (tati[k] != -1) {
		int v = tati[k];
		int cont = 0;
		for (auto& it : rezid[v]) {
			if (it.first == k) {
				it.second = it.second - cf;
				if (it.second == 0) {
					rezid[v].erase(rezid[v].begin() + cont);//stergem un arc dc acesta este 0 (flux maxim pe acest arc)
				}
			}
			cont++;
		}
		int ok = 0;
		for (auto& it : rezid[k]) {
			if (it.first == v) {
				ok = 1;
				it.second += cf;
			}
		}
		if (ok == 0) {
			rezid[k].push_back(std::make_pair(v, cf));//adaugam arcul invers in calea reziduala
		
		}
		parcurgere(v);
	}
}

int main(int argc, char** argv) {

	std::ifstream fin(argv[1]);
	std::ofstream fout(argv[2]);

	fin >> n >> e;
	rezid.resize(n);
	vf.resize(n);
	tati.resize(n);

	for (int i = 1; i <= e; i++) {
		fin >> x >> y >> c;
		rezid[x].push_back(std::make_pair(y, c));
	}

	s = 0, t = n - 1, sw = 1, tati[s] = -1;
	while (sw == 1) {
		fill(vf.begin(), vf.end(), 0);
		sw = 0, cf = INT_MAX;
		BFS(s);
		afla_cf(t);
		if (sw) {
			fMax += cf;
			parcurgere(t);
		}
	}

	fout << fMax;
	return 0;
}
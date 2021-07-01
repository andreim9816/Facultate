#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
ifstream fin("date.in");
vector<int> tata, d, viz;
vector< vector<int> > adj; ///matrice de adiacenta
//complexitate DFS -> O(nr_noduri + nr_muchii) => O(n+ n-1) = O(n)
void DFS(int vf)
{
	viz[vf] = 1;
	for(int i = 0 ;i < adj[vf].size(); i++)
		if(viz[adj[vf][i]] == 0)
			DFS(adj[vf][i]);

	if(d[vf] == 0)
	{
		cout << vf << " ";
		d[tata[vf]] = 1;
	}
}
int main()
{
	int n, x, y;
	fin >> n;
	tata.resize(n + 1);
	viz.resize(n + 1);
	d.resize(n + 1);
	adj.resize(n + 1);
	for(int i = 1 ; i <= n-1; i++)
	{
		fin >> x >> y;
		tata[y] = x;
		adj[x].push_back(y); ///construim matricea de adiacenta
		adj[y].push_back(x);
	}
	DFS(1);
	return 0;
}

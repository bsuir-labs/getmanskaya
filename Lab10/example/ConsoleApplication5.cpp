#include"pch.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
using namespace std;

int main() {
	int m, n, s = 0;
	ifstream fin("input.txt"); 
	for (int j = 0; j < 5; j++) {
	fin >> n >> m;
	vector < vector<int> > graph(n);
		for (int i = 0; i < m; i++) 
		{
			int u, v;
			fin >> u >> v;
			graph[u - 1].push_back(v - 1);
			graph[v - 1].push_back(u - 1);
		}
		fin.close();
		
		queue<int> used; 
		used.push(s);
		vector<bool> color(n); 
		color[s] = true;
		while (!used.empty()) 
		{
			int v = used.front();
			used.pop(); 
			for (size_t i = 0; i < graph[v].size(); ++i) 
			{
				int to = graph[v][i];
				if (!color[to]) 
				{
					color[to] = true; 
					used.push(to); 
				}
			}
		}
		vector<bool>::iterator it;
		it = find(color.begin(), color.end(), false);
		ofstream fout("output.txt");
		if (it == color.end() && n - m == 1)
			fout << "Yes";
		else
			fout << "No";
		fout.close();
	}
	return 0;
}
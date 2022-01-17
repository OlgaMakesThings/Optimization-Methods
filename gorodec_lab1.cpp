#include <iostream>
#include <ctime>
#include <string>
#include <algorithm>
#include <random>
#include <ctime>
#include <string>
#include "dijkstra.h"
#include "bellman.h"
using namespace std;
vector<int> RandomGraph(int size)
{
	mt19937 gen;
	gen.seed(static_cast<unsigned int>(time(0)));
	vector<int> g(size * size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (i == j) {
				g[i * size + j] = 0;
			}
			else {
				if (j < i) {
					g[i * size + j] = g[j * size + i];
				}
				else {
					g[i * size + j] = gen() % 10;
				}
			}
		}
	}
	return g;
}

void PrintGraph(vector<int> g)
{
	for (int i = 0; i < sqrt(g.size()); i++) {
		for (int j = 0; j < sqrt(g.size()); j++) {
			cout << setw(2) << g[i * sqrt(g.size()) + j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void PrintDistance(vector<int> dist)
{
	for (size_t i = 0; i < dist.size(); i++) {
		cout << setw(2) << dist[i] << " ";
	}
	cout << endl;
}

vector<Edges> VectEdges(vector<int> g)
{
	int size = sqrt(g.size());
	vector<Edges> loc_edg;
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			if (g[i * size + j] != 0) {
				loc_edg.push_back({ i,j,g[i * size + j] });
			}
		}
	}
	return loc_edg;
}

bool CheckGraph(int num, vector<Edges> g) {

	int counter = 0;
	if (g[0].f == 0) {
		counter++;
	}
	counter++;
	for (int i = 1; i < g.size(); i++) {
		bool flag = true;
		for (int j = i - 1; j >= 0; j--) {
			if (g[i].s == g[j].s) {
				flag = false;
				break;
			}
		}
		if (flag) {
			counter++;
		}
	}
	if (counter == num) {
		return true;
	}
	else {
		return false;
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");
	string num;
	int size = 0;
	bool ex = false;
	cout << "Введите размер графа: ";
	cin >> size;
	vector<int> graph(size * size);
	vector<Edges> edg;

	cout << "Рандомный граф:" << endl;
	graph = RandomGraph(size);
	PrintGraph(graph);
	cout << "Номера вершин: " << endl;
	for (int i = 0; i < size; i++) {
		cout << i << " ";
	}
	edg = VectEdges(graph);
	cout << endl;
	for (int i = 0; i < edg.size(); i++) {
		cout << "Ребро [" << edg[i].f << "][" << edg[i].s << "] " << " = " << edg[i].weit << "\n";
	}
	cout << endl;	
	
	bool check = CheckGraph(size, edg);
	if (!check) {
		cout << "Граф несвязный, try again." << endl;
		return 0;
	}
	cout << endl;
	while (!ex) {
		cout << "1. Алгоритм Беллмана" << endl;
		cout << "2. Алгоритм Дейкстры" << endl;
		cout << "3. Выход" << endl << endl;
		cout << "Выберите пункт: " << endl;
		cin >> num;
		cout << endl;
		if (num == "1") {
			int f, s;
			cout << "Две вершины" << endl;
			cin >> f;
			cin >> s;
			vector <int> dist(size);
			dist = Bellman(size, edg, f, s);
			cout << "Расстояние от " << dist[0] << " до " << dist[1] << " = " << dist[2] << endl;
			cout << endl;
		}
		else if (num == "2") {
			int vert;
			cout << "Вершина: ";
			cin >> vert;
			vector <int> dist(size);
			dist = Dijkstra(graph, vert);
			cout << "Расстояния вершины " << vert << " до остальных: " << endl;
			PrintDistance(dist);
			cout << endl;
		}
		else if (num == "3") {
			ex = true;
			cout << endl;
		}
		else if (num != "3" && num != "2" && num != "1") {
			cout << "Неверный номер" << endl;
			cout << endl;
		}
	}
	return 0;
}
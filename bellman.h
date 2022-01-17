#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
using namespace std;

struct Edges
{
	int f;
	int s;
	int weit;
};

vector<int> Bellman(int size, vector<Edges> g, int f, int s);

#include "bellman.h"

vector<int> Bellman(int size, vector<Edges> g, int f, int s)
{
	int MAX = 2147483647;
	vector<int> opt_weit(size, MAX);
	vector<int> path(size, -1);
	opt_weit[f] = 0;
	vector<int> res;
	int res_weit = 0;

	while (1) {
		bool flag = false;
		for (int j = 0; j < g.size(); ++j) {
			if (opt_weit[g[j].f] < MAX) {
				if (opt_weit[g[j].s] > opt_weit[g[j].f] + g[j].weit) {
					opt_weit[g[j].s] = opt_weit[g[j].f] + g[j].weit;
					path[g[j].s] = g[j].f;
					flag = true;
				}
			}
		}
		if (!flag) break;
	}
	res.push_back(s);
	int i = s;
	while (path[i] != -1) {
		res.push_back(path[i]);
		for (int j = 0; j < g.size(); j++) {
			if (g[j].f == path[i] && g[j].s == i) {
				res_weit += g[j].weit;
				break;
			}
		}
		i = path[i];
	}
	reverse(res.begin(), res.end());
	res.push_back(res_weit);
	return res;
}
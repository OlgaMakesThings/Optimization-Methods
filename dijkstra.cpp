#include "dijkstra.h"

vector<int> Dijkstra(vector<int> g, int beg) {
    int MAX = 2147483647;
    int size = sqrt(g.size());
    vector<int>dist(size, MAX);
    vector<bool>visit(size, false);
    int id = 0, u = 0;
    dist[beg] = 0;

    for (int i = 0; i < size - 1; i++) {
        int min = MAX;
        for (int j = 0; j < size; j++) {
            if (!visit[j] && dist[j] <= min) {
                min = dist[j];
                id = j;
            }
        }
        u = id;
        visit[u] = true;
        for (int k = 0; k < size; k++) {
            if (!visit[k] && dist[u] != MAX && g[u * size + k]
                && dist[u] + g[u * size + k] < dist[k]) {
                dist[k] = dist[u] + g[u * size + k];
            }
        }
    }
    return dist;
}

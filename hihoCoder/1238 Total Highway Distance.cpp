#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 100000 + 5;

int n, m;
struct Edge {
    int v, w, next;
} edge[MAXN * 2];
int head[MAXN], edgeNum;
int parent[MAXN];

void clearEdge() {
    edgeNum = 0;
    memset(head, -1, sizeof(head));
}

inline void addEdgeSub(int u, int v, int w) {
    edge[edgeNum].v = v;
    edge[edgeNum].w = w;
    edge[edgeNum].next = head[u];
    head[u] = edgeNum++;
}

inline void addEdge(int u, int v, int w) {
    addEdgeSub(u, v, w);
    addEdgeSub(v, u, w);
}

int num[MAXN], weight[MAXN];

long long getDist(int u, int p, int w) {
    long long d = 0;
    parent[u] = p;
    weight[u] = w;
    num[u] = 1;
    for (int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].v;
        if (v != p) {
            d += getDist(v, u, edge[i].w);
            num[u] += num[v];
        }
    }
    if (u != 1) {
        d += (long long)num[u] * (n - num[u]) * w;
    }
    return d;
}

long long total;
char op[20];

int main() {
    int u, v, w;
    scanf("%d%d", &n, &m);
    clearEdge();
    for (int i = 1; i < n; ++i) {
        scanf("%d%d%d", &u, &v, &w);
        addEdge(u, v, w);
    }
    total = getDist(1, 0, 0);
    while (m--) {
        scanf("%s", op);
        if (op[0] == 'Q') {
            cout << total << endl;
        } else {
            scanf("%d%d%d", &u, &v, &w);
            if (parent[u] != v) {
                swap(u, v);
            }
            total += (long long)num[u] * (n - num[u]) * (w - weight[u]);
            weight[u] = w;
        }
    }
    return 0;
}
/*
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <iostream>
using namespace std;

#define MAXN 100010

vector<int> edges[MAXN];
vector<long long> d[MAXN];
int child[MAXN];
int fa[MAXN];
long long thd = 0;

int N, M;


void addEdge(int u, int v, int w) {
    edges[u].push_back(v);
    d[u].push_back(w);
}

void addDEdge(int u, int v, int w) {
    addEdge(u, v, w);
    addEdge(v, u, w);
}

void dfs(int u, vector<int> &vis) {
    vis[u] = 1;
    child[u] = 0;
    for (int i = 0; i < edges[u].size(); ++i) {
        int v = edges[u][i];
        if (!vis[v]) {
            fa[v] = u;
            dfs(v, vis);
            child[u] += child[v] + 1;
            thd += d[u][i] * (child[v] + 1)*(N - 1 - child[v]);
        }
    }
}

int update(int u, int v, int k) {
    int old = 0;
    for (int i = 0; i < edges[u].size(); ++i) {
        if (edges[u][i] == v) {
            old = d[u][i];
            d[u][i] = k;    
        }
    }

    for (int i = 0; i < edges[v].size(); ++i) {
        if (edges[v][i] == u) {
            d[v][i] = k;
        }
    }

    return old;
}

int main() {
    
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N - 1; ++i) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        addDEdge(u, v, w);
    }
    vector<int> vis(N+1, 0);
    fa[1] = 0;
    dfs(1, vis);

    for (int k = 1; k <= M; ++k) {
        char op[10];
        scanf("%s", op);
        if (strcmp(op, "EDIT") == 0) {
            int u, v, k;
            scanf("%d%d%d", &u, &v, &k);
            int old = update(u, v, k);
            if (fa[v] == u) {
                thd += (long long)(k - old) * (child[v] + 1) * (N - 1 - child[v]);
            }
            else {
                thd += (long long)(k - old) * (child[u] + 1) * (N - 1 - child[u]);
            }
        }
        else {
            printf("%lld\n", thd);
        }
    }
}
*/

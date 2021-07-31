set<int> g[N];
int sub[N], par[N], level[N];
int curSize;
int dis[20][N];
int calcSize(int u, int p) {
    sub[u] = 1;  // subtree size calculate
    for (int v : g[u]) {
        if (v != p) sub[u] += calcSize(v, u);
    }
    return sub[u];
}

int getCentroid(int u, int p) {
    for (int v : g[u])  // finding centroid
        if (v != p && sub[v] > curSize / 2) return getCentroid(v, u);
    return u;
}

void setDis(int u, int from, int par = -1, int l = 0) {
    dis[from][u] = l;  // set Distance for ancestors.
    for (int v : g[u]) {
        if (v != par) setDis(v, from, u, l + 1);
    }
}
void decompose(int u, int p, int l) {
    curSize = calcSize(u, u);
    int centroid = getCentroid(u, u);
    setDis(centroid, l);
    par[centroid] = p;
    level[centroid] = l;
    for (int v : g[centroid]) {
        g[v].erase(centroid);
        decompose(v, centroid, l + 1);
    }
    g[centroid].clear();
}
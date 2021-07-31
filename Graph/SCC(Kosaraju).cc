vector<int> g[N], rg[N];
vector<int> order, component;
bool vis[N];
void dfs1(int u) {
    vis[u] = 1;
    for (int v : g[u])
        if (!vis[v]) dfs1(v);
    order.push_back(u);
}
void dfs2(int u) {
    vis[u] = 1;
    component.push_back(u);
    for (int v : rg[u])
        if (!vis[v]) dfs2(v);
}
void scc(int n) {
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= n; i++)
        if (!vis[i]) dfs1(i);
    memset(vis, 0, sizeof(vis));
    reverse(order.begin(), order.end());
    for (auto v : order) {
        if (!vis[v]) {
            dfs2(v);
            component.clear();
        }
    }
}
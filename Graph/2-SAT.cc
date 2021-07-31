bool vis[N];
vector<int> g[N], rg[N];
int dfs_t[N], ord[N], par[N];
int n, intime;  // N=2*n
int neg(int x) { return x <= n ? x + n : x - n; }
void add_implication(int a, int b) {
    if (a < 0) a = n - a;
    if (b < 0) b = n - b;
    g[a].push_back(b);
    rg[b].push_back(a);
}
/*Implication rules
 OR - (-a,b),(-b,a) NOR - (-a,-b)AND
 XOR- (a,b),(-a,-b)OR XNOR - (a,-b),(-a,b)OR
 AND - (a,b),(a,-b),(-a,b)OR NAND - (-a,-b)OR
*/
void force_true(int x) {
    if (x < 0) x = n - x;
    add_implication(neg(x), x);
}
void force_false(int x) {
    if (x < 0) x = n - x;
    add_implication(x, neg(x));
}
void topsort(int u) {
    vis[u] = 1;
    for (int v : rg[u])
        if (!vis[v]) topsort(v);
    dfs_t[u] = ++intime;
}
void dfs(int u, int p) {
    par[u] = p, vis[u] = 1;
    for (int v : g[u])
        if (!vis[v]) dfs(v, p);
}
void build() {
    int i, x;
    for (i = n * 2, intime = 0; i >= 1; i--) {
        if (!vis[i]) topsort(i);
        ord[dfs_t[i]] = i;
    }
    memset(vis, 0, sizeof(vis));
    for (i = n * 2; i > 0; i--) {
        x = ord[i];
        if (!vis[x]) dfs(x, x);
    }
}
bool satisfy(vector<int>& ret) {
    build();  // ret contains true values
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= n * 2; i++) {
        int x = ord[i];
        if (par[x] == par[neg(x)]) return 0;
        if (!vis[par[x]]) {
            vis[par[x]] = 1;
            vis[par[neg(x)]] = 0;
        }
    }
    for (int i = 1; i <= n; i++)
        if (vis[par[i]]) ret.push_back(i);
    return 1;
}
int main() {}

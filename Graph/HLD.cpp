vector<int> adj[mx];
vector<int> val;
int n, cur;  // 1 indexed.
int parent[mx], depth[mx], pos[mx];
int head[mx], tail[mx], heavy[mx];
int dfs(int u) {
    int sub = 1, big = 0;
    for (int v : adj[u]) {
        if (v == parent[u]) continue;
        parent[v] = u;
        depth[v] = depth[u] + 1;
        int subsize = dfs(v);
        if (subsize > big) big = subsize, heavy[u] = v;
        sub += subsize;
    }  // Find depth,parent and heavy child
    return sub;
}
void decompose(int u, int par) {
    head[u] = par;   // head[u] stored the start node of the chain.
    pos[u] = ++cur;  // pos[u] indicates the position of node u in segment tree.
    arr[cur] = val[u];
    if (heavy[u]) decompose(heavy[u], par);
    for (int v : adj[u]) {
        if (v == parent[u] || v == heavy[u]) continue;
        decompose(v, v);
    }
}
void makeHLD(int root = 1) {
    dfs(root);
    decompose(root, root);
    // build(1, 1, n);
}
data pathQuery(int u, int v) {
    data ret;
    for (; head[u] != head[v]; v = parent[head[v]]) {
        if (depth[head[u]] > depth[head[v]]) swap(u, v);
        /* data tmp = query(pos[head[v]], pos[v]);
         combine(ret, ret, tmp);*/
    }
    if (depth[u] > depth[v]) swap(u, v);
    /* data tmp = query(pos[u], pos[v]);
     combine(ret, ret, tmp);*/
    return ret;
}
void pathUpdate(int u, int v, int val) {
    for (; head[u] != head[v]; v = parent[head[v]]) {
        if (depth[head[u]] > depth[head[v]]) swap(u, v);
        // update(pos[head[v]], pos[v], val);
    }
    if (depth[u] > depth[v]) swap(u, v);
    // update(pos[u], pos[v], val);
}
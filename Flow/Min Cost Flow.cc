struct MCMF {
    struct Edge {
        int to, next;
        ll cap, cost;
        Edge() {}
        Edge(int to, int next, ll cap, ll cost)
            : to(to), cap(cap), cost(cost), next(next) {}
    };
    vector<Edge> edge;
    vector<ll> rec, head, pre, dis, vis;
    int source, sink, nNode;
    MCMF() {}
    MCMF(int n) {
        edge.clear();
        rec.assign(n, -1);
        pre.assign(n, -1);
        head.assign(n, -1);
        nNode = n;
    }
    void addEdge(int u, int v, int cap, int cost) {
        // error(u,v,cap,cost);
        edge.eb(v, head[u], cap, cost);
        head[u] = edge.size() - 1;
        edge.eb(u, head[v], 0, -cost);
        head[v] = edge.size() - 1;
    }
    bool spfa() {
        queue<int> q({source});
        dis.assign(nNode, INF);
        vis.assign(nNode, false);
        dis[source] = 0;
        vis[source] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            vis[u] = false;
            // D(u);
            for (int i = head[u]; ~i; i = edge[i].next) {
                int v = edge[i].to;
                if (edge[i].cap > 0 && dis[v] > max(dis[u], edge[i].cost)) {
                    dis[v] = max(dis[u], edge[i].cost);
                    rec[v] = i;
                    pre[v] = u;
                    if (!vis[v]) {
                        // D(v);
                        vis[v] = true;
                        q.push(v);
                    }
                }
            }
        }

        return dis[sink] != INF;
    }
    pll mcmf(ll K = LL_INF) {
        ll flow = 0, cost = 0;
        while (flow < K && spfa()) {
            ll minFlow = K - flow;
            int cur = sink;
            while (cur != source) {
                minFlow = min(minFlow, edge[rec[cur]].cap);
                cost = max(cost, edge[rec[cur]].cost);
                cur = pre[cur];
            }
            flow += minFlow;
            cur = sink;
            while (cur != source) {
                cost = max(cost, edge[rec[cur]].cost);
                edge[rec[cur]].cap -= minFlow;
                edge[rec[cur] ^ 1].cap += minFlow;
                cur = pre[cur];
            }
        }
        return {flow, cost};
    }
};
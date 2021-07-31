struct ahoCorasick {
    vector<int> link, endCnt, finLink, occ, bfsOrder;
    vector<vector<int>> child, endList, adj;
    const int MXCHR = 26;
    int N = 0, P = 0;  // N - number of nodes, P - number of patterns
    int node() {
        link.emplace_back(0);          // suffix/fail link
        child.emplace_back(MXCHR, 0);  // trie childs
        endList.emplace_back(0);       // patterns that end here
        endCnt.emplace_back(0);   // how many time this node is matched in text
        finLink.emplace_back(0);  // fail link with completed pattern
        adj.emplace_back(0);      // tree with suffix link
        return N++;
    }
    ahoCorasick() : N(0), P(0) { node(); }

    inline int getID(char c)  // change with problem requirement
    {
        return c - 'a';
    }
    void add(string &str) {
        int u = 0;
        for (char c : str) {
            if (!child[u][getID(c)]) child[u][getID(c)] = node();
            u = child[u][getID(c)];
        }
        endList[u].push_back(P++);
        occ.emplace_back(0);
    }
    void bfs() {
        queue<int> q;
        q.push(0);
        while (q.size()) {
            int u = q.front();
            bfsOrder.push_back(u);
            int p = link[u];
            q.pop();
            adj[p].push_back(u);
            for (int c = 0; c < MXCHR; c++) {
                int v = child[u][c];
                if (!v)
                    child[u][c] = child[p][c];
                else {
                    link[v] = u ? child[p][c] : 0;
                    finLink[v] =
                        endList[link[v]].size() ? link[v] : finLink[link[v]];
                    q.push(v);
                }
            }
        }
    }
    int push_up() {
        int ttl = 0;
        for (int i = bfsOrder.size() - 1; i >= 0; i--) {
            int u = bfsOrder[i];
            endCnt[link[u]] += endCnt[u];
            for (auto v : endList[u]) {
                occ[v] += endCnt[u];
            }
            ttl += endList[u].size() * endCnt[u];
        }
        return ttl;
    }
    int match_text(string &str) {
        int cur = 0;
        for (char c : str) {
            cur = child[cur][getID(c)];
            endCnt[cur]++;
        }  // Iterate through the whole text and find all matchings
        int totalOcc = push_up();
        return totalOcc;
    }
};
/*
-> take object.
-> add string using add().
-> call bfs()
-> call match to find all matching.
*/

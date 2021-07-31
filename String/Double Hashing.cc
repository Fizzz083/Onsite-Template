const int base1 = 31, base2 = 53;
const int mod1 = 1000000007, mod2 = 1000000009;
ll poly1[mx];
ll poly2[mx];
pll pref[mx];
void init_hash() {
    poly1[0] = poly2[0] = 1;
    for (int i = 1; i < mx; i++) {
        poly1[i] = (poly1[i - 1] * base1) % mod1;
        poly2[i] = (poly2[i - 1] * base2) % mod2;
    }
}
void make_hash(string &str) {
    int n = str.size();
    for (int i = 0; i < n; i++) {
        int d = str[i] - 'a' + 1;
        pref[i + 1].ff = (d + pref[i].ff * base1) % mod1;
        pref[i + 1].ss = (d + pref[i].ss * base2) % mod2;
    }
}
pll sub_hash(int l, int r) {
    int len = r - l + 1;
    pll ans;
    ans.ff =
        (pref[l + len].ff - (pref[l].ff * poly1[len] % mod1) + mod1) % mod1;
    ans.ss =
        (pref[l + len].ss - (pref[l].ss * poly2[len] % mod2) + mod2) % mod2;
    return ans;
}

int lcp(int id1, int id2, int l) {
    int lo = 1, hi = l;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (sub_hash(id1, id1 + mid) == sub_hash(id2, id2 + mid))
            lo = mid + 1;
        else
            hi = mid - 1;
    }
    return hi;
}

int lcp[N], SA[N], c[N], tc[N], tSA[N], lg2[N];
int dp[25][N];
string str;
int n;
void countSort(int n) {
    vector<int> cnt(n);
    for (int i = 0; i < n; i++)
        cnt[c[i]]++;  /// count how many time each value occurs in c.
    for (int i = 1; i < n; i++) cnt[i] += cnt[i - 1];
    for (int i = n - 1; ~i; i--)
        tSA[--cnt[c[SA[i]]]] = SA[i];  /// maintain stable sort
    for (int i = 0; i < n; i++) SA[i] = tSA[i];
}
void SuffixArray(string &s) {
    str = s + '$';
    n = str.size();
    const int alpha = 256;  // initial sorting with single character
    vector<int> cnt(max(alpha, n), 0);
    for (int i = 0; i < n; i++) cnt[str[i]]++;
    for (int i = 1; i < alpha; i++) cnt[i] += cnt[i - 1];
    for (int i = n - 1; ~i; i--) SA[--cnt[str[i]]] = i;
    c[SA[0]] = 0;
    int ec = 0;  /// equivalent class value
    for (int i = 1; i < n; i++) {
        if (str[SA[i]] != str[SA[i - 1]]) ec++;
        c[SA[i]] = ec;
    }
    for (int k = 0; (1 << k) < n; k++) {
        for (int i = 0; i < n; i++) SA[i] = (SA[i] - (1 << k) + n) % n;
        countSort(n);  // sorting using first element
        tc[SA[0]] = ec = 0;
        for (int i = 1; i < n; i++) {
            pii now = {c[SA[i]], c[(SA[i] + (1 << k)) % n]};
            pii prev = {c[SA[i - 1]], c[(SA[i - 1] + (1 << k)) % n]};
            if (now != prev) ec++;
            tc[SA[i]] = ec;
        }
        for (int i = 0; i < n; i++)  // assigning new equivalent class
            c[i] = tc[i];
        if (c[SA[n - 1]] == n - 1) break;
    }
}  // lcp[i] = lcp(i,i+1)
void LCP() {
    for (int i = 0, k = 0, n = str.size(); i < n - 1; i++) {
        int pi = c[i];  /// c[i] position of suffix i in p
        if (pi == n - 1) {
            k = 0;  // c contains inverse permutation of p
            continue;
        }
        int j = SA[pi + 1];  // pi-1 then lcp[i] = lcp(i,i-1)
        while (str[i + k] == str[j + k]) k++;
        lcp[pi] = k;  // concatenation problem occurs when $ is used
        if (k) k--;
    }
}
void initRMQ() {
    for (int i = 0; i <= n; i++) dp[0][i] = lcp[i];
    for (int j = 1; (1 << j) <= n; j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
            dp[j][i] = min(dp[j - 1][i], dp[j - 1][i + (1 << (j - 1))]);
    for (int i = 2; i <= n; i++) lg2[i] = lg2[i / 2] + 1;
}
int askRMQ(int l, int r) {
    int j = lg2[r - l + 1];
    return min(dp[j][l], dp[j][r - (1 << j) + 1]);
}

int askLCP(int i, int j) {  // suffix starting index.not SA index.
    if (i == j) {
        return n - i;
    }
    int l = c[i];
    int r = c[j];

    if (l > r) swap(l, r);
    return askRMQ(l, r - 1);
}
int L(int val, int idx) {  // finds minimum index l such lcp(l,idx)>=val
    int r = idx - 1, l = 1, ans = -1;
    while (l <= r) {
        int mid = (l + r) / 2;
        int v = askRMQ(mid, idx - 1);
        if (v >= val) {
            r = mid - 1;
            ans = mid;
        } else
            l = mid + 1;
    }
    return ans == -1 ? idx : ans;
}
int R(int val, int idx) {  // finds maximum index r such lcp(idx,r)>=val
    int l = idx, r = n - 1, ans = -1;
    while (l <= r) {
        int mid = (l + r) / 2;
        int v = askRMQ(idx, mid);
        if (v >= val) {
            l = mid + 1;
            ans = mid + 1;
        } else
            r = mid - 1;
    }
    return ans == -1 ? idx : ans;
}

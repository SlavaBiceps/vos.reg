решение взять с сайта вош

#include <bits/stdc++.h>

#ifndef LOCAL
#define cerr dolor_sit_amet
#endif

#define mp make_pair
#define sz(x) ((int)((x).size()))
#define X first
#define Y second
#define all(x) (x).begin(), (x).end()

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair < int , int > ipair;
typedef pair < ll , ll > lpair;
const int IINF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;
const double DINF = numeric_limits<double>::infinity();
const int MOD = 1000000007;
const double EPS = 1e-9;
const double PI = acos(-1.0);
const int DX[] = { 1,  0, -1,  0,  1, -1,  1, -1};
const int DY[] = { 0,  1,  0, -1,  1, -1, -1,  1};
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll sqr(ll x) { return x*x; } ll sqr(int x) { return (ll)x*x; }
double sqr(double x) { return x*x; } ld sqr(ld x) { return x*x; }
mt19937 mmtw(960172);
ll rnd(ll x, ll y) { static uniform_int_distribution<ll> d; return d(mmtw) % (y - x + 1) + x; }

// ========================================================================= //

namespace flow {
    struct Edge {
        int nv, f, c;
    };
    vector<Edge> edges;
    vector<vector<int>> e;
    vector<int> dist;
    vector<int> pos;

    void init(int n) {
        e.resize(n);
        dist.resize(n);
        pos.resize(n);
    }

    void addEdge(int v1, int v2, int c) {
        e[v1].push_back(sz(edges));
        edges.push_back({v2, 0, c});
        e[v2].push_back(sz(edges));
        edges.push_back({v1, 0, 0});
    }

    int dfs(int v, int t, int scale, int cur) {
        if (v == t)
            return cur;
        while (pos[v] != sz(e[v])) {
            int ei = e[v][pos[v]];
            Edge &ce = edges[ei];
            int nv = ce.nv;
            int cf = ce.c - ce.f;
            if (dist[nv] - dist[v] != 1 || cf < scale) {
                ++pos[v];
                continue;
            }
            int nf = dfs(nv, t, scale, min(cur, cf));
            if (nf == 0) {
                ++pos[v];
                continue;
            }
            ce.f += nf;
            edges[ei ^ 1].f -= nf;
            return nf;
        }
        return 0;
    }

    bool bfs(int s, int t, int scale) {
        static vector<int> q;
        q.clear();
        q.push_back(s);
        memset(dist.data(), 0x3f, sizeof(int) * sz(dist));
        dist[s] = 0;
        for (int i = 0; i < sz(q); ++i) {
            int v = q[i];
            int cd = dist[v];
            for (int ei : e[v]) {
                Edge const& ce = edges[ei];
                int cf = ce.c - ce.f;
                int nv = ce.nv;
                if (cf < scale || dist[nv] != IINF)
                    continue;
                dist[nv] = cd + 1;
                if (nv == t)
                    return true;
                q.push_back(nv);
            }
        }
        return false;
    }

    int maxflowScale(int s, int t, int scale) {
        int ans = 0;
        while (bfs(s, t, scale)) {
            while (true) {
                memset(pos.data(), 0, sizeof(int) * sz(pos));
                int f = dfs(s, t, scale, IINF);
                if (f == 0)
                    break;
                ans += f;
            }
        }
        return ans;
    }

    int maxflow(int s, int t) {
        int ans = 0;
        for (int scale = 1 << 30; scale > 0; scale >>= 1)
            ans += maxflowScale(s, t, scale);
        return ans;
    }
}

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    n /= 2;
    vector<vector<int>> a(n*2, vector<int>(k));
    vector<vector<int>> coords(k, vector<int>(n*2));
    for (int i = 0; i < n*2; ++i) {
        for (int j = 0; j < k; ++j) {
            scanf("%d", &a[i][j]);
            coords[j][i] = a[i][j];
        }
    }
    vector<int> mid(k);
    for (int i = 0; i < k; ++i) {
        vector<int> &c = coords[i];
        nth_element(c.begin(), c.begin() + n, c.end());
        nth_element(c.begin(), c.begin() + n - 1, c.begin() + n);
        mid[i] = c[n - 1] + c[n];
    }

    vector<int> p3(k + 1);
    p3[0] = 1;
    for (int i = 1; i <= k; ++i)
        p3[i] = p3[i - 1] * 3;

    vector<vector<int>> buckets(p3[k]);
    for (int i = 0; i < n*2; ++i) {
        int b = 0;
        for (int j = 0; j < k; ++j) {
            int x;
            if (a[i][j] * 2 < mid[j])
                x = 0;
            else if (a[i][j] * 2 > mid[j])
                x = 2;
            else
                x = 1;
            b += x * p3[j];
        }
        buckets[b].push_back(i);
    }

    flow::init(p3[k] + 2);
    int vs = p3[k];
    int vt = p3[k] + 1;

    for (int i = 0; i < p3[k]; ++i) {
        int ci = i;
        int c0 = ci % 3;
        if (c0 == 1) {
            assert(buckets[i].empty());
            continue;
        }
        ci /= 3;
        bool was = false;
        for (int j = 1; j < k; ++j) {
            int x = ci % 3;
            ci /= 3;
            if (x == 1) {
                was = true;
                if (c0 == 0) {
                    flow::addEdge(i, i - p3[j], n);
                    flow::addEdge(i, i + p3[j], n);
                } else {
                    flow::addEdge(i - p3[j], i, n);
                    flow::addEdge(i + p3[j], i, n);
                }
                break;
            }
        }
        if (!was && c0 == 0)
            flow::addEdge(i, p3[k] - 1 - i, n);
        if (c0 == 0)
            flow::addEdge(vs, i, sz(buckets[i]));
        else
            flow::addEdge(i, vt, sz(buckets[i]));
    }

    if (flow::maxflow(vs, vt) != n) {
        printf("NO\n");
        return 0;
    }
    printf("YES\n");
    for (int iter = 0; iter < n; ++iter) {
        int v = vs;
        int v1 = -1, v2 = -1;
        while (v != vt) {
            if (v1 == -1 && v != vs)
                v1 = v;
            v2 = v;
            bool was = false;
            for (int ei : flow::e[v]) {
                flow::Edge &ce = flow::edges[ei];
                if (ce.f > 0) {
                    was = true;
                    --ce.f;
                    ++flow::edges[ei ^ 1].f;
                    v = ce.nv;
                    break;
                }
            }
            assert(was);
        }
        assert(!buckets[v1].empty());
        assert(!buckets[v2].empty());
        printf("%d %d\n", buckets[v1].back() + 1, buckets[v2].back() + 1);
        buckets[v1].pop_back();
        buckets[v2].pop_back();
    }

    return 0;
}


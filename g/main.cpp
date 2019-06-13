Решение взято с сайта вош

#ifdef LOCAL
#  define _GLIBCXX_DEBUG
#else
#  define cerr __get_ce
#endif
#include <bits/stdc++.h>
#define ff first
#define ss second
#define szof(x) ((int)x.size())

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
int const INF = (int)1e9 + 1e3;
ll const INFL = (ll)1e18 + 1e6;
mt19937 tw(9450189);
uniform_int_distribution<ll> ll_distr;
ll rnd(ll a, ll b) { return ll_distr(tw) % (b - a + 1) + a; }


void solve() {
    int n;
    cin >> n;
    vector<vector<int>> graph(n);
    vector<pii> edges;
    for (int i = 0; i < n; ++i) {
        int ind;
        cin >> ind;
        if (ind != -1) {
            --ind;
            int a = i;
            int b = ind;
            if (a > b) {
                swap(a, b);
            }
            edges.push_back({a, b});
        }
    }

    sort(edges.begin(), edges.end());
    edges.erase(unique(edges.begin(), edges.end()), edges.end());

    for (pii e : edges) {
        graph[e.ff].push_back(e.ss);
        graph[e.ss].push_back(e.ff);
    }

    vector<int> st, cycle;
    vector<int> used(n);

    function<bool(int, int)> find_cycle = [&](int v, int p) {
        st.push_back(v);
        used[v] = 1;
        for (int to : graph[v]) {
            if (!used[to]) {
                if (find_cycle(to, v)) {
                    return true;
                }
            } else if (used[to] == 1 && to != p) {
                while (st.back() != to) {
                    cycle.push_back(st.back());
                    st.pop_back();
                }
                cycle.push_back(st.back());
                return true;
            }
        }
        used[v] = 2;
        st.pop_back();
        return false;
    };

    function<pii(int, int)> dfs = [&](int v, int p) {
        pii ret = {0, 1};
        for (int to : graph[v]) {
            if (used[to] != 3 && to != p) {
                pii tmp = dfs(to, v);
                ret.ff += max(tmp.ff, tmp.ss);
                ret.ss += tmp.ff;
            }
        }
        // cerr << v << " " << ret.ff << " " << ret.ss << endl;
        return ret;
    };

    function<void(int)> mark = [&](int v) {
        used[v] = 4;
        for (int to : graph[v]) {
            if (used[to] != 4) {
                mark(to);
            }
        }
    };

    int ans = 0;

    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            cycle.clear();
            st.clear();
            find_cycle(i, i);
            if (szof(cycle)) {
                for (int v : cycle) {
                    used[v] = 3;
                }

                vector<pii> arr;
                for (int v : cycle) {
                    arr.push_back(dfs(v, v));
                    // cerr << arr.back().ff << " " << arr.back().ss << endl;
                }

                pair<pii, pii> d = {{arr[0].ff, arr[0].ff}, {arr[0].ff, arr[0].ss}};

                for (int j = 1; j < szof(arr); ++j) {
                    pair<pii, pii> next = {{0, 0}, {0, 0}};
                    next.ff.ff = max(d.ff.ff, d.ff.ss) + arr[j].ff;
                    next.ff.ss = max(max(arr[j].ff, arr[j].ss) + d.ff.ff, next.ff.ff);
                    next.ss.ff = max(d.ss.ff, d.ss.ss) + arr[j].ff;
                    next.ss.ss = max(max(arr[j].ff, arr[j].ss) + d.ss.ff, next.ss.ff);
                    swap(next, d);
                    // cerr << d.ff.ff << " " << d.ff.ss << " " << d.ss.ff << " " << d.ss.ss << endl;
                }

                ans += max(max(d.ff.ss, d.ff.ff), d.ss.ff);
            } else {
                auto tmp = dfs(i, i);
                // cerr << tmp.ff << " " << tmp.ss << endl;
                ans += max(tmp.ff, tmp.ss);
            }

            mark(i);
        }
    }

    cout << ans << "\n";
}


int main() {
#ifdef LOCAL
    auto start_time = clock();
	cerr << setprecision(3) << fixed;
#endif
    cout << setprecision(15) << fixed;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_count = 1;
    // cin >> test_count;
    for (int test = 1; test <= test_count; ++test) {
        solve();
    }

#ifdef LOCAL
    auto end_time = clock();
	cerr << "Execution time: " << (end_time - start_time) * (int)1e3 / CLOCKS_PER_SEC << " ms\n";
#endif
}

/* What's the difference between a baby boomer and a matter baby? */
#include <bits/stdc++.h>

#define TEXT ""

using namespace std;

#define pb push_back
#define mkpr make_pair
#define eb emplace_back
#define endl "\n"
#define ffor(i, a, b) for(int i = a; i <= (b); ++i)
#define rfor(i, a, b) for(int i = a; i >= (b); --i)
#define frep(i, a, b) for(int i = a; i < (b); ++i)
#define rrep(i, a, b) for(int i = a; i > (b); --i)
#define feach(x, a) for (auto& x : (a))
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second

typedef int int2;
#define int long long

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll,ll> pll;
typedef pair<double,double> pdd;

mt19937_64 rd(chrono::high_resolution_clock::now().time_since_epoch().count());

void prans(bool answer = true) { cout << (answer ? "YES\n" : "NO\n"); }
void prno() { cout << "NO\n"; }
void pryes() { cout << "YES\n"; }

template<class T, class U> bool minimize(T& a, const U& b) { return b < a ? (a = b, true) : false; }
template<class T, class U> bool maximize(T& a, const U& b) { return a < b ? (a = b, true) : false; }

namespace dbg_ {
    template<class> inline constexpr bool always_false_v = false;

    template<class T, class = void> struct streamable_ : std::false_type {};
    template<class T> struct streamable_<T, std::void_t<decltype(std::declval<std::ostream&>() << std::declval<const T&>())>> : std::true_type {};

    template<class T> struct is_pair_ : std::false_type {};
    template<class A, class B> struct is_pair_<std::pair<A, B>> : std::true_type {};

    template<class T, class = void> struct iterable_ : std::false_type {};
    template<class T> struct iterable_<T, std::void_t<decltype(std::begin(std::declval<const T&>())), decltype(std::end(std::declval<const T&>()))>> : std::true_type {};

    template<class T, class = void> struct derefable_ : std::false_type {};
    template<class T> struct derefable_<T, std::void_t<decltype(*std::declval<const T&>()), decltype(++std::declval<T&>())>> : std::true_type {};

    // types that consume the NEXT argument as their end: raw pointers (except char*) and iterators
    template<class T> inline constexpr bool wants_end_v =
        (std::is_pointer_v<T> && !std::is_same_v<std::remove_cv_t<std::remove_pointer_t<T>>, char>) ||
        (derefable_<T>::value && !streamable_<T>::value && !iterable_<T>::value);

    template<class T> void pr(const T& x);

    template<class A, class B> void pr_rng(A f, B l) {
        std::cerr << '[';
        bool sep = false;
        for (A it = f; it != l; ++it) { if (sep) std::cerr << ", "; sep = true; pr(*it); }
        std::cerr << ']';
    }

    template<class T> void pr(const T& x) {
        if constexpr (is_pair_<T>::value) { std::cerr << '('; pr(x.first); std::cerr << ", "; pr(x.second); std::cerr << ')'; }
        else if constexpr (std::is_array_v<T> && !std::is_same_v<std::remove_extent_t<T>, char>) pr_rng(std::begin(x), std::end(x));
        else if constexpr (streamable_<T>::value) std::cerr << x;
        else if constexpr (iterable_<T>::value) pr_rng(std::begin(x), std::end(x));
        else static_assert(always_false_v<T>, "dbg: type is not printable");
    }

    inline void go() { std::cerr << '\n'; }
    template<class T, class... R> void go(const T& x, const R&... r);

    template<class P, class Q, class... R> void go_rng(const P& f, const Q& l, const R&... r) {
        static_assert(wants_end_v<Q>, "dbg: a pointer/iterator must be followed by the matching end pointer/iterator");
        pr_rng(f, l);
        if constexpr (sizeof...(R)) std::cerr << ' ';
        go(r...);
    }

    template<class T, class... R> void go(const T& x, const R&... r) {
        if constexpr (std::is_array_v<T>) go(+x, r...);              // decay arrays to pointers
        else if constexpr (wants_end_v<T>) {
            static_assert(sizeof...(R) >= 1, "dbg: a pointer/iterator must be followed by the matching end pointer/iterator");
            if constexpr (sizeof...(R) >= 1) go_rng(x, r...);
        } else {
            pr(x);
            if constexpr (sizeof...(R)) std::cerr << ' ';
            go(r...);
        }
    }
} // namespace dbg_

template<class... Args> void dbg(const Args&... args) { dbg_::go(args...); }
#define dbgl(...) (std::cerr << "[" #__VA_ARGS__ "] = ", dbg(__VA_ARGS__))

// Constants
const int N = 2e5+10;
const int INF = 1e9+7;
const int LG = 63;
const int MD = 1e9+7; //998244353;
const long long LLINF = 1e18+3;

const bool MULTI_TEST = true;

//Starts here

int n,m;
int a[N], b[N];
int w[N], val[N];
vector<int> adj[N];

int dp[LG+1][N];

int iceil(int x, int d) {
    return (x-1)/d+1; 
}

void dfs(int u, int p) {
    priority_queue<pii> pq;
    dp[0][u] = val[u];
    vector<int> child;
    vector<int> ptr;
    for (auto v:adj[u]) {
        if (v==p) continue;
        dfs(v,u);
        child.push_back(v);
        ptr.push_back(0);
        dp[0][u] = max(dp[0][u], dp[0][v]);
        pq.push({dp[0][v], child.size()-1});
    }

    if (child.size() == 0) {
        for (int i=1; i<=LG; i++){
            dp[i][u] = iceil(dp[i-1][u],w[u]);
        }
        return;
    }

    for (int i=1; i<=LG; i++) {
        dp[i][u] = iceil(dp[i-1][u],w[u]);
        auto [x,idx] = pq.top(); pq.pop();
        ++ptr[idx]; pq.push({dp[ptr[idx]][child[idx]], idx});
        dp[i][u] = min(dp[i][u],max(val[u], pq.top().fi));
    }
 }

void solve(){
    cin >> n;
    m = 0;
    for (int i=1; i<=n; i++){
        adj[i].clear();
    }
    ffor (i,1,n) {
        cin >> a[i];
        val[i] = 0;
    }
    int mn = LLINF;
    ffor(i,1,n) {
        cin >> b[i];
        mn = min(mn,b[i]);
    }
    deque<pair<int,int>> dq;
    dq.push_back({0,1});
    vector<pii> child;

    for (int i=1; i<=n; i++){
        child.clear();
        while (!dq.empty() && dq.back().se > b[i]) {
            child.push_back(dq.back());
            dq.pop_back();
        }
        int idx;
        if (dq.back().se != b[i]) {
            ++m;
            w[m] = b[i];
            idx = m;
            dq.push_back({idx,b[i]});
        }
        else {
            idx = dq.back().fi;
        }
        val[idx] = max(val[idx],a[i]);
        for (int x = 0; x < child.size(); x++) {
            if (x == child.size()-1) {
                adj[idx].push_back(child[x].fi);
                adj[child[x].fi].push_back(idx);
            }
            else {
                adj[child[x+1].fi].push_back(child[x].fi);
                adj[child[x].fi].push_back(child[x+1].fi);
            }
        }
        // dbg(m);
        // ffor(i,1,m) {
        //     dbg(all(adj[i]));
        // }
        // for (int i = 1; i < dq.size(); i++){
        //     cerr << dq[i].fi << " ";
        // }
        // cerr << endl;
    }
    int root;

    // cerr << "meow" << endl;
    // dbg(w+1,w+1+m);
    // dbg(val+1,val+1+m);
    // ffor(i,1,m) {
    //     dbg(all(adj[i]));
    // }
    
    while (dq.size()!=1) {
        pii item = dq.back(); dq.pop_back();
        if (dq.size()!=1) {
            adj[dq.back().fi].push_back(item.fi);
            adj[item.fi].push_back(dq.back().fi);
        } else {
            root = item.fi;
        }
    }

    int ans = LG+1;
    dfs(root,0);
    for (int i = LG; i>=0; i--) {
        if (dp[i][root] == 1) {
            ans = min(ans,i);
        }
    }
    cout << ans << endl;
}

/* Cat memes */
signed main(){
    cin.tie(0) -> sync_with_stdio(0);
    if (fopen(TEXT".inp","r")){ freopen(TEXT".inp","r",stdin); freopen(TEXT".out","w",stdout); }

    int test_count = 1;
    
    if (MULTI_TEST) cin >> test_count;
    while (test_count--){ solve(); }

    return 0;
}


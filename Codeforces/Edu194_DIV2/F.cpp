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
const int N = 3000+20;
const int INF = 1e9+7;
const int MD = 1e9+7; //998244353;
const long long LLINF = 1e18+3;

const bool MULTI_TEST = true;

//Starts here

int n,m,k;
vector<pii> adj[N],adj3[N];
vector<pair<pii,int>> back_edges;
vector<pii> edges;
int num[N],low[N];
int timedfs = 0;

void DFS(int u, int p) {
    num[u] = low[u] = ++timedfs;
    for (auto [v,idx]:adj[u]) {
        if (v==p) continue;
        if (!num[v]) {
            adj3[u].push_back({v,idx});
            adj3[v].push_back({u,idx});
            DFS(v,u);
            low[u] = min(low[u],low[v]);
        }
        else if (num[u] > num[v]){
            low[u] = min(low[u],num[v]);
            back_edges.push_back({{u,v},idx});
        }
    }   
}

int pref[N];
vector<pii> adj2[N];
int vis[N];
int marked[N];

void DFSconstruct(int u, int p, int eid) {
    for (auto [v,idx]:adj3[u]) {
        if (v==p) continue;
        DFSconstruct(v,u,idx);
        pref[u] += pref[v];
    }
    if (pref[u]%2==1) {
        marked[eid] = 1;
    }
}

void DFSconnected(int u, int p) {
    vis[u] = true;
    for (auto [v,idx]:adj2[u]) {
        if (!vis[v]) DFSconnected(v,u);
    }
}

bool check(int mask) {
    // dbg(mask);
    ffor(i,1,n) {
        pref[i] = 0;
        vis[i] = 0;
        adj2[i].clear();
    }
    ffor(i,0,m) {
        marked[i] = 0;
    }

    frep(i,0,k) {
        if (mask&(1<<i)) {
            marked[back_edges[i].se] = 1;
            if (num[back_edges[i].fi.fi] > num[back_edges[i].fi.se]) swap(back_edges[i].fi.fi, back_edges[i].fi.se);
            pref[back_edges[i].fi.se]++;
            pref[back_edges[i].fi.fi]--;
        }
    }

    // dbg("dfsconst");
    // dbg(pref+1,pref+1+n);
    DFSconstruct(1,0,-1);
    frep(i,0,m) {
        if (!marked[i]) {
            adj2[edges[i].se].push_back({edges[i].fi,i});
            adj2[edges[i].fi].push_back({edges[i].se,i});
        }
    }
    // ffor(i,1,n) {
    //     dbg(adj2[i]);
    // }
    // dbg("dfscon");
    DFSconnected(1,0);
    // dbg(pref+1,pref+1+n);
    // dbg(vis+1,vis+1+n);
    ffor(i,1,n) {
        if (!vis[i]) return false;
    }
    return true;
}


void solve(){
    cin >> n >> m;
    back_edges.clear();
    edges.clear();
    timedfs = 0;
    ffor(i,1,n) {
        adj[i].clear();
        adj3[i].clear();
        num[i] = low[i] = 0;
    }
    ffor(i,1,m) {
        int u,v; cin >> u >> v;
        adj[u].push_back({v,edges.size()});
        adj[v].push_back({u,edges.size()});
        edges.push_back({u,v});
    }
    DFS(1,0);
    k = back_edges.size();

    // dbg(back_edges);
    // dbg(num+1,num+1+n);
    // dbg(low+1,low+1+n);
    // ffor(i,1,n) {
    //     dbg(adj3[i]);
    // }


    frep(mask,1,(1<<k)) {
        if (check(mask)) {
            cout << "YES" << endl;
            return;
        }
    }
    cout << "NO" << endl;
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


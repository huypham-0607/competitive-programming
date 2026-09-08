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
const int N = 1e5+10;
const int M = 5e6;
const int INF = 1e9+7;
const int MD = 1e9+7; //998244353;
const long long LLINF = 1e18+3;

const bool MULTI_TEST = false;

//Starts here

int n;
signed phi[M+10];

vector<signed> adj[M+10];

void sieve() {
    for (int i = 1; i <= M; i++) { phi[i] = i; }
	for (int i = 2; i <= M; i++) {
		// If i is prime
		if (phi[i] == i) {
			for (int j = i; j <= M; j += i) { phi[j] -= phi[j] / i; }
		}
        adj[phi[i]].push_back(i);
	}
}


const int LG_LCA = 10;

signed up[LG_LCA][M];
int depth[M+10];

void dfsLCA(int u, int p=0){
    // dbg(u);
    depth[u] = depth[p]+1;
    up[0][u] = p;
    for (int lg=1; lg<LG_LCA; lg++){
        int v = up[lg-1][u];
        up[lg][u] = up[lg-1][v];
    }
    for (auto v:adj[u]){
        if (v==p) continue;
        dfsLCA(v,u);
    }
}

int binLift(int u, int x){
    for (int lg=0; lg<LG_LCA; lg++){
        if ((1<<lg)&x) u = up[lg][u];
    }
    return u;
}

int getLCA(int u, int v){
    if (depth[u]>depth[v]) swap(u,v);
    v = binLift(v,depth[v]-depth[u]);
    if (u==v) return u;
    for (int lg=LG_LCA-1; lg>=0; lg--){
        if (up[lg][u]!=up[lg][v]){
            u = up[lg][u];
            v = up[lg][v];
        }
    }
    return up[0][u];
}

struct LazySegmentTree1{
    struct Node{
        int lca, min_depth;
        Node(){
            lca = 1;
            min_depth = 0;
        }
    };

    int n;
    vector<Node> IT;
    vector<int> lazy;

    void apply(int idx, int val) {
        IT[idx].min_depth = max(0LL,IT[idx].min_depth - val);
        if (depth[IT[idx].lca] > IT[idx].min_depth) {
            IT[idx].lca = binLift(IT[idx].lca, depth[IT[idx].lca] - IT[idx].min_depth);
        }
        lazy[idx] += val;
    }

    void propagate(int idx){
        if (lazy[idx]) {
            int val = lazy[idx];
            apply(idx*2, val);
            apply(idx*2+1, val);
        }
        lazy[idx] = 0;
    }

    void comb(Node& i, Node& l, Node& r){
        i.lca = getLCA(l.lca, r.lca);
        i.min_depth = min(l.min_depth, r.min_depth);
    }

    void init(int _n, int a[]) {
        n = _n;
        IT.resize(n*4+10, Node());
        lazy.resize(n*4+10, 0);
        build(1,1,n,a);
    }

    void build(int idx, int l, int r, int a[]){
        if (l==r){
            IT[idx].min_depth = depth[a[l]];
            IT[idx].lca = a[l];
            return;
        }

        int mid = (l+r)/2;
        build(idx*2,l,mid,a);
        build(idx*2+1,mid+1,r,a);
        comb(IT[idx],IT[idx*2],IT[idx*2+1]);
    }

    void update(int idx, int l, int r, int x, int y, int val){
        if (y < l || r < x) return;
        if (x <= l && r <= y){
            apply(idx,val);
            return;
        }

        propagate(idx);

        int mid = (l+r)/2;
        update(idx*2,l,mid,x,y,val);
        update(idx*2+1,mid+1,r,x,y,val);
        comb(IT[idx],IT[idx*2],IT[idx*2+1]);
    }

    int resolve(int u, int v) {
        if (u==0) return v;
        if (v==0) return u;
        return getLCA(u,v);
    }

    int getVal(int idx, int l, int r, int x, int y){
        if (y < l || r < x) return 0;
        if (x <= l && r <= y){
            return IT[idx].lca;
        }

        propagate(idx);

        int mid = (l+r)/2;
        return resolve(getVal(idx*2,l,mid,x,y),getVal(idx*2+1,mid+1,r,x,y));
    }
} IT;

struct LazySegmentTree2{
    struct Node{
        int sum, min_depth, valid_count;
        Node(){
            sum = 0;
            min_depth = INF;
            valid_count = 0;
        }
    };

    int n;
    vector<Node> IT;
    vector<int> lazy;

    void apply(int idx, int val) {
        IT[idx].min_depth -= val;
        IT[idx].sum -= IT[idx].valid_count * val;
        lazy[idx] += val;
    }

    void propagate(int idx){
        if (lazy[idx]) {
            int val = lazy[idx];
            apply(idx*2, val);
            apply(idx*2+1, val);
        }
        lazy[idx] = 0;
    }

    void comb(Node& i, Node& l, Node& r){
        i.sum = l.sum + r.sum;
        i.min_depth = min(l.min_depth, r.min_depth);
        i.valid_count = l.valid_count + r.valid_count;
    }

    void init(int _n, int a[]) {
        n = _n;
        IT.resize(n*4+10, Node());
        lazy.resize(n*4+10, 0);
        build(1,1,n,a);
    }

    void build(int idx, int l, int r, int a[]){
        if (l==r){
            IT[idx].sum = depth[a[l]];
            IT[idx].valid_count = 1;
            IT[idx].min_depth = depth[a[l]];
            return;
        }

        int mid = (l+r)/2;
        build(idx*2,l,mid,a);
        build(idx*2+1,mid+1,r,a);
        comb(IT[idx],IT[idx*2],IT[idx*2+1]);
    }

    void update(int idx, int l, int r, int x, int y, int val){
        if (y < l || r < x) return;
        if (x <= l && r <= y && IT[idx].min_depth >= val){
            apply(idx,val);
            return;
        }
        if (l==r) {
            IT[idx].valid_count = 0;
            IT[idx].min_depth = INF;
            IT[idx].sum = 0;
            return;
        }

        propagate(idx);

        int mid = (l+r)/2;
        update(idx*2,l,mid,x,y,val);
        update(idx*2+1,mid+1,r,x,y,val);
        comb(IT[idx],IT[idx*2],IT[idx*2+1]);
    }

    int getVal(int idx, int l, int r, int x, int y){
        if (y < l || r < x) return 0;
        if (x <= l && r <= y){
            return IT[idx].sum;
        }

        propagate(idx);

        int mid = (l+r)/2;
        return getVal(idx*2,l,mid,x,y) + getVal(idx*2+1,mid+1,r,x,y);
    }
} IT2;

int q;
int a[N];

void solve(){
    sieve();
    cin >> n >> q;
    ffor(i,1,n) {
        cin >> a[i];
    }
    depth[1] = -1;
    ffor(i,1,20) {
        cerr << phi[i] << " ";
    }
    cerr << endl;
    dfsLCA(1,1);
    IT.init(n,a);
    IT2.init(n,a);
    ffor(i,1,q) {
        int id, u,v; cin >> id >> u >>v;
        if (id == 1) {
            IT.update(1,1,n,u,v,1);
            IT2.update(1,1,n,u,v,1);
        }
        else {
            int lca = IT.getVal(1,1,n,u,v);
            int sum = IT2.getVal(1,1,n,u,v);
            int ans = sum - depth[lca]*(v-u+1);
            cout << ans << endl;
        }
    }
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


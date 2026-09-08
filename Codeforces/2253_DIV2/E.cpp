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
const int N = 1e6+10;
const int INF = 1e9+7;
const int MD = 1e9+7; //998244353;
const long long LLINF = 1e18+3;

const bool MULTI_TEST = true;

//Starts here

int n;
vector<int> adj[N];
int dist[N];
int parent[N];

int BFS(int s) {
    queue<int> q;
    q.push(s);
    ffor(i,1,n) { dist[i] = -1; parent[i] = 0; }
    dist[s] = 0;

    int last = s;

    while (!q.empty()){
        int u = q.front(); q.pop();
        last = u;
        for (auto v:adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u]+1;
                parent[v] = u;
                q.push(v);
            }
        }
    }
    return last;
}

vector<int> adj2[N];

vector<int> lst1,lst2;
int cnt[N];
int depth[N];

void calc(int u, int p, vector<int>& lst, int thresh) {
    int branch = 0;
    depth[u] = depth[p]+1;
    feach(v,adj[u]){
        if (v==p) continue;
        calc(v,u,lst,thresh);
        if (cnt[v]) {
            ++branch;
            cnt[u] += cnt[v];
        }
    }
    if (!branch) {
        if (depth[u] == thresh) {
            lst[depth[u]] = 1;
            cnt[u]++;
        }
    }
    else if (branch > 1) {
        lst[depth[u]] = 1;
    }
}

/**
 * Author: chilli
 * Date: 2019-04-16
 * License: CC0
 * Source: based on KACTL's FFT
 * Description: ntt(a) computes $\hat f(k) = \sum_x a[x] g^{xk}$ for all $k$, where $g=\text{root}^{(mod-1)/N}$.
 * N must be a power of 2.
 * Useful for convolution modulo specific nice primes of the form $2^a b+1$,
 * where the convolution result has size at most $2^a$. For arbitrary modulo, see FFTMod.
   \texttt{conv(a, b) = c}, where $c[x] = \sum a[i]b[x-i]$.
   For manual convolution: NTT the inputs, multiply
   pointwise, divide by n, reverse(start+1, end), NTT back.
 * Inputs must be in [0, mod).
 * Time: O(N \log N)
 * Status: stress-tested
 */

const ll mod = (119 << 23) + 1, root = 62; // = 998244353
#define vi vector<signed>
#define sz(a) size(a)
#define rep(i, a, b) for(int i = a; i < (b); ++i)

ll modpow(ll b, ll e) {
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}

// For p < 2^30 there is also e.g. 5 << 25, 7 << 26, 479 << 21
// and 483 << 21 (same root). The last two are > 10^9.
typedef vector<ll> vl;
void ntt(vl &a) {
	int n = sz(a), L = 31 - __builtin_clz(n);
	static vl rt(2, 1);
	for (static int k = 2, s = 2; k < n; k *= 2, s++) {
		rt.resize(n);
		ll z[] = {1, modpow(root, mod >> s)};
		rep(i,k,2*k) rt[i] = rt[i / 2] * z[i & 1] % mod;
	}
	vi rev(n);
	rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
			ll z = rt[j + k] * a[i + j + k] % mod, &ai = a[i + j];
			a[i + j + k] = ai - z + (z > ai ? mod : 0);
			ai += (ai + z >= mod ? z - mod : z);
		}
}
vl conv(const vl &a, const vl &b) {
	if (a.empty() || b.empty()) return {};
	int s = sz(a) + sz(b) - 1, B = 32 - __builtin_clz(s),
	    n = 1 << B;
	int inv = modpow(n, mod - 2);
	vl L(a), R(b), out(n);
	L.resize(n), R.resize(n);
	ntt(L), ntt(R);
	rep(i,0,n)
		out[-i & (n - 1)] = (ll)L[i] * R[i] % mod * inv % mod;
	ntt(out);
	return {out.begin(), out.begin() + s};
}


void solve(){
    cin >> n;
    ffor(i,1,n){
        adj[i].clear();
        adj2[i].clear();
        cnt[i] = 0;
        depth[i] = 0;
    }
    frep(i,1,n) {
        int u,v; cin >> u >>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int endpoint = BFS(1);
    endpoint = BFS(endpoint);

    int dia = 0;
    ffor(i,1,n) maximize(dia, dist[i]);
    // cerr << dia << endl;
    ffor(i,1,dia/2) endpoint = parent[endpoint];
    pii mid = {endpoint, parent[endpoint]};
    
    // dbg(mid);
    
    ffor(u,1,n){
        feach(v,adj[u]) {
            if ((u==mid.fi && v==mid.se) || (u==mid.se && v==mid.fi)) {}
            else adj2[u].push_back(v);
        }
        swap(adj[u], adj2[u]);
    }

    ffor(i,1,n) {
        // dbgl(adj[i]);
    }

    depth[0] = -1;
    lst1.clear(); lst1.resize(n,0);
    lst2.clear(); lst2.resize(n,0);
    calc(mid.fi, 0, lst1, dia/2);
    calc(mid.se, 0, lst2, dia/2);

    // dbg(cnt+1, cnt+1+n);

    // dbg(lst1);
    // dbg(lst2);

    vector<int> ans = conv(lst1, lst2);

    int total = 0;
    frep(i,0,ans.size()) {if (ans[i]) ++total;}
    cout << total << " ";
    frep(i,0,ans.size()) {
        if (ans[i]) cout << i+1 << " ";
    }
    cout << endl;
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


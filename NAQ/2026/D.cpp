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
#define int unsigned long long

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
const int MD = 1e9+7; //998244353;
const long long LLINF = 1e18+3;

const bool MULTI_TEST = false;

//Starts here

int n;
int k;
pii a[N];

int find_dist(int i, int j) {
    int dx = abs((long long) a[i].fi - (long long) a[j].fi);
    int dy = abs((long long)a[i].se - (long long)a[j].se);

    return dx*dx + dy*dy;
}

pii find(int x) {
    // cerr << "find " << x << endl;
    int l = 1, r = n-1;
    int len = 0;
    int ans = 0;
    while (l<=r) {
        int mid = (l+r)/2;
        int da = find_dist(x, (x+mid)%n);
        int db = find_dist(x, (x+mid-1)%n);
        if (da > db) {
            ans = mid;
            l = mid+1;
        }
        else {
            r = mid-1;
        }
    }
    return make_pair(find_dist(x, (x+ans)%n), ans);
}

pii find2(int x) {
    // cerr << "find " << x << endl;
    int l = 1, r = n-1;
    int len = 0;
    int ans = 0;
    while (l<=r) {
        int mid = (l+r)/2;
        int da = find_dist(x, (x+mid)%n);
        int db = find_dist(x, (x+mid-1)%n);
        if (da >= db) {
            ans = mid;
            l = mid+1;
        }
        else {
            r = mid-1;
        }
    }
    return make_pair(find_dist(x, (x+ans)%n), ans);
}

int find_root(int x) {
    int l = 0, r = 4*INF;
    int ans = 0;
    while (l<=r) {
        int mid = (l+r)/2;
        if (mid*mid <= x) {
            ans = mid;
            l = mid+1;
        }
        else {
            r = mid-1;
        }
    }
    if (ans*ans == x) return ans;
    else return -1;
}

long double get(int k, int mx) {
    ld l = 0;
    ld r = 4*INF;
    long double ans = 0;
    for (int i=1; i<=67; i++){
        ld mid = (l+r)/2;
        if (mid*mid > (k*k)/mx+1) {
            r = mid;
        }
        else if (mx*mid*mid <= k*k) {
            ans = mid;
            l = mid;
        }
        else {
            r = mid;
        }
    }
    return ans;
}

void solve(){
    cin >> n >> k;
    ffor(i,0,n) {
        cin >> a[i].fi >> a[i].se;
    }
    int cnt = 0;
    int mx = 0;
    for (int i =0 ; i<n; i++){
        auto p1 = find(i);
        auto p2 = find2(i);
        int tmp = p1.fi;
        int delta = p2.se - p1.se + 1;
        if (tmp > mx) {
            mx = tmp;
            cnt = delta;
        }
        else if (tmp == mx) {
            cnt += delta;
        }
        // cout << i << " " << mx << " " << cnt << " " << delta << endl;
    }

    cnt/=2;

    // int cut = 4*mx;
    // int mult = k*k/cut;
    // cout << ceil(sqrt<long long>(mult) + ((long double)1e-15)) << endl;

    // cout << mx << " " << cnt << endl;

    // cout << k << endl;

    cout << ceil(get(k,4*mx)) << endl;
    if (k*k%(4*mx) == 0) {
        int cut = 4*mx;
        int mult = k*k/cut;
        // cerr << mult << endl;
        int root = find_root(mult);
        if (root == -1) {
            cout << ceil(get(k,4*mx)) << endl;
        }
        else {
            if (root <= cnt) {
                cout << root << endl;
            }
            else {
                cout << root + 1 << endl;
            }
        }
    }
    else {
        // cerr << mult << endl;
        cout << ceil(get(k,4*mx)) << endl;
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


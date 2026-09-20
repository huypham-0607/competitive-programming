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
const int N = 3000+10;
const int INF = 1e9+7;
const int MD = 998244353;
const long long LLINF = 1e18+3;

const bool MULTI_TEST = true;

namespace Comb {
    using ll = long long;

    const int MD = 998244353;
    const int N = 2e5;
    const int LG = 30;

    int invFac[N+1];
    int fac[N+1];
    int pow2[N+1];

    int binPow(int a, int b){
        ll res = 1;
        for (int lg = LG-1; lg>=0; lg--){
            res = res*res%MD;
            if ((1LL<<lg)&b) res = res*a%MD;
        }
        return res;
    }

    int p2(int b) {
        return pow2[b];
    }

    int invMod(int x, int MD){
        return binPow(x,MD-2);
    }

    int nCk(int n, int k){
        return 1LL*fac[n]*invFac[k]%MD*invFac[n-k]%MD;
    }

    struct Init {
        Init() {
            fac[0] = 1;
            invFac[0] = 1;
            pow2[0] = 1;
            for (int i = 1; i <= N; i++){
                fac[i] = (1LL*fac[i-1]*i%MD);
                invFac[i] = invMod(fac[i],MD);
                pow2[i] = pow2[i-1]*2%MD;
            }
        }
    } _init;
}


int n,m;
vector<int> pd[N];
int a[N];
int val[N];
int pref[N];
int dp[N][N];
vector<int> nen;

const int MXP = 3000;

vector<int> pr;

void Sieve(){
    bitset<MXP+1> bs;
    bs.set();
    bs[0] = bs[1] = 0;
    for (int i=2; i*i<=MXP; i++){
        if (!bs[i]) continue;
        for (int j=i*i; j<=MXP; j+=i){
            bs[j]=0;
        }
    }

    for (int i=1; i<=MXP; i++){
        if (bs[i]) pr.push_back(i);
    }
}

int reduce(int x, int p) {
    while (x%p == 0) {
        x/=p;
    }
    return x;
}

int gidx(int val) {
    return lower_bound(all(nen),val) - nen.begin();
}

void solve(){
    cin >> n;
    nen.clear();
    ffor(i,1,n) {
        cin >> a[i];
        nen.push_back(a[i]);
    }
    nen.push_back(0);
    sort(all(nen));
    nen.resize(unique(all(nen)) - nen.begin());
    m = nen.size()-1;

    // cerr << "passed1" << endl;

    ffor(i,1,n) {
        val[gidx(a[i])]++;
    }

    // cerr << "passed" << endl;

    ffor(i,1,m) {
        pref[i] = pref[i-1] + val[i];
    }

    int ans = 0;

    for (int i=1; i<=m; i++){
        for (int j=1; j<i; j++){
            int delta = pref[i-1] - pref[j];
            ans = (ans + (Comb::p2(val[j])-1+MD)%MD * (Comb::p2(delta))%MD * (Comb::p2(val[i])-1+MD)%MD * dp[nen[i]][nen[j]]%MD)%MD;
            // dbg(i,j,ans);
        }
        ans = (ans + (Comb::p2(val[i])-1+MD)%MD * dp[nen[i]][nen[i]]%MD)%MD;
        // dbg(i,i,ans);
    }
    cout << ans << endl;
    ffor(i,1,n) {
        val[gidx(a[i])]--;
    }
}

/* Cat memes */
signed main(){
    cin.tie(0) -> sync_with_stdio(0);
    if (fopen(TEXT".inp","r")){ freopen(TEXT".inp","r",stdin); freopen(TEXT".out","w",stdout); }

    int test_count = 1;
    
    Sieve();
    ffor(i,1,3000) {
        int x = i;
        for (auto p:pr) {
            if (p > i*i) break;
            if (x%p == 0) {
                pd[i].push_back(p);
                x = reduce(x,p);
            }
        }
        if (x!=1) pd[i].push_back(x);
    }
    // ffor(i,1,4) {
    //     for (auto x:pd[i]) {
    //         cerr << x << " ";
    //     }
    //     cerr << endl;
    // }

    for (int i=1; i<=3000; i++){
        for (int j=1; j<i; j++){
            int tmp = i;
            for (auto p:pd[j]) {
                tmp = reduce(tmp,p);
            }

            // dbg(i,j,tmp);

            if (tmp == 1) dp[i][j] = dp[i-1][j-1];
            else dp[i][j] = dp[i-1][j];

            int delta = pref[i-1] - pref[j];
        }
        dp[i][i] = i;
    }

    // ffor(i,1,4) {
    //     ffor(j,1,4) {
    //         cerr << dp[i][j] << " ";
    //     }
    //     cerr << endl;
    // }
    
    if (MULTI_TEST) cin >> test_count;
    while (test_count--){ solve(); }

    return 0;
}


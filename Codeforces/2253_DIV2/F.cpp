/* What's the difference between a baby boomer and a matter baby? */
#include <bits/stdc++.h>
#include <cstdio>

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
const int N = 5e5+10;
const int INF = 1e9+7;
const int LG2 = 19;
const int LG3 = 12;
const int MD = 1e9+7; //998244353;
const long long LLINF = 1e18+3;

const bool MULTI_TEST = false;

//Starts here
int cache2[LG2];
int cache3[LG3];

int n;
int cost[N];
vector<int> dpprev(1<<LG2,0);
vector<int> dp(1<<LG2,0);

int get_cost(int x) {
    return (x>n) ? 0 : cost[x];
}

bool active(int mask, int i) {
    return (mask&(1<<i));
}

int broken_profile(int x, int p2, int p3) {
    rfor(j, p2-1, 0) {
        frep(mask,0,(1<<p2)) {
            dp[mask] = 0;
        }
    }

    // dbgl(x);
    rfor(i, p3-1, 0) {
        rfor(j, p2-1, 0) {
            swap(dpprev, dp);
            int pos = x * cache2[j] * cache3[i];
            int cst = get_cost(pos);
            frep(mask,0,(1<<p2)) {
                dp[mask] = LLINF;
                if (mask&(1<<j)) {
                    dp[mask] = min(dp[mask], min(dpprev[mask], dpprev[mask^(1<<j)]) + cst);
                }
                else {
                    if ((j >= p2-2) || (active(mask,j+1) || active(mask,j+2))) {
                        dp[mask] = min(dp[mask], dpprev[mask]);
                    }
                    dp[mask] = min(dp[mask], dpprev[mask^(1<<j)]);
                }
            }
            // dbgl(i,j);
            // dbgl(pos, cst);
            // dbg(dp.begin(), dp.begin() + (1<<p2));
        }
    }

    int res = LLINF;
    frep(mask,0,(1<<p2)) {
        res = min(res,dp[mask]);
    }
    return res;
}

void solve(){
    cin >> n;
    ffor(i,1,n) {
        cin >> cost[i];
    }
    int ans = 0;
    ffor(i,1,n/4) {
        if ((i%2) && (i%3)) {
            int x = i;
            // dbgl(x);
            int p2 = 0;
            while (x*2<=n) { p2++; x*=2; }
            x = i;
            int p3 = 0;
            while (x*3<=n) { p3++; x*=3; }

            // dbgl(p2, p3);

            ans += broken_profile(i, p2+1, p3+1);
            // dbgl(ans);
        }
    }
    cout << ans << endl;
}

/* Cat memes */
signed main(){
    cin.tie(0) -> sync_with_stdio(0);
    if (fopen(TEXT".inp","r")){ freopen(TEXT".inp","r",stdin); freopen(TEXT".out","w",stdout); }

    int test_count = 1;
    cache2[0] = 1;
    frep(i,1,LG2) cache2[i] = cache2[i-1] * 2;
    cache3[0] = 1;
    frep(i,1,LG3) cache3[i] = cache3[i-1] * 3;
    // dbgl(cache2,cache2+LG2);
    // dbgl(cache3,cache3+LG3);
    if (MULTI_TEST) cin >> test_count;
    while (test_count--){ solve(); }

    return 0;
}


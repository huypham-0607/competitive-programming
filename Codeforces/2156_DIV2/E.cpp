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
const int MD = 1e9+7; //998244353;
const long long LLINF = 1e18+3;

const bool MULTI_TEST = true;

//Starts here

int n;
int a[N];
vector<pii> optimal[N];

struct SegmentTree{
    struct Node{
        int val;
        Node(){
            val = -LLINF;
        }
    };

    int n;
    vector<Node> IT;

    void comb(Node& i, Node& l, Node& r){
        i.val = max(l.val,r.val);
    }

    void init(int _n) {
        n = _n;
        IT.resize(n*4+10, Node());
        build(1,1,n);
    }

    void build(int idx, int l, int r){
        if (l==r){
            IT[idx].val = -LLINF;
            return;
        }

        int mid = (l+r)/2;
        build(idx*2,l,mid);
        build(idx*2+1,mid+1,r);
        comb(IT[idx],IT[idx*2],IT[idx*2+1]);
    }

    void update(int idx, int l, int r, int x, int val){
        if (r < x || x < l) return;
        if (l==r){
            IT[idx].val = val;
            return;
        }
        int mid = (l+r)/2;
        update(idx*2,l,mid,x,val);
        update(idx*2+1,mid+1,r,x,val);
        comb(IT[idx],IT[idx*2],IT[idx*2+1]);
    }

    int getVal(int idx, int l, int r, int x, int y){
        if (y < l || r < x) return -LLINF;
        if (x <= l && r <= y){
            return IT[idx].val;
        }

        int mid = (l+r)/2;
        return max(getVal(idx*2,l,mid,x,y),getVal(idx*2+1,mid+1,r,x,y));

    }
} IT;

template <typename T, typename Compare>
void update(vector<T>& v, T val, Compare comp) {
    frep(i,0,3) {
        if (comp(val,v[i])) {
            for (int j = 2; j > i; j--) {
                v[j] = v[j-1];
            }
            v[i] = val;
            return;
        }
    }
}

vector<int> affect[N];

void solve(){
    // dbg("new test");
    cin >> n;
    ffor(i,1,n) {
        affect[i].clear();
        optimal[i].clear();
        optimal[i].resize(3,{-LLINF, 0});
    }
    ffor(i,1,n) {
        cin >> a[i];
    }

    vector<pii> local_opt(3);
    frep(i,0,3) local_opt[i] = {LLINF,0};
    ffor (i,1,n) {
        // dbg(local_opt);
        frep(idx,0,3) {
            update(optimal[i], make_pair(a[i] - local_opt[idx].fi, local_opt[idx].se), greater<pii>());
        }
        update(local_opt, make_pair(a[i],i), less<pii>());
    }
    ffor(i,1,n) {
        // dbg(optimal[i]);
    }

    frep(i,0,3) local_opt[i] = {-LLINF,0};
    rfor (i,n,1) {
        // dbg(local_opt);
        frep(idx,0,3) {
            update(optimal[i], make_pair(local_opt[idx].fi - a[i], local_opt[idx].se), greater<pii>());
        }
        update(local_opt, make_pair(a[i],i), greater<pii>());
    }

    ffor(i,1,n) {
        for (int idx = 0; idx < 2; idx++) {
            auto [delta,j] = optimal[i][idx];
            affect[j].push_back(i);
        }
    }

    IT.init(n);

    // ffor(i,1,n) {
    //     dbg(optimal[i]);
    // }

    ffor (i,1,n) {
        IT.update(1,1,n,i,optimal[i][1].first);
    }

    int ans = LLINF;
    ffor(i,1,n) {
        IT.update(1,1,n,i,-LLINF);
        for (auto x:affect[i]) {
            IT.update(1,1,n,x,optimal[x][2].first);
        }
        ans = min(ans,IT.getVal(1,1,n,1,n));
        // ffor (i,1,n) {
        //     cerr << IT.getVal(1,1,n,i,i) << " ";
        // }
        // cerr << endl;
        // dbgl(i,ans);
        for (auto x:affect[i]) {
            IT.update(1,1,n,x,optimal[x][1].first);
        }     
        IT.update(1,1,n,i,optimal[i][1].first);

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


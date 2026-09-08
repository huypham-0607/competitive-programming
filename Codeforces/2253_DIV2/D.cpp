/*She smiles, but nothing behind it feels real. The neon glow wraps around her like armor vibrant, untouchable, cold. Once, maybe, there was warmth in her gestures� but now it�s rehearsed. Perfectly practiced detachment. Her wave is polite, her wink playful, yet there�s an eerie hollowness like a ghost who forgot what it meant to feel. She doesn�t break down. She doesn�t react. She simply exists flawless, empty, and free. Because having zero feelings means never being hurt again.*/
#include <bits/stdc++.h>

#define TEXT ""

using namespace std;

#define pb push_back
#define endl "\n"
#define ffor(i, a, b) for(int i = a; i <= (b); ++i)
#define rfor(i, a, b) for(int i = a; i >= (b); --i)
#define frep(i, a, b) for(int i = a; i < (b); ++i)
#define rrep(i, a, b) for(int i = a; i > (b); --i)
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

const int N = 2e5+10;
const int INF = 1e9+7;
const int MD = 1e9+7; //998244353;
const long long LLINF = 1e18+3;

//Starts here

int x,y;

int calc_dist(int a, int b) {
    int dx = (x-a);
    int dy = (y-b);
    return dx*dx + dy*dy;
}

bool check(int mid, int dist) {
    return (calc_dist(mid, dist-mid) < calc_dist(mid-1, dist-mid+1));
}

void solve(){
    cin >> x >> y;

    int ansval = x*x + y*y;
    int ans = 0;
    int epoch = 0;
    ffor(i,1,20000) {
        // cout << "epoch: " << i << endl;
        int dist = (i*(i+1))/2;
        // cout << "dist: " << dist << endl;
        int tans = 0;
        int tansval = calc_dist(0,dist);
        int l = 1, r = dist;
        while (l<=r) {
            int mid = (l+r)/2;
            // cout << l << " " << r << " " << mid << endl;
            if ((dist-mid > y) || (check(mid, dist) && (mid <= x))) {
                tans = mid;
                tansval = calc_dist(mid,dist-mid);
                l = mid+1;
            }
            else r = mid-1;
        }
        if ((dist-tans <= y) && (tans <= x) && (tansval < ansval)) {
            epoch = i;
            ans = tans;
            ansval = tansval;
        }
    }
    int dist = epoch*(epoch-1)/2;
    int curx = ans;
    // cout << curx << endl;
    vector<char> ins;
    rfor(i,epoch,1) {
        if (i<=curx) {
            curx-=i;
            ins.push_back('X');
        }
        else ins.push_back('Y');
    }
    for (char c : ins) {
        cout << c;
    }
    cout << endl;
}

/*Driver Code*/
signed main(){
    cin.tie(0) -> sync_with_stdio(0);
    if (fopen(TEXT".inp","r")){
        freopen(TEXT".inp","r",stdin);
        freopen(TEXT".out","w",stdout);
    }

    int testCount = 1;
   cin >> testCount;
    while (testCount--){
        solve();
    }

    return 0;
}


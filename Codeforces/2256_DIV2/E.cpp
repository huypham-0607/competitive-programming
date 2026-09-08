/*She smiles, but nothing behind it feels real. The neon glow wraps around her like armor vibrant, untouchable, cold. Once, maybe, there was warmth in her gestures� but now it�s rehearsed. Perfectly practiced detachment. Her wave is polite, her wink playful, yet there�s an eerie hollowness like a ghost who forgot what it meant to feel. She doesn�t break down. She doesn�t react. She simply exists flawless, empty, and free. Because having zero feelings means never being hurt again.*/
#include <bits/stdc++.h>
#include <assert.h>

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

const int N = 800+10;
const int INF = 1e9+7;
const int MD = 1e9+7; //998244353;
const long long LLINF = 1e18+3;

//Starts here

int n;
int mat[N][N];

/*
    | Combinatorics |
    Desc: Library for BinPow, InvMod, and Binomial Coefficient
    Source: KawakiMeido
    State: Tested yay!
*/

namespace Comb {
    using ll = long long;

    const int MD = 1e9+7;
    const int N = 2e5;
    const int LG = 30;

    int invFac[N+1];
    int fac[N+1];

    int binPow(int a, int b, int MD){
        ll res = 1;
        for (int lg = LG-1; lg>=0; lg--){
            res = res*res%MD;
            if ((1LL<<lg)&b) res = res*a%MD;
        }
        return res;
    }

    int invMod(int x, int MD){
        return binPow(x,MD-2,MD);
    }

    int nCk(int n, int k){
        return 1LL*fac[n]*invFac[k]%MD*invFac[n-k]%MD;
    }

    struct Init {
        Init() {
            fac[0] = 1;
            invFac[0] = 1;
            for (int i = 1; i <= N; i++){
                fac[i] = (1LL*fac[i-1]*i%MD);
                invFac[i] = invMod(fac[i],MD);
            }
        }
    } _init;
}

void ans1(int i, int j, int x, int y) {
    cout << i+1 << " " <<  j+1 << " " << x+1 << " " << y+1 << endl;
    cout.flush();
}

int inv_mod(int n, int MD) {
    for (int i=1; i<MD; i++){
        if (n*i%MD == 1) return i;
    }
    assert(false);
}

void solvefirst(){
    cin >> n;
    int m = 0;
    int cur_x=0, cur_y=0;
    frep(i,0,n){
        frep(j,0,n) {
            char c; cin >> c;
            if (c=='#') {
                mat[i][j] = 1;
                cur_x = (cur_x + i)%n;
                cur_y = (cur_y + j)%n;
                m = (m+1)%n;
            }
            else mat[i][j] = 0;
        }
    }
    int inv_m = inv_mod(m,n);
    // cout << inv_m << endl;
    // cout << cur_x << " " << cur_y << endl;

    int true_x, true_y; cin >> true_x >> true_y;
    true_x--; true_y--;
    // cout << true_x << " " << true_y << endl;
    int d_x = (m*true_x%n - cur_x+n)%n;
    int d_y = (m*true_y%n - cur_y+n)%n;
    assert(d_x >= 0);
    assert(d_y >= 0);
    // cout << d_x << " " << d_y << endl;
    frep(i,0,n) {
        frep(j,0,n) {
            int x = (i+d_x+n)%n;
            int y = (j+d_y+n)%n;
            if (mat[i][j] == 1 && mat[x][y] == 0) {
                ans1(i,j,x,y);
                return;
            }
        }
    }
    ans1(0,0,0,0);
}

void ans2(int x, int y){
    cout << x+1 << " " << y+1 << endl;
    cout.flush();
}

void solvesecond() {
    cin >> n;
    int cur_x=0, cur_y=0;
    int m = 0;
    frep(i,0,n){
        frep(j,0,n) {
            char c; cin >> c;
            if (c=='#') {
                mat[i][j] = 1;
                cur_x = (cur_x + i)%n;
                cur_y = (cur_y + j)%n;
                m = (m+1)%n;
            }
            else mat[i][j] = 0;
        }
    }
    int inv_m = inv_mod(m,n);

    int x = (cur_x * inv_m)%n;
    int y = (cur_y * inv_m)%n;
    ans2(x,y);
}

/*Driver Code*/
signed main(){
    cin.tie(0) -> sync_with_stdio(0);
    if (fopen(TEXT".inp","r")){
        freopen(TEXT".inp","r",stdin);
        freopen(TEXT".out","w",stdout);
    }
    string tp; cin >> tp;
    int testCount = 1;
   cin >> testCount;
    while (testCount--){
        if (tp == "first") solvefirst();
        else solvesecond();
    }

    return 0;
}


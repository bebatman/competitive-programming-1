#include <iostream>
#include <string>
#include <utility>
#include <sstream>
#include <algorithm>
#include <stack>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <bitset>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <unordered_set>
#include <ctime>

using namespace std;

template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define F0R1(i, a) for (int i=1; i<=(a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)
#define F0Rd1(i, a) for (int i=a; i>0; i--)
#define SORT(vec) sort(vec.begin(), vec.end())
#define MIN(a, b) a = min(a, b)
#define MAX(a, b) a = max(a, b)

#define INF 1000000010
#define LL_INF 4500000000000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define pA first
#define pB second
#define mp make_pair
#define pb push_back
#define PI acos(-1.0)
#define ll long long
#define MOD (int)(2e+9+11)
#define SET(vec, val, size) for (int i = 0; i < size; i++) vec[i] = val;
#define SET2D(arr, val, dim1, dim2) F0R(i, dim1) F0R(j, dim2) arr[i][j] = val;
#define SET3D(arr, val, dim1, dim2, dim3) F0R(i, dim1) F0R(j, dim2) F0R(k, dim3) arr[i][j][k] = val;
#define SET4D(arr, val, dim1, dim2, dim3, dim4) F0R(i, dim1) F0R(j, dim2) F0R(k, dim3) F0R(l, dim4) arr[i][j][k][l] = val;
#define READGRID(arr, dim) F0R(i, dim) F0R(j, dim) cin >> arr[i][j];
#define all(x) (x).begin(), (x).end()

typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<ll> vl;

void setupIO(const string &PROB) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ifstream infile(PROB + ".in");
    if (infile.good()) {
        freopen((PROB + ".in").c_str(), "r", stdin);
        freopen((PROB + ".out").c_str(), "w", stdout);
    }
}

/* ============================ */

int n, k;
ll dp[200][(1 << 16)];
ll finalDP[200];
iii requirements[100];

string solve(ll p, int start) {
    if (start == n) return "";
    if (presetVal[start] != -1) return to_string(presetVal[start]) + solve(p, start + 1);
    if (p >= finalDP[start+1]) {
        return "1" + solve(p-finalDP[start+1], start+1);
    } else {
        return "0" + solve(p, start+1);
    }
}

int main() {
    int t; cin >> t;
    F0R1(caseNum, t) {
        ll p;
        cin >> n >> k >> p;
        F0R(i, k) {
            int a, b, c; cin >> a >> b >> c;
            requirements[i] = { c, { --a, --b } };
        }
        SET2D(dp, 0, 200, (1 << 16));

        // TODO figure out how to populate dp
        F0R(i, n) {
            F0R(j, (1 << 16)) {
                bool bad = false;
                F0R(l, k) {
                    if (requirements[l].pB.pB <= i && requirements[l].pB.pA >= i+15) {
                        int ct = 0;
                        F0R(m, 16) {
                            if (j & (1 << m)) ct++;
                        }
                        if (ct != requirements[l].pA) bad = true;
                    }
                }
                if (bad) dp[i][j] = 0;
                else dp[i][j] = dp[i+1][(j & ~(1 << 16)) << 1] + dp[i+1][((j & ~(1 << 16)) << 1) + 1];
            }
        }

        SET(finalDP, 0, 200);
        F0R(i, n) {
            F0R(j, (1 << 16)) {
                finalDP[i] += dp[i][j];
            }
        }
        cout << "Case #" << caseNum << ": " << solve(p-1, 0) << endl;
    }

    return 0;
}
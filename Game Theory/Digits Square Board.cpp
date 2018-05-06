#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <map>
#include <set>
#include <bitset>
#include <sstream>
#include <cstdlib>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <climits>
#include <cstdio>
#include <ctype.h>
#include <time.h>
using namespace std;

#define PI acos(-1.0)
#define EPS 1e-8
#define MOD 1000000007
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define pb push_back
#define fi first
#define se second
#define go(i, a, b) for(int i = a; i <= b; ++i)
#define gorev(i, a, b) for(int i = a; i >= b; --i)

typedef long double ld;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;

template <class L, class R> ostream &operator <<(ostream &os, pair<L, R> P){
    return os << "(" << P.fi << "," << P.se << ")";
}
template <class T> ostream &operator <<(ostream &os, vector<T> V){
    os << "["; for (auto vv: V) os << vv << ","; return os << "]";
}
template <class L, class R> ostream &operator <<(ostream &os, map<L, R> M){
    os << "["; for (auto pr: M) os << pr.fi << "->" << pr.se << ","; return os << "]";
}
template <class L, class R> ostream &operator <<(ostream &os, unordered_map<L, R> M){
    os << "["; for (auto pr: M) os << pr.fi << "->" << pr.se << ","; return os << "]";
}

struct Matrix {
    vvi data;
    int r, c;
    Matrix(int row, int col, bool identity = false) : r(row), c(col) {
        data.assign(row, vector<int>(col, 0));
        if (identity) {
            for (int i = 0; i < r; ++i) {
                data[i][i] = 1;
            }
        }
    }
    Matrix operator * (Matrix& other) {
        int m = r, n = c, p = other.c;
        Matrix res(m, p);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < p; ++j) {
                for (int k = 0; k < n; ++k) {
                    res.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return res;
    }
};

vector<int> extendGcd(int a, int b) {
    if (b == 0) {
        return {1, 0, a};
    } else {
        vector<int> tmp = extendGcd(b, a % b);
        return {tmp[1], tmp[0] - (a / b) * tmp[1], tmp[2]};
    }
}

Matrix matrix_power(Matrix base, ll exp) {
    int n = base.r;
    Matrix res(n, n, true);
    while (exp) {
        if (exp & 1) {
            res = res * base;
        }
        base = base * base;
        exp >>= 1;
    }
    return res;
}

/******************************** template ********************************/
#define N 31
int n;
int dp[N][N][N][N];
int cnt[N][N];

int sum(int x1, int y1, int x2, int y2) {
    return cnt[x2][y2] - cnt[x2][y1 - 1] - cnt[x1 - 1][y2] + cnt[x1 - 1][y1 - 1];
}

int solve(int x1, int y1, int x2, int y2) {
    if (x1 == x2 && y1 == y2) return 0;
    if (sum(x1, y1, x2, y2) == 0) return 0;
    if (dp[x1][y1][x2][y2] != -1) return dp[x1][y1][x2][y2];

    vi tmp(75, 0);
    for (int i = y1; i < y2; ++i) {
        int sub1 = solve(x1, y1, x2, i);
        int sub2 = solve(x1, i + 1, x2, y2);
        tmp[sub1 ^ sub2] = 1;
    }
    for (int i = x1; i < x2; ++i) {
        int sub1 = solve(x1, y1, i, y2);
        int sub2 = solve(i + 1, y1, x2, y2);
        tmp[sub1 ^ sub2] = 1;
    }

    for (int i = 0; i < 75; ++i) {
        if (tmp[i] == 0) return dp[x1][y1][x2][y2] = i;
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout.precision(10);
    cout << fixed;
#ifdef ZYC_LOCAL
    freopen("input.txt", "rt", stdin);
#endif
    int t, tmp;
    cin >> t;
    while (t--) {
        cin >> n;
        memset(dp, -1, sizeof(dp));
        go(i, 1, n) go(j, 1, n) {
                cin >> tmp;
                if (tmp == 1 || tmp == 4 || tmp == 6 || tmp == 8 || tmp == 9) {
                    cnt[i][j] = 1;
                } else {
                    cnt[i][j] = 0;
                }
                cnt[i][j] += cnt[i - 1][j] + cnt[i][j - 1] - cnt[i - 1][j - 1];
            }

        cout << (solve(1, 1, n, n) ? "First" : "Second") << endl;
    }

#ifdef ZYC_LOCAL
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}

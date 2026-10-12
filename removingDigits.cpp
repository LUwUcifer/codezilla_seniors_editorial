#pragma GCC optimize("O3")

#include <bits/stdc++.h>

using namespace std;

#define IOS ios::sync_with_stdio(false); cin.tie(0)
#define ll long long
#define ld long double
#define mp(a, b) make_pair(a, b)
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pil pair<int, ll>
#define pli pair<ll, int>
#define fi first
#define se second


const int N = 2e5 + 10;
const ll LINF = 1e18;
const int INF = 1e9;
const ld PI = 4*atan((ld)1);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};

pll dp[18][10][10];
ll deg[19];

// dp[i][j][k] == (k)10^(i + 1) - j -> 10^(i - 1)

int main() {
    deg[0] = 1;
    for (int i = 1; i < 19; ++i)
        deg[i] = deg[i - 1] * 10;

    for (int j = 1; j < 10; ++j) {
        for (int k = 0; k < 10; ++k) {
            dp[0][j][k] = {1, -min(0, 10 - j - k)};
        }
    }
    for (int k = 0; k < 10; ++k)  {
        dp[0][0][k] = {2, -min({0, 10 - 2 * k})};
    }

    for (int i = 1; i < 18; ++i)  {
        for (int j = 1; j < 10; ++j)
            for (int k = 0; k < 10; ++k) {
                int cur = j;
                for (int z = 9; z >= 0; --z) {
                    if (cur == 0) {
                        ++dp[i][j][k].fi;
                        cur = max(k, z + 1);
                    }
                    dp[i][j][k].fi += dp[i - 1][cur][max(k, z)].fi;
                    cur = dp[i - 1][cur][max(k, z)].se;
                }
                dp[i][j][k].se = cur;
            }

        for (int k = 0; k < 10; ++k) {
            dp[i][0][k] = dp[i][max(k, 1)][k];
            ++dp[i][0][k].fi;
        }
    }
    ll n;
    cin >> n;
    if (n < 10) {
        cout << 1 << '\n';
        return 0;
    }

    ll res = 0;
    for (int i = 1; n > 0; ++i) {
        int k = 0;
        for (int j = i + 1; j < 19; ++j)
            k = max(k, int(n / deg[j] % 10));

        int cur = (10 - (n % 10)) % 10;
        while(((n / deg[i] % 10) != 9 || cur == 0) && n > 0) {
            int d = n / deg[i] % 10;
            if (cur == 0) {
                n -= max(d, k);
                ++res;
            }
            else {
                res += dp[i - 1][cur][max(d, k)].fi;
                cur = dp[i - 1][cur][max(d, k)].se;
                n /= deg[i];
                n *= deg[i];
                n -= cur;
            }
            cur = (10 - (n % 10)) % 10;
        }
    }

    cout << res << '\n';

    return 0;
}
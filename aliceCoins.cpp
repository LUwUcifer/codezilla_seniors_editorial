#include <bits/stdc++.h>

using namespace std;

#define fixed(n) fixed << setprecision(n)
#define ceil(n, m) (((n) + (m) - 1) / (m))
#define add_mod(a, b, m) (((a % m) + (b % m)) % m)
#define sub_mod(a, b, m) (((a % m) - (b % m) + m) % m)
#define mul_mod(a, b, m) (((a % m) * (b % m)) % m)
#define all(vec) vec.begin(), vec.end()
#define rall(vec) vec.rbegin(), vec.rend()
#define sz(x) int(x.size())
#define debug(x) cout << #x << ": " << (x) << "\n";
#define fi first
#define se second
#define ll long long
#define ull unsigned long long
#define EPS 1e-9
constexpr int INF = 1 << 30, Mod = 1e9 + 7;
constexpr ll LINF = 1LL << 62;
#define PI acos(-1)
template<typename T = int>
using Pair = pair<T, T>;
vector<string> RET = {"NO", "YES"};

template<typename T = int>
istream &operator >>(istream &in, vector<T> &v) {
    for (auto &x: v) in >> x;
    return in;
}

template<typename T = int>
ostream &operator <<(ostream &out, const vector<T> &v) {
    for (const T &x: v) out << x << ' ';
    return out;
}

class Matrix {
public:
    ll a, b, c, d;

    Matrix() : a(0), b(0), c(0), d(0) {
    };

    Matrix(ll a, ll b, ll c, ll d) : a(a), b(b), c(c), d(d) {
    }

    Matrix operator*(const Matrix &m) const {
        Matrix res;
        res.a = (a * m.a + b * m.c) % Mod;
        res.b = (a * m.b + b * m.d) % Mod;
        res.c = (c * m.a + d * m.c) % Mod;
        res.d = (c * m.b + d * m.d) % Mod;
        return res;
    }
};

ll power(ll base, ll exp) {
    ll res{1LL};
    base %= Mod;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % Mod;
        base = (base * base) % Mod;
        exp >>= 1;
    }
    return res;
}

Matrix matPower(Matrix base, ll exp) {
    Matrix res(1, 0, 0, 1);
    while (exp > 0) {
        if (exp & 1) res = (res * base);
        base = (base * base);
        exp >>= 1;
    }
    return res;
}

void Solve() {
    ll a, b, n;
    cin >> a >> b >> n;
    if (n == 1) {
        std::cout << "1" << std::endl;
        return;
    }
    //at i, probability of getting tails is (T[i-1] + H[i-1])*(b-a/b)
    //probability of getting heads is T[i-1]*a/b
    /*
     *i = 1, T[i] = q, H[i] = p
     *i = 2, T[i] = p, H[i] = pq
     *i = 3, T[i] = (p + pq)q, H[i] = p^2
     *Probability of winning = T[n-1] + H[n-1]
     */
    ll p = mul_mod(a, power(b, Mod-2), Mod);
    ll q = (Mod + 1 - p) % Mod;

    if (a == b) {
        cout << 0 << endl;
        return;
    }

    Matrix res(q, q, p, 0);
    res = matPower(res, n - 1);

    ll t = add_mod(mul_mod(res.a, q, Mod), mul_mod(res.b, p, Mod), Mod);
    ll h = add_mod(mul_mod(res.c, q, Mod), mul_mod(res.d, p, Mod), Mod);

    ll ans = add_mod(t, h, Mod);

    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    Solve();
    return 0;
}

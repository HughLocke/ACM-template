//NTT(快速数论变换)
/*
干的事情和FFT差不多,优点：1.可以取模，FFT的浮点运算时不可以取模的
2.全部整数运算避免了fft的浮点数误差
缺点:1.多项式的系数必须是整数
2.如果取模的数字不是998244353,1004535809,469762049这几个原根是3的数字,
需要中国剩余定理求，很麻烦
*/
//模数为998244353
const int maxn = 3 * 1e6 + 10, P = 998244353, G = 3, Gi = 332748118; 
int N, M, limit = 1, L, r[maxn];
LL a[maxn], b[maxn];
inline LL fastpow(LL a, LL k) {
    LL base = 1;
    while(k) {
        if(k & 1) base = (base * a ) % P;
        a = (a * a) % P;
        k >>= 1;
    }
    return base % P;
}
inline void NTT(LL *A, int type) {
    for(int i = 0; i < limit; i++) 
        if(i < r[i]) swap(A[i], A[r[i]]);
    for(int mid = 1; mid < limit; mid <<= 1) {  
        LL Wn = fastpow( type == 1 ? G : Gi , (P - 1) / (mid << 1));
        for(int j = 0; j < limit; j += (mid << 1)) {
            LL w = 1;
            for(int k = 0; k < mid; k++, w = (w * Wn) % P) {
                 int x = A[j + k], y = w * A[j + k + mid] % P;
                 A[j + k] = (x + y) % P,
                 A[j + k + mid] = (x - y + P) % P;
            }
        }
    }
}
int main() {
    N = read(); M = read();
    for(int i = 0; i <= N; i++) a[i] = (read() + P) % P;
    for(int i = 0; i <= M; i++) b[i] = (read() + P) % P;
    while(limit <= N + M) limit <<= 1, L++;
    for(int i = 0; i < limit; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (L - 1));  
    NTT(a, 1);NTT(b, 1);    
    for(int i = 0; i < limit; i++) a[i] = (a[i] * b[i]) % P;
    NTT(a, -1); 
    LL inv = fastpow(limit, P - 2);
    for(int i = 0; i <= N + M; i++)
        printf("%d ", (a[i] * inv) % P);
    return 0;
}
//任意模数NTT
int mod;
namespace Math {
    inline int pw(int base, int p, const int mod) {
        static int res;
        for (res = 1; p; p >>= 1, base = static_cast<long long> (base) * base % mod) if (p & 1) res = static_cast<long long> (res) * base % mod;
        return res;
    }
    inline int inv(int x, const int mod) { return pw(x, mod - 2, mod); }
}

const int mod1 = 998244353, mod2 = 1004535809, mod3 = 469762049, G = 3;
const long long mod_1_2 = static_cast<long long> (mod1) * mod2;
const int inv_1 = Math::inv(mod1, mod2), inv_2 = Math::inv(mod_1_2 % mod3, mod3);
struct Int {
    int A, B, C;
    explicit inline Int() { }
    explicit inline Int(int __num) : A(__num), B(__num), C(__num) { }
    explicit inline Int(int __A, int __B, int __C) : A(__A), B(__B), C(__C) { }
    static inline Int reduce(const Int &x) {
        return Int(x.A + (x.A >> 31 & mod1), x.B + (x.B >> 31 & mod2), x.C + (x.C >> 31 & mod3));
    }
    inline friend Int operator + (const Int &lhs, const Int &rhs) {
        return reduce(Int(lhs.A + rhs.A - mod1, lhs.B + rhs.B - mod2, lhs.C + rhs.C - mod3));
    }
    inline friend Int operator - (const Int &lhs, const Int &rhs) {
        return reduce(Int(lhs.A - rhs.A, lhs.B - rhs.B, lhs.C - rhs.C));
    }
    inline friend Int operator * (const Int &lhs, const Int &rhs) {
        return Int(static_cast<long long> (lhs.A) * rhs.A % mod1, static_cast<long long> (lhs.B) * rhs.B % mod2, static_cast<long long> (lhs.C) * rhs.C % mod3);
    }
    inline int get() {
        long long x = static_cast<long long> (B - A + mod2) % mod2 * inv_1 % mod2 * mod1 + A;
        return (static_cast<long long> (C - x % mod3 + mod3) % mod3 * inv_2 % mod3 * (mod_1_2 % mod) % mod + x) % mod;
    }
} ;

#define maxn 131072

namespace Poly {
#define N (maxn << 1)
    int lim, s, rev[N];
    Int Wn[N | 1];
    inline void init(int n) {
        s = -1, lim = 1; while (lim < n) lim <<= 1, ++s;
        for (register int i = 1; i < lim; ++i) rev[i] = rev[i >> 1] >> 1 | (i & 1) << s;
        const Int t(Math::pw(G, (mod1 - 1) / lim, mod1), Math::pw(G, (mod2 - 1) / lim, mod2), Math::pw(G, (mod3 - 1) / lim, mod3));
        *Wn = Int(1); for (register Int *i = Wn; i != Wn + lim; ++i) *(i + 1) = *i * t;
    }
    inline void NTT(Int *A, const int op = 1) {
        for (register int i = 1; i < lim; ++i) if (i < rev[i]) std::swap(A[i], A[rev[i]]);
        for (register int mid = 1; mid < lim; mid <<= 1) {
            const int t = lim / mid >> 1;
            for (register int i = 0; i < lim; i += mid << 1) {
                for (register int j = 0; j < mid; ++j) {
                    const Int W = op ? Wn[t * j] : Wn[lim - t * j];
                    const Int X = A[i + j], Y = A[i + j + mid] * W;
                    A[i + j] = X + Y, A[i + j + mid] = X - Y;
                }
            }
        }
        if (!op) {
            const Int ilim(Math::inv(lim, mod1), Math::inv(lim, mod2), Math::inv(lim, mod3));
            for (register Int *i = A; i != A + lim; ++i) *i = (*i) * ilim;
        }
    }
#undef N
}

int n, m;
Int A[maxn << 1], B[maxn << 1];
int main() {
    scanf("%d%d%d", &n, &m, &mod); ++n, ++m;
    for (int i = 0, x; i < n; ++i) scanf("%d", &x), A[i] = Int(x % mod);
    for (int i = 0, x; i < m; ++i) scanf("%d", &x), B[i] = Int(x % mod);
    Poly::init(n + m);
    Poly::NTT(A), Poly::NTT(B);
    for (int i = 0; i < Poly::lim; ++i) A[i] = A[i] * B[i];
    Poly::NTT(A, 0);
    for (int i = 0; i < n + m - 1; ++i) {
        printf("%d", A[i].get());
        putchar(i == n + m - 2 ? '\n' : ' ');
    }
    return 0;
}
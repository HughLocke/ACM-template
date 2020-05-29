//组合数 C(n,m)
//预处理Comb[maxn][maxn] ,复杂度n ^ 2
#include<cstdio>
const int N = 2000 + 5;
const int MOD = (int)1e9 + 7;
int comb[N][N];//comb[n][m]就是C(n,m)
void init(){
    for(int i = 0; i < N; i ++){
        comb[i][0] = comb[i][i] = 1;
        for(int j = 1; j < i; j ++){
            comb[i][j] = comb[i-1][j] + comb[i-1][j-1];
            comb[i][j] %= MOD;
        }
    }
}
int main(){
    init();
}
//O(n)求C(n,m)
#include<cstdio>
const int N = 200000 + 5;
const int MOD = (int)1e9 + 7;
int F[N], Finv[N], inv[N];//F是阶乘，Finv是逆元的阶乘 
void init(){
    inv[1] = 1;
    for(int i = 2; i < N; i ++){
        inv[i] = (MOD - MOD / i) * 1ll * inv[MOD % i] % MOD;
    }
    F[0] = Finv[0] = 1;
    for(int i = 1; i < N; i ++){
        F[i] = F[i-1] * 1ll * i % MOD;
        Finv[i] = Finv[i-1] * 1ll * inv[i] % MOD;
    }
}
int comb(int n, int m){//comb(n, m)就是C(n, m) 
    if(m < 0 || m > n) return 0;
    return F[n] * 1ll * Finv[n - m] % MOD * Finv[m] % MOD;
}
int main(){
    init();
}
//不预处理
LL fact(int n, LL p){//n的阶乘求余p 
    LL ret = 1;
     for (int i = 1; i <= n ; i ++) ret = ret * i % p ;
    return ret ;
}
void ex_gcd(LL a, LL b, LL &x, LL &y, LL &d){
    if (!b) {d = a, x = 1, y = 0;}
    else{
        ex_gcd(b, a % b, y, x, d);
        y -= x * (a / b);
    }
}
LL inv(LL t, LL p){//如果不存在，返回-1 
    LL d, x, y;
    ex_gcd(t, p, x, y, d);
    return d == 1 ? (x % p + p) % p : -1;
}
LL comb(int n, int m, LL p){//C(n, m) % p
    if (m < 0 || m > n) return 0;
    return fact(n, p) * inv(fact(m, p), p) % p * inv(fact(n-m, p), p) % p;
}
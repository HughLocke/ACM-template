//二项式反演
/*
    f(n) = ΣC(n,i) * g(i) (0 <= i <= n)
->  g(n) = Σ((-1) ^ (n - i)) * C(n,i) * f(i) (0 <= i <= n)
 */
//模板：n封信对应n个信封，求恰好全部装错了信封的方案数
//设g(i)为恰好装错了i个信封的个数，则装的全部种类f(n) = g(1) * C(n,1) + g(2) * C(n,2)...... + g(n) * C(n,n)
//代入二项式反演公式，其中f(n) = n! 
int N,M,K;
LL fac[maxn];
int comb[30][30];
void init(){
    fac[0] = 1;
    for(int i = 1; i <= 20; i ++) fac[i] = fac[i - 1] * i;
    for(int i = 0 ; i <= 20; i ++){
        comb[i][0] = comb[i][i] = 1;
        for(int j = 1; j < i ; j ++){
            comb[i][j] = comb[i - 1][j] + comb[i - 1][j - 1];
        }
    }
}
int main(){
    init();
    while(~Sca(N)){
        LL ans = 0;
        for(int i = 0 ; i <= N ; i ++){
            LL p = comb[N][i] * fac[i];
            if((N - i) & 1) p = -p;
            ans += p;
        }
        Prl(ans);
    }
    return 0;
}
//Σi ^ k 
//1^k+2^k+3^k+...n^k
/*可以被证明，结果是一个n为自变量的k + 1次多项式
因此我们将n = (0,1,2,3....,k,k + 1)代入算出函数值
将这0 ~ k + 1所有的点用拉格朗日插值插入
求解的时候就将n作为下标代入就可以了。
可以用上面在x取值连续时的做法优化，时间复杂度k ^ 2
 */
 //luoguP4593 模板为函数getsum
const int maxn = 70;
const int mod = 1e9 + 7; 
LL N,M,K;
LL fac[maxn],ifac[maxn]; //阶乘，阶乘的逆元
LL mul(LL a,LL b){
    return a % mod * b % mod;
}
LL add(LL a,LL b){
    return ((a + b) % mod + mod) % mod;
}
LL quick_power(LL a,LL b){
    LL ans = 1;
    while(b){
        if(b & 1) ans = mul(ans,a);
        a = mul(a,a);
        b >>= 1;
    }
    return ans;
}
LL inv(LL x){
    return quick_power(x,mod - 2);
}
void init(){
    fac[0] = 1;
    for(int i = 1; i <= 60 ; i ++) fac[i] = mul(i,fac[i - 1]);
    ifac[60] = inv(fac[60]);
    for(int i = 59; i >= 0; i --) ifac[i] = mul(i + 1,ifac[i + 1]);
} 
LL a[maxn],pre[maxn],suf[maxn],y[maxn];
LL getsum(LL n,LL k){ // 1 ^ k + 2 ^ k + ... + n ^ k
    LL Lim = k + 1,ans = 0; y[0] = 0;
    for(int i = 1; i <= Lim; i ++) y[i] = add(y[i - 1],quick_power(i,k));
    pre[0] = n; suf[Lim + 1] = 1;
    for(int i = 1; i <= Lim; i ++) pre[i] = mul(pre[i - 1],add(n,-i));
    for(int i = Lim; i >= 1; i --) suf[i] = mul(suf[i + 1],add(n,-i));
    for(int i = 1 ; i <= Lim; i ++){
        LL up = mul(y[i],mul(pre[i - 1],suf[i + 1]));
        LL down = mul(ifac[i],ifac[Lim - i]);
        if((Lim - i) & 1) down = mod - down;
        ans = add(ans,mul(down,up));
    }
    return ans;
}
int main(){
    int T; Sca(T); init();
    while(T--){
        scanf("%lld%lld",&N,&M); K = M + 1;
        for(int i = 1; i <= M; i ++) Scl(a[i]);
        a[++M] = ++N;
        sort(a + 1,a + 1 + M);
        LL ans = 0;
        for(int i = 1; i <= M ; i ++){
            for(int j = i ; j <= M ; j ++) ans = add(ans,add(getsum(a[j] - 1,K),-getsum(a[j - 1],K)));
            for(int j = i + 1; j <= M ; j ++) a[j] = add(a[j],-a[i]);
            a[i] = 0;
        }
        Prl(ans);
    }
    return 0;
}
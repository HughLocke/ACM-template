//卢卡斯定理,计算C(n,m) % p, 当n，m很大(1e18)且p比较小(1e5)的情况
//C(n, m) % p  =  C(n / p, m / p) * C(n%p, m%p) % p
LL Lucas(LL n, LL m, int p){
        return m ? Lucas(n/p, m/p, p) * comb(n%p, m%p, p) % p : 1;
}



//例题 hdu5446
/*
给你三个数n, m, k
第二行是k个数，p1,p2,p3...pk
所有p的值不相同且p都是质数
求C(n, m) % (p1*p2*p3*...*pk)的值
范围：1≤m≤n≤1e18，1≤k≤10，pi≤1e5，保证p1*p2*p3*...*pk≤1e18
我们知道题目要求C(n, m) % (p1*p2*p3*...*pk)的值
其实这个就是中国剩余定理最后算出结果后的最后一步求余
那C(n, m)相当于以前我们需要用中国剩余定理求的值
然而C(n, m)太大，我们只好先算出
C(n, m) % p1 = r1
C(n, m) % p2 = r2
C(n, m) % p3 = r3
.
C(n, m) % pk = rk
用Lucas，这些r1,r2,r3...rk可以算出来
然后又是用中国剩余定理求答案
 */
const int maxn = 110;
const int maxp = 1e5 + 10;
const int INF = 0x3f3f3f3f;
LL N,M,K;
LL F[maxp],Finv[maxp],inv[maxp];
void init(LL MOD){
    inv[1] = 1;
    for(int i = 2; i < maxp; i ++){
        inv[i] = (MOD - MOD / i) * 1LL * inv[MOD % i] % MOD; 
    }
    F[0] = Finv[0] = 1;
    for(int i = 1; i < maxp; i ++){
        F[i] = F[i - 1] * 1LL * i % MOD;
        Finv[i] = Finv[i - 1] * 1LL * inv[i] % MOD;
    }
}
LL quick_power(LL a,LL b,LL p){
    LL ans = 1;
    while(b){
        if(b & 1) ans = ans * a % p;
        b >>= 1;
        a = a * a % p;
    }
    return ans;
}
void ex_gcd(LL a, LL b, LL &x, LL &y, LL &d){
    if (!b) {d = a, x = 1, y = 0;}
    else{
        ex_gcd(b, a % b, y, x, d);
        y -= x * (a / b);
    }
}
LL Inv(LL t, LL p){//如果不存在，返回-1 
    LL d, x, y;
    ex_gcd(t, p, x, y, d);
    return d == 1 ? (x % p + p) % p : -1;
}
LL fact(int n, LL p){//n的阶乘求余p 
    LL ret = 1;
     for (int i = 1; i <= n ; i ++) ret = ret * i % p ;
    return ret ;
}
LL comb(int n,int m,LL p){
    if(m < 0 || m > n) return 0;
    return fact(n,p) * Inv(fact(m,p),p) % p * Inv(fact(n - m,p),p) % p;
}
LL Lucas(LL n,LL m,LL p){
    return m?Lucas(n / p,m / p,p) * comb(n % p,m % p,p) % p : 1;
}

LL mul(LL a,LL b,LL p){
    LL ans = 0;
    while(b){
        if(b & 1) ans = (ans + a) % p;
        a = (a + a) % p;
        b >>= 1;
    }
    return ans;
}
LL china(int n,LL *a,LL *m){
    LL M = 1,ret = 0;
    for(int i = 1; i <= n; i ++) M *= m[i];
    for(int i = 1; i <= n; i ++){
        LL w = M / m[i];
        ret = (ret + mul(w * Inv(w,m[i]),a[i],M)) % M;
    }
    return (ret + M) % M;
}
LL a[maxn],b[maxn];
int main(){
    int T; Sca(T);
    while(T--){
        scanf("%lld%lld%lld",&N,&M,&K);
        for(int i = 1; i <= K ; i ++){
            Scl(a[i]); 
            b[i] = Lucas(N,M,a[i]);
        }    
        Prl(china(K,b,a));
    }
    return 0;
}
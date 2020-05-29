/*重心拉格朗日插值法
求原函数复杂度为O(n^2),单次求值复杂度O(n^2)。
动态加点？ 
每次增加一个点，一般求法会重新计算一次达到O(n2^)的复杂度，而重心拉格朗日插值法只需O(n)计算wi即可。
 */
 /*模板：tyvj1858
f(i)=1^k+2^k+3^k+......+i^k
g(x)=f(1)+f(2)+f(3)+....+f(x)
求(g(a)+g(a+d)+g(a+2d)+......+g(a+nd))mod p
解：可知f(i)是k + 1次多项式,g(x)是k + 2次多项式,h(i)是k + 3次多项式
  */
const int maxn = 210;
const LL mod = 1234567891; 
LL K,a,n,d,p;
inline LL mul(LL a,LL b){return (a % mod * b % mod + mod) % mod;}
inline LL add(LL a,LL b){return ((a + b) % mod + mod) % mod;}
LL quick_power(LL a,LL b){
    LL ans = 1;
    while(b){
        if(b & 1) ans = mul(ans,a);
        b >>= 1;
        a = mul(a,a);
    }
    return ans;
}
LL inv(LL a){
    return quick_power(a,mod - 2);
}
LL get(LL *t,LL *x,LL *y,LL Lim,LL n){
    LL g = 1;
    for(int i = 1; i <= Lim; i ++) if(n == x[i]) return y[i];
    for(int i = 1; i <= Lim; i ++) g = mul(g,add(n,-x[i]));
    LL ans = 0;
    for(int i = 1; i <= Lim ; i ++) ans = add(ans,mul(t[i],inv(add(n,-x[i]))));
    ans = mul(ans,g);
    return ans;
}
LL f[maxn],g[maxn],h[maxn],t[maxn];
LL x[maxn];
int main(){
    int T; Sca(T);
    while(T--){
        scanf("%lld%lld%lld%lld",&K,&a,&n,&d);
        for(int i = 1; i <= 130; i ++) f[i] = add(f[i - 1],quick_power(i,K));
        for(int i = 1; i <= 130; i ++) g[i] = add(g[i - 1],f[i]);
        for(int i = 1; i <= K + 3; i ++) x[i] = i;
        for(int i = 1; i <= K + 3; i ++){
            t[i] = 1;
            for(int j = 1 ; j <= K + 3; j ++){
                if(i == j) continue;
                t[i] = mul(t[i],x[i] - x[j]);
            }
            t[i] = mul(g[i],inv(t[i]));
        }
        for(int i = 1; i <= K + 4; i ++) h[i] = add(h[i - 1],get(t,x,g,K + 3,add(a,mul(i - 1,d))));
        for(int i = 1; i <= K + 4; i ++) x[i] = add(a,mul(i - 1,d));
        for(int i = 1; i <= K + 4; i ++){
            t[i] = 1;
            for(int j = 1; j <= K + 4; j ++){
                if(i == j) continue;
                t[i] = mul(t[i],x[i] - x[j]);
            }
            t[i] = mul(h[i],inv(t[i]));
        }    
        Prl(get(t,x,h,K + 4,add(a,mul(n,d))));
    }
    return 0;
}
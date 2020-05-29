/*拉格朗日插值
众所周知，n + 1个x坐标不同的点可以确定唯一的最高为n次的多项式。在算法竞赛中，我们常常会碰到一类题目，题目中直接或间接的给出了n+1个点，让我们求由这些点构成的多项式在某一位置的取值
一个最显然的思路就是直接高斯消元求出多项式的系数，但是这样做复杂度巨大(n^3)且根据算法实现不同往往会存在精度问题
而拉格朗日插值法可以在n^2的复杂度内完美解决上述问题
假设该多项式为f(x), 第i个点的坐标为(xi,yi)，我们需要找到该多项式在k点的取值
根据拉格朗日公式可以直接计算
 */
 const int maxn = 2010;
const int INF = 0x3f3f3f3f;
const LL mod = 998244353; 
int N,M,K;
LL x[maxn],y[maxn];
LL quick_power(LL a,LL b,LL Mod){
    LL ans = 1;
    while(b){
        if(b & 1) ans = ans * a % Mod;
        a = a * a % Mod;
        b >>= 1;
    }
    return ans;
}
LL inv(LL a,LL Mod){
    return quick_power(a,Mod - 2,Mod);
}
LL v;
int main(){
    Sca(N); Scl(v);
    for(int i = 1; i <= N ; i ++) scanf("%lld%lld",&x[i],&y[i]);
    LL ans = 0;
    for(int i = 1; i <= N ; i ++){
        LL sum = 1;
        for(int j = 1; j <= N ; j ++){
            if(i != j) sum = sum * (x[i] + mod - x[j]) % mod;
        }
        sum = inv(sum,mod);
        sum = sum * y[i] % mod;
        for(int j = 1; j <= N ; j ++){
            if(i != j) sum = sum * (v - x[j] + mod) % mod;
        }
        ans = (ans + sum) % mod; 
    }
    Prl(ans);
    return 0;
}
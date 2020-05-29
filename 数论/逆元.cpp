//逆元    (a / b) % mod = a * inv(b) % mod
//拓展欧几里得定理求inv(b)
int mod = 1e9 + 7; 
int N;
LL exgcd(LL a,LL b,LL &x,LL &y){
    if(a == 0 && b == 0) return -1;
    if(b == 0){
        x = 1;y = 0;
        return a;
    }
    LL d = exgcd(b,a % b,y,x);
    y -= a / b * x;
    return d;
}
LL inv(LL a,LL n){
    LL x,y;
    LL d = exgcd(a,n,x,y);
    if(d == 1) return (x % n+ n) % n;
    else return -1;
}
int main(){
    scanf("%lld%lld",&N,&mod);
    Prl(inv(N,mod));
    return 0;
}
//当mod为质数时，可以利用费马小定理，b的逆元为n ^ (mod - 2) % mod
int mod = 1e9 + 7; 
int N;
LL quick_power(LL a,LL b){
    LL ans = 1;
    while(b){
        if(b & 1) ans = ans * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return ans;
}
LL inv(LL a,LL n){
    return quick_power(a,n - 2);
}
int main(){
    scanf("%lld%lld",&N,&mod);
    For(i,1,N) Prl(inv(i,mod));
    return 0;
}
//当我们需要求连续一段数在mod p下的逆元的时候，我们可以使用逆元的递推公式
//模板：求1到N的所有逆元
LL mod = 1e9 + 7; 
LL N;
LL inv[maxn];
int main(){
    scanf("%lld%lld",&N,&mod);
    inv[1] = 1;
    for(int i = 2; i <= N; i ++) inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    for(int i = 1; i <= N ; i ++) Prl(inv[i]);
    return 0;
}
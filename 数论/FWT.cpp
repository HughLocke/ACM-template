/* FWT 快速沃尔什变换
给定A,B两个序列,可以通过FWT求出序列C
其中C(i) = ∑A(j)B(k)  (j⊕k = i) ⊕可以为or,and,xor
 */
const int maxn = 2e5 + 10;
const LL mod = 998244353; 
int N,M,K;
LL inv2 = mod + 1 >> 1;
LL a1[maxn],b1[maxn],a2[maxn],b2[maxn],a3[maxn],b3[maxn];
inline LL add(LL a,LL b){return ((a + b) % mod + mod) % mod;}
inline LL mul(LL a,LL b){return (a % mod * b % mod + mod) % mod;}
void FWT_or(int limit,LL *a,int op){
    for(int i = 1; i < limit; i <<= 1){
        for(int p = i << 1,j = 0; j < limit; j += p){
            for(int k = 0; k < i ; k ++){
                if(op == 1) a[i + j + k] = add(a[j + k],a[i + j + k]);
                else a[i + j + k] = add(a[i + j + k],-a[j + k]);
            }
        }
    }
}
void FWT_and(int limit,LL *a,int op){
    for(int i = 1; i < limit; i <<= 1){
        for(int p = i << 1,j = 0; j < limit; j += p){
            for(int k = 0 ; k < i ; k ++){
                if(op == 1) a[j + k] = add(a[j + k],a[i + j + k]);
                else a[j + k] = add(a[j + k],-a[i + j + k]);
            }
        }
    }
}
void FWT_xor(int limit,LL *a,int op){
    for(int i = 1; i < limit; i <<= 1){
        for(int p = i << 1,j = 0;j < limit; j += p){
            for(int k = 0 ; k < i ; k ++){
                LL x = a[j + k],y = a[i + j + k];
                a[j + k] = add(x,y); a[i + j + k] = add(x,-y);
                if(op == -1) a[j + k] = mul(a[j + k],inv2),a[i + j + k] = mul(a[i + j + k],inv2);
            }
        }
    }
}
int main(){
    Sca(N); N = (1 << N); N--;
    for(int i = 0; i <= N ; i ++) Scl(a1[i]),a2[i] = a3[i] = a1[i];
    for(int i = 0; i <= N ; i ++) Scl(b1[i]),b2[i] = b3[i] = b1[i];
    int limit = 1; while(limit <= N) limit <<= 1;
    FWT_or(limit,a1,1); FWT_or(limit,b1,1);
    for(int i = 0 ; i < limit; i ++) a1[i] = mul(a1[i],b1[i]);
    FWT_or(limit,a1,-1);
    
    FWT_and(limit,a2,1); FWT_and(limit,b2,1);
    for(int i = 0 ; i < limit; i ++) a2[i] = mul(a2[i],b2[i]);
    FWT_and(limit,a2,-1);
    
    FWT_xor(limit,a3,1); FWT_xor(limit,b3,1);
    for(int i = 0 ; i < limit; i ++) a3[i] = mul(a3[i],b3[i]);
    FWT_xor(limit,a3,-1);
    
    for(int i = 0; i <= N ; i ++) printf("%lld%c",a1[i],i == N?'\n':' ');
    for(int i = 0; i <= N ; i ++) printf("%lld%c",a2[i],i == N?'\n':' ');
    for(int i = 0; i <= N ; i ++) printf("%lld%c",a3[i],i == N?'\n':' ');
    return 0;
}
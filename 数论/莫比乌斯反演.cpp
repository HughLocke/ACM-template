//莫比乌斯反演
/* 
f(n) = Σg(d) 其中(d|n)
->g(n) = ∑μ(d)f(n / d) 其中(d|n)
或者描述为
f(n) = ∑g(d) 其中(n|d)
->g(n) = ∑μ(d/n) * f(d) 其中(n|d)
*/
/*
μ(d)为莫比乌斯函数，计算方式为
μ(1) = 1 
x = p1 * p2 * p3 ……*pk（x由k个不同的质数组成）则μ(x) = (-1)^k 
其他情况，μ (x) = 0 
μ(d)的常见性质：对于任意正整数n有
1.∑μ(d) (d|n)  在n = 1的时候为1，在n > 1的时候为0
2.∑μ(d)/d = φ(n)/n ，其中(d|n),φ(n)为欧拉函数
 */
//线性筛求莫比乌斯函数 O(n)
const int maxn = 1e6 + 5;
int mu[maxn], vis[maxn], prime[maxn];
int tot;//用来记录prime的个数
void init(){
    mu[1] = 1;
    for(int i = 2; i < maxn; i ++){
        if(!vis[i]){
            prime[tot ++] = i;
            mu[i] = -1;
        }
        for(int j = 0; j < tot && i * prime[j] < maxn; j ++){
            vis[i * prime[j]] = 1;
            if(i % prime[j]) mu[i * prime[j]] = -mu[i];
            else{
                mu[i * prime[j]] = 0;
                break;
            }
        }
    }
}
int main(){
    init();
}
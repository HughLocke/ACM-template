//欧拉函数是求小于等于n的数中与n互质的数的数目
//表示为phi(i) 或者 φ(i)
//求单个欧拉函数 事件负责度sqrt(n)
//欧拉函数
int phi(int x){
    int ans = x;
    for(int i = 2; i*i <= x; i++){
        if(x % i == 0){
            ans = ans / i * (i-1);
            while(x % i == 0) x /= i;
        }
    }
    if(x > 1) ans = ans / x * (x-1);
    return ans;
}
//求连续的欧拉函数
const int N = 1e6+10 ;
int phi[N], prime[N];
int tot;//tot计数，表示prime[N]中有多少质数 
void Euler(){
    phi[1] = 1;
    for(int i = 2; i < N; i ++){
        if(!phi[i]){
            phi[i] = i-1;
            prime[tot ++] = i;
        }
        for(int j = 0; j < tot && 1ll*i*prime[j] < N; j ++){
            if(i % prime[j]) phi[i * prime[j]] = phi[i] * (prime[j]-1);
            else{
                phi[i * prime[j] ] = phi[i] * prime[j];
                break;
            }
        }
    }
}
int main(){
    Euler();
}
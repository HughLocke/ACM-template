//n个方程：x % m[i] = a[i] (0<=i<n)
LL china(int n, LL *a, LL *m){
    LL M = 1, ret = 0;
    for(int i = 0; i < n; i ++) M *= m[i];
    for(int i = 0; i < n; i ++){
        LL w = M / m[i];
        ret = (ret + w * inv(w, m[i]) * a[i]) % M;
    }
    return (ret + M) % M;
}
//m1,m2...mn不保证两两互质的情况
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long LL;
typedef pair<LL, LL> PLL;
PLL linear(LL A[], LL B[], LL M[], int n) {//求解A[i]x = B[i] (mod M[i]),总共n个线性方程组 
    LL x = 0, m = 1;
    for(int i = 0; i < n; i ++) {
        LL a = A[i] * m, b = B[i] - A[i]*x, d = gcd(M[i], a);
        if(b % d != 0)  return PLL(0, -1);//答案不存在，返回-1 
        LL t = b/d * inv(a/d, M[i]/d)%(M[i]/d);
        x = x + m*t;
        m *= M[i]/d;
    }
    x = (x % m + m ) % m;
    return PLL(x, m);//返回的x就是答案，m是最后的lcm值 
}
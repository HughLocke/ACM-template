
//斜率优化dp
/*方法1.
将dp转移方程化成斜率单调递增(减)的y = kx + b形式
其中b是需要被转移的dp[i],x是只与i有关的单调递增的东西，y是由只与i有关或只与j有关的式子
方法2(推荐).
假设在更新i的时候,对于i存在x > y且x比y更优
即dp[x] + fun(x,i) < dp[y] + fun(y,i) 假设求最小值
化为(dp[x] - dp[y]) / (fun(x) - fun(y)) < fun(i)
则fun(i)为斜率,单调队列维护即可。
*/
/*关于最大(小)值
求最大值:上凸包，斜率单调递减
求最小值:下凸包，斜率单调递增
上下凸包在单调队列判断的时候有点区别
*/

/*求dp[i]最小值,斜率单调递增(下凸包)
方法1.
最终状态转移方程 dp[i]+d[i]*sum[j]=dp[j]+pre[j]+d[i]*sum[i-1]-pre[i-1]+c[i]
其中b为dp[i],k为d[i](单调递增),x为sum[j],y为f[j] + pre[j]
其中d[i]*sum[i-1]-pre[i-1]+c[i]和j无关,算dp[i]的时候可以直接算上
方法2. 
设存在x,y对于i使得x > y且x更优
dp[x]+pre[x]-d[i]*sum[x]<dp[y]+pre[y]-d[i]*sum[y]
->(dp[x]+pre[x]-dp[y]-pre[y]) / (sum[x]-sum[y]) < d[i]
*/
//模板是方法1
const int maxn = 1e6 + 10;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7; 
int N,M;
struct Node{
    LL d,w,C;
}node[maxn];
LL dp[maxn],sum[maxn],pre[maxn];
int Q[maxn];
inline double Y(int i){return dp[i] + pre[i];}
inline double X(int i){return sum[i];}
inline double K(int i,int j){return (Y(j) - Y(i)) / (X(j) - X(i));}
int main(){
    Sca(N);
    for(int i = 1; i <= N ; i ++ ){
        scanf("%lld%lld%lld",&node[i].d,&node[i].w,&node[i].C);
        sum[i] = sum[i - 1] + node[i].w;
        pre[i] = pre[i - 1] + node[i].w * node[i].d;
    } 
    int tail = 0,head = 1;  //单调队列有没有初始数字要看题目决定
    for(int i = 1; i <= N ; i ++){
        dp[i] = node[i].d * sum[i - 1] - pre[i - 1] + node[i].C;
        while(tail > head && K(Q[head],Q[head + 1]) < node[i].d) head++; //这行基本一样
        int j = Q[head]; dp[i] = min(dp[j] + pre[j] + (sum[i - 1] - sum[j]) * node[i].d - pre[i - 1] + node[i].C,dp[i]);
        while(tail > head && K(Q[tail - 1],Q[tail]) > K(Q[tail],i)) tail--;  //这行基本一样
        Q[++tail] = i;
    }
    Prl(dp[N]);
    return 0;
}

/*依然是下凸包,模板是方法2
dp[i] = dp[j] + w[j + 1] * h[i];
方法2. 存在x > y且x优于y
dp[x] + w[x + 1] * h[i] < dp[y] + w[y + 1] * h[i];
(dp[x] - dp[y]) / (w[y + 1] - w[x + 1]) < h[i] 
不等式左边为slope,右边为K
 */
const int maxn = 5e4 + 10;
const int INF = 0x3f3f3f3f;
int N,M;
int Q[maxn];
struct node{
    LL w,h;
}a[maxn];
LL dp[maxn];
double slope(int i,int j){return (dp[i] - dp[j]) / (a[j + 1].w - a[i + 1].w);}
double K(int i){return a[i].h;}
bool cmp(node a,node b){
    if(a.w == b.w) return a.h > b.h;
    return a.w > b.w;
}
int main(){
    Sca(N);
    for(int i = 1; i <= N ; i ++) scanf("%lld%lld",&a[i].h,&a[i].w);
    sort(a + 1,a + 1 + N,cmp); int cnt = 1;
    for(int i = 2; i <= N ; i ++){
        if(a[i].h > a[cnt].h) a[++cnt] = a[i];
    }
    N = cnt;
    int tail = 1,head = 1;
    for(int i = 1; i <= N ; i ++){
        while(tail > head && slope(Q[head],Q[head + 1]) <= K(i)) head++;
        int j = Q[head]; dp[i] = dp[j] + a[j + 1].w * a[i].h;
        while(tail > head && slope(Q[tail - 1],Q[tail]) > slope(Q[tail],i)) tail--;
        Q[++tail] = i;
    }
    Prl(dp[N]);
    return 0;
}
/*上凸包(求最大值)
不等式为dp[i] = dp[j] + a * (sum[i] - sum[j])² + b * (sum[i] - sum[j]) + c (a < 0)
方法1.
dp[i] + 2 * a * sum[i] * sum[j] = dp[j] + a * sum[i]² + a * sum[j]² + b * sum[i] - b * sum[j] + c
斜率为单调递减的2 * a * sum[i]
方法2.
(dp[x] + a * sum[x]² - b * sum[x] - dp[y] - a * sum[y]² + b * sum[y]) / (sum[x] - sum[y]) < 2 * a * sum[i]
不等式左边为slope(x,y)
*/
//方法1模板
const int maxn = 1e6 + 10;
int N,M;
LL sum[maxn],x[maxn],dp[maxn];
LL a,b,c;
int Q[maxn];
inline double X(int i){return sum[i];}
inline double Y(int j){return dp[j] + a * sum[j] * sum[j] - b * sum[j];}
inline double K(int i,int j){return (Y(i) - Y(j)) / (X(i) - X(j));}
int main(){
    Sca(N); scanf("%lld%lld%lld",&a,&b,&c);
    for(int i = 1; i <= N ; i ++){
        Scl(x[i]); sum[i] = sum[i - 1] + x[i];
    }
    int head = 1,tail = 1;
    for(int i = 1; i <= N  ; i++){
        while(tail > head && K(Q[head],Q[head + 1]) >= 2 * a * sum[i]) head++;
        int j = Q[head]; dp[i] = Y(j) - 2 * a * sum[i] * sum[j] + a * sum[i] * sum[i] + b * sum[i] + c;
        while(tail > head && K(Q[tail - 1],Q[tail]) < K (Q[tail],i)) tail--;
        Q[++tail] = i;
    }
    Prl(dp[N]);
    return 0;
}
//方法2模板
const int maxn = 1e6 + 10;
int N,M;
LL sum[maxn],x[maxn],dp[maxn];
LL a,b,c;
int Q[maxn];
inline double K(int i){return 2 * a * sum[i];}
inline double slope(int i,int j){return (dp[i] + a * sum[i] * sum[i] - b * sum[i] - dp[j] - a * sum[j] * sum[j] + b * sum[j]) / (sum[i] - sum[j]);}
int main(){
    Sca(N); scanf("%lld%lld%lld",&a,&b,&c);
    for(int i = 1; i <= N ; i ++){
        Scl(x[i]); sum[i] = sum[i - 1] + x[i];
    }
    int head = 1,tail = 1;
    for(int i = 1; i <= N  ; i++){
        while(tail > head && slope(Q[head],Q[head + 1]) > K(i)) head++;
        int j = Q[head]; dp[i] = dp[j] + a * (sum[i] - sum[j]) * (sum[i] - sum[j]) + b * (sum[i] - sum[j]) + c; 
        while(tail > head && slope(Q[tail - 1],Q[tail]) < slope(Q[tail],i)) tail--;
        Q[++tail] = i;
    }
    Prl(dp[N]);
    return 0;
}
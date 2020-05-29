/*KM算法
二分图最大权匹配，时间复杂度O(n³)
1.最大权匹配不一定是最大匹配
2.若要求最小权匹配，就边权取反然后求最大权，将答案取反
3.对于顶标lx[i],ly[i]的理解
lx初始为i点连出去的最大的边权，ly初始为0
可行顶标：在任意时刻，对于任意边(u,v,w)都满足lx[u] + ly[v] >= w
同时，满足lx[u] + ly[v] >= MAP[u][v]约束下的最小顶标和(∑lx + ∑ly)就是最大权匹配
满足lx[u] + ly[v] <= MAP[u][v]约束下的最大顶标和就是最小权匹配
*/
//模板：求最小权匹配
const int maxn = 210;
const LL INF = 1e18;
LL MAP[maxn][maxn];
LL vx[maxn],vy[maxn],lx[maxn],ly[maxn],slack[maxn];
int pre[maxn],Left[maxn],Right[maxn],NL,NR,Nm,N;
void match(int &u){
    for(;u;swap(u,Right[pre[u]])) Left[u] = pre[u];
}
void bfs(int u){
    static int q[maxn],front,rear;
    front = 0; vx[q[rear = 1] = u] = true;
    while(1){
        while(front < rear){
            int u = q[++front];
            for(int v = 1; v <= Nm; v ++){
                int tmp;
                if(vy[v] || (tmp = lx[u] + ly[v] - MAP[u][v]) > slack[v]) continue;
                pre[v] = u;
                if(!tmp){
                    if(!Left[v]) return match(v);
                    vy[v] = vx[q[++rear] = Left[v]] = true;
                }else slack[v] = tmp;
            }
        }
        LL a = INF;
        for(int i = 1; i <= Nm ; i ++)
            if(!vy[i] && a > slack[i]) a = slack[u = i];
        for(int i = 1; i <= Nm ; i ++){
            if(vx[i]) lx[i] -= a;
            if(vy[i]) ly[i] += a;
            else slack[i] -= a;
        }
        if(!Left[u]) return match(u);
        vy[u] = vx[q[++rear] = Left[u]] = true;
    }
}
void solve(){
    for(int i = 1; i <= Nm; i ++){
        for(int j = 1; j <= Nm; j++){
            slack[j] = INF;
            vx[j] = vy[j] = false;
        }
        bfs(i);
    }
}
LL KM(int nl,int nr){
    NL = nl; NR = nr;
    Nm = max(NL,NR);
    for(int i = 1; i <= Nm; i ++){
        lx[i] = -INF; ly[i] = 0;
        pre[i] = Left[i] = Right[i] = 0;
        for(int j = 1; j <= Nm; j ++){
            lx[i] = max(lx[i],MAP[i][j]);
        }
    }
    solve();
    LL ans = 0;
    for(int i = 1; i <= Nm; i ++) ans += lx[i] + ly[i];
    return ans;
}
void output(){ //输出左边和右边匹配的点
    for(int i = 1; i <= NL; i ++){
        printf("%d ",(MAP[i][Right[i]]?Right[i]:0));
    }
    puts("");
}
int main(){
    int T; scanf("%d",&T); int CASE = 1;
    while(T--){
        scanf("%d",&N);
        for(int i = 1; i <= N ; i ++){
            for(int j = 1; j <= N ; j ++){
                scanf("%lld",&MAP[i][j]);
                MAP[i][j] = -MAP[i][j];
            }
        }
        printf("Case #%d: %lld\n",CASE++,-KM(N,N));
    }
    return 0;
}

/*  斯坦纳树
在一张图上寻找一颗边权和最小的生成树将指定的点集合连起来。
最小生成树事实上是斯坦纳树的一种特殊形式
一般给的点集不会过大(n <= 16左右)
求解方式是状压dp,dp[i][1 << k]表示在i点并且已经连起来了state状态的情况下的最小值
更新的状态用两种
1.相同点的两个子状态合并 dp[i][sta] = min(dp[i][sta1] + dp[i][sta2])
2.点与点之间的松弛 dp[i][sta] = min(dp[j][sta] + dis[i][j])
做法
(1)所以我们从小到大枚举状态
(2)先转移第一种：在相同状态下先利用较小的状态更新过来
(2)更新完了之后利用SPFA松弛，注意SPFA不用考虑进阶到下一状态，只要保证当前状态最优就可以了
 */
 //luogoP4294 游览计划
 /*
 题意:给出一张网格图，点权为正代表联通这个点的代价，点权为0代表需要被联通的点集
 求最小联通所有点集中的点的代价以及输出需要被联通的点,输出'x'表示
  */
const int maxn = 12;
const int INF = 0x3f3f3f3f;
int N,M,K;
int MAP[maxn][maxn],id[maxn][maxn];
int dp[maxn][maxn][(1 << 11) + 10];
char ans[maxn][maxn];
struct node{
    int x,y,state,val;
    node(){}
    node(int x,int y,int state,int val = 0):x(x),y(y),state(state),val(val){}
    friend bool operator < (node a,node b){
        return a.val > b.val;
    }
};
node pre[maxn][maxn][(1 << 11) + 10];
const int a[4][2] = {0,1,1,0,0,-1,-1,0};
int cnt = 0;
bool check(int x,int y){
    return 0 <= x && x < N && 0 <= y && y < M;
}
void dfs(int x,int y,int state){
    if(x == N) return;
    if(MAP[x][y]) ans[x][y] = 'o';
    else ans[x][y] = 'x';
    node u = pre[x][y][state];
    dfs(u.x,u.y,u.state);
    if(u.x == x && u.y == y) dfs(u.x,u.y,state - u.state); //说明是两个子集合并更新过来的 
}
queue<PII>Q;
bool vis[maxn][maxn];
int limit;
void SPFA(int state){   //不要去更新下一层，只要把同一state的更新掉就可以了 
    while(!Q.empty()){
        PII u = Q.front(); Q.pop();
        vis[u.fi][u.se] = 0;
        for(int i = 0 ; i < 4; i ++){
            PII h = u;
            h.fi += a[i][0]; h.se += a[i][1];
            if(!check(h.fi,h.se)) continue;
            if(dp[h.fi][h.se][state] > dp[u.fi][u.se][state] + MAP[h.fi][h.se]){
                dp[h.fi][h.se][state] = dp[u.fi][u.se][state] + MAP[h.fi][h.se];
                pre[h.fi][h.se][state] = node(u.fi,u.se,state);
                if(!vis[h.fi][h.se]){
                    Q.push(h);
                    vis[h.fi][h.se] = 1;
                }
            }
        }
    }
}
void solve(){
    for(int i = 0 ; i < N ; i ++){
        for(int j = 0 ; j < M ; j ++){
            if(!MAP[i][j]){
                Pri(dp[i][j][limit]);
                dfs(i,j,limit);
                return;
            }
        }
    }
}
int main(){
    Sca2(N,M); cnt = 0;
    for(int i = 0; i < N ; i ++){
        for(int j = 0; j < M; j ++){
            Sca(MAP[i][j]); ans[i][j] = '_';
            if(!MAP[i][j]) id[i][j] = cnt++;
        }
    }
    limit = (1 << cnt) - 1; //1111111
    //初始化
    for(int i = 0; i < N ; i ++){
        for(int j = 0; j < M ; j ++){
            for(int k = 0 ; k <= limit; k ++) dp[i][j][k] = INF;
            dp[i][j][0] = 0; pre[i][j][0] = node(N,M,-1);
            if(!MAP[i][j]){
                dp[i][j][1 << id[i][j]] = 0;
                pre[i][j][1 << id[i][j]] = node(N,M,-1);
            }
        }
    }
    //状态转移
    for(int state = 0 ; state <= limit; state ++){ //从小到大枚举状态
        for(int i = 0 ; i < N ; i ++){
            for(int j = 0 ; j < M ; j ++){
                for(int sta = state;sta; sta = (sta - 1) & state){    //枚举state的所有子集
                    if(dp[i][j][sta] + dp[i][j][state - sta] - MAP[i][j] < dp[i][j][state]){
                        dp[i][j][state] = dp[i][j][sta] + dp[i][j][state - sta] - MAP[i][j]; //子集间的更新
                        pre[i][j][state] = node(i,j,sta); //因为要输出方案，所以记录前驱
                    } 
                }
                if(dp[i][j][state] < INF){
                    Q.push(mp(i,j));
                    vis[i][j] = 1;
                } 
            }
        }
        SPFA(state); //当前状态全部从子状态更新上来之后SPFA松弛到最优
    } 
    solve();
    for(int i = 0 ; i < N ; i ++){
        for(int j = 0 ; j < M; j ++){
            printf("%c",ans[i][j]);
        }
        puts("");
    }
    return 0;
}
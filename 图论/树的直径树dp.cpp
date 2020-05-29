//树形dp法：记录当前节点最远端的节点和次远端的节点，两遍dfs更新即可
//注：如果是图上直径，可采用两边BFS的方法
const int maxn = 1e5 + 10;
int N,M,K;
struct Edge{
    int to,next,dis;
}edge[maxn * 2];
int head[maxn],tot;
int dp[maxn],dp2[maxn];
void init(){
    for(int i = 0 ; i <= N ; i ++){
        head[i] = -1;
        dp[i] = dp2[i] = 0;
    }
    tot = 0;
}
void add(int u,int v,int w){
    edge[tot].to = v;
    edge[tot].next = head[u];
    edge[tot].dis = w;
    head[u] = tot++;
}
void change(int t,int w){
    if(dp[t] < w){
        dp2[t] = dp[t];
        dp[t] = w;
    }else if(dp2[t] < w){
        dp2[t] = w;
    }
}
void dfs(int t,int la){
    for(int i = head[t]; ~i; i = edge[i].next){
        int v = edge[i].to,w = edge[i].dis;
        if(v == la) continue;
        dfs(v,t);
        change(t,dp[v] + w);
    }
}
void dfs2(int t,int la){
    for(int i = head[t];~i ; i = edge[i].next){
        int v = edge[i].to,w = edge[i].dis;
        if(v == la) continue;
        if(dp[t] == dp[v] + w) change(v,dp2[t] + w);
        else change(v,dp[t] + w);
        dfs2(v,t);
    }
}
int main(){
    int T;
    scanf("%d",&T);
    int CASE = 1;
    while(T--){
        Sca(N); init();
        for(int i = 1; i <= N - 1; i ++){
            int u,v,w; Sca3(u,v,w); u++; v++;
            add(u,v,w); add(v,u,w);
        }
        int root = 1; 
        dfs(root,-1);
        dfs2(root,-1);
        int ans = 0;
        for(int i = 1; i <= N ; i++) ans = max(ans,dp[i] + dp2[i]);
        printf("Case %d: %d\n",CASE++,ans);
    }
    return 0;
}
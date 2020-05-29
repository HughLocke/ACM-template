//Tarjan缩点
/* 1.有向图缩点
将有向图中的所有强连通分量缩成一个点
缩完点之后原图就变成了一个DAG图（有向无环图）
模板例题
    给定一个n个点m条边有向图，每个点有一个权值，求一条路径，使路径经过的点权值之和最大。你只需要求出这个权值和。
允许多次经过一条边或者一个点，但是，重复经过的点，权值只计算一次。
解法：对整个图缩完点之后跑拓扑排序DP一下即可
*/
const int maxn = 1e4 + 10;
const int maxm = 1e5 + 10;
int val[maxn];
int Low[maxn],dfn[maxn],Stack[maxn],Belong[maxn],num[maxn];
int Index,top,scc;
bool Instack[maxn];
void Tarjan(int u){
    int v;
    Low[u] = dfn[u] = ++Index;
    Stack[top++] = u;
    Instack[u] = true;
    for(int i = head[u]; ~i; i = edge[i].next){
        v = edge[i].to;
        if(!dfn[v]){
            Tarjan(v);
            if(Low[u] > Low[v]) Low[u] = Low[v];
        }else if(Instack[v] && Low[u] > dfn[v]) Low[u] = dfn[v];
    }
    if(Low[u] == dfn[u]){
        scc++;
        do{
            v = Stack[--top];
            Instack[v] = false;
            Belong[v] = scc;
            num[scc]++;
        }while(v != u);
    }
}
int VAL[maxn],ind[maxn];
int dp[maxn];
vector<int>P[maxn];
void solve(){
    for(int i = 1; i <= N ; i ++) dfn[i] = Instack[i] = num[i] = 0;
    Index = scc = top = 0;
    for(int i = 1; i <= N ; i ++) if(!dfn[i]) Tarjan(i);   //将原图缩点为DAG图
    for(int i = 1; i <= N ; i ++){                         //建DAG图
        VAL[Belong[i]] += val[i];
        for(int j = head[i]; ~j; j = edge[j].next){
            int v = edge[j].to;
            if(Belong[v] != Belong[i]){
                P[Belong[i]].pb(Belong[v]);
                ind[Belong[v]]++;
            }
        }
    }
    queue<int>Q;
    for(int i = 1; i <= scc;i ++){
        if(!ind[i]) Q.push(i);
        dp[i] = VAL[i];
    } 
    int ans = 0; 
    while(!Q.empty()){            //拓扑排序
        int u = Q.front(); Q.pop();
        ans = max(ans,dp[u]);
        for(int i = 0 ; i < P[u].size(); i ++){
            int v = P[u][i];
            ind[v]--;
            dp[v] = max(dp[v],dp[u] + VAL[v]);
            if(!ind[v]) Q.push(v);
        }
    }
    Pri(ans);
    
}
int main(){
    N = read(); M = read(); init();
    for(int i = 1; i <= N ; i ++) val[i] = read();
    for(int i = 1; i <= M ; i ++){
        int u = read(),v = read();
        add(u,v);
    }
    solve();
    return 0;
}
//2.无向图缩点
//将所有含有无向图环的点缩点，最终形成一棵树
//模板:找一条路使得路上的点权最大，同一个点只能计入一次贡献，要求不能走回头路
//做法:如果成环那么整个环都可以走且可以走回来环的路上，那么缩点形成一棵树之后树形dp
const int maxn = 4e5 + 10;
int N,M,K;
struct Edge{
    int to,next;
}edge[maxn * 2];
int head[maxn],tot;
void init(){
    for(int i = 0 ; i <= N ; i ++) head[i] = -1;
    tot = 0;
}
void add(int u,int v){
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot++;
}
LL w[maxn];
int belong[maxn],cnt;
int dfn[maxn],low[maxn],num;
LL size[maxn],weight[maxn];//size表示缩点后的点内点的数量，weight表示缩点后的点的点权和
int Stack[maxn],top;
bool Instack[maxn];
void tarjan(int u,int la){
    dfn[u] = low[u] = ++num;
    Stack[++top] = u;
    Instack[u] = true;
    int v;
    for(int i = head[u]; ~i; i = edge[i].next){
        v = edge[i].to;
        if(v == la) continue;
        if(!dfn[v]){
            tarjan(v,u);
            low[u] = min(low[u],low[v]);
        }else{
            low[u] = min(low[u],dfn[v]);
        }
    }
    if(low[u] == dfn[u]){
        v = Stack[top];
        ++cnt;
        while(v != u){
            belong[v] = cnt;
            weight[cnt] += w[v];
            size[cnt]++;
            Instack[v] = false;
            v = Stack[--top];
        }
        --top;
        belong[u] = cnt;
        weight[cnt] += w[u];
        size[cnt]++;
        Instack[u] = false;
    }
}
vector<int>P[maxn];
bool vis[maxn],ret[maxn];
LL dp[maxn],dp2[maxn];
void dfs(int u,int la){
    dp2[u] = weight[u];
    for(int i = 0 ; i < P[u].size(); i ++){
        int v = P[u][i];
        if(v != la && !vis[v]){
            vis[v] = 1; dfs(v,u);
            if(ret[v]) ret[u] = 1;
            dp[u] += dp[v];
            dp2[u] += dp[v];
        }    
    }
    if(size[u] > 1) ret[u] = 1;
    if(ret[u]) dp[u] += weight[u];
    LL t = dp2[u];
    for(int i = 0 ; i < P[u].size(); i ++){
        int v = P[u][i];
        if(v == la) continue;
        dp2[u] = max(dp2[u],dp2[v] + t - dp[v]);
    }
}
int main(){
    Sca2(N,M); init();
    for(int i = 1; i <= N ; i ++) Scl(w[i]);    
    for(int i = 1; i <= M ; i ++){
        int u,v; Sca2(u,v); add(u,v); add(v,u);
    }
    for(int i = 1; i <= N ; i ++) if(!dfn[i]) tarjan(i,i);
    for(int u = 1; u <= N ; u ++){
        for(int i = head[u]; ~i; i = edge[i].next){
            int v = edge[i].to;
            if(belong[u] == belong[v]) continue;
            P[belong[u]].push_back(belong[v]);
        }
    }
    int S = read(); vis[belong[S]] = 1;
    dfs(belong[S],-1);
    Prl(dp2[belong[S]]);
    return 0;
}
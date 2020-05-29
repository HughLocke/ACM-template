/*
    有向无环图的最小点路径覆盖
    路径不相交，每个点属于一条路径（路径长度可为0），求最少路径
    一开始最多有n条路径，对于每两个点的合并就会使路径减一
    所以将点i拆为i和i + n两个点，i代表入点，i + n代表出点
    S与入点连边，出点与T连边，容量均为1
    对于每条边u,v,将u与v + N连边，容量均为1
    S到T的最大流就是最多的可合并点，n - maxflow就是最小路径覆盖
    如果要求方案的话，如果u - v + N这条边上有流量，代表这两个点被合并了
*/
//洛谷P2764 求N点M路的最小路径覆盖数量和方案
const int maxn = 410;
const int maxm = 20010;
int N,M,K;
struct Dinic{
    struct Edge{
        int to,next,cap,flow;
        Edge(){}
        Edge(int to,int next,int cap,int flow):to(to),next(next),cap(cap),flow(flow){}
    }edge[maxm * 2];
    int head[maxn],tot,n,s,t;
    int dis[maxn],pre[maxn];
    int nxt[maxn],vis[maxn];
    void init(int n,int s,int t){
        this->n = n; this->s = s; this->t = t;
        for(int i = 0 ; i <= n ; i ++) head[i] = -1;
        tot = 0;
    }
    void add(int u,int v,int w){
        edge[tot] = Edge(v,head[u],w,0);
        head[u] = tot++;
        edge[tot] = Edge(u,head[v],0,0);
        head[v] = tot++;
    }
    bool BFS(){
        for(int i = 0 ; i <= n ; i ++) dis[i] = -1;
        dis[s] = 0;
        queue<int>Q;
        Q.push(s);
        while(!Q.empty()){
            int u = Q.front(); Q.pop();
            for(int i = head[u]; ~i ; i = edge[i].next){
                int v = edge[i].to;
                if(~dis[v] || edge[i].cap <= edge[i].flow) continue;
                dis[v] = dis[u] + 1;
                Q.push(v);
            }
        }
        return ~dis[t];
    }
    int dfs(int u,int a){
        if(u == t || !a) return a;
        int flow = 0;
        for(int& i = pre[u]; ~i ; i = edge[i].next){
            int v = edge[i].to;
            if(dis[v] != dis[u] + 1) continue;
            int f = dfs(v,min(a,edge[i].cap - edge[i].flow));
            if(!f) continue;
            edge[i].flow += f;
            edge[i ^ 1].flow -= f;
            a -= f;
            flow += f;
        }
        return flow;
    }
    int maxflow(int s,int t){
        int flow = 0;
        while(BFS()){
            for(int i = 0 ; i <= n ; i ++) pre[i] = head[i];
            flow += dfs(s,INF);
        }
        return flow;
    }
    int maxflow(){
        return maxflow(s,t);
    }
    void show(){
        for(int i = 1; i <= N ; i ++){
            for(int j = head[i]; ~j; j = edge[j].next){
                int v = edge[j].to;
                if(!edge[j].flow) continue;
                if(1 + N <=v && v <= N + M){
                    nxt[i] = v - N;
                    vis[v - N] = 1;
                    break;
                }
            }
        }
        for(int i = 1; i <= N; i ++){
            if(!vis[i]){
                int t = i;
                while(t){
                    printf("%d ",t);
                    t = nxt[t];
                }
                puts("");
            }
        }
    }
}g; 
int main(){
    Sca2(N,M);
    int S = 2 * N + 1,T = 2 * N + 2;
    g.init(2 * N + 2,S,T);
    for(int i = 1; i <= N ; i ++){
        g.add(S,i,1);
        g.add(i + N,T,1);
    }
    for(int i = 1; i <= M ; i ++){
        int u,v; Sca2(u,v);
        g.add(u,v + N,1);
    }
    int ans = N - g.maxflow();
    g.show();
    Pri(ans);
    return 0;
}
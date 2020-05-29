/*           最小割
最小割边：为了使原点（记为S）和汇点（记为T）不连通，最少要割几条边
最小割 = 最大流，求最大流即可

最小割点
删去最少的点使原图不联通
假设原来的点编号为i，总共有n个点，那么我们就把每个点拆成两个点，编号分别为i和i+n。
其中点i负责连接原图中连入这个点的边，点i+n负责连原图中连出这个点的边。
i和i + n之间有一条容量为1的边，其余边都为INF
删点的过程相当于删去i 到 i + n之间这条容量为1的边，使得其余点都不能通过这个点到其他的点
如果有不能删去的点，就在把i 到 i + n之间的容量变为INF
*/
//模板：求起点到终点的最小割点
const int maxn = 1010;
const int maxm = 3010;
const int INF = 0x3f3f3f3f;
int N,M,K;
struct Dinic{
    struct Edge{
        int to,next,cap,flow;
        Edge(){}
        Edge(int to,int next,int cap,int flow):to(to),next(next),cap(cap),flow(flow){}
    }edge[maxm * 2];
    int head[maxn],tot;
    int pre[maxn],s,t,n,dis[maxn];
    void init(int n){
        this->n = n;
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
        queue<int>Q; Q.push(s);
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
    int DFS(int u,int a){
        if(u == t || !a) return a;
        int flow = 0;
        for(int& i = pre[u]; ~i ; i = edge[i].next){
            int v = edge[i].to;
            if(dis[v] == dis[u] + 1){
                int f = DFS(v,min(a,edge[i].cap - edge[i].flow));
                if(!f) continue;
                flow += f;
                a -= f;
                edge[i].flow += f;
                edge[i ^ 1].flow -= f;
            }
        }
        return flow;
    }
    int maxflow(int s,int t){
        this->s = s; this->t = t;
        int flow = 0;
        while(BFS()){
            for(int i = 0 ; i <= n; i ++) pre[i] = head[i];
            flow += DFS(s,INF);
        }
        return flow;
    }
}g;
int main(){
    Sca2(N,M); g.init(N + N);  
    int S,T; Sca2(S,T);
    for(int i = 1; i <= N ; i ++) g.add(i,i + N,1);
    g.add(S,S + N,INF);
    g.add(T,T + N,INF);
    for(int i = 1; i <= M; i ++){
        int u,v; Sca2(u,v);
        g.add(u + N,v,INF);
        g.add(v + N,u,INF);
    } 
    Pri(g.maxflow(S,T + N));
    return 0;
}
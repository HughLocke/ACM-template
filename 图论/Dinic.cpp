//最大流 dinic算法 N个点M条边求S到T的最大流
//BFS将残余网络分层，DFS在dep[v] = dep[u] + 1的限制下找增广路
//注意：如果dinic写T了，要关注dfs里有没有用cur数组优化
const int maxn = 10010;
const int maxm = 100000; 
const int INF = 0x3f3f3f3f;
int N,M,K;
struct Dinic{
    struct Edge{
        int from,to,next,cap,flow;
        Edge(){}
        Edge(int from,int to,int next,int cap,int flow):from(from),to(to),next(next),cap(cap),flow(flow){}
    }edge[maxm * 2];     //记得 * 2 
    int n,s,t,head[maxn],tot;
    int dep[maxn],cur[maxn];
    void init(int n,int s,int t){
        this->n = n; this->s = s; this->t = t; //记得三个this都要 
        tot = 0;
        for(int i = 0 ; i <= n ; i ++) head[i] = -1;
    }
    inline void AddEdge(int s,int t,int w){
        edge[tot] = Edge(s,t,head[s],w,0);
        head[s] = tot++;
        edge[tot] = Edge(t,s,head[t],0,0);
        head[t] = tot++;
    }
    inline bool BFS(){
        for(int i = 0 ; i <= n ; i ++) dep[i] = -1;
        dep[s] = 1;
        queue<int>Q; Q.push(s);
        while(!Q.empty()){
            int u = Q.front(); Q.pop();
            for(int i = head[u]; ~i ; i = edge[i].next){
                int v = edge[i].to;
                if(~dep[v] || edge[i].flow >= edge[i].cap) continue;
                dep[v] = dep[u] + 1;
                Q.push(v);
            }
         }
         return ~dep[t];
    }
    inline int DFS(const int& u,int a){
        if(u == t || !a) return a;
        int flow = 0;
        for(int &i = cur[u]; ~i ; i = edge[i].next){
            int v = edge[i].to;
            if(dep[v] != dep[u] + 1) continue;
            int f = DFS(v,min(a,edge[i].cap - edge[i].flow));
            if(!f) continue;
            edge[i ^ 1].flow -= f;
            edge[i].flow += f; 
            a -= f;
            flow += f;
        }
        return flow;
    }
    inline int maxflow(){
        return maxflow(s,t);
    }
    inline int maxflow(int s,int t){
        int flow = 0;
        while(BFS()){
            for(int i = 0; i <= n ; i ++) cur[i] = head[i];
            flow += DFS(s,INF);
        }
        return flow;
    }
}g;
int main(){
    int S,T;
    Sca2(N,M); Sca2(S,T);
    g.init(N,S,T);
    while(M--){
        int u,v,w; Sca3(u,v,w);
        g.AddEdge(u,v,w);
    }
    Pri(g.maxflow());
    return 0;
}
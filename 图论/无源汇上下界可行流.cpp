//无源汇上下界可行流
/*
模型:一个网络,求出一个流,使得每条边的流量必须>=Li且<=Hi,每个点必须满足总流入量=总流出量(流量守恒)(这个流的特点是循环往复,无始无终).
求解方法：1.以每条边的最低容量形成一个初始流（不一定平衡）
2.求出初始流中每个点进入流量和输出流量的差
3.开始建图(附加流)：建立一个源点和汇点，原图上所有边建立一条容量为Hi - Li的边，a[i]表示初始流中输入流量-输出流量,如果a[i] > 0,
则将i向汇点连容量为a[i]的边，如果a[i] < 0则源点向i连容量为a[i]的边
4.可以证明所有a[i]之和相等，因此在原图上跑最大流，如果最大流与正数a[i]之和相等(即满流)则说明有解，解就是
附加流上的流量加上初始流的流量
 */
const int maxn = 210;
const int maxm = 11010;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7; 
int N,M,K;
struct E{
    int u,v,l,r;
}e[maxm];
int F[maxm];
int a[maxn];
struct dinic{
    struct Edge{
        int to,next,flow,cap,id;
        Edge(){}
        Edge(int to,int next,int flow, int cap,int id):
            to(to),next(next),flow(flow),cap(cap),id(id){}
    }edge[maxm * 2];
    int head[maxn],tot;
    int s,n,t,cur[maxn],dep[maxn];
    void init(int n,int s,int t){
        this->n = n; this->s = s; this->t = t;
        for(int i = 0 ; i <= n ; i ++) head[i] = -1;
        tot = 0;
    }
    void add(int u,int v,int w,int id){
        edge[tot] = Edge(v,head[u],0,w,id);
        head[u] = tot++;
        edge[tot] = Edge(u,head[v],0,0,id);
        head[v] = tot++; 
    }
    inline bool bfs(){
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
    inline int dfs(const int &u,int a){
        if(u == t || !a) return a;
        int flow = 0;
        for(int &i = cur[u]; ~i ; i = edge[i].next){
            int v = edge[i].to;
            if(dep[v] != dep[u] + 1) continue;
            int f = dfs(v,min(a,edge[i].cap - edge[i].flow));
            flow += f;
            a -= f;
            edge[i].flow += f;
            edge[i ^ 1].flow -= f;
        }
        return flow;
    }
    int maxflow(){
        return maxflow(s,t);
    }
    int maxflow(int s,int t){
        int flow = 0;
        while(bfs()){
            for(int i = 0 ; i <= n ; i ++) cur[i] = head[i];
            flow += dfs(s,INF);
        }
        return flow;
    }
    void solve(){
        for(int i = 0 ; i <= n ; i ++){
            for(int j = head[i]; ~j; j = edge[j].next){
                if(edge[j].flow > 0) F[edge[j].id] += edge[j].flow;
            }
        }
    }
}g;
int main(){
    Sca2(N,M);
    int S = N + 1,T = N + 2;
    g.init(N + 2,S,T);
    for(int i = 1; i <= M ; i ++){
        scanf("%d%d%d%d",&e[i].u,&e[i].v,&e[i].l,&e[i].r);
        a[e[i].u] += e[i].l; a[e[i].v] -= e[i].l;    //a[i]表示初始流在这个点入流量和出流量的差
        g.add(e[i].u,e[i].v,e[i].r - e[i].l,i);      //在附加流上建边
    }
    int sum = 0;
    for(int i = 1; i <= N ; i ++){
        if(a[i] > 0){
            g.add(i,T,a[i],0);                 
            sum += a[i];             //表示汇出的总流量
        } 
        if(a[i] < 0) g.add(S,i,-a[i],0);
    }
    if(g.maxflow() != sum) puts("NO");   //不满流则无解
    else{
        g.solve(); 
        puts("YES");
        for(int i = 1; i <= M; i ++){
            Pri(e[i].l + F[i]);
        }
    }
    return 0;
}
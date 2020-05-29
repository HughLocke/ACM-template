//最小费用最大流
/*
    不断寻找费用最小的增广路，贪心的使得每一条找到的增广路都是当前残余网络下费用最小的路径
    最终寻找到流量最大前提下费用最小的路
*/
//模板 N点M边求S到T的最小费用最大流
const int maxn = 5010;
const int maxm = 50010;
const int INF = 0x3f3f3f3f;
int N,M,K;
struct Mcmf{
    struct Edge{
        int to,next,cap,flow,cost;
        Edge(){}
        Edge(int to,int next,int cap,int flow,int cost):to(to),next(next),cap(cap),flow(flow),cost(cost){}
    }edge[maxm * 2];
    int n,head[maxn],tot;
    int pre[maxn],dis[maxn],vis[maxn];
    void init(int n){
        this->n = n;
        tot = 0;
        for(int i = 0 ; i <= n ; i ++) head[i] = -1;
    }
    void add(int u,int v,int cap,int cost){
        edge[tot] = Edge(v,head[u],cap,0,cost);
        head[u] = tot++;
        edge[tot] = Edge(u,head[v],0,0,-cost);
        head[v] = tot++;
    }
    bool spfa(int s,int t){
        for(int i = 0 ; i <= n ; i ++){
            vis[i] = 0;
            dis[i] = INF;
            pre[i] = -1;
        }
        dis[s] = 0;
        queue<int>Q; Q.push(s);
        while(!Q.empty()){
            int u = Q.front(); Q.pop();
            vis[u] = 0;
            for(int i = head[u]; ~i; i = edge[i].next){
                int v = edge[i].to;
                if(edge[i].cap - edge[i].flow > 0 && dis[v] > dis[u] + edge[i].cost){
                    dis[v] = dis[u] + edge[i].cost;
                    pre[v] = i;
                    if(!vis[v]){
                        vis[v] = 1;
                        Q.push(v);
                    }
                }
            }
        }
        return ~pre[t];
    }
    int mcmf(int s,int t,int &cost){
        int flow = 0;
        cost = 0;
        while(spfa(s,t)){
            int Min = INF;
            for(int i = pre[t]; ~i ; i = pre[edge[i ^ 1].to]){
                Min = min(Min,edge[i].cap - edge[i].flow);
            }
            flow += Min;
            for(int i = pre[t]; ~i ; i = pre[edge[i ^ 1].to]){
                edge[i].flow += Min;
                edge[i ^ 1].flow -= Min;
                cost += Min * edge[i].cost;
            }
        }
        return flow; 
    }
}g;
int main(){
    int S,T;
    scanf("%d%d%d%d",&N,&M,&S,&T);
      g.init(N);
    for(int i = 1; i <= M ; i ++){
        int u,v,cap,cost;
        scanf("%d%d%d%d",&u,&v,&cap,&cost);
        g.add(u,v,cap,cost);
    }  
    int maxflow,cost;
    maxflow = g.mcmf(S,T,cost);
    printf("%d %d",maxflow,cost);
    return 0;
}
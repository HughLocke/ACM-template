/*      最大权闭合子图
对于一个图而言，如果一个子图中所有点都满足这个点的后继点都在子图内，这就是一个闭合子图
满足点权和最大的闭合子图就是最大权闭合子图
例如有一些实验，完成一个实验需要有一些器材，实验会赚钱器材会花钱，
寻找一个最赚钱的买器材做实验的方案，答案就是最大权闭合子图的总和
做实验赚钱的点权为正，指向那些需要的器材，器材点权为负
最大权闭合子图的解法：
建立源点S连接到所有正点权上，容量为点权值
建立汇点T被所有负点权连接，容量大小为点权值取绝对值
原本的点之间的边照样建，容量为INF
然后答案就是所有正权值的和 - S到T的最大流

理解：假设一开始就把所有的实验经费都收入囊中，然后我们需要放弃一些来满足调节。
要么选择不做这个实验，要么选择购买这些器材，使得满足条件的最小花费就是这个图的最小割

方案：在跑完最大流之后的残余网络中，依然和源点S相连的所有点就是必须选择的器材和必须做的实验
*/
//例题洛谷 P 2762：跑一个图中的最大权闭合子图并输出方案
//1 - N为正权点，N + 1 - N + M为负权点
const int maxn = 1010;
const int maxm = 10010;
const int INF = 0x3f3f3f3f;
int N,M,K;
int vis[maxn];
struct Dinic{
    struct Edge{
        int to,next,cap,flow;
        Edge(){}
        Edge(int to,int next,int cap,int flow):to(to),next(next),cap(cap),flow(flow){}
    }edge[maxn * 2];
    int head[maxn],dis[maxn],tot,pre[maxn];
    int n,s,t;
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
        queue<int>Q;
        dis[s] = 1; Q.push(s);
        while(!Q.empty()){
            int u = Q.front(); Q.pop();
            for(int i = head[u]; ~i; i = edge[i].next){
                int v = edge[i].to;
                if(~dis[v] || edge[i].cap <= edge[i].flow) continue;
                dis[v] = dis[u] + 1; Q.push(v);
            }
        }
        return ~dis[t];
    }
    int dfs(int u,int a){
        if(u == t || !a) return a;
        int flow = 0;
        for(int& i = pre[u]; ~i; i = edge[i].next){
            int v = edge[i].to;
            if(dis[v] != dis[u] + 1) continue;
            int f = dfs(v,min(edge[i].cap - edge[i].flow,a));
            if(!f) continue;
            edge[i].flow += f;
            edge[i ^ 1].flow -= f;
            flow += f;
            a -= f;
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
    int maxflow(){return maxflow(s,t);}
    void show(int t){
        vis[t] = 1;
        for(int i = head[t]; ~i ; i = edge[i].next){
            int v = edge[i].to;
            if(vis[v] || edge[i].cap <= edge[i].flow) continue;
            show(v);
        }
    }
}g;
int main(){
    cin >> N >> M; getchar();
    int s = N + M + 1,t = N + M + 2;
    g.init(N + M + 2,s,t);
    int sum = 0;
    for(int i = 1; i <= N ; i ++){
        int x; Sca(x);
        sum += x;
        g.add(s,i,x);
        while(1){
            char c;
            scanf("%d%c",&x,&c);
            g.add(i,x + N,INF);
            if(c == '\n' || c == '\r') break;
        }
    }
    for(int i = 1; i <= M ; i ++){
        int x; Sca(x); 
        g.add(i + N,t,x);
    }    
    int p = g.maxflow();
    g.show(s);                  //找一下那些点被选中了 
    for(int i = 1; i <= N ; i++){
        if(vis[i]) printf("%d ",i);            //输出与S相连的正权点 
    }
    puts("");
    for(int i = 1 + N; i <= M + N ; i ++){      //输出与T相连的负权点 
        if(vis[i]) printf("%d ",i - N);
    }
    puts("");
    Pri(sum - p);
    return 0;
}
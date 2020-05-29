//树的直径：树上最长长度的链被称作树的直径，求树直径长度的方法有双dfs法和树dp法
//一个有用的结论：从树上任意一个点出发到达的最远的点一定是这棵树的直径的一个端点（距离较长的那一个）。
//双dfs:任选一个点寻找出距离他最远的点a，然后以a为起点寻找出距离他最远的点b,ab距离为树的直径
const int maxn = 1e5 + 10;
int N,M,K;
struct Edge{
    int to,next,dis;
}edge[maxn * 2];
int head[maxn],tot;
int dis[maxn];
void init(){
    for(int i = 0 ; i <= N ; i ++) head[i] = -1;
    tot = 0;
}
void add(int u,int v,int w){
    edge[tot].to = v;
    edge[tot].next = head[u];
    edge[tot].dis = w;
    head[u] = tot++;
}
void dfs(int t,int la){
    for(int i = head[t]; ~i; i = edge[i].next){
        int v = edge[i].to;
        if(v == la) continue;
        dis[v] = dis[t] + edge[i].dis;
        dfs(v,t);
    }
}
int main(){
    int T;
    scanf("%d",&T);
    int CASE = 1;
    while(T--){
        Sca(N); init();
        for(int i = 1; i <= N - 1; i ++){
            int u,v,w; Sca3(u,v,w);
            add(u,v,w); add(v,u,w);
        }
        int root = 1; 
        dis[root] = 0; dfs(root,-1);
        for(int i = 1; i <= N ; i ++) if(dis[root] < dis[i]) root = i;
        dis[root] = 0; dfs(root,-1);
        for(int i = 1; i <= N ; i ++) if(dis[root] < dis[i]) root = i;
        printf("Case %d: ",CASE++);
        Pri(dis[root]);
    }
    return 0;
}
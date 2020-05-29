//树的重心：删除该点之后，使得形成的多棵树中节点数最大值最小。
//模板：求树的所有重心从小到达以此输出
const int maxn = 5e4 + 10;
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
int size[maxn],ans,weight[maxn];
void dfs(int t,int la){
    size[t] = 1;
    int heavy = 0;
    for(int i = head[t]; ~i; i = edge[i].next){
        int y = edge[i].to;
        if(y == la) continue;
        dfs(y,t);
        size[t] += size[y];
        heavy = max(heavy,size[y]); 
    }
    heavy = max(heavy,N - size[t]);
    weight[t] = heavy;
    ans = min(ans,heavy);
}
int main(){
    Sca(N); init(); ans = INF;
    for(int i = 1; i <= N - 1; i ++){
        int u,v; Sca2(u,v);
        add(u,v); add(v,u);
    }
    int root = 1;
    dfs(root,-1);
    for(int i = 1; i <= N ; i ++){
        if(ans == weight[i]){
            printf("%d ",i);
        }
    }
    return 0;
}
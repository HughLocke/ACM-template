/* dsu on tree 启发式合并
nlogn时间处理一类静态无修的子树信息查询问题
通常暴力是每个结点下的子树dfs一遍，时间复杂度n²
像树剖一样处理出每个子树下的重子树，从上往下dfs的时候重子树的信息就可以选择保留
具体步骤：
1.递归所有u的轻点，目的在于计算出他们的答案，不保留贡献
2.递归u的重点，除了计算答案之外还保留贡献
3.再次递归u的轻点，目的在于计算贡献
*/
//模板:每个节点有个颜色，一个子树中颜色节点最多的颜色占领整个子树，问所有子树被占领的颜色编号和（由于节点数有并列，所以是颜色编号和）
const int maxn = 1e5 + 10;
int N,M,K;
LL color[maxn];
struct Edge{
    int to,next;
}edge[maxn * 2];
int head[maxn],tot;
void init(){
    for(int i = 1; i <= N ; i ++) head[i] = -1;
    tot = 0;
}
void add(int u,int v){
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot++;
}
int cnt[maxn];
int fa[maxn],son[maxn],size[maxn];
void dfs1(int t,int la){
    fa[t] = la; son[t] = 0;
    size[t] = 1;
    int heavy = 0;
    for(int i = head[t]; ~i ; i = edge[i].next){
        int v = edge[i].to;
        if(v == la) continue;
        dfs1(v,t);
        if(size[v] > heavy){
            son[t] = v;
            heavy = size[v];
        }
        size[t] += size[v];
    }
}
LL Max,ans[maxn],sum;
void dfs2(int t,int isson,int keep){
    if(keep){
        for(int i = head[t]; ~i ; i = edge[i].next){
            int v = edge[i].to;
            if(v == son[t] || v == fa[t]) continue;
            dfs2(v,0,1);
        }
    }
    if(son[t]) dfs2(son[t],1,keep);
    for(int i = head[t]; ~i ; i = edge[i].next){
        int v = edge[i].to;
        if(v == son[t] || v == fa[t]) continue;
        dfs2(v,0,0);
    }
    cnt[color[t]]++;
    if(cnt[color[t]] > Max) sum = color[t],Max = cnt[color[t]];
    else if(cnt[color[t]] == Max) sum += color[t];
    if(keep) ans[t] = sum;
    if(keep && !isson){
         for(int i = 1; i <= N; i ++) cnt[i] = 0;
         Max = sum = 0;
    }
}
int main(){
    Sca(N); init();
    for(int i = 1; i <= N ; i ++) Scl(color[i]);
    for(int i = 1; i < N ; i ++){
        int u,v; Sca2(u,v);
        add(u,v); add(v,u);
    }
    dfs1(1,0); dfs2(1,1,1);
    for(int i = 1; i <= N ; i ++){
        printf("%lld ",ans[i]);
    }
    return 0;
}
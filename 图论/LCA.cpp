//倍增lca
//注：如果动态建树的话，dfs函数非必要，建树的同时维护稀疏表即可
const int SP = 20; //(1 << SP)为这棵树最多的深度
int pa[maxn][SP],dep[maxn];
void init(){
    Mem(head, -1);
    tot = 0;
}
void dfs(int u, int fa){
    pa[u][0] = fa; dep[u] = dep[fa] + 1;
    for(int i = 1; i < SP; i ++) pa[u][i] = pa[pa[u][i - 1]][i - 1];
    for (int i = head[u]; ~i; i = edge[i].next){
        int v = edge[i].to;
        if (v == fa) continue;
        dfs(v, u);
    }
}
int lca(int u, int v){
    if (dep[u] < dep[v]) swap(u, v);
    int t = dep[u] - dep[v];
    for(int i = 0 ; i < SP; i ++) if (t & (1 << i)) u = pa[u][i];
    for(int i = SP - 1; i >= 0 ; i --){
        int uu = pa[u][i], vv = pa[v][i];
        if (uu != vv){
            u = uu;
            v = vv;
        }
    }
    return u == v ? u : pa[u][0];
}
/*    树上差分
    用来解决一系列将树链上的点权或者边权加上一个数，最后询问每个点的点权（边的边权）的操作
    如果是点权，对于u到v这条树链上的点权全部加上w，
    就进行val[u] += w; val[v] += w; val[lca(u,v)] -= w; val[fa[lca(u,v)]] -= w;
    最后求子树和的操作，每个数的子树和就是我们要的点权
    如果是边权，就将边都转为两端深度较深的那个点，u到v的边权加上w，就是
    val[u] += w; val[v] += w; val[lca(u,v)] -= 2 * w;
    最后同样求一个子树和的操作即可。
*/
//模板 点权的差分

int val[maxn];
void dfs2(int u,int la){
    for(int i = head[u]; ~i; i = edge[i].next){
        int v = edge[i].to;
        if(v == la) continue;
        dfs2(v,u);
        val[u] += val[v];
    }
}
int main(){
    Sca(N); init();
    for(int i = 1; i <= N ; i ++) Sca(a[i]);
    for(int i = 1; i <= N - 1; i ++){
        int u,v; Sca2(u,v);
        add(u,v); add(v,u);
    }
    dfs(1,0);   //是lca里的dfs
    for(int i = 1; i < N ; i ++){
        int u = a[i],v = a[i + 1];
        val[u]++;val[v]++;
        int l = lca(u,v); 
        val[l]--; val[fa[l][0]]--;
    }
    dfs2(1,0);
    for(int i = 1; i <= N ; i ++) Pri(val[i]);
    return 0;
}

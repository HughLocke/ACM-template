/*    树上点分治
    处理树链端点之间的关系，例如树上是否存在距离k的点对，或者树链点权相加小于等于K的个数之类
    核心思想是
    (1)找到树的重心
    (2)求这个重心的子树之间互相是否形成满足题意的条件（子树与子树之间，操作的是经过根节点的那条链）
    (3)遍历所有子树，将子树当成独立的树之后每棵树重复(1)
*/
//例题：洛谷P2634 寻找一棵树上有多少点之间的距离为3的的倍数（T），以及不是3的倍数(F) 求T / (F + T)的最简分数
int root,max_part,SUM;
int size[maxn];
void dfs_root(int u,int la){
    size[u] = 1;int heavy = 0;
    for(int i = head[u]; ~i ; i = edge[i].next){
        int v = edge[i].to;
        if(v == la || vis[v]) continue;
        dfs_root(v,u);
        heavy = max(heavy,size[v]);
        size[u] += size[v];
    }
    if(max_part > max(heavy,SUM - heavy)){
        max_part = max(heavy,SUM - heavy);
        root = u;
    }
}
int judge[5],dis[5];
void dfs_dis(int t,int la,int d){
    dis[d]++;
    for(int i = head[t]; ~i; i = edge[i].next){
        int v = edge[i].to;
        if(vis[v] || v == la) continue;
        dfs_dis(v,t,(d + edge[i].dis) % 3);
    }
}
void work(int t){
    judge[0]++;
    for(int i = head[t]; ~i; i = edge[i].next){
        int v = edge[i].to;
        if(vis[v]) continue;
        dfs_dis(v,t,edge[i].dis);
        for(int k = 0 ; k < 3; k ++){
            for(int j = 0 ; j < 3; j ++){
                if((k + j) % 3 == 0){
                    T += dis[k] * judge[j];
                }else{
                    F += dis[k] * judge[j];
                }
            }
        }
        for(int k = 0 ; k < 3; k ++){
            judge[k] += dis[k];
            dis[k] = 0;
        }
    }
    for(int i = 0 ; i < 3; i ++) judge[i] = 0;
}
void divide(int t){
    max_part = INF,root = t;
    dfs_root(t,-1);
    vis[root] = 1;
    work(root);
    for(int i = head[root]; ~i ; i = edge[i].next){
        int v = edge[i].to;
        if(vis[v]) continue;
        SUM = size[v];
        divide(v);
    }    
}
int gcd(int a,int b){
    return !b?a:gcd(b,a % b);
}
int main(){
    Sca(N); init();
    for(int i = 1; i <= N - 1; i ++){
        int u,v,w; Sca3(u,v,w);
        w %= 3;
        add(u,v,w); add(v,u,w);
    }
    SUM = N;divide(1);
    T <<= 1; F <<= 1;
    T += N;//cout << T << "  " << F + T << endl;
    LL GCD = gcd(T,T + F);
    printf("%lld/%lld",T / GCD,(T + F) / GCD);
    return 0;
}
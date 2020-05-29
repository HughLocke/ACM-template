//树上莫队
/* 查询树链的关系
求出树的欧拉序,将树链关系转化为序列关系
对于不同的子树上的两点而言，序列上前一个的ed到后一个的st包含的所有只出现一次的结点就是树链上的结点。
但是lca不包含在内，因此要特判lca
*/
//查询树链上不同颜色的种数
const int maxn = 4e5 + 10;
const int maxm = 4e5 + 10;
const int SP = 20;
int fa[maxn][SP],dep[maxn]; 
int N,M,K,unit;
struct Edge{
    int to,next;
}edge[maxn * 2]; 
int head[maxn],tot;
void init(){
    for(int i = 0; i <= N ; i ++) head[i] = -1;
    tot = 0;
}
void add(int u,int v){
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot++;
}
int idx[maxn],cnt;
PII pos[maxn];
int ans[maxn],b[maxn],a[maxn];
void dfs(int u,int la){
    fa[u][0] = la;
    dep[u] = dep[la] + 1;
    for(int i = 1; i < SP; i ++) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    idx[++cnt] = u; a[cnt] = b[u];
    pos[u].fi = cnt;
    for(int i = head[u]; ~i ; i = edge[i].next){
        int v = edge[i].to;
        if(v == la) continue;
        dfs(v,u);
    }
    idx[++cnt] = u; a[cnt] = b[u];
    pos[u].se = cnt;
}
int lca(int u,int v){
    if(dep[u] < dep[v]) swap(u,v);
    int t = dep[u] - dep[v];
    for(int i = 0 ; i < SP; i ++) if(t & (1 << i)) u = fa[u][i];
    for(int i = SP - 1; i >= 0 ; i --){
        int uu = fa[u][i],vv = fa[v][i];
        if(uu != vv){
            u = uu;
            v = vv;
        }
    }
    return u == v? u : fa[u][0];
}
struct Query{
    int l,r,t;
    int L,R;
    int lc;  //特判lca    
}node[maxm];
bool cmp(Query a,Query b){
    if(a.l != b.l) return a.l < b.l;
    return a.r < b.r;
}
int num[maxm],sum,vis[maxn];
void add(int p){
    num[p]++;
    sum += (num[p] == 1);
}
void del(int p){
    num[p]--;
    sum -= (num[p] == 0);
}
void work(int t){
    if(vis[t]) del(b[t]);
    else add(b[t]);
    vis[t] ^= 1;
}
void solve(){
    int L = 1,R = 0;
    sum = 0;
    for(int i = 1; i <= M ; i ++){
        while(R < node[i].R) work(idx[++R]);
        while(R > node[i].R) work(idx[R--]);
        while(L < node[i].L) work(idx[L++]);
        while(L > node[i].L) work(idx[--L]);
        if(node[i].lc) work(node[i].lc);
        ans[node[i].t] = sum ;
        if(node[i].lc) work(node[i].lc);
    }
}
int Hash[maxn];
int main(){
    Sca2(N,M); init(); cnt = 0;
    for(int i = 1; i <= N ; i ++) Hash[i] = b[i] = read();
    sort(Hash + 1,Hash + 1 + N);
    int c = unique(Hash + 1,Hash + 1 + N) - Hash;
    for(int i = 1; i <= N ; i ++) b[i] = lower_bound(Hash + 1,Hash + 1 + c,b[i]) - Hash;
    for(int i = 1; i <= N - 1 ; i ++){
        int u,v; Sca2(u,v);
        add(u,v); add(v,u);
    }
    dfs(1,-1); unit = (int)sqrt(cnt);
    for(int i = 1; i <= M ; i ++){
        int u = read(),v = read();
        if(pos[u].fi > pos[v].fi) swap(u,v);
        node[i].lc = lca(u,v);
        node[i].L = pos[u].se; node[i].R = pos[v].fi;
        if(node[i].lc == u){    //如果u是v的祖先,就不用特判lca 
            node[i].L = pos[u].fi;
            node[i].lc = 0;
        } 
        node[i].l = node[i].L / unit; node[i].r = node[i].R / unit;
        node[i].t = i; 
    }
    sort(node + 1,node + 1 + M,cmp);
    solve();
    for(int i = 1; i <= M ; i ++) Pri(ans[i]);
    return 0;
}

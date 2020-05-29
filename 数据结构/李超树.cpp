/* 李超线段树
用来维护二维平面上很多条线段(直线)在x = x0上的最值问题
定义：
1.永久化标记：即线段树标记不删除，每个结点维护的也不一定是最优的信息，需要查询的时候一路统计标记达到最优
2.优势线段：李超树每个节点含有一个优势线段，意为完全覆盖当前区间且在当前区间mid处相比于其他该位置线段最大(小)的线段，李超树的id记录的即为当前的优势线段
3.核心思想：假设维护最大值，每次插入线段时，如果斜率较大的线段为优势线段，则斜率较小的线段只有在左子树才有机会比优势线段大
如果斜率较小的线段为优势线段，则较大的线段只有在右子树才能翻盘
修改(log(n))²(但是常数不大),查询log(n),
*/
/* 模板
操作1.增加一条斜率为P,起始点为S的直线
操作2.询问k点上所有直线的最大值
*/
const int maxn = 5e4 + 10;
int N,M,K;
struct Tree{
    int l,r;
    double S,P;  //P为斜率,S为初始值 
}tree[maxn << 2];
void Build(int t,int l,int r){
    tree[t].l = l; tree[t].r = r;
    tree[t].S = tree[t].P = 0;
    if(l == r) return;
    int m = l + r >> 1;
    Build(t << 1,l,m); Build(t << 1 | 1,m + 1,r);
}
void update(int t,double S,double P){
    int mid = tree[t].l + tree[t].r >> 1;
    if(P > tree[t].P) swap(tree[t].P,P), swap(tree[t].S,S);
    if(S + P * mid < tree[t].S + tree[t].P * mid){ //斜率大的更大就用小的更新左边 
        if(tree[t].l == tree[t].r) return;
        update(t << 1,S,P);
    }else{                                      //否则用大的更新右边 
        swap(tree[t].P,P); swap(tree[t].S,S);
        if(tree[t].l == tree[t].r) return;
        update(t << 1 | 1,S,P);
    }
}
double ans;
void query(int t,int k){
    int mid = tree[t].l + tree[t].r >> 1;
    ans = max(ans,k * tree[t].P + tree[t].S);
    if(tree[t].l == tree[t].r) return ;
    if(k <= mid) query(t << 1,k);
    else query(t << 1 | 1,k);
}
char op[10];
int main(){
    Sca(N);
    Build(1,1,50000);
    for(int i = 1; i <= N ; i ++){
        scanf("%s",op);
        if(op[0] == 'Q'){
            ans = 0;
            query(1,read());
            Pri((int)(ans / 100));
        }else{
            double S,P; scanf("%lf%lf",&S,&P);
            S -= P;
            update(1,S,P);
        }
    } 
    return 0;
}
//模板2
//1.加入x1,y1,x2,y2为端点的线段
//2.查询k点最大值
//注意x1,x2相同的时候需要特判
const int maxn = 4e4 + 10;
const int maxm = 1e5 + 10;
int N,M,K;
double S[maxm],P[maxm];
struct Tree{
    int l,r;
    int id;
}tree[maxn << 2];
void Build(int t,int l,int r){
    tree[t].l = l; tree[t].r = r;
    tree[t].id = 0;
    if(l == r) return;
    int m = l + r >> 1;
    Build(t << 1,l,m);
    Build(t << 1 | 1,m + 1,r);
}
bool dcmp(double a){
    return fabs(a) > eps;
}
void update(int t,int l,int r,int id){
    int m = (tree[t].l + tree[t].r) >> 1;
    if(l <= tree[t].l && tree[t].r <= r){
        int &a = id;
        int &b = tree[t].id;
        if(P[a] > P[b]) swap(a,b);
        if(m * P[a] + S[a] > m * P[b] + S[b] || (!dcmp(m * P[a] + S[a] - m * P[b] + S[b]) && a < b)){
            swap(a,b);
            if(tree[t].l == tree[t].r) return;
            update(t << 1 | 1,l,r,id);
        }else{
            if(tree[t].l == tree[t].r) return;
            update(t << 1,l,r,id);
        }
        return;
    }
    if(r <= m) update(t << 1,l,r,id);
    else if(l > m) update(t << 1 | 1,l,r,id);
    else{
        update(t << 1,l,m,id);
        update(t << 1 | 1,m + 1,r,id);
    }
}
int Id;
void query(int t,int k){
    int a = tree[t].id;
    double Ans = P[Id] * k + S[Id];
    if(Ans < P[a] * k + S[a] || (!dcmp(Ans - P[a] * k - S[a]) && Id > a)){
        Id = a;
    }
    if(tree[t].l == tree[t].r) return;
    int m = (tree[t].l + tree[t].r) >> 1;
    if(k <= m) query(t << 1,k);
    else query(t << 1 | 1,k);
}
int main(){
    Sca(N); Id = 0; int tot = 0;
    Build(1,1,40000);
    for(int i = 1; i <= N ; i ++){
        int op = read();
        if(!op){
            int k = (read() + Id - 1) % 39989 + 1;
            Id = 0; query(1,k);
            Pri(Id);
        }else{
            int x0 = (read() + Id - 1) % 39989 + 1;
            int y0 = (read() + Id - 1) % 1000000000 + 1;
            int x1 = (read() + Id - 1) % 39989 + 1;
            int y1 = (read() + Id - 1) % 1000000000 + 1;
            tot++;
            if(x0 == x1){
                P[tot] = 0;
                S[tot] = max(y1,y0);
            }else{
                P[tot] = 1.0 * (y1 - y0) / (x1 - x0);
                S[tot] = y1 - x1 * P[tot];    
            }
            update(1,min(x0,x1),max(x0,x1),tot);
        }
    }
    return 0;
}
//模板3
/*
题意：树链上每个点添加形如a * dis + b的值的一个点，每次查询树链上最小点
树链剖分 + 李超树
关于李超树的区间查询：
用一个Min维护区间最小值,Min的组成来源为两个子树的Min的较小值和本结点优势线段在两个端点的较小值
如果查询包含整个区间则直接返回Min，否则来源为正常区间最小值查找 + 本结点优势线段在查询两端的较小值
*/
const int maxn = 1e5 + 10;
const LL INF = 123456789123456789;
int N,M,K;
struct Edge{
    int to,next;
    LL dis;
}edge[maxn * 2];
int head[maxn],tot;
void init(){
    for(int i = 0 ; i <= N ; i ++) head[i] = -1;
    tot = 0;
}
void add(int u,int v,LL w){
    edge[tot].to = v;
    edge[tot].next = head[u];
    edge[tot].dis = w;
    head[u] = tot++;
}
int dep[maxn],top[maxn],fa[maxn],pos[maxn];
int sz[maxn],son[maxn],to[maxn];
LL dis[maxn];
void dfs1(int t,int la){
    sz[t] = 1; son[t] = t;
    int heavy = 0;
    for(int i = head[t]; ~i ; i = edge[i].next){
        int v = edge[i].to;
        if(v == la) continue;
        dis[v] = dis[t] + edge[i].dis;
        dep[v] = dep[t] + 1;
        fa[v] = t;
        dfs1(v,t);
        if(sz[v] > heavy){
            heavy = sz[v];
            son[t] = v;
        }
        sz[t] += sz[v];
    }
}
int cnt;
void dfs2(int t,int la){
    top[t] = la;
    pos[t] = ++cnt; to[cnt] = t;
    if(son[t] == t) return;
    dfs2(son[t],la);
    for(int i = head[t]; ~i ; i = edge[i].next){
        int v = edge[i].to;
        if((fa[t] == v) || (v == son[t])) continue;
        dfs2(v,v);
    }
}
LL S[maxn * 2],P[maxn * 2];
int ttt;
struct Tree{
    int l,r,id;
    LL Min;
}tree[maxn << 2];
void Pushup(int t){
    if(tree[t].l == tree[t].r) return;
    tree[t].Min = min(tree[t].Min,min(tree[t << 1].Min,tree[t << 1 | 1].Min));
}
void Build(int t,int l,int r){
    tree[t].l = l; tree[t].r = r;
    tree[t].id = 0; tree[t].Min = INF;
    if(l == r) return;
    int m = l + r >> 1;
    Build(t << 1,l,m); Build(t << 1 | 1,m + 1,r);
}
void update(int t,int l,int r,int id){  //区间查询
    int m = tree[t].l + tree[t].r >> 1;
    if(l <= tree[t].l && tree[t].r <= r){
        int &a = id; int &b = tree[t].id;
        if(P[a] > P[b]) swap(a,b);
        if(dis[to[m]] * P[a] + S[a] < dis[to[m]] * P[b] + S[b]){
            swap(a,b);
            if(tree[t].l != tree[t].r) update(t << 1,l,r,id);
        }else{
            if(tree[t].l != tree[t].r) update(t << 1 | 1,l,r,id);
        }
        Pushup(t);
        tree[t].Min = min(tree[t].Min,dis[to[tree[t].l]] * P[b] + S[b]);
        tree[t].Min = min(tree[t].Min,dis[to[tree[t].r]] * P[b] + S[b]);
        return;
    }
    if(r <= m) update(t << 1,l,r,id);
    else if(l > m) update(t << 1 | 1,l,r,id);
    else{
        update(t << 1,l,m,id);
        update(t << 1 | 1,m + 1,r,id);
    }
    Pushup(t);
}
LL query(int t,int l,int r){
    if(l <= tree[t].l && tree[t].r <= r) return tree[t].Min;
    int m = (tree[t].l + tree[t].r) >> 1;
    LL ans = INF;
    ans = min(ans,dis[to[l]] * P[tree[t].id] + S[tree[t].id]);
    ans = min(ans,dis[to[r]] * P[tree[t].id] + S[tree[t].id]);
    if(r <= m) return min(ans,query(t << 1,l,r));
    else if(l > m) return min(ans,query(t << 1 | 1,l,r));
    else{
        return min(ans,min(query(t << 1,l,m),query(t << 1 | 1,m + 1,r)));
    }
}
int lca(int x,int y){
    while(top[x] != top[y]) dep[top[x]] > dep[top[y]]?x = fa[top[x]]:y = fa[top[y]];
    return dep[x] < dep[y]?x:y;
}
void update(int u,int v,int id){
    while(top[u] != top[v]){
        if(dep[top[u]] < dep[top[v]]) swap(u,v);
        update(1,pos[top[u]],pos[u],id);
        u = fa[top[u]];
    }
    if(dep[u] > dep[v]) swap(u,v);
    update(1,pos[u],pos[v],id); 
}
LL query(int u,int v){
    LL ans = INF;
    while(top[u] != top[v]){
        if(dep[top[u]] < dep[top[v]]) swap(u,v);
        ans = min(ans,query(1,pos[top[u]],pos[u]));
        u = fa[top[u]];
    }
    if(dep[u] > dep[v]) swap(u,v);
    ans = min(ans,query(1,pos[u],pos[v]));
    return ans;
}
int main(){
    Sca2(N,M); init();
    P[0] = 0; S[0] = INF;
    for(int i = 1; i <= N - 1; i ++){
        int u = read(),v = read();
        LL w = read();
        add(u,v,w); add(v,u,w);
    }
    int root = 1;
    dfs1(root,-1); cnt = 0;
    dfs2(root,root);
    Build(1,1,N); ttt = 0;
    while(M--){
        int op = read();
        if(op == 1){
            int s = read(),t = read();
            LL a = read(),b = read();
            int x = lca(s,t);
            ttt++; P[ttt] = -a; S[ttt] = a * dis[s] + b; 
            update(s,x,ttt);
            ttt++; P[ttt] = a; S[ttt] = a * (dis[s] - 2 * dis[x]) + b;
            update(x,t,ttt);
        }else{
            int s = read(),t = read();
            Prl(query(s,t));
        }
    }
    return 0;
}


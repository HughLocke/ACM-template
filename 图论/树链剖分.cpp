//树链剖分，处理将整棵树化成一个序列方便区间操作，用线段树或者其他数据结构统一处理 
//注意：如果树剖写T了，要关注序列有没有按照重链来排，有可能是重链那部分写错了
const int maxn = 3e4 + 10;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7; 
int N,M,K;
struct Edge{
    int to,next;
}edge[maxn * 2];
int head[maxn],tot;
void init(){
    for(int i = 1;i <= N ; i ++) head[i] = -1;
    tot = 0;
}
void add(int u,int v){
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot++;
}

//求结点信息 
int nw[maxn];
int dep[maxn],top[maxn],fa[maxn],key[maxn],pos[maxn],size[maxn],son[maxn];
int To_num[maxn];
void dfs1(int t,int la){
    size[t] = 1; son[t] = t;
    int heavy = 0;
    for(int i = head[t]; ~i ; i = edge[i].next){
        int v = edge[i].to;
        if(v == la) continue;
        dep[v] = dep[t] + 1;
        fa[v] = t;
        dfs1(v,t);
        if(size[v] > heavy){
            heavy = size[v];
            son[t] = v;
        } 
        size[t] += size[v];
    }
}
int cnt;
void dfs2(int t,int la){
    top[t] = la;
    pos[t] = ++cnt;
    To_num[cnt] = t;
    nw[cnt] = key[t];
    if(son[t] == t) return;
    dfs2(son[t],la);
    for(int i = head[t]; ~i ; i = edge[i].next){
        int v = edge[i].to;
        if((fa[t] == v) || (v == son[t])) continue;
        dfs2(v,v);
    }
}
//线段树 
struct Tree{
    int l,r;
    int sum,MAX;
}tree[maxn << 2];
void Pushup(int t){
    tree[t].sum = tree[t << 1].sum + tree[t << 1 | 1].sum;
    tree[t].MAX = max(tree[t << 1].MAX,tree[t << 1 | 1].MAX);
}
void Build(int t,int l,int r){
    tree[t].l = l; tree[t].r = r;
    if(l == r){
        tree[t].sum = tree[t].MAX = nw[l];
        return;
    }
    int m = (l + r) >> 1;
    Build(t << 1,l,m); Build(t << 1 | 1,m + 1,r);
    Pushup(t);
}
void update(int t,int p,int x){
    if(tree[t].l == tree[t].r){
        tree[t].MAX = tree[t].sum = x;
        return;
    }
    int m = (tree[t].l + tree[t].r) >> 1;
    if(p <= m) update(t << 1,p,x);
    else update(t << 1 | 1,p,x);
    Pushup(t);
}
int query(int t,int l,int r,int p){
    if(l <= tree[t].l && tree[t].r <= r){
        if(p) return tree[t].sum;
        else return tree[t].MAX;
    }
    int m = (tree[t].l + tree[t].r ) >> 1;
    if(r <= m) return query(t << 1,l,r,p);
    else if(l > m) return query(t << 1 | 1,l,r,p);
    else{
        if(p) return query(t << 1,l,m,p) + query(t << 1 | 1,m + 1,r,p);
        else return max(query(t << 1,l,m,p),query(t << 1 | 1,m + 1,r,p));
    }
}

//树链剖分求链上信息
int query(int u,int v,int p){
    int ans = 0;
    if(!p) ans = -INF;
    while(top[u] != top[v]){
        if(dep[top[u]] < dep[top[v]]) swap(u,v);
        if(p) ans += query(1,pos[top[u]],pos[u],1);
        else ans = max(ans,query(1,pos[top[u]],pos[u],0));
        u = fa[top[u]];
    }
    if(dep[u] > dep[v]) swap(u,v);
    if(p) ans += query(1,pos[u],pos[v],p);
    else ans = max(ans,query(1,pos[u],pos[v],p));
    return ans;
} 
int main(){
    Sca(N); init();
    for(int i = 1; i <= N - 1; i ++){
        int u,v; Sca2(u,v);
        add(u,v); add(v,u);
    }
    for(int i = 1; i <= N ; i ++) Sca(key[i]);
    int root = 1;
    dfs1(root,-1);
    cnt = 0;
    dfs2(root,root);
    Build(1,1,N);
    Sca(M);
    while(M--){
        char op[10]; int u,v;
        scanf("%s%d%d",op,&u,&v);
        if(op[0] == 'C'){
            update(1,pos[u],v);    //把结点u权值改为t 
        }else if(op[1] == 'M'){
            Pri(query(u,v,0));     //查询链上结点最大值 
        }else if(op[1] == 'S'){
            Pri(query(u,v,1));      //查询树链上的权值和 
        }
    }
    return 0;
}
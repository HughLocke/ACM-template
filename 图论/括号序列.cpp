//括号序列
/*首先dfs整棵树一遍，进入一个节点的时候加上一个左括号，然后是节点编号，
当这个节点的所有子树遍历完后再添上一个右括号，这就是括号序列
假如一棵树的括号序列是(1(2(3))(4(5)(6)(7(8))))
我们要求3到8的距离，截取两点间的括号序列为 3))(4(5)(6)(7(8
把编号和匹配的括号删掉 ))(((
剩下了5个左右括号，而这就是3到8的距离。这就是括号序列的性质。*/
/* 模板
操作1.将一个结点黑白变换，操作2.询问所有黑点之间的最长距离
解法：相当于求出括号序列，线段树维护两个黑点之间的最大距离sum*/
const int maxn = 1e5 + 10;
const int INF = 0x3f3f3f3f;
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
//括号序列
int id[maxn << 2],cnt,pos[maxn];
void dfs(int u,int la){
    id[++cnt] = -1; //左括号
    id[++cnt] = u; pos[u] = cnt; 
    for(int i = head[u]; ~i ; i = edge[i].next){
        int v = edge[i].to;
        if(v == la) continue;
        dfs(v,u);
    }
    id[++cnt] = -2; // 右括号 
}
//设左子树左右括号数量为l1,r1,右子树为l2,r2
//sum = l1 + abs(r1 - l2) + r2 = max(l1 + r1 + (r2 - l2),l1 - r1 + (r2 + l2))
//所以维护后缀的max(l + r),max(l - r),前缀的max(r - l),max(r + l) 
struct Tree{
    int l,r;
    int a,b,sum;
    int l1,l2; //max(l + r),max(r - l)
    int r1,r2; //max(l - r),max(l + r)
}tree[maxn << 4];
//l1表示当前区间前缀的一段中左括号和右括号的和最大是多少，其他同理
bool col[maxn];
//因为是黑点的最远距离，除了黑点之外的坐标都不维护pre,erp,sum,直接当作-INF 
void update(int t){
    tree[t].a = tree[t].b = 0;
    tree[t].sum = tree[t].l1 = tree[t].l2 = tree[t].r1 = tree[t].r2 = -INF;
    int v = tree[t].l;
    if(id[v] == -1) tree[t].b = 1;
    else if(id[v] == -2) tree[t].a = 1;
    else if(!col[id[v]]){
        tree[t].l1 = tree[t].l2 = tree[t].r1 = tree[t].r2 = 0;
    }
}
void Pushup(int t){
    tree[t].b = tree[rc].b;
    tree[t].a = tree[lc].a;
    if(tree[lc].b > tree[rc].a) tree[t].b += tree[lc].b - tree[rc].a;
    else tree[t].a += tree[rc].a - tree[lc].b;
    tree[t].l1 = max(tree[lc].l1,max(tree[rc].l1 + tree[lc].a - tree[lc].b,tree[rc].l2 + tree[lc].a + tree[lc].b));
    tree[t].l2 = max(tree[lc].l2,tree[rc].l2 + tree[lc].b - tree[lc].a);
    tree[t].r1 = max(tree[rc].r1,tree[lc].r1 + tree[rc].a - tree[rc].b);
    tree[t].r2 = max(tree[rc].r2,max(tree[lc].r2 + tree[rc].b - tree[rc].a,tree[lc].r1 + tree[rc].b + tree[rc].a));
    tree[t].sum = max(tree[lc].r1 + tree[rc].l1,tree[lc].r2 + tree[rc].l2);
    tree[t].sum = max(max(tree[lc].sum,tree[rc].sum),tree[t].sum);
}
void Build(int t,int l,int r){
    tree[t].l = l; tree[t].r = r;
    if(l == r){
        update(t);
        return;
    }
    int m = l + r >> 1;
    Build(t << 1,l,m); Build(t << 1 | 1,m + 1,r);
    Pushup(t);
}
void update(int t,int p){
    if(tree[t].l == tree[t].r){
        update(t);
        return;
    }
    int m = tree[t].l + tree[t].r >> 1;
    if(p <= m) update(t << 1,p);
    else update(t << 1 | 1,p);
    Pushup(t);
}
int main(){
    Sca(N); init();
    for(int i = 1; i <= N - 1; i ++){
        int u = read(),v = read();
        add(u,v); add(v,u);
    } 
    dfs(1,-1);
    Build(1,1,cnt);
    Sca(M); int num = N;
    while(M--){
        char op[3]; scanf("%s",op);
        if(op[0] == 'G'){
            if(num == 1) puts("0");
            else if(!num) puts("-1");
            else Pri(tree[1].sum);
        }else{
            int v = read();
            if(col[v]) num--;
            else num++;
            col[v] ^= 1; update(1,pos[v]);
        }
    }
    return 0;
}


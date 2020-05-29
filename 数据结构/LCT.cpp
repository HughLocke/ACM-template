//link cut tree (LCT)
/* lct的性质
    1.lct是将一棵树分为若干的Splay
    每一个Splay维护的是一条从上到下按在原树中深度严格递增的路径，且中序遍历Splay得到的每个点的深度序列严格递增。
    2.每个节点包含且仅包含于一个Splay中
    3.边分为实边和虚边，实边包含在Splay中，而虚边总是由一棵Splay指向另一个节点（指向该Splay中中序遍历最靠前的点在原树中的父亲）。因为性质2，当某点在原树中有多个儿子时，只能向其中一个儿子拉一条实链（只认一个儿子），而其它儿子是不能在这个Splay中的。那么为了保持树的形状，我们要让到其它儿子的边变为虚边，由对应儿子所属的Splay的根节点的父亲指向该点，而从该点并不能直接访问该儿子（认父不认子）。
 */
const int maxn = 3e5 + 10;
int N,M,K;
#define lc e[x].ch[0]
#define rc e[x].ch[1]
#define fc e[x].fa
struct node{
    int fa,ch[2];
    int v,s;   //v存储当前节点信息，s存储子树的异或和 
    bool rev;
}e[maxn];
int Stack[maxn];
//1轻边重边主要看父亲认不认儿子（儿子一定认父亲） 
void pushup(int x){
    e[x].s = e[lc].s ^ e[rc].s ^ e[x].v;
}
bool nroot(int x){   //判断节点是否为一个Splay的根 ,返回1代表不是根 
    return e[fc].ch[0] == x || e[fc].ch[1] == x; //如果是根，他的父亲和他之间是轻边（父亲不认儿子） 
}
void rev(int x){     //翻转子树 
    swap(lc,rc); e[x].rev ^= 1;
}
void pushdown(int x){   //向下更新 
    if(e[x].rev){
        if(lc) rev(lc);
        if(rc) rev(rc);
        e[x].rev = 0;
    }
}
void rotate(int x){    //在x在自己的splay里向上旋转 
    int y = e[x].fa; int z = e[y].fa;
    int ix = e[y].ch[1] == x; int iy = e[z].ch[1] == y;
    int w = e[x].ch[ix ^ 1];
    if(nroot(y)) e[z].ch[iy] = x;   //不判断会错 
    if(w) e[w].fa = y;
    e[x].ch[ix ^ 1] = y; e[y].ch[ix] = w;
    e[y].fa = x; e[x].fa = z;
    pushup(y);
}
void splay(int x){ //只传了一个参数的原因是所有目标都是该Splay的根 
    int y = x,top = 0;
    Stack[++top] = y;
    while(nroot(y)) Stack[++top] = y = e[y].fa;
    while(top) pushdown(Stack[top--]);  //先下方整条路径上的信息 
    while(nroot(x)){
        y = e[x].fa; int z = e[y].fa;
        if(nroot(y)) rotate((e[y].ch[0] == x) ^ (e[z].ch[0] == y)?x:y);  //直连就转父亲，否则转自己 
        rotate(x);
    }
    pushup(x);
}
void access(int x){  //联通x到根，使他们在同一个Splay 
    for(int y = 0;x;x = e[x].fa){
        splay(x);
        e[x].ch[1] = y;
        pushup(x);
        y = x;
    }
} 
//换原树的根 
void makeroot(int x){ 
    access(x); splay(x); rev(x);
}
//找根,即x所属的splay中深度最浅的那个点 
//indroot(x)==findroot(y)表明x,y在同一棵树中
int findroot(int x){   
    access(x); splay(x);
    while(lc) pushdown(x),x = lc;
    splay(x);
    return x;
}
//拉出x-y的路径成为一个Splay (以y作为该Splay的根)
void split(int x,int y){  
    makeroot(x);
    access(y); splay(y);
}
//连一条x-y的边（使x的父亲指向y，连一条轻边）
void link(int x,int y){
    makeroot(x);
    if(findroot(y) != x) e[x].fa = y;
}
//将x-y的边断开
void cut(int x,int y){
    makeroot(x);
    if(findroot(y) == x && e[y].fa == x && !e[y].ch[0]){
        e[y].fa = e[x].ch[1] = 0;
        pushup(x);
    }
}
/* 如果保证断的边都存在可以这么写
void cut(int x,int y){
	split(y,x);
	e[y].fa = e[x].ch[1] = 0;
	pushup(x);
}
 */
int main(){
    Sca2(N,M);
    for(int i = 1; i <= N; i ++) Sca(e[i].v);
    while(M--){
        int op,x,y; Sca3(op,x,y);
        switch(op){
        case 0:split(x,y); Pri(e[y].s); break;
        case 1:link(x,y); break;
        case 2:cut(x,y); break;
        case 3:splay(x); e[x].v = y; break;
        }
    }
    return 0;
}

//LCT的边转点
/*
树链剖分等算法的边转点一般是将边转化为深度交深的点
当用LCT维护类似于树链上最大的边的时候，可以采用(u,v)这条边转化为(u,id),(id,v)的方式，其中
id为u,v之间的边，即将边看作是一个点
模板：luoguP4172 水管局长
给一个n个点m条边的图，支持以下操作：
1.询问x到y所有路径中，路径上最大边权的最小值
2.删去一条边
做法:离线之后变为加边，用LCT维护一个最小生成树
*/

const double eps = 1e-9;
const int maxn = 2e5 + 10;
const int maxm = 1500000; 
const int maxq = 1e5 + 10;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7; 
int N,M,K,Q;
struct Edge{
	int u,v,t;
}edge[maxm + maxn];
struct Q{
	int k,x,y;
}q[maxm];
bool vis[maxm + maxn];
map<PII,int>ide;
int fa[maxm];
void init(){for(int i = 0 ; i <= N ; i ++) fa[i] = i;}
int find(int x){return x == fa[x]?x:fa[x] = find(fa[x]);}
void Union(int a,int b){
	a = find(a); b = find(b);
	fa[a] = b;
}
#define lc e[x].ch[0]
#define rc e[x].ch[1]
#define fc e[x].fa
struct node{
	int ch[2],fa;
	int iv,imax;
	bool rev;
}e[maxn + maxm];
void pushup(int x){
	int a = e[x].iv,b = e[lc].imax,c = e[rc].imax; 
	if(edge[a].t < edge[b].t) a = b;
	if(edge[a].t < edge[c].t) a = c;
	e[x].imax = a;
}
bool nroot(int x){
	return e[fc].ch[0] == x || e[fc].ch[1] == x;
}
void rev(int x){
	swap(lc,rc); e[x].rev ^= 1;
}
void pushdown(int x){
	if(e[x].rev){
		if(lc) rev(lc);
		if(rc) rev(rc);
		e[x].rev = 0;
	}
}
void rotate(int x){
	int y = e[x].fa;int z = e[y].fa;
	int ix = e[y].ch[1] == x;
	int iy = e[z].ch[1] == y;
	int w = e[x].ch[ix ^ 1];
	if(nroot(y)) e[z].ch[iy] = x;
	if(w) e[w].fa = y;
	e[x].ch[ix ^ 1] = y; e[y].ch[ix] = w;
	e[y].fa = x;  e[x].fa = z;
	pushup(y);
}
int Stack[maxn + maxm];
void splay(int x){
	int y = x,top = 0;
	Stack[++top] = y;
	while(nroot(y)) Stack[++top] = y = e[y].fa;
	while(top) pushdown(Stack[top--]);
	while(nroot(x)){
		y = e[x].fa; int z = e[y].fa;
		if(nroot(y)) rotate((e[y].ch[0] == x) ^ (e[z].ch[0] == y)?x:y);
		rotate(x);
	}
	pushup(x);
}

void access(int x){
	for(int y = 0;x;x = e[x].fa){
		splay(x);
		e[x].ch[1] = y;
		pushup(x);
		y = x;
	}
}
void makeroot(int x){
	access(x); splay(x); rev(x);
}
int findroot(int x){
	access(x); splay(x);
	while(lc) pushdown(x),x = lc;
	splay(x);
	return x;
}
void split(int x,int y){
	makeroot(x);
	access(y); splay(y);
}
void link(int x,int y){
	makeroot(x);
	if(findroot(y) != x) e[x].fa = y;
}
void cut(int x,int y){
	split(y,x);
	e[y].fa = e[x].ch[1] = 0;
	pushup(x);
}
void add(int u,int v,int id){
	if(find(u) != find(v)){
		Union(u,v);
		link(u,id); link(id,v);
		return;
	}
	split(u,v);
	int tmp = e[v].imax;
	if(edge[tmp].t > edge[id].t){
		cut(edge[tmp].u,tmp);
		cut(tmp,edge[tmp].v);
		link(u,id); link(id,v);
	}
}
int ans[maxm];
bool cmp(Edge a,Edge b){
	return a.t < b.t;
}
int main(){
	N = read(),M = read(),Q = read();init();
	edge[0].t = -1;
	for(int i = 1; i <= N; i ++) e[i].imax = e[i].iv = 0;
	for(int i = 1 + N; i <= M + N; i ++){
		edge[i].u = read(); edge[i].v = read(); edge[i].t = read();
		if(edge[i].u > edge[i].v) swap(edge[i].u,edge[i].v);
	} 
	sort(edge + 1 + N,edge + 1 + M + N,cmp);
	for(int i = 1 + N; i <= M + N; i ++){
		e[i].iv = e[i].imax = i;
		ide[mp(edge[i].u,edge[i].v)] = i;
	}
	for(int i = 1; i <= Q ; i ++){
		q[i].k = read(); q[i].x = read(); q[i].y = read();
		if(q[i].x > q[i].y) swap(q[i].x,q[i].y);
		if(q[i].k == 2) vis[ide[mp(q[i].x,q[i].y)]] = 1;
	} 
	int cnt = 0;
	for(int i = 1 + N; i <= M + N && cnt < N - 1; i ++){
		if(vis[i]) continue;
		int u = edge[i].u,v = edge[i].v;
		if(find(u) == find(v)) continue;
		cnt++;
		Union(u,v); link(u,i); link(i,v);
	}
	int tot = 0;
	for(int i = Q; i >= 1; i --){
		if(q[i].k == 1){
			split(q[i].x,q[i].y);
			ans[++tot] = edge[e[q[i].y].imax].t;
		}else{
			add(q[i].x,q[i].y,ide[mp(q[i].x,q[i].y)]);
		}
	}
	for(int i = tot; i >= 1; i --) Pri(ans[i]);
	return 0;
}

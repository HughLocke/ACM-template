/*kruskal重构树
这个东西主要来处理最小生成树的最大边权问题
当然也可以处理最大生成树的最小边权问题  核心思想跟 krsskal差不多
我们重构树的过程是这样的
将所有边按边权从小到大排序
每次最小的一条边，如果条边相连的两个点在同一个集合中，那么就跳过，否则就将这两个点的祖先都连到一个虚点上去，让这个虚点的点权等于这条边的边权
这样的话这课被重构的树就有一些奇妙的性质
原本最小生成树上的点在重构树里都是叶节点
从任何一个点往根上引一条路径，这条路径经过的点的点权单调不降（最大生成树单调不升）
任意两点之间路径的最大边权就是他们的LCA的点权*/
//模板：给一张图，每次询问两点间路径最大值的最小值是多少
//做法1.最小生成树上LCA求树链最大值
//作法2(如下代码):kruskal重构树上直接求LCA点权
const int maxn = 3e5 + 10;
int N,M;
int tree[maxn];
int find(int t){
	if(tree[t] == t) return t;
	return tree[t] = find(tree[t]);
}
struct Edge{
	int to,next;
}edge[maxn * 2];
int head[maxn],tot;
void init(){
	for(int i = 0 ; i <= N ; i ++) head[i] = -1,tree[i] = i;
	tot = 0;
}
void add(int u,int v){
	edge[tot].to = v;
	edge[tot].next = head[u];
	head[u] = tot++;
}
struct E{
	int u,v,w;
}e[maxn];
bool cmp(E a,E b){
	return a.w < b.w;
}
int w[maxn];
const int SP = 20;
int pa[maxn][SP],dep[maxn];
void dfs(int u,int la){
	pa[u][0] = la; dep[u] = dep[la] + 1;
	for(int i = 1; i < SP; i ++){
		pa[u][i] = pa[pa[u][i - 1]][i - 1];
	}
	for(int i = head[u]; ~i; i = edge[i].next){
		int v = edge[i].to;
		if(v == la) continue;
		dfs(v,u);
	}
}
int lca(int u,int v){
	if(dep[u] < dep[v]) swap(u,v);
	int t = dep[u] - dep[v];
	for(int i = 0 ; i < SP; i ++) if(t & (1 << i)) u = pa[u][i];
	for(int i = SP - 1; i >= 0; i --){
		int uu = pa[u][i],vv = pa[v][i];
		if(uu != vv){
			u = uu;
			v = vv;
		}
	}
	return u == v?u:pa[u][0];
}
int main(){
	scanf("%d%d",&N,&M); init();
	for(int i = 1; i <= M ;  i++){
		scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
	}
	sort(e + 1,e + 1 + M,cmp);
	for(int i = 1; i <= M ; i ++){
		int u = find(e[i].u),v = find(e[i].v);
		if(u == v) continue;
		N++; tree[N] = N; w[N] = e[i].w; head[N] = -1;
		tree[u] = N; tree[v] = N;
		add(N,u); add(N,v);
	}
	for(int i = 1; i <= N ; i ++){
		if(tree[i] == i) dfs(i,-1);
	}
	int Q; scanf("%d",&Q);
	while(Q--){
		int u,v; scanf("%d%d",&u,&v);
		if(find(u) != find(v)) puts("impossible");
		else printf("%d\n",w[lca(u,v)]);
	}
	return 0;
}

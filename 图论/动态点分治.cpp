//动态点分治(点分树)
/*点分树：当我们可以形如点分治一样的统计答案，即每次确定一个重心，然后计算他们子树之间的贡献和得出答案的时候
我们可以将每个区域的重心作为其所有子树的重心的父亲，构成一颗新的树，显然这棵树的深度不会超过logn
每次对于单点（边）更新的时候，只要对其所有的父亲更新，就只需要更新log个点，这样的数据结构就是点分树
*/
//模板:BZOJ1095
/*
对于本题来说，最终的答案是在每个点作为链上一个点的时候，找每个点出发的最长链和次长链的和的最大值
所以用一个堆A维护每个点在点分树中子树下所有的点到这个点父亲的距离
再用一个堆B维护每个点所有儿子点的堆A的最大值，即每条链的最长的长度
最后用一个堆C维护每个点的最长值 + 次长值的大小
tips:
1.树上两两之间的点的距离可以rmq + ST表预处理之后O(1)查询，注意转化成序列不是dfs序，具体看代码
2.做一个供删除的优先队列，可以用两个优先队列A,B，一个正常用，删除操作就是把元素加入B，当AB顶部相同的时候一起弹出
*/
const int maxn = 2e5 + 10;
int N,M,K;
//带删除的优先队列
struct heap{
    priority_queue<int>A,B;
    void push(int x){A.push(x);}
    void del(int x){B.push(x);}
    void init(){
        while(!B.empty() && A.top() == B.top()){
            A.pop(); B.pop();
        }
    }
    int top(){
        init();
        if(A.empty()) return 0;
        return A.top();
    }
    int size(){
        return A.size() - B.size();
    }
    int Maxdis(){
        if(size() < 2) return 0;
        int x = top(); A.pop();
        int y = top(); A.push(x);
        return x + y;
    }
};
struct Edge{
    int to,next;
}edge[maxn << 1];
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
//st表预处理树上距离
int dep[maxn];
int id[maxn],pos[maxn],cnt;
void dfsinit(int u,int la){
    id[++cnt] = dep[u];
    pos[u] = cnt;
    for(int i = head[u]; ~i ; i = edge[i].next){
        int v = edge[i].to;
        if(v == la) continue;
        dep[v] = dep[u] + 1;
        dfsinit(v,u);
        id[++cnt] = dep[u]; //注意这个点是u而不是v，这不是一个dfs序
    }
}
const int SP = 20;
int MIN[maxn][SP],mm[maxn];
void initRMQ(int n,int b[]){
    for(int i = 1; i <= n ; i ++){
        for(int j = 0 ; j < SP; j ++){
            MIN[i][j] = INF;
        }
    }
    mm[0] = -1;
    for(int i = 1; i <= n; i ++){
        mm[i] = ((i & (i - 1)) == 0)?mm[i - 1] + 1:mm[i - 1];
        MIN[i][0] = b[i];
    }
    for(int j = 1; j <= mm[n]; j ++){
        for(int i = 1; i + (1 << j) - 1 <= n; i ++){
            MIN[i][j] = min(MIN[i][j - 1],MIN[i + (1 << (j - 1))][j - 1]);
        }
    }
}
int rmq(int x,int y){ 
    if(x > y) swap(x,y);
    int k = mm[y - x + 1];
    return min(MIN[x][k],MIN[y - (1 << k) + 1][k]);
}
int getdis(int x,int y){ //查询x到y的树上距离
    return dep[x] + dep[y] - 2 * rmq(pos[x],pos[y]);
}
struct dtnode{
    int fa;
    heap Q,P;
    int Maxdis(){return Q.top();}
    int Maxline(){return P.Maxdis();}
}dt[maxn];
heap fans;
int root,max_part,SUM;
int size[maxn],vis[maxn];
int dis[maxn];
void dfs_root(int u,int la){
    size[u] = 1; int heavy = 0;
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
void dfs(int u,int la){
    dis[u] = getdis(u,dt[root].fa);
    dt[root].Q.push(dis[u]);
    for(int i = head[u]; ~i ; i = edge[i].next){
        int v = edge[i].to;
        if(v == la || vis[v]) continue;
        dfs(v,u);
    }
}
int divide(int t,int la){
    max_part = INF;
    root = t; 
    dfs_root(t,-1); 
    int now = root;
    dt[root].fa = la; dt[root].P.push(0);
    if(~la) dfs(root,-1);
    vis[root] = 1;
    for(int i = head[now]; ~i ; i = edge[i].next){
        int v = edge[i].to;
        if(vis[v]) continue;
        SUM = size[v];
        v = divide(v,now);
        dt[now].P.push(dt[v].Maxdis());
    }
    if(dt[now].P.size() >= 2)fans.push(dt[now].Maxline());
    return now;
}
int use[maxn];
int main(){
    Sca(N); init();
    for(int i = 1; i < N ; i ++){
        int u = read(),v = read();
        add(u,v); add(v,u);
    }
    dfsinit(1,-1); initRMQ(cnt,id);
    SUM = N; divide(1,-1);
    int num = N;
    Sca(M);
    while(M--){
        char op[3]; scanf("%s",op);
        if(op[0] == 'G'){
            if(num == 1) puts("0");
            else if(!num) puts("-1");
            else{
                Pri(fans.top());
            }    
        }else{
            int v = read(); int tmp = v;
            if(use[v]) num++;
            else num--;
            if(dt[v].P.size() >= 2) fans.del(dt[v].Maxline());
            if(use[v]) dt[v].P.push(0);
            else dt[v].P.del(0);
            if(dt[v].P.size() >= 2) fans.push(dt[v].Maxline());
            while(~dt[tmp].fa){
                int u = dt[tmp].fa;
                if(dt[u].P.size() >= 2) fans.del(dt[u].Maxline());
                if(dt[tmp].Q.size()) dt[u].P.del(dt[tmp].Maxdis());
                int d = getdis(v,u);
                if(use[v]) dt[tmp].Q.push(d);
                else dt[tmp].Q.del(d);
                if(dt[tmp].Q.size()) dt[u].P.push(dt[tmp].Maxdis());
                if(dt[u].P.size() >= 2) fans.push(dt[u].Maxline());
                tmp = u;
            }
            use[v] ^= 1;
        }
    }
    return 0;
}

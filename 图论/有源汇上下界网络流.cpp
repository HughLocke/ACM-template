/* 
1.有源汇上下界可行流
首先有源汇与无源汇的区别在于：有源汇可行流中，源点和汇点不一定流量平衡，但是源点多余的流量=汇点的多余流量。
解决有源汇问题时我们通常将其转化为无源汇的问题，具体方法就是连一条(T,S,∞,0)的边。这样的话，汇点多余的输出就可以通过这条边进入源点。
然后我们建立超级源SS与超级汇TT，之后判断是否有可行流就用前面的方法
2.有源汇上下界最大流
因为S与T之间可能存在富余的边，导致没有得到最大流。
我们将超级源和超级汇以及与他们相连的边拆掉，然后在残余网络上在跑一次最大流。得到新的最大流与w的和就是答案。
3.有源汇上下界最小流
法1：与最大流类似。我们先得到了w之后我们尽量减少S和T之间的流量。于是我们拆了超级源和超级汇之后“反着”跑最大流，也就是拿T当源点，S当汇点跑最大流。可以这么理解：反边增加流量相当于正边减少流量。答案就是w-最大流。
法2：当然也可以不用改变图，直接反着跑最大流，答案就是INF-最大流。这里INF就是我们(T,S,∞,0)的上界。
 */
 //有源汇上下界最大流
const int maxn = 410;
const int maxm = 2e5 + 10;
const int INF = 0x3f3f3f3f;
int N,M,K,S,T;
int a[maxn],F[maxm];
struct E{
    int u,v,l,r;
}e[maxm];
struct dinic{
    struct Edge{
        int to,next,flow,cap,id;
        Edge(){}
        Edge(int to,int next,int flow, int cap,int id):
            to(to),next(next),flow(flow),cap(cap),id(id){}
    }edge[maxm * 2];
    int head[maxn],tot;
    int s,n,t,cur[maxn],dep[maxn];
    void init(int n){
        this->n = n; 
        for(int i = 0 ; i <= n ; i ++) head[i] = -1;
        tot = 0;
    }
    void add(int u,int v,int w,int id){
        edge[tot] = Edge(v,head[u],0,w,id);
        head[u] = tot++;
        edge[tot] = Edge(u,head[v],0,0,id);
        head[v] = tot++; 
    }
    inline bool bfs(){
        for(int i = 0 ; i <= n ; i ++) dep[i] = -1;
        dep[s] = 1;
        queue<int>Q; Q.push(s);
        while(!Q.empty()){
            int u = Q.front(); Q.pop();
            for(int i = head[u]; ~i ; i = edge[i].next){
                int v = edge[i].to;
                if(~dep[v] || edge[i].flow >= edge[i].cap) continue;
                dep[v] = dep[u] + 1;
                Q.push(v);
            }
        }
        return ~dep[t];
    }
    inline int dfs(const int &u,int a){
        if(u == t || !a) return a;
        int flow = 0;
        for(int &i = cur[u]; ~i ; i = edge[i].next){
            int v = edge[i].to;
            if(dep[v] != dep[u] + 1) continue;
            int f = dfs(v,min(a,edge[i].cap - edge[i].flow));
            flow += f;
            a -= f;
            edge[i].flow += f;
            edge[i ^ 1].flow -= f;
            if(!a) return flow;
        }
        return flow;
    }
    int maxflow(int s,int t){
        this->s = s; this->t = t; 
        int flow = 0;
        while(bfs()){
            for(int i = 0 ; i <= n ; i ++) cur[i] = head[i];
            flow += dfs(s,INF);
        }
        return flow;
    }
    void solve(){
        for(int i = 0 ; i <= n ; i ++){
            for(int j = head[i]; ~j; j = edge[j].next){
                if(edge[j].flow > 0) F[edge[j].id] += edge[j].flow;
            }
        }
    }
    void del(int S,int T,int SS,int TT){
        for(int i = head[T]; ~i; i = edge[i].next){
            if(edge[i].cap == INF){
                edge[i].cap = edge[i].flow = 0;
                edge[i ^ 1].cap = edge[i ^ 1].flow = 0;
            }
        }
        for(int i = head[SS]; ~i; i = edge[i].next){
            edge[i].cap = edge[i].flow = 0;
            edge[i ^ 1].cap = edge[i ^ 1].flow = 0;
        } 
        for(int i = head[TT]; ~i; i = edge[i].next){
            edge[i].cap = edge[i].flow = 0;
            edge[i ^ 1].cap = edge[i ^ 1].flow = 0;
        } 
    }
}g;
int main(){
    scanf("%d%d%d%d",&N,&M,&S,&T);
    int SS = N + 1,TT = N + 2;
    g.init(N + 2);
    for(int i = 1; i <= M ; i ++){
        scanf("%d%d%d%d",&e[i].u,&e[i].v,&e[i].l,&e[i].r);
        g.add(e[i].u,e[i].v,e[i].r - e[i].l,i);
        a[e[i].u] += e[i].l; a[e[i].v] -= e[i].l;
    }
    g.add(T,S,INF,0);
    int sum = 0;
    for(int i = 1; i <= N; i ++){
        if(a[i] > 0){
            g.add(i,TT,a[i],M + 1);
            sum += a[i];
        } 
        else if(a[i] < 0) g.add(SS,i,-a[i],M + 1);
    }
    if(sum != g.maxflow(SS,TT)){
        puts("please go home to sleep");
        return 0;
    }
    //方法1.删除加入的边之后再残余网络上跑最大流
    // g.solve(); 
    // g.del(S,T,SS,TT);   //删除超级源点汇点以及加的T到S的边 
    // int ans = g.maxflow(S,T) + F[0];
    //方法2.求解可行流并判断可行后，原封不动地进行一次最大流，这个最大流就是答案
    int ans = g.maxflow(S,T);
    Pri(ans);
    return 0;
}
//有源汇上下界最小流
const int maxn = 50010;
const int maxm = 2e5 + 10;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7; 
int N,M,K,S,T;
int a[maxn],F[maxm];
struct E{
    int u,v,l,r;
}e[maxm];
struct dinic{
    struct Edge{
        int to,next,flow,cap,id;
        Edge(){}
        Edge(int to,int next,int flow, int cap,int id):
            to(to),next(next),flow(flow),cap(cap),id(id){}
    }edge[maxm * 2];
    int head[maxn],tot;
    int s,n,t,cur[maxn],dep[maxn];
    void init(int n){
        this->n = n; 
        for(int i = 0 ; i <= n ; i ++) head[i] = -1;
        tot = 0;
    }
    void add(int u,int v,int w,int id){
        edge[tot] = Edge(v,head[u],0,w,id);
        head[u] = tot++;
        edge[tot] = Edge(u,head[v],0,0,id);
        head[v] = tot++; 
    }
    inline bool bfs(){
        for(int i = 0 ; i <= n ; i ++) dep[i] = -1;
        dep[s] = 1;
        queue<int>Q; Q.push(s);
        while(!Q.empty()){
            int u = Q.front(); Q.pop();
            for(int i = head[u]; ~i ; i = edge[i].next){
                int v = edge[i].to;
                if(~dep[v] || edge[i].flow >= edge[i].cap) continue;
                dep[v] = dep[u] + 1;
                Q.push(v);
            }
        }
        return ~dep[t];
    }
    inline int dfs(const int &u,int a){
        if(u == t || !a) return a;
        int flow = 0;
        for(int &i = cur[u]; ~i ; i = edge[i].next){
            int v = edge[i].to;
            if(dep[v] != dep[u] + 1) continue;
            int f = dfs(v,min(a,edge[i].cap - edge[i].flow));
            flow += f;
            a -= f;
            edge[i].flow += f;
            edge[i ^ 1].flow -= f;
            if(!a) return flow;
        }
        return flow;
    }
    int maxflow(int s,int t){
        this->s = s; this->t = t; 
        int flow = 0;
        while(bfs()){
            for(int i = 0 ; i <= n ; i ++) cur[i] = head[i];
            flow += dfs(s,INF);
        }
        return flow;
    }
    void solve(){
        for(int i = 0 ; i <= n ; i ++){
            for(int j = head[i]; ~j; j = edge[j].next){
                if(edge[j].flow > 0) F[edge[j].id] += edge[j].flow;
            }
        }
    }
    void del(int S,int T,int SS,int TT){
        for(int i = head[T]; ~i; i = edge[i].next){
            if(edge[i].cap == INF){
                edge[i].cap = edge[i].flow = 0;
                edge[i ^ 1].cap = edge[i ^ 1].flow = 0;
            }
        }
        for(int i = head[SS]; ~i; i = edge[i].next){
            edge[i].cap = edge[i].flow = 0;
            edge[i ^ 1].cap = edge[i ^ 1].flow = 0;
        } 
        for(int i = head[TT]; ~i; i = edge[i].next){
            edge[i].cap = edge[i].flow = 0;
            edge[i ^ 1].cap = edge[i ^ 1].flow = 0;
        } 
    }
}g;
int main(){
    scanf("%d%d%d%d",&N,&M,&S,&T);
    int SS = N + 1,TT = N + 2;
    g.init(N + 2);
    for(int i = 1; i <= M ; i ++){
        e[i].u = read(),e[i].v = read();e[i].l = read();e[i].r = read();
        g.add(e[i].u,e[i].v,e[i].r - e[i].l,i);
        a[e[i].u] += e[i].l; a[e[i].v] -= e[i].l;
    }
    g.add(T,S,INF,0);
    int sum = 0;
    for(int i = 1; i <= N; i ++){
        if(a[i] > 0){
            g.add(i,TT,a[i],M + 1);
            sum += a[i];
        } 
        else if(a[i] < 0) g.add(SS,i,-a[i],M + 1);
    }
    if(sum != g.maxflow(SS,TT)){
        puts("please go home to sleep"); //不可行情况 
        return 0;
    }
    g.solve(); 
    /*g.del(S,T,SS,TT);   //删除超级源点汇点以及加的T到S的边 
    int ans = F[0] - g.maxflow(T,S);*/
    int ans = INF - g.maxflow(T,S);  //可将本行替换为上面的注释内容 
    Pri(ans);
    return 0;
}
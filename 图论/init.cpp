struct Edge{
    int to,next,dis;
}edge[maxm]; //maxm为边的数量，无向图数目需乘二
int head[maxn],tot;
void init(){
    for(int i = 1; i <= N ; i ++) head[i] = -1;
    tot = 0;
}
void add(int u,int v,int w){
    edge[tot].to = v;
    edge[tot].next = head[u];
    edge[tot].dis = w;
    head[u] = tot++;
}

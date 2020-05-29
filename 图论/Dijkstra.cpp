int dis[1005],vis[1005];
struct node{
    int pos,val;
    node(int pos,int val):pos(pos),val(val){}
    friend bool operator < (node a,node b){
        return a.val > b.val;
    }
};
int Dijkstra(int s,int t){
    for(int i = 1; i <= N ; i ++) dis[i] = INF;
    dis[s] = 0;
    priority_queue<node>Q;
    Q.push(node(s,0));
    while(!Q.empty()){
        node u = Q.top(); Q.pop();
        if(u.val > dis[u.pos]) continue;
        for(int i = head[u.pos]; ~i; i = edge[i].next){
            int v = edge[i].to;
            if(dis[v] > edge[i].dis + u.val){
                dis[v] = edge[i].dis + u.val;
                Q.push(node(v,dis[v]));
            }
        }
    }
    return dis[t];
}

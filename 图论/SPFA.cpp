//spfa判负环，spfa时间复杂度玄学，必要时手写队列以及打上快速读入，spfa容易被卡，非必要时用Dijkstra  
bool vis[maxn];
int dis[maxn],cnt[maxn];
bool spfa(int s){     
    for(int i = 1; i <= N ; i ++){
        vis[i] = 0; cnt[i] = 0; dis[i] = INF;
    }
    queue<int>Q;
    Q.push(s);
    vis[s] = 1; dis[s] = 0;
    while(!Q.empty()){
        int u = Q.front(); Q.pop();
        vis[u] = 0;
        if(cnt[u] >= N) return true;
        for(int i = head[u]; ~i ; i = edge[i].next){
            int v = edge[i].to;
            if(dis[v] > dis[u] + edge[i].dis){
                dis[v] = dis[u] + edge[i].dis;
                if(!vis[v]){
                    Q.push(v);
                    vis[v] = 1;
                    cnt[v]++;
                    if(cnt[v] >= N) return true;
                }
            }
        } 
    }
    return false;
}

//二分图匹配 匈牙利算法
//模板：左边N个点匹配右边M个点，总共K条边的最大匹配数
const int maxn = 1010;
int linker[maxn];
int vis[maxn];
bool dfs(int u){
    for(int i = head[u]; ~i ; i = edge[i].next){
        int v = edge[i].to;
        if(!vis[v]){
            vis[v] = true;
            if(linker[v] == -1 || dfs(linker[v])){
                linker[v] = u;
                return true;
            }
        }
    }
    return false;
}
int hungary(){
    int ans = 0;
    for(int i = 1; i <= M ; i ++) linker[i] = -1;   //注意是右边点的linker
    for(int i = 1; i <= N ; i ++){
        for(int j = 1; j <= M ; j ++) vis[j] = 0;
        if(dfs(i)) ans++;    
    }
    return ans;
}
int main(){
    Sca2(N,M); K = read(); init();
    for(int i = 1; i <= K; i ++){
        int u,v; Sca2(u,v);
        if(u > N || v > M) continue;
        add(u,v);
    }
    Pri(hungary());
    return 0;
}
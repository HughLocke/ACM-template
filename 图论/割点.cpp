//在无向图中，如果删除一个点这个图就不联通，那么这个点就叫割点
//模板：Tarjan求割点，N个点M条边找有多少割点并输出
int Low[maxn],dfn[maxn],Stack[maxn];
int Index,top;
bool Instack[maxn];
bool cut[maxn]; //记录是否为割点 
int add_block[maxn];   //删除这个点之后增加的联通块 
void Tarjan(int u,int la){
    int v;
    Low[u] = dfn[u] = ++Index;
    Stack[++top] = u;
    Instack[u] = true;
    int son = 0;
    for(int i = head[u]; ~i; i = edge[i].next){
        int v = edge[i].to;
        if(v == la) continue;
        if(!dfn[v]){
            son++;
            Tarjan(v,u);
            if(Low[u] > Low[v]) Low[u] = Low[v];
            if(u != la && Low[v] >= dfn[u]){
                cut[u] = 1;
                add_block[u]++;
            }
        }else if(Low[u] > dfn[v]) Low[u] = dfn[v];
    }
    if(u == la && son > 1) cut[u] = 1;
    if(u == la) add_block[u] = son - 1;
    Instack[u] = false;
    top--; 
}
int solve(){
    for(int i = 0 ; i <= N + 1; i ++)cut[i] = add_block[i] = dfn[i] = Instack[i] = 0;
    Index = top = 0;
    int ans = 0;
    for(int i = 1; i <= N ; i ++) if(!dfn[i]) Tarjan(i,i);
    for(int i = 1; i <= N ; i ++) ans += cut[i];
    return ans;
}
int main(){
    N = read(); M = read(); init();
    for(int i = 1; i <= M ; i ++){
        int u = read(), v = read();
        add(u,v); add(v,u);
    }
    Pri(solve());
    for(int i = 1; i <= N ; i ++) if(cut[i]) printf("%d ",i);
    return 0;
}
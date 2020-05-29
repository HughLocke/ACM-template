//点的双联通分量
//一个割点可能被多个点双包含，一个割边不会被多个边双包含
const int maxn = 5e5 + 10;
const int INF = 0x3f3f3f3f;
const int mod = 998244353; 
int N,M,K;
struct Edge{
    int to,next;
    bool vis;
}edge[maxn * 2];
int head[maxn],tot;
void init(){
    for(int i = 0 ; i <= N ; i ++) head[i] = -1;
    tot = 0;
}
void add(int u,int v){
    edge[tot].to = v;
    edge[tot].vis = 0;
    edge[tot].next = head[u];
    head[u] = tot++;
}
int Low[maxn],dfn[maxn],Stack[maxn];
bool Instack[maxn],cut[maxn];
int Index,top;
int dcn; //点双的个数 
vector<int>dcc[maxn];//每个点双含有的点 
void Tarjan(int u,int la){
    Low[u] = dfn[u] = ++Index;
    Stack[++top] = u;
    for(int i = head[u]; ~i; i = edge[i].next){
        int v = edge[i].to;
        if(v == la) continue;
        if(!dfn[v]){
            Tarjan(v,u);
            if(Low[u] > Low[v]) Low[u] = Low[v];
            if(Low[v] >= dfn[u]){
                cut[u] = 1;
                dcn++;
                dcc[dcn].clear();
                dcc[dcn].pb(u);
                while(1){
                    int w = Stack[top--];
                    dcc[dcn].pb(w);
                    if(w == v) break;
                }
            }
        }else if(Low[u] > dfn[v]) Low[u] = dfn[v];
    }
}
LL q_p(LL a,LL b){
    LL ans = 1;
    while(b){
        if(b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}
int main(){
    Sca2(N,M); init();
    for(int i = 1; i <= M ; i ++){
        int u,v; Sca2(u,v); 
        add(u,v); add(v,u);
    }
    dcn = Index = top = 0;
    for(int i = 1; i <= N; i ++){
        Low[i] = dfn[i] = Stack[i] = Instack[i] = cut[i] = 0;
    }
    LL sum = 1;
    int cnt = 0;
    for(int i = 1; i <= N ; i ++){
        if(!dfn[i]) Tarjan(i,-1);
    }
    for(int i = 1; i <= dcn; i ++){
        int v = dcc[i].size();
        if(v == 2) cnt++;
        else if(v > 2) sum = sum * (q_p(2,v) - 1 + mod) % mod;
    } 
    sum = sum * q_p(2,cnt) % mod;
    Prl(sum);
    
    return 0;
}
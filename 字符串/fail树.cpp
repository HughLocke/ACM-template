//fail树：将AC自动机上的所有fail指针反向，就形成了一颗fail树
//fail树所有的父节点是子节点的在所有单词中的最长后缀
//所以同一个AC自动机中，串x包含被其他所有串包含的次数就是x尾结点在fail树上的子树大小
//若要求x被y包含的次数，则仅将y到根节点的所有结点val值 ++ ，求x的子树大小即可
//模板 ： 洛谷P3966 求出每个单词在所有单词中出现的次数
const int maxm = 5e5 + 10;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7; 
int N,M,K;
int head[maxm],tot;
struct Edge{
    int to,next;
}edge[maxm];
void init(int cnt){
    for(int i = 0 ; i <= cnt ; i ++) head[i] = -1;
    tot = 0;
}
void add(int u,int v){
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot++;
}
int nxt[maxm][26],fail[maxm],cnt[maxm];
int ttt,root;
int newnode(){
    for(int i = 0 ; i < 26; i ++) nxt[ttt][i] = -1;
    cnt[ttt] = 0;
    return ttt++;
}
void INIT(){
    ttt = 0;
    root = newnode();
}
int insert(char *str){
    int p = root;
    for(int i = 0; str[i]; i ++){
        int id = str[i] - 'a';
        if(nxt[p][id] == -1) nxt[p][id] = newnode();
        p = nxt[p][id];
        cnt[p]++;
    }
    return p;
}
void Build(){
    queue<int>Q;
    for(int i = 0; i < 26; i ++){
        if(nxt[root][i] == -1){
            nxt[root][i] = 0;
        }else{
            fail[nxt[root][i]] = root;
            Q.push(nxt[root][i]);
            add(root,nxt[root][i]);
        }
    }
    while(!Q.empty()){
        int u = Q.front(); Q.pop();
        for(int i = 0 ; i < 26; i ++){
            if(nxt[u][i] == -1){
                nxt[u][i] = nxt[fail[u]][i];
            }else{
                fail[nxt[u][i]] = nxt[fail[u]][i];
                add(nxt[fail[u]][i],nxt[u][i]);
                Q.push(nxt[u][i]);
            }
        }
    }
}
void dfs(int t,int la){
    for(int i = head[t]; ~i ; i = edge[i].next){
        int v = edge[i].to;
        if(v == la) continue;
        dfs(v,t);
        cnt[t] += cnt[v];
    }
}
int Index[maxn];
char str[1000010];
int main(){
    Sca(N); INIT();
    for(int i = 1; i <= N ; i ++){
        scanf("%s",str);
        Index[i] = insert(str);
    }
    init(ttt);
    Build();
    dfs(root,0);
    for(int i = 1; i <= N ; i ++){
        Pri(cnt[Index[i]]);
    }
    return 0;
}
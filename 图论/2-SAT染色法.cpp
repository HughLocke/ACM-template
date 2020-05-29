//染色法
/* 当题目对字典序有要求的时候，就只能采用比较朴素的方法
在原来的图上，很显然相邻的点不能同时取到，那就是寻找一个字典序最小的染色方法
从小到大枚举点，如果能给这个点涂色就涂上，否则给i'涂色，如果这也不行，则没有可行方案
*/
//模板：1，2//3，4//5，6为各自组的点，为了使得i' = i ^ 1,将所有编号--，变为0,1//2,3//4,5
//给出的约束是u,v两点不能同时涂色
const int maxn = 20010;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7; 
int N,M,K;
struct Edge{
    int to,next;
}edge[maxn << 2];
int head[maxn],tot;
void init(){
    for(int i = 0 ; i <= (N << 1) ; i ++) head[i] = -1;
    tot = 0;
}
void add(int u,int v){
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot++;
}
int color[maxn],top;
int Stack[maxn];
bool dfs(int t){
    if(color[t]) return true;
    if(color[t ^ 1]) return false;
    color[t] = 1;
    Stack[++top] = t;
    for(int i = head[t]; ~i; i = edge[i].next){
        int v = edge[i].to;
        if(!dfs(v)) return false;
    }
    return true;
}
bool solve(){
    for(int i = 0 ; i <= (N << 1); i ++) color[i] = 0;
    for(int i = 0; i < (N << 1) ; i += 2){
        if(!color[i] && !color[i + 1]){
            top = 0;
            if(dfs(i)) continue;
            for(int j = 1; j <= top; j ++) color[Stack[j]] = 0;
            if(!dfs(i + 1)) return false;
        }
    }
    return true;
}
int main(){
    while(~Sca2(N,M)){
        init();
        for(int i = 1; i <= M ; i ++){
            int u,v; Sca2(u,v);
            u--; v--;
            add(u,v ^ 1); add(v,u ^ 1);
        }
        if(solve()){
            for(int i = 0; i < (N << 1); i ++){
                if(color[i]) Pri(1 + i);
            }
        }else{
            puts("NIE");
        }
    }
    return 0;
}
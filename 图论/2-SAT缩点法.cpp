//2-SAT
/*
2—SAT:给出n个布尔变量以及一堆约束，让你寻找其中的可行解
约束的方式形如1.必须(不)选a 2.a与b必须选一个(不能都选) 3.a,b选择情况相同(相反)等等最多由两个变量建立起的约束。
对于这一类的问题，考虑用图论的方式解决，将一个点i拆点为i与i + N，i表示这个值为1，i + N表示为0
a -> b的边表示如果a则b
构图方法: 以下a表示a这个点，a'表示a + N这个点
1.必选a: a'->a     2.必不选a:a->a'
2.a,b中选择一个:a'->b,b'->a    3.a,b不都选:a->b',b->a'
4.a,b选择情况相同 a->b,b->a,a'->b',b'->a'
5.a,b选择情况相反 a->b',b->a',a'->b,b'->a
诸如此类。
*/
/*     Tarjan缩点法
如果题目不要求字典序最小，只要求输出任意一组，我们可以考虑Tarjan缩点的做法
注意到同一个强连通分量里面的点必定互相满足，也就是说如果任意存在一个i使得i 和 i'在一个强连通分量内，
则说明题目无解，因为不可能一个点即为false又为true。
其次，缩点之后会形成一个DAG图，如果拓扑序排在前面的满足，那么拓扑序排在后面的也需要满足。
为了防止出现形如i为i'的前驱，选了i之后会满足i'成立这样的错误情况出现，对于每个点都选取拓扑序较后面的那一个
也就是如果i -> i'，则选i为false一定不会错，但这样的操作无法满足字典序最小，如果要求字典序，需要采用染色法
我们不必特意去跑拓扑，因为Tarjan标记出的强连通分量编号满足逆拓扑序，编号较小的点即为拓扑序在后面的点。
*/
const int maxn = 2e6 + 10;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7; 
int N,M,K;
struct Edge{
    int to,next;
}edge[maxn << 1];
int head[maxn],tot;
void init(){
    for(int i = 0; i <= (N << 1); i ++) head[i] = -1;
    tot = 0;
}
void add(int u,int v){
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot++;
}
int Low[maxn],dfn[maxn],Stack[maxn],Belong[maxn],num[maxn];
int Index,top,scc;
bool Instack[maxn];
void Tarjan(int u){
    int v;
    Low[u] = dfn[u] = ++Index;
    Stack[top++] = u;
    Instack[u] = true;
    for(int i = head[u]; ~i ; i = edge[i].next){
        v = edge[i].to;
        if(!dfn[v]){
            Tarjan(v);
            if(Low[u] > Low[v]) Low[u] = Low[v];
        }else if(Instack[v] && Low[u] > dfn[v]) Low[u] = dfn[v];
    }
    if(Low[u] == dfn[u]){
        scc++;
        do{
            v = Stack[--top];
            Instack[v] = false;
            Belong[v] = scc;
            num[scc]++;
        }while(v != u);
    }
}
int main(){
    Sca2(N,M); init();
    for(int i = 1; i <= M ; i ++){
        int x,a,y,b;
        scanf("%d%d%d%d",&x,&a,&y,&b);
        add(x + a * N,y + (b ^ 1) * N);
        add(y + b * N,x + (a ^ 1) * N);
    }
    for(int i = 1; i <= (N << 1); i ++) if(!dfn[i]) Tarjan(i);
    for(int i = 1; i <= N; i ++){
        if(Belong[i] == Belong[i + N]){
            puts("IMPOSSIBLE");
            return 0;
        }
    }
    puts("POSSIBLE");
    for(int i = 1; i <= N ; i ++){
        if(Belong[i] < Belong[i + N]) printf("1 ");
        else printf("0 ");
    }
    return 0;
}
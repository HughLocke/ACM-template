/*树上k半径覆盖问题
一个点覆盖距离他最长为k的所有点，求一棵树上最少几个点可以全覆盖
贪心做法，从叶子结点向上遍历，每次遇到不得不放点的位置就在他往上k个位置放点。
*/
//例题 洛谷P2279 一个点覆盖最长距离为2的所有点，求做小覆盖点数
const int maxn =2010;
int N,M,K;
int fa[maxn],deep[maxn],a[maxn],o[maxn]; //a数组用来排序，o数组记录和最近的已经放的点还有多少距离
bool cmp(int a,int b){
    return deep[a] > deep[b];
}
int main(){
    Sca(N);  o[1] = INF;
    fa[1] = N + 1;
    fa[N + 1] = N + 2;
    o[N + 1] = o[N + 2] = INF;
    for(int i = 1; i <= N; i ++) a[i] = i; 
    for(int i = 2; i <= N ; i ++){
        Sca(fa[i]);
        deep[i] = deep[fa[i]] + 1;
        o[i] = INF;
    }
    sort(a + 1,a + 1 + N,cmp);
    int ans = 0;
    for(int i = 1; i <= N ; i ++){
        int u = a[i];
        int v = fa[u],w = fa[fa[u]];
        o[u] = min(o[u],min(o[v] + 1,o[w] + 2));
        if(o[u] > 2){
            o[w] = 0;
            o[fa[w]] = min(o[fa[u]],1);
            o[fa[fa[w]]] = min(o[fa[fa[w]]],2);
            ans++;
        }
    }
    Pri(ans);
    return 0;
}

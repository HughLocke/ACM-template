//左偏树(可并堆)
//用来合并两个堆(优先队列)的数据结构
/*
模板 op1:合并两个下标所在的堆
op:2输出下标所在堆的最小值并pop，key值相同先pop下标小的那个
做法：维护每个小根堆 
*/
const int maxn = 1e5 +10;

int N,M;
struct node{
    int l,r,dis,key;
}tree[maxn];
int fa[maxn];
int find(int x){
    if(fa[x] == x) return x;  
    return fa[x] = find(fa[x]);   //路径压缩
}
int merge(int a,int b){
    if(!a) return b;
    if(!b) return a;
    if(tree[a].key >tree[b].key) swap(a,b);
    if((tree[a].key == tree[b].key) && (a > b)) swap(a,b);
    tree[a].r = merge(tree[a].r,b);
    fa[tree[a].r] = a;
    if(tree[tree[a].l].dis < tree[tree[a].r].dis)
        swap(tree[a].l,tree[a].r);
    if(tree[a].r) tree[a].dis = tree[tree[a].r].dis + 1;
    else tree[a].dis = 0;
    return a;
}
bool vis[maxn];
int pop(int a){   
    int l = tree[a].l;
    int r = tree[a].r;
    fa[l] = l; fa[r] = r;
    vis[a] = 1;
    return fa[a]= merge(l,r);  //少了这步不能路径压缩
}
int a[maxn];

int main(){
    scanf("%d%d",&N,&M);
    for(int i = 1; i <= N ; i ++){
        scanf("%d",&tree[i].key); fa[i] = i;
        tree[i].l = tree[i].r = tree[i].dis = 0;
    }
    for(int i = 1; i <= M ; i ++){
        int op; scanf("%d",&op);
        if(op == 1){
            int x,y; scanf("%d%d",&x,&y);
            if(vis[x] || vis[y]) continue;
            x = find(x); y = find(y);
            if(x == y) continue;
            merge(x,y);
        }else{
            int x; scanf("%d",&x);
            if(vis[x]){
                puts("-1");continue;
            }
            x = find(x);
            printf("%d\n",tree[x].key);
            pop(x);
        }
    }
    return 0;
}
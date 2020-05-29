/*用可持久化数组维护并查集的fa数组，模板为BZOJ3674
强制在线，每个值 ^ lastans
n个集合 m个操作
操作：
1 a b 合并a,b所在集合
2 k 回到第k次操作之后的状态(查询算作操作)
3 a b 询问a,b是否属于同一集合，是则输出1否则输出0
*/
const int maxn = 2e5 + 10;
int N,M,K;
int T[maxn],tot;
struct Tree{
    int lt,rt;
    int fa,size;
}tree[maxn * 52];
int fa[maxn],Size[maxn];
void newnode(int &t){
    t = ++tot;
    tree[t].lt = tree[t].rt = tree[t].fa = 0;
}
void Build(int &t,int l,int r){
    newnode(t);
    if(l == r){
        tree[t].fa = l;
        tree[t].size = 0;
        return;
    }
    int m = l + r >> 1;
    Build(tree[t].lt,l,m); Build(tree[t].rt,m + 1,r);
}
int query(int t,int l,int r,int x){
    if(l == r){
        Size[x] = tree[t].size;
        return tree[t].fa;
    }
    int m = l + r >> 1;
    if(x <= m) return query(tree[t].lt,l,m,x);
    else return query(tree[t].rt,m + 1,r,x);
}
void update(int &t,int pre,int l,int r,int x){
    newnode(t);
    tree[t] = tree[pre];
    if(l == r){
        tree[t].fa = fa[x];
        tree[t].size = Size[x];
        return;
    }
    int m = l + r >> 1;
    if(x <= m) update(tree[t].lt,tree[pre].lt,l,m,x);
    else update(tree[t].rt,tree[pre].rt,m + 1,r,x);
}
int find(int id,int x){
    int f = query(T[id],1,N,x);
    if(f == x) return x;
    return find(id,f);
}
int main(){
    //freopen("C.in","r",stdin);
    Sca2(N,M);    
    Build(T[0],1,N);
    int ans = 0; 
    for(int i = 1; i <= M; i ++){
        int op = read();
        if(op == 1){
            int a = read() ^ ans,b = read() ^ ans;
            a = find(i - 1,a); b = find(i - 1,b);
            if(Size[a] > Size[b]) swap(a,b);
            fa[a] = b;
            update(T[i],T[i - 1],1,N,a);
            if(Size[a] == Size[b]){
                Size[b]++; fa[b] = b;
                int x;
                update(x,T[i],1,N,b);
                T[i] = x;
            } 
        }else if(op == 2){
            int k = read() ^ ans;
            T[i] = T[k];
        }else if(op == 3){
            T[i] = T[i - 1];
            int a = read() ^ ans,b = read() ^ ans;
            a = find(i,a); b = find(i,b);
            ans = (a == b);
            if(a == b) puts("1");
            else puts("0");
        }    
        
    }
    return 0;
}
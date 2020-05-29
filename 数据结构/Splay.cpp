//Splay 伸展树
/*
再二叉搜索树的基础上增加了伸展(splay)功能，降低了查询和插入的时间复杂度。
本质上是通过将每一次查询的节点都进行伸展使其靠近根节点
 */
 //luogu 普通平衡树
const int maxn = 1e5 + 10;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7; 
int N,M,K;
struct Splay{
    #define root e[0].ch[1]
    struct node{
        int ch[2];
        int sum,num;
        int v,fa;
    }e[maxn];
    int n,points;
    void update(int x){
        e[x].sum = e[e[x].ch[0]].sum + e[e[x].ch[1]].sum + e[x].num; 
    }
    int id(int x){
        return x == e[e[x].fa].ch[0]?0:1;
    }
    void connect(int x,int y,int p){
        e[x].fa = y;
        e[y].ch[p] = x;
    }
    int find(int v){
        int now = root;
        while(1){
            if(e[now].v == v){
                splay(now,root);
                return now;
            }
            int next = v < e[now].v?0:1;
            if(!e[now].ch[next]) return 0;
            now = e[now].ch[next];
        }
        return 0;
    }
    void rotate(int x){
        int y = e[x].fa;
        int z = e[y].fa;
        int ix = id(x),iy = id(y);
        connect(e[x].ch[ix ^ 1],y,ix);
        connect(y,x,ix ^ 1);
        connect(x,z,iy);
        update(y); update(x);
    }
    void splay(int u,int v){
        v = e[v].fa;
        while(e[u].fa != v){
            int fu = e[u].fa;
            if(e[fu].fa == v) rotate(u);
            else if(id(u) == id(fu)){
                rotate(fu);
                rotate(u);
            }else{
                rotate(u);
                rotate(u);
            }
        }
    }
    int crenode(int v,int father){
        n++;
        e[n].ch[0] = e[n].ch[1] = 0;
        e[n].fa = father;
        e[n].num = e[n].sum = 1;
        e[n].v = v;
        return n;
    }
    void destroy(int x){
        e[x].v = e[x].fa = e[x].num = e[x].sum = e[x].v = 0;
        if (x == n) n--;
    }
    int insert(int v){
        points++;
        if(points == 1){
            n = 0;
            root = 1;
            crenode(v,0);
            return 1;
        }else{
            int now = root;
            while(1){
                e[now].sum++;
                if(v == e[now].v){
                    e[now].num++;
                    return now;        
                }
                int next = v < e[now].v?0:1;
                if(!e[now].ch[next]){
                    crenode(v,now);
                    e[now].ch[next] = n;
                    return n;
                }
                now = e[now].ch[next];
            }
        }
    }
    void push(int v){  //添加元素 
        int add = insert(v);
        splay(add,root);
    }
    void pop(int x){
        int pos = find(x);  //找到节点并作为根 
        if(!pos) return;
        points--;
        if(e[pos].num > 1){ 
            e[pos].num--;
            e[pos].sum--;   //他已经是根节点了，不需要更新祖先的sum了 
            return; 
        }
        if(!e[pos].ch[0]){       //没有左孩子就直接删除，右孩子作为根 
            root = e[pos].ch[1];
            e[root].fa = 0;
        }else{          //有左孩子： 将左子树最大的点转到根，将右子树连到它上 
            int lef = e[pos].ch[0];
            while(e[lef].ch[1]) lef = e[lef].ch[1];
            splay(lef,e[pos].ch[0]);
            int rig = e[pos].ch[1];
            connect(rig,lef,1); connect(lef,0,1);
            update(lef);
        }
        destroy(pos);
    }
    int atrank(int x){
        if(x > points) return -INF;
        int now = root;
        while(1){
            int mid = e[now].sum - e[e[now].ch[1]].sum;
            if(x > mid){
                x -= mid;
                now = e[now].ch[1];
            }else if(x <= e[e[now].ch[0]].sum){
                now = e[now].ch[0];
            }else break;
        }
        splay(now,root);
        return e[now].v;
    }
    int rank(int x){
        int now = find(x);
        if(!now) return 0;
        return e[e[now].ch[0]].sum + 1;
    }
    int upper(int v){
        int now = root;
        int ans = INF;
        while(now){
            if(e[now].v > v && e[now].v < ans) ans = e[now].v;
            if(v < e[now].v) now = e[now].ch[0];
            else now = e[now].ch[1];
        }
        return ans;
    }
    int lower(int v){
        int now = root;
        int ans = -INF;
        while(now){
            if(e[now].v < v && e[now].v > ans) ans = e[now].v;
            if(v > e[now].v) now = e[now].ch[1];
            else now = e[now].ch[0];
        }
        return ans;
    }
    #undef root
}F;
int main(){
    Sca(N);
    while(N--){
        int x,op; Sca2(op,x);
        if(op == 1) F.push(x);    //插入一个元素
        else if(op == 2) F.pop(x);   //删除一个元素
        else if(op == 3) Pri(F.rank(x));   //查询x数的排名(排名定义为比当前数小的数的个数+1+1。若有多个相同的数，因输出最小的排名)
        else if(op == 4) Pri(F.atrank(x)); //查询排名为x的数
        else if(op == 5) Pri(F.lower(x));  //求xx的前驱(前驱定义为小于xx，且最大的数)
        else Pri(F.upper(x)); //求xx的后继(后继定义为大于xx，且最小的数)
    }
    return 0;
}

//Splay合并咋整鸭
//启发式合并，将小的合并到大的上去，用中序遍历的方式暴力插入，时间复杂度ln级别
/* 题意
永无乡包含n座岛，编号从 1到 n，
每座岛都有自己的独一无二的重要度，按照重要度可以将这 n座岛排名，
名次用 1到 n来表示。某些岛之间由巨大的桥连接，通过桥可以从一个岛到达另一个岛。
如果从岛 a出发经过若干座（含 0座）桥可以到达岛 b,则称岛 a和岛 b是连通的。
B x y 表示在岛x与岛y之间修建一座新桥。
Q x k 表示询问当前与岛x连通的所有岛中第k重要的是哪座岛，
即所有与岛x连通的岛中重要度排名第k小的岛是哪座，请你输出那个岛的编号。
 */
 const int maxn = 5e5 + 10;
const int maxm = 3e5 + 10;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7; 
int N,M,K;
struct node{
    int ch[2];
    int sum,v,fa,id;
}e[maxn];
int n,points[maxn];
int root[maxn],tree[maxn];
int crenode(int v,int id,int fa){
    n++;
    e[n].ch[0] = e[n].ch[1] = 0;
    e[n].fa = fa;
    e[n].sum = 1;
    e[n].v = v; e[n].id = id;
    return n;
}
int id(int x){
    return x == e[e[x].fa].ch[0]?0:1; 
}
void connect(int u,int v,int p){
    e[u].fa = v; e[v].ch[p] = u;
}
void update(int x){
    e[x].sum = e[e[x].ch[0]].sum + e[e[x].ch[1]].sum + 1;
}
int insert(int t,int num){
    points[num]++;
    int now = root[num];
    int v = e[t].v;
    while(1){
        e[now].sum++;
        int nxt = v < e[now].v?0:1;
        if(!e[now].ch[nxt]){
            connect(t,now,nxt);
            e[t].ch[0] = e[t].ch[1] = 0;
            e[t].sum = 1;
            return t;
        }
        now = e[now].ch[nxt];
    }
}

void rotate(int x){
    int y = e[x].fa;
    int z = e[y].fa;
    int ix = id(x),iy = id(y);
    connect(e[x].ch[ix ^ 1],y,ix);
    connect(y,x,ix ^ 1);
    connect(x,z,iy);
    update(y); update(x);
}
void splay(int u,int v){
    v = e[v].fa;
    while(e[u].fa != v){
        int fu = e[u].fa;
        if(e[fu].fa == v) rotate(u);
        else if(id(u) == id(fu)){
            rotate(fu);
            rotate(u);
        }else{
            rotate(u);
            rotate(u);
        }
    }
    if(v <= N) root[v] = u;
}

void push(int t,int num){
    int x = insert(t,num);
    splay(x,root[num]);
}
int find(int p){
    return p == tree[p]?p:tree[p] = find(tree[p]);
}
void dfs(int t,int num){
    int l = e[t].ch[0],r = e[t].ch[1];
    if(l) dfs(l,num);
    push(t,num);       //中序遍历合并是log复杂度 
    if(r) dfs(r,num);
}
void Union(int u,int v){
    int x = find(u),y = find(v);
    if(x == y) return;
    if(points[x] > points[y]) swap(x,y);
    tree[x] = y;
    dfs(root[x],y);
}
int Kth(int id,int k){
    if(points[id] < k) return -1;
    int now = root[id];
    while(1){
        int mid = e[now].sum - e[e[now].ch[1]].sum;
        if(k > mid){
            k -= mid;
            now = e[now].ch[1];
        }else if(k <= e[e[now].ch[0]].sum){
            now = e[now].ch[0];
        }else break;
    }
    splay(now,root[id]);
    return e[now].id;
}
int main(){
    Sca2(N,M);
    n = N;      //1 ~ N表示每颗平衡树的0点
    for(int i = 1; i <= N ; i ++){
        tree[i] = i;
        int v; Sca(v);
        points[i] = 1;
        root[i] = crenode(v,i,i);   
    }
    for(int i = 1; i <= M; i ++){
        int u,v; Sca2(u,v);
        Union(v,u);
    }
    int Q; Sca(Q);
    while(Q--){
        char op[2]; int x,y;
        scanf("%s%d%d",op,&x,&y);
        if(op[0] == 'B') Union(x,y);
        else Pri(Kth(find(x),y));
    }
    return 0;
}
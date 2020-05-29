//区间离散化
/*
    涉及到区间修改的离散化是和普通离散化不同的
    假设修改20 - 30,查询10 - 40
    常规的离散化变成1，2，3，4之后线段树修改2,3两个点，询问1-4的sum
    但是修改的时候会分开修改2和3，这和我们想要的不一样
    因为离散化区间是不能直接相加的，[2,2] + [3,3] = [2,3]是没毛病，[20,20] + [30,30] = [20,30]就有问题了
    所以我们希望他的区间可以直接相加
    寻常的线段树是左右都闭，我们需要把它转化为左闭右开的区间
    让他变为[2,3) + [3,4) = [2,4)  => [20,30) + [30,31) = [20,31)
    所以说，我们离散化的时候需要离散的是l和r + 1而不是寻常的l,r
 */
LL read(){LL x = 0,f = 1;char c = getchar();while (c<'0' || c>'9'){if (c == '-') f = -1;c = getchar();}
while (c >= '0'&&c <= '9'){x = x * 10 + c - '0';c = getchar();}return x*f;}
const double eps = 1e-9;
const int maxn = 8e5 + 10;
LL N;
int M;
struct Query{
    int op;
    LL a,b,c;
}query[maxn];
LL Hash[maxn * 2];
struct Tree{
    int l,r;
    ULL sum,lazy;
}tree[maxn * 4];
void Build(int t,int l,int r){
    tree[t].l = l; tree[t].r = r;
    tree[t].sum = tree[t].lazy = 0;
    if(r - l <= 1) return;
    int m = l + r >> 1;
    Build(t << 1,l,m);
    Build(t << 1 | 1,m,r);
}
void Pushup(int t){
    tree[t].sum = tree[t << 1].sum + tree[t << 1 | 1].sum;
}
void solve(int t,ULL p){
    tree[t].lazy = p + tree[t].lazy;
    tree[t].sum = tree[t].sum + ((ULL)Hash[tree[t].r] - (ULL)Hash[tree[t].l]) * p;
}
void Pushdown(int t){
    if(tree[t].lazy){
        solve(t << 1,tree[t].lazy);
        solve(t << 1 | 1,tree[t].lazy);
        tree[t].lazy = 0;
    }
}
void update(int t,int l,int r,ULL p){
    if(l <= tree[t].l && tree[t].r <= r){
        solve(t,p);
        return;
    }
    Pushdown(t);
    int m = (tree[t].l + tree[t].r) >> 1;
    if(r <= m) update(t << 1,l,r,p);
    else if(l >= m) update(t << 1 | 1,l,r,p);
    else{
        update(t << 1,l,m,p);
        update(t << 1 | 1,m,r,p);
    }
    Pushup(t);
}
ULL _query(int t,int l,int r){
    if(l <= tree[t].l && tree[t].r <= r){
        return tree[t].sum;
    }
    Pushdown(t);
    int m = (tree[t].l + tree[t].r) >> 1;
    if(r <= m) return _query(t << 1,l,r);
    else if(l >= m) return _query(t << 1 | 1,l,r);
    else{
        return _query(t << 1,l,m) + _query(t << 1 | 1,m,r);
    }
}
int main(){
    cin >> N >> M;
    int cnt = 0;
    for(int i = 1; i <= M; i ++){
        query[i].op = read();
        query[i].a = read();
        query[i].b = read();
        if(query[i].op == 1) query[i].c = read();
        Hash[++cnt] = query[i].a;
       // Hash[++cnt] = query[i].b;
        Hash[++cnt] = query[i].b + 1;
    }    
    sort(Hash + 1,Hash + 1 + cnt);
    cnt = unique(Hash + 1,Hash + 1 + cnt) - Hash - 1;
    Build(1,1,cnt);
    for(int i = 1; i <= M; i ++){
        query[i].a = lower_bound(Hash + 1,Hash + 1 + cnt,query[i].a) - Hash;
        query[i].b = lower_bound(Hash + 1,Hash + 1 + cnt,query[i].b + 1) - Hash;
        if(query[i].op == 1) update(1,query[i].a,query[i].b,query[i].c);
        else{
            ULL ans = _query(1,query[i].a,query[i].b);
            cout << ans << endl;
        }
    }
    return 0;
}
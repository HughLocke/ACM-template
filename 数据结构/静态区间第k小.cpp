//静态区间第K小 nlogn
const int maxn = 2e5 + 10;
int N,M,K;
int Hash[maxn],a[maxn];
int T[maxn];
struct Tree{
    int lt,rt,sum;
    void init(){
        lt = rt = sum = 0;
    }
}tree[maxn * 60];
int tot;
void newnode(int &t){
    t = ++tot;
    tree[t].init();
}
void Build(int &t,int l,int r){
    newnode(t);
    if(l == r) return;
    int m = l + r >> 1;
    Build(tree[t].lt,l,m); Build(tree[t].rt,m + 1,r);
}
void update(int &t,int pre,int l,int r,int p){
    newnode(t);
    tree[t] = tree[pre];
    tree[t].sum++;
    if(l == r) return;
    int m = l + r >> 1;
    if(p <= m) update(tree[t].lt,tree[pre].lt,l,m,p);
    else update(tree[t].rt,tree[pre].rt,m + 1,r,p);
}
int query(int L,int R,int l,int r,int k){
    if(l >= r) return l;
    int num = tree[tree[R].lt].sum - tree[tree[L].lt].sum;
    int m = l + r >> 1;
    if(num >= k) return query(tree[L].lt,tree[R].lt,l,m,k);
    else return query(tree[L].rt,tree[R].rt,m + 1,r,k - num);
}
int main(){
    Sca2(N,M);
    for(int i = 1; i <= N ; i ++) Hash[i] = a[i] = read();
    sort(Hash + 1,Hash + 1 + N);
    int cnt = unique(Hash + 1,Hash + 1 + N) - Hash - 1;
    Build(T[0],1,cnt);
    for(int i = 1; i <= N ; i ++){
        int p = lower_bound(Hash + 1,Hash + 1 + cnt,a[i]) - Hash;
        update(T[i],T[i - 1],1,cnt,p);    
    }
    for(int i = 1; i <= M ; i ++){
        int l = read(),r = read(),k = read();
        Pri(Hash[query(T[l - 1],T[r],1,cnt,k)]);
    }
    return 0;
}
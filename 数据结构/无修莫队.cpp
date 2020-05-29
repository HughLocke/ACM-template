//无修莫队 时间复杂度n√n 
//小z的袜子 查询区间内任选两个颜色相同的概率，用分数表示
const int maxn = 50010;
const int maxm = 50010;
int N,M,K,unit;
struct Query{
    int L,R,id;
    int l,r;
}node[maxm];
struct Ans{
    LL up,down;
    void reduce(){
        if(!up || !down){
            up = 0;
            down = 1;
            return;
        } 
        LL g = __gcd(up,down);
        up /= g; down /= g;
    }
}ans[maxm];
int a[maxn];
bool cmp(Query a,Query b){
    if(a.l != b.l) return a.l < b.l;
    return a.r < b.r;
}
int num[maxn];
LL up,down,sum;    
void add(int t){
    down += sum; sum++; 
    up += num[t]; num[t]++;
}
void del(int t){
    sum--; down -= sum;
    num[t]--; up -= num[t];
}
void solve(){
    int L = 1,R = 0;
    sum = up = down = 0;
    for(int i = 1; i <= M ; i ++){
        while(R < node[i].R) add(a[++R]);
        while(R > node[i].R) del(a[R--]);
        while(L < node[i].L) del(a[L++]);
        while(L > node[i].L) add(a[--L]);    
        ans[node[i].id].up = up;
        ans[node[i].id].down = down;
    }
}
int main(){
    Sca2(N,M); unit = (int)sqrt(N);
    for(int i = 1; i <= N ; i ++) Sca(a[i]);
    for(int i = 1; i <= M ; i ++){
        Sca2(node[i].L,node[i].R); node[i].id = i;
        node[i].l = node[i].L / unit;
        node[i].r = node[i].R / unit;
    } 
    sort(node + 1,node + 1 + M,cmp);
    solve();
    for(int i = 1; i <= M ; i ++){
        ans[i].reduce();
        printf("%lld/%lld\n",ans[i].up,ans[i].down);
    }
    return 0;
}
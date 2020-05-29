/*例题：无修改求区间L-R出现次数 * 权值最大的点
问题：普通的莫队无法删除，因为删除了最大值之后无法直接找到次大值
解决方法：按照左端点所在的块排序，相同的块按照右端点排序
对于左右端点相同块的询问直接暴力 √n
对于左端点处于同一块的询问一起处理，因为右端点递增，所以右端点只有删除惭怍
对于左端点，每次将左端点初始化到所在块的最右端，先向右扩充之后记录当前答案tmp，然后向左扩充到当前询问的左端点，找到当前询问的答案之后回溯到最右端，答案也返回tmp
虽然依然有删除操作，但是因为我们之前记录过tmp,避免了真正删除完寻找答案的过程
时间复杂度n√n
*/
//BZOJ 4241
const int maxn = 1e5 + 10;
int N,M,K,Q,unit;
LL a[maxn],Hash[maxn];
int belong[maxn]; //每个点所在块的编号
struct Query{
    int l,r,id;
}query[maxn];
bool cmp(Query a,Query b){
    if(belong[a.l] == belong[b.l]) return a.r < b.r;
    return belong[a.l] < belong[b.l];
}
LL vis[maxn],Max;
LL ans[maxn];
void add(int p){
    vis[a[p]]++;
    if(vis[a[p]] * Hash[a[p]]> Max){
        Max = vis[a[p]] * Hash[a[p]];
    }
}
void del(int p){
    vis[a[p]]--;
}
LL use[maxn];
LL cul(int l,int r){
    LL sum = 0;
    for(int i = l; i <= r; i ++){
        use[a[i]]++;
        sum = max(sum,use[a[i]] * Hash[a[i]]);
    }
    for(int i = l; i <= r; i ++) use[a[i]]--;
    return sum;
}
void solve(){
    int up = N / unit;
    int j = 1;
    for(int i = 0; i <= up; i ++){
        Max = 0;
        LL L = (i + 1) * unit,R = L - 1,la,normal = L;
        for(;j <= Q && belong[query[j].l] == i; j ++){  //对于所有左端点在一个块里的单独处理
            if(belong[query[j].r] == i){  //如果处于同一个块 就暴力
                ans[query[j].id] = cul(query[j].l,query[j].r);
                continue;
            }
            while(R < query[j].r) add(++R);   //先扩充右边的
            la = Max;                        //记录下当前答案
            while(L > query[j].l) add(--L);  //再扩充左边的
            ans[query[j].id] = Max;          //真正的答案
            while(L < normal) del(L++);       //回溯，删除之前扩充的左边的
            Max = la;                        //回溯答案
        }
        while(L <= R) del(L++);             
    }
}
int main(){
    Sca2(N,Q); unit = (int)sqrt(N);
    for(int i = 1; i <= N ; i ++) Hash[i] = a[i] = read();
    sort(Hash + 1,Hash + 1 + N);
    int cnt = unique(Hash + 1,Hash + 1 + N) - Hash - 1;
    for(int i = 1; i <= N ; i ++) a[i] = lower_bound(Hash + 1,Hash + 1 + cnt,a[i]) - Hash;
    for(int i = 1; i <= N ; i ++) belong[i] = i / unit;
    for(int i = 1; i <= Q; i ++){
        query[i].l = read(); query[i].r = read();
        query[i].id = i;
    }
    sort(query + 1,query + 1 + Q,cmp);
    solve();
    for(int i = 1; i <= Q; i ++) Prl(ans[i]);
    return 0;
}
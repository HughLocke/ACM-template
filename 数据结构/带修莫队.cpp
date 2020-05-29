//带修莫队 时间复杂度三次根号内(n ^ 4 * t)
//模板：带修询问区间颜色种类数
const int maxn = 150010;
int N,M,K,cnt,t,unit;
int a[maxn];
struct Update{
    int pre,aft;  //修改前和修改后
    int pos;    //修改的位置 
    Update(int pos = 0,int pre = 0,int aft = 0):pos(pos),pre(pre),aft(aft){}
}update[maxn];
struct Query{
    int l,r,t;
    int L,R;
    int upnum; //修改过的次数 
    Query(){}
    Query(int t,int l,int r,int upnum):t(t),l(l),r(r),upnum(upnum){}
}query[maxn];
bool cmp(Query a,Query b){
    if(a.L != b.L) return a.L < b.L;
    if(a.R != b.R) return a.R < b.R;
    return a.t < b.t;
}
int num[1000010],sum,ans[maxn];
void add(int t){
    num[t]++;
    sum += (num[t] == 1);
}
void del(int t){
    num[t]--;
    sum -= (num[t] == 0);
}
void solve(){
    int l = 1, r = 0,t = 0;
    sum = 0;
    for(int i = 1; i <= M ; i ++){
        while(query[i].l < l) add(a[--l]);
        while(query[i].l > l) del(a[l++]);
        while(query[i].r > r) add(a[++r]);
        while(query[i].r < r) del(a[r--]);
        while(query[i].upnum < t){
            int p = update[t].pos;
            if(l <= p && p <= r) del(a[p]);
            a[p] = update[t--].pre;
            if(l <= p && p <= r) add(a[p]);
        }
        while(query[i].upnum > t){
            int p = update[++t].pos;
            if(l <= p && p <= r) del(a[p]);
            a[p] = update[t].aft;
            if(l <= p && p <= r) add(a[p]);
        }
        ans[query[i].t] = sum;
    }
}
int main(){
    Sca2(N,M); cnt = t = 0;
    for(int i = 1; i <= N ; i ++) Sca(a[i]);
    for(int i = 1; i <= M ; i ++){
        char op[2]; scanf("%s",op);
        if(op[0] == 'R'){ //修改 
            int p = read(),c = read();//p点改为c
            update[++t] = Update(p,a[p],c); a[p] = c; 
        }else{
            cnt++; int l = read(),r = read();
            query[cnt] = Query(cnt,l,r,t);
        }
    }
    unit = ceil(exp((log(N) + log(t))/3));
    for(int i = t; i >= 1; i --) a[update[i].pos] = update[i].pre;  //初始化a数组
    for(int i = 1; i <= cnt ; i ++){
        query[i].L = query[i].l/unit;
        query[i].R = query[i].R/unit;
    }
    sort(query + 1,query + 1 + cnt,cmp); 
    solve();
    for(int i = 1; i <= cnt ; i ++) Pri(ans[i]);
    return 0;
}

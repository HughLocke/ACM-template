
/* 珂朵莉树
1.名称来源：从CF896C发明的算法，题干主角是动漫人物珂朵莉
2.解决一类问题：(1)含有区间赋值操作 (2)数据随机 (重要)
3.具体思路:
(1)用set存储每个区间的(l,r)端点和信息
(2)split:当出现新的在l,r之间的端点pos的时候将区间分为(l,pos- 1)(pos,r)
(3)assign:为了降低节点数量，区间赋值的时候把整个区间的结点都去掉，换一个Node(l,r,v)进去
 */
 //模板CF896C,区间加,区间赋值,区间K小,区间每个数K次方和
const int maxn = 1e5 + 10;
const int mod = 1e9 + 7; 
int N,M,K;
LL n,m,seed,vmax,ret;
LL rnd(){
    ret = seed;
    seed = (seed * 7 + 13) % mod;
    return ret;
} 
LL quick_power(LL a,LL b,LL Mod){
    LL ans = 1;
    a %= Mod;
    while(b){
        if(b & 1) ans = (ans * a) % Mod;
        b >>= 1;
        a = a * a % Mod;
    }
    return ans;
}
#define IT set<node>::iterator 
struct node{
    int l,r;
    mutable LL v; //表示可变的变量，突破const函数的限制
    node(int l,int r = -1,LL v = 0):l(l),r(r),v(v) {}
    friend bool operator < (node a,node b){
        return a.l < b.l;
    }
};
set<node>s;
//分割出左端点包含l的区间 
IT split(int pos){
    IT it = s.lower_bound(node(pos));
    if(it != s.end() && it->l == pos) return it;
    --it;
    int L = it->l,R = it->r;
    LL V = it->v;
    s.erase(it); 
    s.insert(node(L,pos - 1,V));
    return s.insert(node(pos,R,V)).first;
}
//推平l-r区间 
void assign(int l,int r,LL val){
    IT itr = split(r + 1),itl = split(l); //一定要先split(r + 1) 
    s.erase(itl,itr);
    s.insert(node(l,r,val)); 
}
void add(int l,int r,LL val){
    IT itr = split(r + 1),itl = split(l);
    for(;itl != itr; ++itl) itl->v += val;    
}
LL ranks(int l,int r,int k){ //第k小 
    vector<PLI> vp;
    IT itr = split(r + 1),itl = split(l);
    vp.clear();
    for(;itl != itr; ++itl) vp.pb(mp(itl->v,itl->r - itl->l + 1));
    sort(vp.begin(),vp.end());
    for(int i = 0 ; i < vp.size(); i ++){
        k -= vp[i].se;
        if(k <= 0) return vp[i].fi;
    }
}

LL sum(int l,int r,LL k,LL Mod){
    IT itr = split(r + 1),itl = split(l);
    LL ans = 0;
    for(;itl != itr; itl++) ans = (ans + (LL)(itl->r - itl->l + 1) * quick_power(itl->v,k,Mod)) % Mod;
    return ans;
}
LL a[maxn];
int main(){
    scanf("%lld%lld%lld%lld",&n,&m,&seed,&vmax);
    for(int i = 1; i <= n ; i ++){
        a[i] = (rnd() % vmax) + 1;
        s.insert(node(i,i,a[i]));
    } 
    s.insert(node(n + 1,n + 1,0)); //防止查询到空 
    for(int i = 1; i <= m ; i ++){
        int op = (rnd() % 4) + 1;
        int l = (rnd() % n) + 1,r = (rnd() % n) + 1;
        if(l > r) swap(l,r);
        int x,y;
        if(op == 3) x = (rnd() % (r - l + 1)) + 1;
        else x = (rnd() % vmax) + 1;
        if(op == 4) y = (rnd() % vmax) + 1;
        //以上随机 op,x,y,l,r
        if(op == 1) add(l,r,x); //区间加 
        else if(op == 2) assign(l,r,x); //推平 
        else if(op == 3) Prl(ranks(l,r,x)); //k小
        else if(op == 4) Prl(sum(l,r,x,y)); //区间x的次方和模y 
    }
    return 0;
}
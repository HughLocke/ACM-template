/* 动态线段树
如果线段树要操作的范围在1 - INF（一个空间存不下的大小）
如果离线可以考虑离散化，如果强制在线就要考虑一下动态线段树了
动态线段树不是一口气把全部结点都开完，而是动态的只开要开的结点
*/
//模板，hdu1199 n个操作为把a - b范围涂成黑色或者白色，查询为最长的连续白色区间，同样长输出最左边
const int maxn = 2010;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7; 

int N,M;
struct Tree{
    LL sum;    //最大连续 
    LL lsum;   //左连续 
    LL rsum;   //右连续 
    int lt,rt,lazy;
    void init(){
        lsum = rsum = sum = lt = rt = 0;
        lazy = -1;
    }
}tree[maxn * 60];
int tot;
void check(int &t){
    if(t) return;
    t = ++tot;
    tree[t].init();
}
void add(int &t,LL L,LL R,int v){
    if(v){
        tree[t].sum = tree[t].lsum = tree[t].rsum = R - L + 1;
    }else{
        tree[t].sum = tree[t].lsum = tree[t].rsum = 0;
    }
    tree[t].lazy = v;
}
void Pushdown(int& t,LL L,LL R){
    if(tree[t].lazy == -1) return;
    int &lt = tree[t].lt; int &rt = tree[t].rt;
    LL M = (L + R) >> 1;
    check(lt); check(rt);
    add(lt,L,M,tree[t].lazy);
    add(rt,M + 1,R,tree[t].lazy);
    tree[t].lazy = -1;
}
void Pushup(int t,LL L,LL R){
    int &ls = tree[t].lt; int &rs = tree[t].rt;
    LL M = (L + R) >> 1; 
    check(ls); check(rs);
    tree[t].sum = max(tree[ls].sum,tree[rs].sum);
    tree[t].sum = max(tree[t].sum,tree[ls].rsum + tree[rs].lsum);
    tree[t].lsum = tree[ls].lsum;
    if(tree[ls].lsum == M - L + 1){
        tree[t].lsum = tree[ls].lsum + tree[rs].lsum;
    } 
    tree[t].rsum = tree[rs].rsum;
    if(tree[rs].rsum == R - M){
        tree[t].rsum = tree[rs].rsum + tree[ls].rsum;
    }
}
//如果是单点修改的话，一个小优化是一路直接修改下去而不是从底部往上Pushup
void update(int &t,int q1,int q2,LL L,LL R,int v){ 
    check(t);       
    if(q1 <= L && R <= q2){
        add(t,L,R,v);
        return;
    }
    Pushdown(t,L,R);
    LL m = (L + R) >> 1;
    if(q1 <= m) update(tree[t].lt,q1,q2,L,m,v);
    if(q2 > m) update(tree[t].rt,q1,q2,m + 1,R,v);
    Pushup(t,L,R);
}
LL Left,Right;
//查询有时可用的一个优化是如果这个点不存在，不需要开辟空间继续查询，之间return 0即可
void query(int t,LL L,LL R){
    if(L == R){
        Left = L;
        Right = R;
        return;
    }
    check(tree[t].lt); check(tree[t].rt);
    int ls = tree[t].lt; int rs = tree[t].rt;
    LL M = (L + R) >> 1;
    if(tree[ls].sum == tree[t].sum) query(ls,L,M);
    else if(tree[rs].sum == tree[t].sum) query(rs,M + 1,R);
    else{
        Left = M - tree[ls].rsum + 1;
        Right = M + tree[rs].lsum;
        return;
    }
 
}
int main()
{
    while(~Sca(N)){
        LL L = 1; LL R = 2147483647;
        tot = 0;
        int root = 0;
        update(root,L,R,L,R,0);
        For(i,1,N){
            LL l,r;
            char op[3];
            scanf("%lld%lld%s",&l,&r,&op);
            if(op[0] == 'w'){
                update(root,l,r,L,R,1);
            }else{
                update(root,l,r,L,R,0);
            }
        }
        if(!tree[root].sum){
            puts("Oh, my god");
            continue;
        }
        query(root,L,R);
        printf("%lld %lld\n",Left,Right);
    }
    return 0;
}
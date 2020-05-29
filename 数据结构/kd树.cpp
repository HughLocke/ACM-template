/* K-DTree是用来解决K维空间中数点问题强有力的数据结构，可以在 (NlogN)-(N√N)的时间复杂度内完成查询和修改。
建树类似于二叉平衡树，只是排序的依据每个维度轮流，第一层取所有节点0维度的中位数点作为结点，比他小的放左边，比他大的放右边
第二层就按照1维度来排序....
每个节点除了表示一个当前节点外，还存储子树信息，查询的时候如果有子树显然不符合条件，就skip掉(类似于剪枝)
*/
//模板1HDU4347.给出N个K维度点，查询的时候给个点和M，询问N个点中前M靠近给定点的点
const int maxn = 50010;
const int maxk = 7;
int N,M,K;
int idx;
struct point{
    int x[maxk];
    bool operator < (const point &u) const{
        return x[idx] < u.x[idx];  //每层排序的维度都不一样,用全局变量idx标识 
    }
}p[maxn];
typedef pair<double,point>tp;
priority_queue<tp>nq;    //维护离查询点最近的点,fi表示距离,se表示点坐标 
int pow2(int x){return x * x;}
struct kdTree{
    point pt[maxn << 2]; //结点表示的点坐标 
    int son[maxn << 2];  //区间长度 
    void build(int t,int l,int r,int dep = 0){
        if(l > r) return;
        son[t] = r - l;   
        son[t << 1] = son[t << 1 | 1] = -1;
        idx = dep % K;
        int mid = l + r >> 1;
        nth_element(p + l,p + mid,p + r + 1);  //当前idx维度排名为中位数的点作为这个结点表示的点 
        pt[t] = p[mid];
        build(t << 1,l,mid - 1,dep + 1);
        build(t << 1 | 1,mid + 1,r,dep + 1);
    }
    void query(int t,point q,int m,int dep = 0){
        if(son[t] == -1) return;
        tp nd(0,pt[t]);
        for(int i = 0 ; i < K; i ++) nd.first += pow2(nd.se.x[i] - q.x[i]);
        int dim = dep % K,x = t << 1,y = t << 1 | 1,flag = 0;
        if(q.x[dim] >= pt[t].x[dim]) swap(x,y);   //如果待查寻的点这个维度比他大就查询右子树 
        if(~son[x]) query(x,q,m,dep + 1);
        if(nq.size() < m) nq.push(nd),flag = 1;
        else{
            if(nd.first < nq.top().fi) nq.pop(),nq.push(nd);
            if(pow2(q.x[dim] - pt[t].x[dim]) < nq.top().fi) flag = 1; //如果这个维度的距离已经比所有的都大了,就没有继续查的必要了 
        }
        if(~son[y] && flag) query(y,q,m,dep + 1);
    }
}kd;
void print(point &t){
    for(int j = 0 ; j < K ; j ++) printf("%d%c",t.x[j],j == K - 1?'\n':' ');
}
int main(){
    while(~Sca2(N,K)){
        for(int i = 0; i < N ; i ++){
            for(int j = 0 ; j < K; j ++) Sca(p[i].x[j]);
        }
        kd.build(1,0,N - 1);
        int t = read();
        while(t--){
            point ask;
            for(int j = 0 ; j < K ; j ++) Sca(ask.x[j]);
            Sca(M); kd.query(1,ask,M);
            printf("the closest %d points are:\n",M);
            point pt[20];
            for(int j = 0;!nq.empty(); j ++) pt[j] = nq.top().second,nq.pop();
            for(int j = M - 1; j >= 0 ; j --) print(pt[j]);
        }
    }
    return 0;
}
//当题目需要在线的时候,就不能用上面的方法构树了
/*insert函数动态加点,利用重构系数判断重构，节点中Max,Min表示该子树中该维度的最大(小)值
重构kdtree的参数选择，插入多查询少的情况，最优参数是接近 0.5 + x / (x + y) 的
x是插入个数，y是查询个数
插入少查询多的话，最优参数其实是更接近 0.7 + x / (x + y) 的， 查询再多也不建议参数低于0.7
当然最优参数的话，有时间可以自己去测试调整
*/
//模板，操作1在坐标(x,y)中加权值v,操作2查询子矩阵和
const int maxn = 1e5 + 10;
const int maxk = 2;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7; 
int N,M,K;
int p[maxk];
int q[maxk][2];
struct Tree{
    int d[maxk];
    int l,r,sum,val,size;
    int Min[maxk],Max[maxk];
}tree[maxn];
int cnt = 0;
const double alpha = 0.75;  //重构系数，当左(右)子树权重超过一定比例的时候将子树重构
int idx,num,tmp[maxn],A;
inline void erase(int &x){ //删除子树中的所有点,把这些点加入tmp
    if(!x) return;
    tmp[++num] = x;
    erase(tree[x].l); erase(tree[x].r);
    x = 0;
}
bool cmp(const int &a,const int &b){    //按照idx维度的大小排序
    return tree[a].d[idx] < tree[b].d[idx];
}
inline void update(int t){   //类似于Pushup
    int l = tree[t].l,r = tree[t].r;
    tree[t].size = tree[l].size + tree[r].size + 1;
    tree[t].sum = tree[t].val + tree[l].sum + tree[r].sum;
    for(int i = 0 ; i < K; i ++){
        if(l){
            tree[t].Max[i] = max(tree[t].Max[i],tree[l].Max[i]);
            tree[t].Min[i] = min(tree[t].Min[i],tree[l].Min[i]);
        }
        if(r){
            tree[t].Max[i] = max(tree[t].Max[i],tree[r].Max[i]);
            tree[t].Min[i] = min(tree[t].Min[i],tree[r].Min[i]);
        }
    }
}
inline void build(int &t,int l,int r,int k){  //构造
    if(l > r) return;
    int mid = l + r >> 1; idx = k;
    nth_element(tmp + l,tmp + 1 + mid,tmp + r + 1,cmp);
    t = tmp[mid];
    tree[t].sum = tree[t].val;
    for(int i = 0; i < K; i ++) tree[t].Max[i] = tree[t].Min[i] = tree[t].d[i];
    build(tree[t].l,l,mid - 1,(k + 1) % K);   //mid点就是t点,已经被加入了 
    build(tree[t].r,mid + 1,r,(k + 1) % K);
    update(t);
}
inline void rebuild(int &t,int k){    //重构子树
    tmp[num = 1] = ++cnt;
    tree[cnt].size = 1;
    for(int i = 0; i < K ; i ++) tree[cnt].d[i] = p[i];
    tree[cnt].val = tree[cnt].sum = A;
    erase(t);
    build(t,1,num,k);
}
void insert(int& t,int k){
    if(!t){
        tree[t = ++cnt].size = 1;
        tree[t].val = tree[t].sum = A;
        for(int i = 0 ; i < K ; i ++){
            tree[t].Max[i] = tree[t].Min[i] = tree[t].d[i] = p[i];
        }
        return;
    }    
    if(p[k] < tree[t].d[k]){
        if(tree[tree[t].l].size > tree[t].size * alpha) rebuild(t,k);
        else insert(tree[t].l,(k + 1) % K);
    }else{
        if(tree[tree[t].r].size > tree[t].size * alpha) rebuild(t,k);
        else insert(tree[t].r,(k + 1) % K);
    }
    update(t);
}
inline bool check_range(int t){  //检查这个区域是否被两个q完全包围 
    if(!t) return 0;
    for(int i = 0 ; i < K ; i ++){ 
        if(q[i][0] > tree[t].Min[i] || q[i][1] < tree[t].Max[i]) return 0;  
    }
    return 1;
}
inline bool check_point(int t){   //检查点是否在子矩阵内
    if(!t) return 0;
    for(int i = 0 ; i < K ; i ++){
        if(tree[t].d[i] < q[i][0] || tree[t].d[i] > q[i][1]) return 0;
    }
    return 1;
} 
inline bool check(int t){ //检查是否两个区间是否有相交部分 
    if(!t) return false;
    for(int i = 0 ; i < K ; i ++){
        if(q[i][1] < tree[t].Min[i] || q[i][0] > tree[t].Max[i]) return false;
    }
    return true;
}
int ans;
inline void query(int t){
    if(check_range(t)){
        ans += tree[t].sum;
        return;
    }
    if(check_point(t)) ans += tree[t].val;
    if(check(tree[t].l)) query(tree[t].l);
    if(check(tree[t].r)) query(tree[t].r);
}
int main(){
    N = read(); K = 2;   //默认为平面(2维)
    int root = 0;
    while(1){
        int op = read();
        if(op == 1){
            for(int i = 0 ; i < K ; i ++) p[i] = read() ^ ans;
            A = read() ^ ans;
            insert(root,0);
        }else if(op == 2){
            for(int i = 0; i <= 1; i ++){
                for(int j = 0 ; j < K ;j ++) q[j][i] = read() ^ ans;
            }
            ans = 0; query(root);
            Pri(ans);
        }else{
            break;
        }
    }
    return 0;
}

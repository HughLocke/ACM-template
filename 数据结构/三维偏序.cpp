//cdq分治：陌上花开
//定义node的等级为xyz全不大于他的node的种数，求每个等级的node有多少种
//注意需要先将xyz完全相同的node合并才行
const double eps = 1e-9;
const int maxn = 1e5 + 10;
const int maxm = 2e5 + 10;
int N,M,K;
struct Node{
    int x,y,z,ans,cnt;
    Node(){}
    Node(int x,int y,int z,int ans,int cnt):x(x),y(y),z(z),ans(ans),cnt(cnt){}
    bool operator == (Node a){
        return x == a.x && y == a.y && z == a.z;
    }
}node[maxn],tmp[maxn];
int ans[maxn],sum[maxn];
int tree[maxm];
void add(int x,int y){
    for(;x <= M; x += x & -x) tree[x] += y;
}
int getsum(int x){
    int ans = 0;
    for(;x > 0; x -= x & -x) ans += tree[x];
    return ans;
}
bool cmp(Node a,Node b){
    if(a.x != b.x) return a.x < b.x;
    if(a.y != b.y) return a.y < b.y;
    return a.z < b.z;
}
void cdq(int l,int r){
    if(l >= r) return;
    int m = l + r >> 1;
    cdq(l,m); cdq(m + 1,r);
    int cnt1 = l,cnt2 = m + 1;
    for(int i = l; i <= r; i ++){
        if((cnt2 > r) || ((node[cnt1].y <= node[cnt2].y) && cnt1 <= m)){
            add(node[cnt1].z,node[cnt1].cnt);
            tmp[i] = node[cnt1++];
        }else{
            node[cnt2].ans += getsum(node[cnt2].z);
            tmp[i] = node[cnt2++];
        }
    }
    for(int i = l; i <= m; i ++) add(node[i].z,-node[i].cnt);
    for(int i = l; i <= r; i ++) node[i] = tmp[i];
}
int main(){
    Sca2(N,M); int cnt = 1;
    for(int i = 1; i <= N ; i ++) node[i] = Node(read(),read(),read(),0,1); 
    sort(node + 1,node + 1 + N,cmp);
    for(int i = 2; i <= N ; i ++){
        if(node[i - 1] == node[i]) node[cnt].cnt++;
        else node[++cnt] = node[i];
    }
    cdq(1,cnt);
    for(int i = 1; i <= cnt ; i ++) sum[node[i].ans + node[i].cnt - 1] += node[i].cnt;
    for(int i = 0; i < N ; i ++) Pri(sum[i]);
    return 0;
}
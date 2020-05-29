//树状数组 注意0是无效下标
int tree[maxn];
void add(int x,int v){   //单点修改
    for(;x < N; x += x & -x) tree[x] += v;
}
LL sum(int x){           //查询前缀和
    LL ans = 0;
    for(;x > 0;x -= x & -x) ans += tree[x];
    return ans;
}
int kth(int k){           //查询从小到大数第K小,数组的下标表示数的大小，第二维表示数的个数
    int ans = 0;
    LL cnt = 0;
    for(int i = SP - 1; i >= 0 ; i --){
        ans += (1 << i);
        if(ans >= N || cnt + tree[ans] >= k){
            ans -= 1 << i;
        }else cnt += tree[ans];
    }
    return ans + 1;
}
//模板:POJ2985 初始N个为1的集合，操作1.合并两个集合，操作2.查询第K大的集合的大小
const int maxn = 2e5 + 10;
const int SP = 20;
int N,M,K;
int fa[maxn],tree[maxn],sz[maxn];
void init(){
    for(int i = 0 ; i <= N ; i ++) fa[i] = i,sz[i] = 1;
}
int find(int x){
    if(fa[x] == x) return x;
    return fa[x] = find(fa[x]);    
}
void add(int x,int v){
    for(;x < N; x += x & -x) tree[x] += v;
}
LL sum(int x){
    LL ans = 0;
    for(;x > 0;x -= x & -x) ans += tree[x];
    return ans;
}
int kth(int k){
    int ans = 0;
    LL cnt = 0;
    for(int i = SP - 1; i >= 0 ; i --){
        ans += (1 << i);
        if(ans >= N || cnt + tree[ans] >= k){
            ans -= 1 << i;
        }else cnt += tree[ans];
    }
    return ans + 1;
}
int main(){
    Sca2(N,M); init();
    add(1,N); int num = N;
    for(int i = 1; i <= M ; i ++){
        int op = read();
        if(op == 0){
            int u,v; Sca2(u,v);
            u = find(u),v = find(v);
            if(u == v) continue;
            add(sz[u],-1); add(sz[v],-1);
            fa[u] = v;
            sz[v] += sz[u];
            add(sz[v],1); num--;
        }else{
            int k; Sca(k);
            k = num - k + 1;
            Pri(kth(k));
        }
    } 
    return 0;
}
//二维树状数组
//模板hdoj2642:单点修改,区间查询
const int maxn = 1010;
int N,M,K;
LL tree[maxn][maxn];
bool MAP[maxn][maxn];
void add(int x,int y,int v){
    for(int tx = x;tx < maxn; tx += tx & -tx){
        for(int ty = y;ty < maxn; ty += ty & -ty) tree[tx][ty] += v;
    }
}
LL getsum(int x,int y){
    LL ans = 0;
    for(int tx = x;tx > 0; tx -= tx & -tx){
        for(int ty = y; ty > 0; ty -= ty & -ty) ans += tree[tx][ty];
    }
    return ans;
}
LL getsum(int x1,int y1,int x2,int y2){
    return getsum(x2,y2) + getsum(x1 - 1,y1 - 1) - getsum(x2,y1 - 1) - getsum(x1 - 1,y2); 
}
int main(){
    while(~Sca(M)){
        Mem(tree,0);
        while(M--){
            char op[2]; scanf("%s",op);
            if(op[0] == 'B'){
                int x = read(),y = read();
                x++;y++;
                if(!MAP[x][y]){
                    MAP[x][y] = 1;
                    add(x,y,1);
                }
            }else if(op[0] == 'D'){
                int x = read(),y = read();
                x++;y++;
                if(MAP[x][y]){
                    add(x,y,-1);
                    MAP[x][y] = 0;
                }
            }else{
                int x1 = read(),x2 = read(),y1 = read(),y2 = read();
                x1++;x2++;y1++;y2++;  //消除x = 0,y = 0的影响,0是无效点
                if(x1 > x2) swap(x1,x2);
                if(y1 > y2) swap(y1,y2);
                LL t = getsum(x1,y1,x2,y2);
                Prl(t);
            }
        }
    }
    return 0;
}

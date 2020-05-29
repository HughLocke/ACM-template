/* 曼哈顿距离和切比雪夫距离
曼哈顿距离:两点横纵坐标差之和 即dis = |x1 - x2| + |y1 - y2|;
切比雪夫距离：两点横纵坐标差的最大值 即dis = max(|x1 - x2|,|y1 -y2|);
两距离可以相互转化
将一个点(x,y)的坐标变为(x+y,x−y)后,原坐标系中的曼哈顿距离 = 新坐标系中的切比雪夫距离
将一个点(x,y)的坐标变为((x+y)/2,(x−y)/2) 后,原坐标系中的切比雪夫距离 = 新坐标系中的曼哈顿距离
用处：
1.切比雪夫距离转曼哈顿距离
切比雪夫距离在计算的时候需要取max，往往不是很好优化，对于一个点，计算其他点到该的距离的复杂度为O(n)
而曼哈顿距离只有求和以及取绝对值两种运算，我们把坐标排序后可以去掉绝对值的影响，进而用前缀和优化，可以把复杂度降为O(1)
2.曼哈顿距离转切比雪夫距离
例如维护区间两点之间最大的曼哈顿距离，可以转为切比雪夫距离，分别维护区间x,y的最大(小)值，求他们之间的差再取x,y中较大的值就是原坐标中的最大的曼哈顿距离
 */
//模板：给一堆点，求一个点使得他到其他所有点的切比雪夫距离最小
//做法:转曼哈顿距离之后排序维护前缀后缀x,y的和
const int maxn = 1e5 + 10;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7; 
int N,M,K;
struct Node{
    LL x,y;
    int id;
}node[maxn];
bool cmp(Node a,Node b){return a.x < b.x;}
bool cmp2(Node a,Node b){return a.y < b.y;}
LL ans[maxn];
int main(){
    Sca(N);
    for(int i = 1; i <= N ; i ++){
        int x,y; Sca2(x,y);
        node[i].x = x + y; node[i].y = x - y;
        node[i].id = i;
    }
    sort(node + 1,node + 1 + N,cmp);
    LL pre = 0;
    for(int i = 1; i <= N ; i ++){
        ans[node[i].id] += (i - 1) * node[i].x - pre;
        pre += node[i].x;
    }
    pre = 0;
    for(int i = N ; i >= 1; i --){
        ans[node[i].id] += pre - (N - i) * node[i].x;
        pre += node[i].x;
    }
    sort(node + 1,node + 1 + N,cmp2);
    pre = 0;
    for(int i = 1; i <= N ; i ++){
        ans[node[i].id] += (i - 1) * node[i].y - pre;
        pre += node[i].y;
    }
    pre = 0;
    for(int i = N ; i >= 1; i --){
        ans[node[i].id] += pre - (N - i) * node[i].y;
        pre += node[i].y;
    }
    LL Min = 1e18;
    for(int i = 1; i <= N ; i ++) Min = min(Min,ans[i]);
    Min /= 2;
    Prl(Min);
    return 0;
}
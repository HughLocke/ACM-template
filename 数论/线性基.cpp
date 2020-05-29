/*    线性基：处理许多数之间的异或问题
对于一个数集V，它的线性基β是它的一个子集，满足β中所有数互相异或得到的集合等价于V中所有数互相异或得到的集合。也就是说，β可以看成是V的压缩。
线性基有一些性质：
1.线性基的异或集合中不存在0。也就是说，β是V中线性无关的极大子集。（这些概念以后再补吧。。）
2.线性基中每个元素的异或方案唯一，也就是说，线性基中不同的异或组合异或出的数都是不一样的。这个与性质1其实是等价的。
3.线性基的二进制最高位互不相同。
4.如果线性基是满的，它的异或集合为[1,2n−1]。
5.线性基中元素互相异或，异或集合不变。
*/
const int maxn = 110;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7; 
int N,M,K;
LL a[maxn],p[100],d[100];
//建立线性基（插入操作） 
inline void add(LL x){
    for(int i = 62; i >= 0; i --){
        if(!(x & (1LL << i))) continue; //注意1LL 
        if(!p[i]){p[i] = x;break;}      //注意break 
        x ^= p[i];                      //注意是x变动 
    }
}
//查询异或最小值：线性基中 位数最低的数字
//查询异或最大值 
inline LL getmax(){
    LL ans = 0;
    for(LL i = 62; i >= 0; i --){
        if(ans < (ans ^ p[i])) ans ^= p[i];
    }
    return ans;
}
//check是否存在子集合可以异或为这个数 
bool check(LL x){  // true存在,false不存在 
    for(int i = 62; i >= 0 ; i --){
        if(!(x & (1LL << i))) continue;
        if(!p[i]) return false;
        x ^= p[i];
    }
    return x == 0;
}
//查询集合所有可异或数中K小的数
//先将线性基rebuild，然后可以O(logn)的查找
void rebuild(){
    for(LL i = 62; i >= 0 ; i --){
        for(LL j = i - 1; j >= 0; j --){
            if(p[i] & (1LL << j)) p[i] ^= p[j];
        }
    }
    for(int i = 0 ; i <= 62; i ++) if(p[i]) d[cnt++] = p[i];
    return ;
}
LL query(LL k){
    if(!k) return 0;
    if(k >= (1LL << cnt)) return -1;
    LL ans = 0;
    for(int i = 62; i >= 0; i --){
        if(k & (1LL << i)) ans ^= d[i];
    }
    return ans;
}
//main函数：查找线性基异或数的K小
int main(){
    int T = read();
    int CASE = 1;
    while(T--){
        for(int i = 0 ; i <= 62; i ++) p[i] = 0;
        Sca(N); 
        for(int i = 1; i <= N ; i ++){
            Scl(a[i]); add(a[i]);
        } 
        cnt = 0; rebuild();
        Sca(Q);
        int flag = (cnt != N);
        for(int i = 1; i <= Q; i ++){
            LL k; scanf("%lld",&k);
            Prl(query(k - flag));
        }
    }
    return 0;
}

//例题：hdu6579
/*给出一个序列.
操作1在序列尾增加一个数 操作2.求区间异或最大值 
做法:维护每个前缀的线性基(上三角形态)
对于每个线性基，讲出现为止靠右的数字尽可能放在高位，也就是说在插入新的数字的时候，要同时记录对应位置上数字出现位置，
并且再找到可以插入的位置的时候，如果新数字比原来位置上的数字更靠右，就将该位置上原来的数字向地位推。
在求最大值的时候，从高位向低位遍历，如果该位上数字出现在询问中左端点的右侧且可以使答案变大，就异或进答案。
对于线性基的每一位，与它异或过的线性基更高位置上的数字肯定都出现在它优策
 */
const int maxn = 1e6 + 10;
int N,M,K;
struct xj{
    int a[32],pos[32];
    inline void init(){
        for(int i = 0; i <= 30; i ++) a[i] = pos[i] = 0;
    }
    inline void add(int x,int p){
        for(int i = 30; i >= 0 ; i --){
            if(!(x & (1 << i))) continue;
            if(!a[i]){
                a[i] = x; pos[i] = p;
                break;
            }else{
                if(p > pos[i])swap(a[i],x),swap(p,pos[i]);
                x ^= a[i];
            }
        }
    }
    inline int getmax(int l){
        int ans = 0;
        for(int i = 30; i >= 0; i --){
            if(pos[i] < l) continue;
            if(ans < (ans ^ a[i])) ans ^= a[i];
        }
        return ans;
    }
}pre[maxn];
int main(){
    int T; Sca(T);
    while(T--){
        Sca2(N,M);
        for(int i = 1; i <= N ; i ++){
            int x = read();
            pre[i] = pre[i - 1];
            pre[i].add(x,i);
        }
        int ans = 0;
        while(M--){
            int op = read();
            if(!op){
                int l = read() ^ ans,r = read() ^ ans;
                l = l % N + 1; r = r % N + 1;
                if(l > r) swap(l,r);
                ans = pre[r].getmax(l);
                Pri(ans);
            }else{
                int x = read() ^ ans;
                N++;
                pre[N] = pre[N - 1];
                pre[N].add(x,N);
            }
        }
    } 
    return 0;
}

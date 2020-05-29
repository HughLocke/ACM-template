/* SAM 后缀自动机
时空复杂度O(n)
1.每个状态对应一个endpos的等价类，表示以该点结尾的子串的集合。
2.t0到任意节点之间的转移连接起来就是字符串的子串，任意子串对应一条t0出发的路径
3.通常一个结点表示的字符串是这个等价类集合中长度最长的字符串，集合中的所有其他字符串都是他的后缀
性质1.考虑一个endpos等价类，将类中的所有子串按长度非递增的顺序排序。每个子串都不会比它前一个子串长,与此同时每个子串也是它前一个子串的后缀。换句话说，对于同一等价类的任一两子串，较短者为较长者的后缀，且该等价类中的子串长度恰好覆盖整个区间[x,y] 。

后缀链接(parent树)
1.结点指向结点表示的最短字符串的去掉第一个字符的字符串
例如结点最短字符串表示abcabc，则指向结点的最长字符串bcabc
2.叶子节点都是主链上的节点，主链上的点不一定是叶子结点
3.在主链上的点，最长的子串都是原串的前缀
4.一个节点上的子串出现次数是一样的
5.对应同一状态v的所有子串在文本串T中的出现次数相同
6.parents上父亲上的子串出现次数，是儿子上的子串出现次数之和，如果父亲在主链上，就再加一
7.点i上面表示子串的数量为len[fa[i]]−len[i]。
8.两节点的最长公共后缀是他们在parent树上的LCA点表示的最长字符串
可以证明后缀自动机上至多有2 * n - 1个结点和3 * n - 4条边
*/
//tag:以下模板不自带初始化，son,fa,len,num等数组均未初始化，多样例请特别注意
/*模板1：求字符串中出现次数不为1的子串中出现次数 * 长度最大的值
num[i]为当前状态点出现次数，len[i]为当前状态点最大字符串长度
根据parent树的性质6，主链上的结点肯定只出现一次，所以dfs之后统计一下儿子的和就可以知道每个结点出现的次数
采用桶排序模拟dfs的过程可以不必实质建出parent树*/
//tag:如果需要动态维护num，每次新加点之后对parent树的每个祖先都+1,同时创建nq的时候需要复制q的num值，下面有给出
int len[maxn << 1],fa[maxn << 1],son[maxn << 1][maxc];
LL num[maxn << 1];
int size,last;
void Init(){
    size = last = 1;
}
void insert(char c){
    int s = c - 'a';
    int p = last,np = ++size;last = np; num[np] = 1; 
    //cout << np << endl;
    len[np] = len[p] + 1;
    for(;p && !son[p][s]; p = fa[p]) son[p][s] = np;
    if(!p) fa[np] = 1;
    else{
        int q = son[p][s];
        if(len[p] + 1 == len[q]) fa[np] = q;
        else{
            int nq = ++size; len[nq] = len[p] + 1;
            memcpy(son[nq],son[q],sizeof(son[q]));
            fa[nq] = fa[q]; fa[q] = fa[np] = nq; 
            //num[nq] = num[q] if 需要动态维护num
            for(;son[p][s] == q && p;p = fa[p]) son[p][s] = nq;
        }
    }
}
void insert(char *s){
    Init();
    for(int i = 0; s[i] ; i ++) insert(s[i]);
}
char str[maxn];
int A[maxn << 1],tmp[maxn << 1];
void Qsort(){
    //排出一个按照len从小到大的结点序列
    //本质上是模拟dfs的加,len小的一定在len大的之前遍历 
    for(int i = 1; i <= size; i ++) tmp[len[i]]++;
    for(int i = 1; i <= size; i ++) tmp[i] += tmp[i - 1];
    for(int i = 1; i <= size; i ++) A[tmp[len[i]]--] = i;
}
int main(){
    scanf("%s",str);
    insert(str);
    Qsort();
    for(int i = size; i >= 1; i --) num[fa[A[i]]] += num[A[i]];
    LL ans = 0;
    for(int i = 2; i <= size; i ++) if(num[i] != 1)ans = max(ans,len[i] * num[i]);
    Prl(ans);
    return 0;
}

/*应用，输出长度为1-n的子串出现最多次数的子串的次数
做法:利用模板1求出每个节点的出现次数，然后每个节点i将len[min]-len[max]的答案更新num[i]
模板:在模板1的基础上添加如下代码*/
for(int i = 2; i <= size; i ++) Max[len[i]] = max(Max[len[i]],num[i]);
for(int i = N; i >= 1 ; i --) Max[i] = max(Max[i],Max[i + 1]);
for(int i = 1; i <= N ; i ++) Prl(Max[i]);

/*应用：求s,t两串的最长公共子串(On)
做法：对S建SAM然后t开始跑,跑到失配点i就跳转到fa[i]*/
scanf("%s%s",s,t);
insert(s);
int ans = 0,tmp = 0;
int p = 1;
for(int i = 0;t[i]; i ++){
    int v = t[i] - 'a';
    while(p != 1 && !son[p][v]) p = fa[p],tmp = len[p];
    if(son[p][v]){
        p = son[p][v]; tmp++; 
    }
    ans = max(ans,tmp);
}    
Pri(ans);
/*应用：多个字符串的最长公共子串
做法：选取一个字符串建SAM，其它字符串如上跑一遍
每个状态对应每个字符串的答案为s1,s2,s3..sn,则每个状态的最终答案为min(s1,s2..sn),取最大即可
模板：dp[i]表示当前结尾的字符匹配上之后的最长匹配长度，显然一个结点匹配上之后他的父亲也匹配上
所以将parent树从叶子到跟再更行一遍*/
int dp[maxn << 1],Max[maxn << 1];
int A[maxn << 1],tmp[maxn << 1];
void ins(char* str){
    for(int i = 0 ; i <= size; i ++) dp[i] = 0;
    int l = 0,p = 1;
    for(int i = 0;str[i]; i ++){
        int v = str[i] - 'a';
        while(p != 1 && !son[p][v]) p = fa[p],l = len[p];
        if(son[p][v]){
            p = son[p][v]; l++;
            dp[p] = max(dp[p],l);    
        }
    }
    for(int i = size; i >= 2; i --){
        dp[fa[A[i]]] = max(dp[fa[A[i]]],min(len[fa[A[i]]],dp[A[i]]));
    }
    for(int i = 1; i <= size; i ++) Max[i] = min(Max[i],dp[i]);
}
int main(){
    scanf("%s",s); int cnt = 1;
    while(~scanf("%s",t[cnt])) cnt++;
    cnt--;
    insert(s); 
    for(int i = 1; i <= size; i ++) tmp[len[i]]++;
    for(int i = 1; i <= size; i ++) tmp[i] += tmp[i - 1];
    for(int i = 1; i <= size; i ++) A[tmp[len[i]]--] = i;
    for(int i = 1; i <= size; i ++) Max[i] = len[i];
    for(int i = 1; i <= cnt ; i ++) ins(t[i]);
    int ans = 0;
    for(int i = 2; i <= size; i ++) ans = max(ans,Max[i]);
    Pri(ans);
}
/*最小表示法，长度为N的循环字符串中找到字典序最小的字符串
模板:将原串倍增一遍之后SAM直接寻找长度为N的字典序最小的路径
数值大小不定，采用map建图，用时间换空间
*/
const int maxn = 6e5 + 10;
int N,M,K;
int len[maxn << 1],fa[maxn << 1];
map<int,int>son[maxn << 1];
int size,last;
void Init(){
    size = last = 1;
}
inline void insert(int c){
    int p = last,np = ++size; last = np;
    len[np] = len[p] + 1;
    for(;p && !son[p].count(c); p = fa[p]) son[p][c] = np;
    if(!p) fa[np] = 1;
    else{
        int q = son[p][c];
        if(len[p] + 1 == len[q]) fa[np] = q;
        else{
            int nq = ++size; len[nq] = len[p] + 1;
            son[nq] = son[q];
            fa[nq] = fa[q]; fa[q] = fa[np] = nq;
            for(;son[p][c] == q && p; p = fa[p]) son[p][c] = nq;
        }
    }
}
int a[maxn];
int main(){
    Sca(N); Init();
    for(int i = 1; i <= N ; i ++) insert(a[i] = read());
    for(int i = 1; i <= N ; i ++) insert(a[i]);
    int t = 1;
    for(int i = 1; i <= N ; i ++){
        printf("%d ",son[t].begin()->first);
        t = son[t].begin()->second;
    }
    return 0;
}
/*应用:检查字符串是否出现在文本中
做法：对文本建后缀自动机，能跑完模式串且不出现NULL结点就是出现在文本中了*/

/*应用:不同子串个数
做法：相当于图上从原点起有多少不同的路径，因为这是一个DAG图，所以直接DP一下就可以了
dp[i]表示从i点出发的路径数量
初始dp[i] = 1,然后从终点向起点累加，即dp[i] = 1 + Σdp[j](j为i的儿子)
最终不同子串的个数就是dp[1] - 1,因为需要减掉一个空串*/

/*模板：求第k小子串，选项0为不同位置的相同子串算一个，1为不同位置的相同子串算不同
做法：选项0:如同上述求不同字串个数的做法求出每个节点出发的路径数量，然后就如权值线段树找k大一般找第k大的路径
选项1:利用模板1求出不同结点表示的串的个数num[i],dp[i]的初始化从1变为num[i],即从i到i的路径变为了num[i]条,然后同上
*/
const int maxn = 5e5 + 10;
char str[maxn];
int tmp[maxn << 1],A[maxn << 1];
int sum[maxn << 1];
void dfs(int t,int k){  //找出t出发的第k大路径
    if(k <= num[t]) return;
    k -= num[t];   //减去当前节点表示的路径数
    for(int i = 0 ; i < 26; i ++){
        if(!son[t][i]) continue;
        int v = son[t][i];
        if(sum[v] >= k){
            printf("%c",i + 'a');
            dfs(v,k);
            return;
        }
        k -= sum[v];
    }
}
int main(){
    scanf("%s",str); 
    insert(str); 
    for(int i = 1; i <= size; i ++) tmp[len[i]]++;
    for(int i = 1; i <= size; i ++) tmp[i] += tmp[i - 1];
    for(int i = 1; i <= size; i ++) A[tmp[len[i]]--] = i;
    for(int i = size; i >= 1; i --) num[fa[A[i]]] += num[A[i]];
    int op = read(),k = read();
    for(int i = 1; i <= size; i ++) sum[i] = op?num[i]:num[i] = 1;
    sum[1] = num[1] = 0;
    for(int i = size; i >= 1; i --){
        for(int j = 0 ; j < 26; j ++){
            if(son[A[i]][j]) sum[A[i]] += sum[son[A[i]][j]];
        }
    }
    if(sum[1] < k) puts("-1");
    else dfs(1,k);
    return 0;
}
/*求区间不同字串个数
做法:一个很关键的性质：SAM每次插入字符后增加的不同字串的个数为len[last] - len[fa[last]]
所以对于每个左端点跑一边SAM，然后插入的时候记录答案，即可获得dp[i][j]表示区间不同字符串的个数*/
int dp[maxn][maxn];
int main(){
    int T = read();
    while(T--){
        scanf("%s",str + 1);
        for(int i = 1; str[i]; i ++){    
            for(int i = 0; i <= size; i ++){
                fa[i] = len[i] = 0;
                for(int j = 0 ; j < 26; j ++) son[i][j] = 0;
            }
            Init();
            for(int j = i ; str[j] ; j ++){
                insert(str[j]);
                dp[i][j] = dp[i][j - 1] + len[last] - len[fa[last]];
            }
        }
        Sca(M);
        while(M--){
            int l = read(),r = read();
            Pri(dp[l][r]);
        }
    }
    return 0;
}
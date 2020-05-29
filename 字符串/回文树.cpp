/*回文树
一个节点表示一个回文串，每个节点之间表示的是本质不同的回文串
len[i]表示i结点表示的回文串的长度
cnt[i]表示i结点表示的回文串的个数,建树的时候cnt是不完全的，需要调用count()之后才是完全的
fail[i]表示结点i失配后跳转的结点，表示结点i表示的回文串的最长后缀回文串
next[i][c]表示结点i表示的字符串在两边添加字符c变成的回文串的编号
num[i]表示i表示的回文串的最右端点为回文串结尾的回文串个数
last指向新添加一个字母后形成的最长回文串标识的结点
S[i]表示第i次添加的字符(一开始设S[0] = -1,也可以是之后不会出现的任意字符)
 */
const int maxn = 2e5 + 10;
const int maxc = 26;
int N,M,K;
struct Pal_T{
    int next[maxn][maxc];
    int fail[maxn],cnt[maxn],num[maxn],len[maxn],S[maxn];
    int last,n,tot;
    int newnode(int l){
        for(int i = 0 ; i < maxc; i ++) next[tot][i] = 0;
        cnt[tot] = num[tot] = 0;
        len[tot] = l;
        return tot++;
    }
    void init(){
        tot = 0; 
        newnode(0); //偶数根节点
        newnode(-1); //奇数根节点
        last = n = 0;
        S[n] = -1; fail[0] = 1;
    }
    int getfail(int x){
        while(S[n - len[x] - 1] != S[n]) x = fail[x];
        return x;
    }
    void add(int c){
        c -= 'a';
        S[++n] = c;
        int cur = getfail(last);
        if(!next[cur][c]){
            int now = newnode(len[cur] + 2);
            fail[now] = next[getfail(fail[cur])][c];
            next[cur][c] = now;
            num[now] = num[fail[now]] + 1;
        }
        last = next[cur][c];
        cnt[last]++;
    }
    void count(){
        for(int i = tot - 1; i >= 0; i --) cnt[fail[i]] += cnt[i];
    }
}PT,PT2;
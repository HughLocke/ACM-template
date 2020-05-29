//序列自动机
//nxt[i][j]表示i后面第一个j出现的位置(不包括i)
//模板：给一个长串，查询N个字符串是否为长串的子序列
//做法：直接跳next即可
const int maxn = 1e5 + 10;
char str[maxn],s[maxn];
int nxt[maxn][26]; //表示i后面第一个j出现的位置(不包括i)
int main(){
    scanf("%s",str + 1);
    int l = strlen(str + 1);
    for(int i = 0 ; i < 26; i ++) nxt[l][i] = -1; //后面不存在则为-1
    for(int i = l ; i >= 1; i --){   //构造序列自动机
        for(int j = 0; j < 26; j ++) nxt[i - 1][j] = nxt[i][j];
        nxt[i - 1][str[i] - 'a'] = i;
    }
    scanf("%d",&N);
    while(N--){
        scanf("%s",s);
        int now = 0;
        for(int i = 0 ;s[i] && ~now; i ++) now = nxt[now][s[i] - 'a'];
        if(~now) puts("YES");
        else puts("NO");
    }
    return 0;
}
//求子序列个数 f[i]表示以i起始的子序列个数
int dfs(int x) //main函数调用：dfs(0);
{
    if(f[x]) return f[x];
    for(int i=1;i<=a;i++)
        if(nxt[x][i]) f[x]+=dfs(nxt[x][i]);
    return ++f[x];
}
//求两串的公共子序列个数，两串都构造一下然后跑
LL dfs(LL x,LL y){
    if(f[x][y]) return f[x][y];
    for(LL i=1;i<=a;++i)
        if(nxt1[x][i]&&nxt2[y][i])
            f[x][y]+=Dfs(nxt1[x][i],nxt2[y][i]);
    return ++f[x][y];
}
//求字符串回文子序列的个数：正反都构造一遍然后跑
LL dfs(LL x,LL y){
    if(f[x][y]) return f[x][y];
    for(LL i=1;i<=a;++i)
        if(nxt1[x][i]&&nxt2[y][i]){
            if(nxt1[x][i]+nxt2[y][i]>n+1) continue;
            if(nxt1[x][i]+nxt2[y][i]<n+1) f[x][y]++;
            f[x][y]=(f[x][y]+Dfs(nxt1[x][i],nxt2[y][i]))%mod;
        }
    return ++f[x][y];
}
//求一个A,B的最长公共子序列S，使得C是S的子序列
//dfs(int x,int y,int z)，表示一匹配到C的z位
//需要改变C的构造方法
for(LL i=1;i<=a;++i) nxt[n][i]=n;
for(LL i=0;i<n;++i){
    for(LL j=1;j<=a;++j) nxt[i][j]=i;
    nxt[i][c[i+1]]=i+1;
}
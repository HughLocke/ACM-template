/* 拓展KMP算法
nxt[]:x串的每一个后缀与整个串的最长公共前缀，即x[i .. m - 1]与x[0...m - 1]的最长公共前缀
extend[]:y的每一个后缀与x的整个串的最长公共前缀，即y[i ... n - 1]与x[0 .. m - 1]的最长公共前缀
模板：求str2的后缀和str1的前缀的最长公共前缀
*/
const int maxn = 1e6 + 10;
int nxt[maxn],extend[maxn];
char str1[maxn],str2[maxn];
void pre_EKMP(char x[],int m,int next[]){
    next[0] = m;
    int j = 0;
    while(j + 1 < m && x[j] == x[j + 1]) j ++;
    next[1] = j;
    int k = 1;
    for(int i = 2; i < m ; i ++){
        int p = next[k] + k - 1;
        int L = next[i - k];
        if(i + L < p + 1) next[i] = L;
        else{
            j = max(0,p - i + 1);
            while(i + j < m && x[i + j] == x[j]) j ++;
            next[i] = j;
            k = i;
        }
    }
}
void EKMP(char x[],int m,char y[],int n,int next[],int extend[]){
    pre_EKMP(x,m,next);
    int j = 0;
    while(j < n && j < m && x[j] == y[j]) j++;
    extend[0] = j;
    int k = 0 ;
    for(int i = 1; i < n ; i++){
        int p = extend[k] + k - 1;
        int L = next[i - k];
        if(i + L < p + 1) extend[i] = L;
        else{
            j = max(0,p - i + 1);
            while(i + j < n && j < m && y[i + j] == x[j]) j ++;
            extend[i] = j;
            k = i;
        }
    }
}
int main(){
    while(~scanf("%s%s",str1,str2)){
        int l1 = strlen(str1),l2 = strlen(str2);
        EKMP(str1,l1,str2,l2,nxt,extend);
        int ans = 0;
        for(int i = 0 ; i < l2 ; i ++) if(extend[i] == l2 - i){
             ans = l2 - i;
             break;
        }
        if(ans) for(int i = 0; i < ans; i ++) putchar(str1[i]);
        if(ans) putchar(' ');
        Pri(ans);
    }
    return 0;
}
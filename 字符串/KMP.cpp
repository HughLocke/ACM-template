//KMP算法模板：输出s2在s1内出现的所有位置的起始点，再输出next数组
//next[i]表示前i个字符前后最长匹配
char s1[maxn],s2[maxn];
int Next[maxn];
void kmp_pre(char x[],int m,int nxt[]){     //计算next数组
    int j = 0;
    nxt[1] = 0;
    for(int i = 2; i <= m; i ++){
        while(j && x[i] != x[j + 1]) j = nxt[j];
        if(x[j + 1] == x[i]) j ++;
        nxt[i] = j;
    }
}
void KMP(char x[],int m,char y[],int n){     //1 - n开始计算
    kmp_pre(x,m,Next);
    int j = 0;
    for(int i = 1 ; i <= n; i ++){
        while(j > 0 && x[j + 1] != y[i]) j = Next[j];
        if(x[j + 1] == y[i]) j ++;
        if(j == m){
            Pri(i - m + 1);                 //如果是计数可以开个计数器然后++
            j = Next[j];
        }
    }
}
int main(){
    scanf("%s%s",s1 + 1,s2 + 1);
    int l1 = strlen(s1 + 1),l2 = strlen(s2 + 1);
    KMP(s2,l2,s1,l1);
    for(int i = 0 ; i < l2; i ++) printf("%d ",Next[i + 1]);
    return 0;
}
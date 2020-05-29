/*  后缀数组
(1)将字符串的所有后缀按照字典序从小到大排序
sa[i]表示排名第i的后缀的下标 , rak[i]表示下标为i的后缀的排名
(2)Height数组
lcp(x,y)：字符串x与字符串y的最长公共前缀，在这里指x号后缀与与y号后缀的最长公共前缀
height[i]：lcp(sa[i],sa[i−1])，即排名为i的后缀与排名为i−1的后缀的最长公共前缀
H[i]：height[rak[i]]，即i号后缀与它前一名的后缀的最长公共前缀
应用：
1.两个后缀的最大公共前缀：lcp(x,y)=min(heigh[x−y])， 用rmq维护，O(1)查询
2.可重叠最长重复子串：Height数组里的最大值
3.不可重叠最长重复子串 POJ1743：首先二分答案x，对height数组进行分组，保证每一组的minheight都>=x
依次枚举每一组，记录下最大和最小长度，多sa[mx]−sa[mi]>=x那么可以更新答案
4.本质不同的子串的数量:枚举每一个后缀，第i个后缀对答案的贡献为len−sa[i]+1−height[i]
*/
const int maxn = 1e6 + 10;
int N,M,K;
char str[maxn];
int sa[maxn],rak[maxn],tex[maxn],tp[maxn],Height[maxn];
void GetHeight() {
    int j, k = 0;
    for(int i = 1; i <= N; i++){
        if(k) k--;
        int j = sa[rak[i] - 1];
        while(str[i + k] == str[j + k]) k++;
        Height[rak[i]] = k;
    }
}
void Qsort(){
    for(int i = 0; i <= M ; i ++) tex[i] = 0;
    for(int i = 1; i <= N ; i ++) tex[rak[i]]++;
    for(int i = 1; i <= M ; i ++) tex[i] += tex[i - 1];
    for(int i = N; i >= 1 ; i --) sa[tex[rak[tp[i]]]--] = tp[i];
}
void SA(){
    for(int i = 1; i <= N ; i ++) rak[i] = str[i] - '0' + 1,tp[i] = i;
    Qsort();
    for(int w = 1,p = 0; p < N; w <<= 1,M = p){
        p = 0;
        for(int i = 1; i <= w; i ++) tp[++p] = N - w + i;
        for(int i = 1; i <= N ; i ++) if(sa[i] > w) tp[++p] = sa[i] - w;
        Qsort();
        swap(tp,rak);
        rak[sa[1]] = p = 1;
        for(int i = 2; i <= N ; i ++){
            rak[sa[i]] = (tp[sa[i - 1]] == tp[sa[i]] && tp[sa[i - 1] + w] == tp[sa[i] + w])?p:++p;
        }
    }
}
int main(){
    scanf("%s",str + 1);
    N = strlen(str + 1);
    M = 122;
    SA();
    for(int i = 1; i <= N ; i ++){
        printf("%d ",sa[i]);
    }
    return 0;
}
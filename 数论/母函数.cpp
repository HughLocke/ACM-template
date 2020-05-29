//母函数
/*
求用1分、2分、3分的邮票贴出不同数值的方案数：（每张邮票的数量是无限的）
那么
1分：(1+x^1+x^2+x^3+x^4+......)
2分：(1+x^2+x^4+x^6+x^8+......)
3分：(1+x^3+x^6+x^9+x^12+......)
然后这3个乘起来（让电脑去乘吧）
对于这种无限的，题目肯定会给你他询问的数值的范围，计算到最大的范围就可以了
 */
 #include<cstdio>
typedef long long LL;
const int maxn = 100 + 5;//假如题目只问到100为止 
const int MAX = 3;//题目只有1,2,3这3种邮票 
LL c1[maxn], c2[maxn];//c2是临时合并的多项式，c1是最终合并的多项式 
int n;
void init(){
    c1[0] = 1;//一开始0的情况算一种 
    for(int i = 1; i <= MAX; i ++){//把1分到MAXN的邮票合并，变成一个多项式 
        for(int j = 0; j < maxn; j += i){//i分的邮票，步长是i
            for(int k = 0; j + k < maxn; k ++){//从x^0到x^N遍历一遍 
                c2[j + k] += c1[k];//因为j的所有项系数为1，所以c1[k]可以看成c1[k]*1; 
            }
        } 
        for(int j = 0; j < maxn; j ++){//把c2的数据抄到c1，清空c2 
            c1[j] = c2[j];
            c2[j] = 0;
        }
    }
} 
int main(){
    init();
    while(scanf("%d", &n) != EOF){
        printf("%I64d\n", c1[n]);
    }
}
//样例2，问一个数字n能够拆成多少种数字的和
/* 比如n = 4
比如n=4
4 = 4;4 = 3 + 1;
4 = 2 + 2;4 = 2 + 1 + 1;
4 = 1 + 1 + 1 + 1;
有5种，那么答案就是5*/
//相当于把所有数当成邮票看能组成多少
const int maxn = 130;
const int MAX = 120;
int N,M,K;
LL c1[maxn],c2[maxn];
void init(){
    c1[0] = 1;
    for(int i = 1; i <= MAX; i ++){
        for(int j = 0 ; j < maxn; j += i){
            for(int k = 0 ; j + k < maxn; k ++){
                c2[j + k] += c1[k];
            }
        }
        for(int j = 0 ; j < maxn; j ++){
            c1[j] = c2[j];
            c2[j] = 0;
        }
    }
}
int main(){
    init();
    while(~Sca(N)) Prl(c1[N]);
    return 0;
}
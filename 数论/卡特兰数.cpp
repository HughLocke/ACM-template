/*卡特兰数
1.前30项
[1,1,2,5,14,42,132,429,1430,4862,16796,58786,
 208012,742900,2674440,9694845,35357670,129644790,
 477638700,1767263190,6564120420,24466267020,
 91482563640,343059613650,1289904147324,
 4861946401452,18367353072152,69533550916004,
 263747951750360,1002242216651368,3814986502092304]
2.在比赛的时候很可能不能证明一个数列是卡特兰数，一般手算几项发现对上了卡特兰数就冲了
*/
//卡特兰数取模模板
LL Catalan[maxn],inv[maxn];
inline void Catalan_init(int n,LL mod){
    inv[1] = 1;
    for(int i = 2; i <= n + 1; i ++){
        inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    }
    Catalan[0] = Catalan[1] = 1;
    for(int i = 2; i <= n ; i ++){
        Catalan[i] = Catalan[i - 1] * (4 * i - 2) % mod * inv[i + 1] % mod;
    }
}
int main(){
    Catalan_init(10000,mod);
    while(~Sca(N)) Prl(Catalan[N]);
    return 0;
}


//卡特兰数大数模板
#include<bits/stdc++.h>
using namespace std;
const int C_maxn = 100 + 10;///项数

int Catalan_Num[C_maxn][1000];///保存卡特兰大数、第二维为具体每个数位的值
int NumLen[C_maxn];///每个大数的数长度、输出的时候需倒序输出

void catalan() //求卡特兰数
{
    int i, j, len, carry, temp;
    Catalan_Num[1][0] = NumLen[1] = 1;
    len = 1;
    for(i = 2; i < 100; i++)
    {
        for(j = 0; j < len; j++) //乘法
        Catalan_Num[i][j] = Catalan_Num[i-1][j]*(4*(i-1)+2);
        carry = 0;
        for(j = 0; j < len; j++) //处理相乘结果
        {
            temp = Catalan_Num[i][j] + carry;
            Catalan_Num[i][j] = temp % 10;
            carry = temp / 10;
        }
        while(carry) //进位处理
        {
            Catalan_Num[i][len++] = carry % 10;
            carry /= 10;
        }
        carry = 0;
        for(j = len-1; j >= 0; j--) //除法
        {
            temp = carry*10 + Catalan_Num[i][j];
            Catalan_Num[i][j] = temp/(i+1);
            carry = temp%(i+1);
        }
        while(!Catalan_Num[i][len-1]) //高位零处理
        len --;
        NumLen[i] = len;
    }
}
int main(void)
{
    catalan();
    for(int i=1; i<=30; i++){
        for(int j=NumLen[i]-1; j>=0; j--){
            printf("%d", Catalan_Num[i][j]);
        }puts("");
    }
    return 0;
}
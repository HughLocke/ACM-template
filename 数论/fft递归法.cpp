/* fft 快速傅里叶变换
用于加速多项式的乘法,形如
给定一个n次多项式F(x)，和一个m次多项式G(x)。
求出F(x)和G(x)的卷积的题目,常规做法是O(n ^ 2)将系数遍历相乘。
fft先将两个多项式nlogn转化为点值表示法，然后O(n)相乘,最后nlogn转化为系数表示法
注：这里的卷积即两个多项式自然相乘
 */
 //递归法:常数巨大，容易爆栈，一般情况下用迭代法
const int maxn = 1e6 + 10;
const double PI = acos(-1.0);
int N,M,K;
struct complex{
    double x,y;
    complex(){}
    complex(double x,double y):x(x),y(y){}
    friend complex operator - (complex a,complex b){return complex(a.x - b.x,a.y - b.y);}
    friend complex operator + (complex a,complex b){return complex(a.x + b.x,a.y + b.y);}
    friend complex operator * (complex a,complex b){return complex(a.x * b.x - a.y * b.y,a.x * b.y + a.y * b.x);}
}a[maxn << 2],b[maxn << 2]; //最坏情况下是4倍
void FFT(int limit,complex *a,int type){  //limit一定是2的幂次，这样保证每次可以对半分 
    if(limit == 1) return;
    complex a1[limit >> 1],a2[limit >> 1]; //分出奇偶位置上的数
    for(int i = 0 ; i < limit; i += 2){
        a1[i >> 1] = a[i];
        a2[i >> 1] = a[i + 1];
    } 
    FFT(limit >> 1,a1,type);
    FFT(limit >> 1,a2,type);
    complex Wn = complex(cos(2 * PI / limit),type * sin(2 * PI / limit)),w = complex(1,0);
    limit >>= 1;    //Wn为单位元,w为幂次
    for(int i = 0 ; i < limit; i ++, w = w * Wn){
        a[i] = a1[i] + w * a2[i];
        a[i + limit] = a1[i] - w * a2[i];
    }
}
int main(){
    Sca2(N,M);
    for(int i = 0; i <= N ; i ++){a[i].y = 0; scanf("%lf",&a[i].x);}
    for(int j = 0; j <= M ; j ++){b[j].y = 0; scanf("%lf",&b[j].x);}
    int limit = 1;
    while(limit <= N + M) limit <<= 1;//使用的是0~limit - 1这几个数
    FFT(limit,a,1); FFT(limit,b,1);   //系数转化为点值表示
    for(int i = 0; i < limit ; i ++) a[i] = a[i] * b[i];  //点值相乘只要O(n)
    FFT(limit,a,-1);                  //点值转化回系数表示
    for(int i = 0 ; i <= N + M; i ++){
        printf("%d ",(int)(a[i].x / limit + 0.5));  //输出系数
    }
    return 0;
}

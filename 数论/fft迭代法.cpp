//迭代法,发现原位置下标和目标位置下表是二进制下翻转的关系
//因此可以预处理好位置优化，不用递归实现，常数较小较安全
//FFT小贴士:1.一定要看清题目需求决定答案要不要/2,例如只想求a,b组合出的情况，不除2的情况下系数同时表示a和b组合以及b和a组合
//2.如果是自身对自身fft一定要处理好相同位置相乘的情况
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
}a[maxn << 2],b[maxn << 2];
int r[maxn << 2];
void FFT(int limit,complex *A,int *r,int type){  //limit一定是2的幂次，这样保证每次可以对半分 
    for(int i = 0 ; i < limit; i ++) if(i < r[i]) swap(A[i],A[r[i]]);
    for(int mid = 1; mid < limit; mid <<= 1){  //待合并区间长度的一半 
        complex Wn(cos(PI / mid),type * sin(PI / mid)); //单位根,mid只有一半所以分子不用 * 2 
        int len = mid << 1;  //区间长度 
        for(int j = 0; j < limit; j += len){ //j表示更新到的位置 
            complex w(1,0);
            for(int k = 0 ; k < mid; k ++, w = w * Wn){
                complex x = A[j + k],y = w * A[j + mid + k];
                A[j + k] = x + y;
                A[j + mid + k] = x - y;
            }
        }
    }
}
int main(){
    Sca2(N,M);
    for(int i = 0; i <= N ; i ++){a[i].y = 0; a[i].x = read();}
    for(int j = 0; j <= M ; j ++){b[j].y = 0; b[j].x = read();}
    int limit = 1,l = 0; while(limit <= N + M) limit <<= 1,l++;
    for(int i = 0 ; i < limit; i ++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
    FFT(limit,a,r,1); FFT(limit,b,r,1);
    for(int i = 0; i < limit ; i ++) a[i] = a[i] * b[i];
    FFT(limit,a,r,-1);
    for(int i = 0 ; i <= N + M; i ++){
        printf("%d ",(int)(a[i].x / limit + 0.5));
    }
    return 0;
}
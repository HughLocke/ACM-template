/*
线性空间
定义
线性空间是一个关于一下两个运算封闭的向量集合：
1.向量加法a+b，其中a,b为向量
2.标量乘法k∗a，其中a为向量，k为常数
基础概念
1.给定若干个向量a1,a2,...,an，若向量b能够通过a1,a2,...,an经过向量加法和标量乘法得到，则称向量b能够通过a1,a2,...,an表出。
2.对于向量a1,a2,...,an能够表出的所有向量所构成了一个线性空间，称a1,a2,...,an为这个线性空间的生成子集。
3.在一个线性空间中选取若干个向量，若一个向量能够被其他向量表出，则称这些向量线性相关，反之，称这些向量线性无关。
4.线性无关的生成子集成为线性空间的基底，简称基。
4′.另外地，线性空间的极大线性无关子集也称为线性空间的基底，简称基。
5.一个线性空间的所有基包含的向量个数都相等，这个个数称为线性空间的维数。

高斯消元和线性基
对于一个n∗m的矩阵，我们可以把它看做n个长度为m的向量，即它的维数为m。那么如果将这个矩阵看做系数矩阵进行高斯消元，则消元后得到的矩阵中所有非0行代表的向量线性无关。
因为初等行变换就是对每行的向量之间进行向量加法和标量乘法，所以高斯消元的操作并不改变n个向量所能表出的线性空间，则消元后的矩阵的所有非0行所代表的向量就是原线性空间的一个基。
综上所述，我们可以利用高斯消元算法对若干个向量求解其构成线性空间的一个基。
 */
//BZOJ4004
//每个向量有一个权值，求给定矩阵的秩和组成这些秩的向量的最小权值和
//这次不需要解线性方程组了，高斯消元的目的是化简矩阵
const int maxn = 510;
const double eps = 1e-5;  //这个精度可能要调，看AC情况 
int N,M,K;

long double MAP[maxn][maxn]; //long double提升精度
int c[maxn];
void gauss(){
    int num = 0,ans = 0;
    for(int i = 1; i <= min(N,M) ; i ++){
        int r = i;
        for(int j = i + 1; j <= N ; j ++){
            if(fabs(MAP[j][i]) < eps) continue;
            if(fabs(MAP[r][i]) < eps || c[r] > c[j]) r = j; 
        } //每次选取代价最小的基底
        if(fabs(MAP[r][i]) < eps) continue;
        num++; ans += c[r];
        swap(MAP[r],MAP[i]); swap(c[r],c[i]);
        long double div = MAP[i][i];
        for(int j = i; j <= M; j ++) MAP[i][j] /= div;
        for(int j = i + 1; j <= N ; j ++){
            div = MAP[j][i];
            for(int k = i ; k <= M; k ++) MAP[j][k] -= MAP[i][k] * div;
        }
    }
    printf("%d %d",num,ans);
}
int main(){
    Sca2(N,M);
    for(int i = 1; i <= N ; i ++){
        for(int j = 1; j <= M ; j ++){
            cin >> MAP[i][j];
        }
    }
    for(int i = 1; i <= N; i ++) Sca(c[i]);
    gauss();
    return 0;
}
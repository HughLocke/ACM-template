//矩阵快速幂，以对一个3 * 3的矩阵求快速幂为例
struct Mat
{
    LL a[3][3];
    void init(){
        Mem(a, 0);
    }
};
Mat operator * (Mat a, Mat b)
{
    Mat ans; ans.init();
    for(int i = 0 ; i <= 2; i ++)
        for(int j = 0; j <= 2; j ++)
            for(int k = 0 ; k <= 2; k ++)
                ans.a[i][j] = (ans.a[i][j] + a.a[i][k] * b.a[k][j]) % mod;
    return ans;
}
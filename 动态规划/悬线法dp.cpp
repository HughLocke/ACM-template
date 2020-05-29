//悬线法dp，用于处理矩阵相关的dp，例如求解最大的满足某个限制的长方形（正方形） 
//用Left Right两个数组记录这个位置最左端和最右端的满足题目限制的条件。
//用up数组记录 这个位置在满足了左右两端条件之后可向上扩充的最大长度
//然后使用up * (Right - Left + 1)的方法更新答案即可。

//模板：ZJOI2007 棋盘制作 寻找最大的满足01交错的长方形和正方形 
int Left[maxn][maxn],Right[maxn][maxn],up[maxn][maxn];
int MAP[maxn][maxn];
int main()
{
    Sca2(N,M);
    for(int i = 1; i <= N ; i ++){
        for(int j = 1; j <= M ; j ++){
            Sca(MAP[i][j]);
            Left[i][j] = Right[i][j] = j;
            up[i][j] = 1;
        }
    }
    for(int i = 1; i <= N ; i ++){
        for(int j = 2; j <= M ; j ++){
            if(MAP[i][j] != MAP[i][j - 1]){
                Left[i][j] = Left[i][j - 1];
            }
        }
        for(int j = M - 1; j >= 1; j --){
            if(MAP[i][j] != MAP[i][j + 1]){
                Right[i][j] = Right[i][j + 1];
            }
        }
    }
    int ans1 = 0,ans2 = 0;
    for(int i = 1; i <= N ; i ++){
        for(int j = 1; j <= M ; j ++){
            if(i > 1 && MAP[i][j] != MAP[i - 1][j]){
                Left[i][j] = max(Left[i][j],Left[i - 1][j]);
                Right[i][j] = min(Right[i][j],Right[i - 1][j]);
                up[i][j] = up[i - 1][j] + 1;
            }
            int a = Right[i][j] - Left[i][j] + 1;
            int b = min(a,up[i][j]);
            ans1 = max(ans1,b * b);
            ans2 = max(ans2,a * up[i][j]);
        }
    }
    Pri(ans1);
    Pri(ans2);
    return 0;
}
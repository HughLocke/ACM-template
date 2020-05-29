//高斯消元,时间复杂度O(n ^ 3)
/*
高斯消元是求解线性方程组的一种做法。将线性方程组列为矩阵的形式
x1 + 2x2 - x3 = -6       
2x1 + x2 - 3x3 = -9
-x1 - x2 + 2x3 = 7
可以写成
1 2 -1 -6        
0 -3 -1 3
-1 -1 2 7
这么一个矩阵,然后利用初等行变换化为最简求每个变量的值 
 */
 //模板，给出像上述增广矩阵求每个变量的值
int N,M,K;
double MAP[maxn][maxn];
double ans[maxn]; 
void gauss(){
    //化简系数矩阵为01矩阵 
    for(int i = 1; i <= N; i ++){
        int r = i;
        for(int j = i + 1; j <= N ; j ++){
            if(fabs(MAP[r][i]) < fabs(MAP[j][i])) r = j;
        }
        if(fabs(MAP[r][i]) < eps){
            puts("No Solution"); //没有唯一解(无穷多个解) 
            //如果要求解的个数，那么自由元++，答案是2 ^ 自由元
            return ;
        }
        swap(MAP[i],MAP[r]);
        double div = MAP[i][i];
        for(int j = i; j <= N + 1; j ++) MAP[i][j] /= div;
        for(int j = i + 1; j <= N ; j ++){
            div = MAP[j][i];
            for(int k = i ; k <= N + 1; k ++) MAP[j][k] -= MAP[i][k] * div;
        }
    }
    for(int i = N; i >= 1; i --){
        ans[i] = MAP[i][N + 1];
        for(int j = i + 1; j <= N ; j ++){
            ans[i] -= MAP[i][j] * ans[j];
        }
    }
    for(int i = 1; i <= N ; i ++) printf("%.2lf\n",ans[i]);
}
int main(){
    Sca(N);
    for(int i = 1; i <= N ; i ++){
        for(int j = 1; j <= N + 1; j ++){
            scanf("%lf",&MAP[i][j]);
        }
    }
    gauss();
    return 0;
}

/*
高斯消元也可求解一类开关问题
所有开关的的开闭状态从一个指定状态变为src另一个指定状态dst的方法
改变一个开关j会改变另一个开关i的状态aij,可列出方程
a1,1 ^ x1 ^ a1,2 ^ x2 .... ^ a1n ^ xn = src1 ^ dst1
a2,1 ^ x1 ^ a2,2 ^ x2 .....^ a2n ^ xn = src2 ^ dst2 
a为已知系数，src和dst为已知系数，直接高斯消元求解可行种数
种数就是(1 << 自由元个数)
n小的话可以用状态压缩,大的话可以用bitset
 */
 //POJ1830
//有N个相同的开关，每个开关都与某些开关有着联系，每当你打开或者关闭某个开关的时候，其他的与此开关相关联的开关也会相应地发生变化，即这些相联系的开关的状态如果原来为开就变为关，如果为关就变为开。你的目标是经过若干次开关操作后使得最后N个开关达到一个特定的状态。对于任意一个开关，最多只能进行一次开关操作。你的任务是，计算有多少种可以达到指定状态的方法。（不计开关操作的顺序）
const int maxn = 33;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7; 
int N,M,K;
bitset<maxn>MAP[maxn];
int gauss(){
    int cnt = 0;
    for(int i = 1; i <= N ; i ++){
        int r = i;
        for(int j = i + 1; j <= N && !MAP[r][i]; j ++){
            if(MAP[j][i]) r = j;
        }
        if(MAP[i].count() == 1 && MAP[i][N + 1] == 1) return -1;  //注意先判断无解再判断自由元 
        if(!MAP[r][i]){
            cnt++;  //自由元++
            continue; 
        }
        swap(MAP[i],MAP[r]);
        for(int j = i + 1; j <= N ; j ++){
            if(!MAP[j][i]) continue;
            for(int k = i ; k <= N + 1; k ++) MAP[j][k] = MAP[j][k] ^ MAP[i][k];
        }
    }
    return (1 << cnt);
}
int main(){
    int T; Sca(T);
    while(T--){
        Sca(N);
        for(int i = 0 ; i <= N + 1; i ++) MAP[i].reset();
        for(int i = 1; i <= N ; i ++) MAP[i][N + 1] = read();
        for(int i = 1; i <= N ; i ++){
            MAP[i][N + 1] = MAP[i][N + 1] ^ read();
            MAP[i][i] = 1;
        }
        int x,y;
        while(~Sca2(x,y) && x && y) MAP[y][x] = 1;
        int ans = gauss();
        if(~ans) Pri(ans);
        else puts("Oh,it's impossible~!!");
    }
    return 0;
}
/*  ST表
    静态处理区间最大最小值
    不可求和，不可动态
*/
//模板：洛谷P2880 求区间最大值和最小值的差
const int maxn = 50010;
const int SP = 20;
int MAX[maxn][SP];
int MIN[maxn][SP];
int mm[maxn];
void initRMQ(int n,int b[]){         //预处理b数组，长度为n
    for(int i = 1; i <= n ; i ++){
        for(int j = 0; j < SP; j ++){
            MIN[i][j] = INF;
        }
    }
    mm[0] = -1;
    for(int i = 1; i <= n ; i ++){
        mm[i] = ((i & (i - 1)) == 0)?mm[i - 1] + 1:mm[i - 1];
        MIN[i][0] = MAX[i][0] = b[i];
    }
    for(int j = 1; j <= mm[n]; j ++){
        for(int i = 1; i + (1 << j) - 1 <= N ; i ++){
            MAX[i][j] = max(MAX[i][j - 1],MAX[i + (1 << (j - 1))][j - 1]);
            MIN[i][j] = min(MIN[i][j - 1],MIN[i + (1 << (j - 1))][j - 1]);
        }
    }
}
int rmq(int x,int y){
    int k = mm[y - x + 1];
    return max(MAX[x][k],MAX[y - (1 << k) + 1][k]) - min(MIN[x][k],MIN[y - (1 << k) + 1][k]);
}
//倘若我们对模板稍加修改，便可以得到一个求最值下标的ST表
//模板：求区间最大值的下标
const int SP = 20;
int Max[maxn][SP];
int mm[maxn];
void initRMQ(int n,LL b[]){
    mm[0] = -1;
    for(int i = 1; i <= n; i ++){
        mm[i] = ((i & (i - 1)) == 0)?mm[i - 1] + 1:mm[i - 1];
        Max[i][0] = i;
    }
    for(int j = 1; j <= mm[n]; j ++){
        for(int i = 1; i + (1 << j) - 1 <= n ; i ++){
            int x = Max[i][j - 1],y = Max[i + (1 << (j - 1))][j - 1];
            Max[i][j] = b[x] > b[y]?x:y;
        }
    }
}
int rmq(int x,int y,LL b[]){
    int k = mm[y - x + 1];
    return b[Max[x][k]] > b[Max[y - (1 << k) + 1][k]]?Max[x][k]:Max[y - (1 << k) + 1][k];
}
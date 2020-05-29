//二维ST表 n²log(n)²预处理,O(1)查询
//注意空间复杂度不要MLE,SP和maxn能小尽量小
const int maxn = 255;
const int SP = 8;
int N,M,K;
int Max[maxn][maxn][SP][SP],Min[maxn][maxn][SP][SP];
int a[maxn][maxn],fac[20];
inline int max4(int a,int b,int c,int d){
    return max(max(a,b),max(c,d));
}
inline int min4(int a,int b,int c,int d){
    return min(min(a,b),min(c,d));
}
void init(){
    for(int i = 0 ; i < SP; i ++) fac[i] = (1 << i);
    for(int i = 1; i <= N ; i ++){
        for(int j = 1; j <= M ; j ++){
            Min[i][j][0][0] = a[i][j];
            Max[i][j][0][0] = a[i][j];
        }
    }
    int k = (int)(log((double)N) / log(2.0));
    for(int x = 0; x <= k; x++){
        for(int y = 0;y <= k; y++){
            if(x == 0 && y == 0) continue;
            for(int i = 1; i + fac[x] - 1 <= N; i ++){
                for(int j = 1; j + fac[y] - 1 <= M; j ++){
                    if(x == 0){
                        Min[i][j][x][y] = min(Min[i][j][x][y - 1],Min[i][j + (1 << (y - 1))][x][y - 1]);
                        Max[i][j][x][y] = max(Max[i][j][x][y - 1],Max[i][j + (1 << (y - 1))][x][y - 1]);
                    }else{
                        Min[i][j][x][y] = min(Min[i][j][x - 1][y],Min[i + (1 << (x - 1))][j][x - 1][y]);
                        Max[i][j][x][y] = max(Max[i][j][x - 1][y],Max[i + (1 << (x - 1))][j][x - 1][y]);
                    }
                }
            }
        }
    }
}
inline int getmax(int x1,int y1,int x2,int y2){
    int k1 = x2 - x1 + 1,k2 = y2 - y1 + 1;
    k1 = (int)(log((double)k1)/log(2.0));
    k2 = (int)(log((double)k2)/log(2.0));
    return max4(Max[x1][y1][k1][k2],Max[x1][y2 - fac[k2] + 1][k1][k2],Max[x2 - fac[k1] + 1][y1][k1][k2],
    Max[x2 - fac[k1] + 1][y2 - fac[k2] + 1][k1][k2]);
}
inline int getmin(int x1,int y1,int x2,int y2){
    int k1 = x2 - x1 + 1,k2 = y2 - y1 + 1;
    k1 = (int)(log((double)k1)/log(2.0));
    k2 = (int)(log((double)k2)/log(2.0));
    return min4(Min[x1][y1][k1][k2],Min[x1][y2 - fac[k2] + 1][k1][k2],Min[x2 - fac[k1] + 1][y1][k1][k2],
    Min[x2 - fac[k1] + 1][y2 - fac[k2] + 1][k1][k2]);
}
int ans[maxn][maxn];
int main(){
    int B;
    Sca3(N,B,K); M = N;
    for(int i = 1; i <= N ; i ++){
        for(int j = 1; j <= N ; j ++){
            Sca(a[i][j]);
        }
    }
    init();
    for(int i = 1; i <= N ; i ++){
        for(int j = 1; j <= M ; j ++){
            int ii = i + B - 1,jj = j + B - 1;
            ii = min(ii,N); jj = min(jj,M);
            ans[i][j] = getmax(i,j,ii,jj) - getmin(i,j,ii,jj);
        }
    }
    while(K--){
        int x = read(),y = read();
        Pri(ans[x][y]);
    }
    return 0;
}
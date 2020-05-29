//二维前缀和
//模板 hdu6541 给出1e6个全1矩阵，然后查询1e6个矩阵是否为全1矩阵
//做法：先用前缀和求出每个点是否是1，然后转化为01矩阵之后再求一个前缀和
const int maxn = 1e7 + 10;
int N,M,K;
LL MAP[maxn];
int id(int i,int j){
    if(i <= 0 || j <= 0 || i > N || j > M) return 0;
    return (i - 1) * M + j;
}
void add(int i,int j,int x){
    int v = id(i,j);
    if(!v) return;
    MAP[v] += x;
}
int main(){
    while(~Sca2(N,M)){
        int Q = read();
        for(int i = 0 ; i <= N * M; i ++) MAP[i] = 0;
        while(Q--){
            int x1 = read(),y1 = read(),x2 = read(),y2 = read();
            if(x1 > x2) swap(x1,x2);
            if(y1 > y2) swap(y1,y2);
            add(x1,y1,1); 
            add(x1,y2 + 1,-1);
            add(x2 + 1,y1,-1);
            add(x2 + 1,y2 + 1,1);
        }
        for(int i = 1; i <= N; i ++){
            for(int j = 1; j <= M ; j ++){
                MAP[id(i,j)] += MAP[id(i - 1,j)] + MAP[id(i,j - 1)] - MAP[id(i - 1,j - 1)];
            }
        }
        for(int i = 1; i <= N ; i ++){
            for(int j = 1; j <= M ; j ++){
                MAP[id(i,j)] = (MAP[id(i,j)] > 0);
            }
        }
        for(int i = 1; i <= N; i ++){
            for(int j = 1; j <= M ; j ++){
                MAP[id(i,j)] += MAP[id(i - 1,j)] + MAP[id(i,j - 1)] - MAP[id(i - 1,j - 1)];
            }
        }
        Q = read();
        while(Q--){
            int x1 = read(),y1 = read(),x2 = read(),y2 = read();
            if(x1 > x2) swap(x1,x2);
            if(y1 > y2) swap(y1,y2);
            if(1ll * (x2 - x1 + 1) * (y2 - y1 + 1) == MAP[id(x2,y2)] + MAP[id(x1 - 1,y1 - 1)] - MAP[id(x2,y1 - 1)] - MAP[id(x1 - 1,y2)])
                puts("YES");
            else 
                puts("NO");
        }
    }
    return 0;
}

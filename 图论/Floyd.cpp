//用于求任意两点间最短距离
//传递闭包：所有两两之间的连通关系
for(int k = 1; k <= N ; k ++){
    for(int i = 1; i <= N ; i ++){
        for(int j = 1; j <= N; j ++){
            MAP[i][j] = min(MAP[i][j],MAP[i][k] + MAP[k][j]);
        }
    }
}

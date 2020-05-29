//图上Hash
//当一个点和他连到的点组成的集合和另一个点和他连到的点组成的集合完全相同的话，那么他们的Hash值相同
ULL Hash[maxn],id[maxn];
for(int i = 1; i <= N ; i ++ ) Hash[i] = id[i] = id[i - 1] * 3;
for(int i = 1; i <= M ; i ++ ){
    int u,v; Sca2(u,v);
    add(u,v); add(v,u);
    Hash[u] += id[v]; Hash[v] += id[u];
}
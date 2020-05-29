//离散化，模板：离散N条线段
int Hash[maxn * 2];
int cnt = 0;
for(int i = 1; i <= N; i ++){
    line[i].fi = read(); line[i].se = read();
    Hash[++cnt] = line[i].fi; Hash[++cnt] = line[i].se;
}
sort(Hash + 1,Hash + 1 + cnt);
cnt = unique(Hash + 1,Hash + 1 + cnt) - Hash - 1;
for(int i = 1; i <= N ; i ++){
    line[i].fi = lower_bound(Hash + 1,Hash + 1 + cnt,line[i].fi) - Hash;
    line[i].se = lower_bound(Hash + 1,Hash + 1 + cnt,line[i].se) - Hash;
}
//手写链表，可用于优化某些需要反复删除的数组。

int pre[maxn],nxt[maxn];
void del(int x){         //删除x结点 
    nxt[pre[x]] = nxt[x];
    pre[nxt[x]] = pre[x];
}
void init(){            //初始化 
    nxt[N] = 0;
    for(int i = 1; i <= N ; i ++){
        nxt[i - 1] = i; pre[i] = i - 1;
    }
}
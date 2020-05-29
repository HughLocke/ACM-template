//可撤销并查集，可以将并查集的操作倒回到n步之前
//用一个栈存储进行的操作，倒回的时候依次退栈即可。
//不可以使用路径压缩，只能用按秩合并（size小的连到size大的上去）优化 
int Stack[maxn],size[maxn];
int fa[maxn],top;
int now;
void init(){
    for(int i = 1; i <= N ; i ++){
        fa[i] = -1;size[i] = 0;
    } 
    top = 0;
}
int find(int x){
    while(fa[x] != -1) x = fa[x];
    return x;
}
bool Union(int x,int y){
    x = find(x); y = find(y);
    if(x == y) return false;
    if(size[x] > size[y]) swap(x,y);
    Stack[top++] = x;
    fa[x] = y;
    size[y] += size[x] + 1;
    now--;
    return true;
}
void rewind(int t){
    while(top > t){
        int x = Stack[--top];
        size[fa[x]] -= size[x] + 1;
        fa[x] = -1;
        now++;
    }
}


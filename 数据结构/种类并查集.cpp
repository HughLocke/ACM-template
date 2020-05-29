//带权并查集 （又称种类并查集）
//除了tree用来记录是否在同一个集合，利用group数组来记录当前节点和父亲结点的关系
int find(int x){
    if (x == tree[x]) return x;
    int fx = find(tree[x]);
    group[x] = (group[tree[x]] + group[x] + 2) % 2; //孙子和爷爷的关系 = 孙子和父亲的关系 + 父亲和爷爷的关系
    tree[x] = fx;
    return fx;
}
void Union(int a, int b){
    int fa = find(a),fb = find(b);
    if (fa != fb){
        group[fa] = (-group[a] + 1 + group[b] + 2) % 2; // 父节点和 x 的关系，x和 y 的关系，y 和父节点的关系
        tree[fa] = fb;
    }
}
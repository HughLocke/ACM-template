//字典树
//模板：洛谷P2580 给定N个单词，查询M个单词在其中是否出现过以及是否第一次出现
//用空间换取时间的静态实现（跑得更快内存更大）
const int maxn = 500010;
int N,M,K;
int nxt[maxn][28];
int val[maxn],cnt;
char str[100];
void insert(char *s){
    int p = 1;
    for(int i = 0; str[i]; i ++){
        int id = str[i] - 'a';
        if(!nxt[p][id]) nxt[p][id] = ++cnt;
        p = nxt[p][id];
    }
    val[p] = 1;
}
void query(char *s){
    int p = 1;
    for(int i = 0; str[i]; i ++){
        int id = str[i] - 'a';
        if(!nxt[p][id]){
            puts("WRONG");
            return; 
        }
        p = nxt[p][id];
    }
    if(val[p] == 0) puts("WRONG");
    else if(val[p] == 1){
        puts("OK"); val[p] = 2;
    }else{
        puts("REPEAT");
    }
}
int main(){
    Sca(N); cnt = 0;
    for(int i = 1; i <= N; i ++){
        scanf("%s",str);
        insert(str);    
    }
    Sca(M);
    while(M--){
        scanf("%s",str);
        query(str);
    }
    return 0;
}


//用时间换取空间的动态实现（跑的更慢空间更小）
int N,M,K;
struct node{
    node* nxt[26];
    int val;
}*root;
char str[100];
node* newnode(){
    node *p = new node();
    p->val = 0;
    for(int i = 0 ; i < 26; i ++) p->nxt[i] = NULL;
    return p;
}
void insert(char *s){
    node* p = root;
    for(int i = 0; str[i]; i ++){
        int id = str[i] - 'a';
        if(p->nxt[id] == NULL) p->nxt[id] = newnode();
        p = p->nxt[id];
    }
    p->val = 1;
}
void query(char *s){
    node* p = root;
    for(int i = 0; str[i]; i ++){
        int id = str[i] - 'a';
        if(p->nxt[id] == NULL){
            puts("WRONG");
            return; 
        }
        p = p->nxt[id];
    }
    if(p->val == 0) puts("WRONG");
    else if(p->val == 1){
        puts("OK"); p->val = 2;
    }else{
        puts("REPEAT");
    }
}
void deal(node *p){
    for(int i = 0 ; i < 26; i ++) if(p->nxt[i]) deal(p->nxt[i]);
    free(p);
}
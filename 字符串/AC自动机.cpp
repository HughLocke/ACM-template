//AC自动机，在文本串里寻找有多少个模式串出现过
const int maxn = 1e6 + 10;
const int INF = 0x3f3f3f3f; 
int N,M,K;
struct AC{
    int next[maxn][26],tot,fail[maxn],end[maxn],root;
    int newnode(){
        for(int i = 0 ; i < 26; i ++) next[tot][i] = -1;
        end[tot++] = 0;
        return tot - 1;
    }
    void init(){
        tot = 0;
        root = newnode();
    }
    void insert(char *str){
        int p = root;
        for(int i = 0 ; str[i] ; i ++){
            int id = str[i] - 'a';
            if(next[p][id] == -1) next[p][id] = newnode();
            p = next[p][id];
        }
        end[p]++;
    }
    void Build(){
        queue<int>Q;
        fail[root] = root;
        for(int i = 0 ; i < 26; i ++){
            if(~next[root][i]){
                fail[next[root][i]] = root;
                Q.push(next[root][i]);
            }else{
                next[root][i] = root;
            } 
        }
        while(!Q.empty()){
            int u = Q.front(); Q.pop();
            for(int i = 0 ; i < 26; i ++){
                if(~next[u][i]){
                    fail[next[u][i]] = next[fail[u]][i];
                    Q.push(next[u][i]);
                }else next[u][i] = next[fail[u]][i];
            }
        }
    }
    int query(char *str){
        int p = root,ans = 0;
        for(int i = 0; str[i]; i ++){
            int id = str[i] - 'a';
            p = next[p][id];
            int tmp = p;
            while(~end[tmp]){
                ans += end[tmp];
                end[tmp] = -1;
                tmp = fail[tmp];
            }
        }
        return ans;
    }
}ac;
char str[maxn];
int main(){
    Sca(N);
    ac.init();
    for(int i = 1; i <= N ; i ++){
        scanf("%s",str);
        ac.insert(str);
    } 
    ac.Build();
    scanf("%s",str);
    Pri(ac.query(str));
    return 0;
}
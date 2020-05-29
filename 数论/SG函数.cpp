/* SG函数
必败态：当前状态不管怎么选择，只要对手采取最优策略就败
必胜态：当前状态只要你采取最优策略就胜
1.当某个局面导向的所有状态都是必胜态时候，当前状态必败
2.当某个局面导向有一个状态是必败的时候，当前状态必胜
3.SG(x) = mex{SG(y1),SG(y2),SG(y3)...SG(yk)} 其中y1..yk是x导向的所有状态
当SG(x) > 0时说明当前状态必胜，SG(x) < 0时说明当前状态必败
4.多个有向图游戏的和SG函数值等于他包含的各个子游戏的异或和
SG(G) = SG(G1) ^ SG(G2) ^ SG(G3)..... ^ SG(Gm) 
SG可以通过递推或者记忆化搜索等方式求出
*/
//模板:总共n堆石子，每个人只能抓2的幂次(1,2,4,8...)个石子，轮流抓取抓不到石头的输
const int maxn = 1010;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7; 
int N,M,K;
int sg[maxn];
int step[maxn];  //step存储可以走的步数，step[0]存储有多少种走法
bool vis[maxn];
void getsg(){   //直接递推 
    sg[0] = 0;
    for(int i = 1; i <= 1000; i ++){
        for(int j = 0 ; j <= i ; j ++) vis[j] = 0;
        for(int j = 1; j <= step[0]; j ++){   
            if(step[j] > i) break; //step需要从小到大排序 
            vis[sg[i - step[j]]] = 1;
        }
        for(int j = 0; j <= i ; j ++){
            if(vis[j]) continue;
            sg[i] = j; break;
        }
    }
}

int main(){
    step[0] = 10; step[1] = 1;
    for(int i = 2; i <= 10 ; i ++) step[i] = step[i - 1] * 2;
    getsg();
    while(~Sca(N)){
        if(sg[N]) puts("Kiki");  //先手胜
        else puts("Cici");   //后手胜 
    }
    return 0;
}
/*模拟退火
1.是一种随机算法,AC不AC靠脸的算法,如果不过可能需要多交几发证明确实这个算法过不了
2.当我们知道一个状态以及一个状态下的答案的时候，我们可以随机变换这个状态的变量并且像退火一样,一开始变很多(温度高),
然后变得少(温度低)直到冷却，每次都向更优秀的状态靠近，到最后就有可能随机到我们想要的状态
3.T温度,delta温度系数,t > eps(1e-18)是冷却点，这些参数决定了模拟退火的次数和精度还有时间
4.带exp的那个公式是模拟退火的固定公式,这样的概率被证明是最优的
5.这个算法在计算几何里面比较常用，例如最小圆覆盖 可以三分套三分再套三分也可以模拟退火
 */
/*模板1:桌子上一个点被N个悬挂着w重量的小球拉着，求平衡点(重力势能最低点)
当我们知道了点的时候我们可以很容易得计算这个点的重力势能(energe),所以我们模拟退火他的坐标点
 */
const int maxn = 2010;
int N,M,K;
struct Node{
    double x,y,w;
    Node(double x = 0,double y = 0,double w = 0):x(x),y(y),w(w){}
}node[maxn];
double energe(double x,double y){ //计算x,y点的势能 
    double sum = 0;
    for(int i = 1; i <= N ;  i++){
        double dx = x - node[i].x,dy = y - node[i].y;
        sum += sqrt(dx * dx + dy * dy) * node[i].w;
    }
    return sum;
}
double xans,yans; //answer
double ans = 1e18 + 7; //势能,需要寻找最小值,初始为INF
const double delta = 0.998;  //4.降温系数可以调整,需要十分接近1 
 
void s_a(){   //模拟退火 
    double xx = xans,yy = yans; //初始位置
    double t = 3000;   //3.温度需要足够高 
    while(t > 1e-18){  //5.eps要低一点 
        double xtmp = xx + (rand() * 2 - RAND_MAX) * t;
        double ytmp = yy + (rand() * 2 - RAND_MAX) * t;
        //随机一个新坐标，变化幅度为t
        //rand() * 2 - RAND_MAX的范围是-RAND_MAX - RANDMAX - 1
        double new_ans = energe(xtmp,ytmp);  //计算当前状态下的值
        double DE = new_ans - ans;
        if(DE < 0){ //更优解 
            xans = xx = xtmp; yans = yy = ytmp;
            ans = new_ans;
        }else if(exp(-DE/t) * RAND_MAX > rand()){  //更差解的话随机是否接受 
            xx = xtmp,yy = ytmp;
        }
        t *= delta;
    } 
} 

void SA(){   //2.多跑几遍模拟退火 
    s_a(); s_a();
    s_a(); s_a();
    s_a(); s_a();
}
int main(){
    Sca(N); srand(time(NULL)); 
    for(int i = 1; i <= N ; i ++){
        scanf("%lf%lf%lf",&node[i].x,&node[i].y,&node[i].w);
        xans += node[i].x; yans += node[i].y; 
    } 
    xans /= N; yans /= N;  //1.取平均值作为初始值 
    ans = energe(xans,yans);
    SA(); 
    printf("%.3lf %.3lf",xans,yans);
    return 0;
}

/* luoguP4360
模板2：伐木场选址，一条数轴上选择两个点使得这条其他点到这条数轴的花费最小，花费计算以及在fun(a,b)中搞定
模拟退火部分:随便选两个点作为数轴上的初始答案，然后模拟退火随机让两个点往左右方向移动,最终选定出状态下
fun(a,b)最小的ansa,ansb
 */

LL w[maxn],d[maxn],sum;
LL fun(int& a,int& b){
    if(a > b) swap(a,b);
    return d[a] * w[a] + (w[b] - w[a]) * d[b] + d[N + 1] * (w[N] - w[b]) - sum;
}
int ansa,ansb,ans;
const double delta = 0.998; //退火系数
void s_a(){
    double t = 30000;  //温度
    int a = ansa,b = ansb;
    while(t > 1e-14){
        int atmp = a + (rand() * 2 - RAND_MAX) * t; atmp = (atmp % N + N) % N; atmp++;
        int btmp = a + (rand() * 2 - RAND_MAX) * t; btmp = (btmp % N + N) % N; btmp++;  //两个点向两边随机移动
        LL new_ans = fun(btmp,atmp);
        LL DE = new_ans - ans;
        if(DE < 0){
            ansa = a = atmp; ansb = b = btmp;
            ans = new_ans;
        }else if(exp(-DE / t) * RAND_MAX > rand()){
            a = atmp; b = btmp;
        }
        t *= delta;
    }
}
void SA(){
    s_a();s_a();s_a();
    s_a();s_a();s_a();
}
int main(){
    Sca(N); srand(time(NULL));
    for(int i = 1; i <= N; i ++){
        Scl(w[i]); Scl(d[i + 1]);
        sum += w[i] * d[i];
        w[i] += w[i - 1];
        d[i + 1] += d[i];
        
    } 
    ansa = 1,ansb = N; ans = fun(ansa,ansb);
    SA();
    Prl(fun(ansa,ansb));
    return 0;
}

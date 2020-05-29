//凸包
struct Point{
    double x,y;
    Point(){}
    Point(double x,double y):x(x),y(y){}
    Point operator - (Point a){
        return Point(x - a.x,y - a.y);
    }
}point[maxn]; 
bool cmp(Point a,Point b){
    return a.x != b.x?a.x < b.x:a.y < b.y;
}
Point Stack[maxn];
double Cross(Point a,Point b){
    return a.x * b.y - a.y * b.x;
}
int ConvexHull(Point* p,int N,Point* S){
    int cnt = 0;
    for(int i = 1; i <= N ; i ++){
        while(cnt >= 2 && Cross(S[cnt] - S[cnt - 1],p[i] - S[cnt - 1]) <= 0) cnt--; // < 就包括凸包上的点，<=不包括凸包边上的点  
        S[++cnt] = p[i];
    }
    int k = cnt;
    for(int i = N; i >= 1; i --){
        while(cnt >= k + 2 && Cross(S[cnt] - S[cnt - 1],p[i] - S[cnt - 1]) <= 0) cnt--;
        S[++cnt] = p[i];
    } 
    if(N > 1) cnt--;
    return cnt;
}
int main(){
    Sca(N);
    for(int i = 1; i <= N ; i ++) scanf("%lf%lf",&point[i].x,&point[i].y);
    sort(point + 1,point + 1 + N,cmp);
    printf("%d",ConvexHull(point,N,Stack));
    return 0;
}
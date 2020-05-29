double simpson(double l, double r){
    double mid = (l+r)/2;
    return (f(l)+4*f(mid)+f(r))*(r-l)/6;
}


double jifen(double L, double R, double eps,double ST){
    //计算[L,R]上的定积分
    double mid = (L+R)/2;
    double SL = simpson(L,mid); //左半边
    double SR = simpson(mid,R); //右
    if(fabs(SL+SR-ST) <= 15*eps)
        return SL+SR+(SL+SR-ST)/15; //误差足够小，直接返回结果
    return jifen(L, mid, eps/2,SL) + jifen(mid, R, eps/2,SR); //继续分

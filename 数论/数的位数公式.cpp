//求一个数x的位数的公式
//x的位数 = log10(x) + 1
/*
    例题：洛谷P2759，求x ^ x大于等于n位数的最小x
    将log(x ^ x) 化为x * log(x),二分查找即可 
*/
LL N;
bool check(LL x){
    return x * log10(x) + 1 >= N;
}
LL solve(){
    LL l = 0,r = N;
    LL ans = 0;
    while(l <= r){
        LL m = (l + r) >> 1;
        if(check(m)){
            r = m - 1;
            ans = m;
        }else{
            l = m + 1;
        }
    }
    return ans;
}
int main(){
    Scl(N);
    Prl(solve());
    return 0;
}
